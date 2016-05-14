using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace QueryService
{
    class ChargeOutputPara
    {
        private bool _flag;
        private string _date;
        private string _errorMessage;
        private string _chargeId;

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
        public string chargeId
        {
            get { return _chargeId; }
            set { _chargeId = value; }
        }
    }
}
