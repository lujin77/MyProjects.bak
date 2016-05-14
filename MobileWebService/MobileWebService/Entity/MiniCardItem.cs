using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace MobileWebService.Entity
{
    public class MiniCardItem
    {
        public Guid id;
        public string cardNo;
        public string noSection;
        public string SP;
        public string state;
        public Guid getWorkerId;    //领卡人
        public string getWorkerName;
        public Guid workerId;   //业务员
        public string workerName;
        public Guid userId;     //网点用户
        public string userName;
        public DateTime getDate;    //领取时间
        public DateTime assignDate; //分配时间
        public DateTime sellDate;   //销售日期
        public DateTime usedDate;   //使用日期

    }
}