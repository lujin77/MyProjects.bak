using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Web;

namespace HttpProxy
{
    public class FunctionManager
    {

        private static FunctionManager instance;
        private string staffId;

        public string StaffId
        {
            get { return staffId; }
            set { staffId = value; }
        }

        public static FunctionManager Instance
        {
            get 
            { 
                if (instance == null)
                {
                    instance = new FunctionManager();
                }
                return FunctionManager.instance; 
            }
           
        }
 
        private FunctionManager()
        {

        }


        /// <summary>
        /// 获取验证码图片流，在原项目DowloadCheckImg方法中有实现
        /// </summary>
        /// <returns></returns>
        public Stream GetCheckCode()
        {
            //先打开页面
            string srcString = HttpProxy.getInstance.GetData("http://10.168.1.27:8080/");
            if (srcString == null )
            {
                Console.WriteLine("为空，请检查网络");
                return null;
            }
            
                  
            //获取验证码
            byte[] bytes = HttpProxy.getInstance.GetCheckImg("http://10.168.1.27:8080/image?mode=validate&width=60&height=20&random=0.4435475317344276");
            Stream stream = new MemoryStream(bytes);
            return stream; 
        }
        /// <summary>
        /// 登录系统
        /// </summary>
        /// <param name="userName">用户输入的用户名</param>
        /// <param name="passWord">用户输入的密码</param>
        /// <param name="checkCode">用户输入的验证码</param>
        /// <returns></returns>
        public bool LoginSystem(string userName, string passWord, string checkCode)
        {
            bool blnLoggin = false;
            //Todo 特别的，用户输入的密码需要加密，加密后才可以发送给服务器，否则登陆不成功，加密算法提供如下，请整合
            passWord = EncodePsw(passWord);

            //输入验证码后发送数据
            string URI = "http://10.168.1.27:8080/ngboss?wade_randomcode=0.2590274697542145";
            string postString = "service=direct/1/Home/$Form&sp=S0&Form0=STAFF_ID,$FormConditional,$FormConditional$0,$FormConditional$1,EPARCHY_CODE,$FormConditional$2,bLoginSubmit&$FormConditional=T&$FormConditional$0=F&$FormConditional$1=T&$FormConditional$2=F&STAFF_ID=" + userName + "&PASSWORD=" + passWord + "&VERIFY_CODE=" + checkCode + "&EPARCHY_CODE=0871&CLIENT_IP_ADDR=&CLIENT_MAC_ADDR=&LOGIN_TYPE=1&bLoginSubmit=%B5%C7%C2%BC&LOGIN_FLAG=1";
            String srcString = HttpProxy.getInstance.PostData(URI, postString);
            //var fs = new FileStream("C:\\1.txt", FileMode.Create, FileAccess.ReadWrite);
            //var sw = new StreamWriter(fs);
            //fs.SetLength(0);//首先把文件清空了。
            //sw.Write(srcString);//写你的字符串。
            //sw.Close();
            //fs.Close();
            //如果返回的报文中，含有“exceDescPageContent”四个字，默认为登陆不成功,返回True，否则认为登录失败，返回False，方法为if(result.Contain("进入系统"))
            if (getParameter(srcString, "pagename").Equals("Main"))
            {
                blnLoggin = true;
            }
            else if (getParameter(srcString, "pagename").Equals("component.Excedesc"))
            {
                Console.WriteLine(srcString);
                blnLoggin = true;
            }
         
            
            //进入系统（这部分也可以放到别的地方）
            String url = "http://10.168.1.27:8080/ngboss?service=page/Main";
            srcString = HttpProxy.getInstance.GetData(url);
            HttpProxy.getInstance.LoginRandomCode = getParameter(srcString, "loginRandomCode");
            return blnLoggin;
        }

