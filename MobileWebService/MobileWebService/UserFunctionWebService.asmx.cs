using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Web;
using System.Web.Services;
using MobileWebService.Entity;
using System.Data.SqlClient;
using System.Data;
using MobileWebService.Validater;
using MobileWebService.Util;


namespace MobileWebService
{
    /// <summary>
    /// UserFunctionWebService 的摘要说明
    /// </summary>
    [WebService(Namespace = "http://tempuri.org/")]
    [WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
    [System.ComponentModel.ToolboxItem(false)]
    // 若要允许使用 ASP.NET AJAX 从脚本中调用此 Web 服务，请取消对下行的注释。
    // [System.Web.Script.Services.ScriptService]
    public class UserFunctionWebService : System.Web.Services.WebService
    {
        #region 客户端专用

        [WebMethod]
        public string HelloWorld()
        {
            var date = DateTime.Now;
            return date.Ticks.ToString();
        }

        [WebMethod]
        public string loggout(string userId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId, userId))
            {
                //不合法的请求调用
                return null;
            }
            userId = NetSecurity.decrypt(userId);
            sessionId = NetSecurity.decrypt(sessionId);

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_网点用户_退出";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;
                        var sp1 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier);
                        sp1.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp1);
                        sp1.Value = new Guid(userId);

                        var sp2 = new SqlParameter("@SessionId", SqlDbType.UniqueIdentifier);
                        sp2.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp2);
                        sp2.Value = new Guid(sessionId);

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("1"))
                        {
                            cmd.Dispose();
                            return "退出成功";
                        }
                        else
                        {
                            cmd.Dispose();
                            return "退出失败";
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

        //测试登录是否成功，返回sessionId
        [WebMethod]
        public string TestLogin(string Username, string Password, string Mac, string ip, string clientType)
        {
            //解密接受到的数据
            Username = NetSecurity.decrypt(Username);
            Password = NetSecurity.decrypt(Password);
            Mac = NetSecurity.decrypt(Mac);
            ip = NetSecurity.decrypt(ip);
            clientType = NetSecurity.decrypt(clientType);

            string sessionId = "";
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_网点用户_登录";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;
                        var sp1 = new SqlParameter("@登陆名", SqlDbType.NVarChar, 50);
                        sp1.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp1);
                        sp1.Value = Username;

                        var sp2 = new SqlParameter("@密码", SqlDbType.NVarChar, 50);
                        sp2.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp2);
                        sp2.Value = Password;

                        var sp3 = new SqlParameter("@IP地址", SqlDbType.NVarChar, 50);
                        sp3.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp3);
                        sp3.Value = ip;

                        var sp4 = new SqlParameter("@MAC地址", SqlDbType.NVarChar, 50);
                        sp4.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp4);
                        sp4.Value = Mac;

                        var sp5 = new SqlParameter("@客户端类型", SqlDbType.NVarChar, 50);
                        sp4.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp5);
                        sp5.Value = clientType;

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("1"))
                        {
                            string uid = "";
                            using (var cmd1 = new SqlCommand())
                            {
                                cmd1.CommandText = "select Id  from 网点用户 Where [登陆名] = '" + Username + "' and [密码] = '" + Password + "' and [客户端类型]='" + clientType + "'";
                                cmd1.CommandType = CommandType.Text;
                                cmd1.Connection = con;
                                using (SqlDataReader sdr = cmd1.ExecuteReader())// cmd2.ExecuteNonQuery();
                                {

                                    if (sdr.HasRows)
                                    {
                                        while (sdr.Read())
                                        {

                                            uid = sdr["Id"].ToString();
                                        }
                                        sdr.Close();
                                    }
                                }
                            }
                            using (var cmd2 = new SqlCommand())
                            {
                                cmd2.CommandText = "Proc_SYS_Session_Insert";
                                cmd2.CommandType = CommandType.StoredProcedure;
                                cmd2.Connection = con;
                                cmd2.Parameters.Clear();

                                var ssp1 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier);
                                ssp1.Direction = ParameterDirection.Input;
                                cmd2.Parameters.Add(ssp1);
                                var id = Guid.NewGuid();
                                sessionId = id.ToString();
                                ssp1.Value = id;

                                var ssp2 = new SqlParameter("@创建时间", SqlDbType.DateTime);
                                ssp2.Direction = ParameterDirection.Input;
                                cmd2.Parameters.Add(ssp2);
                                ssp2.Value = DateTime.Now;

                                var ssp3 = new SqlParameter("@创建用户Id", SqlDbType.UniqueIdentifier);
                                ssp3.Direction = ParameterDirection.Input;
                                cmd2.Parameters.Add(ssp3);
                                ssp3.Value = new Guid(uid);

                                var ssp4 = new SqlParameter("@上一次操作时间", SqlDbType.DateTime);
                                ssp4.Direction = ParameterDirection.Input;
                                cmd2.Parameters.Add(ssp4);
                                ssp4.Value = DateTime.Now;

                                cmd2.ExecuteNonQuery();
                            }
                            return sessionId;
                        }
                        else if (res.Equals("2"))
                        {
                            sessionId = "账户尚未通过审核！请等待...";
                            return sessionId;
                        }
                        else if (res.Equals("3"))
                        {
                            sessionId = "该账户已经被登录！请不要重复登录";
                            return sessionId;
                        }
                        else
                        {
                            sessionId = "用户名或密码错误";
                            return sessionId;
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

        //获取用户详细信息，返回xml
        [WebMethod]
        public User GetUserInfo(string username, string password, string clientType, string sessionId)
        {
            
            if (SessionValidater.ValidateSessionIdWithTime(sessionId) == 0)
            {
                //不合法的请求调用
                return null;
            }
            else if (SessionValidater.ValidateSessionIdWithTime(sessionId) == -1)
            {
                return null;
            }

            //解密
            username = NetSecurity.decrypt(username);
            password = NetSecurity.decrypt(password);
            clientType = NetSecurity.decrypt(clientType);
            

            User user = new User();
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "select * from 网点用户 Where [登陆名] = '" + username + "' and [密码] = '" + password + "' and [客户端类型]='" + clientType + "'";
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;
                        using (SqlDataReader sdr = cmd.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {
                                    if (sdr["Id"] != null)
                                        user.Id = new Guid(sdr["Id"].ToString());
                                    if (sdr["登陆名"] != null)
                                        user.loggingName = sdr["登陆名"].ToString();
                                    if (sdr["密码"] != null)
                                        user.password = sdr["密码"].ToString();
                                    if (sdr["账户余额"] != null)
                                        user.money = float.Parse(sdr["账户余额"].ToString());
                                    if (sdr["MAC地址"] != null)
                                        user.mac = sdr["MAC地址"].ToString();
                                    if (sdr["固定电话"] != null)
                                        user.tel = sdr["固定电话"].ToString();
                                    if (sdr["地址"] != null)
                                        user.address = sdr["地址"].ToString();
                                    if (sdr["店名"] != null)
                                        user.shopName = sdr["店名"].ToString();
                                    if (sdr["移动电话"] != null)
                                        user.mobilePhone = sdr["移动电话"].ToString();
                                    if (sdr["真实姓名拼音"] != null)
                                        user.pingying = sdr["真实姓名拼音"].ToString();
                                    if (sdr["真实姓名"] != null)
                                        user.realName = sdr["真实姓名"].ToString();
                                    if (sdr["身份证号"] != null)
                                        user.indentityNo = sdr["身份证号"].ToString();
                                    if (sdr["业务负责人Id"].ToString() != "")
                                    {
                                        string guid_str = sdr["业务负责人Id"].ToString();
                                        user.manager_id = new Guid(guid_str);
                                    }
                                    if (sdr["业务负责人"] != null)
                                        user.managerName = sdr["业务负责人"].ToString();
                                    if (sdr["存款尾数"] != null)
                                        user.moneyTail = sdr["存款尾数"].ToString();
                                    if (sdr["用户级别"] != null)
                                        user.level = sdr["用户级别"].ToString();
                                    if (sdr["注册时间"].ToString() != "")
                                        user.registerDatetime = DateTime.Parse(sdr["注册时间"].ToString());
                                    if (sdr["是否审核"] != null)
                                        user.isValidate = Convert.ToBoolean(sdr["是否审核"].ToString());
                                }
                                sdr.Close();
                            }
                            else
                            {
                                //用户名或密码错误
                                return null;
                            }
                            //查询按钮的权限
                            if (user.Id != null)
                            {
                                using (var cmd1 = new SqlCommand())
                                {
                                    cmd1.CommandText = "select a.功能名称 from 系统功能 as a, 员工_功能_映射表 as b where a.Id=b.系统功能Id and b.员工Id='" + user.Id.ToString() + "'";
                                    cmd1.CommandType = CommandType.Text;
                                    cmd1.Connection = con;
                                    using (SqlDataReader sdr1 = cmd1.ExecuteReader())// cmd2.ExecuteNonQuery();
                                    {
                                        if (sdr1.HasRows)
                                        {
                                            while (sdr1.Read())
                                            {
                                                user.btnList += sdr1["功能名称"].ToString() + ",";
                                            }
                                        }
                                        sdr1.Close();
                                    }
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
            return user;
        }

        //注册用户
        [WebMethod]
        public string RegisterUser(string username, string password, string mac, string adrTel, string address, string shopName, string mobilePhone, string realName, string identifyNo, string workerName,  string workerId, string moneyTail, string clientType)
        {

            //解密
            username = NetSecurity.decrypt(username);
            password = NetSecurity.decrypt(password);
            mac = NetSecurity.decrypt(mac);
            adrTel = NetSecurity.decrypt(adrTel);
            address = NetSecurity.decrypt(address);
            shopName = NetSecurity.decrypt(shopName);
            mobilePhone = NetSecurity.decrypt(mobilePhone);
            realName = NetSecurity.decrypt(realName);
            identifyNo = NetSecurity.decrypt(identifyNo);
            workerName = NetSecurity.decrypt(workerName);
            workerId = NetSecurity.decrypt(workerId);
            moneyTail = NetSecurity.decrypt(moneyTail);
            clientType = NetSecurity.decrypt(clientType);

            Guid work_id = Guid.Empty;
            string pingying = "";
            if (realName != null)
            {
                pingying = ChineseToPingYing.GetSpell(realName);
            }
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();
                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "select * from 网点用户 Where [登陆名] = '" + username + "' and [客户端类型]='" + clientType + "'";
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;
                        using (SqlDataReader sdr = cmd.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {
                                    return "用户名已经存在！请更换用户名";
                                }
                            }
                            sdr.Close();
                        }
                    }

                    using (var cmd2 = new SqlCommand())
                    {
                        cmd2.CommandText = "Function_网点用户_注册";
                        cmd2.CommandType = CommandType.StoredProcedure;
                        cmd2.Connection = con;
                        cmd2.Parameters.Clear();

                        var sp1 = new SqlParameter("@登陆名", SqlDbType.NVarChar, 50);
                        sp1.Direction = ParameterDirection.Input;
                        cmd2.Parameters.Add(sp1);
                        sp1.Value = username;

                        var sp2 = new SqlParameter("@密码", SqlDbType.NVarChar, 50);
                        sp2.Direction = ParameterDirection.Input;
                        cmd2.Parameters.Add(sp2);
                        sp2.Value = password;

                        var sp3 = new SqlParameter("@MAC地址", SqlDbType.NVarChar, 50);
                        sp3.Direction = ParameterDirection.Input;
                        cmd2.Parameters.Add(sp3);
                        sp3.Value = mac;

                        var sp4 = new SqlParameter("@固定电话", SqlDbType.NVarChar, 50);
                        sp4.Direction = ParameterDirection.Input;
                        cmd2.Parameters.Add(sp4);
                        sp4.Value = adrTel;

                        var sp5 = new SqlParameter("@地址", SqlDbType.NVarChar, 50);
                        sp5.Direction = ParameterDirection.Input;
                        cmd2.Parameters.Add(sp5);
                        sp5.Value = address;

                        var sp6 = new SqlParameter("@店名", SqlDbType.NVarChar, 50);
                        sp6.Direction = ParameterDirection.Input;
                        cmd2.Parameters.Add(sp6);
                        sp6.Value = shopName;

                        var sp7 = new SqlParameter("@移动电话", SqlDbType.NVarChar, 50);
                        sp7.Direction = ParameterDirection.Input;
                        cmd2.Parameters.Add(sp7);
                        sp7.Value = mobilePhone;

                        var sp8 = new SqlParameter("@真实姓名拼音", SqlDbType.NVarChar, 50);
                        sp8.Direction = ParameterDirection.Input;
                        cmd2.Parameters.Add(sp8);
                        sp8.Value = pingying;

                        var sp9 = new SqlParameter("@真实姓名", SqlDbType.NVarChar, 50);
                        sp9.Direction = ParameterDirection.Input;
                        cmd2.Parameters.Add(sp9);
                        sp9.Value = realName;

                        var sp10 = new SqlParameter("@身份证号", SqlDbType.NVarChar, 50);
                        sp10.Direction = ParameterDirection.Input;
                        cmd2.Parameters.Add(sp10);
                        sp10.Value = identifyNo;

                        var sp11 = new SqlParameter("@业务负责人Id", SqlDbType.UniqueIdentifier);
                        sp11.Direction = ParameterDirection.Input;
                        cmd2.Parameters.Add(sp11);
                        sp11.Value = new Guid(workerId);

                        var sp12 = new SqlParameter("@业务负责人", SqlDbType.NVarChar, 50);
                        sp12.Direction = ParameterDirection.Input;
                        cmd2.Parameters.Add(sp12);
                        sp12.Value = workerName;

                        var sp13 = new SqlParameter("@存款尾数", SqlDbType.NVarChar, 50);
                        sp13.Direction = ParameterDirection.Input;
                        cmd2.Parameters.Add(sp13);
                        sp13.Value = moneyTail;

                        var sp14 = new SqlParameter("@客户端类型", SqlDbType.NVarChar, 50);
                        sp14.Direction = ParameterDirection.Input;
                        cmd2.Parameters.Add(sp14);
                        sp14.Value = clientType;

                        cmd2.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd2.ExecuteNonQuery();
                        var res = cmd2.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("1"))
                        {
                            cmd2.Dispose();
                            return "注册成功";
                        }
                        else
                        {
                            cmd2.Dispose();
                            return "注册失败";
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

        //修改密码
        [WebMethod]
        public string AlterPsw(string user_id, string newPsw, string sessionId)
        {
            if (SessionValidater.ValidateSessionIdWithTime(sessionId, user_id) == 0)
            {
                //不合法的请求调用
                return null;
            }
            else if (SessionValidater.ValidateSessionIdWithTime(sessionId, user_id) == -1)
            {
                return "会话超时，请重新登录！";
            }

            //解密
            user_id = NetSecurity.decrypt(user_id);
            newPsw = NetSecurity.decrypt(newPsw);

            //验证权限
            if (!AuthorizationHelper.validate(user_id).Contains("密码修改"))
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
                        cmd.CommandText = "Function_网点用户_修改密码";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;
                        var sp1 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier);
                        sp1.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp1);
                        sp1.Value = new Guid(user_id);

                        var sp2 = new SqlParameter("@密码", SqlDbType.NVarChar, 50);
                        sp2.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp2);
                        sp2.Value = newPsw;

                        cmd.ExecuteNonQuery();

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("1"))
                        {
                            cmd.Dispose();
                            return "修改密码成功";
                        }
                        else
                        {
                            cmd.Dispose();
                            return "修改密码失败";
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

        //修改用户信息
        [WebMethod]
        public string AlterUserInfo(string user_id, string adrTel, string address, string shopName, string mobilePhone, string realName, string identifyNo, string workerName, string moneyTail, string sessionId)
        {

            if (SessionValidater.ValidateSessionIdWithTime(sessionId, user_id) == 0)
            {
                //不合法的请求调用
                return null;
            }
            else if (SessionValidater.ValidateSessionIdWithTime(sessionId, user_id) == -1)
            {
                return "会话超时，请重新登录！";
            }

            //解密
            user_id = NetSecurity.decrypt(user_id);
            adrTel = NetSecurity.decrypt(adrTel);
            address = NetSecurity.decrypt(address);
            shopName = NetSecurity.decrypt(shopName);
            mobilePhone = NetSecurity.decrypt(mobilePhone);
            realName = NetSecurity.decrypt(realName);
            identifyNo = NetSecurity.decrypt(identifyNo);
            workerName = NetSecurity.decrypt(workerName);
            moneyTail = NetSecurity.decrypt(moneyTail);

            //验证权限
            if (!AuthorizationHelper.validate(user_id).Contains("用户信息修改"))
            {
                return null;
            }

            Guid work_id = Guid.Empty;
            string pingying = "";
            if (realName != null)
            {
                pingying = ChineseToPingYing.GetSpell(realName);
            }
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();
                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "select * from 员工 Where [用户名] = '" + workerName + "'";
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;
                        using (SqlDataReader sdr = cmd.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {
                                    if (sdr["Id"].ToString() != "")
                                    {
                                        work_id = new Guid(sdr["Id"].ToString());
                                    }
                                }
                            }
                            else
                            {
                                return "业务员名称有误！";
                            }
                            sdr.Close();
                        }
                    }

                    using (var cmd1 = new SqlCommand())
                    {
                        cmd1.CommandText = "Function_网点用户_修改基本信息";
                        cmd1.CommandType = CommandType.StoredProcedure;
                        cmd1.Connection = con;
                        cmd1.Parameters.Clear();

                        var sp1 = new SqlParameter("@Id", SqlDbType.NVarChar, 50);
                        sp1.Direction = ParameterDirection.Input;
                        cmd1.Parameters.Add(sp1);
                        sp1.Value = user_id;

                        var sp4 = new SqlParameter("@固定电话", SqlDbType.NVarChar, 50);
                        sp4.Direction = ParameterDirection.Input;
                        cmd1.Parameters.Add(sp4);
                        sp4.Value = adrTel;

                        var sp5 = new SqlParameter("@地址", SqlDbType.NVarChar, 50);
                        sp5.Direction = ParameterDirection.Input;
                        cmd1.Parameters.Add(sp5);
                        sp5.Value = address;

                        var sp6 = new SqlParameter("@店名", SqlDbType.NVarChar, 50);
                        sp6.Direction = ParameterDirection.Input;
                        cmd1.Parameters.Add(sp6);
                        sp6.Value = shopName;

                        var sp7 = new SqlParameter("@移动电话", SqlDbType.NVarChar, 50);
                        sp7.Direction = ParameterDirection.Input;
                        cmd1.Parameters.Add(sp7);
                        sp7.Value = mobilePhone;

                        var sp8 = new SqlParameter("@真实姓名拼音", SqlDbType.NVarChar, 50);
                        sp8.Direction = ParameterDirection.Input;
                        cmd1.Parameters.Add(sp8);
                        sp8.Value = pingying;

                        var sp9 = new SqlParameter("@真实姓名", SqlDbType.NVarChar, 50);
                        sp9.Direction = ParameterDirection.Input;
                        cmd1.Parameters.Add(sp9);
                        sp9.Value = realName;

                        var sp10 = new SqlParameter("@身份证号", SqlDbType.NVarChar, 50);
                        sp10.Direction = ParameterDirection.Input;
                        cmd1.Parameters.Add(sp10);
                        sp10.Value = identifyNo;

                        var sp11 = new SqlParameter("@业务负责人Id", SqlDbType.UniqueIdentifier);
                        sp11.Direction = ParameterDirection.Input;
                        cmd1.Parameters.Add(sp11);
                        sp11.Value = work_id;

                        var sp12 = new SqlParameter("@业务负责人", SqlDbType.NVarChar, 50);
                        sp12.Direction = ParameterDirection.Input;
                        cmd1.Parameters.Add(sp12);
                        sp12.Value = workerName;

                        var sp13 = new SqlParameter("@存款尾数", SqlDbType.NVarChar, 50);
                        sp13.Direction = ParameterDirection.Input;
                        cmd1.Parameters.Add(sp13);
                        sp13.Value = moneyTail;

                        cmd1.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd1.ExecuteNonQuery();
                        var res = cmd1.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("1"))
                        {
                            cmd1.Dispose();
                            return "修改基本信息成功";
                        }
                        else
                        {
                            cmd1.Dispose();
                            return "修改基本信息失败";
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

        //账户充值
        [WebMethod]
        public string AddAcountPayment(string username, string userId, float money, string payType, string bankName, string subBankName, long payTime, string content, string clientType, string sessionId)
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
            username = NetSecurity.decrypt(username);
            userId = NetSecurity.decrypt(userId);
            payType = NetSecurity.decrypt(payType);
            bankName = NetSecurity.decrypt(bankName);
            subBankName = NetSecurity.decrypt(subBankName);
            content = NetSecurity.decrypt(content);
            clientType = NetSecurity.decrypt(clientType);

            int limitTimeSpane = 0; //重交限制时间
            System.TimeSpan timeSpan = new TimeSpan();

            //金额合法性验证
            if (money <= 0) 
            {
                return "错误！充值金额必须大于0元"; 
            }

            //验证权限
            if (!AuthorizationHelper.validate(userId).Contains("账户充值"))
            {
                return null;
            }

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd1 = new SqlCommand())
                    {
                        /*判断是否存在多少分钟内重交*/
                        cmd1.CommandText = "select Code from [MobileManage].[dbo].[URP_DIC_Content] Where [Category] = '客户端限制' and [Name]='账户重复充值时间（分）'";
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
                        cmd2.CommandText = "select 充值时间  from 用户充值 Where [网点用户Id] = '" + userId + "' and [充值金额]=" + money + " and [充值银行名称]='" + bankName + "' order by [充值时间] desc";
                        cmd2.CommandType = CommandType.Text;
                        cmd2.Connection = con;
                        using (SqlDataReader sdr = cmd2.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                if (sdr.Read())
                                {

                                    DateTime lastPayTime = Convert.ToDateTime(sdr["充值时间"].ToString());
                                    timeSpan = DateTime.Now - lastPayTime;
                                    if (timeSpan.TotalMinutes < limitTimeSpane)
                                    {
                                        int limitMinutes = limitTimeSpane;
                                        return limitMinutes + "分钟内不能重复提交充值信息";
                                    }
                                }
                                sdr.Close();
                            }
                        }
                    }

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_网点用户_账户充值";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;
                        cmd.Parameters.Clear();


                        var sp0 = new SqlParameter("@网点用户Id", SqlDbType.UniqueIdentifier);
                        sp0.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp0);
                        sp0.Value = string.IsNullOrEmpty(userId) ? (object)DBNull.Value : new Guid(userId);

                        var sp1 = new SqlParameter("@账户名称", SqlDbType.NVarChar, 50);
                        sp1.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp1);
                        sp1.Value = username;

                        var sp4 = new SqlParameter("@充值金额", SqlDbType.Money);
                        sp4.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp4);
                        sp4.Value = money;

                        var sp5 = new SqlParameter("@充值方式", SqlDbType.NVarChar, 50);
                        sp5.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp5);
                        sp5.Value = payType;

                        var sp6 = new SqlParameter("@充值银行名称", SqlDbType.NVarChar, 50);
                        sp6.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp6);
                        sp6.Value = bankName;

                        var sp7 = new SqlParameter("@支行名称", SqlDbType.NVarChar, 50);
                        sp7.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp7);
                        sp7.Value = subBankName;

                        var sp8 = new SqlParameter("@充值时间", SqlDbType.DateTime);
                        sp8.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp8);
                        double secs = Convert.ToDouble(payTime);
                        DateTime dt = new DateTime(1970, 1, 1, 0, 0, 0, DateTimeKind.Unspecified).AddSeconds(secs);
                        sp8.Value = dt.ToLocalTime();

                        var sp9 = new SqlParameter("@备注信息", SqlDbType.Text);
                        sp9.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp9);
                        sp9.Value = content;

                        var sp10 = new SqlParameter("@客户端类型", SqlDbType.NChar, 50);
                        sp10.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp10);
                        sp10.Value = clientType;

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("1"))
                        {
                            cmd.Dispose();
                            return "账户充值成功";
                        }
                        else
                        {
                            cmd.Dispose();
                            return "账户充值失败";
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

        //获取代办费结算统计信息
        [WebMethod]
        public ReturnInfo GetReturnInfo(string userId, string clientLevel, string sessionId)
        {
            ReturnInfo returnInfo = new ReturnInfo();
            
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
            userId = NetSecurity.decrypt(userId);
            clientLevel = NetSecurity.decrypt(clientLevel);

            //验证权限
            if (!AuthorizationHelper.validate(userId).Contains("代办费结算"))
            {
                return null;
            }   

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    //首先获取账户的余额
                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "select * from 网点用户 Where [Id] = '" + userId + "'";
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;
                        using (SqlDataReader sdr = cmd.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {
                                    if (sdr["账户余额"] != null)
                                        returnInfo.curMoney = float.Parse(sdr["账户余额"].ToString());
                                }
                                sdr.Close();
                            }
                        }
                    }

                    //获取上一次结算日期
                    using (var cmd2 = new SqlCommand())
                    {
                        cmd2.CommandText = "SELECT top 1 [充值时间] FROM [MobileManage].[dbo].[用户充值] where [网点用户Id]='" + userId + "'  and [充值方式]='代办费结算' order by [充值时间] desc";
                        cmd2.CommandType = CommandType.Text;
                        cmd2.Connection = con;
                        using (SqlDataReader sdr = cmd2.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                if (sdr.Read())
                                {
                                    returnInfo.lastChargeTime = sdr["充值时间"].ToString();
                                }
                                sdr.Close();
                            }
                            else
                            {
                                returnInfo.lastChargeTime = "未进行过代办费结算";
                            }
                        }
                    }

                    using (var cmd1 = new SqlCommand())
                    {
                        string condition = "";
                        if (clientLevel == "高级用户")
                        {
                            condition = " and 处理时间<=dateadd(ms,-3,DATEADD(mm, DATEDIFF(mm,0,getdate()), 0)) ";
                        }
                        var selectCommand = string.Format("SELECT [返款类型],sum([处理金额]) as 处理金额,sum([返款金额]) as 返款金额, count([Id]) as total FROM [MobileManage].[dbo].[返款未结算记录] where [网点用户Id]='{0}' {1} group by [返款类型]", userId, condition);//组合选择语句
                        cmd1.CommandText = selectCommand;
                        cmd1.CommandType = CommandType.Text;
                        cmd1.Connection = con;

                        using (SqlDataReader sdr = cmd1.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {
                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {
                                    var item = new ReturnInfoItem();
                                    item.type =sdr["返款类型"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["处理金额"].ToString())) 
                                    {
                                        item.totalMoney = Convert.ToDouble(sdr["处理金额"].ToString());
                                        returnInfo.processTotalMoney += item.totalMoney;
                                    }
                                    if (!string.IsNullOrEmpty(sdr["返款金额"].ToString())) 
                                    {
                                        item.returnMoney = Convert.ToDouble(sdr["返款金额"].ToString());
                                         returnInfo.returnTotalMoney += item.returnMoney;
                                    }
                                    if (!string.IsNullOrEmpty(sdr["total"].ToString()))
                                    {
                                        item.count = Convert.ToInt16(sdr["total"].ToString());
                                        returnInfo.total += item.count;
                                    }
                                    returnInfo.list.Add(item);
                                }
                                returnInfo.afterReturnTotalMoney = returnInfo.curMoney+returnInfo.returnTotalMoney;
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
            return returnInfo;
        }

        //代办费结算，成功后返回新的网点用户信息（里面包含结算后的账户余额），失败返回空对象
        [WebMethod]
        public double CharegeReturnedMoney(string userId, string clientType, string clientLevel, string sessionId)
        {

            if (SessionValidater.ValidateSessionIdWithTime(sessionId, userId) == 0)
            {
                //不合法的请求调用
                return 0;
            }
            else if (SessionValidater.ValidateSessionIdWithTime(sessionId, userId) == -1)
            {
                return 0;
            }

            //解密
            userId = NetSecurity.decrypt(userId);
            clientType = NetSecurity.decrypt(clientType);
            clientLevel = NetSecurity.decrypt(clientLevel);

            //验证权限
            if (!AuthorizationHelper.validate(userId).Contains("代办费结算"))
            {
                return 0;
            }

            double newMoney = 0;
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        if (clientLevel == "高级用户")
                        {
                            cmd.CommandText = "Function_网点用户_代办费结算_高级用户";
                        }
                        else
                        {
                            cmd.CommandText = "Function_网点用户_代办费结算";
                        }
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;
                        var sp1 = new SqlParameter("@网点用户Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = string.IsNullOrEmpty(userId) ? (object)DBNull.Value : new Guid(userId) };
                        cmd.Parameters.Add(sp1);

                        var sp2 = new SqlParameter("@客户端类型", SqlDbType.NVarChar, 50);
                        sp2.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp2);
                        sp2.Value = clientType;

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("1"))
                        {
                            using (var cmd1 = new SqlCommand())
                            {
                                cmd1.CommandText = "select 账户余额 from 网点用户 where Id='" + userId + "'";
                                cmd1.CommandType = CommandType.Text;
                                cmd1.Connection = con;

                                using (SqlDataReader sdr = cmd1.ExecuteReader())// cmd2.ExecuteNonQuery();
                                {

                                    if (sdr.HasRows)
                                    {
                                        while (sdr.Read())
                                        {
                                            newMoney = Convert.ToDouble(sdr["账户余额"].ToString());
                                        }
                                    }
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
            return newMoney;
        }

        [WebMethod]
        public List<Worker> GetWorkNameList(string condition)
        {
            //解密
            condition = NetSecurity.decrypt(condition);

            var list = new List<Worker>();
            string selectCondition = "";
            if (!string.IsNullOrEmpty(condition))
            {
                selectCondition = "Where " + condition;
            }
            var selectCommand = string.Format("SELECT * FROM [MobileManage].[dbo].[员工] {0}", selectCondition);//组合选择语句
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
                                    Worker worker = new Worker();
                                    if (!string.IsNullOrEmpty(sdr["Id"].ToString()))
                                    {
                                        worker.Id = new Guid(sdr["Id"].ToString());
                                        worker.WorkerName = sdr["用户名"].ToString();
                                    }
                                    list.Add(worker);
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

        #region 客户端服务端共用
        [WebMethod]
        //获取网点用户或员工具有的功能
        public List<SystemFunction> GetUserFunction(string userId, string sessionId)
        {
            var list = new List<SystemFunction>();
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return list;
            }
            //解密
            userId = NetSecurity.decrypt(userId);


            var selectCommand = string.Format("SELECT * FROM  [MobileManage].[dbo].[系统功能] AS F  left join  [MobileManage].[dbo].[员工_功能_映射表] AS A on F.Id=A.系统功能Id   WHERE a.员工Id='{0}'", userId);//组合选择语句
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
                                    var function = new SystemFunction
                                    {
                                        Id = new Guid(sdr["Id"].ToString()),
                                        FunctionName = sdr["功能名称"].ToString(),
                                        FunctionPictureName = sdr["功能图片"].ToString(),
                                        FunctionNamespace = sdr["功能命名空间"].ToString(),
                                        FunctionScope = sdr["功能作用域"].ToString(),
                                        Right = Convert.ToInt32(sdr["权值"])

                                    };

                                    list.Add(function);
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
            return list.OrderByDescending(x => x.Right).ToList();
        }

        [WebMethod]
        //提取返款记录未结算列表
        public List<ReturnedItem> GetReturnRecord(int top, string condition, string sessionId)
        {
            var list = new List<ReturnedItem>();
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return list;
            }
            //解密
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
            var selectCommand = string.Format("SELECT {0} * FROM [MobileManage].[dbo].[返款未结算记录] {1}", topMessage, selectCondition);//组合选择语句
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
                                    var returnedItem = new ReturnedItem
                                    {
                                        Id = new Guid(sdr["Id"].ToString()),
                                        userId = new Guid(sdr["网点用户Id"].ToString()),
                                        returnType = sdr["返款类型"].ToString(),
                                        operationId = new Guid(sdr["对应业务操作Id"].ToString()),
                                        money = Convert.ToDouble(sdr["处理金额"].ToString()),
                                        returnPoint = Convert.ToDouble(sdr["即时返款比例"].ToString()),
                                        returnMoney = Convert.ToDouble(sdr["返款金额"].ToString()),
                                        datetime = Convert.ToDateTime(sdr["处理时间"].ToString())
                                    };

                                    list.Add(returnedItem);
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
        //提取返款记录已结算列表
        public List<ReturnedItem> GetReturnRecordDeal(int top, string condition, string sessionId)
        {
            List<ReturnedItem> list = new List<ReturnedItem>();
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return list;
            }
            //解密
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
            var selectCommand = string.Format("SELECT {0} * FROM [MobileManage].[dbo].[返款已结算记录] {1}", topMessage, selectCondition);//组合选择语句
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
                                    var returnedItem = new ReturnedItem
                                    {
                                        Id = new Guid(sdr["Id"].ToString()),
                                        userId = new Guid(sdr["网点用户Id"].ToString()),
                                        returnType = sdr["返款类型"].ToString(),
                                        operationId = new Guid(sdr["对应业务操作Id"].ToString()),
                                        money = Convert.ToDouble(sdr["处理金额"].ToString()),
                                        returnPoint = Convert.ToDouble(sdr["即时返款比例"].ToString()),
                                        returnMoney = Convert.ToDouble(sdr["返款金额"].ToString()),
                                        datetime = Convert.ToDateTime(sdr["返款时间"].ToString())
                                    };

                                    list.Add(returnedItem);
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

        //获取账户充值记录
        [WebMethod]
        public List<AcountPaymentItem> GetAcountPaymentRecord(int top, string condition, string sessionId)
        {
            var list = new List<AcountPaymentItem>();
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return list;
            }
            //解密
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
            var selectCommand = string.Format("SELECT {0} * FROM [MobileManage].[dbo].[用户充值汇总] {1}", topMessage, selectCondition);//组合选择语句
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
                                    var acountPaymentItem = new AcountPaymentItem
                                    {
                                        Id = new Guid(sdr["Id"].ToString()),
                                        userId = new Guid(sdr["网点用户Id"].ToString()),
                                        userName = sdr["网点用户姓名"].ToString(),
                                        workerId = sdr["员工Id"].Equals(DBNull.Value) ? Guid.Empty : new Guid(sdr["员工Id"].ToString()),
                                        workName = sdr["处理人"].ToString(),
                                        acountName = sdr["账户名称"].ToString(),
                                        payMoney = float.Parse(sdr["充值金额"].ToString()),
                                        payType = sdr["充值方式"].ToString(),
                                        bankName = sdr["充值银行名称"].ToString(),
                                        subBankName = sdr["支行名称"].ToString(),
                                        payTime = Convert.ToDateTime(sdr["充值时间"].ToString()),
                                        content = sdr["备注信息"].ToString(),
                                        isCheck = Convert.ToBoolean(sdr["是否划账"].ToString()),
                                        state = sdr["状态"].ToString(),
                                        userType = sdr["客户端类型"].Equals(DBNull.Value) ? "联通电信客户端" : sdr["客户端类型"].ToString()
                                    };

                                    list.Add(acountPaymentItem);
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
        //员工登录服务，返回员工信息
        public Worker WorkerLogin(string username, string password, string ip, string mac, string cpu)
        {

            //解密
            username = NetSecurity.decrypt(username);
            password = NetSecurity.decrypt(password);
            ip = NetSecurity.decrypt(ip);
            mac = NetSecurity.decrypt(mac);
            cpu = NetSecurity.decrypt(cpu);

            Worker loginer = null;
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_员工登录";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;
                        var sp1 = new SqlParameter("@用户名", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = username };
                        cmd.Parameters.Add(sp1);


                        var sp2 = new SqlParameter("@密码", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = password };
                        cmd.Parameters.Add(sp2);


                        var sp3 = new SqlParameter("@IP地址", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = ip };
                        cmd.Parameters.Add(sp3);


                        var sp4 = new SqlParameter("@MAC地址", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = mac };
                        cmd.Parameters.Add(sp4);

                        var sp5 = new SqlParameter("@CPU编号", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = cpu };
                        cmd.Parameters.Add(sp5);




                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("1"))
                        {
                            using (var cmd2 = new SqlCommand())
                            {
                                cmd2.CommandText = string.Format("select *  from 员工 Where [用户名] = '{0}' and [密码] = '{1}'", username, password);
                                cmd2.CommandType = CommandType.Text;
                                cmd2.Connection = con;

                                using (SqlDataReader sdr = cmd2.ExecuteReader())
                                {

                                    if (sdr.HasRows)
                                    {
                                        loginer = new Worker();//新建员工对象
                                        while (sdr.Read())
                                        {
                                            loginer.Id = new Guid(sdr["Id"].ToString());
                                            loginer.WorkerName = sdr["用户名"].ToString();
                                            loginer.Password = sdr["密码"].ToString();
                                            loginer.MAC_Address = sdr["MAC地址"].ToString();
                                            loginer.CPU_Code = sdr["CPU编号"].ToString();
                                            loginer.Telephone = sdr["移动电话"].ToString();
                                            loginer.RealName = sdr["真实姓名"].ToString();
                                            loginer.WorkerType = sdr["员工类型"].ToString();
                                        }
                                        sdr.Close();
                                        using (var cmd3 = new SqlCommand())
                                        {
                                            cmd3.CommandText = "Proc_SYS_Session_Insert";
                                            cmd3.CommandType = CommandType.StoredProcedure;
                                            cmd3.Connection = con;

                                            var id = Guid.NewGuid();


                                            var ssp1 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = id };
                                            cmd3.Parameters.Add(ssp1);

                                            var ssp2 = new SqlParameter("@创建时间", SqlDbType.DateTime) { Direction = ParameterDirection.Input, Value = DateTime.Now };
                                            cmd3.Parameters.Add(ssp2);

                                            var ssp3 = new SqlParameter("@创建用户Id", SqlDbType.UniqueIdentifier);
                                            ssp3.Direction = ParameterDirection.Input;
                                            cmd3.Parameters.Add(ssp3);
                                            ssp3.Value = loginer.Id;

                                            cmd3.ExecuteNonQuery();

                                            loginer.SessionId = id;//SessionId赋值
                                        }

                                    }
                                }
                            }

                        }

                    }

                    return loginer;
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
        //员工退出登录服务
        public string WorkerLoginOut(string userId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return null;
            }
            //解密
            userId = NetSecurity.decrypt(userId);
            sessionId = NetSecurity.decrypt(sessionId);
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_员工退出";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;
                        var sp1 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(userId) };
                        cmd.Parameters.Add(sp1);


                        var sp2 = new SqlParameter("@SessionId", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(sessionId) };
                        cmd.Parameters.Add(sp2);


                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("1"))
                        {
                            return "退出成功";
                        }
                        else
                        {
                            return "退出失败";
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
        //员工修改密码
        public string UpdateWorkerPassword(string userId, string oldpassword, string newPassword, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return "非法登录!";
            }
            //解密
            userId = NetSecurity.decrypt(userId);
            oldpassword = NetSecurity.decrypt(oldpassword);
            newPassword = NetSecurity.decrypt(newPassword);

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();
                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = string.Format("select *  from 员工 Where [Id] = '{0}' and [密码] = '{1}'", userId, oldpassword);
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;
                        using (SqlDataReader sdr = cmd.ExecuteReader())
                        {
                            if (sdr.HasRows)
                            {
                                sdr.Close();
                                using (var cmd2 = new SqlCommand())
                                {
                                    cmd2.CommandText = "Function_服务端_员工修改密码";
                                    cmd2.CommandType = CommandType.StoredProcedure;
                                    cmd2.Connection = con;

                                    var sp1 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(userId) };
                                    cmd2.Parameters.Add(sp1);


                                    var sp2 = new SqlParameter("@密码", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = newPassword };
                                    cmd2.Parameters.Add(sp2);


                                    cmd2.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                                    cmd2.ExecuteNonQuery();
                                    var res = cmd2.Parameters["@RETURN_VALUE"].Value.ToString();
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
                            else
                            {
                                return "原密码输入错误！请重试！";
                            }
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
        //按条件获取员工列表，条件为空时获取所有员工
        public List<Worker> GetWorkerList(string condition, string sessionId)
        {
            var list = new List<Worker>();
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return list;
            }
            //解密
            condition = NetSecurity.decrypt(condition);

            string selectCondition = "";
            if (!string.IsNullOrEmpty(condition))
            {
                selectCondition = "Where " + condition;
            }
            var selectCommand = string.Format("SELECT * FROM [MobileManage].[dbo].[员工] {0}", selectCondition);//组合选择语句
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
                                    var worker = new Worker
                                    {
                                        Id = new Guid(sdr["Id"].ToString()),
                                        WorkerName = sdr["用户名"].ToString(),
                                        Password = sdr["密码"].ToString(),
                                        MAC_Address = sdr["MAC地址"].ToString(),
                                        CPU_Code = sdr["CPU编号"].ToString(),
                                        Telephone = sdr["移动电话"].ToString(),
                                        RealName = sdr["真实姓名"].ToString(),
                                        WorkerType = sdr["员工类型"].ToString()
                                    };

                                    list.Add(worker);
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
        //新增员工
        public string AddWorker(Worker worker, string userId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return "非法登录!";
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
                        cmd.CommandText = "Function_服务端_新增员工";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp1 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = Guid.NewGuid() };
                        cmd.Parameters.Add(sp1);


                        var sp2 = new SqlParameter("@用户名", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = worker.WorkerName };
                        cmd.Parameters.Add(sp2);

                        var sp3 = new SqlParameter("@密码", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = worker.Password };
                        cmd.Parameters.Add(sp3);

                        var sp4 = new SqlParameter("@MAC地址", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = string.IsNullOrEmpty(worker.MAC_Address) ? (object)DBNull.Value : worker.MAC_Address };
                        cmd.Parameters.Add(sp4);

                        var sp5 = new SqlParameter("@CPU编号", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = string.IsNullOrEmpty(worker.CPU_Code) ? (object)DBNull.Value : worker.CPU_Code };
                        cmd.Parameters.Add(sp5);

                        var sp6 = new SqlParameter("@移动电话", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = string.IsNullOrEmpty(worker.Telephone) ? (object)DBNull.Value : worker.Telephone };
                        cmd.Parameters.Add(sp6);

                        var sp7 = new SqlParameter("@真实姓名", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = string.IsNullOrEmpty(worker.RealName) ? (object)DBNull.Value : worker.RealName };
                        cmd.Parameters.Add(sp7);

                        var sp8 = new SqlParameter("@员工类型", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = worker.WorkerType };
                        cmd.Parameters.Add(sp8);

                        var sp9 = new SqlParameter("@操作者Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(userId) };
                        cmd.Parameters.Add(sp9);


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
        //修改员工
        public string UpdateWorker(Worker worker, string userId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return "非法登录!";
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
                        cmd.CommandText = "Function_服务端_修改员工";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp1 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = worker.Id };
                        cmd.Parameters.Add(sp1);

                        var sp2 = new SqlParameter("@用户名", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = worker.WorkerName };
                        cmd.Parameters.Add(sp2);

                        var sp3 = new SqlParameter("@密码", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = worker.Password };
                        cmd.Parameters.Add(sp3);

                        var sp4 = new SqlParameter("@MAC地址", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = string.IsNullOrEmpty(worker.MAC_Address) ? (object)DBNull.Value : worker.MAC_Address };
                        cmd.Parameters.Add(sp4);

                        var sp5 = new SqlParameter("@CPU编号", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = string.IsNullOrEmpty(worker.CPU_Code) ? (object)DBNull.Value : worker.CPU_Code };
                        cmd.Parameters.Add(sp5);

                        var sp6 = new SqlParameter("@移动电话", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = string.IsNullOrEmpty(worker.Telephone) ? (object)DBNull.Value : worker.Telephone };
                        cmd.Parameters.Add(sp6);

                        var sp7 = new SqlParameter("@真实姓名", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = string.IsNullOrEmpty(worker.RealName) ? (object)DBNull.Value : worker.RealName };
                        cmd.Parameters.Add(sp7);

                        var sp8 = new SqlParameter("@员工类型", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = worker.WorkerType };
                        cmd.Parameters.Add(sp8);

                        var sp9 = new SqlParameter("@操作者Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(userId) };
                        cmd.Parameters.Add(sp9);


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
        //删除员工
        public string DeleteWorker(Worker worker, string userId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return "非法登录!";
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
                        cmd.CommandText = "Function_服务端_删除员工";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp1 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = worker.Id };
                        cmd.Parameters.Add(sp1);


                        var sp2 = new SqlParameter("@操作者Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(userId) };
                        cmd.Parameters.Add(sp2);


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
        //根据条件获取网点用户列表
        public List<User> GetUserList(string condition, string sessionId)
        {

            var list = new List<User>();
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return list;
            }

            //解密
            condition = NetSecurity.decrypt(condition);

            string selectCondition = "";
            if (!string.IsNullOrEmpty(condition))
            {
                selectCondition = "Where " + condition;
            }
            var selectCommand = string.Format("SELECT * FROM [MobileManage].[dbo].[网点用户] {0}", selectCondition);//组合选择语句
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
                                    var user = new User();
                                    if (sdr["Id"] != null)
                                        user.Id = new Guid(sdr["Id"].ToString());
                                    if (sdr["登陆名"] != null)
                                        user.loggingName = sdr["登陆名"].ToString();
                                    if (sdr["密码"] != null)
                                        user.password = sdr["密码"].ToString();
                                    if (sdr["账户余额"] != null)
                                        user.money = float.Parse(sdr["账户余额"].ToString());
                                    if (sdr["MAC地址"] != null)
                                        user.mac = sdr["MAC地址"].ToString();
                                    if (sdr["固定电话"] != null)
                                        user.tel = sdr["固定电话"].ToString();
                                    if (sdr["地址"] != null)
                                        user.address = sdr["地址"].ToString();
                                    if (sdr["店名"] != null)
                                        user.shopName = sdr["店名"].ToString();
                                    if (sdr["移动电话"] != null)
                                        user.mobilePhone = sdr["移动电话"].ToString();
                                    if (sdr["真实姓名拼音"] != null)
                                        user.pingying = sdr["真实姓名拼音"].ToString();
                                    if (sdr["真实姓名"] != null)
                                        user.realName = sdr["真实姓名"].ToString();
                                    if (sdr["身份证号"] != null)
                                        user.indentityNo = sdr["身份证号"].ToString();
                                    if (sdr["业务负责人Id"].ToString() != "")
                                    {
                                        string guid_str = sdr["业务负责人Id"].ToString();
                                        user.manager_id = new Guid(guid_str);
                                    }
                                    if (sdr["业务负责人"] != null)
                                        user.managerName = sdr["业务负责人"].ToString();
                                    if (sdr["存款尾数"] != null)
                                        user.moneyTail = sdr["存款尾数"].ToString();
                                    if (sdr["用户级别"] != null)
                                        user.level = sdr["用户级别"].ToString();
                                    if (sdr["注册时间"].ToString() != "")
                                        user.registerDatetime = DateTime.Parse(sdr["注册时间"].ToString());
                                    if (sdr["是否审核"] != null)
                                        user.isValidate = bool.Parse(sdr["是否审核"].ToString());
                                    if (sdr["客户端类型"] != null)
                                        user.userType = sdr["客户端类型"].ToString();
                                    else
                                        user.userType = "联通电信客户端";

                                    list.Add(user);
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
        //服务端插入网点用户
        public string InsertUser(User user, string userId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return "非法登录!";
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
                        cmd.CommandText = "select * from 网点用户 Where [登陆名] = '" + user.loggingName + "'";
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;
                        using (SqlDataReader sdr = cmd.ExecuteReader()) // cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {
                                    return "用户名已经存在！请更换用户名";
                                }
                            }
                            sdr.Close();
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
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_新增网点用户";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;
                        cmd.Parameters.Clear();

                        var sp1 = new SqlParameter("@登陆名", SqlDbType.NVarChar, 50);
                        sp1.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp1);
                        sp1.Value = user.loggingName;

                        var sp2 = new SqlParameter("@密码", SqlDbType.NVarChar, 50);
                        sp2.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp2);
                        sp2.Value = user.password;

                        var sp18 = new SqlParameter("@账户余额", SqlDbType.Money);
                        sp18.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp18);
                        sp18.Value = user.money;

                        var sp3 = new SqlParameter("@MAC地址", SqlDbType.NVarChar, 50);
                        sp3.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp3);
                        sp3.Value = user.mac;

                        var sp4 = new SqlParameter("@固定电话", SqlDbType.NVarChar, 50);
                        sp4.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp4);
                        sp4.Value = user.tel;

                        var sp5 = new SqlParameter("@地址", SqlDbType.NVarChar, 50);
                        sp5.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp5);
                        sp5.Value = user.address;

                        var sp6 = new SqlParameter("@店名", SqlDbType.NVarChar, 50);
                        sp6.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp6);
                        sp6.Value = user.shopName;

                        var sp7 = new SqlParameter("@移动电话", SqlDbType.NVarChar, 50);
                        sp7.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp7);
                        sp7.Value = user.mobilePhone;

                        var sp8 = new SqlParameter("@真实姓名拼音", SqlDbType.NVarChar, 50);
                        sp8.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp8);
                        sp8.Value = ChineseToPingYing.GetSpell(user.realName); ;

                        var sp9 = new SqlParameter("@真实姓名", SqlDbType.NVarChar, 50);
                        sp9.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp9);
                        sp9.Value = user.realName;

                        var sp10 = new SqlParameter("@身份证号", SqlDbType.NVarChar, 50);
                        sp10.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp10);
                        sp10.Value = user.indentityNo;

                        var sp11 = new SqlParameter("@业务负责人Id", SqlDbType.UniqueIdentifier);
                        sp11.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp11);
                        sp11.Value = user.manager_id;

                        var sp12 = new SqlParameter("@业务负责人", SqlDbType.NVarChar, 50);
                        sp12.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp12);
                        sp12.Value = user.managerName;

                        var sp13 = new SqlParameter("@存款尾数", SqlDbType.NVarChar, 50);
                        sp13.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp13);
                        sp13.Value = user.moneyTail;

                        var sp14 = new SqlParameter("@用户级别", SqlDbType.NVarChar, 50);
                        sp14.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp14);
                        sp14.Value = user.level;

                        var sp16 = new SqlParameter("@客户端类型", SqlDbType.NVarChar, 50);
                        sp16.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp16);
                        sp16.Value = user.userType;


                        var sp15 = new SqlParameter("@操作者Id", SqlDbType.UniqueIdentifier);
                        sp15.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp15);
                        sp15.Value = new Guid(userId);

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
        //服务端修改网点用户
        public string UpdateUser(User user, string userId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return "非法登录!";
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
                        cmd.CommandText = "Function_服务端_修改网点用户";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;
                        cmd.Parameters.Clear();


                        var sp0 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier);
                        sp0.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp0);
                        sp0.Value = user.Id;

                        var sp1 = new SqlParameter("@登陆名", SqlDbType.NVarChar, 50);
                        sp1.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp1);
                        sp1.Value = user.loggingName;

                        var sp2 = new SqlParameter("@密码", SqlDbType.NVarChar, 50);
                        sp2.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp2);
                        sp2.Value = user.password;


                        var sp18 = new SqlParameter("@账户余额", SqlDbType.Money);
                        sp18.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp18);
                        sp18.Value = user.money;

                        var sp3 = new SqlParameter("@MAC地址", SqlDbType.NVarChar, 50);
                        sp3.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp3);
                        sp3.Value = user.mac;

                        var sp4 = new SqlParameter("@固定电话", SqlDbType.NVarChar, 50);
                        sp4.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp4);
                        sp4.Value = user.tel;

                        var sp5 = new SqlParameter("@地址", SqlDbType.NVarChar, 50);
                        sp5.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp5);
                        sp5.Value = user.address;

                        var sp6 = new SqlParameter("@店名", SqlDbType.NVarChar, 50);
                        sp6.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp6);
                        sp6.Value = user.shopName;

                        var sp7 = new SqlParameter("@移动电话", SqlDbType.NVarChar, 50);
                        sp7.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp7);
                        sp7.Value = user.mobilePhone;

                        var sp8 = new SqlParameter("@真实姓名拼音", SqlDbType.NVarChar, 50);
                        sp8.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp8);
                        sp8.Value = ChineseToPingYing.GetSpell(user.realName); ;

                        var sp9 = new SqlParameter("@真实姓名", SqlDbType.NVarChar, 50);
                        sp9.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp9);
                        sp9.Value = user.realName;

                        var sp10 = new SqlParameter("@身份证号", SqlDbType.NVarChar, 50);
                        sp10.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp10);
                        sp10.Value = user.indentityNo;

                        var sp11 = new SqlParameter("@业务负责人Id", SqlDbType.UniqueIdentifier);
                        sp11.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp11);
                        sp11.Value = user.manager_id;

                        var sp12 = new SqlParameter("@业务负责人", SqlDbType.NVarChar, 50);
                        sp12.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp12);
                        sp12.Value = user.managerName;

                        var sp13 = new SqlParameter("@存款尾数", SqlDbType.NVarChar, 50);
                        sp13.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp13);
                        sp13.Value = user.moneyTail;

                        var sp14 = new SqlParameter("@用户级别", SqlDbType.NVarChar, 50);
                        sp14.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp14);
                        sp14.Value = user.level;

                        var sp15 = new SqlParameter("@注册时间", SqlDbType.DateTime);
                        sp15.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp15);
                        sp15.Value = user.registerDatetime;

                        var sp16 = new SqlParameter("@是否审核", SqlDbType.Bit);
                        sp16.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp16);
                        sp16.Value = user.isValidate;

                        var sp19 = new SqlParameter("@客户端类型", SqlDbType.NVarChar, 50);
                        sp19.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp19);
                        sp19.Value = user.userType;

                        var sp17 = new SqlParameter("@操作者Id", SqlDbType.UniqueIdentifier);
                        sp17.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp17);
                        sp17.Value = new Guid(userId);

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
        //服务端删除网点用户
        public string DeleteUser(User user, string userId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return "非法登录!";
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
                        cmd.CommandText = "Function_服务端_删除网点用户";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp1 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = user.Id };
                        cmd.Parameters.Add(sp1);


                        var sp2 = new SqlParameter("@操作者Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(userId) };
                        cmd.Parameters.Add(sp2);


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
        //服务端获取网点用户修改其基本信息的申请
        public List<User> GetUserUpdateInformation(string condition, string sessionId)
        {
            var list = new List<User>();
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return list;
            }
            //解密
            condition = NetSecurity.decrypt(condition);
            string selectCondition = "";
            if (!string.IsNullOrEmpty(condition))
            {
                selectCondition = "Where " + condition;
            }
            var selectCommand = string.Format("SELECT * FROM [MobileManage].[dbo].[网点用户_修改临时表] {0}", selectCondition);//组合选择语句
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
                                    var user = new User();
                                    if (sdr["Id"] != null)
                                        user.Id = new Guid(sdr["Id"].ToString());
                                    if (sdr["固定电话"] != null)
                                        user.tel = sdr["固定电话"].ToString();
                                    if (sdr["地址"] != null)
                                        user.address = sdr["地址"].ToString();
                                    if (sdr["店名"] != null)
                                        user.shopName = sdr["店名"].ToString();
                                    if (sdr["移动电话"] != null)
                                        user.mobilePhone = sdr["移动电话"].ToString();
                                    if (sdr["真实姓名拼音"] != null)
                                        user.pingying = sdr["真实姓名拼音"].ToString();
                                    if (sdr["真实姓名"] != null)
                                        user.realName = sdr["真实姓名"].ToString();
                                    if (sdr["身份证号"] != null)
                                        user.indentityNo = sdr["身份证号"].ToString();
                                    if (sdr["业务负责人Id"].ToString() != "")
                                    {
                                        string guid_str = sdr["业务负责人Id"].ToString();
                                        user.manager_id = new Guid(guid_str);
                                    }
                                    if (sdr["业务负责人"] != null)
                                        user.managerName = sdr["业务负责人"].ToString();
                                    if (sdr["存款尾数"] != null)
                                        user.moneyTail = sdr["存款尾数"].ToString();
                                    list.Add(user);
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
        //服务端审核网点用户修改信息
        public string ExamineUserInfo(string clientId, int operateNum, string userId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return "非法登录!";
            }
            //解密
            clientId = NetSecurity.decrypt(clientId);
            userId = NetSecurity.decrypt(userId);

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_审核网点用户所修改的信息";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp1 = new SqlParameter("@网点用户Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(clientId) };
                        cmd.Parameters.Add(sp1);

                        var sp2 = new SqlParameter("@操作类型", SqlDbType.Int) { Direction = ParameterDirection.Input, Value = operateNum };
                        cmd.Parameters.Add(sp2);

                        var sp3 = new SqlParameter("@操作者Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(userId) };
                        cmd.Parameters.Add(sp3);


                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();
                        if (res.Equals("1"))
                        {
                            if (operateNum == 1)
                                return "网店用户修改信息已被允许";
                            else
                                return "网店用户修改信息已被拒绝";
                        }
                        else
                        {
                            return "数据库操作失败";
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
        //锁定用户充值信息
        public bool LockAcountPayment(string acountpaymentId, string workerId, string workerName, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return false;
            }
            //解密
            workerId = NetSecurity.decrypt(workerId);
            acountpaymentId = NetSecurity.decrypt(acountpaymentId);
            workerName = NetSecurity.decrypt(workerName);

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_更改充值状态为锁定_员工";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp1 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(acountpaymentId) };
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
        //充值信息审核成功
        public bool AcountPaymentSuccess(string acountpaymentId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return false;
            }

            //解密
            acountpaymentId = NetSecurity.decrypt(acountpaymentId);


            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_账户充值成功";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp1 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(acountpaymentId) };
                        cmd.Parameters.Add(sp1);

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
        //充值信息审核失败
        public bool AcountPaymentFailed(string acountpaymentId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return false;
            }
            //解密
            acountpaymentId = NetSecurity.decrypt(acountpaymentId);

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_账户充值失败";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp1 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(acountpaymentId) };
                        cmd.Parameters.Add(sp1);

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



        #endregion
        */
    }
}
