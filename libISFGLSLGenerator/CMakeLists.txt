cmake_minimum_required(VERSION 3.20...3.25)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS True)

#add_compile_options("-stdlib=libc++" "-v" "-DLLVM_ENABLE_PROJECTS=\"clang\"" "-DLLVM_ENABLE_RUNTIMES=\"libcxx;libcxxabi\"")
#add_compile_options("-stdlib=libc++" "-std=c++20" "-v" "-DLLVM_ENABLE_PROJECTS=clang" "-DLLVM_ENABLE_RUNTIMES=libcxx,libcxxabi")
#add_compile_options ("-Wall")
add_compile_options ("-v")

add_library(ISFGLSLGenerator SHARED
	${CMAKE_CURRENT_SOURCE_DIR}/src/ISFAttr.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ISFDoc.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ISFPassTarget.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ISFVal.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/VVISF_Base.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/VVISF_StringUtils.cpp
	#${CMAKE_CURRENT_SOURCE_DIR}/include/ISFAttr.hpp
	#${CMAKE_CURRENT_SOURCE_DIR}/include/ISFDoc.hpp
	#${CMAKE_CURRENT_SOURCE_DIR}/include/ISFImageInfo.hpp
	#${CMAKE_CURRENT_SOURCE_DIR}/include/ISFPassTarget.hpp
	#${CMAKE_CURRENT_SOURCE_DIR}/include/ISFVal.hpp
	#${CMAKE_CURRENT_SOURCE_DIR}/include/VVISF_Base.hpp
	#${CMAKE_CURRENT_SOURCE_DIR}/include/VVISF_Constants.hpp
	#${CMAKE_CURRENT_SOURCE_DIR}/include/VVISF_Err.hpp
	#${CMAKE_CURRENT_SOURCE_DIR}/include/VVISF_StringUtils.hpp
	#${CMAKE_CURRENT_SOURCE_DIR}/include/VVISF.hpp
	#${CMAKE_CURRENT_SOURCE_DIR}/include/exprtk.hpp
	#${CMAKE_CURRENT_SOURCE_DIR}/include/json.hpp
)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# these lines are needed if you want to build a dylib that will be bundled with an app at runtime
#set(CMAKE_BUILD_WITH_INSTALL_RPATH YES)
#set_target_properties(ISFGLSLGenerator PROPERTIES INSTALL_RPATH @loader_path/../Frameworks/)

#target_include_directories(ISFGLSLGenerator PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_include_directories(ISFGLSLGenerator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
#target_include_directories(ISFGLSLGenerator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/exprtk)
#target_include_directories(ISFGLSLGenerator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/nlohmann_json))



# i'm pretty sure this is a bug, but this is the only way i can get cmake to include multiple headers in the build.  shouldn't i be able to just list all these files in the set_target_properties() call below?  if i do i get a cmake error about the wrong # of args...
#set(MY_LOCAL_HEADER_ARRAY
#	${CMAKE_CURRENT_SOURCE_DIR}/include/ISFAttr.hpp
#	${CMAKE_CURRENT_SOURCE_DIR}/include/ISFDoc.hpp
#	${CMAKE_CURRENT_SOURCE_DIR}/include/ISFImageInfo.hpp
#	${CMAKE_CURRENT_SOURCE_DIR}/include/ISFPassTarget.hpp
#	${CMAKE_CURRENT_SOURCE_DIR}/include/ISFVal.hpp
#	${CMAKE_CURRENT_SOURCE_DIR}/include/VVISF_Base.hpp
#	${CMAKE_CURRENT_SOURCE_DIR}/include/VVISF_Constants.hpp
#	${CMAKE_CURRENT_SOURCE_DIR}/include/VVISF_Err.hpp
#	${CMAKE_CURRENT_SOURCE_DIR}/include/VVISF_StringUtils.hpp
#	${CMAKE_CURRENT_SOURCE_DIR}/include/VVISF.hpp
#	${CMAKE_CURRENT_SOURCE_DIR}/include/exprtk.hpp
#	${CMAKE_CURRENT_SOURCE_DIR}/include/json.hpp
#)
#set_target_properties(ISFGLSLGenerator PROPERTIES PUBLIC_HEADER "${MY_LOCAL_HEADER_ARRAY}")

#set_target_properties(ISFGLSLGenerator PROPERTIES
#	FRAMEWORK TRUE
#	FRAMEWORK_VERSION A
#	MACOSX_FRAMEWORK_BUNDLE_VERSION 1.0.0.1	# CFBundleVersion
#	#MACOSX_FRAMEWORK_ICON_FILE myfile.icn	# CFBundleIconFile
#	MACOSX_FRAMEWORK_IDENTIFIER com.yourcompany.ISFGLSLGenerator	# CFBundleIdentifier
#	MACOSX_FRAMEWORK_SHORT_VERSION_STRING 1	# CFBundleShortVersionString
#	MACOSX_FRAMEWORK_INFO_PLIST "${CMAKE_CURRENT_LIST_DIR}/Info.plist"
#	VERSION 16.4.0	# "current version" in semantic format in Mach-O binary file
#	SOVERSION 1.0.0	# "compatibility version" in semantic format in Mach-O binary file
#	#PUBLIC_HEADER lib.hpp
#	#XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer"
#	
#	#INSTALL_NAME_DIR "@rpath"
#	
#	INSTALL_RPATH @loader_path/../Frameworks/
#	#XCODE_ATTRIBUTE_CODE_SIGNING_ALLOWED FALSE
#)

#target_include_directories( ISFGLSLGenerator PUBLIC
#	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#	$<INSTALL_INTERFACE:include>
#	)

target_compile_features(ISFGLSLGenerator PUBLIC cxx_std_20)

install(TARGETS ISFGLSLGenerator DESTINATION lib)
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/" DESTINATION include)
