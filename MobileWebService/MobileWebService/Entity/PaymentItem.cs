using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace MobileWebService.Entity
{
    [Serializable]
    public class PaymentItem
    {
        public Guid Id;
        public string customerName;
        public double customerBeforeMoney;
        public double customerAfterMoney;
        public string clientType; //客户端类型
        public string telNo;
        public double chargeMoney;
        public DateTime chargeTime;
        public string NoLocation;   //号码归属
        public double moneyBefore;
        public double moneyAfter;
        public string state;
        public string brand;
        public string area;
        public string user_id;  //网点用户
        public string user_name;  //网点用户
        public string work_id;  //员工id
        public string work_name;//员工姓名
        public string manager_name;//业务负责人
        public double repay;    //返款金额
        public string SP;   //service provider 运营商

    }
}