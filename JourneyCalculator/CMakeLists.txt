file (GLOB SRC_FILES CONFIGURE_DEPENDS *.h *.cpp)
add_library(JourneyCalculator OBJECT ${SRC_FILES})
