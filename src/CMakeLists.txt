add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(user)
add_subdirectory(utilities)
add_subdirectory(db)

target_link_libraries(${PROJECT_NAME} PRIVATE user utilities db SQLiteCpp)

# Include headers from submodules
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

