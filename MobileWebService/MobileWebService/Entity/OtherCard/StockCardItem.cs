using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace MobileWebService.Entity
{
    /// <summary>
    /// 库存卡类
    /// </summary>
    public class StockCardItem
    {
        public Guid Id;
        public string cardType;
        public string cardName;
        public string cardSeq;
        public string cardPsw;
        public DateTime getDate;    //领取时间
        public Guid getterId;   //领入人id
        public string getterName;
        public DateTime sellDate;   //销售日期
        public Guid userId; //网点用户id
        public string userName;
        public string state;
    }
}