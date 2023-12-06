project(day1)

add_executable(day1 main.cpp)

add_custom_target(run1 $<TARGET_FILE:day1>
    DEPENDS day1
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
