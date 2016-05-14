using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;
using System.Linq;
using System.Web;
using System.Web.Services;
using MobileWebService.Entity;
using MobileWebService.Validater;

namespace MobileWebService
{
    /// <summary>
    /// UtilFunctionWebService 的摘要说明
    /// </summary>
    [WebService(Namespace = "http://tempuri.org/")]
    [WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
    [System.ComponentModel.ToolboxItem(false)]
    // 若要允许使用 ASP.NET AJAX 从脚本中调用此 Web 服务，请取消对下行的注释。
    // [System.Web.Script.Services.ScriptService]
    public class UtilFunctionWebService : System.Web.Services.WebService
    {
        #region 字典表相关操作服务

        [WebMethod]
        //根据条件获取字典表信息
        public List<DIC_Content> GetDicContentByCondition(string condition, string sessionId)
        {
            //解密
            condition = NetSecurity.decrypt(condition);

            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return null;
            }
            var contents = new List<DIC_Content>();
            string selectCondition = "";
            if (!string.IsNullOrEmpty(condition))
            {
                selectCondition = "Where " + condition;
            }
            var selectCommand = string.Format("SELECT  * FROM [MobileManage].[dbo].[URP_DIC_Content] {0}",
                                              selectCondition); //组合选择语句
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
                                    var content = new DIC_Content()
                                                      {
                                                          Category = sdr["Category"].ToString(),
                                                          Name = sdr["Name"].ToString(),
                                                          Code = sdr["Code"].ToString(),
                                                          Enabled = Convert.ToBoolean(sdr["Enabled"]),
                                                          content = sdr["备注"].ToString(),
                                                          val1 = sdr["附加字段1"].ToString(),
                                                          val2 = sdr["附加字段2"].ToString()
                                                      };

                                    contents.Add(content);
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
            return contents;
        }

        [WebMethod]
        //获取所有字典表目录信息
        public List<DIC_Category> GetAllCategory(string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return null;
            }

            var categorys = new List<DIC_Category>();
            const string selectCommand = "SELECT  * FROM [MobileManage].[dbo].[URP_DIC_Category]"; //选择语句
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
                                    var category = new DIC_Category()
                                                       {
                                                           Category = sdr["Category"].ToString(),
                                                           Editable = Convert.ToBoolean(sdr["Editable"])
                                                       };

                                    categorys.Add(category);
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
            return categorys;
        }

