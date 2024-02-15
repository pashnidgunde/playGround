project(PlayGroundTests)

find_package(GTest CONFIG REQUIRED)

add_executable(${PROJECT_NAME}
        array/binarySreach/MinInSortedRotatedArray.cpp
        array/binarySreach/SearchInSortedRotatedArray.cpp
        array/ProductExceptSelf.cpp
        array/MaximumSubarray.cpp
        array/MaxProductSubarray.cpp
        array/ThreeSum.cpp
        array/NumberOfOneBits.cpp

        bitwise/HammingDistance.cpp
        
        constantTime/TestCanWin.cpp

        dp/ClimbingStairs.cpp
        dp/CoinChange.cpp
        dp/CoinChangeII.cpp
        dp/MinimumCostForTickets.cpp
        
        hashing/ContainsDuplicate.cpp
        hashing/TwoSum.cpp
        
        puzzles/headlands.cpp
        puzzles/SnowFlakes.cpp
                
        queue/CircularQueue.cpp

        slidingWindow/ContainerWithMostWater.cpp
        slidingWindow/MaxProfit.cpp
        slidingWindow/ContainerWithMostWater.cpp
        std/shared_ptr.cpp
        std/String.cpp
)

include(CTest)
enable_testing()

target_include_directories(${PROJECT_NAME} PRIVATE ../include)
target_link_libraries(${PROJECT_NAME} PRIVATE GTest::gtest GTest::gtest_main)
#target_link_libraries(${PROJECT_NAME} PRIVATE GTest::gtest GTest::gmock GTest::gtest_main)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Tests")