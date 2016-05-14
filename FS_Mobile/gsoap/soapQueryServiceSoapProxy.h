/* soapQueryServiceSoapProxy.h
   Generated by gSOAP 2.8.3 from soapProxy.h

Copyright(C) 2000-2011, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under one of the following licenses:
1) GPL or 2) Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#ifndef soapQueryServiceSoapProxy_H
#define soapQueryServiceSoapProxy_H
#include "soapH.h"
class QueryServiceSoap
{   public:
	/// Runtime engine context allocated in constructor
	struct soap *soap;
	/// Endpoint URL of service 'QueryServiceSoap' (change as needed)
	const char *endpoint;
	/// Constructor allocates soap engine context, sets default endpoint URL, and sets namespace mapping table
	QueryServiceSoap()
	{ soap = soap_new(); endpoint = "http://localhost:2556/QueryService.asmx"; if (soap && !soap->namespaces) { static const struct Namespace namespaces[] = 
{
	{"SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope", NULL},
	{"SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://www.w3.org/*/soap-encoding", NULL},
	{"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
	{"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL},
	{"ns2", "http://microsoft.com/wsdl/types/", NULL, NULL},
	{"ns10", "http://tempuri.org/QueryServiceSoap12", NULL, NULL},
	{"ns11", "http://tempuri.org/HttpServiceSoap", NULL, NULL},
	{"ns12", "http://tempuri.org/HttpServiceSoap12", NULL, NULL},
	{"ns3", "http://tempuri.org/PaymentFunctionWebServiceSoap", NULL, NULL},
	{"ns4", "http://tempuri.org/PaymentFunctionWebServiceSoap12", NULL, NULL},
	{"ns5", "http://tempuri.org/UserFunctionWebServiceSoap", NULL, NULL},
	{"ns6", "http://tempuri.org/UserFunctionWebServiceSoap12", NULL, NULL},
	{"ns7", "http://tempuri.org/UtilFunctionWebServiceSoap", NULL, NULL},
	{"ns1", "http://tempuri.org/", NULL, NULL},
	{"ns8", "http://tempuri.org/UtilFunctionWebServiceSoap12", NULL, NULL},
	{"ns9", "http://tempuri.org/QueryServiceSoap", NULL, NULL},
	{NULL, NULL, NULL, NULL}
};
	soap->namespaces = namespaces; } };
	/// Destructor frees deserialized data and soap engine context
	virtual ~QueryServiceSoap() { if (soap) { soap_destroy(soap); soap_end(soap); soap_free(soap); } };
	/// Invoke 'queryPhoneNOInfo' of service 'QueryServiceSoap' and return error code (or SOAP_OK)
	virtual int __ns9__queryPhoneNOInfo(_ns1__queryPhoneNOInfo *ns1__queryPhoneNOInfo, _ns1__queryPhoneNOInfoResponse *ns1__queryPhoneNOInfoResponse) { return soap ? soap_call___ns9__queryPhoneNOInfo(soap, endpoint, NULL, ns1__queryPhoneNOInfo, ns1__queryPhoneNOInfoResponse) : SOAP_EOM; };
};
#endif
