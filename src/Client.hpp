#pragma once

#include "Framework.hpp"

#include <vector>
#include <include/cef_client.h>
#include <include/views/cef_browser_view.h>

#include <include/cef_keyboard_handler.h>

namespace VK {
	constexpr int R = 0x52;
}

class Client
	: public CefClient,
	public CefDisplayHandler,
	public CefLifeSpanHandler,
	public CefLoadHandler,
	public CefKeyboardHandler
{
public:
	Client();

	/*--------CefClient---------*/
	CefRefPtr<CefDisplayHandler> GetDisplayHandler() override { return this; }
  	CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override { return this; }
  	CefRefPtr<CefLoadHandler> GetLoadHandler() override { return this; }
  	CefRefPtr<CefKeyboardHandler> GetKeyboardHandler() override { return this; }


	/*--------CefDisplayHandler--------------*/
	void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title) override;


	/*--------CefLoadHandler---------------*/
	virtual void OnLoadError(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		ErrorCode errorCode,
		const CefString& errorText,
		const CefString& failedUrl
	) override;


	/*--------CefLifeSpanHandler--------*/
	void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
	bool DoClose(CefRefPtr<CefBrowser> browser) override;
	void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;

	/*--------CefKeyboardHandler-------*/
	bool OnKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent &event, CefEventHandle osEvent) override;
private:
	std::vector<CefRefPtr<CefBrowser>> browsers;

	IMPLEMENT_REFCOUNTING(Client);
	DISALLOW_COPY_AND_ASSIGN(Client);
};