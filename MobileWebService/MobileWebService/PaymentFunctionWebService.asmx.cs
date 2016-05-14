using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services;
using MobileWebService.Entity;
using System.Data.SqlClient;
using System.Data;
using MobileWebService.Validater;

namespace MobileWebService
{
    /// <summary>
    /// PaymentFunctionWebService 的摘要说明
    /// </summary>
    [WebService(Namespace = "http://tempuri.org/")]
    [WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
    [System.ComponentModel.ToolboxItem(false)]
    // 若要允许使用 ASP.NET AJAX 从脚本中调用此 Web 服务，请取消对下行的注释。
    // [System.Web.Script.Services.ScriptService]
    public class PaymentFunctionWebService : System.Web.Services.WebService
    {
        #region 客户端专用

        //收到号码前7位，返回归属地字符串。查询失败返回空
        [WebMethod]
        public string GetLocation(string phoneNo, string clientType, string sessionId)
        {
            if (SessionValidater.ValidateSessionIdWithTime(sessionId) == 0)
            {
                //不合法的请求调用
                return null;
            }
            else if (SessionValidater.ValidateSessionIdWithTime(sessionId) == -1)
            {
                //不合法的请求调用
                return null;
            }

            //解密数据
            phoneNo = NetSecurity.decrypt(phoneNo);
            clientType = NetSecurity.decrypt(clientType);

            if (phoneNo.Length > 7)
            {
                phoneNo = phoneNo.Substring(0, 7);
            }
            string location = "";
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    //手机类型判断
                    using (var cmd0 = new SqlCommand())
                    {
                        string NoFront = phoneNo.Substring(0, 3);
                        string NoFrontValidate = "";
                        /*判断缴费号码的合法性*/
                        if (clientType == "移动客户端")
                        {
                            cmd0.CommandText = "select Name from [MobileManage].[dbo].[URP_DIC_Content] Where [Category] = '移动'";
                        }
                        else if (clientType == "联通电信客户端")
                        {
                            cmd0.CommandText = "select Name from [MobileManage].[dbo].[URP_DIC_Content] Where [Category] = '联通' or [Category] = '电信'";
                        }
                        else
                        {
                            return "未知";
                        }
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
                                if (phoneNo.Substring(0, 1) == "0" && clientType == "联通电信客户端")
                                {
                                    // do nothing
                                }
                                else
                                {
                                    if (!NoFrontValidate.Contains(NoFront))
                                    {
                                        return "未知";
                                    }
                                }
                                sdr.Close();
                            }
                        }
                    }

                    //如果是座机
                    if (phoneNo.Substring(0, 1) == "0")
                    {
                        phoneNo = phoneNo.Substring(0, 4);

                        using (var cmd = new SqlCommand())
                        {
                            cmd.CommandText = "select *  from 号码归属 Where [区号] = '" + phoneNo + "'";
                            cmd.CommandType = CommandType.Text;
                            cmd.Connection = con;
                            using (SqlDataReader sdr = cmd.ExecuteReader())// cmd2.ExecuteNonQuery();
                            {

                                if (sdr.HasRows)
                                {
                                    while (sdr.Read())
                                    {

                                        location = sdr["省份"].ToString() + sdr["城市"].ToString();
                                    }

                                    cmd.Dispose();
                                    sdr.Close();
                                }
                            }
                        }
                    }
                    else
                    {
                        using (var cmd = new SqlCommand())
                        {
                            cmd.CommandText = "select *  from 号码归属 Where [号段] = '" + phoneNo + "'";
                            cmd.CommandType = CommandType.Text;
                            cmd.Connection = con;
                            using (SqlDataReader sdr = cmd.ExecuteReader())// cmd2.ExecuteNonQuery();
                            {

                                if (sdr.HasRows)
                                {
                                    while (sdr.Read())
                                    {

                                        location = sdr["省份"].ToString() + sdr["城市"].ToString();
                                    }

                                    cmd.Dispose();
                                    sdr.Close();
                                }
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
            return location;
        }

        //收到缴费信息，返回缴费是否成功的xml
        [WebMethod]
        public string PayMoney(string phoneNo, string money, string userId, string userName, string sessionId, string SP)
        {
  
            if (SessionValidater.ValidateSessionIdWithTime(sessionId, userId) == 0)
            {
                //不合法的请求调用
                return null;
            }
            else if (SessionValidater.ValidateSessionIdWithTime(sessionId, userId) == -1)
            {
                return "会话超时，请重新登录！";
            }

            //解密
            phoneNo = NetSecurity.decrypt(phoneNo);
            money = NetSecurity.decrypt(money);
            userId = NetSecurity.decrypt(userId);
            userName = NetSecurity.decrypt(userName); 
            SP = NetSecurity.decrypt(SP);

            //验证权限
            if (!AuthorizationHelper.validate(userId).Contains("手机缴费"))
            {
                return null;
            }


            //初始化局部变量
            int payMoney = Convert.ToInt16(money);
            string location = "";   //号码归属地,http查询得到，部分数据库提取
            string area = "";       //地区，数据库提取
            int limitTimeSpane = 0; //重交限制时间
            double currentMoney = 0;//当前账户余额
            string userLevel = "";  //用户级别
            double returnPoint = -1; //返款比例
            string noType = "";     //号码的运营商
            System.TimeSpan timeSpan = new TimeSpan();

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    //座机缴费判断
                    if (phoneNo.Substring(0, 1) == "0")
                    {

                        //座机缴费合法性验证
                        if (SP != "联通电信") 
                        {
                            return "只有联通电信客户端可以为座机缴费！";
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
                            else
                            {
                                return "您当前的客户端类型有误";
                            }
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
                                        return "失败！缴费的号码不是" + SP + "号码";
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

                    if (noType == "") return "号码分类未设置完整！请联系管理员";

                    //判断该类号码能不能缴费
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
                                        return "数据接口故障，暂时不能为该号码缴费\n请联系管理员或稍后再试...";
                                    }
                                }
                                sdr.Close();
                            }
                        }
                    }

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
                                    if (currentMoney < payMoney)
                                    {
                                        return "您当前的余额为：" + currentMoney + "，不足以缴费" + payMoney + "元";
                                    }
                                    userLevel = sdr["用户级别"].ToString();
                                }
                                sdr.Close();
                            }
                        }
                    }

                    using (var cmd1 = new SqlCommand())
                    {
                        /*判断是否存在多少分钟内重交*/
                        cmd1.CommandText = "select Code from [MobileManage].[dbo].[URP_DIC_Content] Where [Category] = '客户端限制' and [Name]='重缴时间'";
                        cmd1.CommandType = CommandType.Text;
                        cmd1.Connection = con;
                        using (SqlDataReader sdr = cmd1.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {
                                    limitTimeSpane = Convert.ToInt16(sdr["Code"].ToString());
                                }
                                sdr.Close();
                            }
                        }
                    }

                    using (var cmd2 = new SqlCommand())
                    {
                        cmd2.CommandText = "select 缴费时间  from 缴费 Where [缴费客户号码] = '" + phoneNo + "' and [缴费金额]=" + payMoney + " order by 缴费时间 desc";
                        cmd2.CommandType = CommandType.Text;
                        cmd2.Connection = con;
                        using (SqlDataReader sdr = cmd2.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                if (sdr.Read())
                                {

                                    DateTime lastPayTime = Convert.ToDateTime(sdr["缴费时间"].ToString());
                                    timeSpan = DateTime.Now - lastPayTime;
                                    if (timeSpan.TotalSeconds < limitTimeSpane)
                                    {
                                        int limitMinutes = limitTimeSpane / 60;
                                        return "同一账号" + limitMinutes + "分钟内不能重复缴费";
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

                    if (returnPoint == -1) return "返款比例未设置完整！请联系管理员";


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

                        cmd4.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd4.ExecuteNonQuery();
                        var res = cmd4.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("1"))
                        {
                            return "成功为" + phoneNo + "缴费" + payMoney + "元";
                        }
                        else
                        {
                            return "为" + phoneNo + "缴费失败"; ;
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

        //收到缴费信息，返回缴费是否成功的xml
        [WebMethod]
        public PayWithListResult PayMoneyWithList(string data, string userId, string userName, string sessionId, string SP)
        {
            if (SessionValidater.ValidateSessionIdWithTime(sessionId, userId) == 0)
            {
                //不合法的请求调用
                return null;
            }
            else if (SessionValidater.ValidateSessionIdWithTime(sessionId, userId) == -1)
            {
                return null;
            }

            //解密
            data = NetSecurity.decrypt(data);
            userId = NetSecurity.decrypt(userId);
            SP = NetSecurity.decrypt(SP);

            //验证权限
            if (!AuthorizationHelper.validate(userId).Contains("批量缴费"))
            {
                return null;
            }
            
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return null;
            }
               
            //构造数据
            List<PayWithListItem> list = new List<PayWithListItem>();

            string[] tmp = data.Split('|');
            foreach (string str in tmp)
            {
                if (string.IsNullOrEmpty(str)) continue;
                string[] d = str.Split(',');
                PayWithListItem item = new PayWithListItem();
                if (d.Length != 2) continue;
                item.phoneNo = d[0];
                item.money = Convert.ToDouble(d[1]);
                list.Add(item);
            }
            var payWithListResult = new PayWithListResult();
            //初始化返回结果
            payWithListResult.count = list.Count;
            payWithListResult.failedCount = 0;
            payWithListResult.successCount = 0;
            payWithListResult.totalMoney = 0;
            payWithListResult.list = new List<PayWithListItem>();

            string userLevel = "";  //用户级别
            double currentMoney = 0;//当前账户余额
            double totalMoney = 0;
            //计算缴费总金额
            foreach (PayWithListItem payWithListItem in list)
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
                        cmd.CommandText = "select 账户余额,用户级别,登陆名  from 网点用户 Where [Id] = '" + userId + "'";
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
                                        payWithListResult.result = "错误!您当前的余额为：" + currentMoney + "，不足以支付总和的" + totalMoney + "元";
                                        payWithListResult.count = list.Count;
                                        payWithListResult.successCount = 0;
                                        payWithListResult.failedCount = list.Count;
                                        return payWithListResult;
                                    }
                                    userLevel = sdr["用户级别"].ToString();
                                    userName = sdr["登陆名"].ToString();
                                }
                                sdr.Close();
                            }
                        }
                    }

                    //循环处理每一条缴费记录
                    foreach (PayWithListItem payWithListItem in list)
                    {
                        string phoneNo = "";
                        double money = 0;
                        //号码合法性验证
                        if (payWithListItem.phoneNo.Substring(0, 4) == "0871" && payWithListItem.phoneNo.Length != 12)
                        {
                            payWithListResult.failedCount++;
                            payWithListResult.list.Add(payWithListItem);
                            continue;
                        }
                        else if (payWithListItem.phoneNo.Substring(0, 4) != "0871" && payWithListItem.phoneNo.Length != 11)
                        {
                            payWithListResult.failedCount++;
                            payWithListResult.list.Add(payWithListItem);
                            continue;
                        }
                        else
                        {
                            phoneNo = payWithListItem.phoneNo;
                        }
                        //钱合法性验证
                        if (payWithListItem.money <= 0)
                        {
                            payWithListResult.failedCount++;
                            payWithListResult.list.Add(payWithListItem);
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
                                payWithListResult.failedCount++;
                                payWithListResult.list.Add(payWithListItem);
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
                                            payWithListResult.failedCount++;
                                            payWithListResult.list.Add(payWithListItem);
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
                            payWithListResult.failedCount++;
                            payWithListResult.list.Add(payWithListItem);
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
                                            payWithListResult.failedCount++;
                                            payWithListResult.list.Add(payWithListItem);
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
                                            payWithListResult.failedCount++;
                                            payWithListResult.list.Add(payWithListItem);
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
                            payWithListResult.failedCount++;
                            payWithListResult.list.Add(payWithListItem);
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

                            cmd4.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                            cmd4.ExecuteNonQuery();
                            var res = cmd4.Parameters["@RETURN_VALUE"].Value.ToString();

                            if (res.Equals("1"))
                            {
                                payWithListResult.successCount++;
                                payWithListResult.totalMoney += money;
                                continue;
                            }
                            else
                            {
                                payWithListResult.failedCount++;
                                payWithListResult.list.Add(payWithListItem);
                                continue;
                            }
                        }
                    }
                    string result = "批量缴费成功！\n共计" + payWithListResult.count.ToString() + "条记录\n"
                                + "成功缴费:" + payWithListResult.successCount.ToString() + "条\n"
                                + "失败:" + payWithListResult.failedCount.ToString() + "条\n"
                                + "缴费总金额:" + payWithListResult.totalMoney.ToString() + "元";
                    payWithListResult.result = result;
                    return payWithListResult;
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

        //请求返销或撤销的方法，type="申请返销" or "申请撤销"
        [WebMethod]
        public string RequstRollback(string paymentId, string userId, string type, string sessionId)
        {
            if (SessionValidater.ValidateSessionIdWithTime(sessionId, userId) == 0)
            {
                //不合法的请求调用
                return null;
            }
            else if (SessionValidater.ValidateSessionIdWithTime(sessionId, userId) == -1)
            {
                return "会话超时，请重新登录！";
            }

            //解密
            paymentId = NetSecurity.decrypt(paymentId);
            userId = NetSecurity.decrypt(userId);
            type = NetSecurity.decrypt(type);

            //验证权限
            if (!AuthorizationHelper.validate(userId).Contains("缴费日报"))
            {
                return null;
            }

            //参数有效性验证
            if (string.IsNullOrEmpty(paymentId))
                return "paymentId不能为空";
            if (string.IsNullOrEmpty(paymentId))
                return "userId不能为空";
            if (string.IsNullOrEmpty(type))
            {
                return "type不能为空";
            }
            else
            {
                if (type != "申请返销" && type != "申请撤销")
                    return "type不是有效的类型";
            }

            Guid payment_id = new Guid(paymentId);
            Guid user_id = new Guid(userId);

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        if (type == "申请返销")
                        {
                            cmd.CommandText = "Function_网点用户_申请返销";
                        }
                        else if (type == "申请撤销")
                        {
                            cmd.CommandText = "Function_网点用户_申请撤销";
                        }
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;
                        var sp1 = new SqlParameter("@payment_id", SqlDbType.UniqueIdentifier);
                        sp1.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp1);
                        sp1.Value = payment_id;

                        var sp2 = new SqlParameter("@worker_id", SqlDbType.UniqueIdentifier);
                        sp2.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp2);
                        sp2.Value = user_id;

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("1"))
                        {
                            cmd.Dispose();
                            return type + "成功";
                        }
                        else
                        {
                            cmd.Dispose();
                            return type + "失败";
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

        //宽带缴费
        [WebMethod]
        public string PayInternet(string internetType, string internetAccount, string money, string content, string userId,  string userName, string sessionId, string clientType)
        {
            if (SessionValidater.ValidateSessionIdWithTime(sessionId, userId) == 0)
            {
                //不合法的请求调用
                return null;
            }
            else if (SessionValidater.ValidateSessionIdWithTime(sessionId, userId) == -1)
            {
                return "会话超时，请重新登录！";
            }

            //解密
            internetType = NetSecurity.decrypt(internetType);
            internetAccount = NetSecurity.decrypt(internetAccount);
            money = NetSecurity.decrypt(money);
            content = NetSecurity.decrypt(content);
            userId = NetSecurity.decrypt(userId);
            userName = NetSecurity.decrypt(userName);
            clientType = NetSecurity.decrypt(clientType);

            //验证权限
            if (!AuthorizationHelper.validate(userId).Contains("宽带公话"))
            {
                return null;
            }

            double currentMoney = 0;
            string userLevel = "";
            string area = "";
            string location = "";
            int limitTimeSpane = 0;
            double returnPoint = -1;
            System.TimeSpan timeSpan = new TimeSpan();

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

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
                                    if (currentMoney < Convert.ToDouble(money))
                                    {
                                        return "您当前的余额为：" + currentMoney + "，不足以缴费" + money + "元";
                                    }
                                    userLevel = sdr["用户级别"].ToString();
                                }
                                sdr.Close();
                            }
                        }
                    }

                    using (var cmd1 = new SqlCommand())
                    {
                        /*判断是否存在多少分钟内重交*/
                        cmd1.CommandText = "select Code from [MobileManage].[dbo].[URP_DIC_Content] Where [Category] = '客户端限制' and [Name]='重缴时间'";
                        cmd1.CommandType = CommandType.Text;
                        cmd1.Connection = con;
                        using (SqlDataReader sdr = cmd1.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {
                                    limitTimeSpane = Convert.ToInt16(sdr["Code"].ToString());
                                }
                                sdr.Close();
                            }
                        }
                    }

                    using (var cmd2 = new SqlCommand())
                    {
                        cmd2.CommandText = "select 提交日期 from 宽带缴费 Where [宽带类型]='" + internetType + "' and [宽带账号] = '" + internetAccount + "' and [缴费金额]=" + money + " order by 提交日期 desc";
                        cmd2.CommandType = CommandType.Text;
                        cmd2.Connection = con;
                        using (SqlDataReader sdr = cmd2.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                if (sdr.Read())
                                {

                                    DateTime lastPayTime = Convert.ToDateTime(sdr["提交日期"].ToString());
                                    timeSpan = DateTime.Now - lastPayTime;
                                    if (timeSpan.TotalSeconds < limitTimeSpane)
                                    {
                                        int limitMinutes = limitTimeSpane / 60;
                                        return "同一账号" + limitMinutes + "分钟内不能重复缴费";
                                    }
                                }
                                sdr.Close();
                            }
                        }
                    }

                    //提取地区
                    if (internetAccount.Substring(0, 1) == "0" && internetAccount.Length > 4)
                    {
                        //号码归属地查询
                        using (var cmd31 = new SqlCommand())
                        {
                            /*取相关参数进行缴费*/
                            string tel4 = internetAccount.Substring(0, 4);
                            cmd31.CommandText = "select *  from 区号 Where [区号] = '" + tel4 + "'";
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
                    }

                    if (string.IsNullOrEmpty(area)) 
                    {
                        return "不合法的账号！充值失败\n请检查您输入的账号是否以区号开头";
                    }

                    //提取返款比例
                    using (var cmd5 = new SqlCommand())
                    {
                        cmd5.CommandText = "select [返款比例]  from [dbo].[返款比例明细] Where [返款类型]='宽带返款' and [返款项目]='" + internetType + "' and [地区]='" + area + "' and [用户级别] = '" + userLevel + "'";
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

                    if (returnPoint == -1) return "宽带充值返款比例未设置完整！请联系管理员";

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_网点用户_宽带充值";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;
                        cmd.Parameters.Clear();


                        var sp0 = new SqlParameter("@网点用户Id", SqlDbType.UniqueIdentifier);
                        sp0.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp0);
                        sp0.Value = string.IsNullOrEmpty(userId) ? (object)DBNull.Value : new Guid(userId);

                        var _sp1 = new SqlParameter("@网点用户登录名", SqlDbType.NVarChar, 50);
                        _sp1.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(_sp1);
                        _sp1.Value = userName;

                        var sp1 = new SqlParameter("@宽带类型", SqlDbType.NVarChar, 50);
                        sp1.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp1);
                        sp1.Value = internetType;

                        var sp4 = new SqlParameter("@宽带账号", SqlDbType.NVarChar, 50);
                        sp4.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp4);
                        sp4.Value = internetAccount;

                        var sp5 = new SqlParameter("@缴费金额", SqlDbType.Money);
                        sp5.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp5);
                        sp5.Value = Convert.ToDouble(money);

                        var sp6 = new SqlParameter("@备注", SqlDbType.NVarChar, 100);
                        sp6.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp6);
                        sp6.Value = content;

                        var sp7 = new SqlParameter("@客户端类型", SqlDbType.NVarChar, 50);
                        sp7.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp7);
                        sp7.Value = clientType;

                        var sp8 = new SqlParameter("@返款金额", SqlDbType.Money);
                        sp8.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp8);
                        sp8.Value = Convert.ToDouble(money) * returnPoint;

                        var sp9 = new SqlParameter("@地区", SqlDbType.NVarChar, 50);
                        sp9.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp9);
                        sp9.Value = area;

                        var sp10 = new SqlParameter("@号码归属", SqlDbType.NVarChar, 50);
                        sp10.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp10);
                        sp10.Value = area;

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("1"))
                        {
                            cmd.Dispose();
                            return "成功为" + internetType + "账号: " + internetAccount + " 缴费" + money.ToString() + "元";
                        }
                        else
                        {
                            cmd.Dispose();
                            return "宽带充值失败";
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

        //收到缴费信息，返回缴费是否成功的xml
        [WebMethod]
        public PayWithListResult PayInternetWithList(string data, string userId, string userName, string sessionId)
        {
 
            if (SessionValidater.ValidateSessionIdWithTime(sessionId, userId) == 0)
            {
                //不合法的请求调用
                return null;
            }
            else if (SessionValidater.ValidateSessionIdWithTime(sessionId, userId) == -1)
            {
                return null;
            }

            //解密
            data = NetSecurity.decrypt(data);
            userId = NetSecurity.decrypt(userId);

            //验证权限
            if (!AuthorizationHelper.validate(userId).Contains("宽带批量缴费"))
            {
                return null;
            }

            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return null;
            }

            //构造数据
            List<PayWithListItem> list = new List<PayWithListItem>();

            string[] tmp = data.Split('|');
            foreach (string str in tmp)
            {
                if (string.IsNullOrEmpty(str)) continue;
                string[] d = str.Split(',');
                PayWithListItem item = new PayWithListItem();
                if (d.Length != 3) continue;
                if (string.IsNullOrEmpty(d[0])) continue;
                item.phoneNo = d[0];
                if (string.IsNullOrEmpty(d[1])) continue;
                item.money = Convert.ToDouble(d[1]);
                if (string.IsNullOrEmpty(d[2])) continue;
                item.type = d[2];
                list.Add(item);
            }
            var payWithListResult = new PayWithListResult();
            //初始化返回结果
            payWithListResult.count = list.Count;
            payWithListResult.failedCount = 0;
            payWithListResult.successCount = 0;
            payWithListResult.totalMoney = 0;
            payWithListResult.list = new List<PayWithListItem>();

            string userLevel = "";  //用户级别
            double currentMoney = 0;//当前账户余额
            double totalMoney = 0;
            //计算缴费总金额
            foreach (PayWithListItem payWithListItem in list)
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
                        cmd.CommandText = "select 账户余额,用户级别,登陆名  from 网点用户 Where [Id] = '" + userId + "'";
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
                                        payWithListResult.result = "错误!您当前的余额为：" + currentMoney + "，不足以支付总和的" + totalMoney + "元";
                                        payWithListResult.count = list.Count;
                                        payWithListResult.successCount = 0;
                                        payWithListResult.failedCount = list.Count;
                                        return payWithListResult;
                                    }
                                    userLevel = sdr["用户级别"].ToString();
                                    userName = sdr["登陆名"].ToString();
                                }
                                sdr.Close();
                            }
                        }
                    }

                    //循环处理每一条缴费记录
                    foreach (PayWithListItem payWithListItem in list)
                    {
                        string internetAccount = "";
                        string internetType = "";
                        double money = 0;
                        //号码合法性验证
                        if (payWithListItem.phoneNo.Substring(0, 1) == "0" && payWithListItem.phoneNo.Length > 4)
                        {
                            internetAccount = payWithListItem.phoneNo;
                            internetType = payWithListItem.type;
                        }
                        else
                        {
                            payWithListResult.failedCount++;
                            payWithListResult.list.Add(payWithListItem);
                            continue;
                        }

                        //钱合法性验证
                        if (payWithListItem.money <= 0)
                        {
                            payWithListResult.failedCount++;
                            payWithListResult.list.Add(payWithListItem);
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

                            //号码归属地查询
                        using (var cmd31 = new SqlCommand())
                        {
                            /*取相关参数进行缴费*/
                            string tel4 = internetAccount.Substring(0, 4);
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

                        //一些不合法的状态，需要补充数据库的值
                        if (string.IsNullOrEmpty(noType) || string.IsNullOrEmpty(area) || string.IsNullOrEmpty(userLevel))
                        {
                            payWithListResult.failedCount++;
                            payWithListResult.list.Add(payWithListItem);
                            continue;
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
                                            payWithListResult.failedCount++;
                                            payWithListResult.list.Add(payWithListItem);
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
                            payWithListResult.failedCount++;
                            payWithListResult.list.Add(payWithListItem);
                            continue;
                        }

                        //缴费，附带扣款，但是返款未计算
                        using (var cmd4 = new SqlCommand())
                        {
                            cmd4.CommandText = "Function_网点用户_宽带充值";
                            cmd4.CommandType = CommandType.StoredProcedure;
                            cmd4.Connection = con;
                            cmd4.Parameters.Clear();


                            var sp0 = new SqlParameter("@网点用户Id", SqlDbType.UniqueIdentifier);
                            sp0.Direction = ParameterDirection.Input;
                            cmd4.Parameters.Add(sp0);
                            sp0.Value = string.IsNullOrEmpty(userId) ? (object)DBNull.Value : new Guid(userId);

                            var _sp1 = new SqlParameter("@网点用户登录名", SqlDbType.NVarChar, 50);
                            _sp1.Direction = ParameterDirection.Input;
                            cmd4.Parameters.Add(_sp1);
                            _sp1.Value = userName;

                            var sp1 = new SqlParameter("@宽带类型", SqlDbType.NVarChar, 50);
                            sp1.Direction = ParameterDirection.Input;
                            cmd4.Parameters.Add(sp1);
                            sp1.Value = internetType;

                            var sp4 = new SqlParameter("@宽带账号", SqlDbType.NVarChar, 50);
                            sp4.Direction = ParameterDirection.Input;
                            cmd4.Parameters.Add(sp4);
                            sp4.Value = internetAccount;

                            var sp5 = new SqlParameter("@缴费金额", SqlDbType.Money);
                            sp5.Direction = ParameterDirection.Input;
                            cmd4.Parameters.Add(sp5);
                            sp5.Value = Convert.ToDouble(money);

                            var sp6 = new SqlParameter("@备注", SqlDbType.NVarChar, 100);
                            sp6.Direction = ParameterDirection.Input;
                            cmd4.Parameters.Add(sp6);
                            sp6.Value = "";

                            var sp7 = new SqlParameter("@客户端类型", SqlDbType.NVarChar, 50);
                            sp7.Direction = ParameterDirection.Input;
                            cmd4.Parameters.Add(sp7);
                            sp7.Value = "联通电信客户端";

                            var sp8 = new SqlParameter("@返款金额", SqlDbType.Money);
                            sp8.Direction = ParameterDirection.Input;
                            cmd4.Parameters.Add(sp8);
                            sp8.Value = Convert.ToDouble(money) * returnPoint;

                            var sp9 = new SqlParameter("@地区", SqlDbType.NVarChar, 50);
                            sp9.Direction = ParameterDirection.Input;
                            cmd4.Parameters.Add(sp9);
                            sp9.Value = area;

                            var sp10 = new SqlParameter("@号码归属", SqlDbType.NVarChar, 50);
                            sp10.Direction = ParameterDirection.Input;
                            cmd4.Parameters.Add(sp10);
                            sp10.Value = area;

                            cmd4.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                            cmd4.ExecuteNonQuery();
                            var res = cmd4.Parameters["@RETURN_VALUE"].Value.ToString();

                            if (res.Equals("1"))
                            {
                                payWithListResult.successCount++;
                                payWithListResult.totalMoney += money;
                                continue;
                            }
                            else
                            {
                                payWithListResult.failedCount++;
                                payWithListResult.list.Add(payWithListItem);
                                continue;
                            }
                        }
                    }
                    string result = "批量缴费成功！\n共计" + payWithListResult.count.ToString() + "条记录\n"
                                + "成功缴费:" + payWithListResult.successCount.ToString() + "条\n"
                                + "失败:" + payWithListResult.failedCount.ToString() + "条\n"
                                + "缴费总金额:" + payWithListResult.totalMoney.ToString() + "元";
                    payWithListResult.result = result;
                    return payWithListResult;
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

        //宽带或公话返销
        [WebMethod]
        public string RequstInternetRollback(string paymentId, string userId, string type, string sessionId)
        {
            
            if (SessionValidater.ValidateSessionIdWithTime(sessionId, userId) == 0)
            {
                //不合法的请求调用
                return null;
            }
            else if (SessionValidater.ValidateSessionIdWithTime(sessionId, userId) == -1)
            {
                return "会话超时，请重新登录！";
            }

            //解密
            paymentId = NetSecurity.decrypt(paymentId);
            userId = NetSecurity.decrypt(userId);
            type = NetSecurity.decrypt(type);
            
            //验证权限
            if (!AuthorizationHelper.validate(userId).Contains("宽带公话"))
            {
                return null;
            }
            
            string exec_str = "";
            //参数有效性验证
            if (string.IsNullOrEmpty(paymentId))
                return "paymentId不能为空";
            if (string.IsNullOrEmpty(paymentId))
                return "userId不能为空";
            if (string.IsNullOrEmpty(type))
            {
                return "type不能为空";
            }
            else
            {
                if (type == "宽带返销")
                {
                    exec_str = "Function_网点用户_宽带返销";
                }
                else
                {
                    return "type不是有效的类型";
                }
            }

            Guid payment_id = new Guid(paymentId);
            Guid user_id = new Guid(userId);

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = exec_str;
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;
                        var sp1 = new SqlParameter("@payment_id", SqlDbType.UniqueIdentifier);
                        sp1.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp1);
                        sp1.Value = payment_id;

                        var sp2 = new SqlParameter("@user_id", SqlDbType.UniqueIdentifier);
                        sp2.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp2);
                        sp2.Value = user_id;

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("1"))
                        {
                            cmd.Dispose();
                            return type + "成功";
                        }
                        else
                        {
                            cmd.Dispose();
                            return type + "失败";
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

        //游戏充值
        [WebMethod]
        public string PayGame(string gameType, string gameAccount, string money, string content, string userId, string userName, string sessionId, string clientType)
        {
            if (SessionValidater.ValidateSessionIdWithTime(sessionId, userId) == 0)
            {
                //不合法的请求调用
                return null;
            }
            else if (SessionValidater.ValidateSessionIdWithTime(sessionId, userId) == -1)
            {
                return "会话超时，请重新登录！";
            }

            //解密
            gameType = NetSecurity.decrypt(gameType);
            gameAccount = NetSecurity.decrypt(gameAccount);
            money = NetSecurity.decrypt(money);
            content = NetSecurity.decrypt(content);
            userId = NetSecurity.decrypt(userId);
            userName = NetSecurity.decrypt(userName);
            clientType = NetSecurity.decrypt(clientType);

            //验证权限
            if (!AuthorizationHelper.validate(userId).Contains("游戏充值"))
            {
                return null;
            }

            double currentMoney = 0;
            string userLevel = "";
            int limitTimeSpane = 0;
            double returnPoint = -1;
            System.TimeSpan timeSpan = new TimeSpan();
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

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
                                    if (currentMoney < Convert.ToDouble(money))
                                    {
                                        return "您当前的余额为：" + currentMoney + "，不足以缴费" + money + "元";
                                    }
                                    userLevel = sdr["用户级别"].ToString();
                                }
                                sdr.Close();
                            }
                        }
                    }

                    using (var cmd1 = new SqlCommand())
                    {
                        /*判断是否存在多少分钟内重交*/
                        cmd1.CommandText = "select Code from [MobileManage].[dbo].[URP_DIC_Content] Where [Category] = '客户端限制' and [Name]='重缴时间'";
                        cmd1.CommandType = CommandType.Text;
                        cmd1.Connection = con;
                        using (SqlDataReader sdr = cmd1.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {
                                    limitTimeSpane = Convert.ToInt16(sdr["Code"].ToString());
                                }
                                sdr.Close();
                            }
                        }
                    }

                    using (var cmd2 = new SqlCommand())
                    {
                        cmd2.CommandText = "select 提交日期 from 游戏充值 Where [游戏类型名称]='" + gameType + "' and [游戏账号] = '" + gameAccount + "' and [缴费金额]=" + money + " order by 提交日期 desc";
                        cmd2.CommandType = CommandType.Text;
                        cmd2.Connection = con;
                        using (SqlDataReader sdr = cmd2.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                if (sdr.Read())
                                {

                                    DateTime lastPayTime = Convert.ToDateTime(sdr["提交日期"].ToString());
                                    timeSpan = DateTime.Now - lastPayTime;
                                    if (timeSpan.TotalSeconds < limitTimeSpane)
                                    {
                                        int limitMinutes = limitTimeSpane / 60;
                                        return "同一账号" + limitMinutes + "分钟内不能重复缴费";
                                    }
                                }
                                sdr.Close();
                            }
                        }
                    }

                    //提取返款比例
                    using (var cmd5 = new SqlCommand())
                    {
                        cmd5.CommandText = "select [返款比例]  from [dbo].[返款比例明细] Where [返款类型]='游戏返款' and [返款项目]='" + gameType + "' and [用户级别] = '" + userLevel + "'";
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

                    if (returnPoint == -1) return "游戏充值返款比例未设置完整！请联系管理员";

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_网点用户_游戏充值";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;
                        cmd.Parameters.Clear();


                        var sp0 = new SqlParameter("@网点用户Id", SqlDbType.UniqueIdentifier);
                        sp0.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp0);
                        sp0.Value = string.IsNullOrEmpty(userId) ? (object)DBNull.Value : new Guid(userId);

                        var _sp1 = new SqlParameter("@网点用户登录名", SqlDbType.NVarChar, 50);
                        _sp1.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(_sp1);
                        _sp1.Value = userName;

                        var sp1 = new SqlParameter("@游戏类型名称", SqlDbType.NVarChar, 50);
                        sp1.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp1);
                        sp1.Value = gameType;

                        var sp4 = new SqlParameter("@游戏账号", SqlDbType.NVarChar, 50);
                        sp4.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp4);
                        sp4.Value = gameAccount;

                        var sp5 = new SqlParameter("@缴费金额", SqlDbType.Money);
                        sp5.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp5);
                        sp5.Value = Convert.ToDouble(money);

                        var sp6 = new SqlParameter("@备注", SqlDbType.NVarChar, 100);
                        sp6.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp6);
                        sp6.Value = content;

                        var sp7 = new SqlParameter("@客户端类型", SqlDbType.NVarChar, 50);
                        sp7.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp7);
                        sp7.Value = clientType;

                        var sp8 = new SqlParameter("@返款金额", SqlDbType.Money);
                        sp8.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp8);
                        sp8.Value = Convert.ToDouble(money) * returnPoint;

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("1"))
                        {
                            cmd.Dispose();
                            return "成功为" + gameType + "玩家: " + gameAccount + " 缴费" + money.ToString() + "元";
                        }
                        else
                        {
                            cmd.Dispose();
                            return "游戏充值失败";
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

        //公话缴费
        [WebMethod]
        public string PayPublicTel(string telType, string telAccount, string money, string content, string userId, string userName, string sessionId, string clientType)
        {
            
            if (SessionValidater.ValidateSessionIdWithTime(sessionId, userId) == 0)
            {
                //不合法的请求调用
                return null;
            }
            else if (SessionValidater.ValidateSessionIdWithTime(sessionId, userId) == -1)
            {
                return "会话超时，请重新登录！";
            }

            //解密
            telType = NetSecurity.decrypt(telType);
            telAccount = NetSecurity.decrypt(telAccount);
            money = NetSecurity.decrypt(money);
            content = NetSecurity.decrypt(content);
            userId = NetSecurity.decrypt(userId);
            userName = NetSecurity.decrypt(userName);
            clientType = NetSecurity.decrypt(clientType);

            //验证权限
            if (!AuthorizationHelper.validate(userId).Contains("宽带公话"))
            {
                return null;
            }
            
            double currentMoney = 0;
            string userLevel = "";
            string area = "";
            string location = "";
            int limitTimeSpane = 0;
            double returnPoint = -1;
            System.TimeSpan timeSpan = new TimeSpan();

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

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
                                    if (currentMoney < Convert.ToDouble(money))
                                    {
                                        return "您当前的余额为：" + currentMoney + "，不足以缴费" + money + "元";
                                    }
                                    userLevel = sdr["用户级别"].ToString();
                                }
                                sdr.Close();
                            }
                        }
                    }

                    using (var cmd1 = new SqlCommand())
                    {
                        /*判断是否存在多少分钟内重交*/
                        cmd1.CommandText = "select Code from [MobileManage].[dbo].[URP_DIC_Content] Where [Category] = '客户端限制' and [Name]='重缴时间'";
                        cmd1.CommandType = CommandType.Text;
                        cmd1.Connection = con;
                        using (SqlDataReader sdr = cmd1.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {
                                    limitTimeSpane = Convert.ToInt16(sdr["Code"].ToString());
                                }
                                sdr.Close();
                            }
                        }
                    }

                    using (var cmd2 = new SqlCommand())
                    {
                        cmd2.CommandText = "select 提交日期 from 公话缴费 Where [公话类型]='" + telType + "' and [公话号码] = '" + telAccount + "' and [缴费金额]=" + money + " order by 提交日期 desc";
                        cmd2.CommandType = CommandType.Text;
                        cmd2.Connection = con;
                        using (SqlDataReader sdr = cmd2.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                if (sdr.Read())
                                {

                                    DateTime lastPayTime = Convert.ToDateTime(sdr["提交日期"].ToString());
                                    timeSpan = DateTime.Now - lastPayTime;
                                    if (timeSpan.TotalSeconds < limitTimeSpane)
                                    {
                                        int limitMinutes = limitTimeSpane / 60;
                                        return "同一账号" + limitMinutes + "分钟内不能重复缴费";
                                    }
                                }
                                sdr.Close();
                            }
                        }
                    }

                    //提取地区
                    if (telAccount.Substring(0, 1) == "0" && telAccount.Length > 4)
                    {
                        //号码归属地查询
                        using (var cmd31 = new SqlCommand())
                        {
                            /*取相关参数进行缴费*/
                            string tel4 = telAccount.Substring(0, 4);
                            cmd31.CommandText = "select *  from 区号 Where [区号] = '" + tel4 + "'";
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
                    }

                    if (string.IsNullOrEmpty(area))
                    {
                        return "不合法的账号！充值失败\n请检查您输入的号码是否以区号开头";
                    }

                    //提取返款比例
                    using (var cmd5 = new SqlCommand())
                    {
                        cmd5.CommandText = "select [返款比例]  from [dbo].[返款比例明细] Where [返款类型]='公话返款' and [返款项目]='" + telType + "' and [地区]='" + area + "' and [用户级别] = '" + userLevel + "'";
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

                    if (returnPoint == -1) return "公话缴费返款比例未设置完整！请联系管理员";

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_网点用户_公话缴费";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;
                        cmd.Parameters.Clear();


                        var sp0 = new SqlParameter("@网点用户Id", SqlDbType.UniqueIdentifier);
                        sp0.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp0);
                        sp0.Value = string.IsNullOrEmpty(userId) ? (object)DBNull.Value : new Guid(userId);

                        var _sp1 = new SqlParameter("@网点用户登录名", SqlDbType.NVarChar, 50);
                        _sp1.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(_sp1);
                        _sp1.Value = userName;

                        var sp1 = new SqlParameter("@公话类型", SqlDbType.NVarChar, 50);
                        sp1.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp1);
                        sp1.Value = telType;

                        var sp4 = new SqlParameter("@公话号码", SqlDbType.NVarChar, 50);
                        sp4.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp4);
                        sp4.Value = telAccount;

                        var sp5 = new SqlParameter("@缴费金额", SqlDbType.Money);
                        sp5.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp5);
                        sp5.Value = Convert.ToDouble(money);

                        var sp6 = new SqlParameter("@备注", SqlDbType.NVarChar, 100);
                        sp6.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp6);
                        sp6.Value = content;

                        var sp7 = new SqlParameter("@客户端类型", SqlDbType.NVarChar, 50);
                        sp7.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp7);
                        sp7.Value = clientType;

                        var sp8 = new SqlParameter("@返款金额", SqlDbType.Money);
                        sp8.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp8);
                        sp8.Value = Convert.ToDouble(money) * returnPoint;

                        var sp9 = new SqlParameter("@地区", SqlDbType.NVarChar, 50);
                        sp9.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp9);
                        sp9.Value = area;

                        var sp10 = new SqlParameter("@号码归属", SqlDbType.NVarChar, 50);
                        sp10.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp10);
                        sp10.Value = area;

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("1"))
                        {
                            cmd.Dispose();
                            return "成功为" + telType + "号码: " + telAccount + " 缴费" + money.ToString() + "元";
                        }
                        else
                        {
                            cmd.Dispose();
                            return "公话缴费失败";
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

        #endregion

        #region 客户端服务端共用

        //查询缴费记录，int位表示是提前最新几条数据
        [WebMethod]
        public List<PaymentItem> GetPaymentRecord(int top, string condition, string sessionId)
        {
            var list = new List<PaymentItem>();

            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return list;
            }

            //解密数据
            condition = NetSecurity.decrypt(condition);

            string topMessage = "";
            string selectCondition = "";
            if (top != 0) //查询头几条
            {
                topMessage = " TOP " + top;
            }
            else
            {
                topMessage = "";
            }

            if (!string.IsNullOrEmpty(condition))
            {
                selectCondition = "Where " + condition;
            }
            var selectCommand = string.Format("SELECT {0} * FROM [MobileManage].[dbo].[缴费信息] {1}", topMessage, selectCondition);//组合选择语句
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
                                    var paymentItem = new PaymentItem
                                    {
                                        Id = new Guid(sdr["Id"].ToString()),
                                        customerName = sdr["缴费客户名称"].ToString(),
                                        telNo = sdr["缴费客户号码"].ToString(),
                                        clientType = sdr["客户端类型"].ToString(),
                                        chargeMoney = Convert.ToDouble(sdr["缴费金额"]),
                                        chargeTime = Convert.ToDateTime(sdr["缴费时间"].ToString()),
                                        NoLocation = sdr["号码归属"].ToString(),
                                        customerBeforeMoney = Convert.ToDouble(sdr["缴费前余额"]),
                                        customerAfterMoney = Convert.ToDouble(sdr["缴费后余额"]),
                                        moneyBefore = Convert.ToDouble(sdr["处理前金额"]),
                                        moneyAfter = Convert.ToDouble(sdr["处理后金额"]),
                                        state = sdr["缴费状态"].ToString(),
                                        brand = sdr["品牌"].ToString(),
                                        area = sdr["地区"].ToString(),
                                        user_id = sdr["网点用户Id"].ToString(),
                                        user_name = sdr["网点用户登录名"].ToString(),
                                        work_id = sdr["员工Id"].ToString(),
                                        work_name = sdr["员工登录名"].ToString(),
                                        manager_name = sdr["业务负责人"].ToString(),
                                        repay = Convert.ToDouble(sdr["返款金额"]),
                                        SP = sdr["运营商"].ToString(),
                                    };

                                    list.Add(paymentItem);
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

            return list;
        }

        //查询单项缴费记录，condition接where后面的条件
        [WebMethod]
        public PaymentItem GetPaymentItem(string condition, string sessionId)
        {
            var paymentItem = new PaymentItem();
            
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return paymentItem;
            }
            
            //解密数据
            condition = NetSecurity.decrypt(condition);

            string selectCondition = "";
            if (!string.IsNullOrEmpty(condition))
            {
                selectCondition = "Where " + condition;
            }
            var selectCommand = string.Format("SELECT * FROM [MobileManage].[dbo].[缴费汇总信息] {0}", selectCondition);//组合选择语句
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
                        using (SqlDataReader sdr = cmd.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                if (sdr.Read())
                                {
                                    if (!String.IsNullOrEmpty(sdr["Id"].ToString()))
                                        paymentItem.Id = new Guid(sdr["Id"].ToString());
                                    paymentItem.customerName = sdr["缴费客户名称"].ToString();
                                    paymentItem.telNo = sdr["缴费客户号码"].ToString();
                                    paymentItem.chargeMoney = Convert.ToDouble(sdr["缴费金额"]);
                                    if (!String.IsNullOrEmpty(sdr["缴费时间"].ToString()))
                                        paymentItem.chargeTime = Convert.ToDateTime(sdr["缴费时间"].ToString());
                                    paymentItem.NoLocation = sdr["号码归属"].ToString();
                                    paymentItem.customerBeforeMoney = Convert.ToDouble(sdr["缴费前余额"]);
                                    paymentItem.customerAfterMoney =  Convert.ToDouble(sdr["缴费后余额"]);
                                    paymentItem.state = sdr["缴费状态"].ToString();
                                    paymentItem.brand = sdr["品牌"].ToString();
                                    paymentItem.area = sdr["地区"].ToString();
                                    paymentItem.user_id = sdr["网点用户Id"].ToString();
                                    paymentItem.user_name = sdr["网点用户登录名"].ToString();
                                    paymentItem.work_id = sdr["员工Id"].ToString();
                                    paymentItem.work_name = sdr["员工登录名"].ToString();
                                    paymentItem.repay = Convert.ToDouble(sdr["返款金额"]);
                                    paymentItem.SP = sdr["运营商"].ToString();
                                }
                                cmd.Dispose();
                                sdr.Close();
                            }
                        }
                    }
                    return paymentItem;
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
        //根据条件获取符合条件的交易明细记录
        public List<Transaction> GetTransactionByCondition(string condition, string sessionId)
        {
            var list = new List<Transaction>();
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return list;
            }

            //解密数据
            condition = NetSecurity.decrypt(condition);

            string selectCondition = "";


            if (!string.IsNullOrEmpty(condition))
            {
                selectCondition = "Where " + condition;
            }
            var selectCommand = string.Format("SELECT * FROM [MobileManage].[dbo].[交易明细信息] {0}", selectCondition);//组合选择语句
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
                        using (SqlDataReader sdr = cmd.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {
                                    var transaction = new Transaction();
                                    if (!string.IsNullOrEmpty(sdr["Id"].ToString()))
                                        transaction.Id = new Guid(sdr["Id"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["网点用户Id"].ToString()))
                                        transaction.userId = new Guid(sdr["网点用户Id"].ToString());
                                    transaction.name = sdr["用户名"].ToString();
                                    transaction.type = sdr["业务类型"].ToString();
                                    transaction.phoneNo = sdr["办理号码"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["办理前余额"].ToString()))
                                        transaction.accountBefore = Convert.ToDouble(sdr["办理前余额"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["办理金额"].ToString()))
                                        transaction.processMoney = Convert.ToDouble(sdr["办理金额"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["返款金额"].ToString()))
                                        transaction.returnMoney = Convert.ToDouble(sdr["返款金额"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["办理后余额"].ToString()))
                                        transaction.accountAfter = Convert.ToDouble(sdr["办理后余额"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["办理时间"].ToString()))
                                        transaction.processTime = Convert.ToDateTime(sdr["办理时间"].ToString());
                                    transaction.state = sdr["状态"].ToString();
                                    list.Add(transaction);
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

            return list;
        }

        [WebMethod]
        //根据条件获取符合条件的交易统计记录
        public List<TransStaticsItem> GetTransactionStaticsByCondition(string condition, string sessionId)
        {
            var list = new List<TransStaticsItem>();
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return list;
            }

            //解密数据
            condition = NetSecurity.decrypt(condition);

            string selectCondition = "";


            if (!string.IsNullOrEmpty(condition))
            {
                selectCondition = "Where " + condition;
            }
            var selectCommand = string.Format("SELECT [业务类型],COUNT(Id) as 办理笔数,sum([办理金额]) as 办理总额,sum([返款金额]) as 利润 FROM [MobileManage].[dbo].[交易明细信息] {0} group by [业务类型]", selectCondition);//组合选择语句
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
                        using (SqlDataReader sdr = cmd.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                int totalCount = 0;
                                double totalPay = 0;
                                double totalCharge = 0;
                                double totalReturn = 0;

                                while (sdr.Read())
                                {
                                    var transaction = new TransStaticsItem();
                                    transaction.transName = sdr["业务类型"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["办理笔数"].ToString()))
                                    {
                                        transaction.count = Convert.ToInt16(sdr["办理笔数"].ToString());
                                        totalCount += transaction.count;
                                    }

                                    if (transaction.transName != "账户充值")
                                    {
                                        if (!string.IsNullOrEmpty(sdr["办理总额"].ToString()))
                                        {
                                            transaction.totalPay = Convert.ToDouble(sdr["办理总额"].ToString());
                                            totalPay += transaction.totalPay;
                                        }
                                        //扣款金额
                                        transaction.totalCharge = transaction.totalPay;
                                        totalCharge += transaction.totalCharge;
                                        //返款
                                        if (!string.IsNullOrEmpty(sdr["利润"].ToString()))
                                        {
                                            transaction.totalReturn = Convert.ToDouble(sdr["利润"].ToString());
                                            totalReturn += transaction.totalReturn;
                                        }
                                    }
                                    else
                                    {
                                        if (!string.IsNullOrEmpty(sdr["办理总额"].ToString()))
                                        {
                                            transaction.totalPay = Convert.ToDouble(sdr["办理总额"].ToString());
                                        }
                                        transaction.totalCharge = 0;
                                        transaction.totalReturn = 0;

                                    }
                                    list.Add(transaction);
                                }
                                //最后的总计信息
                                var totalTrans = new TransStaticsItem();
                                totalTrans.transName = "总计";
                                totalTrans.count = totalCount;
                                totalTrans.totalPay = totalPay;
                                totalTrans.totalCharge = totalCharge;
                                totalTrans.totalReturn = totalReturn;
                                list.Add(totalTrans);
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

            return list;
        }

        [WebMethod]
        //根据条件获取符合条件的缴费记录或者缴费历史记录
        public List<PaymentItem> GetPaymentOrPaymentHistoryByCondition(string condition, string sessionId)
        {
            var list = new List<PaymentItem>();
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return list;
            }

            //解密数据
            condition = NetSecurity.decrypt(condition);

            string selectCondition = "";


            if (!string.IsNullOrEmpty(condition))
            {
                selectCondition = "Where " + condition;
            }
            var selectCommand = string.Format("SELECT * FROM [MobileManage].[dbo].[缴费汇总信息]  {0} ", selectCondition);//组合选择语句
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
                        using (SqlDataReader sdr = cmd.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {
                                    var paymentItem = new PaymentItem
                                    {
                                        Id = new Guid(sdr["Id"].ToString()),
                                        customerName = sdr["缴费客户名称"].ToString(),
                                        telNo = sdr["缴费客户号码"].ToString(),
                                        clientType = sdr["客户端类型"].ToString(),
                                        chargeMoney = Convert.ToDouble(sdr["缴费金额"]),
                                        chargeTime = Convert.ToDateTime(sdr["缴费时间"].ToString()),
                                        NoLocation = sdr["号码归属"].ToString(),
                                        customerBeforeMoney = Convert.ToDouble(sdr["缴费前余额"].ToString()),
                                        customerAfterMoney = Convert.ToDouble(sdr["缴费后余额"].ToString()),
                                        moneyBefore = Convert.ToDouble(sdr["处理前金额"].ToString()),
                                        moneyAfter = Convert.ToDouble(sdr["处理后金额"].ToString()),
                                        state = sdr["缴费状态"].ToString(),
                                        brand = sdr["品牌"].ToString(),
                                        area = sdr["地区"].ToString(),
                                        user_id = sdr["网点用户Id"].ToString(),
                                        user_name = sdr["网点用户登录名"].ToString(),
                                        work_id = sdr["员工Id"].ToString(),
                                        work_name = sdr["员工登录名"].ToString(),
                                        manager_name = sdr["业务负责人"].ToString(),
                                        repay = Convert.ToDouble(sdr["返款金额"]),
                                        SP = sdr["运营商"].ToString()
                                    };

                                    list.Add(paymentItem);
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

            return list;
        }

        [WebMethod]
        //根据条件获取符合条件宽带缴费记录
        public List<PayInternetItem> GetPayInternetByCondition(int top, string condition, string sessionId)
        {
            var list = new List<PayInternetItem>();
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return list;
            }

            //解密数据
            condition = NetSecurity.decrypt(condition);

            string topMessage = "";
            string selectCondition = "";
            if (top != 0) //查询头几条
            {
                topMessage = " TOP " + top;
            }
            else
            {
                topMessage = "";
            }

            if (!string.IsNullOrEmpty(condition))
            {
                selectCondition = "Where " + condition;
            }
            var selectCommand = string.Format("SELECT {0} * FROM [MobileManage].[dbo].[宽带缴费信息] {1} ", topMessage, selectCondition);//组合选择语句
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
                        using (SqlDataReader sdr = cmd.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {
                                    var payInternetItem = new PayInternetItem();
                                    if (!string.IsNullOrEmpty(sdr["Id"].ToString()))
                                        payInternetItem.Id = new Guid(sdr["Id"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["网点用户Id"].ToString()))
                                        payInternetItem.userId = new Guid(sdr["网点用户Id"].ToString());
                                    payInternetItem.userName = sdr["网点用户登录名"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["提交日期"].ToString()))
                                        payInternetItem.addDateTime = Convert.ToDateTime(sdr["提交日期"].ToString());
                                    payInternetItem.internentType = sdr["宽带类型"].ToString();
                                    payInternetItem.internetAccount = sdr["宽带账号"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["缴费金额"].ToString()))
                                        payInternetItem.money = Convert.ToDouble(sdr["缴费金额"].ToString());
                                    payInternetItem.content = sdr["备注"].ToString();
                                    payInternetItem.state = sdr["状态"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["处理前余额"].ToString()))
                                        payInternetItem.moneyBefore = Convert.ToDouble(sdr["处理前余额"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["处理后余额"].ToString()))
                                        payInternetItem.moneyAfter = Convert.ToDouble(sdr["处理后余额"].ToString());
                                    payInternetItem.clientType = sdr["客户端类型"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["返款金额"].ToString()))
                                        payInternetItem.returnMoney = Convert.ToDouble(sdr["返款金额"].ToString());
                                    payInternetItem.area = sdr["地区"].ToString();
                                    payInternetItem.location = sdr["号码归属"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["员工Id"].ToString()))
                                        payInternetItem.workId = new Guid(sdr["员工Id"].ToString());
                                    payInternetItem.work_name = sdr["员工登录名"].ToString();
                                    payInternetItem.manager_name = sdr["业务负责人"].ToString();
                                    //payInternetItem.customerName = sdr["缴费客户名称"].ToString();
                                    //if (!string.IsNullOrEmpty(sdr["缴费前余额"].ToString()))
                                    //    payInternetItem.customerBeforeMoney = Convert.ToDouble(sdr["缴费前余额"].ToString());
                                    //if (!string.IsNullOrEmpty(sdr["缴费后余额"].ToString()))
                                    //    payInternetItem.customerAfterMoney = Convert.ToDouble(sdr["缴费后余额"].ToString());
                                    list.Add(payInternetItem);
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

            return list;
        }

        [WebMethod]
        //根据条件获取符合条件宽带缴费记录或者宽带缴费历史记录
        public List<PayInternetItem> GetPayInternetHistoryByCondition(string condition, string sessionId)
        {
            var list = new List<PayInternetItem>();
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return list;
            }

            //解密数据
            condition = NetSecurity.decrypt(condition);

            string selectCondition = "";


            if (!string.IsNullOrEmpty(condition))
            {
                selectCondition = "Where " + condition;
            }
            var selectCommand = string.Format("select * from 宽带汇总信息 {0} ", selectCondition);//组合选择语句
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
                        using (SqlDataReader sdr = cmd.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {
                                    var payInternetItem = new PayInternetItem();
                                    if (!string.IsNullOrEmpty(sdr["Id"].ToString()))
                                        payInternetItem.Id = new Guid(sdr["Id"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["网点用户Id"].ToString()))
                                        payInternetItem.userId = new Guid(sdr["网点用户Id"].ToString());
                                    payInternetItem.userName = sdr["网点用户登录名"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["提交日期"].ToString()))
                                        payInternetItem.addDateTime = Convert.ToDateTime(sdr["提交日期"].ToString());
                                    payInternetItem.internentType = sdr["宽带类型"].ToString();
                                    payInternetItem.internetAccount = sdr["宽带账号"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["缴费金额"].ToString()))
                                        payInternetItem.money = Convert.ToDouble(sdr["缴费金额"].ToString());
                                    payInternetItem.content = sdr["备注"].ToString();
                                    payInternetItem.state = sdr["状态"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["处理前余额"].ToString()))
                                        payInternetItem.moneyBefore = Convert.ToDouble(sdr["处理前余额"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["处理后余额"].ToString()))
                                        payInternetItem.moneyAfter = Convert.ToDouble(sdr["处理后余额"].ToString());
                                    payInternetItem.clientType = sdr["客户端类型"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["返款金额"].ToString()))
                                        payInternetItem.returnMoney = Convert.ToDouble(sdr["返款金额"].ToString());
                                    payInternetItem.area = sdr["地区"].ToString();
                                    payInternetItem.location = sdr["号码归属"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["员工Id"].ToString()))
                                        payInternetItem.workId = new Guid(sdr["员工Id"].ToString());
                                    payInternetItem.work_name = sdr["员工登录名"].ToString();
                                    payInternetItem.manager_name = sdr["业务负责人"].ToString();
                                    //payInternetItem.customerName = sdr["缴费客户名称"].ToString();
                                    //if (!string.IsNullOrEmpty(sdr["缴费前余额"].ToString()))
                                    //    payInternetItem.customerBeforeMoney = Convert.ToDouble(sdr["缴费前余额"].ToString());
                                    //if (!string.IsNullOrEmpty(sdr["缴费后余额"].ToString()))
                                    //    payInternetItem.customerAfterMoney = Convert.ToDouble(sdr["缴费后余额"].ToString());
                                    list.Add(payInternetItem);
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

            return list;
        }

        [WebMethod]
        //根据条件获取符合条件游戏充值记录
        public List<PayGameItem> GetPayGameByCondition(int top, string condition, string sessionId)
        {
            var list = new List<PayGameItem>();
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return list;
            }

            //解密数据
            condition = NetSecurity.decrypt(condition);

            string topMessage = "";
            string selectCondition = "";
            if (top != 0) //查询头几条
            {
                topMessage = " TOP " + top;
            }
            else
            {
                topMessage = "";
            }


            if (!string.IsNullOrEmpty(condition))
            {
                selectCondition = "Where " + condition;
            }
            var selectCommand = string.Format("SELECT {0} * FROM [MobileManage].[dbo].[游戏充值信息] {1} ", topMessage, selectCondition);//组合选择语句
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
                                    var payGameItem = new PayGameItem();
                                    if (!string.IsNullOrEmpty(sdr["Id"].ToString()))
                                        payGameItem.Id = new Guid(sdr["Id"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["网点用户Id"].ToString()))
                                        payGameItem.userId = new Guid(sdr["网点用户Id"].ToString());
                                    payGameItem.userName = sdr["网点用户登录名"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["提交日期"].ToString()))
                                        payGameItem.addDateTime = Convert.ToDateTime(sdr["提交日期"].ToString());
                                    payGameItem.gameType = sdr["游戏类型名称"].ToString();
                                    payGameItem.gameAccount = sdr["游戏账号"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["缴费金额"].ToString()))
                                        payGameItem.money = Convert.ToDouble(sdr["缴费金额"].ToString());
                                    payGameItem.content = sdr["备注"].ToString();
                                    payGameItem.state = sdr["状态"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["员工Id"].ToString()))
                                        payGameItem.workId = new Guid(sdr["员工Id"].ToString());
                                    payGameItem.work_name = sdr["员工登录名"].ToString();
                                    payGameItem.manager_name = sdr["业务负责人"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["处理前余额"].ToString()))
                                        payGameItem.moneyBefore = Convert.ToDouble(sdr["处理前余额"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["处理后余额"].ToString()))
                                        payGameItem.moneyAfter = Convert.ToDouble(sdr["处理后余额"].ToString());
                                    payGameItem.clientType = sdr["客户端类型"].ToString();

                                    if (!string.IsNullOrEmpty(sdr["返款金额"].ToString()))
                                        payGameItem.returnMoney = Convert.ToDouble(sdr["返款金额"].ToString());

                                    //payGameItem.customerName = sdr["缴费客户名称"].ToString();
                                    //if (!string.IsNullOrEmpty(sdr["缴费前余额"].ToString()))
                                    //    payGameItem.customerBeforeMoney = Convert.ToDouble(sdr["缴费前余额"].ToString());
                                    //if (!string.IsNullOrEmpty(sdr["缴费后余额"].ToString()))
                                    //    payGameItem.customerAfterMoney = Convert.ToDouble(sdr["缴费后余额"].ToString());
                                    list.Add(payGameItem);
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

            return list;
        }

        [WebMethod]
        //根据条件获取符合条件游戏充值记录或者游戏充值历史记录
        public List<PayGameItem> GetPayGameHistoryByCondition(string condition, string sessionId)
        {
            var list = new List<PayGameItem>();
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return list;
            }

            //解密数据
            condition = NetSecurity.decrypt(condition);

            string selectCondition = "";


            if (!string.IsNullOrEmpty(condition))
            {
                selectCondition = "Where " + condition;
            }
            var selectCommand = string.Format("SELECT * FROM [MobileManage].[dbo].[游戏汇总信息]  {0} ", selectCondition);//组合选择语句
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
                        using (SqlDataReader sdr = cmd.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {
                                    var payGameItem = new PayGameItem();
                                    if (!string.IsNullOrEmpty(sdr["Id"].ToString()))
                                        payGameItem.Id = new Guid(sdr["Id"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["网点用户Id"].ToString()))
                                        payGameItem.userId = new Guid(sdr["网点用户Id"].ToString());
                                    payGameItem.userName = sdr["网点用户登录名"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["提交日期"].ToString()))
                                        payGameItem.addDateTime = Convert.ToDateTime(sdr["提交日期"].ToString());
                                    payGameItem.gameType = sdr["游戏类型名称"].ToString();
                                    payGameItem.gameAccount = sdr["游戏账号"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["缴费金额"].ToString()))
                                        payGameItem.money = Convert.ToDouble(sdr["缴费金额"].ToString());
                                    payGameItem.content = sdr["备注"].ToString();
                                    payGameItem.state = sdr["状态"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["员工Id"].ToString()))
                                        payGameItem.workId = new Guid(sdr["员工Id"].ToString());
                                    payGameItem.work_name = sdr["员工登录名"].ToString();
                                    payGameItem.manager_name = sdr["业务负责人"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["处理前余额"].ToString()))
                                        payGameItem.moneyBefore = Convert.ToDouble(sdr["处理前余额"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["处理后余额"].ToString()))
                                        payGameItem.moneyAfter = Convert.ToDouble(sdr["处理后余额"].ToString());
                                    payGameItem.clientType = sdr["客户端类型"].ToString();

                                    if (!string.IsNullOrEmpty(sdr["返款金额"].ToString()))
                                        payGameItem.returnMoney = Convert.ToDouble(sdr["返款金额"].ToString());
                                    //payGameItem.customerName = sdr["缴费客户名称"].ToString();
                                    //if (!string.IsNullOrEmpty(sdr["缴费前余额"].ToString()))
                                    //    payGameItem.customerBeforeMoney = Convert.ToDouble(sdr["缴费前余额"].ToString());
                                    //if (!string.IsNullOrEmpty(sdr["缴费后余额"].ToString()))
                                    //    payGameItem.customerAfterMoney = Convert.ToDouble(sdr["缴费后余额"].ToString());
                                    list.Add(payGameItem);
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

            return list;
        }

        //[WebMethod]
        ////根据条件获取符合条件游戏名称列表
        //public List<GameType> GetGameTypeByCondition(string condition, string sessionId)
        //{
        //    var list = new List<GameType>();
        //    if (!SessionValidater.ValidateSessionId(sessionId))
        //    {
        //        //不合法的请求调用
        //        return list;
        //    }

        //    //解密数据
        //    condition = NetSecurity.decrypt(condition);

        //    string selectCondition = "";


        //    if (!string.IsNullOrEmpty(condition))
        //    {
        //        selectCondition = "Where " + condition;
        //    }
        //    var selectCommand = string.Format("select * from [MobileManage].[dbo].[游戏类型] {0} ", selectCondition);//组合选择语句
        //    using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
        //    {
        //        try
        //        {
        //            con.Open();

        //            using (var cmd = new SqlCommand())
        //            {
        //                cmd.CommandText = selectCommand;
        //                cmd.CommandType = CommandType.Text;
        //                cmd.Connection = con;
        //                using (SqlDataReader sdr = cmd.ExecuteReader())// cmd2.ExecuteNonQuery();
        //                {

        //                    if (sdr.HasRows)
        //                    {
        //                        while (sdr.Read())
        //                        {
        //                            var gameType = new GameType();
        //                            if (!string.IsNullOrEmpty(sdr["Id"].ToString()))
        //                                gameType.Id = new Guid(sdr["Id"].ToString());
        //                            gameType.gameName = sdr["游戏类型名称"].ToString();
        //                            if (!string.IsNullOrEmpty(sdr["返款比例"].ToString()))
        //                                gameType.returnPercent = Convert.ToDouble(sdr["返款比例"].ToString());
        //                            list.Add(gameType);
        //                        }

        //                        cmd.Dispose();
        //                        sdr.Close();
        //                    }
        //                }
        //            }
        //        }
        //        catch (Exception ex)
        //        {
        //            throw new Exception(ex.Message);
        //        }
        //        finally
        //        {
        //            con.Close();
        //        }
        //        return list;
        //    }
        //}

        //[WebMethod]
        ////根据条件获取符合条件宽带名称列表
        //public List<InternetType> GetInternetTypeByCondition(string condition, string sessionId)
        //{
        //    var list = new List<InternetType>();
        //    if (!SessionValidater.ValidateSessionId(sessionId))
        //    {
        //        //不合法的请求调用
        //        return list;
        //    }

        //    //解密数据
        //    condition = NetSecurity.decrypt(condition);

        //    string selectCondition = "";


        //    if (!string.IsNullOrEmpty(condition))
        //    {
        //        selectCondition = "Where " + condition;
        //    }
        //    var selectCommand = string.Format("select * from [MobileManage].[dbo].[宽带类型] {0} ", selectCondition);//组合选择语句
        //    using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
        //    {
        //        try
        //        {
        //            con.Open();

        //            using (var cmd = new SqlCommand())
        //            {
        //                cmd.CommandText = selectCommand;
        //                cmd.CommandType = CommandType.Text;
        //                cmd.Connection = con;
        //                using (SqlDataReader sdr = cmd.ExecuteReader())// cmd2.ExecuteNonQuery();
        //                {

        //                    if (sdr.HasRows)
        //                    {
        //                        while (sdr.Read())
        //                        {
        //                            var internetType = new InternetType();
        //                            if (!string.IsNullOrEmpty(sdr["Id"].ToString()))
        //                                internetType.Id = new Guid(sdr["Id"].ToString());
        //                            internetType.internetName = sdr["宽带类型"].ToString();
        //                            internetType.area = sdr["地区"].ToString();
        //                            if (!string.IsNullOrEmpty(sdr["返款比例"].ToString()))
        //                                internetType.returnPercent = Convert.ToDouble(sdr["返款比例"].ToString());
        //                            list.Add(internetType);
        //                        }

        //                        cmd.Dispose();
        //                        sdr.Close();
        //                    }
        //                }
        //            }
        //        }
        //        catch (Exception ex)
        //        {
        //            throw new Exception(ex.Message);
        //        }
        //        finally
        //        {
        //            con.Close();
        //        }
        //    }

        //    return list;
        //}

        [WebMethod]
        //根据条件获取符合条件公话缴费记录
        public List<PayPublicTelItem> GetPayPublicTelByCondition(int top, string condition, string sessionId)
        {
            var list = new List<PayPublicTelItem>();
            
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return list;
            }

            //解密数据
            condition = NetSecurity.decrypt(condition);
            
            string topMessage = "";
            string selectCondition = "";
            if (top != 0) //查询头几条
            {
                topMessage = " TOP " + top;
            }
            else
            {
                topMessage = "";
            }

            if (!string.IsNullOrEmpty(condition))
            {
                selectCondition = "Where " + condition;
            }
            var selectCommand = string.Format("SELECT {0} * FROM [MobileManage].[dbo].[公话缴费信息] {1} ", topMessage, selectCondition);//组合选择语句
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
                        using (SqlDataReader sdr = cmd.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {
                                    var payInternetItem = new PayPublicTelItem();
                                    if (!string.IsNullOrEmpty(sdr["Id"].ToString()))
                                        payInternetItem.Id = new Guid(sdr["Id"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["网点用户Id"].ToString()))
                                        payInternetItem.userId = new Guid(sdr["网点用户Id"].ToString());
                                    payInternetItem.userName = sdr["网点用户登录名"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["提交日期"].ToString()))
                                        payInternetItem.addDateTime = Convert.ToDateTime(sdr["提交日期"].ToString());
                                    payInternetItem.telType = sdr["公话类型"].ToString();
                                    payInternetItem.telAccount = sdr["公话号码"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["缴费金额"].ToString()))
                                        payInternetItem.money = Convert.ToDouble(sdr["缴费金额"].ToString());
                                    payInternetItem.content = sdr["备注"].ToString();
                                    payInternetItem.state = sdr["状态"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["员工Id"].ToString()))
                                        payInternetItem.workId = new Guid(sdr["员工Id"].ToString());
                                    payInternetItem.work_name = sdr["员工登录名"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["处理前余额"].ToString()))
                                        payInternetItem.moneyBefore = Convert.ToDouble(sdr["处理前余额"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["处理后余额"].ToString()))
                                        payInternetItem.moneyAfter = Convert.ToDouble(sdr["处理后余额"].ToString());
                                    payInternetItem.clientType = sdr["客户端类型"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["返款金额"].ToString()))
                                        payInternetItem.returnMoney = Convert.ToDouble(sdr["返款金额"].ToString());
                                    payInternetItem.area = sdr["地区"].ToString();
                                    payInternetItem.location = sdr["号码归属"].ToString();
                                    payInternetItem.customerName = sdr["缴费客户名称"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["缴费前余额"].ToString()))
                                        payInternetItem.customerBeforeMoney = Convert.ToDouble(sdr["缴费前余额"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["缴费后余额"].ToString()))
                                        payInternetItem.customerAfterMoney = Convert.ToDouble(sdr["缴费后余额"].ToString());
                                    list.Add(payInternetItem);
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

            return list;
        }

        [WebMethod]
        //根据条件获取符合条件公话缴费记录或者公话缴费历史记录
        public List<PayPublicTelItem> GetPayPublicTelHistoryByCondition(string condition, string sessionId)
        {
            var list = new List<PayPublicTelItem>();
            
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return list;
            }

            //解密数据
            condition = NetSecurity.decrypt(condition);
            
            string selectCondition = "";


            if (!string.IsNullOrEmpty(condition))
            {
                selectCondition = "Where " + condition;
            }
            var selectCommand = string.Format("SELECT * FROM [MobileManage].[dbo].[公话汇总信息] {0} ", selectCondition);//组合选择语句
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
                        using (SqlDataReader sdr = cmd.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {
                                    var payInternetItem = new PayPublicTelItem();
                                    if (!string.IsNullOrEmpty(sdr["Id"].ToString()))
                                        payInternetItem.Id = new Guid(sdr["Id"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["网点用户Id"].ToString()))
                                        payInternetItem.userId = new Guid(sdr["网点用户Id"].ToString());
                                    payInternetItem.userName = sdr["网点用户登录名"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["提交日期"].ToString()))
                                        payInternetItem.addDateTime = Convert.ToDateTime(sdr["提交日期"].ToString());
                                    payInternetItem.telType = sdr["公话类型"].ToString();
                                    payInternetItem.telAccount = sdr["公话号码"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["缴费金额"].ToString()))
                                        payInternetItem.money = Convert.ToDouble(sdr["缴费金额"].ToString());
                                    payInternetItem.content = sdr["备注"].ToString();
                                    payInternetItem.state = sdr["状态"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["员工Id"].ToString()))
                                        payInternetItem.workId = new Guid(sdr["员工Id"].ToString());
                                    payInternetItem.work_name = sdr["员工登录名"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["业务负责人"].ToString()))
                                        payInternetItem.manager_name = sdr["业务负责人"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["处理前余额"].ToString()))
                                        payInternetItem.moneyBefore = Convert.ToDouble(sdr["处理前余额"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["处理后余额"].ToString()))
                                        payInternetItem.moneyAfter = Convert.ToDouble(sdr["处理后余额"].ToString());
                                    payInternetItem.clientType = sdr["客户端类型"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["返款金额"].ToString()))
                                        payInternetItem.returnMoney = Convert.ToDouble(sdr["返款金额"].ToString());
                                    payInternetItem.area = sdr["地区"].ToString();
                                    payInternetItem.location = sdr["号码归属"].ToString();
                                    payInternetItem.customerName = sdr["缴费客户名称"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["缴费前余额"].ToString()))
                                        payInternetItem.customerBeforeMoney = Convert.ToDouble(sdr["缴费前余额"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["缴费后余额"].ToString()))
                                        payInternetItem.customerAfterMoney = Convert.ToDouble(sdr["缴费后余额"].ToString());
                                    list.Add(payInternetItem);
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

            return list;
        }

        #endregion
        /*
        #region 服务端专用

        [WebMethod]
        //更新缴费状态
        public bool UpdatePaymentState(string paymentId, string state, string sessionId)
        {

            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return false;
            }
            //解密
            paymentId = NetSecurity.decrypt(paymentId);
            state = NetSecurity.decrypt(state);


            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_更改缴费状态";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp1 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(paymentId) };
                        cmd.Parameters.Add(sp1);

                        var sp2 = new SqlParameter("@State", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = state };
                        cmd.Parameters.Add(sp2);


                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;


                        cmd.ExecuteNonQuery();




                        var result = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (result.Equals("1"))
                        {
                            return true;
                        }

                        cmd.Dispose();
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
            return false;
        }

        [WebMethod]
        //更新游戏充值状态
        public bool UpdateGamePaymentState(string paymentId, string state, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return false;
            }
            //解密
            paymentId = NetSecurity.decrypt(paymentId);
            state = NetSecurity.decrypt(state);

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_更改游戏充值状态";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp1 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(paymentId) };
                        cmd.Parameters.Add(sp1);

                        var sp2 = new SqlParameter("@State", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = state };
                        cmd.Parameters.Add(sp2);


                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;


                        cmd.ExecuteNonQuery();




                        var result = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (result.Equals("1"))
                        {
                            return true;
                        }

                        cmd.Dispose();
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
            return false;
        }


        [WebMethod]
        //更新宽带充值状态
        public bool UpdateInternetPaymentState(string paymentId, string state, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return false;
            }
            //解密
            paymentId = NetSecurity.decrypt(paymentId);
            state = NetSecurity.decrypt(state);

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_更改宽带充值状态";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp1 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(paymentId) };
                        cmd.Parameters.Add(sp1);

                        var sp2 = new SqlParameter("@State", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = state };
                        cmd.Parameters.Add(sp2);


                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;


                        cmd.ExecuteNonQuery();




                        var result = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (result.Equals("1"))
                        {
                            return true;
                        }

                        cmd.Dispose();
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
            return false;
        }

        [WebMethod]
        //更新公话缴费状态
        public bool UpdatePublicTelPaymentState(string paymentId, string state, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return false;
            }
            //解密
            paymentId = NetSecurity.decrypt(paymentId);
            state = NetSecurity.decrypt(state);

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_更改公话缴费状态";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp1 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(paymentId) };
                        cmd.Parameters.Add(sp1);

                        var sp2 = new SqlParameter("@State", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = state };
                        cmd.Parameters.Add(sp2);


                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;


                        cmd.ExecuteNonQuery();

                        var result = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (result.Equals("1"))
                        {
                            return true;
                        }

                        cmd.Dispose();
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
            return false;
        }


        [WebMethod]
        //锁定缴费信息
        public bool LockPayment(string paymentId, string workerId, string workerName, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId, workerId))
            {
                //不合法的请求调用
                return false;
            }
            //解密
            paymentId = NetSecurity.decrypt(paymentId);
            workerId = NetSecurity.decrypt(workerId);
            workerName = NetSecurity.decrypt(workerName);



            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_更改缴费状态为锁定_员工";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp1 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(paymentId) };
                        cmd.Parameters.Add(sp1);

                        var sp2 = new SqlParameter("@员工Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(workerId) };
                        cmd.Parameters.Add(sp2);

                        var sp3 = new SqlParameter("@name", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = workerName };
                        cmd.Parameters.Add(sp3);

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;

                        cmd.ExecuteNonQuery();

                        var result = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (result.Equals("1"))
                        {
                            return true;
                        }

                        cmd.Dispose();
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
            return false;
        }


        [WebMethod]
        //锁定缴费信息
        public bool LockGamePayment(string paymentId, string workerId, string workerName, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId, workerId))
            {
                //不合法的请求调用
                return false;
            }
            //解密
            paymentId = NetSecurity.decrypt(paymentId);
            workerId = NetSecurity.decrypt(workerId);
            workerName = NetSecurity.decrypt(workerName);

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_更改游戏充值状态为锁定_员工";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp1 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(paymentId) };
                        cmd.Parameters.Add(sp1);

                        var sp2 = new SqlParameter("@员工Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(workerId) };
                        cmd.Parameters.Add(sp2);

                        var sp3 = new SqlParameter("@name", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = workerName };
                        cmd.Parameters.Add(sp3);

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;

                        cmd.ExecuteNonQuery();

                        var result = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (result.Equals("1"))
                        {
                            return true;
                        }

                        cmd.Dispose();
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
            return false;
        }

        [WebMethod]
        //锁定缴费信息
        public bool LockInternetPayment(string paymentId, string workerId, string workerName, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId, workerId))
            {
                //不合法的请求调用
                return false;
            }
            //解密
            paymentId = NetSecurity.decrypt(paymentId);
            workerId = NetSecurity.decrypt(workerId);
            workerName = NetSecurity.decrypt(workerName);

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_更改宽带缴费状态为锁定_员工";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp1 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(paymentId) };
                        cmd.Parameters.Add(sp1);

                        var sp2 = new SqlParameter("@员工Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(workerId) };
                        cmd.Parameters.Add(sp2);

                        var sp3 = new SqlParameter("@name", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = workerName };
                        cmd.Parameters.Add(sp3);

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;

                        cmd.ExecuteNonQuery();

                        var result = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (result.Equals("1"))
                        {
                            return true;
                        }

                        cmd.Dispose();
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
            return false;
        }

        [WebMethod]
        //锁定公话缴费信息
        public bool LockPublicTelPayment(string paymentId, string workerId, string workerName, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId, workerId))
            {
                //不合法的请求调用
                return false;
            }
            //解密
            paymentId = NetSecurity.decrypt(paymentId);
            workerId = NetSecurity.decrypt(workerId);
            workerName = NetSecurity.decrypt(workerName);

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_更改公话缴费状态为锁定_员工";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp1 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(paymentId) };
                        cmd.Parameters.Add(sp1);

                        var sp2 = new SqlParameter("@员工Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(workerId) };
                        cmd.Parameters.Add(sp2);

                        var sp3 = new SqlParameter("@name", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = workerName };
                        cmd.Parameters.Add(sp3);

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;

                        cmd.ExecuteNonQuery();

                        var result = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (result.Equals("1"))
                        {
                            return true;
                        }

                        cmd.Dispose();
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
            return false;
        }

        [WebMethod]
        //锁定撤销缴费信息
        public bool LockCheXiaoPayment(string paymentId, string workerId, string workerName, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId, workerId))
            {
                //不合法的请求调用
                return false;
            }
            //解密
            paymentId = NetSecurity.decrypt(paymentId);
            workerId = NetSecurity.decrypt(workerId);
            workerName = NetSecurity.decrypt(workerName);

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_更改缴费状态为撤销锁定_员工";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp1 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(paymentId) };
                        cmd.Parameters.Add(sp1);

                        var sp2 = new SqlParameter("@员工Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(workerId) };
                        cmd.Parameters.Add(sp2);

                        var sp3 = new SqlParameter("@name", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = workerName };
                        cmd.Parameters.Add(sp3);

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;

                        cmd.ExecuteNonQuery();

                        var result = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (result.Equals("1"))
                        {
                            return true;
                        }

                        cmd.Dispose();
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
            return false;
        }

        [WebMethod]
        //锁定返销缴费信息
        public bool LockFanXiaoPayment(string paymentId, string workerId, string workerName, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId, workerId))
            {
                //不合法的请求调用
                return false;
            }
            //解密
            paymentId = NetSecurity.decrypt(paymentId);
            workerId = NetSecurity.decrypt(workerId);
            workerName = NetSecurity.decrypt(workerName);

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_更改缴费状态为返销锁定_员工";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp1 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(paymentId) };
                        cmd.Parameters.Add(sp1);

                        var sp2 = new SqlParameter("@员工Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(workerId) };
                        cmd.Parameters.Add(sp2);

                        var sp3 = new SqlParameter("@name", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = workerName };
                        cmd.Parameters.Add(sp3);

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;

                        cmd.ExecuteNonQuery();

                        var result = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (result.Equals("1"))
                        {
                            return true;
                        }

                        cmd.Dispose();
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
            return false;
        }


        [WebMethod]
        //锁定返销宽带信息
        public bool LockFanXiaoInternetPayment(string paymentId, string workerId, string workerName, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId, workerId))
            {
                //不合法的请求调用
                return false;
            }
            //解密
            paymentId = NetSecurity.decrypt(paymentId);
            workerId = NetSecurity.decrypt(workerId);
            workerName = NetSecurity.decrypt(workerName);

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_更改宽带状态为返销锁定_员工";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp1 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(paymentId) };
                        cmd.Parameters.Add(sp1);

                        var sp2 = new SqlParameter("@员工Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(workerId) };
                        cmd.Parameters.Add(sp2);

                        var sp3 = new SqlParameter("@name", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = workerName };
                        cmd.Parameters.Add(sp3);

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;

                        cmd.ExecuteNonQuery();

                        var result = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (result.Equals("1"))
                        {
                            return true;
                        }

                        cmd.Dispose();
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
            return false;
        }



        [WebMethod]
        //服务端退款
        public bool RefundPayment(PaymentItem item, string userId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId, userId))
            {
                //不合法的请求调用
                return false;
            }
            //解密
            userId = NetSecurity.decrypt(userId);

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_缴费退款";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp0 = new SqlParameter("@返款金额 ", SqlDbType.Money) { Direction = ParameterDirection.Input, Value = item.repay };
                        cmd.Parameters.Add(sp0);

                        var sp1 = new SqlParameter("@缴费客户名称 ", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = item.customerName };
                        cmd.Parameters.Add(sp1);

                        var sp2 = new SqlParameter("@缴费客户号码", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = item.telNo };
                        cmd.Parameters.Add(sp2);

                        var sp4 = new SqlParameter("@缴费金额", SqlDbType.Money) { Direction = ParameterDirection.Input, Value = item.chargeMoney };
                        cmd.Parameters.Add(sp4);

                        var sp5 = new SqlParameter("@号码归属", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = item.NoLocation };
                        cmd.Parameters.Add(sp5);

                        var sp6 = new SqlParameter("@品牌", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = item.brand };
                        cmd.Parameters.Add(sp6);

                        var sp7 = new SqlParameter("@地区", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = item.area };
                        cmd.Parameters.Add(sp7);

                        var sp8 = new SqlParameter("@网点用户Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(item.user_id) };
                        cmd.Parameters.Add(sp8);

                        var sp9 = new SqlParameter("@运营商", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = item.SP };
                        cmd.Parameters.Add(sp9);

                        var sp10 = new SqlParameter("@操作者Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(userId) };
                        cmd.Parameters.Add(sp10);



                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;

                        cmd.ExecuteNonQuery();

                        var result = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (result.Equals("1"))
                        {
                            return true;
                        }

                        cmd.Dispose();
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
            return false;
        }


        [WebMethod]
        //游戏充值退款
        public bool RefundGamePayment(PayGameItem item, string userId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId, userId))
            {
                //不合法的请求调用
                return false;
            }
            //解密
            userId = NetSecurity.decrypt(userId);
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();
                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_游戏充值退款";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;
                        cmd.Parameters.Clear();


                        var sp0 = new SqlParameter("@网点用户Id", SqlDbType.UniqueIdentifier);
                        sp0.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp0);
                        sp0.Value = string.IsNullOrEmpty(userId) ? (object)DBNull.Value : item.userId;

                        var sp1 = new SqlParameter("@游戏类型名称", SqlDbType.NVarChar, 50);
                        sp1.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp1);
                        sp1.Value = item.gameType;

                        var sp4 = new SqlParameter("@游戏账号", SqlDbType.NVarChar, 50);
                        sp4.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp4);
                        sp4.Value = item.gameAccount;

                        var sp5 = new SqlParameter("@缴费金额", SqlDbType.Money);
                        sp5.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp5);
                        sp5.Value = item.money;

                        var sp6 = new SqlParameter("@备注", SqlDbType.NVarChar, 100);
                        sp6.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp6);
                        sp6.Value = item.content;

                        var sp7 = new SqlParameter("@客户端类型", SqlDbType.NVarChar, 50);
                        sp7.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp7);
                        sp7.Value = item.clientType;

                        var sp8 = new SqlParameter("@返款金额", SqlDbType.Money);
                        sp8.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp8);
                        sp8.Value = item.returnMoney;


                        var sp9 = new SqlParameter("@操作者Id", SqlDbType.UniqueIdentifier);
                        sp9.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp9);
                        if (userId != null) sp9.Value = new Guid(userId);

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("1"))
                        {
                            cmd.Dispose();
                            return true;
                        }
                        else
                        {
                            cmd.Dispose();
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
            return false;
        }



        [WebMethod]
        //宽带充值退款
        public bool RefundInternetPayment(PayInternetItem item, string userId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId, userId))
            {
                //不合法的请求调用
                return false;
            }
            //解密
            userId = NetSecurity.decrypt(userId);
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();
                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_宽带充值退款";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;
                        cmd.Parameters.Clear();


                        var sp0 = new SqlParameter("@网点用户Id", SqlDbType.UniqueIdentifier);
                        sp0.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp0);
                        sp0.Value = string.IsNullOrEmpty(userId) ? (object)DBNull.Value : item.userId;

                        var sp1 = new SqlParameter("@宽带类型名称", SqlDbType.NVarChar, 50);
                        sp1.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp1);
                        sp1.Value = item.internentType;

                        var sp4 = new SqlParameter("@宽带账号", SqlDbType.NVarChar, 50);
                        sp4.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp4);
                        sp4.Value = item.internetAccount;

                        var sp5 = new SqlParameter("@缴费金额", SqlDbType.Money);
                        sp5.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp5);
                        sp5.Value = item.money;

                        var sp6 = new SqlParameter("@备注", SqlDbType.NVarChar, 100);
                        sp6.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp6);
                        sp6.Value = item.content;

                        var sp7 = new SqlParameter("@客户端类型", SqlDbType.NVarChar, 50);
                        sp7.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp7);
                        sp7.Value = item.clientType;

                        var sp8 = new SqlParameter("@返款金额", SqlDbType.Money);
                        sp8.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp8);
                        sp8.Value = item.returnMoney;


                        var sp9 = new SqlParameter("@操作者Id", SqlDbType.UniqueIdentifier);
                        sp9.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp9);
                        if (userId != null) sp9.Value = new Guid(userId);

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("1"))
                        {
                            cmd.Dispose();
                            return true;
                        }
                        else
                        {
                            cmd.Dispose();
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
            return false;
        }

        [WebMethod]
        //公话缴费退款
        public bool RefundPublicTelPayment(PayPublicTelItem item, string userId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId, userId))
            {
                //不合法的请求调用
                return false;
            }
            //解密
            userId = NetSecurity.decrypt(userId);
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();
                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_公话缴费退款";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;
                        cmd.Parameters.Clear();


                        var sp0 = new SqlParameter("@网点用户Id", SqlDbType.UniqueIdentifier);
                        sp0.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp0);
                        sp0.Value = string.IsNullOrEmpty(userId) ? (object)DBNull.Value : item.userId;

                        var sp1 = new SqlParameter("@公话类型", SqlDbType.NVarChar, 50);
                        sp1.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp1);
                        sp1.Value = item.telType;

                        var sp4 = new SqlParameter("@公话账号", SqlDbType.NVarChar, 50);
                        sp4.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp4);
                        sp4.Value = item.telAccount;

                        var sp5 = new SqlParameter("@缴费金额", SqlDbType.Money);
                        sp5.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp5);
                        sp5.Value = item.money;

                        var sp6 = new SqlParameter("@备注", SqlDbType.NVarChar, 100);
                        sp6.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp6);
                        sp6.Value = item.content;

                        var sp7 = new SqlParameter("@客户端类型", SqlDbType.NVarChar, 50);
                        sp7.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp7);
                        sp7.Value = item.clientType;

                        var sp8 = new SqlParameter("@返款金额", SqlDbType.Money);
                        sp8.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp8);
                        sp8.Value = item.returnMoney;


                        var sp9 = new SqlParameter("@操作者Id", SqlDbType.UniqueIdentifier);
                        sp9.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp9);
                        if (userId != null) sp9.Value = new Guid(userId);

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("1"))
                        {
                            cmd.Dispose();
                            return true;
                        }
                        else
                        {
                            cmd.Dispose();
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
            return false;
        }


        [WebMethod]
        //插入缴费返款未结算记录
        public string InsertPaymentReturnedItem(ReturnedItem item, string operatorId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId, operatorId))
            {
                //不合法的请求调用
                return "非法登录！";
            }
            //解密
            operatorId = NetSecurity.decrypt(operatorId);

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_新增缴费返款未结算记录";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp0 = new SqlParameter("@网点用户Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = item.userId.Equals(Guid.Empty) ? (object)DBNull.Value : item.userId };
                        cmd.Parameters.Add(sp0);

                        var sp1 = new SqlParameter("@缴费Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = item.operationId.Equals(Guid.Empty) ? (object)DBNull.Value : item.operationId };
                        cmd.Parameters.Add(sp1);

                        var sp2 = new SqlParameter("@缴费金额", SqlDbType.Money) { Direction = ParameterDirection.Input, Value = item.money };
                        cmd.Parameters.Add(sp2);

                        var sp3 = new SqlParameter("@返款比例", SqlDbType.Float) { Direction = ParameterDirection.Input, Value = item.returnPoint };
                        cmd.Parameters.Add(sp3);

                        var sp5 = new SqlParameter("@返款类型", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = item.returnType };
                        cmd.Parameters.Add(sp5);

                        var sp4 = new SqlParameter("@操作者Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = string.IsNullOrEmpty(operatorId) ? (object)DBNull.Value : new Guid(operatorId) };
                        cmd.Parameters.Add(sp4);

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();
                        if (res.Equals("1"))
                        {
                            return "新增返款未结算记录成功";
                        }
                        else
                        {
                            return "新增返款未结算记录失败";
                        }
                    }

                }
                catch (Exception ex)
                {
                    return ex.Message;
                }
                finally
                {

                    con.Close();
                }
            }


        }

        [WebMethod]
        //返销时删除该用户的返款记录，如该记录未结算，则删除即可，若已结算，除删除该记录以外，还得扣去用户相应余额
        public string DeletePaymentReturnedItemByFanXiao(string paymentId, string operatorId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId, operatorId))
            {
                //不合法的请求调用
                return "非法登录！";
            }
            //解密
            paymentId = NetSecurity.decrypt(paymentId);
            operatorId = NetSecurity.decrypt(operatorId);

            var us = new UserFunctionWebService();
            var returnedItemNotDealList = us.GetReturnRecord(0, NetSecurity.encrypt(string.Format(" 对应业务操作Id='{0}'", paymentId)), sessionId);
            var returnedItemDealList = us.GetReturnRecordDeal(0, NetSecurity.encrypt(string.Format("对应业务操作Id='{0}'", paymentId)), sessionId);
            if (returnedItemNotDealList.Count > 0)
            {
                using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
                {
                    try
                    {
                        con.Open();

                        using (var cmd = new SqlCommand())
                        {
                            cmd.CommandText = "Function_服务端_删除缴费返款未结算记录";
                            cmd.CommandType = CommandType.StoredProcedure;
                            cmd.Connection = con;

                            var sp0 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = returnedItemNotDealList[0].Id };
                            cmd.Parameters.Add(sp0);

                            var sp4 = new SqlParameter("@操作者Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = string.IsNullOrEmpty(operatorId) ? (object)DBNull.Value : new Guid(operatorId) };
                            cmd.Parameters.Add(sp4);

                            cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                            cmd.ExecuteNonQuery();
                            var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();
                            if (res.Equals("1"))
                            {
                                return "删除该返销缴费相应的用户返款未结算记录成功！";
                            }
                            else
                            {
                                return "删除该返销缴费相应的用户返款未结算记录失败！请与管理员联系";
                            }
                        }

                    }
                    catch (Exception ex)
                    {
                        return ex.Message;
                    }
                    finally
                    {

                        con.Close();
                    }
                }
            }
            else if (returnedItemDealList.Count > 0)
            {
                using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
                {
                    try
                    {
                        con.Open();

                        using (var cmd = new SqlCommand())
                        {
                            cmd.CommandText = "Function_服务端_删除缴费返款已结算记录并扣除用户余额";
                            cmd.CommandType = CommandType.StoredProcedure;
                            cmd.Connection = con;

                            var sp0 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = returnedItemDealList[0].Id };
                            cmd.Parameters.Add(sp0);

                            var sp4 = new SqlParameter("@操作者Id", SqlDbType.UniqueIdentifier)
                                          {
                                              Direction = ParameterDirection.Input,
                                              Value =
                                                  string.IsNullOrEmpty(operatorId)
                                                      ? (object)DBNull.Value
                                                      : new Guid(operatorId)
                                          };
                            cmd.Parameters.Add(sp4);

                            cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                            cmd.ExecuteNonQuery();
                            var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();
                            if (res.Equals("1"))
                            {
                                return "删除该返销缴费相应的用户返款已结算记录成功！并已扣除相应返款！";
                            }
                            else
                            {
                                return "删除该返销缴费相应的用户返款已结算记录失败！请与管理员联系";
                            }
                        }

                    }
                    catch (Exception ex)
                    {
                        return ex.Message;
                    }
                    finally
                    {

                        con.Close();
                    }
                }
            }
            return "并未查到相应返款信息";
        }



        #endregion
        */
    }
}
