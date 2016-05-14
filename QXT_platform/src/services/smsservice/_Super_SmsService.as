/**
 * This is a generated class and is not intended for modification.  To customize behavior
 * of this service wrapper you may modify the generated sub-class of this class - SmsService.as.
 */
package services.smsservice
{
import com.adobe.fiber.core.model_internal;
import com.adobe.fiber.services.wrapper.WebServiceWrapper;
import com.adobe.serializers.utility.TypeUtility;
import flash.utils.ByteArray;
import mx.rpc.AbstractOperation;
import mx.rpc.AsyncToken;
import mx.rpc.soap.mxml.Operation;
import mx.rpc.soap.mxml.WebService;

[ExcludeClass]
internal class _Super_SmsService extends com.adobe.fiber.services.wrapper.WebServiceWrapper
{
    
    // Constructor
    public function _Super_SmsService()
    {
        // initialize service control
        _serviceControl = new mx.rpc.soap.mxml.WebService();
        var operations:Object = new Object();
        var operation:mx.rpc.soap.mxml.Operation;

        operation = new mx.rpc.soap.mxml.Operation(null, "SendSMS");
         operation.resultType = String;
        operations["SendSMS"] = operation;

        operation = new mx.rpc.soap.mxml.Operation(null, "OpenExcel");
         operation.resultType = Object;
        operations["OpenExcel"] = operation;

        operation = new mx.rpc.soap.mxml.Operation(null, "SaveGroup");
         operation.resultType = String;
        operations["SaveGroup"] = operation;

        operation = new mx.rpc.soap.mxml.Operation(null, "ReSendSMS");
         operation.resultType = String;
        operations["ReSendSMS"] = operation;

        operation = new mx.rpc.soap.mxml.Operation(null, "SubmitSMS");
         operation.resultType = String;
        operations["SubmitSMS"] = operation;

        operation = new mx.rpc.soap.mxml.Operation(null, "ExportExcel");
         operation.resultType = String;
        operations["ExportExcel"] = operation;

        operation = new mx.rpc.soap.mxml.Operation(null, "UploadExcel");
         operation.resultType = String;
        operations["UploadExcel"] = operation;

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


        _serviceControl.service = "SmsService";
        _serviceControl.port = "SmsServiceSoap";
        wsdl = "http://www.10086yn.net/SmsService.asmx?wsdl";
        model_internal::loadWSDLIfNecessary();
    }
    

    /**
      * This method is a generated wrapper used to call the 'SendSMS' operation. It returns an mx.rpc.AsyncToken whose 
      * result property will be populated with the result of the operation when the server response is received. 
      * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
      * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an mx.rpc.AsyncToken whose result property will be populated with the result of the operation when the server response is received.
      */
    public function SendSMS(user_id:String, username:String, messsage:String, smsNum:int, count:int, tels:String, time:String, file:String, token:String) : mx.rpc.AsyncToken
    {
        model_internal::loadWSDLIfNecessary();
        var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("SendSMS");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send(user_id,username,messsage,smsNum,count,tels,time,file,token) ;
        return _internal_token;
    }
     
    /**
      * This method is a generated wrapper used to call the 'OpenExcel' operation. It returns an mx.rpc.AsyncToken whose 
      * result property will be populated with the result of the operation when the server response is received. 
      * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
      * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an mx.rpc.AsyncToken whose result property will be populated with the result of the operation when the server response is received.
      */
    public function OpenExcel(filePath:String) : mx.rpc.AsyncToken
    {
        model_internal::loadWSDLIfNecessary();
        var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("OpenExcel");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send(filePath) ;
        return _internal_token;
    }
     
    /**
      * This method is a generated wrapper used to call the 'SaveGroup' operation. It returns an mx.rpc.AsyncToken whose 
      * result property will be populated with the result of the operation when the server response is received. 
      * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
      * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an mx.rpc.AsyncToken whose result property will be populated with the result of the operation when the server response is received.
      */
    public function SaveGroup(user_id:String, name:String, data:String, token:String) : mx.rpc.AsyncToken
    {
        model_internal::loadWSDLIfNecessary();
        var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("SaveGroup");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send(user_id,name,data,token) ;
        return _internal_token;
    }
     
    /**
      * This method is a generated wrapper used to call the 'ReSendSMS' operation. It returns an mx.rpc.AsyncToken whose 
      * result property will be populated with the result of the operation when the server response is received. 
      * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
      * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an mx.rpc.AsyncToken whose result property will be populated with the result of the operation when the server response is received.
      */
    public function ReSendSMS(sms_id:String, user_id:String, username:String, token:String) : mx.rpc.AsyncToken
    {
        model_internal::loadWSDLIfNecessary();
        var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("ReSendSMS");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send(sms_id,user_id,username,token) ;
        return _internal_token;
    }
     
    /**
      * This method is a generated wrapper used to call the 'SubmitSMS' operation. It returns an mx.rpc.AsyncToken whose 
      * result property will be populated with the result of the operation when the server response is received. 
      * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
      * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an mx.rpc.AsyncToken whose result property will be populated with the result of the operation when the server response is received.
      */
    public function SubmitSMS(fileName:String, user_id:String, username:String, token:String) : mx.rpc.AsyncToken
    {
        model_internal::loadWSDLIfNecessary();
        var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("SubmitSMS");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send(fileName,user_id,username,token) ;
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
      * This method is a generated wrapper used to call the 'UploadExcel' operation. It returns an mx.rpc.AsyncToken whose 
      * result property will be populated with the result of the operation when the server response is received. 
      * To use this result from MXML code, define a CallResponder component and assign its token property to this method's return value. 
      * You can then bind to CallResponder.lastResult or listen for the CallResponder.result or fault events.
      *
      * @see mx.rpc.AsyncToken
      * @see mx.rpc.CallResponder 
      *
      * @return an mx.rpc.AsyncToken whose result property will be populated with the result of the operation when the server response is received.
      */
    public function UploadExcel(fileName:String, filestrem:ByteArray, token:String) : mx.rpc.AsyncToken
    {
        model_internal::loadWSDLIfNecessary();
        var _internal_operation:mx.rpc.AbstractOperation = _serviceControl.getOperation("UploadExcel");
		var _internal_token:mx.rpc.AsyncToken = _internal_operation.send(fileName,filestrem,token) ;
        return _internal_token;
    }
     
}

}
