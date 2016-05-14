using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace MobileWebService.Entity
{
    public class NoticeItem
    {
        public Guid Id;
        public string title;
        public string content;
        public DateTime publishDatetime;
        public string type;
        public Guid publisher_id;
        public bool isEnable;
        public int weight;
        public string clientType;
    }
}