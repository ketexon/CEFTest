#include "BrowserApp.hpp"

#include "V8/TestBinding.hpp"
#include "SchemeHandler.hpp"

#include <ctime>
#include <iomanip>

void BrowserApp::OnContextInitialized() {
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

		CefRegisterSchemeHandlerFactory(
			"https", "internal",
			new ClientSchemeHandlerFactory{}
		);

		CefRefPtr<CefBrowserView> browserView = CefBrowserView::CreateBrowserView(
			client,
			startupURL,
			browserSettings,
			nullptr, nullptr, nullptr
		);
		CefWindow::CreateTopLevelWindow(new WindowDelegate(browserView));
	}

void BrowserApp::OnContextCreated(
	CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefV8Context> context
) {
	std::time_t time = std::time(nullptr);
	std::tm* tm = std::localtime(&time);
	std::cout
		<< "[" << std::put_time(tm, "%F %T") << "]"
		<< "--- Context Created ---"
		<< std::endl;
	CefRefPtr<CefV8Value> object = context->GetGlobal();

	CefRefPtr<CefV8Value> func = CefV8Value::CreateFunction("testFunction", new TestBinding);

	object->SetValue("testFunction", func, V8_PROPERTY_ATTRIBUTE_NONE);
}