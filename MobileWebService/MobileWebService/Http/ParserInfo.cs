using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using System.Web;

namespace HttpProxy
{
    class ParserInfo
    {
        private XmlDocument xmlDoc;
        private XmlNodeList xnl;
        private XmlNode root = null, userBillPart = null, userInfoShowPart = null, c_inputField = null, body = null, aclinicOn = null, char4 = null, tableCol5 = null, tr = null, hidden_condition1Tr = null, hidden_conditionTr =null;

        private string userName = null;//用户姓名
        private string balance = null;//当前余额
        private string phoneType = null;//套餐类型
        private static ParserInfo instance;

        public string UserName
        {
            get { return userName; }
        }
        public string Balance
        {
            get { return balance; }
        }
        public string PhoneType
        {
            get { return phoneType; }
        }

        public ParserInfo(string s)
        {
            init(s);
        }

        private void init(string s)
        {
            xmlDoc = new XmlDocument();
            //xmlDoc.Load(@"D:\444.xml");
            xmlDoc.LoadXml(s);
            root = xmlDoc.SelectSingleNode("parts");
            xnl = root.ChildNodes;
            
            userBillPart = getNode(xnl, "part", "UserBillPart");
            xnl = userBillPart.ChildNodes;
            userInfoShowPart = getNode(xnl, "div", "UserInfoShowPart");
            xnl = userInfoShowPart.ChildNodes;
            c_inputField = getNode(xnl, "div", "c_inputField l_mt");
            xnl = c_inputField.ChildNodes;
            body = getNode(xnl, "div", "body");
            xnl = body.ChildNodes;
            aclinicOn = getNode(xnl, "div", "aclinicOn");
            xnl = aclinicOn.ChildNodes;
            char4 = getNode(xnl, "div", "char4");
            xnl = char4.ChildNodes;
            tableCol5 = getNode(xnl, "table", "col5");
            xnl = tableCol5.ChildNodes;
            tr = xnl[0];
            hidden_condition1Tr = getNode(xnl, "tr", "hidden_condition1");
            hidden_conditionTr = getNode(xnl, "tr", "hidden_condition");

            userName = getInpuAreaByLabel(tr.ChildNodes, "客户名称：");
            Console.WriteLine(userName);
            balance = getInpuAreaByLabel(hidden_conditionTr.ChildNodes, "实时结余：");
            Console.WriteLine(balance);
            phoneType = getInpuAreaByLabel(hidden_condition1Tr.ChildNodes, "产品名称：");
            Console.WriteLine(phoneType);

            
        }

        //nodeName为要查找的节点的名字，atrributeValue为这个节点的属性的值
        private XmlNode getNode(XmlNodeList xnl,string nodeName,string attributeValue)
        {
            foreach (XmlNode node in xnl)
            {
                if (node.Name.Equals(nodeName))
                {
                    for (int i = 0; i < node.Attributes.Count; ++i)
                    {
                        if (node.Attributes[i].Value == attributeValue)
                        {
                            //userInfoShowPart = node;
                            return node;
                        }
                    }

                    //break;
                }
            }
            return null;
        }

        //得到label为这个的的那个列
        private string getInpuAreaByLabel(XmlNodeList xnl,string labelString)
        {
            XmlNode tempNode = null;
            XmlNodeList tempNl = null;
            string s = null;
            foreach(XmlNode node in xnl)
            {
                tempNode = node.FirstChild.FirstChild;
                if(tempNode.FirstChild.InnerText.Equals(labelString))
                {
                    tempNode = tempNode.NextSibling;
                    tempNode = tempNode.FirstChild.FirstChild;
                    s = tempNode.Attributes["title"].Value;
                    if (HttpUtility.HtmlDecode(s) != null)
                    {
                        s = HttpUtility.HtmlDecode(s);
                    }
                    return s;
                }
            }
            return null;
        }

      
    }
}
