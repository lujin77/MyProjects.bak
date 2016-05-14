using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace MobileWebService.Entity
{
    public class PayPublicTelItem
    {
        public Guid Id;
        public Guid userId;
        public string userName;
        public DateTime addDateTime;
        public string telType;
        public string telAccount;
        public double money;
        public string content;
        public string state;
        public Guid workId;
        public string work_name;
        public string manager_name;//业务负责人
        public double moneyBefore;
        public double moneyAfter;
        public string clientType;
        public double returnMoney;
        public string area;
        public string location;
        public string customerName;
        public double customerBeforeMoney;
        public double customerAfterMoney;
    }
}