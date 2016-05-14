using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace BatchPay
{
    [Serializable]
    public class PaymentItem
    {
        public string customerName;         //缴费客户名称
        public double customerBeforeMoney;  //缴费后号码余额
        public double customerAfterMoney;   //缴费前号码余额
        public string telNo;        //缴费号码
        public double chargeMoney;  //缴费金额
        public DateTime chargeTime; //缴费时间
        public string SP;           //运营商
        public string NoLocation;   //号码归属
        public string brand;        //品牌
        public string state;        //状态
    }
}