using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using System.Web;

namespace QueryService
{
    //目的是读取xml文件中存储的用户名和密码
    class UserInfoOper
    {
        //private static string currentPath = System.Environment.CurrentDirectory;
        private static string xmlPath = HttpContext.Current.Server.MapPath(@"~/App_Data/config.xml");
        private User user;
        private XmlDocument xmlDoc;
        private XmlNode ydNode;//移动
        private XmlNode dxNode;//联通


        public string getPath()
        {
            return xmlPath;
        }
        public UserInfoOper()
        {
           
            //创建xml对象
            xmlDoc = new XmlDocument();
            //载入xml文件名
            xmlDoc.Load(xmlPath);
            //读取根节点的所有子节点，放到xn0中
            ydNode = xmlDoc.SelectSingleNode("UserInfos").FirstChild;
            dxNode = xmlDoc.SelectSingleNode("UserInfos").LastChild;

        }
        //移动读取数据
        public User readUserData()
        {
            user = new User();
            foreach (XmlNode node in ydNode.ChildNodes)
            {
                if (node.Name == "name")
                {
                    user.UserName = node.InnerText.Trim();
                }
                if (node.Name == "password")
                {
                    user.UserPassword = node.InnerText.Trim();
                }
            }
            return user;
        }
        //移动写数据
        public void writeUserData(string name,string psd)
        {
            foreach (XmlNode node in ydNode.ChildNodes)
            {
                if (node.Name == "name")
                {
                    node.InnerText = name;
                }
                if (node.Name == "password")
                {
                    node.InnerText = psd;
                }
            }
            xmlDoc.Save(xmlPath);
        }
       
        //电信读取数据
       public User readTelUserData()
       {
           user = new User();
           foreach (XmlNode node in dxNode.ChildNodes)
           {
               if (node.Name == "name")
               {
                   user.UserName = node.InnerText.Trim();
               }
               if (node.Name == "password")
               {
                   user.UserPassword = node.InnerText.Trim();
               }
           }
           return user;
       }
       //电信写数据
       public void writeTelUserData(string name, string psd)
       {
           foreach (XmlNode node in dxNode.ChildNodes)
           {
               if (node.Name == "name")
               {
                   node.InnerText = name;
               }
               if (node.Name == "password")
               {
                   node.InnerText = psd;
               }
           }
           xmlDoc.Save(xmlPath);
       }
    }
}
