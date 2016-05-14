using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services;
using QXT_service.Entity;
using System.Data.SqlClient;
using QXT_service.Util;
using System.Data;
using System.Xml;

namespace QXT_service
{
    /// <summary>
    /// UtilService 的摘要说明
    /// </summary>
    [WebService(Namespace = "http://tempuri.org/")]
    [WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
    [System.ComponentModel.ToolboxItem(false)]
    // 若要允许使用 ASP.NET AJAX 从脚本中调用此 Web 服务，请取消对下行的注释。
    // [System.Web.Script.Services.ScriptService]
    public class UtilService : System.Web.Services.WebService
    {

        [WebMethod]
        public List<Turple> GetNoGroups(string user_id, string type)
        {
            List<Turple> list = new List<Turple>();
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {

                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        var selectCommand = string.Format("SELECT * FROM [QXT_platform].[dbo].[号码群组] where [用户id]='{0}' and [类型]='{1}'", user_id, type);//组合选择语句
                        cmd.CommandText = selectCommand;
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;
                        using (SqlDataReader sdr = cmd.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {
                                    Turple turple = new Turple();
                                    turple.data = sdr["id"].ToString();
                                    turple.label = sdr["组名称"].ToString();
                                    list.Add(turple);
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
        public List<string> GetStrList(string table, string condition, string colName, string token)
        {
            List<string> list = new List<string>();
            if (!Authentication.Check(token))
            {
                return list;

            }

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    if (!string.IsNullOrEmpty(condition))
                    {
                        condition = " where " + condition;
                    }

                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        var selectCommand = string.Format("SELECT * FROM [QXT_platform].[dbo].[{0}] {1}", table, condition);//组合选择语句
                        cmd.CommandText = selectCommand;
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;
                        using (SqlDataReader sdr = cmd.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {
                            
                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {
                                    list.Add(sdr[colName].ToString());
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
        public bool CheckExist(string table, string condition)
        {
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    if (!string.IsNullOrEmpty(condition))
                    {
                        condition = " where " + condition;
                    }

                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        var selectCommand = string.Format("SELECT * FROM [QXT_platform].[dbo].[{0}] {1}", table, condition);//组合选择语句
                        cmd.CommandText = selectCommand;
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;
                        using (SqlDataReader sdr = cmd.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                return true;
                            }
                            else
                            {
                                return false;
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
        public string Query(string pageIndex, string pageSize, string tableName, string order, string columns, string filters, string token)
        {
            XmlDocument xmldoc = new XmlDocument();
            XmlDeclaration xmldecl;
            xmldecl = xmldoc.CreateXmlDeclaration("1.0", "utf-8", null);
            xmldoc.AppendChild(xmldecl);
            var xmlelem = xmldoc.CreateElement("", "result", "");
            xmldoc.AppendChild(xmlelem);

            if (!Authentication.Check(token))
            {
                XmlNode root = xmldoc.SelectSingleNode("result");//查找<Employees> 
                XmlElement xe1 = xmldoc.CreateElement("status");//创建一个<Node>节点 
                XmlElement xesub1 = xmldoc.CreateElement("code");
                xesub1.InnerText = "无权限操作!";//设置文本节点 
                xe1.AppendChild(xesub1);         //添加到<Node>节点中 
                XmlElement xesub2 = xmldoc.CreateElement("page");
                xesub2.InnerText = "0";
                xe1.AppendChild(xesub2);
                XmlElement xesub3 = xmldoc.CreateElement("count");
                xesub3.InnerText = "0";
                xe1.AppendChild(xesub3);
                root.AppendChild(xe1);//添加到<Employees>节点中 
                return Utility.ConvertXMLToString(xmldoc);
                //return xmldoc;

            }
            

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        var selectCommand = "Function_网点用户_分页查询";
                        cmd.CommandText = selectCommand;
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        cmd.Parameters.Add(new System.Data.SqlClient.SqlParameter("@PageIndex", System.Data.SqlDbType.Int));
                        cmd.Parameters["@PageIndex"].Value = pageIndex;
                        cmd.Parameters.Add(new System.Data.SqlClient.SqlParameter("@PageSize", System.Data.SqlDbType.Int));
                        cmd.Parameters["@PageSize"].Value = pageSize;
                        cmd.Parameters.Add(new System.Data.SqlClient.SqlParameter("@TableName", System.Data.SqlDbType.NVarChar, 100));
                        cmd.Parameters["@TableName"].Value = tableName;
                        cmd.Parameters.Add(new System.Data.SqlClient.SqlParameter("@Orders", System.Data.SqlDbType.NVarChar, 100));
                        cmd.Parameters["@Orders"].Value = order;
                        cmd.Parameters.Add(new System.Data.SqlClient.SqlParameter("@Columns", System.Data.SqlDbType.NVarChar, 100));
                        cmd.Parameters["@Columns"].Value = columns;
                        cmd.Parameters.Add(new System.Data.SqlClient.SqlParameter("@Filters", System.Data.SqlDbType.NVarChar, 500));
                        cmd.Parameters["@Filters"].Value = filters;
                        cmd.Parameters.Add(new System.Data.SqlClient.SqlParameter("@TotalPages", System.Data.SqlDbType.Int));
                        cmd.Parameters["@TotalPages"].Value = 0;
                        cmd.Parameters["@TotalPages"].Direction = System.Data.ParameterDirection.InputOutput;
                        cmd.Parameters.Add(new System.Data.SqlClient.SqlParameter("@TOTALCOUNT", System.Data.SqlDbType.Int));
                        cmd.Parameters["@TOTALCOUNT"].Value = 0;
                        cmd.Parameters["@TOTALCOUNT"].Direction = System.Data.ParameterDirection.InputOutput;

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;

                        DataSet ds = new DataSet();
                        SqlDataAdapter da = new SqlDataAdapter(cmd);
                        da.Fill(ds);
                        XmlDocument xml=new XmlDocument();
                        xml.LoadXml(ds.GetXml());

                        string res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();
                        int totalPage = Convert.ToInt16(cmd.Parameters["@TotalPages"].Value.ToString());
                        int count = Convert.ToInt16(cmd.Parameters["@TOTALCOUNT"].Value.ToString());

                        if (res == "0")
                        {
                            XmlNode root = xmldoc.SelectSingleNode("result");//查找<Employees> 
                            XmlElement xe1 = xmldoc.CreateElement("status");//创建一个<Node>节点 
                            XmlElement xesub1 = xmldoc.CreateElement("code");
                            xesub1.InnerText = "查询成功！";//设置文本节点 
                            xe1.AppendChild(xesub1);         //添加到<Node>节点中 
                            XmlElement xesub2 = xmldoc.CreateElement("page");
                            xesub2.InnerText = totalPage.ToString(); ;
                            xe1.AppendChild(xesub2);
                            XmlElement xesub3 = xmldoc.CreateElement("count");
                            xesub3.InnerText = count.ToString(); ;
                            xe1.AppendChild(xesub3);
                            root.AppendChild(xe1);//添加到<Employees>节点中 

                            XmlNode data = xmldoc.ImportNode(xml.DocumentElement, true);
                            xmldoc.DocumentElement.AppendChild(data);

                            return Utility.ConvertXMLToString(xmldoc);
                            //return xmldoc;
                        }
                        else
                        {
                            XmlNode root = xmldoc.SelectSingleNode("result");//查找<Employees> 
                            XmlElement xe1 = xmldoc.CreateElement("status");//创建一个<Node>节点 
                            XmlElement xesub1 = xmldoc.CreateElement("code");
                            xesub1.InnerText = "查询错误！code=" + res;//设置文本节点 
                            xe1.AppendChild(xesub1);         //添加到<Node>节点中 
                            XmlElement xesub2 = xmldoc.CreateElement("total");
                            xesub2.InnerText = "0";
                            xe1.AppendChild(xesub2);
                            root.AppendChild(xe1);//添加到<Employees>节点中 

                            return Utility.ConvertXMLToString(xmldoc);
                            //return xmldoc;
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
        public string Delete(string user_id, string username, string tableName, string filters, string token)
        {
            if (!Authentication.Check(token))
            {
                return "没有操作权限！";
            }


            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        var selectCommand = "Function_网点用户_删除";
                        cmd.CommandText = selectCommand;
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        cmd.Parameters.Add(new System.Data.SqlClient.SqlParameter("@用户id", SqlDbType.UniqueIdentifier));
                        cmd.Parameters["@用户id"].Value = new Guid(user_id);
                        cmd.Parameters.Add(new System.Data.SqlClient.SqlParameter("@用户名", System.Data.SqlDbType.NVarChar, 50));
                        cmd.Parameters["@用户名"].Value = username;
                        cmd.Parameters.Add(new System.Data.SqlClient.SqlParameter("@TableName", System.Data.SqlDbType.NVarChar, 100));
                        cmd.Parameters["@TableName"].Value = tableName;
                        cmd.Parameters.Add(new System.Data.SqlClient.SqlParameter("@Filters", System.Data.SqlDbType.NVarChar, 100));
                        cmd.Parameters["@Filters"].Value = filters;

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();

                        string res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res == "0")
                        {
                            return "删除成功！";
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
        public string Insert(string user_id, string username, string tableName, string values, string token)
        {
            if (!Authentication.Check(token))
            {
                return "没有操作权限！";
            }


            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        var selectCommand = "Function_网点用户_新建";
                        cmd.CommandText = selectCommand;
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        cmd.Parameters.Add(new System.Data.SqlClient.SqlParameter("@用户id", SqlDbType.UniqueIdentifier));
                        cmd.Parameters["@用户id"].Value = new Guid(user_id);
                        cmd.Parameters.Add(new System.Data.SqlClient.SqlParameter("@用户名", System.Data.SqlDbType.NVarChar, 50));
                        cmd.Parameters["@用户名"].Value = username;
                        cmd.Parameters.Add(new System.Data.SqlClient.SqlParameter("@TableName", System.Data.SqlDbType.NVarChar, 100));
                        cmd.Parameters["@TableName"].Value = tableName;
                        cmd.Parameters.Add(new System.Data.SqlClient.SqlParameter("@values", System.Data.SqlDbType.NVarChar, 500));
                        cmd.Parameters["@values"].Value = values;

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();

                        string res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res == "0")
                        {
                            return "插入成功！";
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
        public string Update(string user_id, string username, string tableName, string values, string filters, string token)
        {
            if (!Authentication.Check(token))
            {
                return "没有操作权限！";
            }


            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        var selectCommand = "Function_网点用户_更新";
                        cmd.CommandText = selectCommand;
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        cmd.Parameters.Add(new System.Data.SqlClient.SqlParameter("@用户id", SqlDbType.UniqueIdentifier));
                        cmd.Parameters["@用户id"].Value = new Guid(user_id);
                        cmd.Parameters.Add(new System.Data.SqlClient.SqlParameter("@用户名", System.Data.SqlDbType.NVarChar, 50));
                        cmd.Parameters["@用户名"].Value = username;
                        cmd.Parameters.Add(new System.Data.SqlClient.SqlParameter("@TableName", System.Data.SqlDbType.NVarChar, 100));
                        cmd.Parameters["@TableName"].Value = tableName;
                        cmd.Parameters.Add(new System.Data.SqlClient.SqlParameter("@values", System.Data.SqlDbType.NVarChar, 500));
                        cmd.Parameters["@values"].Value = values;
                        cmd.Parameters.Add(new System.Data.SqlClient.SqlParameter("@Filters", System.Data.SqlDbType.NVarChar, 500));
                        cmd.Parameters["@Filters"].Value = filters;

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();

                        string res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res == "0")
                        {
                            return "更新成功！";
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
        public string DeleteAll(string user_id, string username, string tableName, string col, string list, string token)
        {
            if (!Authentication.Check(token))
            {
                return "没有操作权限！";
            }


            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    int succ = 0;
                    int fail = 0;
                    string[] arr = list.Split(',');
                    foreach (var item in arr)
                    {

                        using (var cmd = new SqlCommand())
                        {

                            string filters = "";
                            filters = col + "='" + item + "'";

                            var selectCommand = "Function_网点用户_删除";
                            cmd.CommandText = selectCommand;
                            cmd.CommandType = CommandType.StoredProcedure;
                            cmd.Connection = con;

                            cmd.Parameters.Add(new System.Data.SqlClient.SqlParameter("@用户id", SqlDbType.UniqueIdentifier));
                            cmd.Parameters["@用户id"].Value = new Guid(user_id);
                            cmd.Parameters.Add(new System.Data.SqlClient.SqlParameter("@用户名", System.Data.SqlDbType.NVarChar, 50));
                            cmd.Parameters["@用户名"].Value = username;
                            cmd.Parameters.Add(new System.Data.SqlClient.SqlParameter("@TableName", System.Data.SqlDbType.NVarChar, 100));
                            cmd.Parameters["@TableName"].Value = tableName;
                            cmd.Parameters.Add(new System.Data.SqlClient.SqlParameter("@Filters", System.Data.SqlDbType.NVarChar, 100));
                            cmd.Parameters["@Filters"].Value = filters;

                            cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                            cmd.ExecuteNonQuery();

                            string res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                            if (res == "0")
                            {
                                succ++;
                            }
                            else
                            {
                                fail++;
                            }
                        }
                    }

                    string result = "成功删除" + succ + "条记录!";

                    if (fail > 0)
                    {
                        result += "\n(有" + fail + "条删除失败)";
                    }

                    return result;
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
   
        /*
        [WebMethod]
        public XmlDocument Test(string user_id, string type)
        {
            var selectCommand = string.Format("SELECT * FROM [QXT_platform].[dbo].[号码群组] where [用户id]='{0}' and [类型]='{1}'", user_id, type);//组合选择语句
            SqlConnection con = DBConn.CreateConn();//新建数据库连接
            SqlDataAdapter da = new SqlDataAdapter(selectCommand, con);
            DataSet dt = new DataSet();
            da.Fill(dt, "号码群组");
            try
            {
                XmlDocument xml = new XmlDocument();
                xml.LoadXml(dt.GetXml());
                return xml;
            }
            catch (Exception ex)
            {

                XmlDocument xml = new XmlDocument();
                xml.LoadXml("<Error>" + ex.Message + "</Error>");
                return xml;

            }
        }
         */
    }
}
