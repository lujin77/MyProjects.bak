using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services;
using System.Data.SqlClient;
using QXT_service.Util;
using System.Data;
using System.Data.OleDb;
using System.Collections;
using System.IO;
using System.Xml;

namespace QXT_service
{
    /// <summary>
    /// SmsService 的摘要说明
    /// </summary>
    [WebService(Namespace = "http://tempuri.org/")]
    [WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
    [System.ComponentModel.ToolboxItem(false)]
    // 若要允许使用 ASP.NET AJAX 从脚本中调用此 Web 服务，请取消对下行的注释。
    // [System.Web.Script.Services.ScriptService]
    public class SmsService : System.Web.Services.WebService
    {
        [WebMethod]
        public string SendSMS(string user_id, string username, string message, int smsNum, int count, string tels, string time, string file, string token)
        {
            if (!Authentication.Check(token))
            {
                return "无权限操作！";
                 
            }

            //增加短信长度校验
            int smsNum4validate = calcSmsNum(message);
            if (smsNum4validate == 0)
            {
                return "短信超长！";
            }
            else
            {
                if (smsNum4validate > smsNum) 
                {
                    smsNum = smsNum4validate;
                }
            }

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Function_网点用户_发送短信";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp0 = new SqlParameter("@用户id", SqlDbType.UniqueIdentifier);
                        sp0.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp0);
                        sp0.Value = new Guid(user_id);

                        var sp1 = new SqlParameter("@用户名", SqlDbType.NVarChar, 50);
                        sp1.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp1);
                        sp1.Value = username;

                        var sp1_1 = new SqlParameter("@短信内容", SqlDbType.Text);
                        sp1_1.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp1_1);
                        sp1_1.Value = message;

