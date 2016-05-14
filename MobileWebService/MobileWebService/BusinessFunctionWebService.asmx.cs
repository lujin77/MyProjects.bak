using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services;
using MobileWebService.Entity;
using MobileWebService.Validater;
using System.Data.SqlClient;
using System.Data;

namespace MobileWebService
{
    /// <summary>
    /// BusinessFunctionWebService 的摘要说明
    /// </summary>
    [WebService(Namespace = "http://tempuri.org/")]
    [WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
    [System.ComponentModel.ToolboxItem(false)]
    // 若要允许使用 ASP.NET AJAX 从脚本中调用此 Web 服务，请取消对下行的注释。
    // [System.Web.Script.Services.ScriptService]
    public class BusinessFunctionWebService : System.Web.Services.WebService
    {
        #region 客户端专用

        //小卡扣款
        [WebMethod]
        public string BuyMiniCard(string data, string userId, string workerId, string SP, string count, string money, string content, string clientType, string sessionId)
        {

            if (!SessionValidater.ValidateSessionId(sessionId, userId))
            {
                //不合法的请求调用
                return "非法登录！";
            }

            //解密数据
            data = NetSecurity.decrypt(data);
            userId = NetSecurity.decrypt(userId);
            workerId = NetSecurity.decrypt(workerId);
            SP = NetSecurity.decrypt(SP);
            count = NetSecurity.decrypt(count);
            money = NetSecurity.decrypt(money);
            content = NetSecurity.decrypt(content);
            clientType = NetSecurity.decrypt(clientType);

            //验证权限
            if (!AuthorizationHelper.validate(userId).Contains("小卡扣款"))
            {
                return null;
            }

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
                                    double currentMoney = 0;
                                    currentMoney = Convert.ToDouble(sdr["账户余额"].ToString());
                                    if (currentMoney < Convert.ToDouble(money))
                                    {
                                        return "您当前的余额为：" + currentMoney + "，不足以扣款" + money + "元";
                                    }
                                }
                                sdr.Close();
                            }
                        }
                    }

                    //构造数据, 验证小卡号码和业务员，运营商是否匹配
                    string[] tmp = data.Split(',');
                    string realWorkId = "";
                    string realSP = "";
                    List<string> miniCardIdList = new List<string>();
                    foreach (string str in tmp)
                    {
                        if (!string.IsNullOrEmpty(str))
                        {
                            //先验证该小卡是否是该业务员的
                            using (var cmd = new SqlCommand())
                            {
                                cmd.CommandText = "select * from 库存小卡 where 小卡号码='" + str + "' and 使用状态='未使用' ";
                                cmd.CommandType = CommandType.Text;
                                cmd.Connection = con;
                                using (SqlDataReader sdr = cmd.ExecuteReader())
                                {

                                    if (sdr.HasRows)
                                    {
                                        if (sdr.Read())
                                        {
                                            miniCardIdList.Add(sdr["Id"].ToString());
                                            realWorkId = sdr["业务员Id"].ToString();
                                            realSP = sdr["运营商"].ToString();
                                        }
                                        cmd.Dispose();
                                        sdr.Close();
                                    }
                                    else
                                    {
                                        return "您输入的小卡号" + str + "不存在或已被销售, 请重新检查!";
                                    }

                                    if (realWorkId.ToUpper() != workerId.ToUpper())
                                    {
                                        return "您输入的小卡号" + str + "不属于该业务员, 请重新检查!";
                                    }

                                    if (realSP != SP)
                                    {
                                        return "您输入的小卡号" + str + "运营商有误, 请重新检查!";
                                    }
                                }
                            }
                        }
                    }

                    Guid recordId = Guid.NewGuid();
                    //存入小卡扣款请求记录
                    using (var cmd4 = new SqlCommand())
                    {
                        cmd4.CommandText = "Function_网点用户_小卡扣款";
                        cmd4.CommandType = CommandType.StoredProcedure;
                        cmd4.Connection = con;

                        var sp0 = new SqlParameter("@扣款Id", SqlDbType.UniqueIdentifier);
                        sp0.Direction = ParameterDirection.Input;
                        cmd4.Parameters.Add(sp0);
                        sp0.Value = recordId;

                        var sp1 = new SqlParameter("@网点用户Id", SqlDbType.UniqueIdentifier);
                        sp1.Direction = ParameterDirection.Input;
                        cmd4.Parameters.Add(sp1);
                        sp1.Value = new Guid(userId);

                        var sp2 = new SqlParameter("@业务员Id", SqlDbType.UniqueIdentifier);
                        sp2.Direction = ParameterDirection.Input;
                        cmd4.Parameters.Add(sp2);
                        sp2.Value = new Guid(workerId);

                        var sp3 = new SqlParameter("@运营商", SqlDbType.NVarChar, 50);
                        sp3.Direction = ParameterDirection.Input;
                        cmd4.Parameters.Add(sp3);
                        sp3.Value = SP;

                        var sp4 = new SqlParameter("@张数", SqlDbType.Int);
                        sp4.Direction = ParameterDirection.Input;
                        cmd4.Parameters.Add(sp4);
                        sp4.Value = Convert.ToInt16(count);

                        var sp5 = new SqlParameter("@扣款金额", SqlDbType.Money);
                        sp5.Direction = ParameterDirection.Input;
                        cmd4.Parameters.Add(sp5);
                        sp5.Value = Convert.ToDouble(money); ;

                        var sp6 = new SqlParameter("@备注", SqlDbType.Text);
                        sp6.Direction = ParameterDirection.Input;
                        cmd4.Parameters.Add(sp6);
                        sp6.Value = content;

                        var sp7 = new SqlParameter("@客户端类型", SqlDbType.NVarChar, 50);
                        sp7.Direction = ParameterDirection.Input;
                        cmd4.Parameters.Add(sp7);
                        sp7.Value = clientType;

                        cmd4.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd4.ExecuteNonQuery();
                        var res = cmd4.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("1"))
                        {
                            //讲提交的小卡号
                            using (var cmd5 = new SqlCommand())
                            {
                                //等待审核的卡号存入映射表
                                foreach (string str in miniCardIdList)
                                {
                                    if (!string.IsNullOrEmpty(str))
                                    {
                                        cmd5.CommandText = "INSERT INTO [MobileManage].[dbo].[小卡扣款_映射表] ([小卡扣款Id],[库存小卡Id]) VALUES ('" + recordId.ToString() + "','" + str + "')";
                                        cmd5.CommandType = CommandType.Text;
                                        cmd5.Connection = con;
                                        cmd5.ExecuteNonQuery();
                                    }
                                }
                            }
                            return "小卡扣款提交成功！\n共提交" + count + "张，总计：" + money + "元";
                        }
                        else
                        {
                            return "提交小卡扣款请求失败！";
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

        //查询号码
        //通过条件获取电话号码
        //传入分页的大小，要查询的页数
        //返回对象中包含信息：号码总条数，总页数，分页大小，当前页面号，页面信息
        [WebMethod]
        public PhoneNoList GetPhoneNoByCondition(int pageSize, int pageIndex, string condition, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return null;
            }
            //解密
            condition = NetSecurity.decrypt(condition);

            var phoneNoList = new PhoneNoList();
            //参数有效性验证
            if (pageSize < 1)
                return phoneNoList;
            if (pageIndex < 1)
                return phoneNoList;

            var whereCondition = "";
            if (!string.IsNullOrEmpty(condition))
            {
                whereCondition = "Where " + condition;
            }

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd0 = new SqlCommand())
                    {
                        var selectCommand = string.Format("SELECT count(Id) as total FROM [dbo].[库存号码] {0}", whereCondition);
                        cmd0.CommandText = selectCommand;
                        cmd0.CommandType = CommandType.Text;
                        cmd0.Connection = con;

                        using (SqlDataReader sdr0 = cmd0.ExecuteReader()) // cmd2.ExecuteNonQuery();
                        {
                            int total = 0;
                            if (sdr0.HasRows)
                            {
                                while (sdr0.Read())
                                {
                                    total = Convert.ToInt16(sdr0["total"].ToString());
                                }

                                cmd0.Dispose();
                                sdr0.Close();
                            }
                            phoneNoList.total = total;
                            phoneNoList.totalPage = (int)Math.Ceiling((double)total / (double)pageSize);
                            phoneNoList.currentPageIndex = pageIndex;
                            phoneNoList.pageSize = pageSize;
                        }
                    }

                    using (var cmd = new SqlCommand())
                    {
                        var selectCommand = string.Format("SELECT * FROM (SELECT ROW_NUMBER() OVER(ORDER BY [权值] desc,[领入时间]desc) AS rownum, Id, 号码, 号段, 入网政策, 选号费, 分区, 权值,使用状态 FROM [dbo].[库存号码] {2}) AS D WHERE rownum BETWEEN ({0}-1)*{1}+1 AND {0}*{1}", pageIndex, pageSize, whereCondition);
                        cmd.CommandText = selectCommand;
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;

                        using (SqlDataReader sdr = cmd.ExecuteReader()) // cmd2.ExecuteNonQuery();
                        {
                            int total = 0;
                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {
                                    total++;
                                    var phoneNoItem = new PhoneNoItem();
                                    if (!String.IsNullOrEmpty(sdr["Id"].ToString()))
                                        phoneNoItem.id = new Guid(sdr["Id"].ToString());
                                    phoneNoItem.No = sdr["号码"].ToString();
                                    phoneNoItem.NoSection = sdr["号段"].ToString();
                                    phoneNoItem.inNetPolicy = sdr["入网政策"].ToString();
                                    if (!String.IsNullOrEmpty(sdr["选号费"].ToString()))
                                        phoneNoItem.NoPrice = Convert.ToDouble(sdr["选号费"].ToString());
                                    phoneNoItem.area = sdr["分区"].ToString();
                                    if (!String.IsNullOrEmpty(sdr["权值"].ToString()))
                                        phoneNoItem.weight = Convert.ToInt16(sdr["权值"].ToString());
                                    phoneNoItem.state = sdr["使用状态"].ToString();
                                    phoneNoList.listOfPhoneNo.Add(phoneNoItem);
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
            return phoneNoList;
        }

        //获取我的号段(给出指定网点用户拥有的可以使用的小卡对应的号段)
        //SELECT [号段] FROM [MobileManage].[dbo].[库存小卡] where [使用状态]='未使用' and [网点用户Id]='512A841A-A925-4D22-9BAE-087B0FBAFDB2' and [销售时间] is not null group by [号段]
        [WebMethod]
        public List<string> GetMyNoSection(string userId, string sessionId)
        {
            List<string> list = new List<string>();

            if (!SessionValidater.ValidateSessionId(sessionId, userId))
            {
                //不合法的请求调用
                return null;
            }

            //解密
            userId = NetSecurity.decrypt(userId);

            var contents = new List<DIC_Content>();

            var selectCommand = string.Format("SELECT [号段] FROM [MobileManage].[dbo].[库存小卡] where [使用状态]='未使用' and [网点用户Id]='{0}' and [销售时间] is not null group by [号段]", userId); //组合选择语句
            using (SqlConnection con = DBConn.CreateConn()) //新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = selectCommand;
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;
                        using (SqlDataReader sdr = cmd.ExecuteReader()) // cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {
                                    string tmp = sdr["号段"].ToString();
                                    list.Add(tmp);
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

        //锁定号码
        [WebMethod]
        public string LockNo(string No, string userId, string sessionId)
        {

            if (!SessionValidater.ValidateSessionId(sessionId, userId))
            {
                //不合法的请求调用
                return "非法登录！";
            }

            //解密
            No = NetSecurity.decrypt(No);
            userId = NetSecurity.decrypt(userId);


            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_网点用户_锁定号码";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp1 = new SqlParameter("@user_Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(userId) };
                        cmd.Parameters.Add(sp1);

                        var sp2 = new SqlParameter("@号码", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = No };
                        cmd.Parameters.Add(sp2);

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;

                        cmd.ExecuteNonQuery();

                        var result = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (result.Equals("-1"))
                        {
                            return "该号码已被锁定！\n请重新刷新号码列表";
                        }
                        else if (result.Equals("1"))
                        {
                            return "成功锁定号码：" + No;
                        }
                        else
                        {
                            return "错误！请重新选择号码";
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

        //解锁号码
        [WebMethod]
        public string UnlockNo(string No, string userId, string sessionId)
        {

            if (!SessionValidater.ValidateSessionId(sessionId, userId))
            {
                //不合法的请求调用
                return "非法登录！";
            }

            //解密
            No = NetSecurity.decrypt(No);
            userId = NetSecurity.decrypt(userId);

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_网点用户_解锁号码";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp1 = new SqlParameter("@user_Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(userId) };
                        cmd.Parameters.Add(sp1);

                        var sp2 = new SqlParameter("@号码", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = No };
                        cmd.Parameters.Add(sp2);

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;

                        cmd.ExecuteNonQuery();

                        var result = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (result.Equals("-1"))
                        {
                            return "您不能解锁别人的号码！";
                        }
                        else if (result.Equals("-2"))
                        {
                            return "该号码没有锁定！";
                        }
                        else if (result.Equals("1"))
                        {
                            return "成功解锁号码：" + No;
                        }
                        else
                        {
                            return "错误！请重新选择号码";
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

        //办理业务
        [WebMethod]
        public string SubmitBusiness(string userId, string userLevel, string businessName, string businessSpec, string sp, string No, string passwd, string content, string sessionId)
        {
            
            if (!SessionValidater.ValidateSessionId(sessionId, userId))
            {
                //不合法的请求调用
                return "非法登录！";
            }

            //解密
            userId = NetSecurity.decrypt(userId);
            userLevel = NetSecurity.decrypt(userLevel);
            businessName = NetSecurity.decrypt(businessName);
            businessSpec = NetSecurity.decrypt(businessSpec);
            sp = NetSecurity.decrypt(sp);
            No = NetSecurity.decrypt(No);
            passwd = NetSecurity.decrypt(passwd);
            content = NetSecurity.decrypt(content);
            
            //验证权限
            if (!AuthorizationHelper.validate(userId).Contains("业务受理"))
            {
                return null;
            } 

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    string SP = "";
                    //提取号码的运营商
                    using (var cmd_fl = new SqlCommand())
                    {
                        string tel3 = No.Substring(0, 3);
                        cmd_fl.CommandText = "select [Category]  from [dbo].[URP_DIC_Content] Where [Name]='" + tel3 + "'";
                        cmd_fl.CommandType = CommandType.Text;
                        cmd_fl.Connection = con;
                        using (SqlDataReader sdr = cmd_fl.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {
                                    SP = sdr["Category"].ToString();
                                    if (sp == "移动" || sp == "联通" || sp == "电信") break;
                                }
                                sdr.Close();
                            }
                        }
                    }

                    if (string.IsNullOrEmpty(SP)) return "失败！输入的号码有误，请重新检查";

                    double returnPoint = -1;
                    //提取返款比例
                    using (var cmd5 = new SqlCommand())
                    {
                        cmd5.CommandText = "select [返款比例]  from [dbo].[返款比例明细] Where [返款类型]='业务返款' and [返款项目]='" + businessName + "' and [地区]='全国' and [用户级别] = '" + userLevel + "'";
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

                    double returnMoney = 1 * returnPoint;

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_网点用户_业务办理";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp1 = new SqlParameter("@提交网点用户Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(userId) };
                        cmd.Parameters.Add(sp1);

                        var sp2 = new SqlParameter("@业务名称", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = businessName };
                        cmd.Parameters.Add(sp2);

                        var sp3 = new SqlParameter("@业务明细", SqlDbType.Text) { Direction = ParameterDirection.Input, Value = businessSpec };
                        cmd.Parameters.Add(sp3);

                        var sp4 = new SqlParameter("@运营商", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = SP };
                        cmd.Parameters.Add(sp4);

                        var sp5 = new SqlParameter("@电话号码", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = No };
                        cmd.Parameters.Add(sp5);

                        var sp6 = new SqlParameter("@密码", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = passwd };
                        cmd.Parameters.Add(sp6);

                        var sp7 = new SqlParameter("@备注", SqlDbType.Text) { Direction = ParameterDirection.Input, Value = content };
                        cmd.Parameters.Add(sp7);

                        var sp8 = new SqlParameter("@返款金额", SqlDbType.Money) { Direction = ParameterDirection.Input, Value = Convert.ToDouble(returnMoney) };
                        cmd.Parameters.Add(sp8);

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;

                        cmd.ExecuteNonQuery();

                        var result = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (result.Equals("1"))
                        {
                            return "办理业务成功！\n办理号码：" + No + ", 办理项目：" + businessName;
                        }
                        else
                        {
                            return "业务办理失败！";
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

        //开卡
        [WebMethod]
        public string SellNo(string userId, string No, string miniCard, string serviceName, string value, string sessionId, string business1, string business2, string business3, string clientType)
        {

            if (!SessionValidater.ValidateSessionId(sessionId, userId))
            {
                //不合法的请求调用
                return "非法登录！";
            }

            //解密
            userId = NetSecurity.decrypt(userId);
            No = NetSecurity.decrypt(No);
            miniCard = NetSecurity.decrypt(miniCard);
            serviceName = NetSecurity.decrypt(serviceName);
            value = NetSecurity.decrypt(value);
            clientType = NetSecurity.decrypt(clientType);

            //验证权限
            if (!AuthorizationHelper.validate(userId).Contains("手机选号"))
            {
                return null;
            }

            if (!string.IsNullOrEmpty(business1)) business1 = NetSecurity.decrypt(business1);
            if (!string.IsNullOrEmpty(business2)) business2 = NetSecurity.decrypt(business2);
            if (!string.IsNullOrEmpty(business3)) business3 = NetSecurity.decrypt(business3);

            //写入数据库用的值
            string passwd = "";
            string serviceNo = "";
            bool isOther = false;

            //临时变量
            double NoPrice = 0; //选号费
            string area = "";   //分区
            string sp = "";
            double areaPrice = 0;
            double pricePercent = 0;

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    //提取号码基本信息：选号费，分区，运营商
                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "select * from [dbo].[库存号码] where [号码]='" + No + "'";
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;
                        using (SqlDataReader sdr = cmd.ExecuteReader()) // cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                if (sdr.Read())
                                {
                                    if (!string.IsNullOrEmpty(sdr["选号费"].ToString()))
                                        NoPrice = Convert.ToDouble(sdr["选号费"].ToString());
                                    area = sdr["分区"].ToString();
                                    sp = sdr["运营商"].ToString();
                                    //验证该号码是否已经被使用
                                    if (sdr["使用状态"].ToString() == "已使用" || !string.IsNullOrEmpty(sdr["使用时间"].ToString())) return "错误！该号码已经被使用";
                                }

                                cmd.Dispose();
                                sdr.Close();
                            }
                        }
                    }

                    if (string.IsNullOrEmpty(area)) return "错误！本号码的区位设置不正确，请联系管理员";
                    if (string.IsNullOrEmpty(sp)) return "错误！本号码的运营商设置不正确，请联系管理员";

                    //提取分区价位
                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "select * from [dbo].[URP_DIC_Content] where [Category]='号码分区' and [Name]='" + area + "' and [附加字段1]='" + sp + "'";
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;
                        using (SqlDataReader sdr = cmd.ExecuteReader()) // cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                if (sdr.Read())
                                {
                                    if (!string.IsNullOrEmpty(sdr["Code"].ToString()))
                                        areaPrice = Convert.ToDouble(sdr["Code"].ToString());
                                }

                                cmd.Dispose();
                                sdr.Close();
                            }
                        }
                    }

                    if (areaPrice == 0) return "错误！本号码的区位价格设置不正确，请联系管理员";

                    //提取选号费百分比
                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "select * from [dbo].[URP_DIC_Content] where [Category]='选号设置' and [Name]='选号扣款比率' and [附加字段1]='" + sp + "'";
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;
                        using (SqlDataReader sdr = cmd.ExecuteReader()) // cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                if (sdr.Read())
                                {
                                    if (!string.IsNullOrEmpty(sdr["Code"].ToString()))
                                        pricePercent = Convert.ToDouble(sdr["Code"].ToString());
                                }

                                cmd.Dispose();
                                sdr.Close();
                            }
                        }
                    }

                    if (pricePercent == 0) return "错误！选号费扣款比例设置不正确，请联系管理员";

                    //提取选号密码
                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "select * from [dbo].[URP_DIC_Content] where [Category]='选号设置' and [Name]='选号密码' and [附加字段1]='" + sp + "'";
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;
                        using (SqlDataReader sdr = cmd.ExecuteReader()) // cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                if (sdr.Read())
                                {
                                    passwd = sdr["Code"].ToString();
                                }

                                cmd.Dispose();
                                sdr.Close();
                            }
                        }
                    }

                    //提取套餐编号
                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "select * from [dbo].[套餐编号_映射表] where [套餐名称]='" + serviceName + "'";
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;
                        using (SqlDataReader sdr = cmd.ExecuteReader()) // cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                if (sdr.Read())
                                {
                                    serviceNo = sdr["套餐编号"].ToString();
                                }

                                cmd.Dispose();
                                sdr.Close();
                            }
                        }
                    }

                    if (clientType == "移动客户端")
                    {
                        if (string.IsNullOrEmpty(serviceNo)) return "错误！套餐编号设置不正确，请联系管理员";
                    }

                    //开卡扣费计算公式, 实际扣款 = 选号费 * 扣款比例 + 区位费
                    double realPayMoney = 0;
                    realPayMoney = pricePercent * NoPrice + areaPrice;

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
                                    double currentMoney = Convert.ToDouble(sdr["账户余额"].ToString());
                                    if (currentMoney < realPayMoney)
                                    {
                                        return "您当前的余额为：" + currentMoney + "，不足以开卡！\n请先为账户充值";
                                    }
                                }
                                sdr.Close();
                            }
                        }
                    }

                    //如果有其他业务，则办理
                    if (!string.IsNullOrEmpty(business1))
                    {
                        using (var cmd = new SqlCommand())
                        {
                            cmd.CommandText = "Function_网点用户_业务办理";
                            cmd.CommandType = CommandType.StoredProcedure;
                            cmd.Connection = con;

                            var sp1 = new SqlParameter("@提交网点用户Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(userId) };
                            cmd.Parameters.Add(sp1);

                            var sp2 = new SqlParameter("@业务名称", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = "开通来电" };
                            cmd.Parameters.Add(sp2);

                            var sp3 = new SqlParameter("@业务明细", SqlDbType.Text) { Direction = ParameterDirection.Input, Value = business1 };
                            cmd.Parameters.Add(sp3);

                            var sp4 = new SqlParameter("@运营商", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = sp };
                            cmd.Parameters.Add(sp4);

                            var sp5 = new SqlParameter("@电话号码", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = No };
                            cmd.Parameters.Add(sp5);

                            var sp6 = new SqlParameter("@密码", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = passwd };
                            cmd.Parameters.Add(sp6);

                            cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;

                            cmd.ExecuteNonQuery();

                            var result = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                            if (result.Equals("1"))
                            {
                                isOther = true;
                            }
                            else
                            {
                                return "办理来电显示业务失败！";
                            }


                            cmd.Dispose();
                        }
                    }

                    //彩铃
                    if (!string.IsNullOrEmpty(business2))
                    {
                        using (var cmd = new SqlCommand())
                        {
                            cmd.CommandText = "Function_网点用户_业务办理";
                            cmd.CommandType = CommandType.StoredProcedure;
                            cmd.Connection = con;

                            var sp1 = new SqlParameter("@提交网点用户Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(userId) };
                            cmd.Parameters.Add(sp1);

                            var sp2 = new SqlParameter("@业务名称", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = "开通彩铃" };
                            cmd.Parameters.Add(sp2);

                            var sp3 = new SqlParameter("@业务明细", SqlDbType.Text) { Direction = ParameterDirection.Input, Value = business2 };
                            cmd.Parameters.Add(sp3);

                            var sp4 = new SqlParameter("@运营商", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = sp };
                            cmd.Parameters.Add(sp4);

                            var sp5 = new SqlParameter("@电话号码", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = No };
                            cmd.Parameters.Add(sp5);

                            var sp6 = new SqlParameter("@密码", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = passwd };
                            cmd.Parameters.Add(sp6);

                            cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;

                            cmd.ExecuteNonQuery();

                            var result = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                            if (result.Equals("1"))
                            {
                                isOther = true;
                            }
                            else
                            {
                                return "办理彩铃业务失败！";
                            }


                            cmd.Dispose();
                        }
                    }

                    //更改姓名
                    if (!string.IsNullOrEmpty(business3))
                    {
                        using (var cmd = new SqlCommand())
                        {
                            cmd.CommandText = "Function_网点用户_业务办理";
                            cmd.CommandType = CommandType.StoredProcedure;
                            cmd.Connection = con;

                            var sp1 = new SqlParameter("@提交网点用户Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(userId) };
                            cmd.Parameters.Add(sp1);

                            var sp2 = new SqlParameter("@业务名称", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = "更改姓名" };
                            cmd.Parameters.Add(sp2);

                            var sp3 = new SqlParameter("@业务明细", SqlDbType.Text) { Direction = ParameterDirection.Input, Value = business3 };
                            cmd.Parameters.Add(sp3);

                            var sp4 = new SqlParameter("@运营商", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = sp };
                            cmd.Parameters.Add(sp4);

                            var sp5 = new SqlParameter("@电话号码", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = No };
                            cmd.Parameters.Add(sp5);

                            var sp6 = new SqlParameter("@密码", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = passwd };
                            cmd.Parameters.Add(sp6);

                            cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;

                            cmd.ExecuteNonQuery();

                            var result = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                            if (result.Equals("1"))
                            {
                                isOther = true;
                            }
                            else
                            {
                                return "办理更改姓名业务失败！";
                            }


                            cmd.Dispose();
                        }
                    }

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_网点用户_售卡";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp1 = new SqlParameter("@销售用户ID", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(userId) };
                        cmd.Parameters.Add(sp1);

                        var sp2 = new SqlParameter("@电话号码", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = No };
                        cmd.Parameters.Add(sp2);

                        var sp3 = new SqlParameter("@小卡号码", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = miniCard };
                        cmd.Parameters.Add(sp3);

                        var sp4 = new SqlParameter("@开卡服务密码", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = passwd };
                        cmd.Parameters.Add(sp4);

                        var sp5 = new SqlParameter("@套餐名称", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = serviceName };
                        cmd.Parameters.Add(sp5);

                        var sp6 = new SqlParameter("@套餐编号", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = serviceNo };
                        cmd.Parameters.Add(sp6);

                        var sp7 = new SqlParameter("@开卡面值", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = value };
                        cmd.Parameters.Add(sp7);

                        var sp8 = new SqlParameter("@其他业务", SqlDbType.Bit) { Direction = ParameterDirection.Input, Value = isOther };
                        cmd.Parameters.Add(sp8);

                        var sp9 = new SqlParameter("@扣款金额", SqlDbType.Money) { Direction = ParameterDirection.Input, Value = realPayMoney };
                        cmd.Parameters.Add(sp9);

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;

                        cmd.ExecuteNonQuery();

                        var result = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (result.Equals("1"))
                        {
                            return "号码：" + No + "开卡成功！";
                        }
                        else
                        {
                            //撤销附带的业务
                            using (var cmd1 = new SqlCommand())
                            {
                                cmd1.CommandText = "delete from [dbo].[业务办理记录] where [电话号码]='" + No + "' and [提交网点用户Id]='" + userId + "' and [办理状态]='正在处理'";
                                cmd1.CommandType = CommandType.Text;
                                cmd1.Connection = con;
                                cmd1.ExecuteNonQuery();
                            }
                            return "号码：" + No + "开卡失败！";
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

        //卡类销售
        [WebMethod]
        public string SellOhterCard(string userId, string cardType, string cardName, string sessionId)
        {

            if (!SessionValidater.ValidateSessionId(sessionId, userId))
            {
                //不合法的请求调用
                return "非法登录！";
            }

            //解密
            userId = NetSecurity.decrypt(userId);
            cardType = NetSecurity.decrypt(cardType);
            cardName = NetSecurity.decrypt(cardName);

            //验证权限
            if (!AuthorizationHelper.validate(userId).Contains("卡类销售"))
            {
                return null;
            }


            //临时变量
            bool isGetCardInfo = false; //是否有库存
            double payPrice = 0; //扣款
            string cardSeq = "";
            string cardPsw = "";

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    //提取卡类扣款信息
                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "select * from [dbo].[URP_DIC_Content] where [Category]='卡类管理' and [附加字段1] like '%" + cardType + "%' and [Name] like '%" + cardName + "%'";
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;
                        using (SqlDataReader sdr = cmd.ExecuteReader()) // cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                if (sdr.Read())
                                {
                                    if (!string.IsNullOrEmpty(sdr["Code"].ToString()))
                                        payPrice = Convert.ToDouble(sdr["Code"].ToString());
                                }

                                cmd.Dispose();
                                sdr.Close();
                            }
                        }
                    }

                    if (payPrice == 0) return "错误！本卡的价格设置有误，请联系管理员";

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
                                    double currentMoney = Convert.ToDouble(sdr["账户余额"].ToString());
                                    if (currentMoney < payPrice)
                                    {
                                        return "您当前的余额为：" + currentMoney + "，不购买该卡类！\n请先为账户充值";
                                    }
                                }
                                sdr.Close();
                            }
                        }
                    }

                    //判断是否有库存
                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_网点用户_使用卡类";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp1 = new SqlParameter("@网点用户Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(userId) };
                        cmd.Parameters.Add(sp1);

                        var sp2 = new SqlParameter("@卡类型", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = cardType };
                        cmd.Parameters.Add(sp2);

                        var sp3 = new SqlParameter("@卡名称", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = cardName };
                        cmd.Parameters.Add(sp3);

                        var sp4 = new SqlParameter("@序列号", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Output };
                        cmd.Parameters.Add(sp4);

                        var sp5 = new SqlParameter("@卡密", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Output };
                        cmd.Parameters.Add(sp5);

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;

                        cmd.ExecuteNonQuery();

                        var result = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (result.Equals("1"))
                        {
                            isGetCardInfo = true;
                            cardSeq = cmd.Parameters["@序列号"].Value.ToString();
                            cardPsw = cmd.Parameters["@卡密"].Value.ToString();
                        }
                        else
                        {
                            isGetCardInfo = false;
                        }
                        cmd.Dispose();
                    }



                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_网点用户_卡类销售";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp1 = new SqlParameter("@网点用户Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(userId) };
                        cmd.Parameters.Add(sp1);

                        var sp2 = new SqlParameter("@卡类型", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = cardType };
                        cmd.Parameters.Add(sp2);

                        var sp3 = new SqlParameter("@卡名称", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = cardName };
                        cmd.Parameters.Add(sp3);

                        if (isGetCardInfo)
                        {
                            var sp4 = new SqlParameter("@序列号", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = cardSeq };
                            cmd.Parameters.Add(sp4);

                            var sp5 = new SqlParameter("@卡密", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = cardPsw };
                            cmd.Parameters.Add(sp5);

                            var sp6 = new SqlParameter("@状态", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = "处理成功" };
                            cmd.Parameters.Add(sp6);
                        }
                        else
                        {
                            var sp6 = new SqlParameter("@状态", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = "正在处理" };
                            cmd.Parameters.Add(sp6);
                        }

                        var sp9 = new SqlParameter("@扣款金额", SqlDbType.Money) { Direction = ParameterDirection.Input, Value = payPrice };
                        cmd.Parameters.Add(sp9);

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;

                        cmd.ExecuteNonQuery();

                        var result = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (result.Equals("1"))
                        {
                            string respStr = "";
                            respStr = "购买[" + cardType + "] " + cardName + " 成功！\n";
                            if (isGetCardInfo)
                            {
                                respStr += "序列号：" + cardSeq + "\n";
                                respStr += "卡密：" + cardPsw;
                                return respStr;

                            }
                            else
                            {
                                respStr += "请等待处理...";
                                return respStr;
                            }
                        }
                        else
                        {
                            return "购买[" + cardType + "] " + cardName + " 失败！\n";
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

        #region 客户端和管理端共用

        //查询库存小卡
        [WebMethod]
        public List<MiniCardItem> GetMiniCardRecord(int top, string condition, string sessionId)
        {
            var list = new List<MiniCardItem>();

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
            var selectCommand = string.Format("SELECT {0} * FROM [MobileManage].[dbo].[库存小卡汇总信息]  {1}", topMessage, selectCondition);//组合选择语句

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
                                    var miniCardItem = new MiniCardItem();
                                    if (!string.IsNullOrEmpty(sdr["Id"].ToString()))
                                        miniCardItem.id = new Guid(sdr["Id"].ToString());
                                    miniCardItem.cardNo = sdr["小卡号码"].ToString();
                                    miniCardItem.noSection = sdr["号段"].ToString();
                                    miniCardItem.SP = sdr["运营商"].ToString();
                                    miniCardItem.state = sdr["使用状态"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["领卡人Id"].ToString()))
                                        miniCardItem.getWorkerId = new Guid(sdr["领卡人Id"].ToString());
                                    miniCardItem.getWorkerName = sdr["领卡人登录名"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["业务员Id"].ToString()))
                                        miniCardItem.workerId = new Guid(sdr["业务员Id"].ToString());
                                    miniCardItem.workerName = sdr["业务员登录名"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["网点用户Id"].ToString()))
                                        miniCardItem.userId = new Guid(sdr["网点用户Id"].ToString());
                                    miniCardItem.userName = sdr["网点用户登录名"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["领入时间"].ToString()))
                                        miniCardItem.getDate = Convert.ToDateTime(sdr["领入时间"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["分配时间"].ToString()))
                                        miniCardItem.assignDate = Convert.ToDateTime(sdr["分配时间"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["销售时间"].ToString()))
                                        miniCardItem.sellDate = Convert.ToDateTime(sdr["销售时间"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["使用时间"].ToString()))
                                        miniCardItem.usedDate = Convert.ToDateTime(sdr["使用时间"].ToString());
                                    list.Add(miniCardItem);
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
        //根据条件获取符合条件小卡扣款记录
        [WebMethod]
        public List<PayMiniCardItem> GetPayMiniCardByCondition(int top, string condition, string sessionId)
        {
            var list = new List<PayMiniCardItem>();
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
            var selectCommand = string.Format("SELECT {0} * FROM [MobileManage].[dbo].[小卡扣款信息] {1} ", topMessage, selectCondition);//组合选择语句
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
                                    var payMiniCardItem = new PayMiniCardItem();
                                    if (!string.IsNullOrEmpty(sdr["Id"].ToString()))
                                        payMiniCardItem.Id = new Guid(sdr["Id"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["网点用户Id"].ToString()))
                                        payMiniCardItem.userId = new Guid(sdr["网点用户Id"].ToString());
                                    payMiniCardItem.userName = sdr["网点用户登录名"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["申请时间"].ToString()))
                                        payMiniCardItem.addDateTime = Convert.ToDateTime(sdr["申请时间"].ToString());
                                    payMiniCardItem.managerId = new Guid(sdr["业务员Id"].ToString());
                                    payMiniCardItem.managerName = sdr["业务员登录名"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["扣款金额"].ToString()))
                                        payMiniCardItem.money = Convert.ToDouble(sdr["扣款金额"].ToString());
                                    payMiniCardItem.content = sdr["备注"].ToString();
                                    payMiniCardItem.state = sdr["状态"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["员工Id"].ToString()))
                                        payMiniCardItem.workId = new Guid(sdr["员工Id"].ToString());
                                    payMiniCardItem.work_name = sdr["员工登录名"].ToString();
                                    payMiniCardItem.workType = sdr["员工类型"].ToString();
                                    payMiniCardItem.clientType = sdr["客户端类型"].ToString();
                                    payMiniCardItem.SP = sdr["运营商"].ToString();
                                    payMiniCardItem.cardNum = (int)sdr["张数"];
                                    if (!string.IsNullOrEmpty(sdr["处理前余额"].ToString()))
                                        payMiniCardItem.moneyBefore = Convert.ToDouble(sdr["处理前余额"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["处理后余额"].ToString()))
                                        payMiniCardItem.moneyAfter = Convert.ToDouble(sdr["处理后余额"].ToString());
                                    list.Add(payMiniCardItem);
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
        //根据条件获取符合条件小卡扣款记录或者小卡扣款历史记录
        public List<PayMiniCardItem> GetPayMiniCardHistoryByCondition(string condition, string sessionId)
        {
            var list = new List<PayMiniCardItem>();
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
            var selectCommand = string.Format("select * from 小卡扣款汇总信息 {0} ", selectCondition);//组合选择语句
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
                                    var payMiniCardItem = new PayMiniCardItem();
                                    if (!string.IsNullOrEmpty(sdr["Id"].ToString()))
                                        payMiniCardItem.Id = new Guid(sdr["Id"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["网点用户Id"].ToString()))
                                        payMiniCardItem.userId = new Guid(sdr["网点用户Id"].ToString());
                                    payMiniCardItem.userName = sdr["网点用户登录名"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["申请时间"].ToString()))
                                        payMiniCardItem.addDateTime = Convert.ToDateTime(sdr["申请时间"].ToString());
                                    payMiniCardItem.managerId = new Guid(sdr["业务员Id"].ToString());
                                    payMiniCardItem.managerName = sdr["业务员登录名"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["扣款金额"].ToString()))
                                        payMiniCardItem.money = Convert.ToDouble(sdr["扣款金额"].ToString());
                                    payMiniCardItem.content = sdr["备注"].ToString();
                                    payMiniCardItem.state = sdr["状态"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["员工Id"].ToString()))
                                        payMiniCardItem.workId = new Guid(sdr["员工Id"].ToString());
                                    payMiniCardItem.work_name = sdr["员工登录名"].ToString();
                                    payMiniCardItem.workType = sdr["员工类型"].ToString();
                                    payMiniCardItem.clientType = sdr["客户端类型"].ToString();
                                    payMiniCardItem.SP = sdr["运营商"].ToString();
                                    payMiniCardItem.cardNum = (int)sdr["张数"];
                                    if (!string.IsNullOrEmpty(sdr["处理前余额"].ToString()))
                                        payMiniCardItem.moneyBefore = Convert.ToDouble(sdr["处理前余额"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["处理后余额"].ToString()))
                                        payMiniCardItem.moneyAfter = Convert.ToDouble(sdr["处理后余额"].ToString());
                                    list.Add(payMiniCardItem);
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
        //查询符合条件的库存号码
        public List<PhoneNoItem> GetPhoneNoItemByCondition(string condition, string sessionId)
        {
            var list = new List<PhoneNoItem>();
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
            var selectCommand = string.Format("select * from 库存号码信息 {0} ", selectCondition);//组合选择语句
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
                                    var phoneNoItem = new PhoneNoItem();
                                    if (!string.IsNullOrEmpty(sdr["Id"].ToString()))
                                        phoneNoItem.id = new Guid(sdr["Id"].ToString());

                                    phoneNoItem.No = sdr["号码"].ToString();
                                    phoneNoItem.NoSection = sdr["号段"].ToString();
                                    phoneNoItem.inNetPolicy = sdr["入网政策"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["选号费"].ToString()))
                                        phoneNoItem.NoPrice = Convert.ToDouble(sdr["选号费"].ToString());
                                    phoneNoItem.area = sdr["分区"].ToString();
                                    phoneNoItem.weight = Convert.ToInt32(sdr["权值"].ToString());
                                    phoneNoItem.state = sdr["使用状态"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["锁定时间"].ToString()))
                                        phoneNoItem.lockDateime = Convert.ToDateTime(sdr["锁定时间"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["领号人Id"].ToString()))
                                        phoneNoItem.getterId = new Guid(sdr["领号人Id"].ToString());
                                    phoneNoItem.getterName = sdr["领号人姓名"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["领入时间"].ToString()))
                                        phoneNoItem.getDateime = Convert.ToDateTime(sdr["领入时间"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["分配人Id"].ToString()))
                                        phoneNoItem.assignerId = new Guid(sdr["分配人Id"].ToString());
                                    phoneNoItem.assignerName = sdr["分配人姓名"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["分配时间"].ToString()))
                                        phoneNoItem.assignDateime = Convert.ToDateTime(sdr["分配时间"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["网点用户Id"].ToString()))
                                        phoneNoItem.userId = new Guid(sdr["网点用户Id"].ToString());
                                    phoneNoItem.userName = sdr["网点用户名"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["使用时间"].ToString()))
                                        phoneNoItem.usedDateime = Convert.ToDateTime(sdr["使用时间"].ToString());
                                    phoneNoItem.sp = sdr["运营商"].ToString();


                                    list.Add(phoneNoItem);
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
        //查询符合条件的库存号码以及库存号码历史记录
        public List<PhoneNoItem> GetPhoneNoItemAndHistoryByCondition(string condition, string sessionId)
        {
            var list = new List<PhoneNoItem>();
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
            var selectCommand = string.Format("select * from 库存号码汇总信息 {0} ", selectCondition);//组合选择语句
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
                                    var phoneNoItem = new PhoneNoItem();
                                    if (!string.IsNullOrEmpty(sdr["Id"].ToString()))
                                        phoneNoItem.id = new Guid(sdr["Id"].ToString());

                                    phoneNoItem.No = sdr["号码"].ToString();
                                    phoneNoItem.NoSection = sdr["号段"].ToString();
                                    phoneNoItem.inNetPolicy = sdr["入网政策"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["选号费"].ToString()))
                                        phoneNoItem.NoPrice = Convert.ToDouble(sdr["选号费"].ToString());
                                    phoneNoItem.area = sdr["分区"].ToString();
                                    phoneNoItem.weight = Convert.ToInt32(sdr["权值"].ToString());
                                    phoneNoItem.state = sdr["使用状态"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["锁定时间"].ToString()))
                                        phoneNoItem.lockDateime = Convert.ToDateTime(sdr["锁定时间"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["领号人Id"].ToString()))
                                        phoneNoItem.getterId = new Guid(sdr["领号人Id"].ToString());
                                    phoneNoItem.getterName = sdr["领号人姓名"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["领入时间"].ToString()))
                                        phoneNoItem.getDateime = Convert.ToDateTime(sdr["领入时间"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["分配人Id"].ToString()))
                                        phoneNoItem.assignerId = new Guid(sdr["分配人Id"].ToString());
                                    phoneNoItem.assignerName = sdr["分配人姓名"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["分配时间"].ToString()))
                                        phoneNoItem.assignDateime = Convert.ToDateTime(sdr["分配时间"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["网点用户Id"].ToString()))
                                        phoneNoItem.userId = new Guid(sdr["网点用户Id"].ToString());
                                    phoneNoItem.userName = sdr["网点用户名"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["使用时间"].ToString()))
                                        phoneNoItem.usedDateime = Convert.ToDateTime(sdr["使用时间"].ToString());
                                    phoneNoItem.sp = sdr["运营商"].ToString();


                                    list.Add(phoneNoItem);
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

        //查询套餐服务
        [WebMethod]
        public List<CardService> GetCardService(int top, string condition, string sessionId)
        {
            var list = new List<CardService>();


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
            var selectCommand = string.Format("SELECT {0} * FROM [MobileManage].[dbo].[套餐类型]  {1}", topMessage, selectCondition);//组合选择语句

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
                                    var cardService = new CardService();
                                    if (!string.IsNullOrEmpty(sdr["Id"].ToString()))
                                        cardService.Id = new Guid(sdr["Id"].ToString());
                                    cardService.SP = sdr["运营商"].ToString();
                                    cardService.serviceName = sdr["套餐名称"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["是否常用"].ToString()))
                                        cardService.isFreq = Convert.ToBoolean(sdr["是否常用"].ToString());
                                    cardService.serviceSpec = sdr["套餐说明"].ToString();
                                    list.Add(cardService);
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

        //根据条件获取符合条件售卡记录
        [WebMethod]
        public List<SellCardItem> GetSellCardRecordByCondition(int top, string condition, string sessionId)
        {

            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return null;
            }

            //解密数据
            condition = NetSecurity.decrypt(condition);

            return MobileWebService.Service.BusinessStub.GetSellCardRecordByCondition(top, condition, "[售卡信息视图]");

        }
        [WebMethod]
        //根据条件获取符合条件售卡记录记录或者售卡记录历史记录
        public List<SellCardItem> GetSellCardRecordHistoryByCondition(int top, string condition, string sessionId)
        {

            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return null;
            }

            //解密数据
            condition = NetSecurity.decrypt(condition);

            return MobileWebService.Service.BusinessStub.GetSellCardRecordByCondition(top, condition, "[售卡信息汇总]");
        }

        //根据条件获取符合条件业务办理记录
        [WebMethod]
        public List<BusinessItem> GetBusinessRecordByCondition(int top, string condition, string sessionId)
        {

            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return null;
            }

            //解密数据
            condition = NetSecurity.decrypt(condition);

            return MobileWebService.Service.BusinessStub.GetBusinessRecordByCondition(top, condition, "[业务办理信息]");

        }
        [WebMethod]
        //根据条件获取符合条件业务办理记录或者业务办理历史记录
        public List<BusinessItem> GettBusinessRecordHistoryByCondition(int top, string condition, string sessionId)
        {

            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return null;
            }

            //解密数据
            condition = NetSecurity.decrypt(condition);

            return MobileWebService.Service.BusinessStub.GetBusinessRecordByCondition(top, condition, "[业务办理汇总信息]");
        }

        //根据条件获取符合条件卡类销售记录
        [WebMethod]
        public List<SellOtherCardItem> GetSellOtherCardRecordByCondition(int top, string condition, string sessionId)
        {

            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return null;
            }

            //解密数据
            condition = NetSecurity.decrypt(condition);

            return MobileWebService.Service.BusinessStub.GetSellOtherRecordByCondition(top, condition, "[卡类销售信息]");

        }
        [WebMethod]
        //根据条件获取符合条件卡类销售记录或者卡类销售历史记录
        public List<SellOtherCardItem> GettSellOtherCardRecordHistoryByCondition(int top, string condition, string sessionId)
        {

            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return null;
            }

            //解密数据
            condition = NetSecurity.decrypt(condition);

            return MobileWebService.Service.BusinessStub.GetSellOtherRecordByCondition(top, condition, "[卡类销售汇总信息]");
        }

        //获取卡类销售的卡类名称列表
        [WebMethod]
        public List<OtherCardItem> GetOtherCardList(string condition, string sessionId)
        {
            var list = new List<OtherCardItem>();

            
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return list;
            }

            //解密数据
            condition = NetSecurity.decrypt(condition);

            string selectCondition = " where [Category]='卡类管理' ";

            if (!string.IsNullOrEmpty(condition))
            {
                selectCondition += " and " + condition;
            }
            var selectCommand = string.Format("SELECT * FROM [MobileManage].[dbo].[URP_DIC_Content] {0}", selectCondition);//组合选择语句

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
                                    var OtherCardItem = new OtherCardItem();
                                    OtherCardItem.cardName = sdr["Name"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["Code"].ToString()))
                                        OtherCardItem.cardPrice = Convert.ToDouble(sdr["Code"].ToString());
                                    OtherCardItem.cardType = sdr["附加字段1"].ToString();
                                    list.Add(OtherCardItem);
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
        //查询符合条件的库存卡类
        public List<StockCardItem> GetStockCardItemByCondition(string condition, string sessionId)
        {
            var list = new List<StockCardItem>();
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
            var selectCommand = string.Format("select * from 库存卡类信息 {0} ", selectCondition);//组合选择语句
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
                                    var stockCardItem = new StockCardItem();
                                    if (!string.IsNullOrEmpty(sdr["Id"].ToString()))
                                        stockCardItem.Id = new Guid(sdr["Id"].ToString());

                                    stockCardItem.cardType = sdr["卡类型"].ToString();
                                    stockCardItem.cardName = sdr["卡名称"].ToString();
                                    stockCardItem.cardSeq = sdr["序列号"].ToString();
                                    stockCardItem.cardPsw = sdr["卡密"].ToString();

                                    if (!string.IsNullOrEmpty(sdr["领入时间"].ToString()))
                                        stockCardItem.getDate = Convert.ToDateTime(sdr["领入时间"].ToString());

                                    if (!string.IsNullOrEmpty(sdr["领入者Id"].ToString()))
                                        stockCardItem.getterId = new Guid(sdr["领入者Id"].ToString());
                                    stockCardItem.getterName = sdr["员工登录名"].ToString();


                                    if (!string.IsNullOrEmpty(sdr["销售时间"].ToString()))
                                        stockCardItem.sellDate = Convert.ToDateTime(sdr["销售时间"].ToString());

                                    if (!string.IsNullOrEmpty(sdr["网点用户Id"].ToString()))
                                        stockCardItem.userId = new Guid(sdr["网点用户Id"].ToString());
                                    stockCardItem.userName = sdr["网点用户登录名"].ToString();


                                    stockCardItem.state = sdr["状态"].ToString();



                                    list.Add(stockCardItem);
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
        //查询符合条件的库存卡类以及库存卡类历史记录
        public List<StockCardItem> GetStockCardItemAndHistoryByCondition(string condition, string sessionId)
        {
            var list = new List<StockCardItem>();
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
            var selectCommand = string.Format("select * from 库存卡类汇总信息 {0} ", selectCondition);//组合选择语句
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
                                    var stockCardItem = new StockCardItem();
                                    if (!string.IsNullOrEmpty(sdr["Id"].ToString()))
                                        stockCardItem.Id = new Guid(sdr["Id"].ToString());

                                    stockCardItem.cardType = sdr["卡类型"].ToString();
                                    stockCardItem.cardName = sdr["卡名称"].ToString();
                                    stockCardItem.cardSeq = sdr["序列号"].ToString();
                                    stockCardItem.cardPsw = sdr["卡密"].ToString();

                                    if (!string.IsNullOrEmpty(sdr["领入时间"].ToString()))
                                        stockCardItem.getDate = Convert.ToDateTime(sdr["领入时间"].ToString());

                                    if (!string.IsNullOrEmpty(sdr["领入者Id"].ToString()))
                                        stockCardItem.getterId = new Guid(sdr["领入者Id"].ToString());
                                    stockCardItem.getterName = sdr["员工登录名"].ToString();


                                    if (!string.IsNullOrEmpty(sdr["销售时间"].ToString()))
                                        stockCardItem.sellDate = Convert.ToDateTime(sdr["销售时间"].ToString());

                                    if (!string.IsNullOrEmpty(sdr["网点用户Id"].ToString()))
                                        stockCardItem.userId = new Guid(sdr["网点用户Id"].ToString());
                                    stockCardItem.userName = sdr["网点用户登录名"].ToString();


                                    stockCardItem.state = sdr["状态"].ToString();



                                    list.Add(stockCardItem);
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
        #region 管理端端专用
        [WebMethod]
        //锁定小卡扣款信息
        public bool LocktMiniCardPayment(string paymentId, string workerId, string workerName, string sessionId)
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
                        cmd.CommandText = "Function_服务端_更改小卡扣款状态为锁定_员工";
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
        //锁定业务办理信息
        public bool LocktBussinessPayment(string paymentId, string workerId, string workerName, string sessionId)
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
                        cmd.CommandText = "Function_服务端_更改业务办理状态为锁定_员工";
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
        //锁定售卡信息
        public bool LockSellCardPayment(string paymentId, string workerId, string workerName, string sessionId)
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
                        cmd.CommandText = "Function_服务端_更改售卡状态为锁定_员工";
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
        //锁定卡类销售信息
        public bool LockCardTypePayment(string paymentId, string workerId, string workerName, string sessionId)
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
                        cmd.CommandText = "Function_服务端_更改卡类销售状态为锁定_员工";
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
        //小卡扣款处理
        public string DealPayMiniCard(string miniCardId, string userId, int opNum, string wordId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId, wordId))
            {
                //不合法的请求调用
                return "非法登录";
            }
            //解密
            miniCardId = NetSecurity.decrypt(miniCardId);
            userId = NetSecurity.decrypt(userId);
            wordId = NetSecurity.decrypt(wordId);
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();
                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_小卡扣款";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;
                        cmd.Parameters.Clear();


                        var sp0 = new SqlParameter("@小卡扣款Id", SqlDbType.UniqueIdentifier);
                        sp0.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp0);
                        sp0.Value = string.IsNullOrEmpty(miniCardId) ? (object)DBNull.Value : new Guid(miniCardId);

                        var sp1 = new SqlParameter("@网点用户Id", SqlDbType.UniqueIdentifier);
                        sp1.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp1);
                        sp1.Value = string.IsNullOrEmpty(userId) ? (object)DBNull.Value : new Guid(userId);

                        var sp2 = new SqlParameter("@操作Num", SqlDbType.Int);
                        sp2.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp2);
                        sp2.Value = opNum;

                        var sp3 = new SqlParameter("@操作者Id", SqlDbType.UniqueIdentifier);
                        sp3.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp3);
                        sp3.Value = string.IsNullOrEmpty(wordId) ? (object)DBNull.Value : new Guid(wordId);

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("1"))
                        {
                            cmd.Dispose();
                            return (opNum == 1 ? "'处理成功'," : "'处理失败',") + "操作成功！";
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
            return (opNum == 1 ? "'处理成功'," : "'处理失败',") + "操作失败";
        }

        [WebMethod]
        //业务办理处理
        public string DealBusiness(string businessId, string userId, int opNum,string replay ,string workId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId, workId))
            {
                //不合法的请求调用
                return "非法登录";
            }
            //解密
            businessId = NetSecurity.decrypt(businessId);
            userId = NetSecurity.decrypt(userId);
            replay = NetSecurity.decrypt(replay);
            workId = NetSecurity.decrypt(workId);
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();
                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_业务办理";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;
                        cmd.Parameters.Clear();


                        var sp0 = new SqlParameter("@业务办理Id", SqlDbType.UniqueIdentifier);
                        sp0.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp0);
                        sp0.Value = string.IsNullOrEmpty(businessId) ? (object)DBNull.Value : new Guid(businessId);

                        var sp1 = new SqlParameter("@网点用户Id", SqlDbType.UniqueIdentifier);
                        sp1.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp1);
                        sp1.Value = string.IsNullOrEmpty(userId) ? (object)DBNull.Value : new Guid(userId);

                        var sp2 = new SqlParameter("@操作Num", SqlDbType.Int);
                        sp2.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp2);
                        sp2.Value = opNum;

                        var sp3 = new SqlParameter("@操作者Id", SqlDbType.UniqueIdentifier);
                        sp3.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp3);
                        sp3.Value = string.IsNullOrEmpty(workId) ? (object)DBNull.Value : new Guid(workId);

                        var sp4 = new SqlParameter("@回复", SqlDbType.Text);
                        sp4.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp4);
                        sp4.Value = replay;

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("1"))
                        {
                            cmd.Dispose();
                            return (opNum == 1 ? "'处理成功'," : "'处理失败',") + "操作成功！";
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
            return (opNum == 1 ? "'处理成功'," : "'处理失败',") + "操作失败";
        }

        [WebMethod]
        //售卡处理
        public string DealSellCard(string sellCardId, string userId, int opNum, string workId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId, workId))
            {
                //不合法的请求调用
                return "非法登录";
            }
            //解密
            sellCardId = NetSecurity.decrypt(sellCardId);
            userId = NetSecurity.decrypt(userId);
            workId = NetSecurity.decrypt(workId);
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();
                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_售卡";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;
                        cmd.Parameters.Clear();


                        var sp0 = new SqlParameter("@售卡Id", SqlDbType.UniqueIdentifier);
                        sp0.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp0);
                        sp0.Value = string.IsNullOrEmpty(sellCardId) ? (object)DBNull.Value : new Guid(sellCardId);

                        var sp1 = new SqlParameter("@网点用户Id", SqlDbType.UniqueIdentifier);
                        sp1.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp1);
                        sp1.Value = string.IsNullOrEmpty(userId) ? (object)DBNull.Value : new Guid(userId);

                        var sp2 = new SqlParameter("@操作Num", SqlDbType.Int);
                        sp2.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp2);
                        sp2.Value = opNum;

                        var sp3 = new SqlParameter("@操作者Id", SqlDbType.UniqueIdentifier);
                        sp3.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp3);
                        sp3.Value = string.IsNullOrEmpty(workId) ? (object)DBNull.Value : new Guid(workId);

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("1"))
                        {
                            cmd.Dispose();
                            return (opNum == 1 ? "'处理成功'," : "'处理失败',") + "操作成功！";
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
            return (opNum == 1 ? "'处理成功'," : "'处理失败',") + "操作失败";
        }

        [WebMethod]
        //卡类销售处理
        public string DealSellOtherCard(string sellOtherCardId, string userId,string cardSeq,string cardPsw, int opNum, string workId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId, workId))
            {
                //不合法的请求调用
                return "非法登录";
            }
            //解密
            sellOtherCardId = NetSecurity.decrypt(sellOtherCardId);
            userId = NetSecurity.decrypt(userId);
            workId = NetSecurity.decrypt(workId);
            cardSeq = NetSecurity.decrypt(cardSeq);
            cardPsw = NetSecurity.decrypt(cardPsw);
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();
                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_卡类销售";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;
                        cmd.Parameters.Clear();


                        var sp0 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier);
                        sp0.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp0);
                        sp0.Value = string.IsNullOrEmpty(sellOtherCardId) ? (object)DBNull.Value : new Guid(sellOtherCardId);

                        var sp1 = new SqlParameter("@网点用户Id", SqlDbType.UniqueIdentifier);
                        sp1.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp1);
                        sp1.Value = string.IsNullOrEmpty(userId) ? (object)DBNull.Value : new Guid(userId);


                        var sp4 = new SqlParameter("@序列号", SqlDbType.NVarChar,50);
                        sp4.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp4);
                        sp4.Value = cardSeq;

                        var sp5 = new SqlParameter("@卡密", SqlDbType.NVarChar, 50);
                        sp5.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp5);
                        sp5.Value = cardPsw;

                        var sp2 = new SqlParameter("@操作Num", SqlDbType.Int);
                        sp2.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp2);
                        sp2.Value = opNum;

                        var sp3 = new SqlParameter("@操作者Id", SqlDbType.UniqueIdentifier);
                        sp3.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp3);
                        sp3.Value = string.IsNullOrEmpty(workId) ? (object)DBNull.Value : new Guid(workId);

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("1"))
                        {
                            cmd.Dispose();
                            return (opNum == 1 ? "'处理成功'," : "'处理失败',") + "操作成功！";
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
            return (opNum == 1 ? "'处理成功'," : "'处理失败',") + "操作失败";
        }

        [WebMethod]
        //导入库存小卡
        public string ImportMiniCard(string miniCardCommon, int miniCardPre, int miniCardSuf, string haoDuan, string sp, string wordId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId, wordId))
            {
                //不合法的请求调用
                return "非法登录";
            }
            //解密
            miniCardCommon = NetSecurity.decrypt(miniCardCommon);
            haoDuan = NetSecurity.decrypt(haoDuan);
            sp = NetSecurity.decrypt(sp);
            wordId = NetSecurity.decrypt(wordId);
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();
                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_导入库存小卡";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;
                        cmd.Parameters.Clear();


                        var sp0 = new SqlParameter("@小卡号码共同前缀", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = miniCardCommon };
                        cmd.Parameters.Add(sp0);


                        var sp1 = new SqlParameter("@小卡号码后缀起始", SqlDbType.Int) { Direction = ParameterDirection.Input, Value = miniCardPre };
                        cmd.Parameters.Add(sp1);


                        var sp2 = new SqlParameter("@小卡号码后缀截止", SqlDbType.Int) { Direction = ParameterDirection.Input, Value = miniCardSuf };
                        cmd.Parameters.Add(sp2);

                        var sp3 = new SqlParameter("@号段", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = haoDuan };
                        cmd.Parameters.Add(sp3);

                        var sp4 = new SqlParameter("@运营商", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = sp };
                        cmd.Parameters.Add(sp4);


                        var sp5 = new SqlParameter("@操作者Id", SqlDbType.UniqueIdentifier)
                                      {
                                          Direction = ParameterDirection.Input,
                                          Value =
                                              string.IsNullOrEmpty(wordId) ? (object)DBNull.Value : new Guid(wordId)
                                      };
                        cmd.Parameters.Add(sp5);

                        var sp6 = new SqlParameter("@出错小卡号码", SqlDbType.NVarChar, 100)
                                      {
                                          Direction = ParameterDirection.Output
                                      };
                        cmd.Parameters.Add(sp6);


                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("1"))
                        {
                            cmd.Dispose();
                            return "库存小卡导入成功!";
                        }
                        else
                        {
                            cmd.Dispose();
                            return "小卡：" + sp6.Value.ToString() + "已存在，请检查或与管理员联系!";
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

        [WebMethod]
        //分配库存小卡
        public string AssignmentMiniCard(string miniCardCommon, int miniCardPre, int miniCardSuf, string businessId, string sp, string wordId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId, wordId))
            {
                //不合法的请求调用
                return "非法登录";
            }
            //解密
            miniCardCommon = NetSecurity.decrypt(miniCardCommon);
            businessId = NetSecurity.decrypt(businessId);
            sp = NetSecurity.decrypt(sp);
            wordId = NetSecurity.decrypt(wordId);
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();
                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_分配库存小卡";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;
                        cmd.Parameters.Clear();


                        var sp0 = new SqlParameter("@小卡号码共同前缀", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = miniCardCommon };
                        cmd.Parameters.Add(sp0);


                        var sp1 = new SqlParameter("@小卡号码后缀起始", SqlDbType.Int) { Direction = ParameterDirection.Input, Value = miniCardPre };
                        cmd.Parameters.Add(sp1);


                        var sp2 = new SqlParameter("@小卡号码后缀截止", SqlDbType.Int) { Direction = ParameterDirection.Input, Value = miniCardSuf };
                        cmd.Parameters.Add(sp2);

                        var sp9 = new SqlParameter("@运营商", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = sp };
                        cmd.Parameters.Add(sp9);

                        var sp4 = new SqlParameter("@业务员Id", SqlDbType.UniqueIdentifier)
                        {
                            Direction = ParameterDirection.Input,
                            Value =
                                string.IsNullOrEmpty(wordId) ? (object)DBNull.Value : new Guid(businessId)
                        };
                        cmd.Parameters.Add(sp4);


                        var sp5 = new SqlParameter("@操作者Id", SqlDbType.UniqueIdentifier)
                        {
                            Direction = ParameterDirection.Input,
                            Value =
                                string.IsNullOrEmpty(wordId) ? (object)DBNull.Value : new Guid(wordId)
                        };
                        cmd.Parameters.Add(sp5);

                        var sp6 = new SqlParameter("@出错小卡号码", SqlDbType.NVarChar, 100)
                        {
                            Direction = ParameterDirection.Output
                        };
                        cmd.Parameters.Add(sp6);

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("1"))
                        {
                            cmd.Dispose();
                            return "库存小卡分配成功!";
                        }
                        else
                        {
                            cmd.Dispose();
                            return "小卡：" + sp6.Value.ToString() + "不存在，请检查或与管理员联系!";
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

        [WebMethod]
        //分配库存小卡给用户
        public string AssignmentMiniCardToUser(string miniCardCommon, int miniCardPre, int miniCardSuf, string userId, string sp, string wordId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId, wordId))
            {
                //不合法的请求调用
                return "非法登录";
            }
            //解密
            miniCardCommon = NetSecurity.decrypt(miniCardCommon);
            userId = NetSecurity.decrypt(userId);
            sp = NetSecurity.decrypt(sp);
            wordId = NetSecurity.decrypt(wordId);
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();
                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_分配库存小卡_网点用户";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;
                        cmd.Parameters.Clear();


                        var sp0 = new SqlParameter("@小卡号码共同前缀", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = miniCardCommon };
                        cmd.Parameters.Add(sp0);


                        var sp1 = new SqlParameter("@小卡号码后缀起始", SqlDbType.Int) { Direction = ParameterDirection.Input, Value = miniCardPre };
                        cmd.Parameters.Add(sp1);


                        var sp2 = new SqlParameter("@小卡号码后缀截止", SqlDbType.Int) { Direction = ParameterDirection.Input, Value = miniCardSuf };
                        cmd.Parameters.Add(sp2);

                        var sp9 = new SqlParameter("@运营商", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = sp };
                        cmd.Parameters.Add(sp9);

                        var sp4 = new SqlParameter("@网点用户Id", SqlDbType.UniqueIdentifier)
                        {
                            Direction = ParameterDirection.Input,
                            Value =
                                string.IsNullOrEmpty(wordId) ? (object)DBNull.Value : new Guid(userId)
                        };
                        cmd.Parameters.Add(sp4);


                        var sp5 = new SqlParameter("@操作者Id", SqlDbType.UniqueIdentifier)
                        {
                            Direction = ParameterDirection.Input,
                            Value =
                                string.IsNullOrEmpty(wordId) ? (object)DBNull.Value : new Guid(wordId)
                        };
                        cmd.Parameters.Add(sp5);

                        var sp6 = new SqlParameter("@出错小卡号码", SqlDbType.NVarChar, 100)
                        {
                            Direction = ParameterDirection.Output
                        };
                        cmd.Parameters.Add(sp6);

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("1"))
                        {
                            cmd.Dispose();
                            return "库存小卡分配成功!";
                        }
                        else
                        {
                            cmd.Dispose();
                            return "小卡：" + sp6.Value.ToString() + "不存在，请检查或与管理员联系!";
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

        [WebMethod]
        //维护库存小卡
        public string MaintainMiniCard(MiniCardItem item, int operType, string wordId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId, wordId))
            {
                //不合法的请求调用
                return "非法登录！";
            }
            if (operType > 3 || operType < 1)
            {
                return "非法操作序号！";
            }
            //解密
            wordId = NetSecurity.decrypt(wordId);
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();
                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_维护库存小卡";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;
                        cmd.Parameters.Clear();


                        var sp0 = new SqlParameter("@小卡Id", SqlDbType.UniqueIdentifier)
                                      {
                                          Direction = ParameterDirection.Input,
                                          Value = item.id.Equals(Guid.Empty) ? Guid.NewGuid() : item.id
                                      };
                        cmd.Parameters.Add(sp0);


                        var sp1 = new SqlParameter("@小卡号码", SqlDbType.NVarChar, 50) { Value = item.cardNo, Direction = ParameterDirection.Input };

                        cmd.Parameters.Add(sp1);


                        var sp2 = new SqlParameter("@号段", SqlDbType.NVarChar, 50) { Value = item.noSection, Direction = ParameterDirection.Input };

                        cmd.Parameters.Add(sp2);


                        var sp3 = new SqlParameter("@运营商", SqlDbType.NVarChar, 50)
                                      {
                                          Direction = ParameterDirection.Input,
                                          Value =
                                              string.IsNullOrEmpty(item.SP)
                                                  ? (object)DBNull.Value
                                                  : item.SP
                                      };
                        cmd.Parameters.Add(sp3);


                        var sp4 = new SqlParameter("@使用状态", SqlDbType.NVarChar, 50)
                        {
                            Direction = ParameterDirection.Input,
                            Value =
                                string.IsNullOrEmpty(item.state)
                                    ? (object)DBNull.Value
                                    : item.state
                        };
                        cmd.Parameters.Add(sp4);

                        var sp5 = new SqlParameter("@领卡人Id", SqlDbType.UniqueIdentifier)
                        {
                            Direction = ParameterDirection.Input,
                            Value = item.getWorkerId.Equals(Guid.Empty) ? (object)DBNull.Value : item.getWorkerId
                        };
                        cmd.Parameters.Add(sp5);

                        var sp6 = new SqlParameter("@业务员Id", SqlDbType.UniqueIdentifier)
                        {
                            Direction = ParameterDirection.Input,
                            Value = item.workerId.Equals(Guid.Empty) ? (object)DBNull.Value : item.workerId
                        };
                        cmd.Parameters.Add(sp6);

                        var sp7 = new SqlParameter("@网点用户Id", SqlDbType.UniqueIdentifier)
                        {
                            Direction = ParameterDirection.Input,
                            Value = item.userId.Equals(Guid.Empty) ? (object)DBNull.Value : item.userId
                        };
                        cmd.Parameters.Add(sp7);




                        var sp8 = new SqlParameter("@OperType", SqlDbType.Int) { Direction = ParameterDirection.Input, Value = operType };
                        cmd.Parameters.Add(sp8);


                        var sp9 = new SqlParameter("@操作者Id", SqlDbType.UniqueIdentifier)
                                      {
                                          Direction = ParameterDirection.Input,
                                          Value =
                                              string.IsNullOrEmpty(wordId) ? (object)DBNull.Value : new Guid(wordId)
                                      };
                        cmd.Parameters.Add(sp9);


                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("1"))
                        {
                            cmd.Dispose();
                            if (operType == 1)
                            {
                                return "新增库存小卡成功！";
                            }
                            else if (operType == 2)
                            {
                                return "修改库存小卡成功！";
                            }
                            else
                            {
                                return "删除库存小卡成功！";
                            }
                        }
                        else
                        {
                            cmd.Dispose();
                            if (operType == 1)
                            {
                                return "新增库存小卡失败！";
                            }
                            else if (operType == 2)
                            {
                                return "修改库存小卡失败！";
                            }
                            else
                            {
                                return "删除库存小卡失败！";
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

        [WebMethod]
        //导入库存号码
        public string ImportPhoneNo(string num, string haoduan, string zhengce, string sp, double money, string workId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId, workId))
            {
                //不合法的请求调用
                return "非法登录！";
            }
            //解密
            num = NetSecurity.decrypt(num);
            haoduan = NetSecurity.decrypt(haoduan);
            zhengce = NetSecurity.decrypt(zhengce);
            sp = NetSecurity.decrypt(sp);
            workId = NetSecurity.decrypt(workId);
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();
                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_导入库存号码";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;
                        cmd.Parameters.Clear();


                        var sp0 = new SqlParameter("@号码", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = num };
                        cmd.Parameters.Add(sp0);


                        var sp1 = new SqlParameter("@号段", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = haoduan };
                        cmd.Parameters.Add(sp1);


                        var sp3 = new SqlParameter("@入网政策", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = zhengce };
                        cmd.Parameters.Add(sp3);

                        var sp4 = new SqlParameter("@运营商", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = sp };
                        cmd.Parameters.Add(sp4);

                        var sp6 = new SqlParameter("@选号费", SqlDbType.Money) { Direction = ParameterDirection.Input, Value = money >= 0 ? money : (object)DBNull.Value };
                        cmd.Parameters.Add(sp6);


                        var sp5 = new SqlParameter("@操作者Id", SqlDbType.UniqueIdentifier)
                        {
                            Direction = ParameterDirection.Input,
                            Value =
                                string.IsNullOrEmpty(workId) ? (object)DBNull.Value : new Guid(workId)
                        };
                        cmd.Parameters.Add(sp5);





                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("1"))
                        {
                            cmd.Dispose();
                            return "导入成功";
                        }
                        else
                        {
                            cmd.Dispose();
                            return "导入失败";
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

        [WebMethod]
        //分配库存号码
        public string AssignmentPhoneNo(string numId, double fee, int right, string area, string workId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId, workId))
            {
                //不合法的请求调用
                return "非法登录！";
            }
            //解密
            numId = NetSecurity.decrypt(numId);
            area = NetSecurity.decrypt(area);
            workId = NetSecurity.decrypt(workId);
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();
                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_分配库存号码";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;
                        cmd.Parameters.Clear();


                        var sp0 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(numId) };
                        cmd.Parameters.Add(sp0);


                        var sp1 = new SqlParameter("@选号费", SqlDbType.Money) { Direction = ParameterDirection.Input, Value = fee };
                        cmd.Parameters.Add(sp1);


                        var sp3 = new SqlParameter("@权值", SqlDbType.Int) { Direction = ParameterDirection.Input, Value = right };
                        cmd.Parameters.Add(sp3);

                        var sp4 = new SqlParameter("@分区", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = area };
                        cmd.Parameters.Add(sp4);


                        var sp5 = new SqlParameter("@操作者Id", SqlDbType.UniqueIdentifier)
                        {
                            Direction = ParameterDirection.Input,
                            Value =
                                string.IsNullOrEmpty(workId) ? (object)DBNull.Value : new Guid(workId)
                        };
                        cmd.Parameters.Add(sp5);





                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("1"))
                        {
                            cmd.Dispose();
                            return "分配成功";
                        }
                        else
                        {
                            cmd.Dispose();
                            return "分配失败";
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

        [WebMethod]
        //维护库存号码
        public string MaintainPhoneNo(PhoneNoItem item, int operType, string workId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId, workId))
            {
                //不合法的请求调用
                return "非法登录！";
            }
            if (operType > 3 || operType < 1)
            {
                return "非法操作序号！";
            }
            //解密
            workId = NetSecurity.decrypt(workId);
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();
                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_维护库存号码";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;
                        cmd.Parameters.Clear();


                        var sp0 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier)
                        {
                            Direction = ParameterDirection.Input,
                            Value = item.id.Equals(Guid.Empty) ? Guid.NewGuid() : item.id
                        };
                        cmd.Parameters.Add(sp0);


                        var sp1 = new SqlParameter("@号码", SqlDbType.NVarChar, 50) { Value = item.No, Direction = ParameterDirection.Input };

                        cmd.Parameters.Add(sp1);


                        var sp2 = new SqlParameter("@号段", SqlDbType.NVarChar, 50) { Value = item.NoSection, Direction = ParameterDirection.Input };

                        cmd.Parameters.Add(sp2);


                        var sp3 = new SqlParameter("@运营商", SqlDbType.NVarChar, 50)
                        {
                            Direction = ParameterDirection.Input,
                            Value =
                                string.IsNullOrEmpty(item.sp)
                                    ? (object)DBNull.Value
                                    : item.sp
                        };
                        cmd.Parameters.Add(sp3);


                        var sp4 = new SqlParameter("@使用状态", SqlDbType.NVarChar, 50)
                        {
                            Direction = ParameterDirection.Input,
                            Value =
                                string.IsNullOrEmpty(item.state)
                                    ? (object)DBNull.Value
                                    : item.state
                        };
                        cmd.Parameters.Add(sp4);

                        var sp5 = new SqlParameter("@入网政策", SqlDbType.NVarChar, 50)
                        {
                            Direction = ParameterDirection.Input,
                            Value =
                                string.IsNullOrEmpty(item.inNetPolicy)
                                    ? (object)DBNull.Value
                                    : item.inNetPolicy
                        };
                        cmd.Parameters.Add(sp5);

                        var sp6 = new SqlParameter("@分区", SqlDbType.NVarChar, 50)
                        {
                            Direction = ParameterDirection.Input,
                            Value =
                                string.IsNullOrEmpty(item.inNetPolicy)
                                    ? (object)DBNull.Value
                                    : item.area
                        };
                        cmd.Parameters.Add(sp6);

                        var sp7 = new SqlParameter("@权值", SqlDbType.Int)
                        {
                            Direction = ParameterDirection.Input,
                            Value = item.weight

                        };
                        cmd.Parameters.Add(sp7);

                        var sp8 = new SqlParameter("@选号费", SqlDbType.Money)
                        {
                            Direction = ParameterDirection.Input,
                            Value = item.NoPrice

                        };
                        cmd.Parameters.Add(sp8);


                        var sp10 = new SqlParameter("@OperType", SqlDbType.Int) { Direction = ParameterDirection.Input, Value = operType };
                        cmd.Parameters.Add(sp10);


                        var sp9 = new SqlParameter("@操作者Id", SqlDbType.UniqueIdentifier)
                        {
                            Direction = ParameterDirection.Input,
                            Value =
                                string.IsNullOrEmpty(workId) ? (object)DBNull.Value : new Guid(workId)
                        };
                        cmd.Parameters.Add(sp9);


                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("1"))
                        {
                            cmd.Dispose();
                            if (operType == 1)
                            {
                                return "新增库存号码成功！";
                            }
                            else if (operType == 2)
                            {
                                return "修改库存号码成功！";
                            }
                            else
                            {
                                return "删除库存号码成功！";
                            }
                        }
                        else
                        {
                            cmd.Dispose();
                            if (operType == 1)
                            {
                                return "新增库存号码失败！";
                            }
                            else if (operType == 2)
                            {
                                return "修改库存号码失败！";
                            }
                            else
                            {
                                return "删除库存号码失败！";
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

        [WebMethod]
        //增加套餐类型,input: 运营商，套餐名，是否常用，套餐介绍
        public string AddCardService(string SP, string serviceName, bool isFreq, string serviceSpec, string workerId, string sessionId)
        {

            if (!SessionValidater.ValidateSessionId(sessionId, workerId))
            {
                //不合法的请求调用
                return "非法登录";
            }
            //解密
            SP = NetSecurity.decrypt(SP);
            serviceName = NetSecurity.decrypt(serviceName);
            serviceSpec = NetSecurity.decrypt(serviceSpec);
            workerId = NetSecurity.decrypt(workerId);

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_新增套餐";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp1 = new SqlParameter("@发布者Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = string.IsNullOrEmpty(workerId) ? (object)DBNull.Value : new Guid(workerId) };
                        cmd.Parameters.Add(sp1);


                        var sp2 = new SqlParameter("@运营商", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = SP };
                        cmd.Parameters.Add(sp2);

                        var sp3 = new SqlParameter("@套餐名称", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = serviceName };
                        cmd.Parameters.Add(sp3);

                        var sp4 = new SqlParameter("@是否常用", SqlDbType.Bit) { Direction = ParameterDirection.Input, Value = isFreq };
                        cmd.Parameters.Add(sp4);

                        var sp5 = new SqlParameter("@套餐说明", SqlDbType.Text) { Direction = ParameterDirection.Input, Value = serviceSpec };
                        cmd.Parameters.Add(sp5);

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();
                        if (res.Equals("1"))
                        {
                            return "新增成功";
                        }
                        else
                        {
                            return "新增失败";
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
        //修改套餐类型,input: id，运营商，套餐名，是否常用，套餐介绍
        public string UpdateCardService(string id, string SP, string serviceName, bool isFreq, string serviceSpec, string workerId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId, workerId))
            {
                //不合法的请求调用
                return "非法登录";
            }
            //解密
            id = NetSecurity.decrypt(id);
            SP = NetSecurity.decrypt(SP);
            serviceName = NetSecurity.decrypt(serviceName);
            serviceSpec = NetSecurity.decrypt(serviceSpec);
            workerId = NetSecurity.decrypt(workerId);

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_修改套餐";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp0 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = string.IsNullOrEmpty(workerId) ? (object)DBNull.Value : new Guid(id) };
                        cmd.Parameters.Add(sp0);

                        var sp1 = new SqlParameter("@操作员Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = string.IsNullOrEmpty(workerId) ? (object)DBNull.Value : new Guid(workerId) };
                        cmd.Parameters.Add(sp1);


                        var sp2 = new SqlParameter("@运营商", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = SP };
                        cmd.Parameters.Add(sp2);

                        var sp3 = new SqlParameter("@套餐名称", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = serviceName };
                        cmd.Parameters.Add(sp3);

                        var sp4 = new SqlParameter("@是否常用", SqlDbType.Bit) { Direction = ParameterDirection.Input, Value = isFreq };
                        cmd.Parameters.Add(sp4);

                        var sp5 = new SqlParameter("@套餐说明", SqlDbType.Text) { Direction = ParameterDirection.Input, Value = serviceSpec };
                        cmd.Parameters.Add(sp5);

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();
                        if (res.Equals("1"))
                        {
                            return "修改成功";
                        }
                        else
                        {
                            return "修改失败";
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
        //删除套餐类型
        public string DeleteCardService(string id, string workerId, string sessionId)
        {

            if (!SessionValidater.ValidateSessionId(sessionId, workerId))
            {
                //不合法的请求调用
                return "非法登录";
            }
            //解密
            id = NetSecurity.decrypt(id);
            workerId = NetSecurity.decrypt(workerId);

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_删除套餐";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp0 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = string.IsNullOrEmpty(workerId) ? (object)DBNull.Value : new Guid(id) };
                        cmd.Parameters.Add(sp0);

                        var sp1 = new SqlParameter("@操作员Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = string.IsNullOrEmpty(workerId) ? (object)DBNull.Value : new Guid(workerId) };
                        cmd.Parameters.Add(sp1);

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();
                        if (res.Equals("1"))
                        {
                            return "删除成功";
                        }
                        else
                        {
                            return "删除失败";
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
        //导入库存卡类
        public string ImportStockCard(string cardType, string cardName, string cardSeq, string cardPsw, string workId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId, workId))
            {
                //不合法的请求调用
                return "非法登录！";
            }
            //解密
            cardType = NetSecurity.decrypt(cardType);
            cardName = NetSecurity.decrypt(cardName);
            cardSeq = NetSecurity.decrypt(cardSeq);
            cardPsw = NetSecurity.decrypt(cardPsw);
            workId = NetSecurity.decrypt(workId);
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();
                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_导入库存卡类";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;
                        cmd.Parameters.Clear();


                        var sp1 = new SqlParameter("@卡类型", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = cardType };
                        cmd.Parameters.Add(sp1);


                        var sp2 = new SqlParameter("@卡名称", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = cardName };
                        cmd.Parameters.Add(sp2);


                        var sp3 = new SqlParameter("@序列号", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = cardSeq };
                        cmd.Parameters.Add(sp3);

                        var sp4 = new SqlParameter("@卡密", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = cardPsw };
                        cmd.Parameters.Add(sp4);

                        var sp5 = new SqlParameter("@操作者Id", SqlDbType.UniqueIdentifier)
                        {
                            Direction = ParameterDirection.Input,
                            Value =
                                string.IsNullOrEmpty(workId) ? (object)DBNull.Value : new Guid(workId)
                        };
                        cmd.Parameters.Add(sp5);





                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("1"))
                        {
                            cmd.Dispose();
                            return "导入成功";
                        }
                        else
                        {
                            cmd.Dispose();
                            return "导入失败";
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

        [WebMethod]
        //维护库存卡类
        public string MaintainStockCard(StockCardItem item, int operType, string workId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId, workId))
            {
                //不合法的请求调用
                return "非法登录！";
            }
            if (operType > 3 || operType < 1)
            {
                return "非法操作序号！";
            }
            //解密
            workId = NetSecurity.decrypt(workId);
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();
                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_维护库存卡类";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;
                        cmd.Parameters.Clear();


                        var sp0 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier)
                        {
                            Direction = ParameterDirection.Input,
                            Value = item.Id.Equals(Guid.Empty) ? Guid.NewGuid() : item.Id
                        };
                        cmd.Parameters.Add(sp0);


                        var sp1 = new SqlParameter("@卡类型", SqlDbType.NVarChar, 50) { Value = item.cardType, Direction = ParameterDirection.Input };

                        cmd.Parameters.Add(sp1);


                        var sp2 = new SqlParameter("@卡名称", SqlDbType.NVarChar, 50) { Value = item.cardName, Direction = ParameterDirection.Input };

                        cmd.Parameters.Add(sp2);


                        var sp3 = new SqlParameter("@序列号", SqlDbType.NVarChar, 50)
                        {
                            Direction = ParameterDirection.Input,
                            Value =
                                string.IsNullOrEmpty(item.cardSeq)
                                    ? (object)DBNull.Value
                                    : item.cardSeq
                        };
                        cmd.Parameters.Add(sp3);


                        var sp4 = new SqlParameter("@卡密", SqlDbType.NVarChar, 50)
                        {
                            Direction = ParameterDirection.Input,
                            Value =
                                string.IsNullOrEmpty(item.cardPsw)
                                    ? (object)DBNull.Value
                                    : item.cardPsw
                        };
                        cmd.Parameters.Add(sp4);

                        var sp5 = new SqlParameter("@状态", SqlDbType.NVarChar, 50)
                        {
                            Direction = ParameterDirection.Input,
                            Value =
                                string.IsNullOrEmpty(item.state)
                                    ? (object)DBNull.Value
                                    : item.state
                        };
                        cmd.Parameters.Add(sp5);

                      

                        var sp10 = new SqlParameter("@OperType", SqlDbType.Int) { Direction = ParameterDirection.Input, Value = operType };
                        cmd.Parameters.Add(sp10);


                        var sp9 = new SqlParameter("@操作者Id", SqlDbType.UniqueIdentifier)
                        {
                            Direction = ParameterDirection.Input,
                            Value =
                                string.IsNullOrEmpty(workId) ? (object)DBNull.Value : new Guid(workId)
                        };
                        cmd.Parameters.Add(sp9);


                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("1"))
                        {
                            cmd.Dispose();
                            if (operType == 1)
                            {
                                return "新增库存卡类成功！";
                            }
                            else if (operType == 2)
                            {
                                return "修改库存卡类成功！";
                            }
                            else
                            {
                                return "删除库存卡类成功！";
                            }
                        }
                        else
                        {
                            cmd.Dispose();
                            if (operType == 1)
                            {
                                return "新增库存卡类失败！";
                            }
                            else if (operType == 2)
                            {
                                return "修改库存卡类失败！";
                            }
                            else
                            {
                                return "删除库存卡类失败！";
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

        #endregion
        */
    }
}
