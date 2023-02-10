#include "Client.hpp"

#include <algorithm>
#include <iostream>

#include <include/views/cef_browser_view.h>
#include <include/views/cef_window.h>
#include <include/cef_app.h>

Client::Client(){}

void Client::OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title){
	CefRefPtr<CefBrowserView> browserView = CefBrowserView::GetForBrowser(browser);
	CefRefPtr<CefWindow> window;
	if(browserView && (window = browserView->GetWindow())){
		window->SetTitle(title);
	}
}

void Client::OnLoadError(
	CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	ErrorCode errorCode,
	const CefString& errorText,
	const CefString& failedUrl
){
	std::cout << "Failed to load URL: " << failedUrl << std::endl;
}

void Client::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
	browsers.push_back(browser);
}

bool Client::DoClose(CefRefPtr<CefBrowser> closedBrowser) {
	return false;
}

void Client::OnBeforeClose(CefRefPtr<CefBrowser> closingBrowser) {
	browsers.erase(std::remove_if(
		browsers.begin(),
		browsers.end(),
		[&](const CefRefPtr<CefBrowser>& browser){
			return browser->IsSame(closingBrowser);
		}
	));
	if(browsers.empty()){
		CefQuitMessageLoop();
	}
}



bool Client::OnKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent &event, CefEventHandle osEvent){
	if(event.type == KEYEVENT_RAWKEYDOWN){
		if(event.windows_key_code == VK::R && event.modifiers & EVENTFLAG_CONTROL_DOWN){
			std::cout << "REFRESH" << std::endl;
			browser->Reload();
		}
	}
	return false;
}