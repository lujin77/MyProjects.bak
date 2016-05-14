using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace MobileWebService.Entity
{
    [Serializable]
    //号码归属
    public class PhoneNumberBelong
    {
        public Guid Id { get; set; }
        public string HaoDuan { get; set; }//号段
        public string QuHao { get; set; }//区号
        public string ShengFen { get; set; }//省份
        public string City { get; set; }//城市
        public string Area { get; set; }//地区
        public DateTime AddTime { get; set; }//添加时间
    }
}