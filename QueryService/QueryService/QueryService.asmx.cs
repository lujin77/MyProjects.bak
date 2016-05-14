using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services;

namespace QueryService
{
    /// <summary>
    /// Service1 的摘要说明
    /// </summary>
    [WebService(Namespace = "http://tempuri.org/")]
    [WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
    [System.ComponentModel.ToolboxItem(false)]
    // 若要允许使用 ASP.NET AJAX 从脚本中调用此 Web 服务，请取消对下行的注释。
    // [System.Web.Script.Services.ScriptService]
    public class HttpService : System.Web.Services.WebService
    {
        private static User user = null;
        /*
        [WebMethod]
        public string getUser()
        {
            if (user == null)
            {
                UserInfoOper uio = new UserInfoOper();
                user = uio.readTelUserData();

            }
            return user.UserName;
        }*/
        [WebMethod]
        public Result queryPhoneNOInfo(string phoneNO)
        {
            Result r = new Result();
            
                if (user == null)
                {
                    UserInfoOper uio = new UserInfoOper();
                    user = uio.readTelUserData();

                }
                FunctionOperations fo = new FunctionOperations();
                QueryOutputPara qop = fo.queryUserInfo(user.UserName, user.UserPassword, phoneNO);
                //r = new Result() { UserName = qop.custName, PhoneType = qop.Info, Balance = qop.fee };
                r.UserName = qop.custName;
                r.PhoneType = qop.Info;
                r.Balance = qop.fee;




                return r;
        }
        /*
        [WebMethod]
        public string returnPath()
        {
            return new DesBase64Tool().getPath();

        }
        [WebMethod]
        public string returnPath2()
        {
            return new UserInfoOper().getPath();
        }*/
        
    }

    public class Result
    {


        public string UserName//用户姓名
        {
            get;
            set;
        }
        public string Balance//当前余额
        {
            get;
            set;
        }
        public string PhoneType//套餐类型
        {
            get;
            set;
        }


        public Result()
        {

        }
    }
}