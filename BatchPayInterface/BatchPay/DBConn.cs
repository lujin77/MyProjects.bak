using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Data.SqlClient;

namespace BatchPay
{
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
                        "BatchPayInterfaceConnectionString"].ConnectionString
            };

            return (con);
        }
    }
}