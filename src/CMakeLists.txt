project(LeetCodeTest)

find_package(GTest CONFIG REQUIRED)

add_executable(${PROJECT_NAME}
        array/ProductExceptSelf.cpp
        bitwise/TestHammingDistance.cpp
        constantTime/TestCanWin.cpp
        hashing/TwoSum.cpp
        hashing/ContainsDuplicate.cpp
        slidingWindow/MaxProfit.cpp
        queue/CircularQueue.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ../include)
target_link_libraries(${PROJECT_NAME} PRIVATE GTest::gtest GTest::gtest_main)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Tests")