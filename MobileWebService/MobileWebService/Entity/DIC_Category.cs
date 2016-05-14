using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace MobileWebService.Entity
{
    [Serializable]
    public class DIC_Category  //字典表目录实体
    {
        public string Category { get; set; }//字典表目录名称
        public bool Editable { get; set; }//是否可编辑标识
    }
}