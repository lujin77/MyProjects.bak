using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace QueryService
{
    class QueryInputPara
    {
        public QueryInputPara(string workId,string pass,string no)
        {
            _callName = "query";
            _date = FunctionOperations.getNowTime();
            _workId = workId;
            _pass = pass;
            _no = no;
        }
        private string _callName;
        private string _date;//格式yyyyMMddHHmmss
        private string _workId;
        private string _pass;
        private string _no;//电话号码

        
        public string callName
        {
            get { return _callName; }
            set { _callName = value; }
        }
        public string date
        {
            get { return _date; }
            set { _date = value; }
        }
        public string pass
        {
            get { return _pass; }
            set { _pass = value; }
        }
        public string workId
        {
            get { return _workId; }
            set { _workId = value; }
        }
        public string no
        {
            get { return _no; }
            set { _no = value; }
        }
    }
}
