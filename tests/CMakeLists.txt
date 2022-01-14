include_directories("../")

add_executable(tests2 test.cpp)

target_link_libraries(tests2 PRIVATE Catch2::Catch2WithMain)
