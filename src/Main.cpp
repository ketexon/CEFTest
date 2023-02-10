#include "Framework.hpp"

#include <iostream>
#include <fstream>

#include <include/base/cef_build.h>

#include "BrowserApp.hpp"

int wWinMain(
  __in HINSTANCE hInstance,
  __in HINSTANCE hPrevInstance,
  __in LPWSTR lpCmdLine,
  __in int nShowCmd
){
	CefEnableHighDPISupport();

	CefMainArgs mainArgs{hInstance};

	int exitCode = CefExecuteProcess(mainArgs, nullptr, nullptr);
	if(exitCode >= 0){
		return exitCode;
	}

	{
		AllocConsole();

		FILE *file = nullptr;
		freopen_s(&file,"CONIN$", "r", stdin);
		freopen_s(&file, "CONOUT$", "w", stdout);
		freopen_s(&file, "CONOUT$", "w", stderr);
	}

	CefSettings settings;

	CefRefPtr<CefApp> app = new BrowserApp{};

	CefInitialize(mainArgs, settings, app, nullptr);
	CefRunMessageLoop();
	CefShutdown();

	//_getwch();

	return 0;
}