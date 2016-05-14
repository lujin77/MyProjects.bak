using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace MobileWebService.Entity
{
    public class CardService
    {
        public Guid Id;
        public string SP;   //运营商
        public string serviceName;  //套餐名称
        public bool isFreq;  //是否常用
        public string serviceSpec;  //套餐介绍
    }
}