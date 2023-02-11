#include "Framework.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

#include <include/base/cef_build.h>

#include "BrowserApp.hpp"

#ifdef _MSC_VER
static_assert(_MSVC_LANG >= 202000L);
#else
static_assert(__cplusplus >= 202000L);
#endif

const std::map<std::string, std::string> ProcessTypeConsoleTitleMap {
	{"", "Main Window"},
	{"renderer", "Renderer"},
};

int wWinMain(
  __in HINSTANCE hInstance,
  __in HINSTANCE hPrevInstance,
  __in LPWSTR lpCmdLine,
  __in int nShowCmd
){
	CefEnableHighDPISupport();

	CefMainArgs mainArgs{hInstance};

	CefRefPtr<CefApp> app = new BrowserApp{};

	{
		std::string processType;
		std::stringstream cmdLine{GetCommandLineA()};
		while(!cmdLine.eof() && !cmdLine.bad() && !cmdLine.fail()){
			std::string s;
			cmdLine >> s;
			if(s.starts_with("--type=")){
				processType = s.substr(7).c_str();
				break;
			}
		}

		if(ProcessTypeConsoleTitleMap.contains(processType)){
			AllocConsole();

			FILE *file = nullptr;
			freopen_s(&file,"CONIN$", "r", stdin);
			freopen_s(&file, "CONOUT$", "w", stdout);
			freopen_s(&file, "CONOUT$", "w", stderr);

			SetConsoleTitleA(ProcessTypeConsoleTitleMap.at(processType).c_str());
		}
	}

	int exitCode = CefExecuteProcess(mainArgs, app, nullptr);
	if(exitCode >= 0){
		return exitCode;
	}

	CefSettings settings;

	CefInitialize(mainArgs, settings, app, nullptr);
	CefRunMessageLoop();
	CefShutdown();

	//_getwch();

	return 0;
}