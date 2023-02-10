#pragma once

#include <include/views/cef_window.h>
#include <include/views/cef_browser_view.h>

class WindowDelegate : public CefWindowDelegate {
public:
	explicit WindowDelegate(CefRefPtr<CefBrowserView> browserView)
		: browserView(browserView) {}

	void OnWindowCreated(CefRefPtr<CefWindow> window) override {
		window->AddChildView(browserView);
		window->Show();

		browserView->RequestFocus();
	}

	void OnWindowDestroyed(CefRefPtr<CefWindow> window) override {
		browserView = nullptr;
	}

	bool CanClose(CefRefPtr<CefWindow> window) override {
		CefRefPtr<CefBrowser> browser = browserView->GetBrowser();
		if (browser)
			return browser->GetHost()->TryCloseBrowser();
		return true;
	}

	CefSize GetPreferredSize(CefRefPtr<CefView> view) override { return CefSize(800, 600); }
	CefSize GetMinimumSize(CefRefPtr<CefView> view) override { return CefSize(200, 100); }

private:
	CefRefPtr<CefBrowserView> browserView;

	IMPLEMENT_REFCOUNTING(WindowDelegate);
	DISALLOW_COPY_AND_ASSIGN(WindowDelegate);
};