        [WebMethod]
        //插入字典表内容
        public string InsertDicContent(string category, string name, string code, bool enabled, string content, 
                                        string val1, string val2, string operatorId, string sessionId)
        {

            if (!SessionValidater.ValidateSessionId(sessionId, operatorId))
            {
                //不合法的请求调用
                return "非法登录";
            }
            //解密
            category = NetSecurity.decrypt(category);
            name = NetSecurity.decrypt(name);
            code = NetSecurity.decrypt(code);
            operatorId = NetSecurity.decrypt(operatorId);
            content = NetSecurity.decrypt(content);
            val1 = NetSecurity.decrypt(val1);
            val2 = NetSecurity.decrypt(val2);


            using (SqlConnection con = DBConn.CreateConn()) //新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText =
                            string.Format("select * from URP_DIC_Content where Category= '{0}' AND Name='{1}'", category,
                                          name);
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;
                        using (SqlDataReader sdr = cmd.ExecuteReader()) // cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                return "该字典表内容已经存在！不允许重复插入";
                            }
                        }
                    }

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_新增字典表内容";
                        cmd.CommandType = cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp1 = new SqlParameter("@Category", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = category };
                        cmd.Parameters.Add(sp1);


                        var sp2 = new SqlParameter("@Name", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = name };
                        cmd.Parameters.Add(sp2);


                        var sp3 = new SqlParameter("@Code", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = code };
                        cmd.Parameters.Add(sp3);

                        var sp4 = new SqlParameter("@Enabled", SqlDbType.Bit) { Direction = ParameterDirection.Input, Value = enabled };
                        cmd.Parameters.Add(sp4);

                        var sp5 = new SqlParameter("@操作者Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(operatorId) };
                        cmd.Parameters.Add(sp5);

                        var sp6 = new SqlParameter("@备注", SqlDbType.NVarChar, 100) { Direction = ParameterDirection.Input, Value = content };
                        cmd.Parameters.Add(sp6);

                        var sp7 = new SqlParameter("@附加字段1", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = val1 };
                        cmd.Parameters.Add(sp7);

                        var sp8 = new SqlParameter("@附加字段2", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = val2 };
                        cmd.Parameters.Add(sp8);

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;


                        cmd.ExecuteNonQuery();

                        var result = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (Convert.ToInt32(result) > 0)
                        {
                            return "成功";
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
            return "失败";
        }


        [WebMethod]
        //修改字典表内容
        public string UpdateDicContent(string category, string name, string code, bool enabled, string content,
                                        string val1, string val2, string operatorId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId, operatorId))
            {
                //不合法的请求调用
                return "非法登录";
            }
            //解密
            category = NetSecurity.decrypt(category);
            name = NetSecurity.decrypt(name);
            code = NetSecurity.decrypt(code);
            operatorId = NetSecurity.decrypt(operatorId);
            content = NetSecurity.decrypt(content);
            val1 = NetSecurity.decrypt(val1);
            val2 = NetSecurity.decrypt(val2);

            using (SqlConnection con = DBConn.CreateConn()) //新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_修改字典表内容";
                        cmd.CommandType = cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp1 = new SqlParameter("@Category", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = category };
                        cmd.Parameters.Add(sp1);


                        var sp2 = new SqlParameter("@Name", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = name };
                        cmd.Parameters.Add(sp2);


                        var sp3 = new SqlParameter("@Code", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = code };
                        cmd.Parameters.Add(sp3);

                        var sp4 = new SqlParameter("@Enabled", SqlDbType.Bit) { Direction = ParameterDirection.Input, Value = enabled };
                        cmd.Parameters.Add(sp4);

                        var sp5 = new SqlParameter("@操作者Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(operatorId) };
                        cmd.Parameters.Add(sp5);

                        var sp6 = new SqlParameter("@备注", SqlDbType.NVarChar, 100) { Direction = ParameterDirection.Input, Value = content };
                        cmd.Parameters.Add(sp6);

                        var sp7 = new SqlParameter("@附加字段1", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = val1 };
                        cmd.Parameters.Add(sp7);

                        var sp8 = new SqlParameter("@附加字段2", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = val2 };
                        cmd.Parameters.Add(sp8);

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;


                        cmd.ExecuteNonQuery();

                        var result = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (Convert.ToInt32(result) > 0)
                        {
                            return "成功";
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
            return "失败";
        }


        [WebMethod]
        //删除字典表内容
        public string DeleteDicContent(string category, string name, string operatorId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId, operatorId))
            {
                //不合法的请求调用
                return "非法登录";
            }
            //解密
            category = NetSecurity.decrypt(category);
            name = NetSecurity.decrypt(name);
            operatorId = NetSecurity.decrypt(operatorId);
            using (SqlConnection con = DBConn.CreateConn()) //新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_删除字典表内容";
                        cmd.CommandType = cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp1 = new SqlParameter("@Category", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = category };
                        cmd.Parameters.Add(sp1);


                        var sp2 = new SqlParameter("@Name", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = name };
                        cmd.Parameters.Add(sp2);


                        var sp3 = new SqlParameter("@操作者Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(operatorId) };
                        cmd.Parameters.Add(sp3);



                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;


                        cmd.ExecuteNonQuery();

                        var result = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (Convert.ToInt32(result) > 0)
                        {
                            return "成功";
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
            return "失败";
        }

        [WebMethod]
        //根据目录更新该目录下所有字典表内容
        public string UpdateDicContentByCategory(string category, List<DIC_Content> contentList, string operatorId,
                                                 string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId, operatorId))
            {
                //不合法的请求调用
                return "非法登录";
            }
            //解密
            category = NetSecurity.decrypt(category);
            operatorId = NetSecurity.decrypt(operatorId);
            using (SqlConnection con = DBConn.CreateConn()) //新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_删除字典表内容_根据目录";
                        cmd.CommandType = cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp1 = new SqlParameter("@Category", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = category };
                        cmd.Parameters.Add(sp1);

                        var sp2 = new SqlParameter("@操作者Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(operatorId) };
                        cmd.Parameters.Add(sp2);

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();

                        var result = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (Convert.ToInt32(result) <= 0)
                        {
                            return "更新失败——删除字典表失败";
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
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();
                    foreach (var content in contentList)
                    {
                        using (var cmd = new SqlCommand())
                        {
                            cmd.CommandText = "Function_服务端_新增字典表内容";
                            cmd.CommandType = cmd.CommandType = CommandType.StoredProcedure;
                            cmd.Connection = con;

                            var sp1 = new SqlParameter("@Category", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = category };
                            cmd.Parameters.Add(sp1);


                            var sp2 = new SqlParameter("@Name", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = content.Name };
                            cmd.Parameters.Add(sp2);


                            var sp3 = new SqlParameter("@Code", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = content.Code };
                            cmd.Parameters.Add(sp3);

                            var sp4 = new SqlParameter("@Enabled", SqlDbType.Bit) { Direction = ParameterDirection.Input, Value = content.Enabled };
                            cmd.Parameters.Add(sp4);

                            var sp5 = new SqlParameter("@操作者Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(operatorId) };
                            cmd.Parameters.Add(sp5);

                            var sp6 = new SqlParameter("@备注", SqlDbType.NVarChar, 100) { Direction = ParameterDirection.Input, Value = content.content };
                            cmd.Parameters.Add(sp6);

                            var sp7 = new SqlParameter("@附加字段1", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = content.val1 };
                            cmd.Parameters.Add(sp7);

                            var sp8 = new SqlParameter("@附加字段2", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = content.val2 };
                            cmd.Parameters.Add(sp8);

                            cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;


                            cmd.ExecuteNonQuery();

                            var result = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                            if (Convert.ToInt32(result) <= 0)
                            {
                                return "更新失败——增加字典表失败";
                            }

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

            return "字典表修改成功";

        }




        #endregion

        #region 系统功能权限相关操作
        [WebMethod]
        //获取条件获取系统功能，条件为空时获取所有功能
        public List<SystemFunction> GetFunctionList(string condition, string sessionId)
        {
            var list = new List<SystemFunction>();
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

            var selectCommand = string.Format("SELECT * FROM [MobileManage].[dbo].[系统功能] {0}", selectCondition);//组合选择语句

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
                                        FunctionPictureName = sdr["功能图片"] == null ? null : sdr["功能图片"].ToString(),
                                        FunctionNamespace = sdr["功能命名空间"] == null ? null : sdr["功能命名空间"].ToString(),
                                        FunctionScope = sdr["功能作用域"] == null ? null : sdr["功能作用域"].ToString(),
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
            return list;
        }



        [WebMethod]
        //更新用户（包括用户和员工）所具有的权限
        public string UpdateUserFunctionList(string userIdOrWokerId, string operateId, List<SystemFunction> functionList, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId, operateId))
            {
                //不合法的请求调用
                return "非法登录";
            }
            //解密
            userIdOrWokerId = NetSecurity.decrypt(userIdOrWokerId);
            operateId = NetSecurity.decrypt(operateId);


            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_删除用户全部功能映射";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp1 = new SqlParameter("@员工Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(userIdOrWokerId) };
                        cmd.Parameters.Add(sp1);


                        var sp2 = new SqlParameter("@操作者Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(operateId) };
                        cmd.Parameters.Add(sp2);


                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();
                        if (!res.Equals("1"))
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

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    foreach (var function in functionList)
                    {
                        using (var cmd = new SqlCommand())
                        {
                            cmd.CommandText = "Function_服务端_新增功能映射";
                            cmd.CommandType = CommandType.StoredProcedure;
                            cmd.Connection = con;

                            var sp1 = new SqlParameter("@员工Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(userIdOrWokerId) };
                            cmd.Parameters.Add(sp1);

                            var sp2 = new SqlParameter("@系统功能Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = function.Id };
                            cmd.Parameters.Add(sp2);

                            var sp3 = new SqlParameter("@操作者Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(operateId) };
                            cmd.Parameters.Add(sp3);


                            cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                            cmd.ExecuteNonQuery();
                            var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();
                            if (!res.Equals("1"))
                            {
                                return "数据库操作失败";
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

            return "权限设置成功";


        }
        [WebMethod]
        //更新系统功能权值
        public string UpdateFunctionRight(string functionId, int right, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return "非法登录！";
            }

            //解密
            functionId = NetSecurity.decrypt(functionId);

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = string.Format("UPDATE [MobileManage].[dbo].[系统功能] SET [权值] ={0} where[Id]='{1}' ", right, functionId);
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;
                        cmd.ExecuteNonQuery();
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
            return "设置成功";
        }

        #endregion

        #region 统计表头相关操作

        //统计表头信息
        //传入表名，需要计算sum的2个字段名称，过滤条件
        [WebMethod]
        public TableStatistics GetTableStatistics(string tableName, string sumItem1, string sumItem2,
                                                    string condition, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return null;
            }
            var table = new TableStatistics();
            //参数有效性验证
            if (string.IsNullOrEmpty(tableName))
                return table;
            if (string.IsNullOrEmpty(sumItem1))
                return table;
            if (string.IsNullOrEmpty(sumItem2))
                return table;
            string selectCondition = "";
            if (!string.IsNullOrEmpty(condition))
            {
                selectCondition = "Where " + condition;
            }
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        var selectCommand = string.Format("SELECT count([Id]) as total, sum([{0}]) as sum1, sum([{1}]) as sum2 FROM [MobileManage].[dbo].[{2}] {3}", sumItem1, sumItem2, tableName, selectCondition);
                        cmd.CommandText = selectCommand;
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;

                        using (SqlDataReader sdr = cmd.ExecuteReader()) // cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {
                                    table.total = Convert.ToInt16(sdr["total"].ToString());
                                    table.sum1 = Convert.ToDouble(sdr["sum1"].ToString());
                                    table.sum2 = Convert.ToDouble(sdr["sum2"].ToString());
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
            return table;
        }
        #endregion

        #region 公告相关操作

        //获取公告信息
        //传入分页的大小，要查询的页数
        //返回对象中包含信息：公告总条数，总页数，分页大小，当前页面号，页面信息
        [WebMethod]
        public Notice GetNoticeList(int pageSize, int pageIndex, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return null;
            }
            var notic = new Notice();
            //参数有效性验证
            if (pageSize < 1)
                return notic;
            if (pageIndex < 1)
                return notic;

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd0 = new SqlCommand())
                    {
                        var selectCommand = string.Format("SELECT count(Id) as total FROM [dbo].[系统公告] where [是否显示]=1");
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
                            notic.total = total;
                            notic.totalPage = (int)Math.Ceiling((double)total / (double)pageSize);
                            notic.currentPageIndex = pageIndex;
                            notic.pageSize = pageSize;
                        }
                    }

                    using (var cmd = new SqlCommand())
                    {
                        var selectCommand = string.Format("SELECT * FROM (SELECT ROW_NUMBER() OVER(ORDER BY [权值] desc,[发布时间]desc) AS rownum, Id, 标题, 内容, 发布时间, 公告类型, 发布者Id, 是否显示,权值,客户端类型 FROM [dbo].[系统公告] where [是否显示]=1) AS D WHERE rownum BETWEEN ({0}-1)*{1}+1 AND {0}*{1}", pageIndex, pageSize);
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
                                    var notcieItem = new NoticeItem();
                                    if (!String.IsNullOrEmpty(sdr["Id"].ToString()))
                                        notcieItem.Id = new Guid(sdr["Id"].ToString());
                                    notcieItem.title = sdr["标题"].ToString();
                                    notcieItem.content = sdr["内容"].ToString();
                                    notcieItem.publishDatetime = Convert.ToDateTime(sdr["发布时间"].ToString());
                                    notcieItem.type = sdr["公告类型"].ToString();
                                    if (!String.IsNullOrEmpty(sdr["发布者Id"].ToString()))
                                        notcieItem.publisher_id = new Guid(sdr["发布者Id"].ToString());
                                    notcieItem.isEnable = Convert.ToBoolean(sdr["是否显示"].ToString());
                                    notcieItem.weight = Convert.ToInt16(sdr["权值"].ToString());
                                    notcieItem.clientType = sdr["客户端类型"].ToString();
                                    notic.listOfNotice.Add(notcieItem);
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
            return notic;
        }

        //通过条件获取公告信息
        //传入分页的大小，要查询的页数
        //返回对象中包含信息：公告总条数，总页数，分页大小，当前页面号，页面信息
        [WebMethod]
        public Notice GetNoticeListByCondition(int pageSize, int pageIndex, string condition, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return null;
            }
            //解密
            condition = NetSecurity.decrypt(condition);

            var notic = new Notice();
            //参数有效性验证
            if (pageSize < 1)
                return notic;
            if (pageIndex < 1)
                return notic;

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
                        var selectCommand = string.Format("SELECT count(Id) as total FROM [dbo].[系统公告] {0}", whereCondition);
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
                            notic.total = total;
                            notic.totalPage = (int)Math.Ceiling((double)total / (double)pageSize);
                            notic.currentPageIndex = pageIndex;
                            notic.pageSize = pageSize;
                        }
                    }

                    using (var cmd = new SqlCommand())
                    {
                        var selectCommand = string.Format("SELECT * FROM (SELECT ROW_NUMBER() OVER(ORDER BY [权值] desc,[发布时间]desc) AS rownum, Id, 标题, 内容, 发布时间, 公告类型, 发布者Id, 是否显示,权值,客户端类型 FROM [dbo].[系统公告] {2}) AS D WHERE rownum BETWEEN ({0}-1)*{1}+1 AND {0}*{1}", pageIndex, pageSize, whereCondition);
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
                                    var notcieItem = new NoticeItem();
                                    if (!String.IsNullOrEmpty(sdr["Id"].ToString()))
                                        notcieItem.Id = new Guid(sdr["Id"].ToString());
                                    notcieItem.title = sdr["标题"].ToString();
                                    notcieItem.content = sdr["内容"].ToString();
                                    notcieItem.publishDatetime = Convert.ToDateTime(sdr["发布时间"].ToString());
                                    notcieItem.type = sdr["公告类型"].ToString();
                                    if (!String.IsNullOrEmpty(sdr["发布者Id"].ToString()))
                                        notcieItem.publisher_id = new Guid(sdr["发布者Id"].ToString());
                                    notcieItem.isEnable = Convert.ToBoolean(sdr["是否显示"].ToString());
                                    notcieItem.weight = Convert.ToInt16(sdr["权值"].ToString());
                                    notcieItem.clientType = sdr["客户端类型"].ToString();
                                    notic.listOfNotice.Add(notcieItem);
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
            return notic;
        }

        //取某一公告的详细内容
        [WebMethod]
        public NoticeItem GetNoticeItem(string noticeId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return null;
            }
            noticeId = NetSecurity.decrypt(noticeId);
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        var selectCommand = string.Format("SELECT * FROM [dbo].[系统公告] where [Id]='{0}'", noticeId);
                        cmd.CommandText = selectCommand;
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;

                        using (SqlDataReader sdr = cmd.ExecuteReader()) // cmd2.ExecuteNonQuery();
                        {
                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {
                                    var notcieItem = new NoticeItem();
                                    if (!String.IsNullOrEmpty(sdr["Id"].ToString()))
                                        notcieItem.Id = new Guid(sdr["Id"].ToString());
                                    notcieItem.title = sdr["标题"].ToString();
                                    notcieItem.content = sdr["内容"].ToString();
                                    notcieItem.publishDatetime = Convert.ToDateTime(sdr["发布时间"].ToString());
                                    notcieItem.type = sdr["公告类型"].ToString();
                                    if (!String.IsNullOrEmpty(sdr["发布者Id"].ToString()))
                                        notcieItem.publisher_id = new Guid(sdr["发布者Id"].ToString());
                                    notcieItem.isEnable = Convert.ToBoolean(sdr["是否显示"].ToString());
                                    notcieItem.weight = Convert.ToInt16(sdr["权值"].ToString());
                                    return notcieItem;
                                }
                                cmd.Dispose();
                                sdr.Close();
                            }
                        }
                    }
                    return null;
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

        //获取及时公告
        [WebMethod]
        public Notice GetAlertNoticeList(string userId, string clientType, string sessionId)
        {
            
            
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return null;
            }

            userId = NetSecurity.decrypt(userId);
            clientType = NetSecurity.decrypt(clientType);
    
            var notic = new Notice();

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();
                    int total = 0;
                    

                    using (var cmd = new SqlCommand())
                    {
                        //查询对所有人的和本人的即时消息
                        var selectCommand = "SELECT * FROM [MobileManage].[dbo].[即时消息信息] where ([网点用户Id] is NULL or [网点用户Id]='" + userId + "') and [客户端类型]='" + clientType + "' order by [发布时间] desc";
                        //var selectCommand = string.Format("SELECT * FROM [dbo].[系统公告] where [公告类型]='即时消息' and [是否显示]=1 and [客户端类型]='" + clientType + "' order by [发布时间] desc");
                        cmd.CommandText = selectCommand;
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;

                        using (SqlDataReader sdr = cmd.ExecuteReader()) // cmd2.ExecuteNonQuery();
                        {
                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {
                                    total++;
                                    var notcieItem = new NoticeItem();
                                    if (!String.IsNullOrEmpty(sdr["Id"].ToString()))
                                        notcieItem.Id = new Guid(sdr["Id"].ToString());
                                    notcieItem.title = sdr["标题"].ToString();
                                    notcieItem.content = sdr["内容"].ToString();
                                    if (!String.IsNullOrEmpty(sdr["发布时间"].ToString()))
                                        notcieItem.publishDatetime = Convert.ToDateTime(sdr["发布时间"].ToString());
                                    notcieItem.type = sdr["公告类型"].ToString();
                                    if (!String.IsNullOrEmpty(sdr["发布者Id"].ToString()))
                                        notcieItem.publisher_id = new Guid(sdr["发布者Id"].ToString());
                                    if (!String.IsNullOrEmpty(sdr["是否显示"].ToString()))
                                        notcieItem.isEnable = Convert.ToBoolean(sdr["是否显示"].ToString());
                                    if (!String.IsNullOrEmpty(sdr["权值"].ToString()))
                                        notcieItem.weight = Convert.ToInt16(sdr["权值"].ToString());
                                    notic.listOfNotice.Add(notcieItem);
                                }

                                cmd.Dispose();
                                sdr.Close();
                            }
                        }
                    }

                    /*
                    using (var cmd = new SqlCommand())
                    {

                        //先查询对所有人发送的即时消息
                        var selectCommand = string.Format("SELECT * FROM [dbo].[系统公告] where [公告类型]='即时消息' and [是否显示]=1 and [客户端类型]='"+clientType+"' and Id not in (select [系统公告Id] from [dbo].[系统公告_即时消息_映射表]) order by [发布时间] desc");
                        cmd.CommandText = selectCommand;
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;

                        using (SqlDataReader sdr = cmd.ExecuteReader()) // cmd2.ExecuteNonQuery();
                        {
                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {
                                    total++;
                                    var notcieItem = new NoticeItem();
                                    if (!String.IsNullOrEmpty(sdr["Id"].ToString()))
                                        notcieItem.Id = new Guid(sdr["Id"].ToString());
                                    notcieItem.title = sdr["标题"].ToString();
                                    notcieItem.content = sdr["内容"].ToString();
                                    if (!String.IsNullOrEmpty(sdr["发布时间"].ToString()))
                                        notcieItem.publishDatetime = Convert.ToDateTime(sdr["发布时间"].ToString());
                                    notcieItem.type = sdr["公告类型"].ToString();
                                    if (!String.IsNullOrEmpty(sdr["发布者Id"].ToString()))
                                        notcieItem.publisher_id = new Guid(sdr["发布者Id"].ToString());
                                    if (!String.IsNullOrEmpty(sdr["是否显示"].ToString()))
                                        notcieItem.isEnable = Convert.ToBoolean(sdr["是否显示"].ToString());
                                    if (!String.IsNullOrEmpty(sdr["权值"].ToString()))
                                        notcieItem.weight = Convert.ToInt16(sdr["权值"].ToString());
                                    notic.listOfNotice.Add(notcieItem);
                                }

                                cmd.Dispose();
                                sdr.Close();
                            }
                        }
                    }
                    using (var cmd1 = new SqlCommand())
                    {
                        //在查询发给个人的即时消息
                        var selectCommand = string.Format("SELECT * FROM [dbo].[系统公告] where [公告类型]='即时消息' and [是否显示]=1 and Id in (select [系统公告Id] from [dbo].[系统公告_即时消息_映射表] where [网点用户Id]='" + userId + "') order by [发布时间] desc");
                        cmd1.CommandText = selectCommand;
                        cmd1.CommandType = CommandType.Text;
                        cmd1.Connection = con;

                        using (SqlDataReader sdr1 = cmd1.ExecuteReader()) // cmd2.ExecuteNonQuery();
                        {

                            if (sdr1.HasRows)
                            {
                                while (sdr1.Read())
                                {
                                    total++;
                                    var notcieItem = new NoticeItem();
                                    if (!String.IsNullOrEmpty(sdr1["Id"].ToString()))
                                        notcieItem.Id = new Guid(sdr1["Id"].ToString());
                                    notcieItem.title = sdr1["标题"].ToString();
                                    notcieItem.content = sdr1["内容"].ToString();
                                    if (!String.IsNullOrEmpty(sdr1["发布时间"].ToString()))
                                        notcieItem.publishDatetime = Convert.ToDateTime(sdr1["发布时间"].ToString());
                                    notcieItem.type = sdr1["公告类型"].ToString();
                                    if (!String.IsNullOrEmpty(sdr1["发布者Id"].ToString()))
                                        notcieItem.publisher_id = new Guid(sdr1["发布者Id"].ToString());
                                    if (!String.IsNullOrEmpty(sdr1["是否显示"].ToString()))
                                        notcieItem.isEnable = Convert.ToBoolean(sdr1["是否显示"].ToString());
                                    if (!String.IsNullOrEmpty(sdr1["权值"].ToString()))
                                        notcieItem.weight = Convert.ToInt16(sdr1["权值"].ToString());
                                    notic.listOfNotice.Add(notcieItem);
                                }
                                cmd1.Dispose();
                                sdr1.Close();
                            }
                        }
                    }
                     */ 

                    notic.total = total;
                    notic.totalPage = 1;
                    notic.currentPageIndex = 1;
                    return notic;

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

        //新增公告
        [WebMethod]
        public string AddNoticeItem(string title, string content, string type, string publisherId
                                        , bool isShow, int weight, string clientType, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return "非法登录";
            }
            //解密
            title = NetSecurity.decrypt(title);
            content = NetSecurity.decrypt(content);
            type = NetSecurity.decrypt(type);
            publisherId = NetSecurity.decrypt(publisherId);
            clientType = NetSecurity.decrypt(clientType);

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_新增公告";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp1 = new SqlParameter("@标题", SqlDbType.NVarChar, 100) { Direction = ParameterDirection.Input, Value = title };
                        cmd.Parameters.Add(sp1);


                        var sp2 = new SqlParameter("@内容", SqlDbType.Text) { Direction = ParameterDirection.Input, Value = content };
                        cmd.Parameters.Add(sp2);

                        var sp3 = new SqlParameter("@公告类型", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = type };
                        cmd.Parameters.Add(sp3);

                        var sp4 = new SqlParameter("@发布者Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = string.IsNullOrEmpty(publisherId) ? (object)DBNull.Value : new Guid(publisherId) };
                        cmd.Parameters.Add(sp4);

                        var sp5 = new SqlParameter("@是否显示", SqlDbType.Bit) { Direction = ParameterDirection.Input, Value = isShow };
                        cmd.Parameters.Add(sp5);

                        var sp6 = new SqlParameter("@权值", SqlDbType.Int) { Direction = ParameterDirection.Input, Value = weight };
                        cmd.Parameters.Add(sp6);

                        var sp7 = new SqlParameter("@客户端类型", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = clientType };
                        cmd.Parameters.Add(sp7);

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

        //新增公告给某一用户
        [WebMethod]
        public string AddNoticeItemToSomeone(string title, string content, string type, string publisherId
                                        , bool isShow, int weight, string userId, string clientType, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return "非法登录";
            }
            //解密
            title = NetSecurity.decrypt(title);
            content = NetSecurity.decrypt(content);
            type = NetSecurity.decrypt(type);
            publisherId = NetSecurity.decrypt(publisherId);
            clientType = NetSecurity.decrypt(clientType);
            userId = NetSecurity.decrypt(userId);
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_新增公告对于某一用户";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp1 = new SqlParameter("@标题", SqlDbType.NVarChar, 100) { Direction = ParameterDirection.Input, Value = title };
                        cmd.Parameters.Add(sp1);


                        var sp2 = new SqlParameter("@内容", SqlDbType.Text) { Direction = ParameterDirection.Input, Value = content };
                        cmd.Parameters.Add(sp2);

                        var sp3 = new SqlParameter("@公告类型", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = type };
                        cmd.Parameters.Add(sp3);

                        var sp4 = new SqlParameter("@发布者Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = string.IsNullOrEmpty(publisherId) ? (object)DBNull.Value : new Guid(publisherId) };
                        cmd.Parameters.Add(sp4);

                        var sp5 = new SqlParameter("@是否显示", SqlDbType.Bit) { Direction = ParameterDirection.Input, Value = isShow };
                        cmd.Parameters.Add(sp5);

                        var sp6 = new SqlParameter("@权值", SqlDbType.Int) { Direction = ParameterDirection.Input, Value = weight };
                        cmd.Parameters.Add(sp6);

                        var sp7 = new SqlParameter("@网点用户Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(userId) };
                        cmd.Parameters.Add(sp7);

                        var sp8 = new SqlParameter("@客户端类型", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = clientType };
                        cmd.Parameters.Add(sp8);

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

        //修改公告
        [WebMethod]
        public string UpdateNoticeItem(string Id, string title, string content, string type, bool isShow, int weight
                                        , string operatorId, string clientType, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId, operatorId))
            {
                //不合法的请求调用
                return "非法登录";
            }
            //解密
            title = NetSecurity.decrypt(title);
            content = NetSecurity.decrypt(content);
            type = NetSecurity.decrypt(type);
            operatorId = NetSecurity.decrypt(operatorId);
            clientType = NetSecurity.decrypt(clientType);
            Id = NetSecurity.decrypt(Id);

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_修改公告";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp0 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = string.IsNullOrEmpty(Id) ? (object)DBNull.Value : new Guid(Id) };
                        cmd.Parameters.Add(sp0);

                        var sp1 = new SqlParameter("@标题", SqlDbType.NVarChar, 100) { Direction = ParameterDirection.Input, Value = title };
                        cmd.Parameters.Add(sp1);


                        var sp2 = new SqlParameter("@内容", SqlDbType.Text) { Direction = ParameterDirection.Input, Value = content };
                        cmd.Parameters.Add(sp2);

                        var sp3 = new SqlParameter("@公告类型", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = type };
                        cmd.Parameters.Add(sp3);

                        var sp4 = new SqlParameter("@操作员Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = string.IsNullOrEmpty(operatorId) ? (object)DBNull.Value : new Guid(operatorId) };
                        cmd.Parameters.Add(sp4);

                        var sp5 = new SqlParameter("@是否显示", SqlDbType.Bit) { Direction = ParameterDirection.Input, Value = isShow };
                        cmd.Parameters.Add(sp5);

                        var sp6 = new SqlParameter("@权值", SqlDbType.Int) { Direction = ParameterDirection.Input, Value = weight };
                        cmd.Parameters.Add(sp6);

                        var sp7 = new SqlParameter("@客户端类型", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = clientType };
                        cmd.Parameters.Add(sp7);

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

        //删除公告
        [WebMethod]
        public string DeleteNoticeItem(string Id, string operatorId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId, operatorId))
            {
                //不合法的请求调用
                return "非法登录";
            }
            //解密
            operatorId = NetSecurity.decrypt(operatorId);
            Id = NetSecurity.decrypt(Id);

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_删除公告";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp0 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = string.IsNullOrEmpty(Id) ? (object)DBNull.Value : new Guid(Id) };
                        cmd.Parameters.Add(sp0);

                        var sp4 = new SqlParameter("@操作员Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = string.IsNullOrEmpty(operatorId) ? (object)DBNull.Value : new Guid(operatorId) };
                        cmd.Parameters.Add(sp4);

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
        //将某一公告指定给某一用户
        public bool InserNoticeToSomeOne(string noticeId, string userId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return false;
            }
            //解密
            noticeId = NetSecurity.decrypt(noticeId);
            userId = NetSecurity.decrypt(userId);

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_指定公告给某一用户";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp1 = new SqlParameter("@公告Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(noticeId) };
                        cmd.Parameters.Add(sp1);


                        var sp2 = new SqlParameter("@网点用户Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(userId) };
                        cmd.Parameters.Add(sp2);

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();
                        if (res.Equals("1"))
                        {
                            return true;
                        }
                        else
                        {
                            return false;
                        }
                    }

                }
                catch (Exception)
                {
                    return false;
                }
                finally
                {

                    con.Close();
                }
            }

        }

        #endregion

        #region 返款比例相关
        //查询返款比例信息
        [WebMethod]
        public List<ReturnProportion> GetReturnProportionRecord(int top, string condition, string sessionId)
        {
            var list = new List<ReturnProportion>();
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
            var selectCommand = string.Format("SELECT {0} * FROM [MobileManage].[dbo].[返款比例明细] {1}", topMessage, selectCondition);//组合选择语句
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
                                    var returnProportion = new ReturnProportion
                                    {
                                        Id = new Guid(sdr["Id"].ToString()),
                                        ReturnClass = sdr["返款类型"].ToString(),
                                        ReturnName = sdr["返款项目"].ToString(),
                                        area = sdr["地区"].ToString(),
                                        level = sdr["用户级别"].ToString(),
                                        returnPoint = Convert.ToDouble(sdr["返款比例"].ToString()),
                                        content = sdr["备注"].ToString()
                                    };

                                    list.Add(returnProportion);
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

        //新增返款比例信息
        [WebMethod]
        public string AddtReturnProportion(string returnClass, string returnName, string area, string level, double returnProportion, string content, string operatorId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId, operatorId))
            {
                //不合法的请求调用
                return "非法登录！";
            }
            //解密
            returnClass = NetSecurity.decrypt(returnClass);
            returnName = NetSecurity.decrypt(returnName);
            area = NetSecurity.decrypt(area);
            level = NetSecurity.decrypt(level);
            content = NetSecurity.decrypt(content);
            operatorId = NetSecurity.decrypt(operatorId);


            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_新增返款比例";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp0 = new SqlParameter("@返款类型", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = returnClass };
                        cmd.Parameters.Add(sp0);

                        var sp1 = new SqlParameter("@返款项目", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = returnName };
                        cmd.Parameters.Add(sp1);

                        var sp2 = new SqlParameter("@地区", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = area };
                        cmd.Parameters.Add(sp2);

                        var sp3 = new SqlParameter("@用户级别", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = level };
                        cmd.Parameters.Add(sp3);

                        var sp4 = new SqlParameter("@返款比例", SqlDbType.Float) { Direction = ParameterDirection.Input, Value = returnProportion };
                        cmd.Parameters.Add(sp4);

                        var sp5 = new SqlParameter("@备注", SqlDbType.Text) { Direction = ParameterDirection.Input, Value = content };
                        cmd.Parameters.Add(sp5);

                        var sp6 = new SqlParameter("@操作员Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = string.IsNullOrEmpty(operatorId) ? (object)DBNull.Value : new Guid(operatorId) };
                        cmd.Parameters.Add(sp6);

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

        //修改返款比例信息
        [WebMethod]
        public string UpdatetReturnProportion(string Id, string returnClass, string returnName, string area, string level, double returnProportion, string content, string operatorId, string sessionId)
        {

            if (!SessionValidater.ValidateSessionId(sessionId, operatorId))
            {
                //不合法的请求调用
                return "非法登录！";
            }
            //解密
            Id = NetSecurity.decrypt(Id);
            returnClass = NetSecurity.decrypt(returnClass);
            returnName = NetSecurity.decrypt(returnName);
            area = NetSecurity.decrypt(area);
            level = NetSecurity.decrypt(level);
            content = NetSecurity.decrypt(content);
            operatorId = NetSecurity.decrypt(operatorId);

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_修改返款比例";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp = new SqlParameter("@Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = string.IsNullOrEmpty(Id) ? (object)DBNull.Value : new Guid(Id) };
                        cmd.Parameters.Add(sp);

                        var sp0 = new SqlParameter("@返款类型", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = returnClass };
                        cmd.Parameters.Add(sp0);

                        var sp1 = new SqlParameter("@返款项目", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = returnName };
                        cmd.Parameters.Add(sp1);

                        var sp2 = new SqlParameter("@地区", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = area };
                        cmd.Parameters.Add(sp2);

                        var sp3 = new SqlParameter("@用户级别", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = level };
                        cmd.Parameters.Add(sp3);

                        var sp4 = new SqlParameter("@返款比例", SqlDbType.Float) { Direction = ParameterDirection.Input, Value = returnProportion };
                        cmd.Parameters.Add(sp4);

                        var sp5 = new SqlParameter("@备注", SqlDbType.Text) { Direction = ParameterDirection.Input, Value = content };
                        cmd.Parameters.Add(sp5);

                        var sp6 = new SqlParameter("@操作员Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = string.IsNullOrEmpty(operatorId) ? (object)DBNull.Value : new Guid(operatorId) };
                        cmd.Parameters.Add(sp6);

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

        //删除返款比例信息
        [WebMethod]
        public string DeletetReturnProportion(string Id, string operatorId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId, operatorId))
            {
                //不合法的请求调用
                return "非法登录！";
            }
            //解密
            Id = NetSecurity.decrypt(Id);
            operatorId = NetSecurity.decrypt(operatorId);
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_删除返款比例";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp0 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = string.IsNullOrEmpty(Id) ? (object)DBNull.Value : new Guid(Id) };
                        cmd.Parameters.Add(sp0);

                        var sp4 = new SqlParameter("@操作员Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = string.IsNullOrEmpty(operatorId) ? (object)DBNull.Value : new Guid(operatorId) };
                        cmd.Parameters.Add(sp4);

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

        //#region 游戏返款比例
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

        //    //解密
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
        //    }

        //    return list;
        //}

        ////新增游戏返款比例信息
        //[WebMethod]
        //public string AddGameReturnProportion(string gameName, double returnProportion, string operatorId, string sessionId)
        //{
        //    if (!SessionValidater.ValidateSessionId(sessionId, operatorId))
        //    {
        //        //不合法的请求调用
        //        return "非法登录！";
        //    }
        //    //解密
        //    gameName = NetSecurity.decrypt(gameName);
        //    operatorId = NetSecurity.decrypt(operatorId);


        //    using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
        //    {
        //        try
        //        {
        //            con.Open();

        //            using (var cmd = new SqlCommand())
        //            {
        //                cmd.CommandText = "Function_服务端_新增游戏类型及其返款比例";
        //                cmd.CommandType = CommandType.StoredProcedure;
        //                cmd.Connection = con;

        //                var sp1 = new SqlParameter("@游戏类型名称", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = gameName };
        //                cmd.Parameters.Add(sp1);



        //                var sp2 = new SqlParameter("@返款比例", SqlDbType.Float) { Direction = ParameterDirection.Input, Value = returnProportion };
        //                cmd.Parameters.Add(sp2);


        //                var sp3 = new SqlParameter("@操作员Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = string.IsNullOrEmpty(operatorId) ? (object)DBNull.Value : new Guid(operatorId) };
        //                cmd.Parameters.Add(sp3);

        //                cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
        //                cmd.ExecuteNonQuery();
        //                var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();
        //                if (res.Equals("1"))
        //                {
        //                    return "新增成功";
        //                }
        //                else
        //                {
        //                    return "新增失败";
        //                }
        //            }

        //        }
        //        catch (Exception ex)
        //        {
        //            return ex.Message;
        //        }
        //        finally
        //        {

        //            con.Close();
        //        }
        //    }

        //}

        ////修改游戏返款比例信息
        //[WebMethod]
        //public string UpdateGameReturnProportion(string id, string gameName, double returnProportion, string operatorId, string sessionId)
        //{
        //    if (!SessionValidater.ValidateSessionId(sessionId, operatorId))
        //    {
        //        //不合法的请求调用
        //        return "非法登录！";
        //    }
        //    //解密
        //    id = NetSecurity.decrypt(id);
        //    gameName = NetSecurity.decrypt(gameName);
        //    operatorId = NetSecurity.decrypt(operatorId);

        //    using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
        //    {
        //        try
        //        {
        //            con.Open();

        //            using (var cmd = new SqlCommand())
        //            {
        //                cmd.CommandText = "Function_服务端_修改游戏类型及其返款比例";
        //                cmd.CommandType = CommandType.StoredProcedure;
        //                cmd.Connection = con;


        //                var sp0 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = string.IsNullOrEmpty(id) ? (object)DBNull.Value : new Guid(id) };
        //                cmd.Parameters.Add(sp0);

        //                var sp1 = new SqlParameter("@游戏类型名称", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = gameName };
        //                cmd.Parameters.Add(sp1);



        //                var sp2 = new SqlParameter("@返款比例", SqlDbType.Float) { Direction = ParameterDirection.Input, Value = returnProportion };
        //                cmd.Parameters.Add(sp2);


        //                var sp3 = new SqlParameter("@操作员Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = string.IsNullOrEmpty(operatorId) ? (object)DBNull.Value : new Guid(operatorId) };
        //                cmd.Parameters.Add(sp3);



        //                cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
        //                cmd.ExecuteNonQuery();
        //                var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();
        //                if (res.Equals("1"))
        //                {
        //                    return "修改成功";
        //                }
        //                else
        //                {
        //                    return "修改失败";
        //                }
        //            }

        //        }
        //        catch (Exception ex)
        //        {
        //            return ex.Message;
        //        }
        //        finally
        //        {

        //            con.Close();
        //        }
        //    }

        //}

        ////删除游戏返款比例信息
        //[WebMethod]
        //public string DeleteGameReturnProportion(string id, string operatorId, string sessionId)
        //{
        //    if (!SessionValidater.ValidateSessionId(sessionId, operatorId))
        //    {
        //        //不合法的请求调用
        //        return "非法登录！";
        //    }
        //    //解密
        //    id = NetSecurity.decrypt(id);
        //    operatorId = NetSecurity.decrypt(operatorId);

        //    using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
        //    {
        //        try
        //        {
        //            con.Open();

        //            using (var cmd = new SqlCommand())
        //            {
        //                cmd.CommandText = "Function_服务端_删除游戏类型及其返款比例";
        //                cmd.CommandType = CommandType.StoredProcedure;
        //                cmd.Connection = con;

        //                var sp0 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = string.IsNullOrEmpty(id) ? (object)DBNull.Value : new Guid(id) };
        //                cmd.Parameters.Add(sp0);

        //                var sp4 = new SqlParameter("@操作员Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = string.IsNullOrEmpty(operatorId) ? (object)DBNull.Value : new Guid(operatorId) };
        //                cmd.Parameters.Add(sp4);

        //                cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
        //                cmd.ExecuteNonQuery();
        //                var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();
        //                if (res.Equals("1"))
        //                {
        //                    return "删除成功";
        //                }
        //                else
        //                {
        //                    return "删除失败";
        //                }
        //            }

        //        }
        //        catch (Exception ex)
        //        {
        //            return ex.Message;
        //        }
        //        finally
        //        {

        //            con.Close();
        //        }
        //    }

        //}
        //#endregion

        //#region 宽带返款比例
        //[WebMethod]
        ////根据条件获取符合条件游戏名称列表
        //public List<InternetType> GetInteretTypeByCondition(string condition, string sessionId)
        //{
        //    var list = new List<InternetType>();
        //    if (!SessionValidater.ValidateSessionId(sessionId))
        //    {
        //        //不合法的请求调用
        //        return list;
        //    }

        //    //解密
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

        ////新增游戏返款比例信息
        //[WebMethod]
        //public string AddInternetReturnProportion(string internetName, double returnProportion, string operatorId, string sessionId)
        //{
        //    if (!SessionValidater.ValidateSessionId(sessionId, operatorId))
        //    {
        //        //不合法的请求调用
        //        return "非法登录！";
        //    }
        //    //解密
        //    internetName = NetSecurity.decrypt(internetName);
        //    operatorId = NetSecurity.decrypt(operatorId);

        //    using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
        //    {
        //        try
        //        {
        //            con.Open();

        //            using (var cmd = new SqlCommand())
        //            {
        //                cmd.CommandText = "Function_服务端_新增宽带类型及其返款比例";
        //                cmd.CommandType = CommandType.StoredProcedure;
        //                cmd.Connection = con;

        //                var sp1 = new SqlParameter("@宽带类型名称", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = internetName };
        //                cmd.Parameters.Add(sp1);



        //                var sp2 = new SqlParameter("@返款比例", SqlDbType.Float) { Direction = ParameterDirection.Input, Value = returnProportion };
        //                cmd.Parameters.Add(sp2);


        //                var sp3 = new SqlParameter("@操作员Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = string.IsNullOrEmpty(operatorId) ? (object)DBNull.Value : new Guid(operatorId) };
        //                cmd.Parameters.Add(sp3);

        //                cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
        //                cmd.ExecuteNonQuery();
        //                var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();
        //                if (res.Equals("1"))
        //                {
        //                    return "新增成功";
        //                }
        //                else
        //                {
        //                    return "新增失败";
        //                }
        //            }

        //        }
        //        catch (Exception ex)
        //        {
        //            return ex.Message;
        //        }
        //        finally
        //        {

        //            con.Close();
        //        }
        //    }

        //}

        ////修改游戏返款比例信息
        //[WebMethod]
        //public string UpdateInternetReturnProportion(string id, string internetName, double returnProportion, string operatorId, string sessionId)
        //{
        //    if (!SessionValidater.ValidateSessionId(sessionId, operatorId))
        //    {
        //        //不合法的请求调用
        //        return "非法登录！";
        //    }
        //    //解密
        //    id = NetSecurity.decrypt(id);
        //    internetName = NetSecurity.decrypt(internetName);
        //    operatorId = NetSecurity.decrypt(operatorId);
        //    using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
        //    {
        //        try
        //        {
        //            con.Open();

        //            using (var cmd = new SqlCommand())
        //            {
        //                cmd.CommandText = "Function_服务端_修改宽带类型及其返款比例";
        //                cmd.CommandType = CommandType.StoredProcedure;
        //                cmd.Connection = con;


        //                var sp0 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = string.IsNullOrEmpty(id) ? (object)DBNull.Value : new Guid(id) };
        //                cmd.Parameters.Add(sp0);

        //                var sp1 = new SqlParameter("@宽带类型名称", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = internetName };
        //                cmd.Parameters.Add(sp1);



        //                var sp2 = new SqlParameter("@返款比例", SqlDbType.Float) { Direction = ParameterDirection.Input, Value = returnProportion };
        //                cmd.Parameters.Add(sp2);


        //                var sp3 = new SqlParameter("@操作员Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = string.IsNullOrEmpty(operatorId) ? (object)DBNull.Value : new Guid(operatorId) };
        //                cmd.Parameters.Add(sp3);



        //                cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
        //                cmd.ExecuteNonQuery();
        //                var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();
        //                if (res.Equals("1"))
        //                {
        //                    return "修改成功";
        //                }
        //                else
        //                {
        //                    return "修改失败";
        //                }
        //            }

        //        }
        //        catch (Exception ex)
        //        {
        //            return ex.Message;
        //        }
        //        finally
        //        {

        //            con.Close();
        //        }
        //    }

        //}

        ////删除游戏返款比例信息
        //[WebMethod]
        //public string DeleteInternetReturnProportion(string id, string operatorId, string sessionId)
        //{

        //    if (!SessionValidater.ValidateSessionId(sessionId, operatorId))
        //    {
        //        //不合法的请求调用
        //        return "非法登录！";
        //    }
        //    //解密
        //    id = NetSecurity.decrypt(id);
        //    operatorId = NetSecurity.decrypt(operatorId);

        //    using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
        //    {
        //        try
        //        {
        //            con.Open();

        //            using (var cmd = new SqlCommand())
        //            {
        //                cmd.CommandText = "Function_服务端_删除宽带类型及其返款比例";
        //                cmd.CommandType = CommandType.StoredProcedure;
        //                cmd.Connection = con;

        //                var sp0 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = string.IsNullOrEmpty(id) ? (object)DBNull.Value : new Guid(id) };
        //                cmd.Parameters.Add(sp0);

        //                var sp4 = new SqlParameter("@操作员Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = string.IsNullOrEmpty(operatorId) ? (object)DBNull.Value : new Guid(operatorId) };
        //                cmd.Parameters.Add(sp4);

        //                cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
        //                cmd.ExecuteNonQuery();
        //                var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();
        //                if (res.Equals("1"))
        //                {
        //                    return "删除成功";
        //                }
        //                else
        //                {
        //                    return "删除失败";
        //                }
        //            }

        //        }
        //        catch (Exception ex)
        //        {
        //            return ex.Message;
        //        }
        //        finally
        //        {

        //            con.Close();
        //        }
        //    }

        //}
        //#endregion

        #endregion

        #region 号段相关操作
        //根据条件获取号码归属
        [WebMethod]
        public List<PhoneNumberBelong> GetPhoneNumberBelongByCondition(string condition, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return null;
            }

            //解密
            condition = NetSecurity.decrypt(condition);

            var numberBelong = new List<PhoneNumberBelong>();
            string selectCondition = "";
            if (!string.IsNullOrEmpty(condition))
            {
                selectCondition = "Where " + condition;
            }
            var selectCommand = string.Format("SELECT  * FROM [MobileManage].[dbo].[号码归属] {0}",
                                              selectCondition); //组合选择语句
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
                                    var belong = new PhoneNumberBelong()
                                    {
                                        Id = new Guid(sdr["Id"].ToString()),
                                        HaoDuan = sdr["号段"].ToString(),
                                        QuHao = sdr["区号"].ToString(),
                                        ShengFen = sdr["省份"].ToString(),
                                        City = sdr["城市"].ToString(),
                                        Area = sdr["地区"].ToString(),
                                        AddTime = Convert.ToDateTime(sdr["添加时间"])
                                    };

                                    numberBelong.Add(belong);
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
            return numberBelong.OrderByDescending(x => x.AddTime).ToList();
        }

        [WebMethod]
        //修改号码归属
        public string UpdatePhoneNumberBelong(PhoneNumberBelong belong, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return null;
            }
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = string.Format("UPDATE [MobileManage].[dbo].[号码归属] SET [号段] ='{0}',[区号] ='{1}',[省份] ='{2}',[城市] ='{3}',[地区] ='{4}' where[Id]='{5}' ", belong.HaoDuan, belong.QuHao, belong.ShengFen, belong.City, belong.Area, belong.Id.ToString());
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;
                        cmd.ExecuteNonQuery();
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
            return "修改成功";
        }

        [WebMethod]
        //新增号码归属
        public string AddPhoneNumberBelong(PhoneNumberBelong belong, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return null;
            }
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = string.Format("INSERT INTO [MobileManage].[dbo].[号码归属] ([Id]  ,[号段] ,[区号] ,[省份] ,[城市] ,[地区] ,[添加时间])    VALUES  ('{0}','{1}','{2}','{3}','{4}','{5}','{6}')", belong.Id, belong.HaoDuan, belong.QuHao, belong.ShengFen, belong.City, belong.Area, belong.AddTime.ToString());
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;
                        cmd.ExecuteNonQuery();
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
            return "添加成功";
        }


        [WebMethod]
        //删除号码归属
        public string DeletePhoneNumberBelong(string belongId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return null;
            }
            //解密
            belongId = NetSecurity.decrypt(belongId);

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = string.Format("delete from [MobileManage].[dbo].[号码归属] where Id='{0}'", belongId);
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;
                        cmd.ExecuteNonQuery();
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
            return "删除成功";
        }

        #endregion 号段相关操作

        #region 公司基本信息
        //获取公司信息
        [WebMethod]
        public CompanyInfo GetCompanyInfo(string clientType, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return null;
            }

            //解密
            clientType = NetSecurity.decrypt(clientType);

            var companyInfo = new CompanyInfo();
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = string.Format("select * from [MobileManage].[dbo].[公司信息] where [客户端类型]='{0}'", clientType);
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;
                        using (SqlDataReader sdr = cmd.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {
                                    companyInfo.name = sdr["公司名称"].ToString();
                                    companyInfo.address = sdr["公司地址"].ToString();
                                    companyInfo.manager = sdr["公司经理"].ToString();
                                    companyInfo.QQ = sdr["服务QQ"].ToString();
                                    companyInfo.tel_1 = sdr["服务电话1"].ToString();
                                    companyInfo.tel_2 = sdr["服务电话2"].ToString();
                                    companyInfo.clientType = sdr["客户端类型"].ToString();
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
            return companyInfo;
        }

        [WebMethod]
        public string UpdateCompanyInfo(CompanyInfo info, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId))
            {
                //不合法的请求调用
                return "不合法登录！";
            }
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_修改公司信息";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;


                        var sp1 = new SqlParameter("@公司名称", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = info.name };
                        cmd.Parameters.Add(sp1);

                        var sp2 = new SqlParameter("@公司地址", SqlDbType.Text) { Direction = ParameterDirection.Input, Value = info.address };
                        cmd.Parameters.Add(sp2);

                        var sp3 = new SqlParameter("@公司经理", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = info.manager };
                        cmd.Parameters.Add(sp3);
                        var sp4 = new SqlParameter("@服务电话1", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = info.tel_1 };
                        cmd.Parameters.Add(sp4);
                        var sp5 = new SqlParameter("@服务电话2", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = info.tel_2 };
                        cmd.Parameters.Add(sp5);
                        var sp6 = new SqlParameter("@服务QQ", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = info.QQ };
                        cmd.Parameters.Add(sp6);
                        var sp7 = new SqlParameter("@客户端类型", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = info.clientType };
                        cmd.Parameters.Add(sp7);



                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();
                        if (res.Equals("1"))
                        {
                            return "修改公司信息成功";
                        }
                        else
                        {
                            return "修改公司信息失败";
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


        //获取公司账号
        [WebMethod]
        public List<CompanyAccount> GetCompanyAccount(int top, string condition, string sessionId)
        {
            var list = new List<CompanyAccount>();
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
            var selectCommand = string.Format("SELECT {0} * FROM [MobileManage].[dbo].[公司账号] {1}", topMessage, selectCondition);//组合选择语句
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
                                    var companyAccount = new CompanyAccount();
                                    if (!string.IsNullOrEmpty(sdr["Id"].ToString()))
                                        companyAccount.Id = new Guid(sdr["Id"].ToString());
                                    companyAccount.AccountNo = sdr["银行账号"].ToString();
                                    companyAccount.Bank = sdr["银行名称"].ToString();
                                    companyAccount.userName = sdr["户名"].ToString();
                                    companyAccount.clientType = sdr["客户端类型"].ToString();
                                    list.Add(companyAccount);
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
        //新增公司账号
        [WebMethod]
        public string AddCompanyAccount(CompanyAccount account, string operatorId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId, operatorId))
            {
                //不合法的请求调用
                return null;
            }

            operatorId = NetSecurity.decrypt(operatorId);

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_新增公司账号";
                        cmd.CommandType = cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp1 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = account.Id };
                        cmd.Parameters.Add(sp1);

                        var sp2 = new SqlParameter("@银行账号", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = account.AccountNo };
                        cmd.Parameters.Add(sp2);

                        var sp3 = new SqlParameter("@银行名称", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = account.Bank };
                        cmd.Parameters.Add(sp3);

                        var sp4 = new SqlParameter("@户名", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = account.userName };
                        cmd.Parameters.Add(sp4);

                        var sp5 = new SqlParameter("@客户端类型", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = account.clientType };
                        cmd.Parameters.Add(sp5);

                        var sp6 = new SqlParameter("@操作员Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(operatorId) };
                        cmd.Parameters.Add(sp6);


                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;


                        cmd.ExecuteNonQuery();

                        var result = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (Convert.ToInt32(result) > 0)
                        {
                            return "新增公司账号成功";
                        }
                        else
                        {
                            return "新增公司账号失败";
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
        //修改公司账号
        [WebMethod]
        public string UpdateCompanyAccount(CompanyAccount account, string operatorId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId, operatorId))
            {
                //不合法的请求调用
                return null;
            }

            operatorId = NetSecurity.decrypt(operatorId);

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_修改公司账号";
                        cmd.CommandType = cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp1 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = account.Id };
                        cmd.Parameters.Add(sp1);

                        var sp2 = new SqlParameter("@银行账号", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = account.AccountNo };
                        cmd.Parameters.Add(sp2);

                        var sp3 = new SqlParameter("@银行名称", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = account.Bank };
                        cmd.Parameters.Add(sp3);

                        var sp4 = new SqlParameter("@户名", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = account.userName };
                        cmd.Parameters.Add(sp4);

                        var sp5 = new SqlParameter("@客户端类型", SqlDbType.NVarChar, 50) { Direction = ParameterDirection.Input, Value = account.clientType };
                        cmd.Parameters.Add(sp5);

                        var sp6 = new SqlParameter("@操作员Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(operatorId) };
                        cmd.Parameters.Add(sp6);


                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;


                        cmd.ExecuteNonQuery();

                        var result = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (Convert.ToInt32(result) > 0)
                        {
                            return "修改公司账号成功";
                        }
                        else
                        {
                            return "修改公司账号失败";
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
        //删除公司账号
        [WebMethod]
        public string DeleteCompanyAccount(string accountId, string operatorId, string sessionId)
        {
            if (!SessionValidater.ValidateSessionId(sessionId, operatorId))
            {
                //不合法的请求调用
                return null;
            }

            operatorId = NetSecurity.decrypt(operatorId);
            accountId = NetSecurity.decrypt(accountId);

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_服务端_删除公司账号";
                        cmd.CommandType = cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp1 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(accountId) };
                        cmd.Parameters.Add(sp1);

                        var sp6 = new SqlParameter("@操作员Id", SqlDbType.UniqueIdentifier) { Direction = ParameterDirection.Input, Value = new Guid(operatorId) };
                        cmd.Parameters.Add(sp6);

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;

                        cmd.ExecuteNonQuery();

                        var result = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (Convert.ToInt32(result) > 0)
                        {
                            return "删除公司账号成功";
                        }
                        else
                        {
                            return "删除公司账号失败";
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

        #endregion 公司基本信息

        #region 版本号

        //获取服务器端版本号
        [WebMethod]
        public string GetClientVersion(string clientType)
        {
            //解密
            clientType = NetSecurity.decrypt(clientType);

            string ver = "";
            var selectCommand = "";

            if (clientType == "移动客户端")
            {
                selectCommand = string.Format("SELECT  * FROM [MobileManage].[dbo].[URP_DIC_Content] where [Category]='客户端限制' and [Name]='移动版本号' and [Enabled]=1");
            }
            else
            {
                selectCommand = string.Format("SELECT  * FROM [MobileManage].[dbo].[URP_DIC_Content] where [Category]='客户端限制' and [Name]='联通电信版本号' and [Enabled]=1");
            }
            
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
                                    ver = sdr["Code"].ToString();
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
            return ver;
        }
    
        #endregion
    }
}
