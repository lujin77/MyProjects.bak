using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace MobileWebService.Entity
{
    public class SellCardItem
    {
        public Guid Id;
        public string telNo;
        public string miniNo;
        public DateTime sellTime;
        public string passwd;   //开卡服务密码
        public string brand;    //品牌
        public string brandNo;    //品牌编号
        public string cardPrice;    //开卡面值
        public Boolean isOtherService;  //是否有其他服务
        public double chargeMoney;
        public double moneyBefore;
        public double moneyAfter;
        public string state;
        public Guid user_id;  //网点用户
        public string user_name;  //网点用户
        public Guid work_id;  //员工id
        public string work_name;//员工姓名
        public Guid manager_id;  //员工id
        public string manager_name;//业务负责人
        public string SP;   //service provider 运营商
        public string clientType;
        public string noSection;    //号段
        public double noPrice;  //选号费
        public string area; //分区
    }
}