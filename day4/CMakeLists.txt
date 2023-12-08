project(day4)

add_executable(day4_part1 day4_part1.cpp)
add_executable(day4_part2 day4_part2.cpp)

add_custom_target(run4_part1 $<TARGET_FILE:day4_part1>
    DEPENDS day4_part1
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_custom_target(run4_part2 $<TARGET_FILE:day4_part2>
    DEPENDS day4_part2
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
