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
	void OnContextInitialized() override;

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