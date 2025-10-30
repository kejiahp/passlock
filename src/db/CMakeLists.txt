# This recursively checks this directory for all .cpp files
file(GLOB_RECURSE DB_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# THIS IS FOR DEBUGGING PURPOSES TO SEE THE SOURCE FILES INCLUDED IN THIS LIBRARY
message(STATUS "DB: " ${DB_SOURCES})

add_library(db STATIC ${DB_SOURCES})


target_link_libraries(db PRIVATE utilities SQLiteCpp)
target_include_directories(db PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})