using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Xml.Serialization;
 

namespace MobileWebService.Entity
{
    [Serializable]
    public class UserVO
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
    }
}