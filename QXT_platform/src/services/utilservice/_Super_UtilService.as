/**
 * This is a generated class and is not intended for modification.  To customize behavior
 * of this service wrapper you may modify the generated sub-class of this class - UtilService.as.
 */
package services.utilservice
{
import com.adobe.fiber.core.model_internal;
import com.adobe.fiber.services.wrapper.WebServiceWrapper;
import com.adobe.serializers.utility.TypeUtility;
import mx.rpc.AbstractOperation;
import mx.rpc.AsyncToken;
import mx.rpc.soap.mxml.Operation;
import mx.rpc.soap.mxml.WebService;
import valueObjects.Turple;

[ExcludeClass]
internal class _Super_UtilService extends com.adobe.fiber.services.wrapper.WebServiceWrapper
{
    
    // Constructor
    public function _Super_UtilService()
    {
        // initialize service control
        _serviceControl = new mx.rpc.soap.mxml.WebService();
        var operations:Object = new Object();
        var operation:mx.rpc.soap.mxml.Operation;

        operation = new mx.rpc.soap.mxml.Operation(null, "CheckExist");
         operation.resultType = Boolean;
        operations["CheckExist"] = operation;

        operation = new mx.rpc.soap.mxml.Operation(null, "GetStrList");
         operation.resultElementType = String;
        operations["GetStrList"] = operation;

        operation = new mx.rpc.soap.mxml.Operation(null, "Insert");
         operation.resultType = String;
        operations["Insert"] = operation;

        operation = new mx.rpc.soap.mxml.Operation(null, "DeleteAll");
         operation.resultType = String;
        operations["DeleteAll"] = operation;

        operation = new mx.rpc.soap.mxml.Operation(null, "Delete");
         operation.resultType = String;
        operations["Delete"] = operation;

        operation = new mx.rpc.soap.mxml.Operation(null, "Query");
         operation.resultType = String;
        operations["Query"] = operation;

        operation = new mx.rpc.soap.mxml.Operation(null, "GetNoGroups");
         operation.resultElementType = valueObjects.Turple;
        operations["GetNoGroups"] = operation;

        operation = new mx.rpc.soap.mxml.Operation(null, "Update");
         operation.resultType = String;
        operations["Update"] = operation;

        _serviceControl.operations = operations;
        try
        {
            _serviceControl.convertResultHandler = com.adobe.serializers.utility.TypeUtility.convertResultHandler;
        }
        catch (e: Error)
        { /* Flex 3.4 and earlier does not support the convertResultHandler functionality. */ }


        preInitializeService();
        model_internal::initialize();
    }
    
    //init initialization routine here, child class to override
    protected function preInitializeService():void
    {


        _serviceControl.service = "UtilService";
        _serviceControl.port = "UtilServiceSoap";
        wsdl = "http://www.10086yn.net/UtilService.asmx?wsdl";
        model_internal::loadWSDLIfNecessary();
    }
    

    /**
      * This method is a generated wrapper used to call the 'CheckExist' operation. It returns an mx.rpc.AsyncToken whose 
      * result property will be populated with the result of the operation when the server response is received. 
      * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
      * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an mx.rpc.AsyncToken whose result property will be populated with the result of the operation when the server response is received.
      */
    public function CheckExist(table:String, condition:String) : mx.rpc.AsyncToken
    {
        model_internal::loadWSDLIfNecessary();
        var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("CheckExist");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send(table,condition) ;
        return _internal_token;
    }
     
    /**
      * This method is a generated wrapper used to call the 'GetStrList' operation. It returns an mx.rpc.AsyncToken whose 
      * result property will be populated with the result of the operation when the server response is received. 
      * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
      * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an mx.rpc.AsyncToken whose result property will be populated with the result of the operation when the server response is received.
      */
    public function GetStrList(table:String, condition:String, colName:String, token:String) : mx.rpc.AsyncToken
    {
        model_internal::loadWSDLIfNecessary();
        var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("GetStrList");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send(table,condition,colName,token) ;
        return _internal_token;
    }
     
    /**
      * This method is a generated wrapper used to call the 'Insert' operation. It returns an mx.rpc.AsyncToken whose 
      * result property will be populated with the result of the operation when the server response is received. 
      * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
      * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an mx.rpc.AsyncToken whose result property will be populated with the result of the operation when the server response is received.
      */
    public function Insert(user_id:String, username:String, tableName:String, values:String, token:String) : mx.rpc.AsyncToken
    {
        model_internal::loadWSDLIfNecessary();
        var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("Insert");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send(user_id,username,tableName,values,token) ;
        return _internal_token;
    }
     
    /**
      * This method is a generated wrapper used to call the 'DeleteAll' operation. It returns an mx.rpc.AsyncToken whose 
      * result property will be populated with the result of the operation when the server response is received. 
      * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
      * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an mx.rpc.AsyncToken whose result property will be populated with the result of the operation when the server response is received.
      */
    public function DeleteAll(user_id:String, username:String, tableName:String, col:String, list:String, token:String) : mx.rpc.AsyncToken
    {
        model_internal::loadWSDLIfNecessary();
        var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("DeleteAll");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send(user_id,username,tableName,col,list,token) ;
        return _internal_token;
    }
     
    /**
      * This method is a generated wrapper used to call the 'Delete' operation. It returns an mx.rpc.AsyncToken whose 
      * result property will be populated with the result of the operation when the server response is received. 
      * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
      * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an mx.rpc.AsyncToken whose result property will be populated with the result of the operation when the server response is received.
      */
    public function Delete(user_id:String, username:String, tableName:String, filters:String, token:String) : mx.rpc.AsyncToken
    {
        model_internal::loadWSDLIfNecessary();
        var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("Delete");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send(user_id,username,tableName,filters,token) ;
        return _internal_token;
    }
     
    /**
      * This method is a generated wrapper used to call the 'Query' operation. It returns an mx.rpc.AsyncToken whose 
      * result property will be populated with the result of the operation when the server response is received. 
      * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
      * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an mx.rpc.AsyncToken whose result property will be populated with the result of the operation when the server response is received.
      */
    public function Query(pageIndex:String, pageSize:String, tableName:String, order:String, columns:String, filters:String, token:String) : mx.rpc.AsyncToken
    {
        model_internal::loadWSDLIfNecessary();
        var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("Query");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send(pageIndex,pageSize,tableName,order,columns,filters,token) ;
        return _internal_token;
    }
     
    /**
      * This method is a generated wrapper used to call the 'GetNoGroups' operation. It returns an mx.rpc.AsyncToken whose 
      * result property will be populated with the result of the operation when the server response is received. 
      * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
      * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an mx.rpc.AsyncToken whose result property will be populated with the result of the operation when the server response is received.
      */
    public function GetNoGroups(user_id:String, type:String) : mx.rpc.AsyncToken
    {
        model_internal::loadWSDLIfNecessary();
        var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("GetNoGroups");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send(user_id,type) ;
        return _internal_token;
    }
     
    /**
      * This method is a generated wrapper used to call the 'Update' operation. It returns an mx.rpc.AsyncToken whose 
      * result property will be populated with the result of the operation when the server response is received. 
      * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
      * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an mx.rpc.AsyncToken whose result property will be populated with the result of the operation when the server response is received.
      */
    public function Update(user_id:String, username:String, tableName:String, values:String, filters:String, token:String) : mx.rpc.AsyncToken
    {
        model_internal::loadWSDLIfNecessary();
        var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("Update");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send(user_id,username,tableName,values,filters,token) ;
        return _internal_token;
    }
     
}

}
