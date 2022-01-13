cmake_minimum_required(VERSION 3.15)
project(game)

#if (${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
    #add_compile_options("-s" "USE_FREETYPE=1")
#endif()
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(BISMUTH_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/bismuth/include")
#set(ENTT_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/bismuth/externals/entt")
#set(BOX2D_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/bismuth/externals/box2d")
set(GLM_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/bismuth/externals/glm")
set(TMX_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/bismuth/externals/tmxlite")
#set(NANO_VG_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/bismuth/externals/nanovg/include")
#set(NUKLEAR_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/bismuth/externals/nuklear/include")
#set(FREE_TYPE_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/bismuth/externals/freetype2/include")


if (${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
    set (source "${CMAKE_CURRENT_LIST_DIR}/resources")
    set (destination "${CMAKE_CURRENT_BINARY_DIR}/resources")
else()
    set (source "${CMAKE_CURRENT_LIST_DIR}/resources")
    set (destination "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources")
endif()


file(GLOB_RECURSE source_list
    "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")

file(GLOB_RECURSE header_list
    "${CMAKE_CURRENT_LIST_DIR}/src/*.h")

add_executable(${PROJECT_NAME} ${source_list} ${header_list} )

add_custom_command(
    TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${source} ${destination}
    #COMMAND ${CMAKE_COMMAND} -E copy ${source} ${destination}
    DEPENDS ${destination}
    COMMENT "symbolic link resources folder from ${source} => ${destination}")

if (${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
    message("Compiling to WASM")

    set(CMAKE_EXECUTABLE_SUFFIX ".html")

    target_link_libraries(${PROJECT_NAME} "-s WASM=1") #web assembly FTW
    target_link_libraries(${PROJECT_NAME} "-s USE_WEBGL2=1")
    #target_link_libraries(${PROJECT_NAME} "-s FULL_ES3=1")
    #target_link_libraries(${PROJECT_NAME} "-s FULL_ES2=1")
    #target_link_libraries(${PROJECT_NAME} "-s USE_FREETYPE=1")
    target_link_libraries(${PROJECT_NAME} "-s ALLOW_MEMORY_GROWTH=1")
    target_link_libraries(${PROJECT_NAME} "--preload-file resources")
    target_link_libraries(${PROJECT_NAME} "--use-preload-plugins")
    target_link_libraries(${PROJECT_NAME} "-o ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/game.html")
    target_link_libraries(${PROJECT_NAME} "-s DEMANGLE_SUPPORT=1")
    target_compile_options(${PROJECT_NAME} PUBLIC "-O2") #creates the runtime resources
    target_link_libraries(${PROJECT_NAME} "-O2") #creates the runtime resources

    target_link_directories(${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)

    target_include_directories(${PROJECT_NAME}
        PUBLIC
        #${ENTT_INCLUDE_DIR}
        ${BISMUTH_INCLUDE_DIR}
        #${BOX2D_INCLUDE_DIR}
        ${GLM_INCLUDE_DIR}
        ${TMX_INCLUDE_DIR}
        #${NANO_VG_INCLUDE_DIR}
        #${NUKLEAR_INCLUDE_DIR}
        #${FREE_TYPE_INCLUDE_DIR}
        )

    target_link_libraries(${PROJECT_NAME} bismuth)

else()
    target_link_directories(${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)

    target_include_directories(${PROJECT_NAME} PUBLIC
        #${ENTT_INCLUDE_DIR}
        ${BISMUTH_INCLUDE_DIR}
        #${BOX2D_INCLUDE_DIR}
        ${TMX_INCLUDE_DIR}
        ${GLM_INCLUDE_DIR}
        #${NANO_VG_INCLUDE_DIR}
        #${NUKLEAR_INCLUDE_DIR}
        )
    target_link_libraries(${PROJECT_NAME} bismuth)
endif()
