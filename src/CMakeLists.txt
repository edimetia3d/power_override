
file(GLOB_RECURSE poweroverride_srcs ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_library(poweroverride OBJECT ${poweroverride_srcs})
set_property(TARGET poweroverride PROPERTY CXX_STANDARD 11)
set_property(TARGET poweroverride PROPERTY POSITION_INDEPENDENT_CODE ON)
target_include_directories(poweroverride PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TARGET spdlog PROPERTY POSITION_INDEPENDENT_CODE ON)
target_link_libraries(poweroverride PUBLIC poweroverride_pub_hdrs dl spdlog)