using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace MobileWebService.Entity
{
    [Serializable]
    public class Worker
    {
        public Guid Id { get; set; }
        public string WorkerName { get; set; }
        public string Password { get; set; }
        public string MAC_Address { get; set; }
        public string CPU_Code { get; set; }
        public string Telephone { get; set; }
        public string RealName { get; set; }
        public string WorkerType { get; set; }
        public Guid SessionId { get; set; }
    }
}