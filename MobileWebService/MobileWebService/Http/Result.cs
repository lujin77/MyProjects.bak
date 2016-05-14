using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace MobileWebService
{
    public class Result
    {

        private string userName = null;//用户姓名
        private string balance = null;//当前余额
        private string phoneType = null;//套餐类型

        public string UserName
        {
            get { return userName; }
            set { value = userName; }
        }
        public string Balance
        {
            get { return balance; }
            set { value = balance; }
        }
        public string PhoneType
        {
            get { return phoneType; }
            set { value = phoneType; }
        }

        public Result(string username,string balance,string type)
        {
            userName = username;//用户姓名
            this.balance = balance;//当前余额
            phoneType = type;//套餐类型
        }

        public Result()
        {

        }
    }
}