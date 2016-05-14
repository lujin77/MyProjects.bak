using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace MobileWebService.Entity
{
    [Serializable]
    public class DIC_Content//字典表内容实体
    {
        public string Name { get; set; } //条目名称
        public string Code { get; set; } //条目代码
        public string Category { get; set; }//字典表目录名称
        public bool Enabled { get; set; }//该条目是否可用标识
        public string content { get; set; }//备注
        public string val1 { get; set; }//附件字段1
        public string val2 { get; set; }//附件字段2
    }
}