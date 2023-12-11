#include <vector>
#include <gtest/gtest.h>

class MinimumPathSum {
public:
    int minPathSum(vector<vector<int>>& grid) {
        if (grid.empty()) {
            return 0;
        }

        size_t m = grid.size();
        size_t n = grid[0].size(); 

        for (size_t i = 1; i < m; ++i ) {
            grid[i][0] += grid[i-1][0];
        }

        for (size_t j = 1; j < n; ++j ) {
            grid[0][j] += grid[0][j-1];
        }

        for (size_t i=1; i< m; i++) {
            for (size_t j=1; j<n; ++j) {
                grid[i][j] = grid[i][j] + std::min(grid[i][j-1], grid[i-1][j]);
            }
        }

        return grid[m-1][n-1];
    }
};




class TestMinimumPathSum : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestMinimumPathSum, testCases) {
    MinimumPathSum cs;
    
}

