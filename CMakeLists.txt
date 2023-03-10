cmake_minimum_required(VERSION 3.24)

project(CEFTest)

######### CONFIG ##########

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

set(CEFTEST_ASSET_DIR ${CMAKE_SOURCE_DIR}/assets)

set(
	CEFTEST_SRC
	Main.cpp
	BrowserApp.hpp BrowserApp.cpp
	WindowDelegate.hpp
	Client.hpp Client.cpp
	Framework.hpp

	V8/TestBinding.hpp
	V8/Bindings.cpp

	SchemeHandler.hpp SchemeHandler.cpp
)

list(TRANSFORM CEFTEST_SRC PREPEND src/)

set(
	CEFTEST_PRECOMPILED_HEADERS
	Framework.hpp
)

list(TRANSFORM CEFTEST_PRECOMPILED_HEADERS PREPEND src/)

# CEF

set(CEF_VERSION "110.0.25+g75b1c96+chromium-110.0.5481.78")

######## END CONFIG #########

######## CEF #########

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
  if("${CMAKE_CXX_COMPILER_ARCHITECTURE_ID}" STREQUAL "ARM64")
    set(CEF_PLATFORM "windowsarm64")
  elseif(CMAKE_SIZEOF_VOID_P MATCHES 8)
    set(CEF_PLATFORM "windows64")
  else()
    set(CEF_PLATFORM "windows32")
  endif()
endif()

if(CEF_PLATFORM STREQUAL "")
	message(FATAL_ERROR "Unsupported platform")
endif()

include(DownloadCEF)
DownloadCEF("${CEF_PLATFORM}" "${CEF_VERSION}" "${CMAKE_SOURCE_DIR}/extern/cef")

list(APPEND CMAKE_MODULE_PATH "${CEF_ROOT}/cmake")

find_package(CEF REQUIRED)
add_subdirectory(${CEF_LIBCEF_DLL_WRAPPER_PATH} libcef_dll_wrapper)

########### END CEF ############
########### CEFTEST ############

add_executable(
	CEFTest WIN32
	${CEFTEST_SRC}
)

set_target_properties(
	CEFTest
	PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED TRUE
)

target_precompile_headers(
	CEFTest
	PUBLIC ${CEFTEST_PRECOMPILED_HEADERS}
)

target_compile_definitions(
	CEFTest
	PUBLIC UNICODE _UNICODE
)

##### THIRD PARTY #####

add_subdirectory(extern/spdlog)

add_subdirectory(extern/CxxUrl)

install(TARGETS CxxUrl)

# add_dependencies(
# 	CEFTest
# 	CxxUrl
# )

target_link_libraries(
	CEFTest
	PRIVATE CxxUrl
)

target_link_libraries(
	CEFTest
	PRIVATE spdlog::spdlog
)

##### OTHER THIRD PARTY #####

set(TARGET_OUT_DIR "$<TARGET_FILE_DIR:CEFTest>")

ADD_LOGICAL_TARGET("libcef_lib" "${CEF_LIB_DEBUG}" "${CEF_LIB_RELEASE}")
COPY_FILES("CEFTest" "${CEF_BINARY_FILES}" "${CEF_BINARY_DIR}" "${TARGET_OUT_DIR}")
COPY_FILES("CEFTest" "${CEF_RESOURCE_FILES}" "${CEF_RESOURCE_DIR}" "${TARGET_OUT_DIR}")

add_dependencies(
	CEFTest
	libcef_dll_wrapper
)

target_link_libraries(
	CEFTest
	PRIVATE libcef_lib libcef_dll_wrapper ${CEF_STANDARD_LIBS}
)

list(REMOVE_ITEM CEF_CXX_COMPILER_FLAGS "/std:c++17")
list(APPEND CEF_CXX_COMPILER_FLAGS "/std:c++20")

SET_EXECUTABLE_TARGET_PROPERTIES(CEFTest)

target_compile_definitions(
	CEFTest
	PUBLIC $<IF:$<CONFIG:Debug>,CEFTEST_DBG_APP_DIR="${CEFTEST_ASSET_DIR}",>
)

add_custom_command(
	TARGET CEFTest
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CEFTEST_ASSET_DIR} ${TARGET_OUT_DIR}
)