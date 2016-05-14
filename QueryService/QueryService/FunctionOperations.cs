using System;
using System.Globalization;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using System.Web;

namespace QueryService
{
    class FunctionOperations
    {
        private static string url = "http://www.qnt100.com/business.do";//发送地址
        private static string workId = "";
        private static string password = "";

        //充值
        public ChargeOutputPara chargePhone(string workId, string pass, string no,int fee)
        {

            ChargeOutputPara cop = new ChargeOutputPara();
            try
            {
                ChargeInputPara cip = new ChargeInputPara(workId, pass, no,fee);
                string postData = JsonConvert.SerializeObject(cip);
                string returnResult = HttpTelProxy.getInstance.PostData(url, "para=" + HttpUtility.UrlEncode(DesBase64Tool.DESEncode(postData)));
                string decodeResult = DesBase64Tool.DESDecode(returnResult);
                cop = JsonConvert.DeserializeObject<ChargeOutputPara>(decodeResult);
            }
            catch (System.Exception ex)
            {
                //Console.WriteLine(ex.Message);
                throw ex;
            }
            return cop;
        }
        //查询
        public QueryOutputPara queryUserInfo(string workId,string pass,string no)
        {
            QueryOutputPara qop = new QueryOutputPara();
            //输入参数
            try
            {
                QueryInputPara qip = new QueryInputPara(workId,pass,no);
                string postData = JsonConvert.SerializeObject(qip);
                string returnResult = HttpTelProxy.getInstance.PostData(url, "para=" + HttpUtility.UrlEncode(DesBase64Tool.DESEncode(postData)));
                string decodeResult = DesBase64Tool.DESDecode(returnResult);
                qop = JsonConvert.DeserializeObject<QueryOutputPara>(decodeResult);
            }
            catch (System.Exception ex)
            {
                //Console.WriteLine(ex.Message);
                throw ex;
            }

            return qop;
        }
        //返销
        public CancelOutputPara cancelCharge(string workId, string pass, string chargeId)
        {
            CancelOutputPara cop = new CancelOutputPara();
            try
            {
                CancelInputPara cip = new CancelInputPara(workId, pass, chargeId);
                string postData = JsonConvert.SerializeObject(cip);
                string returnResult = HttpTelProxy.getInstance.PostData(url, "para=" + HttpUtility.UrlEncode(DesBase64Tool.DESEncode(postData)));
                string decodeResult = DesBase64Tool.DESDecode(returnResult);
                cop = JsonConvert.DeserializeObject<CancelOutputPara>(decodeResult);
            }
            catch (System.Exception ex)
            {
                //Console.WriteLine(ex.Message);
                throw ex;
            }
            return cop;
        }
        //对账
        public CheckOutputPara checkCharge(string workId, string pass, string chargeId)
        {
            CheckOutputPara cop = new CheckOutputPara();
            try
            {
                CheckInputPara cip = new CheckInputPara(workId, pass, chargeId);
                string postData = JsonConvert.SerializeObject(cip);
                string returnResult = HttpTelProxy.getInstance.PostData(url, "para=" + HttpUtility.UrlEncode(DesBase64Tool.DESEncode(postData)));
                string decodeResult = DesBase64Tool.DESDecode(returnResult);
                cop = JsonConvert.DeserializeObject<CheckOutputPara>(decodeResult);
            }
            catch (System.Exception ex)
            {
                //Console.WriteLine(ex.Message);
                throw ex;
            }
            return cop;
        }
        public static string getNowTime()
        {
            return DateTime.Now.ToString("yyyyMMddHHmmss", DateTimeFormatInfo.InvariantInfo);
        }

    }
}