        /// <summary>
        /// 查询用户品牌
        /// </summary>
        /// <param name="userName">工号</param>
        /// <param name="userPhoneNum">用户输入的电话号码</param>
        /// <param name="queryHistoryData">是否查询历史品牌</param>
        /// <returns>返回服务器返回的结果流字符串</returns>
        public string QueryUserBand(string userName, string userPhoneNum, bool queryHistoryData)
        {
            Random rand = new Random();
            int randomcode = rand.Next(100000000,999999999);
            randomcode = 542135914;
            //模拟点击“用户品牌查询”——目的是为了获得SALESERV_JSESSIONID
            String url = "http://10.168.1.27:8080/saleserv/saleserv?service=page/person.sundryquery.other.QueryBrandInfo&RIGHT_CODE=crm9909&LOGIN_TYPE=1&staffId=" + userName + "&subSysCode=NBS&eparchyCode=0871";
            String refer = "http://10.168.1.27:8080/ngboss?service=page/Sidebar&frame_randomcode=" + randomcode.ToString();
            String saleserv = HttpProxy.getInstance.GetResponseCookie(url, "SALESERV_JSESSIONID", refer);

            var queryHistoryDataString = "";
            if(queryHistoryData)
            {
                queryHistoryDataString = "TRUE";
            }

            //实际进行查询品牌处理
            url = "http://10.168.1.27:8080/saleserv/saleserv;SALESERV_JSESSIONID=" + saleserv + "?staffId=" + userName + "&eparchyCode=0871&wade_randomcode=0.32432929629418705";
            refer = "http://10.168.1.27:8080/saleserv/saleserv?service=page/person.sundryquery.other.QueryBrandInfo&RIGHT_CODE=crm9909&LOGIN_TYPE=1&staffId=" + userName + "&subSysCode=NBS&eparchyCode=0871";//必须要有。。。好像他是要验证你是从哪里request的。。。
            String postString = "service=direct/1/person.sundryquery.other.QueryBrandInfo/$Form&sp=S0&Form0=cond_SERIAL_NUMBER,bquery,cond_SET_CHECK_BRAND&cond_SERIAL_NUMBER=" + userPhoneNum + "&bquery=''&default_pagin_pagesize=20&cond_SET_CHECK_BRAND=" + queryHistoryDataString + "&staffId=" + userName + "&subSysCode=saleserv";
            String srcString = HttpProxy.getInstance.PostData(url, postString, refer);
  
            //queryHistoryData对应的POST字符串参数为cond_SET_CHECK_BRAND，他有两个值	TRUE  FALSE
            return srcString;
        }
        /// <summary>
        /// 用户缴费
        /// </summary>
        /// <param name="userName">工号</param>
        /// <param name="userPhoneNum">用户输入的电话号码</param>
        /// <param name="money">用户输入的金额</param>
        /// <returns>返回服务器返回的结果流字符串</returns>
        public string Payment(string userName, string userPhoneNum, string money)
        {
            //点击“计费账务”
            clickJFZW(userName);
            //点击“代理商转账”
            clickDLSZZ(userName);

            //关键参数
            String X_USER_ACCT_ID = null;
            String X_USER_USER_ID = null;
            //提交查询号码
            String result = RequestPhoneNo(userName, userPhoneNum);
            //利用正则表达式取出X_USER_ACCT_ID和X_USER_USER_ID
            X_USER_ACCT_ID = GetHiddenInputValue("X_USER_ACCT_ID", result);
            X_USER_USER_ID = GetHiddenInputValue("X_USER_USER_ID", result);


            string url = "http://10.168.1.27:8080/acctmanm/acctmanm?staffId=" + userName + "&eparchyCode=0871&wade_randomcode=0.07099627822870769";
            string refer = "http://10.168.1.27:8080/acctmanm/acctmanm?service=page/amcharge.agentmovefee.AgentMoveFee&listener=myInitialize&RIGHT_CODE=ASMAGENTMOVEFEE&LOGIN_RANDOM_CODE=2011071438614939&LOGIN_TYPE=1&staffId=" + userName + "&subSysCode=NBS&eparchyCode=0871";//必须要有。。。好像他是要验证你是从哪里request的。。。
            String postString = "service=direct/1/amcharge.agentmovefee.AgentMoveFee/$Form&sp=S0&Form0=cond_SERIAL_TYPE,cond_AGENT_SERIAL_NUMBER,bqueryAgenttop,bquerytop,cond_TRADE_FEE,movefee&cond_SERIAL_TYPE=0&cond_AGENT_SERIAL_NUMBER=13808704459&X_AGENT_LEFTFEE=3215.00&X_AGENT_ACCT_ID=7111031017307655&X_AGENT_USER_ID=7106110503891116&X_ACCT_BALANCE_ID=2011031134679008&X_CHNL_CODE=%7CA0AXXM76&SERIAL_NUMBER=13808704459&cond_NET_TYPE_CODE=&cond_ID_TYPE=0&cond_SERIAL_NUMBER=" + userPhoneNum + "&POPU_INFOS=%7B%22SERIAL_NUMBER%22%3A%22%B5%E7%BB%B0%BA%C5%C2%EB%A3%BA" + userPhoneNum + "%22%2C%22RSRV_STRQ1%22%3A%22VPN%A3%BA%C0%A5%C3%F7%CD%AC%B7%BD%BB%E3%D6%C7%BF%C6%BC%BC%D3%D0%CF%DE%B9%AB%CB%BE.%22%2C%22RSRV_STRQ2%22%3A%22%B8%C3%BF%CD%BB%A7%CA%C7%B2%CA%C1%E5%A1%A2%B2%CA%D0%C5%A1%A2%CA%D6%BB%FA%C9%CF%CD%F8%B5%C4%B3%C1%C4%AC%BF%CD%BB%A7%A3%AC%C7%EB%D2%FD%B5%BC%D0%AD%D6%FA%BF%AA%CD%A8%BF%AA%CD%A8%B2%CA%C1%E5%A1%A2%B2%CA%D0%C5%A1%A2%CA%D6%BB%FA%C9%CF%CD%F8%A1%A3%22%2C%22RSRV_STR3%22%3A%22%D3%C3%BB%A7%C6%B7%C5%C6%3A%B6%AF%B8%D0%B5%D8%B4%F8%22%2C%22RSRV_STR4%22%3A%22%B5%B1%C7%B0%B2%FA%C6%B7%3A%C3%DC%D3%EF%C1%AA%C3%CB%28%D0%C2%29%22%7D&cond_X_USER_COUNT=0&cond_X_ACCT_COUNT=&cond_X_HAVE_SELECTED=false&cond_X_POPUP_VALUEMAP=&cond_GROUP_ID=&X_USER_ACCT_ID=" + X_USER_ACCT_ID + "&X_USER_USER_ID=" + X_USER_USER_ID + "&SERIAL_NUMBER_B=" + userPhoneNum + "&cond_TRADE_FEE=" + money + "&movefee=+%D7%AA+%D5%CA+&userinfoback_ACCT_ID=&userinfoback_SERIAL_NUMBER=&userinfoback_USER_ID=&userinfoback_NET_TYPE_CODE=&userinfoback_PAY_MODE_CODE=&userinfoback_ROUTE_EPARCHY_CODE=&userinfoback_BRAND=&userinfoback_PAY_NAME=&userinfoback_ALLBOWE_FEE=&printData_BRAND=&printData_NOTE_TYPE=&printData_CHARGE_ID=&printData_PRINT_PARTITION_ID=&printData_ACCT_ID=&printData_SERIAL_NUMBER=&printData_USER_ID=&printData_TRADE_FEE=&printData_PAY_NAME=&printData_AGENTFLAG=&printData_ALL_NEW_BALANCE=&X_AGENT_CODING_STR=&X_USER_CODING_STR=";

            String srcString = HttpProxy.getInstance.PostData(url, postString, refer);

            return srcString;
        }

