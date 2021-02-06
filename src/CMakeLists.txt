
file(GLOB_RECURSE powerhook_srcs ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_library(powerhook OBJECT ${powerhook_srcs})
set_property(TARGET powerhook PROPERTY CXX_STANDARD 11)
set_property(TARGET powerhook PROPERTY POSITION_INDEPENDENT_CODE ON)
target_include_directories(powerhook PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(powerhook PUBLIC powerhook_pub_hdrs dl)