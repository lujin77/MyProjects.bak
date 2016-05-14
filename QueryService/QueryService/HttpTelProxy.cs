using System;
using System.Collections.Generic;
using System.Collections;
using System.Linq;
using System.Text;
using System.Net;
using System.Web;
using System.Security.Policy;
using System.IO;
using System.Timers;

namespace QueryService
{
    class HttpTelProxy
    {
        CookieContainer cookie;
        String methodType;
        String userAgentType;
        String acceptType;
        String contentType;
        bool keepAlive;
        bool allowWriteStreamBuffering;
        ICredentials credentials;
        int maximumResponseHeadersLength = -1;
        String refer;
        String headAccept;
        String headEncoding;
        Encoding encoding;
        private string loginRandomCode;

        public string LoginRandomCode
        {
            get { return loginRandomCode; }
            set { loginRandomCode = value; }
        }

         

        //单例模式
        private static HttpTelProxy instance;
        public static HttpTelProxy getInstance
        {
            get
            {
                if (instance == null)
                {
                    instance = new HttpTelProxy();
                }
                return instance;
            }
        }

        private HttpTelProxy()
        {
            cookie = new CookieContainer();
            
            methodType = MethodType.POST;
            userAgentType = UserAgentType.Default();
            acceptType = AcceptType.Default();
            contentType = ContentType.Default();
            keepAlive = true;
            allowWriteStreamBuffering = true;
            credentials = System.Net.CredentialCache.DefaultCredentials;
            maximumResponseHeadersLength = -1;
            refer = "";
            headAccept = "zh-cn";
            headEncoding = "gzip,deflate";
            encoding = Encoding.UTF8;
            
        }

        

        //Post发送Http请求
        public String PostData(String url, String postData, String refer = "")
        {
            HttpWebRequest request;
            String result;
            request = WebRequest.Create(url) as HttpWebRequest;
            request.Method = MethodType.POST;
            request.KeepAlive = keepAlive;
            request.UserAgent = userAgentType;
            request.Accept = acceptType;
            request.ContentType = contentType;
            request.AllowWriteStreamBuffering = true;
            request.Credentials = System.Net.CredentialCache.DefaultCredentials;
            request.MaximumResponseHeadersLength = maximumResponseHeadersLength;
            request.Headers.Add("Accept-Language", headAccept);
            request.Headers.Add("Accept-Encoding", headEncoding);
            request.Referer = refer;
            request.CookieContainer = cookie;

            //var encoding = Encoding.GetEncoding("GBK");
            //byte[] b = Encoding.ASCII.GetBytes(postData);
            byte[] b = Encoding.UTF8.GetBytes(postData);
            request.ContentLength = b.Length;
            // 提交请求数据
            using (Stream stream = request.GetRequestStream())
            {
                stream.Write(b, 0, b.Length);
                //stream.Close();
            }

            try
            {
                //获取服务器返回的资源   
                using (HttpWebResponse response = (HttpWebResponse)request.GetResponse())
                {
                    using (StreamReader reader = new StreamReader(response.GetResponseStream(), encoding))
                    {
                        if (response.Cookies.Count > 0)
                            cookie.Add(response.Cookies);
                        result = reader.ReadToEnd();
                    }
                }
            }
            catch (WebException wex)
            {
                WebResponse wr = wex.Response;
                using (Stream st = wr.GetResponseStream())
                {
                    using (StreamReader sr = new StreamReader(st, System.Text.Encoding.UTF8))
                    {
                        result = sr.ReadToEnd();
                    }
                }
            }
            catch (Exception ex)
            {
                result = "发生异常\n\r" + ex.Message;
            }
            return result;
        }

        //Get发送Http请求
        public String GetData(String url, String refer = "")
        {
            String result;

            HttpWebRequest request = WebRequest.Create(url) as HttpWebRequest;
            request.Method = MethodType.GET;
            request.KeepAlive = keepAlive;
            request.UserAgent = userAgentType;
            request.Accept = acceptType;
            request.Referer = refer;
            request.CookieContainer = cookie;

            try
            {
                //获取服务器返回的资源   
                using (HttpWebResponse response = (HttpWebResponse)request.GetResponse())
                {
                    using (StreamReader reader = new StreamReader(response.GetResponseStream(), encoding))
                    {
                        if (response.Cookies.Count > 0)
                            cookie.Add(response.Cookies);
                        result = reader.ReadToEnd();
                    }
                }
            }
            catch (WebException wex)
            {
                if (wex.Message == "无法连接到远程服务器")
                {
                    return null;
                }
                WebResponse wr = wex.Response;
                using (Stream st = wr.GetResponseStream())
                {
                    using (StreamReader sr = new StreamReader(st, System.Text.Encoding.Default))
                    {
                        result = sr.ReadToEnd();
                    }
                }
            }
            catch (Exception ex)
            {
                result = "发生异常\n\r" + ex.Message;
            }
            return result;
        }


        class MethodType
        {
            public const String GET = "GET";
            public const String POST = "POST";
        }

        class UserAgentType
        {
            //常用的客户端类型
            public const String FIRE_FOX = "Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.1; Trident/4.0; .NET4.0C; msn OptimizedIE8;ZHCN)";

            //默认参数
            public static String Default()
            {
                return FIRE_FOX;
            }
        }

        class AcceptType
        {
            //常用的接受类型
            public const String GIF = "image/gif";
            public const String BITMAP = "image/x-xbitmap";

            //默认参数
            public static String Default()
            {
                return "image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/x-shockwave-flash, application/vnd.ms-excel, application/vnd.ms-powerpoint, application/msword, */*";
            }
        }

        class ContentType
        {
            public const String APPLICATION = "application/x-www-form-urlencoded";

            //默认参数
            public static String Default()
            {
                return APPLICATION;
            }
        }
    }

}
