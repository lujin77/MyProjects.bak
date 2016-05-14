using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace BatchPay
{
    public class Report
    {
        public string result;  //处理结果
        public int count;      //总共处理多少条
        public int successCount;   //成功条数
        public int failedCount;    //失败条数
        public List<RecordItem> list; //失败的记录
        public double totalMoney;      //实际缴费金额
    }
}