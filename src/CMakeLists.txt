add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(user)
add_subdirectory(credential)
add_subdirectory(utilities)
add_subdirectory(db)

target_link_libraries(${PROJECT_NAME} PRIVATE SQLiteCpp user credential utilities db)

# Include headers from submodules
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

