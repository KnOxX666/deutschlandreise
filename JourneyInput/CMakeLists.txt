file (GLOB SRC_FILES CONFIGURE_DEPENDS *.h *.cpp)
add_library(JourneyInput OBJECT ${SRC_FILES})