                        var sp2 = new SqlParameter("@折算短信条数", SqlDbType.Int);
                        sp2.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp2);
                        sp2.Value = smsNum;

                        var sp3 = new SqlParameter("@发送号码数量", SqlDbType.Int);
                        sp3.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp3);
                        sp3.Value = count;

                        var sp4 = new SqlParameter("@号码列表", SqlDbType.Text);
                        sp4.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp4);
                        sp4.Value = tels;

                        if (!string.IsNullOrEmpty(time)) 
                        {
                            var sp5 = new SqlParameter("@定时发送", SqlDbType.DateTime);
                            sp5.Direction = ParameterDirection.Input;
                            cmd.Parameters.Add(sp5);
                            sp5.Value = Convert.ToDateTime(time);
                        }

                        if (!string.IsNullOrEmpty(file)) 
                        {
                            var sp6 = new SqlParameter("@彩信文件", SqlDbType.NVarChar, 50);
                            sp6.Direction = ParameterDirection.Input;
                            cmd.Parameters.Add(sp6);
                            sp6.Value = file;
                        }

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("0"))
                        {
                            return "发送成功！";
                        }
                        else if (res.Equals("3"))
                        {
                            return "余额不足，发送失败！";
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
        public string SaveGroup(string user_id, string name, string data, string token)
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

                    using (var cmd0 = new SqlCommand())
                    {
                        var selectCommand = string.Format("select * from 号码群组 where [用户id]='{0}' and [类型]='群发簿' and [组名称]='{1}'", user_id, name);//组合选择语句
                        cmd0.CommandText = selectCommand;
                        cmd0.CommandType = CommandType.Text;
                        cmd0.Connection = con;
                        using (SqlDataReader sdr = cmd0.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                return "群发簿名称已存在！";
                            }
                        }
                    }

                    Guid id = Guid.NewGuid();

                    using (var cmd = new SqlCommand())
                    {
                        var selectCommand = string.Format("insert into 号码群组 values('{0}', '{1}', '{2}', '群发簿', GETDATE(), '自动保存')", id.ToString(), user_id, name);//组合选择语句
                        cmd.CommandText = selectCommand;
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;
                        int ret = cmd.ExecuteNonQuery();
                        if (ret != 1)
                        {
                            return "保存群发簿失败！";
                        }
                        else
                        {
                            List<string> list = new List<string>();
                            if (!data.Contains(',') && data.Length == 11)
                            {
                                list.Add(data);
                            }
                            else
                            {
                                string[] tels = data.Split(',');
                                foreach (string tel in tels)
                                {
                                    list.Add(tel);
                                }
                            }

                            foreach (string item in list)
                            {
                                using (var cmd1 = new SqlCommand())
                                {
                                    var sql = string.Format("insert into 群发簿 values(NEWID(), '{0}', '{1}')", id.ToString(), item);//组合选择语句
                                    cmd1.CommandText = sql;
                                    cmd1.CommandType = CommandType.Text;
                                    cmd1.Connection = con;
                                    cmd1.ExecuteNonQuery();
                                }
                            }
                            return "保存成功！";
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
        public XmlDocument OpenExcel(string filePath)
        {
            XmlDocument xml = new XmlDocument();

            //string result = "";
            string connStr = "";
            string fileType = System.IO.Path.GetExtension(filePath);
            if (string.IsNullOrEmpty(fileType)) return null;

            if (fileType == ".xls")
                connStr = "Provider=Microsoft.Jet.OLEDB.4.0;" + "Data Source=" + filePath + ";" + ";Extended Properties=\"Excel 8.0;HDR=YES;IMEX=1\"";
            else
                connStr = "Provider=Microsoft.ACE.OLEDB.12.0;" + "Data Source=" + filePath + ";" + ";Extended Properties=\"Excel 12.0;HDR=YES;IMEX=1\"";
            string sql_F = "Select * FROM [{0}]";

            OleDbConnection conn = null;
            OleDbDataAdapter da = null;
            DataTable tblSchema = null;

            // 初始化连接，并打开
            conn = new OleDbConnection(connStr);
            conn.Open();

            // 获取数据源的表定义元数据                        
            tblSchema = conn.GetOleDbSchemaTable(OleDbSchemaGuid.Tables, new object[] { null, null, null, "TABLE" });


            // 初始化适配器
            da = new OleDbDataAdapter();
            // 准备数据，导入DataSet
            DataSet ds = new DataSet();
            da.SelectCommand = new OleDbCommand(String.Format(sql_F, (string)tblSchema.Rows[0]["TABLE_NAME"]), conn);
            try
            {
                da.Fill(ds, (string)tblSchema.Rows[0]["TABLE_NAME"]);
                
                xml.LoadXml(ds.GetXml());
                return xml;
                /*
                DataTable dt = ds.Tables[0];     
                for(int i = 0;  i < dt.Rows.Count;  i++) 
                {
                   result +=  dt.Rows[i]["号码"].ToString() + "\t" + dt.Rows[i]["内容"].ToString() + "\n"; 
                }
                 * */
            }
            catch
            {
                // 关闭连接
                if (conn.State == ConnectionState.Open)
                {
                    conn.Close();
                }
                throw;
            }
            finally
            {
                // 关闭连接
                if (conn.State == ConnectionState.Open)
                {
                    conn.Close();
                }
            }
        }

        [WebMethod]
        public string UploadExcel(string fileName, byte[] filestrem, string token)
        {

            if (!Authentication.Check(token))
            {
                return "无权限操作！";

            }

            XmlDocument xml = new XmlDocument();
            string filePath = Server.MapPath("File/") + fileName;
            //如果已经存在，则删除
            if (IsExistFile(filePath))
            {
                File.Delete(filePath);
            }

            FileStream fs = new FileStream(filePath, FileMode.Create);
            //获得字节数组
            byte[] data = filestrem;
            //开始写入
            fs.Write(data, 0, data.Length);
            //清空缓冲区、关闭流
            fs.Flush();
            fs.Close();

            //解析excel内容
            string result = "";
            string connStr = "";
            string fileType = System.IO.Path.GetExtension(filePath);
            
            if (string.IsNullOrEmpty(fileType)) 
                return null;

            if (fileType == ".xls")
                connStr = "Provider=Microsoft.Jet.OLEDB.4.0;" + "Data Source=" + filePath + ";" + ";Extended Properties=\"Excel 8.0;HDR=YES;IMEX=1\"";
            else
                connStr = "Provider=Microsoft.ACE.OLEDB.12.0;" + "Data Source=" + filePath + ";" + ";Extended Properties=\"Excel 12.0;HDR=YES;IMEX=1\"";
            string sql_F = "Select * FROM [{0}]";

            OleDbConnection conn = null;
            OleDbDataAdapter da = null;
            DataTable tblSchema = null;

            // 初始化连接，并打开
            conn = new OleDbConnection(connStr);
            conn.Open();

            // 获取数据源的表定义元数据                        
            tblSchema = conn.GetOleDbSchemaTable(OleDbSchemaGuid.Tables, new object[] { null, null, null, "TABLE" });

            // 初始化适配器
            da = new OleDbDataAdapter();
            // 准备数据，导入DataSet
            DataSet ds = new DataSet();
            da.SelectCommand = new OleDbCommand(String.Format(sql_F, (string)tblSchema.Rows[0]["TABLE_NAME"]), conn);
            try
            {
                da.Fill(ds, (string)tblSchema.Rows[0]["TABLE_NAME"]);
                da.Dispose();
                xml.LoadXml(ds.GetXml());
                result = Utility.ConvertXMLToString(xml);
                // 关闭连接
                /*
                if (conn.State == ConnectionState.Open)
                {
                    conn.Close();
                }*/
                conn.Close();
                conn.Dispose();
                return result;
            }
            catch
            {
                // 关闭连接
                if (conn.State == ConnectionState.Open)
                {
                    conn.Close();
                    conn.Dispose();
                }
                throw;
            }
            finally
            {
                // 关闭连接
                if (conn.State == ConnectionState.Open)
                {
                    conn.Close();
                    conn.Dispose();
                }
            }
        }

        [WebMethod]
        public string SubmitSMS(string fileName, string user_id, string username, string token)
        {
            if (!Authentication.Check(token))
            {
                return "无权限操作！";

            }

            //解析excel内容
            string filePath = Server.MapPath("File/") + fileName;
            string connStr = "";
            string fileType = System.IO.Path.GetExtension(filePath);

            if (string.IsNullOrEmpty(fileType))
                return null;

            if (fileType == ".xls")
            {
                connStr = "Provider=Microsoft.Jet.OLEDB.4.0;" + "Data Source=" + filePath + ";" + ";Extended Properties=\"Excel 8.0;HDR=YES;IMEX=1\"";
            }
            else
            {
                connStr = "Provider=Microsoft.ACE.OLEDB.12.0;" + "Data Source=" + filePath + ";" + ";Extended Properties=\"Excel 12.0;HDR=YES;IMEX=1\"";
            }
            string sql_F = "Select * FROM [{0}]";

            OleDbConnection conn = null;
            OleDbDataAdapter da = null;
            DataTable tblSchema = null;

            // 初始化连接，并打开
            conn = new OleDbConnection(connStr);
            conn.Open();

            // 获取数据源的表定义元数据                        
            tblSchema = conn.GetOleDbSchemaTable(OleDbSchemaGuid.Tables, new object[] { null, null, null, "TABLE" });

            // 初始化适配器
            da = new OleDbDataAdapter();
            // 准备数据，导入DataSet
            DataSet ds = new DataSet();
            da.SelectCommand = new OleDbCommand(String.Format(sql_F, (string)tblSchema.Rows[0]["TABLE_NAME"]), conn);
            try
            {
                da.Fill(ds, (string)tblSchema.Rows[0]["TABLE_NAME"]);
                da.Dispose();
                DataTable dt = ds.Tables[0];
                int succNum = 0;
                int failNum = 0;
                int totalNum = dt.Rows.Count;
                int totalSmsNum = 0;
                using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
                {
                    try
                    {
                        con.Open();
                         //逐条发送
                        for (int i = 0; i < dt.Rows.Count; i++)
                        {
                            string message = dt.Rows[i]["内容（必填）"].ToString();
                            //长度有效性验证
                            int smsNum = calcSmsNum(message);
                            if (smsNum == 0)
                            {
                                ++succNum;
                                totalSmsNum += smsNum;
                            }
                            else
                            {
                                ++failNum;
                            }
                            string tels = dt.Rows[i]["号码（必填）"].ToString();
                            //result += dt.Rows[i]["号码"].ToString() + "\t" + dt.Rows[i]["内容"].ToString() + "\n";

                            using (var cmd = new SqlCommand())
                            {
                                cmd.CommandText = "Function_网点用户_发送短信";
                                cmd.CommandType = CommandType.StoredProcedure;
                                cmd.Connection = con;

                                var sp0 = new SqlParameter("@用户id", SqlDbType.UniqueIdentifier);
                                sp0.Direction = ParameterDirection.Input;
                                cmd.Parameters.Add(sp0);
                                sp0.Value = new Guid(user_id);

                                var sp1 = new SqlParameter("@用户名", SqlDbType.NVarChar, 50);
                                sp1.Direction = ParameterDirection.Input;
                                cmd.Parameters.Add(sp1);
                                sp1.Value = username;

                                var sp1_1 = new SqlParameter("@短信内容", SqlDbType.Text);
                                sp1_1.Direction = ParameterDirection.Input;
                                cmd.Parameters.Add(sp1_1);
                                sp1_1.Value = message;

                                var sp2 = new SqlParameter("@折算短信条数", SqlDbType.Int);
                                sp2.Direction = ParameterDirection.Input;
                                cmd.Parameters.Add(sp2);
                                sp2.Value = smsNum;

                                var sp3 = new SqlParameter("@发送号码数量", SqlDbType.Int);
                                sp3.Direction = ParameterDirection.Input;
                                cmd.Parameters.Add(sp3);
                                sp3.Value = 1;

                                var sp4 = new SqlParameter("@号码列表", SqlDbType.Text);
                                sp4.Direction = ParameterDirection.Input;
                                cmd.Parameters.Add(sp4);
                                sp4.Value = tels;

                                cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                                cmd.ExecuteNonQuery();
                                var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                                if (res.Equals("0"))
                                {
                                    ++succNum;
                                    totalSmsNum += smsNum;
                                }
                                else
                                {
                                    ++failNum;
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
                // 关闭连接
                conn.Close();
                conn.Dispose();
                File.Delete(filePath);
                return "共提交：" + totalNum + "条记录！\n" + "成功：" + succNum + "条，失败：" + failNum + "条\n" + "共折合：" + totalSmsNum + "条短信";
            }
            catch (Exception ex)
            {
                throw new Exception(ex.Message);
            }
            finally
            {
                // 关闭连接
                if (conn.State == ConnectionState.Open)
                {
                    conn.Close();
                    conn.Dispose();
                    File.Delete(filePath);
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
                        var selectCommand = string.Format("select [号码],[短信内容],[折算短信条数],[提交时间],[定时发送],'发送成功' as 状态 from  [QXT_platform].[dbo].[短信发送报告] {0} order by 提交时间 desc", condition);
                        cmd.CommandText = selectCommand;
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;

                        DataSet ds = new DataSet();
                        SqlDataAdapter da = new SqlDataAdapter(cmd);
                        da.Fill(ds);

                        string filePath = Server.MapPath("File/") + user_id + ".xls";
                        //如果已经存在，则删除
                        if (IsExistFile(filePath))
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
        public string ReSendSMS(string sms_id, string user_id, string username, string token)
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
                        cmd.CommandText = "Function_网点用户_重发短信";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;

                        var sp0 = new SqlParameter("@短信id", SqlDbType.UniqueIdentifier);
                        sp0.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp0);
                        sp0.Value = new Guid(sms_id);

                        var sp1 = new SqlParameter("@用户id", SqlDbType.UniqueIdentifier);
                        sp1.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp1);
                        sp1.Value = new Guid(user_id);

                        var sp2 = new SqlParameter("@用户名", SqlDbType.NChar, 50);
                        sp2.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp2);
                        sp2.Value = username;

                        cmd.Parameters.AddWithValue("@RETURN_VALUE", "").Direction = ParameterDirection.ReturnValue;
                        cmd.ExecuteNonQuery();
                        var res = cmd.Parameters["@RETURN_VALUE"].Value.ToString();

                        if (res.Equals("0"))
                        {
                            return "发送成功！";
                        }
                        else if (res.Equals("3"))
                        {
                            return "余额不足，发送失败！";
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

        /// <summary>   
        /// 检测指定文件是否存在,如果存在则返回true。  
        /// </summary>   
        /// <param name="filePath">文件的绝对路径</param>
        public static bool IsExistFile(string filePath)
        {
            return File.Exists(filePath);
        }

        public static int calcSmsNum(string message)
        {
            if (message.Length <= 70) 
            {
                return 1;
            }
            else if (message.Length > 70 && message.Length <= 130) 
            {
                return 2;
            }
            else if (message.Length > 130 && message.Length <= 190)
            {
                return 3;
            }
            else if (message.Length > 190 && message.Length <= 240)
            {
                return 4;
            }
            else if (message.Length > 240 && message.Length <= 290)
            {
                return 5;
            }
            else if (message.Length > 290 && message.Length <= 320)
            {
                return 6;
            }
            else if (message.Length > 320 && message.Length <= 350)
            {
                return 7;
            }
            else
            {
                return 0;
            }
        }
    }
}
