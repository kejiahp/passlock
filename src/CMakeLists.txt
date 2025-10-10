add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(user)
add_subdirectory(utilities)

target_link_libraries(${PROJECT_NAME} PRIVATE user utilities)

# Include headers from submodules
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

