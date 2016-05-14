using System.Data.SqlClient;

namespace MobileWebService
{
    /// <summary>
    ///DBConn 主要用于创建一个连接
    /// </summary>
    public class DBConn
    {
        public DBConn()
        {

        }

        public static SqlConnection CreateConn()
        {
            var con = new SqlConnection
                          {
                              ConnectionString =
                                  System.Configuration.ConfigurationManager.ConnectionStrings[
                                      "MobileManageConnectionString"].ConnectionString
                          };

            return (con);
        }
    }
}