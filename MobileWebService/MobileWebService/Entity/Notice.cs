using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace MobileWebService.Entity
{
    public class Notice
    {
        public int total;
        public int totalPage;
        public int pageSize;
        public int currentPageIndex;
        public List<NoticeItem> listOfNotice;

        public Notice()
        {
            listOfNotice = new List<NoticeItem>();
        }
    }
}