/**
 * This is a generated class and is not intended for modification.  To customize behavior
 * of this service wrapper you may modify the generated sub-class of this class - UserService.as.
 */
package services.userservice
{
import com.adobe.fiber.core.model_internal;
import com.adobe.fiber.services.wrapper.WebServiceWrapper;
import com.adobe.serializers.utility.TypeUtility;
import mx.rpc.AbstractOperation;
import mx.rpc.AsyncToken;
import mx.rpc.soap.mxml.Operation;
import mx.rpc.soap.mxml.WebService;
import valueObjects.Account;
import valueObjects.User;

[ExcludeClass]
internal class _Super_UserService extends com.adobe.fiber.services.wrapper.WebServiceWrapper
{
    
    // Constructor
    public function _Super_UserService()
    {
        // initialize service control
        _serviceControl = new mx.rpc.soap.mxml.WebService();
        var operations:Object = new Object();
        var operation:mx.rpc.soap.mxml.Operation;

        operation = new mx.rpc.soap.mxml.Operation(null, "UpdateUser");
         operation.resultType = String;
        operations["UpdateUser"] = operation;

        operation = new mx.rpc.soap.mxml.Operation(null, "EditNoList");
         operation.resultType = String;
        operations["EditNoList"] = operation;

        operation = new mx.rpc.soap.mxml.Operation(null, "UpdatePsw");
         operation.resultType = String;
        operations["UpdatePsw"] = operation;

        operation = new mx.rpc.soap.mxml.Operation(null, "Register");
         operation.resultType = String;
        operations["Register"] = operation;

        operation = new mx.rpc.soap.mxml.Operation(null, "Login");
         operation.resultType = valueObjects.User;
        operations["Login"] = operation;

        operation = new mx.rpc.soap.mxml.Operation(null, "AddNoList");
         operation.resultType = String;
        operations["AddNoList"] = operation;

        operation = new mx.rpc.soap.mxml.Operation(null, "getAccount");
         operation.resultType = valueObjects.Account;
        operations["getAccount"] = operation;

        operation = new mx.rpc.soap.mxml.Operation(null, "UpdateSign");
         operation.resultType = String;
        operations["UpdateSign"] = operation;

        operation = new mx.rpc.soap.mxml.Operation(null, "GetSharedUsers");
         operation.resultElementType = String;
        operations["GetSharedUsers"] = operation;

        operation = new mx.rpc.soap.mxml.Operation(null, "GetNoWithGroups");
         operation.resultElementType = String;
        operations["GetNoWithGroups"] = operation;

        operation = new mx.rpc.soap.mxml.Operation(null, "ExportExcel");
         operation.resultType = String;
        operations["ExportExcel"] = operation;

        operation = new mx.rpc.soap.mxml.Operation(null, "EditGroup");
         operation.resultType = String;
        operations["EditGroup"] = operation;

        operation = new mx.rpc.soap.mxml.Operation(null, "DeleteGroup");
         operation.resultType = String;
        operations["DeleteGroup"] = operation;

        operation = new mx.rpc.soap.mxml.Operation(null, "AddGroup");
         operation.resultType = String;
        operations["AddGroup"] = operation;

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


        _serviceControl.service = "UserService";
        _serviceControl.port = "UserServiceSoap";
        wsdl = "http://www.10086yn.net/UserService.asmx?wsdl";
        model_internal::loadWSDLIfNecessary();
    }
    

    /**
      * This method is a generated wrapper used to call the 'UpdateUser' operation. It returns an mx.rpc.AsyncToken whose 
      * result property will be populated with the result of the operation when the server response is received. 
      * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
      * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an mx.rpc.AsyncToken whose result property will be populated with the result of the operation when the server response is received.
      */
    public function UpdateUser(id:String, userid:String, name:String, sex:String, mobile:String, tel:String, qq:String, email:String, com_name:String, com_addr:String, token:String) : mx.rpc.AsyncToken
    {
        model_internal::loadWSDLIfNecessary();
        var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("UpdateUser");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send(id,userid,name,sex,mobile,tel,qq,email,com_name,com_addr,token) ;
        return _internal_token;
    }
     
    /**
      * This method is a generated wrapper used to call the 'EditNoList' operation. It returns an mx.rpc.AsyncToken whose 
      * result property will be populated with the result of the operation when the server response is received. 
      * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
      * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an mx.rpc.AsyncToken whose result property will be populated with the result of the operation when the server response is received.
      */
    public function EditNoList(id:String, userid:String, groupId:String, groupName:String, content:String, tels:String, shared_users:String, token:String) : mx.rpc.AsyncToken
    {
        model_internal::loadWSDLIfNecessary();
        var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("EditNoList");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send(id,userid,groupId,groupName,content,tels,shared_users,token) ;
        return _internal_token;
    }
     
    /**
      * This method is a generated wrapper used to call the 'UpdatePsw' operation. It returns an mx.rpc.AsyncToken whose 
      * result property will be populated with the result of the operation when the server response is received. 
      * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
      * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an mx.rpc.AsyncToken whose result property will be populated with the result of the operation when the server response is received.
      */
    public function UpdatePsw(id:String, userid:String, psw:String, token:String) : mx.rpc.AsyncToken
    {
        model_internal::loadWSDLIfNecessary();
        var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("UpdatePsw");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send(id,userid,psw,token) ;
        return _internal_token;
    }
     
    /**
      * This method is a generated wrapper used to call the 'Register' operation. It returns an mx.rpc.AsyncToken whose 
      * result property will be populated with the result of the operation when the server response is received. 
      * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
      * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an mx.rpc.AsyncToken whose result property will be populated with the result of the operation when the server response is received.
      */
    public function Register(userid:String, password:String, name:String, sex:String, mobile:String, tel:String, qq:String, email:String, com_name:String, com_addr:String) : mx.rpc.AsyncToken
    {
        model_internal::loadWSDLIfNecessary();
        var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("Register");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send(userid,password,name,sex,mobile,tel,qq,email,com_name,com_addr) ;
        return _internal_token;
    }
     
    /**
      * This method is a generated wrapper used to call the 'Login' operation. It returns an mx.rpc.AsyncToken whose 
      * result property will be populated with the result of the operation when the server response is received. 
      * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
      * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an mx.rpc.AsyncToken whose result property will be populated with the result of the operation when the server response is received.
      */
    public function Login(userid:String, password:String) : mx.rpc.AsyncToken
    {
        model_internal::loadWSDLIfNecessary();
        var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("Login");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send(userid,password) ;
        return _internal_token;
    }
     
    /**
      * This method is a generated wrapper used to call the 'AddNoList' operation. It returns an mx.rpc.AsyncToken whose 
      * result property will be populated with the result of the operation when the server response is received. 
      * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
      * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an mx.rpc.AsyncToken whose result property will be populated with the result of the operation when the server response is received.
      */
    public function AddNoList(id:String, userid:String, groupName:String, content:String, tels:String, shared_user:String, token:String) : mx.rpc.AsyncToken
    {
        model_internal::loadWSDLIfNecessary();
        var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("AddNoList");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send(id,userid,groupName,content,tels,shared_user,token) ;
        return _internal_token;
    }
     
    /**
      * This method is a generated wrapper used to call the 'getAccount' operation. It returns an mx.rpc.AsyncToken whose 
      * result property will be populated with the result of the operation when the server response is received. 
      * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
      * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an mx.rpc.AsyncToken whose result property will be populated with the result of the operation when the server response is received.
      */
    public function getAccount(userid:String, password:String) : mx.rpc.AsyncToken
    {
        model_internal::loadWSDLIfNecessary();
        var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("getAccount");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send(userid,password) ;
        return _internal_token;
    }
     
    /**
      * This method is a generated wrapper used to call the 'UpdateSign' operation. It returns an mx.rpc.AsyncToken whose 
      * result property will be populated with the result of the operation when the server response is received. 
      * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
      * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an mx.rpc.AsyncToken whose result property will be populated with the result of the operation when the server response is received.
      */
    public function UpdateSign(id:String, sign:String, token:String) : mx.rpc.AsyncToken
    {
        model_internal::loadWSDLIfNecessary();
        var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("UpdateSign");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send(id,sign,token) ;
        return _internal_token;
    }
     
    /**
      * This method is a generated wrapper used to call the 'GetSharedUsers' operation. It returns an mx.rpc.AsyncToken whose 
      * result property will be populated with the result of the operation when the server response is received. 
      * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
      * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an mx.rpc.AsyncToken whose result property will be populated with the result of the operation when the server response is received.
      */
    public function GetSharedUsers(group_id:String, token:String) : mx.rpc.AsyncToken
    {
        model_internal::loadWSDLIfNecessary();
        var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("GetSharedUsers");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send(group_id,token) ;
        return _internal_token;
    }
     
    /**
      * This method is a generated wrapper used to call the 'GetNoWithGroups' operation. It returns an mx.rpc.AsyncToken whose 
      * result property will be populated with the result of the operation when the server response is received. 
      * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
      * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an mx.rpc.AsyncToken whose result property will be populated with the result of the operation when the server response is received.
      */
    public function GetNoWithGroups(group_id:String, type:String, token:String) : mx.rpc.AsyncToken
    {
        model_internal::loadWSDLIfNecessary();
        var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("GetNoWithGroups");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send(group_id,type,token) ;
        return _internal_token;
    }
     
    /**
      * This method is a generated wrapper used to call the 'ExportExcel' operation. It returns an mx.rpc.AsyncToken whose 
      * result property will be populated with the result of the operation when the server response is received. 
      * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
      * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an mx.rpc.AsyncToken whose result property will be populated with the result of the operation when the server response is received.
      */
    public function ExportExcel(user_id:String, condition:String, token:String) : mx.rpc.AsyncToken
    {
        model_internal::loadWSDLIfNecessary();
        var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("ExportExcel");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send(user_id,condition,token) ;
        return _internal_token;
    }
     
    /**
      * This method is a generated wrapper used to call the 'EditGroup' operation. It returns an mx.rpc.AsyncToken whose 
      * result property will be populated with the result of the operation when the server response is received. 
      * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
      * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an mx.rpc.AsyncToken whose result property will be populated with the result of the operation when the server response is received.
      */
    public function EditGroup(id:String, userid:String, groupId:String, groupName:String, content:String, contract_user_id:String, token:String) : mx.rpc.AsyncToken
    {
        model_internal::loadWSDLIfNecessary();
        var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("EditGroup");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send(id,userid,groupId,groupName,content,contract_user_id,token) ;
        return _internal_token;
    }
     
    /**
      * This method is a generated wrapper used to call the 'DeleteGroup' operation. It returns an mx.rpc.AsyncToken whose 
      * result property will be populated with the result of the operation when the server response is received. 
      * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
      * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an mx.rpc.AsyncToken whose result property will be populated with the result of the operation when the server response is received.
      */
    public function DeleteGroup(id:String, userid:String, groupId:String, deleteType:String, token:String) : mx.rpc.AsyncToken
    {
        model_internal::loadWSDLIfNecessary();
        var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("DeleteGroup");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send(id,userid,groupId,deleteType,token) ;
        return _internal_token;
    }
     
    /**
      * This method is a generated wrapper used to call the 'AddGroup' operation. It returns an mx.rpc.AsyncToken whose 
      * result property will be populated with the result of the operation when the server response is received. 
      * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
      * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an mx.rpc.AsyncToken whose result property will be populated with the result of the operation when the server response is received.
      */
    public function AddGroup(id:String, userid:String, groupName:String, content:String, contract_user_id:String, token:String) : mx.rpc.AsyncToken
    {
        model_internal::loadWSDLIfNecessary();
        var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("AddGroup");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send(id,userid,groupName,content,contract_user_id,token) ;
        return _internal_token;
    }
     
}

}
