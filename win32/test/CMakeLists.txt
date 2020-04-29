project (mytest)

ADD_DEFINITIONS(-DCURL_STATICLIB -DCARES_STATICLIB)
INCLUDE_DIRECTORIES (${COMMON_INCLUDE} .. "..\\common" )

FILE (GLOB_RECURSE header_files *.h)
FILE (GLOB_RECURSE source_files *.c *.cc *.cpp)

LINK_DIRECTORIES(${COMMON_LIB}/../youme_voice_engine/youme_common/lib/windows)

ADD_EXECUTABLE (mytest ${header_files} ${source_files})



IF(WIN32)
	TARGET_LINK_LIBRARIES (mytest youme_voice_engine wldap32.lib  Version.lib Setupapi.lib ws2_32)
ELSEIF (__ANDROID__) 
	TARGET_LINK_LIBRARIES (mytest YouMeIMEngine z)
ELSE(WIN32)

	TARGET_LINK_LIBRARIES (mytest YouMeCommon YouMeIMEngine  z )
ENDIF(WIN32)