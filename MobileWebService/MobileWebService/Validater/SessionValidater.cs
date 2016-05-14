using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Data.SqlClient;
using System.Data;

namespace MobileWebService.Validater
{
    public class SessionValidater
    {
        //验证session是否有效
        //带解密函数
        public static bool ValidateSessionId(string sessionId)
        {
            //解密session
            sessionId = NetSecurity.decrypt(sessionId);

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "select *  from SYS_Session Where [Id] = '" + sessionId + "'";
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;
                        using (SqlDataReader sdr = cmd.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {
                                    cmd.Dispose();
                                    sdr.Close();
                                    using (var cmd2 = new SqlCommand())
                                    {
                                        cmd2.CommandText = "update SYS_Session set  [上一次操作时间]='" + DateTime.Now.ToString() + "' Where [Id] = '" + sessionId + "'";
                                        cmd2.CommandType = CommandType.Text;
                                        cmd2.Connection = con;
                                        cmd2.ExecuteNonQuery();
                                        return true;
                                    }     
                                }
                                
                            }
                        }
                    }
                    return false;
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

        //验证session是否有效,带超时判断.如果没超时，则刷新上一次操作时间
        //0：无效的session
        //1：验证成功
        //-1：session超时
        public static int ValidateSessionIdWithTime(string sessionId)
        {
            //解密session
            sessionId = NetSecurity.decrypt(sessionId);

            int limitTimeSpane = 0;
            DateTime lastOperateTime = DateTime.MinValue;
            System.TimeSpan timeSpan = new TimeSpan();

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    //提取超时时间限制
                    using (var cmd1 = new SqlCommand())
                    {
                        cmd1.CommandText = "select Code from [MobileManage].[dbo].[URP_DIC_Content] Where [Category] = '服务端限制' and [Name]='系统安全相关_会话超时（分钟）'";
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

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "select *  from SYS_Session Where [Id] = '" + sessionId + "'";
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;
                        using (SqlDataReader sdr = cmd.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {

                                    if (!string.IsNullOrEmpty(sdr["上一次操作时间"].ToString()))
                                        lastOperateTime = Convert.ToDateTime(sdr["上一次操作时间"].ToString());

                                    timeSpan = DateTime.Now - lastOperateTime;
                                    //如果没有超时，则更新上一次操作时间
                                    if (timeSpan.TotalMinutes < limitTimeSpane)
                                    {
                                        cmd.Dispose();
                                        sdr.Close();
                                        using (var cmd2 = new SqlCommand())
                                        {
                                            cmd2.CommandText = "update SYS_Session set  [上一次操作时间]='" + DateTime.Now.ToString() + "' Where [Id] = '" + sessionId + "'";
                                            cmd2.CommandType = CommandType.Text;
                                            cmd2.Connection = con;
                                            cmd2.ExecuteNonQuery();
                                        }
                                        return 1;
                                    }
                                    else
                                    {
                                        //服务超时
                                        return -1;
                                    }
                                } 
                            }
                        }
                    }
                    return 0;
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

        //验证session和对应的user_id是否有效
        public static bool ValidateSessionId(string sessionId, string userId)
        {
            //解密
            sessionId = NetSecurity.decrypt(sessionId);
            userId = NetSecurity.decrypt(userId);

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "select *  from SYS_Session Where [Id] = '" + sessionId + "' and [创建用户Id]='" + userId + "' order by [创建时间] desc";
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;
                        using (SqlDataReader sdr = cmd.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {
                                    cmd.Dispose();
                                    sdr.Close();
                                    using (var cmd2 = new SqlCommand())
                                    {
                                        cmd2.CommandText = "update SYS_Session set  [上一次操作时间]='" + DateTime.Now.ToString() + "' Where [Id] = '" + sessionId + "'";
                                        cmd2.CommandType = CommandType.Text;
                                        cmd2.Connection = con;
                                        cmd2.ExecuteNonQuery();
                                        return true;
                                    }
                                }
                            }
                            else
                            {
                                return false;   //用户名和session不匹配，是盗用的session
                            }
                        }
                    }
                    return false;
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

        //同时验证session和user_id，带超时判断
        //0：无效的session
        //1：验证成功
        //-1：session超时
        public static int ValidateSessionIdWithTime(string sessionId, string userId)
        {
            //解密
            sessionId = NetSecurity.decrypt(sessionId);
            userId = NetSecurity.decrypt(userId);

            int limitTimeSpane = 0;
            DateTime lastOperateTime = DateTime.MinValue;
            System.TimeSpan timeSpan = new TimeSpan();

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    //提取超时时间限制
                    using (var cmd1 = new SqlCommand())
                    {
                        cmd1.CommandText = "select Code from [MobileManage].[dbo].[URP_DIC_Content] Where [Category] = '服务端限制' and [Name]='系统安全相关_会话超时（分钟）'";
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

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "select *  from SYS_Session Where [Id] = '" + sessionId + "' and [创建用户Id]='" + userId + "' order by [创建时间] desc";
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;
                        using (SqlDataReader sdr = cmd.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {

                                    if (!string.IsNullOrEmpty(sdr["上一次操作时间"].ToString()))
                                        lastOperateTime = Convert.ToDateTime(sdr["上一次操作时间"].ToString());

                                    timeSpan = DateTime.Now - lastOperateTime;
                                    //如果没有超时，则更新上一次操作时间
                                    if (timeSpan.TotalMinutes < limitTimeSpane)
                                    {
                                            cmd.Dispose();
                                            sdr.Close();
                                            using (var cmd2 = new SqlCommand())
                                            {
                                                cmd2.CommandText = "update SYS_Session set  [上一次操作时间]='" + DateTime.Now.ToString() + "' Where [Id] = '" + sessionId + "'";
                                                cmd2.CommandType = CommandType.Text;
                                                cmd2.Connection = con;
                                                cmd2.ExecuteNonQuery();
                                            }
                                            return 1;
                                    }
                                    else
                                    {
                                        //服务超时
                                        return -1;
                                    }
                                }
                            }
                        }
                    }
                    return 0;  
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

        public static void DisposeSession(string sessionId) 
        {
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "Proc_SYS_Session_Delete";
                        cmd.CommandType = CommandType.StoredProcedure;
                        cmd.Connection = con;
                        var sp1 = new SqlParameter("@Id", SqlDbType.UniqueIdentifier);
                        sp1.Direction = ParameterDirection.Input;
                        cmd.Parameters.Add(sp1);
                        sp1.Value = new Guid(sessionId);

                        cmd.ExecuteNonQuery();

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
        }
    }
}