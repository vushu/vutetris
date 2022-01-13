set(CATCH2_INCLUDE_DIR "../externals/catch2")


file(GLOB_RECURSE TEST_SRC
    "${CMAKE_CURRENT_LIST_DIR}/*.cpp")

add_executable(bismuth_test ${TEST_SRC})

target_include_directories(bismuth_test PRIVATE ${CATCH2_INCLUDE_DIR})

target_link_libraries(bismuth_test bismuth)



