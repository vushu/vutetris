cmake_minimum_required(VERSION 3.15)

#if (${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
    #add_compile_options("-s" "USE_FREETYPE=1")
#endif()
set(PROJECT_VERSION "1.0.0")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(STB_IMAGE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/externals/stb")
set(GLM_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/externals/glm")
set(MINIAUDIO_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/externals/miniaudio")
set(EMSCRIPTEN_INCLUDE_DIRS "/home/vushu/coding/repos/emsdk/upstream/emscripten/system/include")
set(TMXLITE_INCLUDE_DIRS "{CMAKE_CURRENT_SOURCE_DIR}/externals/tmxlite/include")

include(GNUInstallDirs)

project(bismuth VERSION ${PROJECT_VERSION} DESCRIPTION "Small gamelib")

file(GLOB_RECURSE source_list
    "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")

file(GLOB_RECURSE header_list
    "${CMAKE_CURRENT_LIST_DIR}/include/*h")

add_library(${PROJECT_NAME} SHARED ${header_list} ${source_list} include/bismuth/math.hpp src/core/math.cpp)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION})
#GLAD
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/externals/glad)
#box2d
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/externals/box2d)
#tmxlite
set(TMXLITE_STATIC_LIB on)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/externals/tmxlite)
add_compile_options(-Wsign-compare -Wunused-but-set-variable)

#message(STATUS "GLM included at ${GLM_INCLUDE_DIRS}")
if (${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
    target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${GLM_INCLUDE_DIRS}
        ${STB_IMAGE_INCLUDE_DIR}
        #${ENTT_INCLUDE_DIR}
        ${MINIAUDIO_INCLUDE_DIR}
        #${BOX2D_INCLUDE_DIRS}
        ${IMGUI_INCLUDE_DIRS}
        ${TMXLITE_INCLUDE_DIRS}
        #${NANO_VG_INCLUDE_DIRS}
        #${NUKLEAR_INCLUDE_DIRS}
        #${GLFW_INCLUDE_DIRS}
        #${FREETYPE_INCLUDE_DIRS}
        #${CATCH2_INCLUDE_DIRS}
        #${EMSCRIPTEN_INCLUDE_DIRS}
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        src)
else()
    target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${GLM_INCLUDE_DIRS}
        ${STB_IMAGE_INCLUDE_DIR}
        ${MINIAUDIO_INCLUDE_DIR}
        ${IMGUI_INCLUDE_DIRS}
        ${TMXLITE_INCLUDE_DIRS}
        ${GLFW_INCLUDE_DIRS}
        #${EMSCRIPTEN_INCLUDE_DIRS}
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        src)
endif()

#window compatibility
set(CMAKE_WINDOW_EXPORT_ALL_SYMBOLS ON)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
    message("Compiling to WASM")

    target_link_libraries(${PROJECT_NAME} "-s USE_GLFW=3")
    #target_link_libraries(${PROJECT_NAME} "-s USE_FREETYPE=1")
    #target_link_libraries(${PROJECT_NAME} "-s STB_IMAGE=1")
    #target_link_libraries(${PROJECT_NAME} "-lopenal")
    #target_link_libraries(${PROJECT_NAME} glad miniaudio box2d imgui tmxlite)
    target_link_libraries(${PROJECT_NAME} glad tmxlite)

else()
    find_package(glfw3 3.3 REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE PUBLIC ${CMAKE_DL_LIBS} glfw glad tmxlite)
endif()

add_subdirectory(tests)
add_test(NAME tests COMMAND bismuth_test)



#export(TARGETS ${PROJECT_NAME} FILE bismuthConfig.cmake)
