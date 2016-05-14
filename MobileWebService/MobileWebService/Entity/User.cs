using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Xml.Serialization;
 

namespace MobileWebService.Entity
{
    [Serializable]
    public class User
    {
        public Guid Id;
        public string loggingName;
        public string password;
        public float money;
        public string tel;
        public string mac;
        public string address;
        public string shopName;
        public string mobilePhone;
        public string pingying;
        public string realName;
        public string indentityNo;
        public Guid manager_id;
        public string managerName;
        public string moneyTail;
        public string level;
        public DateTime registerDatetime;
        public bool isValidate;
        public string btnList;  //可以操作的功能按钮，名称之间用，号分隔
        public string userType;//客户端类型
    }
}