using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Security;
using System.Security.Cryptography;
using System.Web;

namespace QueryService
{
    public  class DesBase64Tool
    {
        //private static string currentPath = System.Environment.CurrentDirectory;
        private static string keyPath = HttpContext.Current.Server.MapPath(@"~/App_Data/key.data");
        private static string ivString = "*&@#asd.";//des加密偏移量
        private static byte[] iv;//des加密偏移量的字节表示
        private static byte[] key = new byte[8]; //存储密钥
        private static bool isInit = false;//是否初始化了

        public DesBase64Tool()
        {
            
        }

        public string getPath()
        {
            return keyPath;
        }

        public static void init()
        {
            try
            {
                iv = Encoding.UTF8.GetBytes(ivString.Substring(0, 8));
                FileStream fs = new FileStream(keyPath, FileMode.Open, FileAccess.Read);
                //创建读取器 
                //StreamReader mySr = new StreamReader(fs);
                //读取文件所有的内容 
                fs.Read(key, 0, 8);
                //key = Encoding.UTF8.GetBytes(content);
                fs.Close();
               // Console.WriteLine(key.ToString());
            }
            catch (System.Exception ex)
            {
                //Console.WriteLine(ex.Message);
                throw ex;
            }
        }
        public static string DESEncode(string encryptString)
        {
            //如果没有初始化
            if (!isInit)
            {
                init();
            }
            byte[] inputByteArray = Encoding.UTF8.GetBytes(encryptString);
            DESCryptoServiceProvider dCSP = new DESCryptoServiceProvider();
            MemoryStream mStream = new MemoryStream();
            CryptoStream cStream = new CryptoStream(mStream, dCSP.CreateEncryptor(key, iv), CryptoStreamMode.Write);
            cStream.Write(inputByteArray, 0, inputByteArray.Length);
            cStream.FlushFinalBlock();
            return Convert.ToBase64String(mStream.ToArray());
        }
        public static string DESDecode(string decryptString)
        {

            if (!isInit)
            {
                init();
            }
            try
            {
               
                byte[] inputByteArray = Convert.FromBase64String(decryptString);
                DESCryptoServiceProvider DCSP = new DESCryptoServiceProvider();
                MemoryStream mStream = new MemoryStream();
                CryptoStream cStream = new CryptoStream(mStream, DCSP.CreateDecryptor(key, iv), CryptoStreamMode.Write);
                cStream.Write(inputByteArray, 0, inputByteArray.Length);
                cStream.FlushFinalBlock();
                return Encoding.UTF8.GetString(mStream.ToArray());
            }
            catch { return string.Empty; }
        }
        /*
        public static string Base64Encode(string encryptString)
        {
            byte[] encbuff = System.Text.Encoding.UTF8.GetBytes(encryptString);
            return Convert.ToBase64String(encbuff);
        }
        public static string Base64Decode(string decryptString)
        {
            byte[] decbuff = Convert.FromBase64String(decryptString);
            return System.Text.Encoding.UTF8.GetString(decbuff);
        }
        */
    }
}
