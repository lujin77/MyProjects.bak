using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace QueryService
{
    class CheckOutputPara
    {
        private bool _flag;
        private string _date;
        private string _errorMessage;
        private int _count;
        private string[] _detail;

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
        public int count
        {
            get { return _count; }
            set { _count = value; }
        }

        public string[] detail
        {
            get { return _detail; }
            set { _detail = value; }
        }

    }
}
