#pragma once

#include <include/cef_app.h>
#include <include/views/cef_browser_view.h>
#include <include/views/cef_window.h>
#include <include/wrapper/cef_helpers.h>
#include <include/cef_v8.h>
#include <include/cef_render_process_handler.h>

#include <iostream>
#include <filesystem>

#include "WindowDelegate.hpp"
#include "Client.hpp"

class BrowserApp
	: public CefApp,
	public CefBrowserProcessHandler,
	public CefV8Handler,
	public CefRenderProcessHandler
{
public:
	BrowserApp() = default;

	/*--------CefApp----------*/
	CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override {
		return this;
	}

	CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() override {
		return this;
	}

	/*--------CefBrowserProcessHandler----------*/
	void OnContextInitialized() override {
		CEF_REQUIRE_UI_THREAD();

		CefRefPtr<CefClient> client{new Client{}};
		CefBrowserSettings browserSettings {};
		CefString startupURL;

		char exePathStr[MAX_PATH + 1];
		if(GetModuleFileNameA(NULL, exePathStr, MAX_PATH + 1) == 0){
			std::cout << "Could not get module file name." << std::endl;
		}
		else{
			std::filesystem::path exePath{exePathStr};
			startupURL.FromString(
				(exePath.parent_path() / "App" / "index.html").string()
			);
		}

		CefRefPtr<CefBrowserView> browserView = CefBrowserView::CreateBrowserView(
			client,
			startupURL,
			browserSettings,
			nullptr, nullptr, nullptr
		);
		CefWindow::CreateTopLevelWindow(new WindowDelegate(browserView));
	}

	/*--------CefV8Handler------------*/
	bool Execute(
		const CefString &name,
		CefRefPtr<CefV8Value> object,
		const CefV8ValueList &arguments,
		CefRefPtr<CefV8Value> &retval,
		CefString &exception
	) override;

	/*---------CefRenderProcessHandler--------*/
	void OnContextCreated(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefV8Context> context
	) override;

private:
	IMPLEMENT_REFCOUNTING(BrowserApp);
  	DISALLOW_COPY_AND_ASSIGN(BrowserApp);
};