# This recursively checks this directory for all .cpp files
file(GLOB_RECURSE UTILITIES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# THIS IS FOR DEBUGGING PURPOSES TO SEE THE SOURCE FILES INCLUDED IN THIS LIBRARY
message(STATUS "Utilities: " ${UTILITIES})

# Conditional check, just to be safe
if(UTILITIES)
    add_library(utilities STATIC ${UTILITIES})

    target_include_directories(utilities PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
endif()