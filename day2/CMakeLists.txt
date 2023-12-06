project(day2)

add_executable(day2_part1 main.cpp)
add_executable(day2_part2 main2.cpp)

add_custom_target(run2_part1 $<TARGET_FILE:day2_part1>
    DEPENDS day2_part1
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_custom_target(run2_part2 $<TARGET_FILE:day2_part2>
    DEPENDS day2_part2
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

