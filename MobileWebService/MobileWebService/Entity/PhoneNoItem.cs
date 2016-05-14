using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace MobileWebService.Entity
{
    public class PhoneNoItem
    {
        public Guid id;
        public string No;
        public string NoSection;    //号段
        public string inNetPolicy;  //入网政策
        public double NoPrice;  //选号费
        public string area; //分区
        public int weight;
        public string state;
        public DateTime lockDateime;
        public Guid getterId;   //领入人id
        public string getterName;
        public DateTime getDateime;
        public Guid assignerId; //分配人id
        public string assignerName;
        public DateTime assignDateime;
        public Guid userId; //网点用户id
        public string userName;
        public DateTime usedDateime;
        public string sp;
    }
}