        /// <summary>
        /// 密码加密算法
        /// </summary>
        /// <param name="str"></param>
        /// <returns></returns>
        public static string EncodePsw(string str)
        {
            Random rand = new Random();
            char[] chars = new char[] { '!', '@', '#', '$', '%', '^', '&', '*', '(', ')' };
            int len = str.Length;
            string rs = "";
            for (int i = 0; i < len; i++)
            {
                rs += "&#" + charCodeAt(str, i) + ";";
                for (int j = 0; j < 4; j++)
                {

                    rs += chars[rand.Next(0, 10)];
                }

            }

            return UrlEncode(rs); ;
        }
        /// <summary>
        /// 密码加密内部算法
        /// </summary>
        /// <param name="s"></param>
        /// <param name="n"></param>
        /// <returns></returns>
        public static byte charCodeAt(string s, int n)
        {
            byte[] bytes = System.Text.Encoding.Default.GetBytes(s);
            return bytes[n];
        }
        /// <summary>
        /// URL编码
        /// </summary>
        /// <param name="str"></param>
        /// <returns></returns>
        public static string UrlEncode(string str)
        {
            var sb = new StringBuilder();
            byte[] byStr = System.Text.Encoding.UTF8.GetBytes(str); //默认是System.Text.Encoding.Default.GetBytes(str)
            for (int i = 0; i < byStr.Length; i++)
            {
                sb.Append(@"%" + Convert.ToString(byStr[i], 16));
            }
            
            return (sb.ToString());
        }

