using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services;
using System.Data.SqlClient;
using System.Data;
using BatchPay.Entity;

namespace BatchPay
{
    /// <summary>
    /// BatchPayInterface 的摘要说明
    /// </summary>
    [WebService(Namespace = "http://tempuri.org/")]
    [WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
    [System.ComponentModel.ToolboxItem(false)]
    // 若要允许使用 ASP.NET AJAX 从脚本中调用此 Web 服务，请取消对下行的注释。
    // [System.Web.Script.Services.ScriptService]
    public class BatchPayInterface : System.Web.Services.WebService
    {

        [WebMethod]
        public Report BatchPayChinaMobile(string data, string userName, string passwd)
        {
            return BatchPay(data, userName, passwd, "移动客户端");
        }

        [WebMethod]
        public Report BatchPayChinaUnicom(string data, string userName, string passwd)
        {
            return BatchPay(data, userName, passwd, "联通电信客户端");
        }

        public Report BatchPay(string data, string userName, string passwd, string clientType)
        {
            string SP = "";
            if (clientType == "移动客户端") 
            {
                SP = "移动";
            }
            else if (clientType == "联通电信客户端")
            {
                SP = "联通电信";
            }

            //构造数据
            List<RecordItem> list = new List<RecordItem>();

            var report = new Report();
            //初始化返回结果
            report.count = 0;
            report.failCount = 0;
            report.succCount = 0;
            report.totalMoney = 0;
            report.listSucc = new List<RecordItem>();
            report.listFail = new List<RecordItem>();

            if (string.IsNullOrEmpty(data) ||
                    string.IsNullOrEmpty(userName) ||
                        string.IsNullOrEmpty(passwd))
            {
                report.result = "参数不能为空";
                return report;
            }

            try
            {
                string[] tmp = data.Split('|');
                foreach (string str in tmp)
                {
                    if (string.IsNullOrEmpty(str)) continue;
                    string[] d = str.Split(',');
                    RecordItem item = new RecordItem();
                    if (d.Length != 2) continue;
                    item.phoneNo = d[0];
                    item.money = Convert.ToDouble(d[1]);
                    item.id = Guid.Empty;
                    list.Add(item);
                }
                report.count = list.Count;
            }
            catch (Exception)
            {
                report.result = "非法的参数";
                return report;
            }

            string userId = UserValidator.ValidateLogging(userName, passwd, clientType);
            if (string.IsNullOrEmpty(userId))
            {
                //不合法的请求调用
                report.result = "用户名或密码不正确";
                return report;
            }

            //验证权限
            if (!AuthorizationHelper.validate(userId).Contains("批量缴费"))
            {
                report.result = "您的账号没有缴费的权限";
                return report;
            }

            string userLevel = "";  //用户级别
            double currentMoney = 0;//当前账户余额
            double totalMoney = 0;
            //计算缴费总金额
            foreach (RecordItem payWithListItem in list)
            {
                totalMoney += payWithListItem.money;
            }
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    //判断余额是否充足
                    using (var cmd = new SqlCommand())
                    {
                        /*判断账户余额是否充足*/
                        cmd.CommandText = "select 账户余额,用户级别  from 网点用户 Where [Id] = '" + userId + "'";
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;
                        using (SqlDataReader sdr = cmd.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {
                                    currentMoney = Convert.ToDouble(sdr["账户余额"].ToString());
                                    if (currentMoney < totalMoney)
                                    {
                                        report.result = "错误!您当前的余额为：" + currentMoney + "，不足以支付总和的" + totalMoney + "元";
                                        report.count = list.Count;
                                        report.succCount = 0;
                                        report.failCount = list.Count;
                                        return report;
                                    }
                                    userLevel = sdr["用户级别"].ToString();
                                }
                                sdr.Close();
                            }
                        }
                    }

                    //循环处理每一条缴费记录
                    foreach (RecordItem payWithListItem in list)
                    {
                        string phoneNo = "";
                        double money = 0;

                        //号码合法性验证
                        if (payWithListItem.phoneNo.Substring(0,4) == "0871")
                        {
                            if (payWithListItem.phoneNo.Length != 12)
                            {
                                report.failCount++;
                                report.listFail.Add(payWithListItem);
                                continue;
                            }
                            else
                            {
                                phoneNo = payWithListItem.phoneNo;
                            }
                        } else {                                     
                            if (payWithListItem.phoneNo.Length != 11)
                            {
                                report.failCount++;
                                report.listFail.Add(payWithListItem);
                                continue;
                            }
                            else
                            {
                                phoneNo = payWithListItem.phoneNo;
                            }
                        }

                        //钱合法性验证
                        if (payWithListItem.money <= 0)
                        {
                            report.failCount++;
                            report.listFail.Add(payWithListItem);
                            continue;
                        }
                        else
                        {
                            money = payWithListItem.money;
                        }

                        string location = "";   //号码归属地,http查询得到，部分数据库提取
                        string area = "";       //地区，数据库提取
                        double returnPoint = -1; //返款比例
                        string noType = "";     //号码的运营商

                        //座机缴费判断
                        if (phoneNo.Substring(0, 1) == "0")
                        {
                            //座机缴费合法性验证
                            if (SP != "联通电信")
                            {
                                report.failCount++;
                                report.listFail.Add(payWithListItem);
                                continue;
                            }

                            //号码归属地查询
                            using (var cmd31 = new SqlCommand())
                            {
                                /*取相关参数进行缴费*/
                                string tel4 = phoneNo.Substring(0, 4);
                                cmd31.CommandText = "select *  from 号码归属 Where [区号] = '" + tel4 + "'";
                                cmd31.CommandType = CommandType.Text;
                                cmd31.Connection = con;
                                using (SqlDataReader sdr = cmd31.ExecuteReader())// cmd2.ExecuteNonQuery();
                                {

                                    if (sdr.HasRows)
                                    {
                                        if (sdr.Read())
                                        {

                                            location = sdr["省份"].ToString() + sdr["城市"].ToString();
                                            area = sdr["地区"].ToString();
                                        }
                                        sdr.Close();
                                    }
                                }
                            }
                            //号码类型
                            noType = "电信";
                        }
                        else
                        {
                            //手机缴费判断
                            using (var cmd0 = new SqlCommand())
                            {
                                string NoFront = phoneNo.Substring(0, 3);
                                string NoFrontValidate = "";
                                /*判断缴费号码的合法性*/
                                if (SP == "移动")
                                {
                                    cmd0.CommandText = "select Name from [MobileManage].[dbo].[URP_DIC_Content] Where [Category] = '移动'";
                                }
                                else if (SP == "联通电信")
                                {
                                    cmd0.CommandText = "select Name from [MobileManage].[dbo].[URP_DIC_Content] Where [Category] = '联通' or [Category] = '电信'";
                                }

                                //验证运营商
                                cmd0.CommandType = CommandType.Text;
                                cmd0.Connection = con;
                                using (SqlDataReader sdr = cmd0.ExecuteReader())// cmd2.ExecuteNonQuery();
                                {

                                    if (sdr.HasRows)
                                    {
                                        while (sdr.Read())
                                        {
                                            NoFrontValidate += sdr["Name"].ToString() + ",";

                                        }
                                        sdr.Close();
                                        if (!NoFrontValidate.Contains(NoFront))
                                        {
                                            report.failCount++;
                                            report.listFail.Add(payWithListItem);
                                            continue;
                                        }
                                    }
                                }
                            }

                            //号码归属地查询
                            using (var cmd3 = new SqlCommand())
                            {
                                /*取相关参数进行缴费*/
                                string tel7 = phoneNo.Substring(0, 7);
                                cmd3.CommandText = "select *  from 号码归属 Where [号段] = '" + tel7 + "'";
                                cmd3.CommandType = CommandType.Text;
                                cmd3.Connection = con;
                                using (SqlDataReader sdr = cmd3.ExecuteReader())// cmd2.ExecuteNonQuery();
                                {

                                    if (sdr.HasRows)
                                    {
                                        if (sdr.Read())
                                        {

                                            location = sdr["省份"].ToString() + sdr["城市"].ToString();
                                            area = sdr["地区"].ToString();
                                        }
                                        sdr.Close();
                                    }
                                }
                            }

                            //提取号码的分类
                            using (var cmd_fl = new SqlCommand())
                            {
                                string tel3 = phoneNo.Substring(0, 3);
                                cmd_fl.CommandText = "select [Category]  from [dbo].[URP_DIC_Content] Where [Name]='" + tel3 + "'";
                                cmd_fl.CommandType = CommandType.Text;
                                cmd_fl.Connection = con;
                                using (SqlDataReader sdr = cmd_fl.ExecuteReader())// cmd2.ExecuteNonQuery();
                                {

                                    if (sdr.HasRows)
                                    {
                                        while (sdr.Read())
                                        {
                                            noType = sdr["Category"].ToString();
                                            if (noType == "移动" || noType == "联通" || noType == "电信") break;
                                        }
                                        sdr.Close();
                                    }
                                }
                            }
                        }

                        //一些不合法的状态，需要补充数据库的值
                        if (string.IsNullOrEmpty(noType) || string.IsNullOrEmpty(area) || string.IsNullOrEmpty(userLevel))
                        {
                            report.failCount++;
                            report.listFail.Add(payWithListItem);
                            continue;
                        }

                        //判断该缴费接口打开没
                        using (var cmd = new SqlCommand())
                        {
                            /*判断账户余额是否充足*/
                            cmd.CommandText = "select *  from [dbo].[URP_DIC_Content] Where [Category]='号码提交设置' and [Code]='" + noType + "' and [附加字段1]='" + area + "'";
                            cmd.CommandType = CommandType.Text;
                            cmd.Connection = con;
                            using (SqlDataReader sdr = cmd.ExecuteReader())// cmd2.ExecuteNonQuery();
                            {

                                if (sdr.HasRows)
                                {
                                    while (sdr.Read())
                                    {
                                        string isEnable = sdr["附加字段2"].ToString();
                                        if (isEnable != "启用")
                                        {
                                            report.failCount++;
                                            report.listFail.Add(payWithListItem);
                                            continue;
                                        }
                                    }
                                    sdr.Close();
                                }
                            }
                        }

                        using (var cmd = new SqlCommand())
                        {
                            /*判断账户余额是否充足*/
                            cmd.CommandText = "select 账户余额  from 网点用户 Where [Id] = '" + userId + "'";
                            cmd.CommandType = CommandType.Text;
                            cmd.Connection = con;
                            using (SqlDataReader sdr = cmd.ExecuteReader())// cmd2.ExecuteNonQuery();
                            {

                                if (sdr.HasRows)
                                {
                                    while (sdr.Read())
                                    {
                                        currentMoney = Convert.ToDouble(sdr["账户余额"].ToString());
                                        if (currentMoney < money)
                                        {
                                            report.failCount++;
                                            report.listFail.Add(payWithListItem);
                                            continue;
                                        }
                                    }
                                    sdr.Close();
                                }
                            }
                        }

                        //提取返款比例
                        using (var cmd5 = new SqlCommand())
                        {
                            cmd5.CommandText = "select [返款比例]  from [dbo].[返款比例明细] Where [返款类型]='手机缴费返款' and [返款项目]='" + noType + "' and [地区]='" + area + "' and [用户级别] = '" + userLevel + "'";
                            cmd5.CommandType = CommandType.Text;
                            cmd5.Connection = con;
                            using (SqlDataReader sdr = cmd5.ExecuteReader())// cmd2.ExecuteNonQuery();
                            {

                                if (sdr.HasRows)
                                {
                                    while (sdr.Read())
                                    {
                                        if (!String.IsNullOrEmpty(sdr["返款比例"].ToString()))
                                            returnPoint = Convert.ToDouble(sdr["返款比例"].ToString());
                                    }
                                    sdr.Close();
                                }
                            }
                        }

                        //未设置返款比例
                        if (returnPoint == -1)
                        {
                            report.failCount++;
                            report.listFail.Add(payWithListItem);
                            continue;
                        }

                        //缴费，附带扣款，但是返款未计算
                        using (var cmd4 = new SqlCommand())
                        {
                            cmd4.CommandText = "Function_网点用户_缴费";
                            cmd4.CommandType = CommandType.StoredProcedure;
                            cmd4.Connection = con;
                            var sp1 = new SqlParameter("@缴费客户号码", SqlDbType.NVarChar, 50);
                            sp1.Direction = ParameterDirection.Input;
                            cmd4.Parameters.Add(sp1);
                            sp1.Value = phoneNo;

                            var sp2 = new SqlParameter("@缴费金额", SqlDbType.Money);
                            sp2.Direction = ParameterDirection.Input;
                            cmd4.Parameters.Add(sp2);
                            sp2.Value = Convert.ToDouble(money);

                            var sp3 = new SqlParameter("@号码归属", SqlDbType.NVarChar, 50);
                            sp3.Direction = ParameterDirection.Input;
                            cmd4.Parameters.Add(sp3);
                            sp3.Value = location;

                            var sp4 = new SqlParameter("@地区", SqlDbType.NVarChar, 50);
                            sp4.Direction = ParameterDirection.Input;
                            cmd4.Parameters.Add(sp4);
                            sp4.Value = area;

                            var sp5 = new SqlParameter("@网点用户Id", SqlDbType.UniqueIdentifier);
                            sp5.Direction = ParameterDirection.Input;
                            cmd4.Parameters.Add(sp5);
                            Guid userIdGuid = new Guid(userId);
                            sp5.Value = userIdGuid;

                            var _sp5 = new SqlParameter("@网点用户登录名", SqlDbType.NVarChar, 50);
                            _sp5.Direction = ParameterDirection.Input;
                            cmd4.Parameters.Add(_sp5);
                            _sp5.Value = userName;

                            var sp6 = new SqlParameter("@返款金额", SqlDbType.Money);
                            sp6.Direction = ParameterDirection.Input;
                            cmd4.Parameters.Add(sp6);
                            double repay = Convert.ToDouble(money) * returnPoint;
                            sp6.Value = repay;

                            var sp7 = new SqlParameter("@运营商", SqlDbType.NVarChar, 50);
                            sp7.Direction = ParameterDirection.Input;
                            cmd4.Parameters.Add(sp7);
                            sp7.Value = noType;

                            var sp8 = new SqlParameter("@订单Id", SqlDbType.UniqueIdentifier)
                            {
                                Direction = ParameterDirection.Output
                            };
                            cmd4.Parameters.Add(sp8);

                            cmd4.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                            cmd4.ExecuteNonQuery();
                            var res = cmd4.Parameters["@RETURN_VALUE"].Value.ToString();

                            if (res.Equals("1"))
                            {
                                report.succCount++;
                                report.totalMoney += money;
                                payWithListItem.id = new Guid(sp8.Value.ToString());
                                report.listSucc.Add(payWithListItem);
                                continue;
                            }
                            else
                            {
                                report.failCount++;
                                report.listFail.Add(payWithListItem);
                                continue;
                            }
                        }
                    }
                    string result = "批量缴费成功！\n共计" + report.count.ToString() + "条记录\n"
                                + "成功缴费:" + report.succCount.ToString() + "条\n"
                                + "失败:" + report.failCount.ToString() + "条\n"
                                + "缴费总金额:" + report.totalMoney.ToString() + "元";
                    report.result = result;
                    return report;
                }
                catch (Exception ex)
                {
                    throw new Exception(ex.Message);
                }
                finally
                {
                    con.Close();
                }
            }
        }

        [WebMethod]
        public PaymentItem GetPaymentRecordChinaMobile(string id, string userName, string passwd)
        {
            return GetPaymentRecord(id, userName, passwd, "移动客户端");
        }

        [WebMethod]
        public PaymentItem GetPaymentRecordChinaUnicom(string id, string userName, string passwd)
        {
            return GetPaymentRecord(id, userName, passwd, "联通电信客户端");
        }
        /*
        public GetPaymentListResult GetPaymentRecord(string data, string userName, string passwd, string clientType)
        {
            //构造数据
            List<RecordItem> list = new List<RecordItem>();

            var result = new GetPaymentListResult();
            //初始化返回结果
            result.result = "";
            result.count = 0;
            result.failedCount = 0;
            result.successCount = 0;
            result.listFail = new List<RecordItem>();
            result.listSucc = new List<PaymentItem>();

            if (string.IsNullOrEmpty(data) ||
                    string.IsNullOrEmpty(userName) ||
                        string.IsNullOrEmpty(passwd))
            {
                result.result = "参数不能为空";
                return result;
            }

            try
            {
                string[] tmp = data.Split('|');
                foreach (string str in tmp)
                {
                    if (string.IsNullOrEmpty(str)) continue;
                    string[] d = str.Split(',');
                    RecordItem item = new RecordItem();
                    if (d.Length != 2) continue;
                    item.phoneNo = d[0];
                    item.money = Convert.ToDouble(d[1]);
                    list.Add(item);
                }
                result.count = list.Count;
            }
            catch (Exception)
            {
                result.result = "非法的参数";
                return result;
            }

            string userId = UserValidator.ValidateLogging(userName, passwd, clientType);
            if (string.IsNullOrEmpty(userId))
            {
                //不合法的请求调用
                result.result = "用户名或密码不正确";
                return result;
            }

            //验证权限
            if (!AuthorizationHelper.validate(userId).Contains("批量缴费"))
            {
                result.result = "您的账号没有缴费的权限";
                return result;
            }

            //循环处理每一条缴费记录
            foreach (RecordItem item in list)
            {
                string phoneNo = "";
                double money = 0;
                //号码合法性验证
                if (item.phoneNo.Length != 11)
                {
                    result.failedCount++;
                    result.listFail.Add(item);
                    continue;
                }
                else
                {
                    phoneNo = item.phoneNo;
                }
                //钱合法性验证
                if (item.money <= 0)
                {
                    result.failedCount++;
                    result.listFail.Add(item);
                    continue;
                }
                else
                {
                    money = item.money;
                }

                var selectCommand = string.Format("SELECT * FROM [MobileManage].[dbo].[缴费信息] where 网点用户Id='{0}' and 缴费客户号码='{1}' and 缴费金额={2}", userId, phoneNo, money);//组合选择语句
                using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
                {
                    try
                    {
                        con.Open();

                        using (var cmd = new SqlCommand())
                        {
                            cmd.CommandText = selectCommand;
                            cmd.CommandType = CommandType.Text;
                            cmd.Connection = con;
                            using (SqlDataReader sdr = cmd.ExecuteReader())
                            {

                                if (sdr.HasRows)
                                {
                                    while (sdr.Read())
                                    {
                                        var paymentItem = new PaymentItem()
                                        {
                                            customerName = sdr["缴费客户名称"].ToString(),
                                            customerBeforeMoney = Convert.ToDouble(sdr["缴费前余额"]),
                                            customerAfterMoney = Convert.ToDouble(sdr["缴费后余额"]),
                                            telNo = sdr["缴费客户号码"].ToString(),
                                            chargeMoney = Convert.ToDouble(sdr["缴费金额"]),
                                            chargeTime = Convert.ToDateTime(sdr["缴费时间"].ToString()),
                                            NoLocation = sdr["号码归属"].ToString(),
                                            state = sdr["缴费状态"].ToString(),
                                            brand = sdr["品牌"].ToString(),
                                            SP = sdr["运营商"].ToString(),
                                        };
                                        result.successCount++;
                                        result.listSucc.Add(paymentItem);
                                    }
                                   
                                    cmd.Dispose();
                                    sdr.Close();
                                }
                            }
                        }
                    }
                    catch (Exception ex)
                    {
                        throw new Exception(ex.Message);
                    }
                    finally
                    {
                        con.Close();
                    }
                }
            }

            return result;
        }
        */
        public PaymentItem GetPaymentRecord(string id, string userName, string passwd, string clientType)
        {
            //构造数据
            PaymentItem item = new PaymentItem();

            if (string.IsNullOrEmpty(id) ||
                    string.IsNullOrEmpty(userName) ||
                        string.IsNullOrEmpty(passwd))
            {
                item.telNo = "不合法的参数";
                return item;
            }

            string userId = UserValidator.ValidateLogging(userName, passwd, clientType);
            if (string.IsNullOrEmpty(userId))
            {
                item.telNo = "用户名或密码错误";
                return item;
            }

            //验证权限
            if (!AuthorizationHelper.validate(userId).Contains("批量缴费"))
            {
                item.telNo = "您的账号没有缴费的权限";
                return item;
            }

            string phoneNo = "";
            double money = 0;
            //号码合法性验证
            if (id.Length != 36)
            {
                item.telNo = "id长度有误";
                return item;
            }

            var selectCommand = string.Format("SELECT * FROM [MobileManage].[dbo].[缴费信息] where Id='{0}'", id);//组合选择语句
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = selectCommand;
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;
                        using (SqlDataReader sdr = cmd.ExecuteReader())
                        {

                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {
                                    item.customerName = sdr["缴费客户名称"].ToString();
                                    item.customerBeforeMoney = Convert.ToDouble(sdr["缴费前余额"]);
                                    item.customerAfterMoney = Convert.ToDouble(sdr["缴费后余额"]);
                                    item.telNo = sdr["缴费客户号码"].ToString();
                                    item.chargeMoney = Convert.ToDouble(sdr["缴费金额"]);
                                    item.chargeTime = Convert.ToDateTime(sdr["缴费时间"].ToString());
                                    item.NoLocation = sdr["号码归属"].ToString();
                                    item.state = sdr["缴费状态"].ToString();
                                    item.brand = sdr["品牌"].ToString();
                                    item.SP = sdr["运营商"].ToString();
                                    return item;
                                }

                                cmd.Dispose();
                                sdr.Close();
                            }
                        }
                    }
                }
                catch (Exception ex)
                {
                    throw new Exception(ex.Message);
                }
                finally
                {
                    con.Close();
                }
            }

            return item;
        }

        [WebMethod]
        public double GetAccountChinaMobile(string userName, string passwd)
        {
            return GetAccount(userName, passwd, "移动客户端");
        }

        [WebMethod]
        public double GetAccountChinaUnicom(string userName, string passwd)
        {
            return GetAccount(userName, passwd, "联通电信客户端");
        }

        public double GetAccount(string userName, string passwd, string clientType)
        {
            string userId = UserValidator.ValidateLogging(userName, passwd, clientType);
            if (string.IsNullOrEmpty(userId))
            {
                return -1;
            }

            //验证权限
            if (!AuthorizationHelper.validate(userId).Contains("查询余额"))
            {
                return -2;
            }

            double money = 0;

            var selectCommand = string.Format("SELECT [账户余额] FROM [MobileManage].[dbo].[网点用户] where Id='{0}'", userId);//组合选择语句
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = selectCommand;
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;
                        using (SqlDataReader sdr = cmd.ExecuteReader())
                        {

                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {
                                    money = Convert.ToDouble(sdr["账户余额"]);
                                }

                                cmd.Dispose();
                                sdr.Close();
                            }
                        }
                    }
                }
                catch (Exception ex)
                {
                    throw new Exception(ex.Message);
                }
                finally
                {
                    con.Close();
                }
            }

            return money;
        }


        [WebMethod]
        public AccountInfo StatisticChinaMobile(string userName, string passwd, string type, int offset)
        {
            return Statistic(userName, passwd, type, offset, "移动客户端");
        }

        [WebMethod]
        public AccountInfo StatisticChinaUnicom(string userName, string passwd, string type, int offset)
        {
            return Statistic(userName, passwd, type, offset, "联通电信客户端");
        }

        public AccountInfo Statistic(string userName, string passwd, string type, int offset, string clientType)
        {
            AccountInfo info = new AccountInfo();
            info.type = type;
            info.sum = 0;
            info.count = 0;
            info.state = 0;

            string userId = UserValidator.ValidateLogging(userName, passwd, clientType);
            if (string.IsNullOrEmpty(userId))
            {
                info.state = -1;
                return info;
            }

            //验证权限
            if (!AuthorizationHelper.validate(userId).Contains("账务统计"))
            {
                info.state = -2;
                return info;
            }

            if (offset < 0) 
            {
                info.state = -3;
                return info;
            }
            offset = 0 - offset;

            string sql = "";

            switch (type)
            {
                case "手机缴费":
                    sql = string.Format("select COUNT([缴费金额]) as 总笔数, SUM([缴费金额]) as 总金额 from [MobileManage].[dbo].[缴费汇总信息] where [网点用户Id]='{0}' and [缴费状态]='缴费成功' and [缴费时间]>=DATEADD(d,{1},convert(varchar(10),getdate(),120))", userId, offset);//组合选择语句
                    break;
                case "小卡扣款":
                    sql = string.Format("  select COUNT([扣款金额]) as 总笔数, SUM([扣款金额]) as 总金额 from [MobileManage].[dbo].[小卡扣款汇总信息] where [网点用户Id]='{0}' and [状态]='成功' and [申请时间]>=DATEADD(d,{1},convert(varchar(10),getdate(),120))", userId, offset);
                    break;
                case "用户充值":
                    sql = string.Format(" select COUNT([充值金额]) as 总笔数, SUM([充值金额]) as 总金额 from [MobileManage].[dbo].[用户充值] where [网点用户Id]='{0}' and [状态]='充值成功' and [充值时间]>=DATEADD(d,{1},convert(varchar(10),getdate(),120))", userId, offset);
                    break;
                default:
                    info.state = -4;
                    return info;
            }

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = sql;
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;
                        using (SqlDataReader sdr = cmd.ExecuteReader())
                        {

                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {
                                    if (string.IsNullOrEmpty(sdr["总金额"].ToString()))
                                    {
                                        info.sum = 0;
                                    }
                                    else
                                    {
                                        info.sum = Convert.ToDouble(sdr["总金额"]);
                                    }

                                    info.count = Convert.ToInt16(sdr["总笔数"]);

                                    return info;
                                }

                                cmd.Dispose();
                                sdr.Close();
                            }
                        }
                    }
                }
                catch (Exception ex)
                {
                    throw new Exception(ex.Message);
                }
                finally
                {
                    con.Close();
                }
            }

            return info;

        }
    }
}
