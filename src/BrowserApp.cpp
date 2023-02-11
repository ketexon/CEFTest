#include "BrowserApp.hpp"

#include "V8/TestBinding.hpp"

#include <ctime>
#include <iomanip>

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