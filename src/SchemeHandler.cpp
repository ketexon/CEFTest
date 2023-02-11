#include "SchemeHandler.hpp"

#include <include/wrapper/cef_helpers.h>

#include <iostream>

/*-------------ClientSchemeHandler----------------*/
bool ClientSchemeHandler::ProcessRequest(CefRefPtr<CefRequest> request, CefRefPtr<CefCallback> callback){
	CEF_REQUIRE_IO_THREAD();

	std::cout << request->GetURL() << std::endl;

	return false;
}

void ClientSchemeHandler::GetResponseHeaders(CefRefPtr<CefResponse> response, int64& responseLength, CefString& redirectUrl){
	CEF_REQUIRE_IO_THREAD();

	response->SetMimeType("text/html");
	response->SetStatus(200);

	responseLength = 0;
}

void ClientSchemeHandler::Cancel(){CEF_REQUIRE_IO_THREAD();}

bool ClientSchemeHandler::ReadResponse(void* dataOut, int bytesToRead, int& bytesRead, CefRefPtr<CefCallback> callback){
	CEF_REQUIRE_IO_THREAD();
	return false;
}



/*-----------ClientSchemeHandlerFactory--------------*/
CefRefPtr<CefResourceHandler> ClientSchemeHandlerFactory::Create(
	CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	const CefString& schemeName,
	CefRefPtr<CefRequest> request
){
	CEF_REQUIRE_IO_THREAD();
	return new ClientSchemeHandler();
}