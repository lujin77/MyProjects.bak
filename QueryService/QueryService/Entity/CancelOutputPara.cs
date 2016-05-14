using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace QueryService
{
    class CancelOutputPara
    {
        private bool _flag;
        private string _date;
        private string _errorMessage;

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
       
    }
}
