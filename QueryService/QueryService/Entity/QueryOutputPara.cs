using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace QueryService
{
    class QueryOutputPara
    {
        private bool _flag;
        private string _date;
        private string _errorMessage;
        private int _balance;
        private string _fee;
        private string _custName;
        private string _custZone;
        private string _info;
        

        public bool flag
        {
            get { return _flag; }
            set { _flag = value; }
        }
        public string date
        {
            get { return _date; }
            set { _date = value; }
        }
        public string errorMessage
        {
            get { return _errorMessage; }
            set { _errorMessage = value; }
        }
        public int balance
        {
            get { return _balance; }
            set { _balance = value; }
        }
        public string fee
        {
            get { return _fee; }
            set { _fee = value; }
        }
        public string custName
        {
            get { return _custName; }
            set { _custName = value; }
        }
        public string custZone
        {
            get { return _custZone; }
            set { _custZone = value; }
        }
        public string Info
        {
            get { return _info; }
            set { _info = value; }
        }

    }
}
