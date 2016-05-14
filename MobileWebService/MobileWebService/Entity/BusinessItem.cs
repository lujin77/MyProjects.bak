using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace MobileWebService.Entity
{
    public class BusinessItem
    {
        public Guid Id;
        public string businessName;
        public string businessSpec;
        public Guid userId;
        public string userName;
        public string sp;
        public string no;
        public string passwd;
        public DateTime datetime;
        public string state;
        public string content;
        public string replay;
        public Guid workerId;
        public string workerName;
        public string clientType;
        public double returnMoney; //返款金额, 2012-4-15

    }
}