        private void clickJFZW(string userName)//点击“计费账务”
        {
            //先点击“计费账务”页面，目的是刷新cookie
            string url = "http://10.168.1.27:8080/ngboss?service=ajaxDirect/1/Nav/Nav/javascript/MenuPart&pagename=Nav&eventname=queryMenuData&&STAFF_ID=" + userName + "&SUBSYS_CODE=BIL&staffId=" + userName + "&subSysCode=NBS&eparchyCode=0871&LOGIN_LOG_ID=" + HttpProxy.getInstance.LoginRandomCode + "&partids=MenuPart";
            string refer = "http://10.168.1.27:8080/ngboss?service=page/Nav";
            string srcString = HttpProxy.getInstance.GetData(url, refer);
        }
        private void clickDLSZZ(string userName)//点击“代理商转账”
        {
            //先请求“代理商转账”页面-目的是为了修改cookieCntainer，最好是把cookieContainer设置成全局变量这样，修改起来就比较方便了
            string url = "http://10.168.1.27:8080/acctmanm/acctmanm?service=page/amcharge.agentmovefee.AgentMoveFee&listener=myInitialize&RIGHT_CODE=ASMAGENTMOVEFEE&LOGIN_RANDOM_CODE=" + HttpProxy.getInstance.LoginRandomCode + "&LOGIN_TYPE=1&staffId=" + userName + "&subSysCode=NBS&eparchyCode=0871&LOGIN_LOG_ID=" + HttpProxy.getInstance.LoginRandomCode;
            string refer = "http://10.168.1.27:8080/ngboss?service=page/Sidebar&frame_randomcode=352546961";

            string srcString = HttpProxy.getInstance.GetData(url, refer);
        }
        //查询代理商信息
        public string queryAgentInfo(string userName,string agentServiceNO)
        {
            clickJFZW(userName);
            clickDLSZZ(userName);
            String url = "http://10.168.1.27:8080/acctmanm/acctmanm?service=ajaxDirect/1/amcharge.agentmovefee.AgentMoveFee/amcharge.agentmovefee.AgentMoveFee/javascript/AgentBillPart&pagename=amcharge.agentmovefee.AgentMoveFee&eventname=qryAgentBill&staffId=" + userName + "&subSysCode=acctmanm&eparchyCode=0871&LOGIN_LOG_ID=" + HttpProxy.getInstance.LoginRandomCode + "&partids=AgentBillPart&ajaxSubmitType=post&ajax_randomcode=0.40148226485548266";
            String refer = "http://10.168.1.27:8080/acctmanm/acctmanm?service=page/amcharge.agentmovefee.AgentMoveFee&listener=myInitialize&RIGHT_CODE=ASMAGENTMOVEFEE&LOGIN_RANDOM_CODE=" + HttpProxy.getInstance.LoginRandomCode + "&LOGIN_TYPE=1&staffId=" + userName + "&subSysCode=NBS&eparchyCode=0871&LOGIN_LOG_ID=" + HttpProxy.getInstance.LoginRandomCode;
            String postString = "cond_AGENT_SERIAL_NUMBER="+ agentServiceNO + "&bqueryAgenttop=%20%E6%9F%A5%20%E8%AF%A2%20&X_AGENT_LEFTFEE=&X_AGENT_ACCT_ID=&X_AGENT_USER_ID=&X_ACCT_BALANCE_ID=&X_CHNL_CODE=&SERIAL_NUMBER=&cond_ID_TYPE=0&cond_SERIAL_NUMBER=&bquerytop=%20%E6%9F%A5%20%E8%AF%A2%20&POPU_INFOS=&cond_X_USER_COUNT=&cond_X_ACCT_COUNT=&cond_X_HAVE_SELECTED=false&cond_X_POPUP_VALUEMAP=&cond_GROUP_ID=&X_USER_ACCT_ID=&X_USER_USER_ID=&SERIAL_NUMBER_B=&cond_TRADE_FEE=0.00&cond_NOTE_TYPE=1&movefee=%20%E8%BD%AC%20%E5%B8%90%20&userinfoback_ACCT_ID=&userinfoback_SERIAL_NUMBER=&userinfoback_USER_ID=&userinfoback_NET_TYPE_CODE=&userinfoback_PAY_MODE_CODE=&userinfoback_ROUTE_EPARCHY_CODE=&userinfoback_BRAND=&userinfoback_PAY_NAME=&userinfoback_ALLBOWE_FEE=&printData_BRAND=&printData_NOTE_TYPE=&printData_CHARGE_ID=&printData_PRINT_PARTITION_ID=&printData_ACCT_ID=&printData_SERIAL_NUMBER=&printData_USER_ID=&printData_TRADE_FEE=&printData_PAY_NAME=&printData_AGENTFLAG=&printData_ALL_NEW_BALANCE=&X_AGENT_CODING_STR=&X_USER_CODING_STR=&cond_SERIAL_TYPE=0&cond_NET_TYPE_CODE=";
            string srcString = HttpProxy.getInstance.PostData(url, postString, refer);
            return srcString;

        }

