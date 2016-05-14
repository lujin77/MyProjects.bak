using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace MobileWebService.Entity
{
    //卡类销售
    public class SellOtherCardItem
    {
        public Guid Id;
        public Guid userId;
        public string userName;
        public DateTime datetime;
        public string cardType;
        public string cardName;
        public string cardSeq;
        public string cardPsw;
        public string state;
        public Guid workerId;
        public string workerName;
        public double chargeMoney;
        public double moneyBefore;
        public double moneyAfter;
        public string clientType;
    }
}