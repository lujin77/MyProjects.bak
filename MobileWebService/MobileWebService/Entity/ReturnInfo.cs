using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace MobileWebService.Entity
{
    //代办费结算，统计信息
    public class ReturnInfo
    {
        public string lastChargeTime;
        public double curMoney;
        public List<ReturnInfoItem> list;
        public int total;
        public double processTotalMoney;
        public double returnTotalMoney;
        public double afterReturnTotalMoney;

        public ReturnInfo()
        {
            list = new List<ReturnInfoItem>();
        }
    }
}