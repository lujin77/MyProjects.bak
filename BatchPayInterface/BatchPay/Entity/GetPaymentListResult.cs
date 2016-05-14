using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace BatchPay.Entity
{
    public class GetPaymentListResult
    {
        public string result;       //处理结果
        public int count;           //请求的号码数
        public int successCount;    //成功获取的条数
        public int failedCount;     //不能获取的条数
        public List<RecordItem> listFail;      //不能获取的号码列表
        public List<PaymentItem> listSucc;     //成功获取的详细信息
    }
}