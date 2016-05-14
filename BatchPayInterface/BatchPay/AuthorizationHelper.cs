using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Data.SqlClient;
using System.Data;

namespace BatchPay
{
    public class AuthorizationHelper
    {
        public static string validate(string userId)
        {
            //解密session
            string result = "";

            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = "SELECT * FROM [MobileManage].[dbo].[用户权限验证] where 员工Id='" + userId + "'";
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;
                        using (SqlDataReader sdr = cmd.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {

                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {
                                    result += sdr["功能名称"].ToString() + ",";
                                }

                            }
                        }
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
    }
}