using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace MobileWebService.Entity
{
    public class PhoneNoList
    {
        public int total;
        public int totalPage;
        public int pageSize;
        public int currentPageIndex;
        public List<PhoneNoItem> listOfPhoneNo;

        public PhoneNoList()
        {
            listOfPhoneNo = new List<PhoneNoItem>();
        }
    }
}