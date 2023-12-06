project(day3)

add_executable(day3_part1 day3_part1.cpp)
add_executable(day3_part2 day3_part2.cpp)

add_custom_target(run3_part1 $<TARGET_FILE:day3_part1>
    DEPENDS day3_part1
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_custom_target(run3_part2 $<TARGET_FILE:day3_part2>
    DEPENDS day3_part2
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
