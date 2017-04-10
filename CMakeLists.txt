cmake_minimum_required(VERSION 3.5)
project(GLPress)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

set(SOURCE_FILES
        CubeModel.cpp
        GLSLProgramCompiller.cpp
        Main.cpp
        Utils.cpp
        Window.cpp
        Material.cpp
        Material.h
        )

find_package(GLFW3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")
find_package(SOIL REQUIRED)
message(STATUS "Found SOIL in ${SOIL_INCLUDE_DIR}")
find_package(GLEW REQUIRED)
message(STATUS "Found GLEW in ${GLEW_INCLUDE_DIR}")
find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
find_package(OpenGL REQUIRED)
add_definitions(${OPENGL_DEFINITIONS})
find_package(X11 REQUIRED)
set(LIBS ${GLFW3_LIBRARY} X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL dl pthread GLEW SOIL)

file(GLOB SHADERS "shaders/*")
foreach (SHADER ${SHADERS})
    file(COPY ${SHADER} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shaders)
    message(STATUS ${SHADER})
endforeach (SHADER)

file(GLOB RESOURCES "resources/*")
foreach (RES ${RESOURCES})
    file(REMOVE ${CMAKE_CURRENT_BINARY_DIR}/resources)
    file(COPY ${RES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources)
    message(STATUS ${RES})
endforeach (RES)

add_executable(GLPress ${SOURCE_FILES})
target_link_libraries(GLPress ${LIBS})

#
#add_custom_command(TARGET GLPress POST_BUILD
#        COMMAND cp -Rf ${CMAKE_SOURCE_DIR}/shaders ${CMAKE_CURRENT_BINARY_DIR}/shaders
#        COMMAND cp -Rf ${CMAKE_SOURCE_DIR}/resources ${CMAKE_CURRENT_BINARY_DIR}/resources
#        COMMENT "Copied shaders and resources"
#        DEPENDS shaders/gl_06.vert
#        DEPENDS shaders/gl_06.frag
#        )
