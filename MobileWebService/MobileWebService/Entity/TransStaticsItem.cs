using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace MobileWebService.Entity
{
    // 交易统计项目
    public class TransStaticsItem
    {
        public string transName;
        public int count;
        public double totalPay;
        public double totalCharge;
        public double totalReturn;
    }
}