        //查询手机号码信息——单独的功能暴露出来给别人使用，和下边的RequestPhoneNo差不多，只是那个是给内部使用，不需要重复点击那两个页面而已
        public string queryPhoneNOInfo(string userName,string phoneNO)
        {
            clickJFZW(userName);
            clickDLSZZ(userName);
            String url = "http://10.168.1.27:8080/acctmanm/acctmanm?service=ajaxDirect/1/amcharge.agentmovefee.AgentMoveFee/amcharge.agentmovefee.AgentMoveFee/javascript/UserBillPart&pagename=amcharge.agentmovefee.AgentMoveFee&eventname=qryuserDeposit&staffId=" + userName + "&subSysCode=acctmanm&eparchyCode=0871&LOGIN_LOG_ID=" + HttpProxy.getInstance.LoginRandomCode + "&partids=UserBillPart&ajaxSubmitType=post&ajax_randomcode=0.8067738364404495";
            String refer = "http://10.168.1.27:8080/acctmanm/acctmanm?service=page/amcharge.agentmovefee.AgentMoveFee&listener=myInitialize&RIGHT_CODE=ASMAGENTMOVEFEE&LOGIN_RANDOM_CODE=" + HttpProxy.getInstance.LoginRandomCode + "&LOGIN_TYPE=1&staffId=" + userName + "&subSysCode=NBS&eparchyCode=0871&LOGIN_LOG_ID=" + HttpProxy.getInstance.LoginRandomCode;
            String postString = "cond_AGENT_SERIAL_NUMBER=&bqueryAgenttop=%20%E6%9F%A5%20%E8%AF%A2%20&X_AGENT_LEFTFEE=&X_AGENT_ACCT_ID=&X_AGENT_USER_ID=&X_ACCT_BALANCE_ID=&X_CHNL_CODE=&SERIAL_NUMBER=&cond_ID_TYPE=0&cond_SERIAL_NUMBER=" + phoneNO + "&bquerytop=%20%E6%9F%A5%20%E8%AF%A2%20&POPU_INFOS=&cond_X_USER_COUNT=&cond_X_ACCT_COUNT=&cond_X_HAVE_SELECTED=false&cond_X_POPUP_VALUEMAP=&cond_GROUP_ID=&X_USER_ACCT_ID=&X_USER_USER_ID=&SERIAL_NUMBER_B=&cond_TRADE_FEE=0.00&cond_NOTE_TYPE=1&movefee=%20%E8%BD%AC%20%E5%B8%90%20&userinfoback_ACCT_ID=&userinfoback_SERIAL_NUMBER=&userinfoback_USER_ID=&userinfoback_NET_TYPE_CODE=&userinfoback_PAY_MODE_CODE=&userinfoback_ROUTE_EPARCHY_CODE=&userinfoback_BRAND=&userinfoback_PAY_NAME=&userinfoback_ALLBOWE_FEE=&printData_BRAND=&printData_NOTE_TYPE=&printData_CHARGE_ID=&printData_PRINT_PARTITION_ID=&printData_ACCT_ID=&printData_SERIAL_NUMBER=&printData_USER_ID=&printData_TRADE_FEE=&printData_PAY_NAME=&printData_AGENTFLAG=&printData_ALL_NEW_BALANCE=&X_AGENT_CODING_STR=&X_USER_CODING_STR=&cond_SERIAL_TYPE=0&cond_NET_TYPE_CODE=";
            string srcString = HttpProxy.getInstance.PostData(url, postString, refer);
            return srcString;
            return null;
        }
        /// <summary>
        /// 获取隐藏域的值
        /// </summary>
        /// <param name="inputName"></param>
        /// <param name="webContent"></param>
        /// <returns></returns>
        private string GetHiddenInputValue(string inputName, string webContent)
        {
            string patternRegion = "input[^>]*?\\bvalue=['\"]?(?<value>[^\"].*?)['\"]?\\b[^>]*?type=\"hidden\"[^>]*?\\bname=['\"]?(?<name>[^\"].*?)['\"]?\\b[^>]*?";


            RegexOptions regexOptions = RegexOptions.Singleline | RegexOptions.IgnoreCase | RegexOptions.Compiled;

            Regex regexRegion = new Regex(patternRegion, regexOptions); //解析Region的正则

            MatchCollection mc = regexRegion.Matches(webContent); //code为要分析的网页代码
            foreach (Match m in mc)
            {
                string strName = m.Groups["name"].Value;//取匹配到的命名组的值
                if (!string.IsNullOrEmpty(strName))
                {
                    if (strName.Equals(inputName))
                    {
                        string strValue = m.Groups["value"].Value;
                        return strValue;

                    }
                }
            }
            return null;

        }
        /// <summary>
        /// 查询手机号
        /// </summary>
        /// <param name="userName">工号</param>
        /// <param name="phone"></param>
        /// <returns></returns>
        private string RequestPhoneNo(string userName, string phone)
        {
            String url = "http://10.168.1.27:8080/acctmanm/acctmanm?service=ajaxDirect/1/amcharge.agentmovefee.AgentMoveFee/amcharge.agentmovefee.AgentMoveFee/javascript/UserBillPart&pagename=amcharge.agentmovefee.AgentMoveFee&eventname=qryuserDeposit&staffId=" +  userName+ "&subSysCode=acctmanm&eparchyCode=0871&partids=UserBillPart&ajaxSubmitType=post&ajax_randomcode=0.8067738364404495";
            String refer = "http://10.168.1.27:8080/acctmanm/acctmanm?service=page/amcharge.agentmovefee.AgentMoveFee&listener=myInitialize&RIGHT_CODE=ASMAGENTMOVEFEE&staffId=" + userName + "&subSysCode=NBS&eparchyCode=0871";
            String postString = "cond_AGENT_SERIAL_NUMBER=13808704459&bqueryAgenttop=%20%E6%9F%A5%20%E8%AF%A2%20&X_AGENT_LEFTFEE=2836.97&X_AGENT_ACCT_ID=7111031017307655&X_AGENT_USER_ID=7106110503891116&X_ACCT_BALANCE_ID=2011031134679008&X_CHNL_CODE=%7CA0AXXM76&SERIAL_NUMBER=13808704459&cond_ID_TYPE=0&cond_SERIAL_NUMBER=" + phone + "&bquerytop=%20%E6%9F%A5%20%E8%AF%A2%20&POPU_INFOS=&cond_X_USER_COUNT=&cond_X_ACCT_COUNT=&cond_X_HAVE_SELECTED=false&cond_X_POPUP_VALUEMAP=&cond_GROUP_ID=&X_USER_ACCT_ID=&X_USER_USER_ID=&SERIAL_NUMBER_B=&cond_TRADE_FEE=0.00&cond_NOTE_TYPE=1&movefee=%20%E8%BD%AC%20%E5%B8%90%20&userinfoback_ACCT_ID=&userinfoback_SERIAL_NUMBER=&userinfoback_USER_ID=&userinfoback_NET_TYPE_CODE=&userinfoback_PAY_MODE_CODE=&userinfoback_ROUTE_EPARCHY_CODE=&userinfoback_BRAND=&userinfoback_PAY_NAME=&userinfoback_ALLBOWE_FEE=&printData_BRAND=&printData_NOTE_TYPE=&printData_CHARGE_ID=&printData_PRINT_PARTITION_ID=&printData_ACCT_ID=&printData_SERIAL_NUMBER=&printData_USER_ID=&printData_TRADE_FEE=&printData_PAY_NAME=&printData_AGENTFLAG=&printData_ALL_NEW_BALANCE=&X_AGENT_CODING_STR=&X_USER_CODING_STR=&cond_SERIAL_TYPE=0&cond_NET_TYPE_CODE=";
            string srcString = HttpProxy.getInstance.PostData(url, postString, refer);
            return srcString;
        }
        /// <summary>
        /// 退出系统
        /// </summary>
        public string Exit()
        {
            string URI = "http://10.168.1.27:8080/ngboss?service=page/Logout&listener=proxyLogout&LOGIN_TYPE=1";
            string srcString = HttpProxy.getInstance.GetData(URI);
            Console.WriteLine("---退出----\n" + srcString);
            Console.WriteLine("*************************************");
            return srcString;
        }

        public string getParameter(string originalString, string parameter)
        {
            string content;
            string regexString = parameter + @"=('|"").*?('|"")";//匹配的格式为parameter='**********'或者parameter="**********"
            Regex r = new Regex(regexString);

            if (r.IsMatch(originalString))
            {
                Match m = r.Match(originalString);
                content = m.Value.Substring(parameter.Length + 2, m.Length - parameter.Length - 3);
                return content;
            }
            return null;
        }
    }
}
