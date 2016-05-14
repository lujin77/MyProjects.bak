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

namespace HttpProxy
{
    class HttpProxy
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
        //HttpWebRequest request;
        //HttpWebResponse response;
         

        //单例模式
        private static HttpProxy instance;
        public static HttpProxy getInstance
        {
            get
            {
                if (instance == null)
                {
                    instance = new HttpProxy();
                }
                return instance;
            }
        }

        private HttpProxy()
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
            encoding = Encoding.GetEncoding("gb2312");
            
        }

        /*
        //配置http代理的Get方法基本参数
        private void configGetRequest(String refer)
        {
            request.Method = MethodType.GET;
            request.KeepAlive = keepAlive;
            request.UserAgent = userAgentType;
            request.Accept = acceptType;
            request.Referer = refer;
            request.CookieContainer = cookie;
        }

        //配置http代理的Post方法基本参数
        private void configPostRequest(String refer)
        {
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
        }
         * */

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
            byte[] b = Encoding.ASCII.GetBytes(postData);
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

        //下载验证码图片
        public bool DowloadCheckImg(string url, string savePath)
        {
            bool bol = true;
            HttpWebRequest request = (HttpWebRequest)WebRequest.Create(url);
            request.Method = MethodType.GET;
            request.KeepAlive = keepAlive;
            request.UserAgent = userAgentType;
            request.Accept = acceptType;
            request.Referer = refer;
            request.CookieContainer = cookie;

            try
            {
                //获取服务器返回的资源
                using (HttpWebResponse webResponse = (HttpWebResponse)request.GetResponse())
                {
                    using (Stream sream = webResponse.GetResponseStream())
                    {
                        List<byte> list = new List<byte>();
                        while (true)
                        {
                            int data = sream.ReadByte();
                            if (data == -1)
                                break;
                            list.Add((byte)data);
                        }
                        File.WriteAllBytes(savePath, list.ToArray());
                    }
                }
            }
            catch (WebException ex)
            {
                bol = false;
            }
            catch (Exception ex)
            {
                bol = false;
            }
            return bol;
        }

        //以字节流的形式返回验证码图片
        public byte[] GetCheckImg(string url)
        {
            bool bol = true;
            HttpWebRequest request = (HttpWebRequest)WebRequest.Create(url);
            request.Method = MethodType.GET;
            request.KeepAlive = keepAlive;
            request.UserAgent = userAgentType;
            request.Accept = acceptType;
            request.Referer = refer;
            request.CookieContainer = cookie;

            try
            {
                //获取服务器返回的资源
                using (HttpWebResponse webResponse = (HttpWebResponse)request.GetResponse())
                {
                    using (Stream sream = webResponse.GetResponseStream())
                    {
                        List<byte> list = new List<byte>();
                        while (true)
                        {
                            int data = sream.ReadByte();
                            if (data == -1)
                                break;
                            list.Add((byte)data);
                        }
                        return list.ToArray();
                    }
                }
            }
            catch (WebException ex)
            {
                bol = false;
            }
            catch (Exception ex)
            {
                bol = false;
            }
            return null;
        }

        //取客户端缓存的cookie的值
        public String GetCookie(String url, String name)
        {
            Uri uri = new Uri(url);
            return (cookie.GetCookies(uri))[name].Value;
        }

        //取客户端上一次收到的response报文中返回的cookie
        public String GetResponseCookie(String url, String cookieName, String refer = "")
        {
            String cookieValue = null;
            String result;

            HttpWebRequest request = WebRequest.Create(url) as HttpWebRequest;//as强制转化
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
                    cookieValue = response.Cookies[cookieName].Value;
                    Console.WriteLine("取cookie[" + cookieName + "] = " + cookieValue);
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
            return cookieValue;
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
