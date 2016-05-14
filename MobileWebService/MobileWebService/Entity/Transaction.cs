using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace MobileWebService.Entity
{
    public class Transaction
    {
        public Guid Id;
        public Guid userId;
        public string name;
        public string type;
        public string phoneNo;
        public double accountBefore;
        public double processMoney;
        public double returnMoney;
        public double accountAfter;
        public DateTime processTime;
        public string state;
    }
}