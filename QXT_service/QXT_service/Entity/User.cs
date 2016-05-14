using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace QXT_service.Entity
{
    public class User
    {
        public Guid id;
        public string userid;
        public string psw;
        public string name;
        public string sex;
        public string mobile;
        public string tel;
        public string qq;
        public string email;
        public string com_name;
        public string com_addr;
        public string state;
        public string level;
        public int sms;
        public int msms;
        public int reply;
        public Guid manager_id;
        public string sms_sign;
    }
}