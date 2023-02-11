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

#ifndef CEFTEST_DBG_APP_DIR
		char exePathStr[MAX_PATH + 1];
		if(GetModuleFileNameA(NULL, exePathStr, MAX_PATH + 1) == 0){
			std::cout << "Could not get module file name." << std::endl;
			return;
		}
		std::filesystem::path exePath{exePathStr};
		std::filesystem::path appDir = exePath.parent_path();
#else
		std::filesystem::path appDir = CEFTEST_DBG_APP_DIR;
#endif
		startupURL.FromString(
			(appDir / "App" / "index.html").string()
		);

		CefRefPtr<CefBrowserView> browserView = CefBrowserView::CreateBrowserView(
			client,
			startupURL,
			browserSettings,
			nullptr, nullptr, nullptr
		);
		CefWindow::CreateTopLevelWindow(new WindowDelegate(browserView));
	}

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