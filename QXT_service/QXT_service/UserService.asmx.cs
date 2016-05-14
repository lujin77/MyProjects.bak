using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services;
using System.Data.SqlClient;
using QXT_service.Util;
using System.Data;
using QXT_service.Entity;
using System.Web.Services.Protocols;
using System.IO;

namespace QXT_service
{
    /// <summary>
    /// UserService 的摘要说明
    /// </summary>
    [WebService(Namespace = "http://tempuri.org/")]
    [WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
    [System.ComponentModel.ToolboxItem(false)]
    // 若要允许使用 ASP.NET AJAX 从脚本中调用此 Web 服务，请取消对下行的注释。
    // [System.Web.Script.Services.ScriptService]
    public class UserService : System.Web.Services.WebService
    {

        public AuthenticationInfo authenticationInfo; ////定义用户身份验证类变量header 

        [WebMethod]
        public string Register(string userid, string password, string name, string sex, string mobile, string tel, string qq, string email, string com_name, string com_addr)
        {
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_网点用户_注册";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp0 = new SqlParameter("@用户名", SqlDbType.NVarChar, 50);
                        sp0.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp0);
                        sp0.Value = userid;

                        var sp1 = new SqlParameter("@密码", SqlDbType.NVarChar, 50);
                        sp1.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp1);
                        sp1.Value = password;

                        var sp2 = new SqlParameter("@真实姓名", SqlDbType.NVarChar, 20);
                        sp2.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp2);
                        sp2.Value = name;

