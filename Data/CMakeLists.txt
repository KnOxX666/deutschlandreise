file (GLOB SRC_FILES CONFIGURE_DEPENDS *.h *.cpp)
add_library(DeutschlandreiseData OBJECT ${SRC_FILES})
