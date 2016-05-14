using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace MobileWebService
{
    public class NetSecurity
    {
        public static string getKey()
        {
            //默认密钥
            string key = "6F5EDFF6C1AE490FA3650920BA611D2E";
            string outputStr = "";
            char[] c = key.ToCharArray();
            //Console.WriteLine("init key:"+key);
            for (int k = 0; k < c.Length; ++k)
            {
                //c[k] = Convert.ToChar(AscII(c[k].ToString()) - (short)('0'));
                c[k] = Convert.ToChar(AscII(c[k].ToString()) % 10);
                outputStr += c[k].ToString();
            }
            //Console.WriteLine("real key:" + outputStr);
            return outputStr;
        }

        public static string encrypt(string src)
        {
            string encrypt_data = "";
            string key = getKey();
            Console.WriteLine("转化后:" + Base64Encode(src));
            char[] c = Base64Encode(src).ToCharArray();
            char[] p = key.ToCharArray();
            for (int i = 0, j = 0; i < c.Length; ++i)
            {
                /*
                //Console.WriteLine(c[i].ToString() + " "+ p[j].ToString());
                c[i] = Convert.ToChar((short)c[i] + (short)(p[j]) - (short)('0'));
                //Console.WriteLine(c[i].ToString());
                if ((short)c[i] > 100)
                {
                    c[i] = Convert.ToChar((short)c[i] % 100 + 40);
                }
                ++j;
                if (j == p.Length)
                {
                    j = 0;
                }
                encrypt_data += c[i].ToString();
                 */
                //c[i] = (char)(c[i] ^ p[j]);
                c[i] = (char)(c[i] - p[j]);
                ++j;
                if (j == p.Length)
                {
                    j = 0;
                }
                encrypt_data += c[i].ToString();
            }
            return encrypt_data;
        }

        public static string decrypt(string src)
        {
            string result = "";
            string decrypt_data = "";
            string key = getKey();
            char[] c = src.ToCharArray();
            char[] p = key.ToCharArray();
            for (int i = 0, j = 0; i < c.Length; ++i)
            {
                /*
                c[i] = Convert.ToChar((short)c[i] - ((short)(p[j]) - (short)('0')));
                if ((short)c[i] < 40)
                {
                    c[i] = Convert.ToChar((short)c[i] + 100 - 40);
                }
                 */
                //c[i] = (char)(c[i] ^ p[j]);
                c[i] = (char)(c[i] + p[j]);
                ++j;
                if (j == p.Length)
                {
                    j = 0;
                }
                decrypt_data += c[i].ToString();
            }
            Console.WriteLine(decrypt_data);
            try
            {
                result = Base64Decode(decrypt_data);
            }
            catch (Exception ex)
            {
                throw new Exception(ex.Message);
            }
            return result;
        }

        public static int AscII(string str)
        {
            byte[] array = new byte[1];
            array = System.Text.Encoding.ASCII.GetBytes(str);
            int asciicode = (short)(array[0]);
            return asciicode;
        }

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
    }
}