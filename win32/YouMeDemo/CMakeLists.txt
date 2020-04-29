project (YouMeDemo)

ADD_DEFINITIONS(-DCURL_STATICLIB -DCARES_STATICLIB)
INCLUDE_DIRECTORIES (${COMMON_INCLUDE} .. "..\\common" ../../../youme_voice_engine/bindings/cocos2d-x/interface 
../../../youme_voice_engine/bindings/cocos2d-x/win/)

FILE (GLOB_RECURSE header_files *.h)
FILE (GLOB_RECURSE source_files *.c *.cc *.cpp)
FILE (GLOB_RECURSE resource_files *.aps *.rc *.ico *.rc2)

LINK_DIRECTORIES(${COMMON_LIB})
IF (WIN_X86_32_2013MT)
	LINK_DIRECTORIES(${COMMON_LIB}/../youme_voice_engine/youme_common/lib/windows 
	${COMMON_LIB}/lib/${CMAKE_PLATFORM}/${CMAKE_BUILD_TYPE})
ELSEIF (WIN_X86_64_2013MT)
	LINK_DIRECTORIES(${COMMON_LIB}/../youme_voice_engine/youme_common/lib/x86_64_2013
	${COMMON_LIB}/lib/${CMAKE_PLATFORM}/${CMAKE_BUILD_TYPE})
ELSEIF (WIN_X86_64_2015MD)
	LINK_DIRECTORIES(${COMMON_LIB}/../youme_voice_engine/youme_common/lib/x86_64
	${COMMON_LIB}/lib/${CMAKE_PLATFORM}/${CMAKE_BUILD_TYPE})
ENDIF(WIN_X86_32_2013MT)

if((${CMAKE_CONFIGURATION_TYPES} MATCHES Debug) OR (UN_REAL))
	ADD_DEFINITIONS(-D_AFXDLL)
	SET(CMAKE_MFC_FLAG 2)
ELSE((${CMAKE_CONFIGURATION_TYPES} MATCHES Debug) OR (UN_REAL))
	ADD_DEFINITIONS(-D_AFX)
	SET(CMAKE_MFC_FLAG 1)
ENDIF((${CMAKE_CONFIGURATION_TYPES} MATCHES Debug) OR (UN_REAL))

ADD_DEFINITIONS(-D_UNICODE)
ADD_EXECUTABLE (YouMeDemo WIN32 ${header_files} ${source_files} ${resource_files})



IF(WIN32)
	TARGET_LINK_LIBRARIES (YouMeDemo youme_voice_engine.lib wldap32.lib  Version.lib Setupapi.lib ws2_32)
ELSEIF (__ANDROID__) 
	TARGET_LINK_LIBRARIES (YouMeDemo YouMeIMEngine z)
ELSE(WIN32)

	TARGET_LINK_LIBRARIES (YouMeDemo YouMeCommon YouMeIMEngine  z )
ENDIF(WIN32)