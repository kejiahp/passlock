# This recursively checks this directory for all .cpp files
file(GLOB_RECURSE UTILITIES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# THIS IS FOR DEBUGGING PURPOSES TO SEE THE SOURCE FILES INCLUDED IN THIS LIBRARY
message(STATUS "Utilities: " ${UTILITIES})

add_library(utilities STATIC ${UTILITIES})

find_package(OpenSSL REQUIRED)
target_link_libraries(utilities OpenSSL::SSL OpenSSL::Crypto)
target_include_directories(utilities PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
