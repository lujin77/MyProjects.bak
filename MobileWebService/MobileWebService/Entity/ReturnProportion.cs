using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace MobileWebService.Entity
{
    public class ReturnProportion
    {
        public Guid Id;
        public string ReturnClass;   //返款类型
        public string ReturnName;//返款项目
        public string area; //地区
        public string level;    //用户级别
        public double returnPoint;  //返款比例
        public string content;  //备注
    }
}