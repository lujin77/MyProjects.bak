using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace MobileWebService.Entity
{
    public class PayMiniCardItem //小卡扣款
    {
        public Guid Id;
        public Guid userId;
        public string userName;//网点用户登录名
        public DateTime addDateTime;//申请时间
        public Guid managerId;//业务员Id
        public string managerName;//业务员登录名
        public double money;
        public string content;
        public string state;
        public Guid workId;//员工Id
        public string work_name;//员工登录名
        public string workType;//员工类型
        public string clientType;//客户端类型
        public string SP;//运营商
        public int cardNum;//小卡张数
        public double moneyBefore;//处理前余额
        public double moneyAfter;//处理后余额
    }
}