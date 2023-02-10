#include "BrowserApp.hpp"

bool BrowserApp::Execute(
	const CefString &name,
	CefRefPtr<CefV8Value> object,
	const CefV8ValueList &arguments,
	CefRefPtr<CefV8Value> &retval,
	CefString &exception
){
	std::cout << "hi" << std::endl;
	return false;
}

void BrowserApp::OnContextCreated(
	CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefV8Context> context
) {

	std::cout << "Context" << std::endl;
	CefRefPtr<CefV8Value> object = context->GetGlobal();

	CefRefPtr<CefV8Value> func = CefV8Value::CreateFunction("testFunction", this);

	object->SetValue("testFunction", func, V8_PROPERTY_ATTRIBUTE_NONE);
}