#pragma once

#include <include/cef_v8.h>

class TestBinding
	: public CefV8Handler
{
public:
	/*--------CefV8Handler------------*/
	bool Execute(
		const CefString &name,
		CefRefPtr<CefV8Value> object,
		const CefV8ValueList &arguments,
		CefRefPtr<CefV8Value> &retval,
		CefString &exception
	) override;

private:
	IMPLEMENT_REFCOUNTING(TestBinding);
};