project(FSM_UT LANGUAGES CXX)

find_package(GTest CONFIG REQUIRED)

enable_testing()

include_directories(${HEADER_FILES_DIR} ${SOURCE_TEST_DIR}/${HEADER_FILES_DIR_NAME})
add_executable(${PROJECT_NAME} ${SOURCE_TEST_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

#add_test(NAME event_handler_test COMMAND ${PROJECT_NAME})
