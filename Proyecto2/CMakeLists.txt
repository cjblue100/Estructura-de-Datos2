cmake_minimum_required ( VERSION 3.8 )
project ( Project2 )
 
find_package ( OpenGL REQUIRED )
find_package ( GLEW REQUIRED )
find_package ( GLUT REQUIRED )
 
set ( MPPP_SOURCE_DIR "/home/cjblue100/matplotpp" )
 
set ( COMMON_INCLUDES ${MPPP_SOURCE_DIR}/include )
 
include_directories ( 
    ${COMMON_INCLUDES}
    ${OPENGL_INCLUDE_DIRS} 
    ${GLEW_INCLUDE_DIRS} 
    ${GLUT_INCLUDE_DIRS} 
)
 
# Library
set ( LINK_LIBS ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
 
file ( GLOB SRCS ${MPPP_SOURCE_DIR}/src/*.* )
 
add_library ( matplotpp STATIC ${SRCS} )
 
target_include_directories ( matplotpp PUBLIC ${COMMON_INCLUDES} )
 
target_link_libraries ( matplotpp LINK_PUBLIC ${LINK_LIBS} )
 
# Executable
 
add_executable(Project2 main.cpp FileM.cpp)
 
target_link_libraries(Project2 matplotpp)







