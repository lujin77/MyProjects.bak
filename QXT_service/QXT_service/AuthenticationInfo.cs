using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services.Protocols;

namespace QXT_service
{
    public class AuthenticationInfo  : SoapHeader
    {

        public AuthenticationInfo()
        {
        }

        private string userName;
        private string passWord;

        public AuthenticationInfo(string userName, string passWord)
        {
            this.userName = userName;
            this.passWord = passWord;
        }

        public string UserName
        {
            get { return userName; }
            set { userName = value; }
        }

        public string PassWord
        {
            get { return passWord; }
            set { passWord = value; }
        }

        /*
        public string UserName
        {
            get { return userName; }
            set { userName = value; }

        }

        public string PassWord
        {
            get { return passWord; }
            set { passWord = value; }
        }
         * */
    }

    //用户密码验证类
    public class Authentication
    {
        public static bool Check(string token)
        {
            return (token == "zhq1969");
        }
    }
}