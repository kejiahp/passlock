# This recursively checks this directory for all .cpp files
file(GLOB_RECURSE USER_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# THIS IS FOR DEBUGGING PURPOSES TO SEE THE SOURCE FILES INCLUDED IN THIS LIBRARY
message(STATUS "USER: " ${USER_SOURCES})

add_library(user STATIC ${USER_SOURCES})


target_link_libraries(user PRIVATE SQLiteCpp)
target_include_directories(user PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})