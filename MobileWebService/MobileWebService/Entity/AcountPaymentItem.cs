using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace MobileWebService.Entity
{
    [Serializable]
    public class AcountPaymentItem
    {
        public Guid Id;
        public Guid userId;
        public string userName;
        public string acountName;
        public float payMoney;
        public string payType;
        public string bankName;
        public string subBankName;
        public DateTime payTime;
        public string content;
        public bool isCheck;    //是否划账
        public string state;
        public Guid workerId;
        public string workName;
        public string userType;//客户端类型
     
       
    }
}