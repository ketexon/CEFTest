#pragma once

#include <include/cef_scheme.h>
#include <include/cef_resource_handler.h>

class ClientSchemeHandler
 : public CefResourceHandler
{
public:
	ClientSchemeHandler() = default;

	/*---------CefResourceHandler-----------*/
	bool ProcessRequest(CefRefPtr<CefRequest> request, CefRefPtr<CefCallback> callback) override;

	void GetResponseHeaders(CefRefPtr<CefResponse> response, int64& responseLength, CefString& redirectUrl) override;

	void Cancel() override;

	bool ReadResponse(void* dataOut, int bytesToRead, int& bytesRead, CefRefPtr<CefCallback> callback) override;

private:
	IMPLEMENT_REFCOUNTING(ClientSchemeHandler);
	DISALLOW_COPY_AND_ASSIGN(ClientSchemeHandler);
};

class ClientSchemeHandlerFactory
 : public CefSchemeHandlerFactory
{
public:
	ClientSchemeHandlerFactory() = default;

	CefRefPtr<CefResourceHandler> Create(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		const CefString& schemeName,
		CefRefPtr<CefRequest> request
	) override;

private:
	IMPLEMENT_REFCOUNTING(ClientSchemeHandlerFactory);
	DISALLOW_COPY_AND_ASSIGN(ClientSchemeHandlerFactory);
};