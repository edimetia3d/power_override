
add_library(foo SHARED foo.cpp)

add_library(naive_override_foo SHARED naive_override_foo.cpp)
target_link_libraries(naive_override_foo dl)

add_library(override_foo SHARED override_foo.cpp)
target_link_libraries(override_foo powerhook)

add_custom_target(override_test_libs)
add_dependencies(override_test_libs override_foo naive_override_foo foo)

add_executable(link_call_foo link_call_foo.cpp)
target_link_libraries(link_call_foo foo)
add_dependencies(link_call_foo override_test_libs)

add_executable(dlopen_call_foo dlopen_call_foo.cpp)
target_link_libraries(dlopen_call_foo dl)
add_dependencies(dlopen_call_foo override_test_libs)