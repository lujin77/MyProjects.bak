using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace QueryService
{
    class CancelInputPara
    {

        public CancelInputPara(string workId, string pass, string chargeId)
        {
            _callName = "cancelCharge";
            _date = FunctionOperations.getNowTime();
            _workId = workId;
            _pass = pass;
            _chargeId = chargeId;
        }

        private string _callName;
        private string _date;//格式yyyyMMddHHmmss
        private string _workId;
        private string _pass;
        private string _chargeId;

        

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
        public string chargeId
        {
            get { return _chargeId; }
            set { _chargeId = value; }
        }
        
    }
}
