#include "TestBinding.hpp"

#include <iostream>

bool TestBinding::Execute(
	const CefString &name,
	CefRefPtr<CefV8Value> object,
	const CefV8ValueList &arguments,
	CefRefPtr<CefV8Value> &retval,
	CefString &exception
){
	retval = CefV8Value::CreateInt(10);
	return true;
}