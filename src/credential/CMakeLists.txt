# This recursively checks this directory for all .cpp files
file(GLOB_RECURSE CREDENTIAL_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# THIS IS FOR DEBUGGING PURPOSES TO SEE THE SOURCE FILES INCLUDED IN THIS LIBRARY
message(STATUS "CREDENTIAL: " ${CREDENTIAL_SOURCES})

add_library(credential STATIC ${CREDENTIAL_SOURCES})


target_link_libraries(credential PRIVATE SQLiteCpp utilities)
target_include_directories(credential PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})