                        var sp3 = new SqlParameter("@性别", SqlDbType.NVarChar, 4);
                        sp3.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp3);
                        sp3.Value = sex;

                        var sp4 = new SqlParameter("@手机号码", SqlDbType.NVarChar, 15);
                        sp4.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp4);
                        sp4.Value = mobile;

                        var sp5 = new SqlParameter("@公司电话", SqlDbType.NVarChar, 15);
                        sp5.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp5);
                        sp5.Value = tel;

                        var sp6 = new SqlParameter("@QQ", SqlDbType.NVarChar, 20);
                        sp6.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp6);
                        sp6.Value = qq;

                        var sp7 = new SqlParameter("@Email", SqlDbType.VarChar, 50);
                        sp7.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp7);
                        sp7.Value = email;

                        var sp8 = new SqlParameter("@公司名称", SqlDbType.NVarChar, 20);
                        sp8.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp8);
                        sp8.Value = com_name;

                        var sp9 = new SqlParameter("@公司地址", SqlDbType.NVarChar, 50);
                        sp9.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp9);
                        sp9.Value = com_addr;

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("0"))
                        {
                            return "注册成功！\n请等待管理员审核...";
                        }
                        else if (res.Equals("1"))
                        {
                            return "用户名已存在！\n请更换用户名";
                        }
                        else
                        {
                            return "系统错误！\n请联系管理员, code=" + res;
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
        public User Login(string userid, string password)
        {
            User user = new User();

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        var selectCommand = string.Format("SELECT * FROM 用户 where 用户名='{0}' and 密码='{1}'", userid, password);//组合选择语句
                        cmd.CommandText = selectCommand;
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;
                        using (SqlDataReader sdr = cmd.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {
                                    user.id = new Guid(sdr["id"].ToString());
                                    user.userid = sdr["用户名"].ToString();
                                    user.psw = sdr["密码"].ToString();
                                    user.name = sdr["真实姓名"].ToString();
                                    user.sex = sdr["性别"].ToString();
                                    user.mobile = sdr["手机号"].ToString();
                                    user.tel = sdr["公司电话"].ToString();
                                    user.qq = sdr["QQ"].ToString();
                                    user.email = sdr["Email"].ToString();
                                    user.com_name = sdr["公司名称"].ToString();
                                    user.com_addr = sdr["公司地址"].ToString();
                                    user.state = sdr["账号状态"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["短信条数"].ToString()))
                                        user.sms = Convert.ToInt32(sdr["短信条数"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["彩信条数"].ToString()))
                                        user.msms = Convert.ToInt32(sdr["彩信条数"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["回复条数"].ToString()))
                                        user.reply = Convert.ToInt32(sdr["回复条数"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["业务负责人id"].ToString()))
                                        user.manager_id = new Guid(sdr["业务负责人id"].ToString());
                                    user.sms_sign = sdr["短信签名"].ToString();
                                }

                            }
                        }
                    }
                    return user;
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
        public Account getAccount(string userid, string password)
        {
            Account account = new Account();

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        var selectCommand = string.Format("SELECT * FROM 用户 where 用户名='{0}' and 密码='{1}'", userid, password);//组合选择语句
                        cmd.CommandText = selectCommand;
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;
                        using (SqlDataReader sdr = cmd.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {
         
                                    if (!string.IsNullOrEmpty(sdr["短信条数"].ToString()))
                                        account.sms = Convert.ToInt32(sdr["短信条数"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["彩信条数"].ToString()))
                                        account.msms = Convert.ToInt32(sdr["彩信条数"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["回复条数"].ToString()))
                                        account.reply = Convert.ToInt32(sdr["回复条数"].ToString());
                                }

                            }
                        }
                    }
                    return account;
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
        public string UpdateUser(string id, string userid, string name, string sex, string mobile, string tel, string qq, string email, string com_name, string com_addr, string token)
        {
            if (!Authentication.Check(token))
            {
                return "无权限操作！";

            }

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        var selectCommand = "Function_网点用户_修改信息";
                        cmd.CommandText = selectCommand;
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp = new SqlParameter("@用户id", SqlDbType.UniqueIdentifier);
                        sp.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp);
                        sp.Value = new Guid(id);

                        var sp0 = new SqlParameter("@用户名", SqlDbType.NVarChar, 50);
                        sp0.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp0);
                        sp0.Value = userid;

                        var sp2 = new SqlParameter("@真实姓名", SqlDbType.NVarChar, 20);
                        sp2.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp2);
                        sp2.Value = name;

                        var sp3 = new SqlParameter("@性别", SqlDbType.NVarChar, 4);
                        sp3.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp3);
                        sp3.Value = sex;

                        var sp4 = new SqlParameter("@手机号码", SqlDbType.NVarChar, 15);
                        sp4.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp4);
                        sp4.Value = mobile;

                        var sp5 = new SqlParameter("@公司电话", SqlDbType.NVarChar, 15);
                        sp5.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp5);
                        sp5.Value = tel;

                        var sp6 = new SqlParameter("@QQ", SqlDbType.NVarChar, 20);
                        sp6.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp6);
                        sp6.Value = qq;

                        var sp7 = new SqlParameter("@Email", SqlDbType.VarChar, 50);
                        sp7.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp7);
                        sp7.Value = email;

                        var sp8 = new SqlParameter("@公司名称", SqlDbType.NVarChar, 20);
                        sp8.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp8);
                        sp8.Value = com_name;

                        var sp9 = new SqlParameter("@公司地址", SqlDbType.NVarChar, 50);
                        sp9.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp9);
                        sp9.Value = com_addr;

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("0"))
                        {
                            return "用户信息修改成功！";
                        }
                        else
                        {
                            return "系统错误！\n请联系管理员, code=" + res;
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
        public string UpdatePsw(string id, string userid, string psw, string token)
        {
            if (!Authentication.Check(token))
            {
                return "无权限操作！";

            }

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        var selectCommand = "Function_网点用户_修改密码";
                        cmd.CommandText = selectCommand;
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp = new SqlParameter("@用户id", SqlDbType.UniqueIdentifier);
                        sp.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp);
                        sp.Value = new Guid(id);

                        var sp0 = new SqlParameter("@用户名", SqlDbType.NVarChar, 50);
                        sp0.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp0);
                        sp0.Value = userid;

                        var sp2 = new SqlParameter("@密码", SqlDbType.NVarChar, 50);
                        sp2.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp2);
                        sp2.Value = psw;

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("0"))
                        {
                            return "密码修改成功！";
                        }
                        else
                        {
                            return "系统错误！\n请联系管理员, code=" + res;
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
        public string UpdateSign(string id, string sign, string token)
        {
            if (!Authentication.Check(token))
            {
                return "无权限操作！";

            }

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        var selectCommand = string.Format("update 用户 set [短信签名]='{0}' where id='{1}'", sign, id);
                        cmd.CommandText = selectCommand;
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;

                        int ret = cmd.ExecuteNonQuery();
                        if (ret == 1)
                        {
                            return "修改签名成功！";
                        }
                        else
                        {
                            return "系统错误！";
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
        public string ExportExcel(string user_id, string condition, string token)
        {
            if (!Authentication.Check(token))
            {
                return "无权限操作！";

            }

            if (!string.IsNullOrEmpty(condition))
            {
                condition = " where " + condition;
            }

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        var selectCommand = string.Format("select [姓名],[手机号],[固定电话],[Email],[生日],[单位],[地址],[备注] from  [QXT_platform].[dbo].[通信录] {0} ", condition);
                        cmd.CommandText = selectCommand;
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;

                        DataSet ds = new DataSet();
                        SqlDataAdapter da = new SqlDataAdapter(cmd);
                        da.Fill(ds);

                        string filePath = Server.MapPath("File/") + user_id + ".xls";
                        //如果已经存在，则删除
                        if (File.Exists(filePath))
                        {
                            File.Delete(filePath);
                        }

                        ExcelExporter.ExportDataTableToExcel(ds.Tables[0], filePath);

                        return "生成成功！";

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
        public string AddGroup(string id, string userid, string groupName, string content, string contract_user_id, string token)
        {
            if (!Authentication.Check(token))
            {
                return "无权限操作！";

            }

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        var selectCommand = "Function_网点用户_添加联系组";
                        cmd.CommandText = selectCommand;
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp = new SqlParameter("@用户id", SqlDbType.UniqueIdentifier);
                        sp.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp);
                        sp.Value = new Guid(id);

                        var sp0 = new SqlParameter("@用户名", SqlDbType.NVarChar, 50);
                        sp0.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp0);
                        sp0.Value = userid;

                        var sp1 = new SqlParameter("@组名称", SqlDbType.NVarChar, 50);
                        sp1.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp1);
                        sp1.Value = groupName;

                        var sp2 = new SqlParameter("@备注", SqlDbType.Text);
                        sp2.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp2);
                        sp2.Value = content;

                        var sp3 = new SqlParameter("@关联用户Ids", SqlDbType.Text);
                        sp3.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp3);
                        sp3.Value = contract_user_id;

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("0"))
                        {
                            return "添加联系组成功！";
                        }
                        else
                        {
                            return "系统错误！\n请联系管理员, code=" + res;
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
        public string EditGroup(string id, string userid, string groupId, string groupName, string content, string contract_user_id, string token)
        {
            if (!Authentication.Check(token))
            {
                return "无权限操作！";

            }

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        var selectCommand = "Function_网点用户_编辑联系组";
                        cmd.CommandText = selectCommand;
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp = new SqlParameter("@用户id", SqlDbType.UniqueIdentifier);
                        sp.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp);
                        sp.Value = new Guid(id);

                        var sp0 = new SqlParameter("@用户名", SqlDbType.NVarChar, 50);
                        sp0.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp0);
                        sp0.Value = userid;

                        var sp0_1 = new SqlParameter("@联系组id", SqlDbType.UniqueIdentifier);
                        sp0_1.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp0_1);
                        sp0_1.Value = new Guid(groupId);

                        var sp1 = new SqlParameter("@组名称", SqlDbType.NVarChar, 50);
                        sp1.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp1);
                        sp1.Value = groupName;

                        var sp2 = new SqlParameter("@备注", SqlDbType.Text);
                        sp2.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp2);
                        sp2.Value = content;

                        var sp3 = new SqlParameter("@关联用户Ids", SqlDbType.Text);
                        sp3.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp3);
                        sp3.Value = contract_user_id;

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("0"))
                        {
                            return "编辑联系组成功！";
                        }
                        else
                        {
                            return "系统错误！\n请联系管理员, code=" + res;
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
        public string EditNoList(string id, string userid, string groupId, string groupName, string content, string tels, string shared_users, string token)
        {
            if (!Authentication.Check(token))
            {
                return "无权限操作！";

            }

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        var selectCommand = "Function_网点用户_编辑群发簿";
                        cmd.CommandText = selectCommand;
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp = new SqlParameter("@用户id", SqlDbType.UniqueIdentifier);
                        sp.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp);
                        sp.Value = new Guid(id);

                        var sp0 = new SqlParameter("@用户名", SqlDbType.NVarChar, 50);
                        sp0.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp0);
                        sp0.Value = userid;

                        var sp0_1 = new SqlParameter("@群发簿id", SqlDbType.UniqueIdentifier);
                        sp0_1.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp0_1);
                        sp0_1.Value = new Guid(groupId);

                        var sp1 = new SqlParameter("@群发簿名称", SqlDbType.NVarChar, 50);
                        sp1.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp1);
                        sp1.Value = groupName;

                        var sp2 = new SqlParameter("@备注", SqlDbType.Text);
                        sp2.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp2);
                        sp2.Value = content;

                        var sp3 = new SqlParameter("@号码", SqlDbType.Text);
                        sp3.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp3);
                        sp3.Value = tels;

                        var sp4 = new SqlParameter("@共享用户", SqlDbType.Text);
                        sp4.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp4);
                        sp4.Value = shared_users;

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("0"))
                        {
                            return "编辑群发薄成功！";
                        }
                        else
                        {
                            return "系统错误！\n请联系管理员, code=" + res;
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
        public string DeleteGroup(string id, string userid, string groupId, string deleteType, string token)
        {
            if (!Authentication.Check(token))
            {
                return "无权限操作！";

            }

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        var selectCommand = "Function_网点用户_删除联系组";
                        cmd.CommandText = selectCommand;
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp = new SqlParameter("@用户id", SqlDbType.UniqueIdentifier);
                        sp.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp);
                        sp.Value = new Guid(id);

                        var sp0 = new SqlParameter("@用户名", SqlDbType.NVarChar, 50);
                        sp0.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp0);
                        sp0.Value = userid;

                        var sp0_1 = new SqlParameter("@联系组id", SqlDbType.UniqueIdentifier);
                        sp0_1.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp0_1);
                        sp0_1.Value = new Guid(groupId);

                        var sp1 = new SqlParameter("@删除类型", SqlDbType.NVarChar, 50);
                        sp1.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp1);
                        sp1.Value = deleteType;

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("0"))
                        {
                            return deleteType + "成功！";
                        }
                        else
                        {
                            return "系统错误！\n请联系管理员, code=" + res;
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
        public string AddNoList(string id, string userid, string groupName, string content, string tels, string shared_user, string token)
        {
            if (!Authentication.Check(token))
            {
                return "无权限操作！";

            }

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        var selectCommand = "Function_网点用户_添加群发簿";
                        cmd.CommandText = selectCommand;
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp = new SqlParameter("@用户id", SqlDbType.UniqueIdentifier);
                        sp.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp);
                        sp.Value = new Guid(id);

                        var sp0 = new SqlParameter("@用户名", SqlDbType.NVarChar, 50);
                        sp0.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp0);
                        sp0.Value = userid;

                        var sp1 = new SqlParameter("@群发簿名称", SqlDbType.NVarChar, 50);
                        sp1.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp1);
                        sp1.Value = groupName;

                        var sp2 = new SqlParameter("@备注", SqlDbType.Text);
                        sp2.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp2);
                        sp2.Value = content;

                        var sp3 = new SqlParameter("@关联号码", SqlDbType.Text);
                        sp3.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp3);
                        sp3.Value = tels;

                        var sp4 = new SqlParameter("@共享用户", SqlDbType.NVarChar, 1000);
                        sp4.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp4);
                        sp4.Value = shared_user;

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("0"))
                        {
                            return "添加群发薄成功！";
                        }
                        else
                        {
                            return "系统错误！\n请联系管理员, code=" + res;
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
        public List<string> GetNoWithGroups(string group_id, string type, string token)
        {
            List<string> list = new List<string>();

            if (!Authentication.Check(token))
            {
                return null;

            }

            string colm = "";
            string table = "";
            string condition = "";

            if (type == "群发簿")
            {
                colm = "号码";
                table = "[QXT_platform].[dbo].[群发簿]";
            }
            else if (type == "联系组")
            {
                colm = "手机号";
                table = "[QXT_platform].[dbo].[View_通信录分组_录]";
            }
            else
            {
                return null;
            }

            string[] group_id_list = group_id.Split(',');

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        foreach (string item in group_id_list) 
                        {
                            if (type == "群发簿")
                            {
                                condition = "where 分组id='" + item + "'";
                            }
                            else if (type == "联系组")
                            {
                                condition = "where 组id='" + item + "'";

                            }

                            var selectCommand = string.Format("select {0} as tel from {1} {2}", colm, table, condition);
                            cmd.CommandText = selectCommand;
                            cmd.CommandType = CommandType.Text;
                            cmd.Connection = con;

                            using (SqlDataReader sdr = cmd.ExecuteReader())// cmd2.ExecuteNonQuery();
                            {

                                if (sdr.HasRows)
                                {
                                    while (sdr.Read())
                                    {
                                        list.Add(sdr["tel"].ToString());
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
                return list;
            }
        }

        [WebMethod]
        public List<string> GetSharedUsers(string group_id, string token)
        {
            List<string> list = new List<string>();

            if (!Authentication.Check(token))
            {
                return null;

            }

            string[] group_id_list = group_id.Split(',');

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        foreach (string item in group_id_list)
                        {
                            var selectCommand = string.Format("select 使用者名 from View_群发簿共享 where 群发薄id='{0}'", group_id);
                            cmd.CommandText = selectCommand;
                            cmd.CommandType = CommandType.Text;
                            cmd.Connection = con;

                            using (SqlDataReader sdr = cmd.ExecuteReader())// cmd2.ExecuteNonQuery();
                            {

                                if (sdr.HasRows)
                                {
                                    while (sdr.Read())
                                    {
                                        list.Add(sdr["使用者名"].ToString());
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
                return list;
            }
        }

        /** for admin 

        [WebMethod]
        public List<User> GetUsers(string condition)
        {
            List<User> list = new List<User>();
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        string where = "";
                        if (!string.IsNullOrEmpty(condition))
                        {
                            where = " where " + condition;
                        }
                        var selectCommand = string.Format("SELECT * FROM 用户 {0}", where);//组合选择语句
                        cmd.CommandText = selectCommand;
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;
                        using (SqlDataReader sdr = cmd.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {
                                    User user = new User();
                                    user.id = new Guid(sdr["id"].ToString());
                                    user.userid = sdr["用户名"].ToString();
                                    user.psw = sdr["密码"].ToString();
                                    user.name = sdr["真实姓名"].ToString();
                                    user.sex = sdr["性别"].ToString();
                                    user.mobile = sdr["手机号"].ToString();
                                    user.tel = sdr["公司电话"].ToString();
                                    user.qq = sdr["QQ"].ToString();
                                    user.email = sdr["Email"].ToString();
                                    user.com_name = sdr["公司名称"].ToString();
                                    user.com_addr = sdr["公司地址"].ToString();
                                    user.state = sdr["账号状态"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["短信条数"].ToString()))
                                        user.sms = Convert.ToInt32(sdr["短信条数"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["彩信条数"].ToString()))
                                        user.msms = Convert.ToInt32(sdr["彩信条数"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["回复条数"].ToString()))
                                        user.reply = Convert.ToInt32(sdr["回复条数"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["业务负责人id"].ToString()))
                                        user.manager_id = new Guid(sdr["业务负责人id"].ToString());
                                    user.sms_sign = sdr["短信签名"].ToString();
                                    list.Add(user);
                                }

                            }
                        }
                    }
                    return list;
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
        public string EditUser(string id, string psw, string name, string sex, string mobile, string tel, string qq, string email, string com_name, string com_addr, string state, string level, string manager_id, string sms_sign)
        {
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        var sql = string.Format("update 用户 set 密码='{0}',  真实姓名='{1}',  性别='{2}',  手机号='{3}',  公司电话='{4}',  QQ='{5}',  Email='{6}',  公司名称='{7}',  公司地址='{8}',  账号状态='{9}',  用户等级='{10}',  业务负责人id='{11}',  短信签名='{12}',  操作时间=getdate() where id='{13}'",psw, name, sex, mobile, tel, qq, email, com_name, com_addr, state, level, manager_id, sms_sign, id);
                        cmd.CommandText = sql;
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;

                        int ret = cmd.ExecuteNonQuery();

                        if (ret == 1)
                        {
                            return "修改成功！";
                        }
                        else
                        {
                            return "系统错误！\n请联系管理员";
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
        public string ChangeUserState(string id, string state, string manager_id)
        {
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        var sql = string.Format("update 用户 set 账号状态='{0}',  业务负责人id='{1}', 操作时间=getdate() where id='{2}'", state, manager_id, id);
                        cmd.CommandText = sql;
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;

                        int ret = cmd.ExecuteNonQuery();

                        if (ret == 1)
                        {
                            return "开通用户账户成功！";
                        }
                        else
                        {
                            return "系统错误！\n请联系管理员";
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
        public string DeleteUser(string id, string manager_id)
        {
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        var sql = string.Format("delete from  用户 where id='{0} and 业务负责人id='{1}''", id, manager_id);
                        cmd.CommandText = sql;
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;

                        int ret = cmd.ExecuteNonQuery();

                        if (ret == 1)
                        {
                            return "删除账户成功！";
                        }
                        else
                        {
                            return "系统错误！\n请联系管理员";
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
        public string EditMoney(string admin_id, string user_id, string type, int num, string content)
        {
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务器_充值";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp0 = new SqlParameter("@业务员id", SqlDbType.UniqueIdentifier);
                        sp0.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp0);
                        sp0.Value = new Guid(admin_id);

                        var sp1 = new SqlParameter("@用户id", SqlDbType.UniqueIdentifier);
                        sp1.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp1);
                        sp1.Value = new Guid(user_id);

                        var sp2 = new SqlParameter("@充值类型", SqlDbType.NVarChar, 20);
                        sp2.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp2);
                        sp2.Value = type;

                        var sp3 = new SqlParameter("@数量", SqlDbType.Int);
                        sp3.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp3);
                        sp3.Value = num;

                        var sp4 = new SqlParameter("@备注", SqlDbType.Text);
                        sp4.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp4);
                        sp4.Value = content;


                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("0"))
                        {
                            return "成功为用户充值：" + num + "条" + type;
                        }
                        else
                        {
                            return "系统错误！\n请联系管理员, code=" + res;
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

        */
    }
}
