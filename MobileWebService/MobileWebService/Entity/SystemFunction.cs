using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace MobileWebService.Entity
{
    [Serializable] //系统功能实体
    public class SystemFunction
    {
        public Guid Id { get; set; }
        public string FunctionName { get; set; }
        public string FunctionPictureName { get; set; }
        public string FunctionNamespace { get; set; }
        public string FunctionScope { get; set; } //功能作用域
        public int Right { get; set; }//功能权值，排序用
    }
}