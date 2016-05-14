using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Data.SqlClient;
using System.Data;

namespace BatchPay
{
    public class UserValidator
    {
        public static string ValidateLogging(string userName, string passwd, string clientType)
        {
            string userId = "";
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "SELECT top 1 * FROM [MobileManage].[dbo].[网点用户] where [登陆名]='" + userName + "' and [密码]='" + passwd + "' and [客户端类型]='" + clientType + "'";
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;
                        using (SqlDataReader sdr = cmd.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {
                                    userId = sdr["Id"].ToString();
                                    return userId;
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
                return userId;
            }
        }
    }
}