using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace MobileWebService.Entity
{
    //返款结算记录
    public class ReturnedItem
    {
        public Guid Id;
        public Guid userId;
        public DateTime datetime;
        public string returnType;
        public Guid operationId;
        public double money;        //处理金额
        public double returnPoint;   //即时返款比例
        public double returnMoney;  //返款金额
    }
}