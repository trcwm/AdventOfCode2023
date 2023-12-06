project(day1)

add_executable(day1_part1 day1_part1.cpp)
add_executable(day1_part2 day1_part2.cpp)

add_custom_target(run1_part1 $<TARGET_FILE:day1_part1>
    DEPENDS day1_part1
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_custom_target(run1_part2 $<TARGET_FILE:day1_part2>
    DEPENDS day1_part2
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
