#include <algorithm>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <gtest/gtest.h>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <optional>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <unordered_set>

struct HL1 {
    struct Job {
        int _id{0};
        int _next{0};
        int _runtime{0};

        Job() = default;
        Job(int id, int next, int runtime) : _id(id) , _next(next), _runtime(runtime) {
        }
    };

    struct Result{
        size_t begin{0};
        size_t end{0};
        size_t total{0};
        size_t count{0};

        friend std::ostream& operator << (std::ostream& os, const Result& result) {
          os << result.begin << " , "
             << result.end << " , "
             << result.total << " , "
             << result.count << std::endl;
          return os;
        }
    };

    using JobsById = std::unordered_map<size_t, Job>;
    using AdjacencyList = std::unordered_map<size_t, std::list<size_t>>;

    [[nodiscard]] std::optional<std::vector<Job>> parseJobs(const std::vector<std::string>& inputs) {

      auto inValid = [](const Job& j) {
        bool invalidInput = (j._id < 0 || j._next < 0 || j._runtime < 0);
        bool currentEqualsNext = j._id == j._next;
        return invalidInput || currentEqualsNext;

        // to do , check for cycles
      };

      char c1;
      char c2;
      std::vector<Job> jobs;
      for (auto& input : inputs) {
        std::stringstream stream(input);
        Job j;
        stream >> j._id >> c1 >> j._next >> c2 >> j._runtime;

        if (inValid(j)) {
          return std::nullopt;
        }

        jobs.emplace_back(j._id, j._next, j._runtime);
      }
      return jobs;
    }

    [[nodiscard]] static std::optional<JobsById> indexJobs(const std::vector<Job>& jobs) {
      JobsById jobsById;
      for (const auto& job : jobs) {
        if (jobsById.find(job._id) != jobsById.end()) {
          return std::nullopt;
        }
        jobsById[job._id] = job;
      }
      return jobsById;
    }


    [[nodiscard]] static AdjacencyList generateAdjacencyList(const JobsById& jobs) {
      AdjacencyList adjacencyList;
      for (auto const& [jobId, job] : jobs) {
        adjacencyList[job._next].push_back(jobId);
      }
      return adjacencyList;
    }

    /*
    Algorithm: start at 0 and work upwards
    */
    static std::optional<std::list<Result>> generateReport(const AdjacencyList& adjacencyList, const JobsById& jobsById) {
      if (adjacencyList.find(0) == adjacencyList.end()) {
        return std::nullopt;
      }

      std::list<Result> results;
      std::unordered_map<size_t, Result> dp;
      dp[0] = {0,0,0,0};

      std::queue<size_t> idQueue;
      idQueue.push(0);

      while(!idQueue.empty()) {
        auto childId{idQueue.front()};
        idQueue.pop();

        std::cout << childId << std::endl;

        auto&childResult{dp[childId]};

        if (adjacencyList.find(childId) == adjacencyList.end()) {
          results.push_back(childResult);
        }
        else {
          const auto&incomingParents {adjacencyList.at(childId)};
          for (const auto&incomingParent : incomingParents) {
            auto& result {dp[incomingParent]};
            result.begin = incomingParent;
            result.end = childId == 0 ? incomingParent : childResult.end;
            result.total = childResult.total + jobsById.at(incomingParent)._runtime;
            result.count = childResult.count + 1;

            idQueue.push(incomingParent);
          }
        }
      }
      return results;
    }

    void process(const std::vector<std::string>& inputs) {
      auto parsedJobs = parseJobs(inputs);
      if (!parsedJobs) {
        std::cout << "Malformed input" << std::endl;
        return;
      }

      auto indexedJobs = indexJobs(parsedJobs.value());
      if (!indexedJobs) {
        std::cout << "Malformed input" << std::endl;
        return;
      }

      auto adjacencyList = generateAdjacencyList(indexedJobs.value());

      auto optionalResults = generateReport(adjacencyList, indexedJobs.value());

      if (!optionalResults) {
        std::cout << "Malformed input" << std::endl;
        return;
      }

      for (const auto &result : optionalResults.value()) {
        std::cout << result;
      }
    }
};

class TestHL1 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// TEST_F(TestHL1, simpleCase) {

//     HL1 h;
//     std::vector<std::string> inputs {
//         "1,2,1",
//         "2,3,1",
//         "3,4,1",
//         "4,5,6",
//     };
//     auto parsed = h.parseJobs(inputs);
//     EXPECT_TRUE(parsed.has_value());

//     auto &parsed_value = parsed.value();
//     EXPECT_EQ(parsed_value.size(), 4);

//     auto indexed = h.indexJobs(parsed_value);
//     EXPECT_TRUE(indexed.has_value());
//     auto &indexedValue = indexed.value();
//     EXPECT_EQ(indexedValue.size(), 4);

//     auto adjList = h.generateAdjacencyList(indexedValue);
//     EXPECT_EQ(adjList.size(), 2);

//     auto reports = h.generateReport(adjList,indexedValue);
//     EXPECT_FALSE(reports.has_value());
// }

// TEST_F(TestHL1, malformed) {

//   HL1 h;
//   std::vector<std::string> inputs {
//       "1,2,1",
//       "2,3,1",
//       "3,4,1",
//       "4,5,6",
//       "2,5,8"       // pointing to a new value
//   };


//   auto parsed = h.parseJobs(inputs);
//   EXPECT_TRUE(parsed.has_value());

//   auto &parsed_value = parsed.value();
//   EXPECT_EQ(parsed_value.size(), 5);

//   auto indexed = h.indexJobs(parsed_value);
//   EXPECT_FALSE(indexed.has_value());
// }

// TEST_F(TestHL1, ajsList) {
//     HL1 h;
//     std::vector<std::string> inputs {
//         "1,2,3",
//         "2,5,8",
//         "5,0,5",
//         "3,2,5",
//         "6,5,8",
//         "10,0,10"
//     };

//     auto parsed = h.parseJobs(inputs);
//     EXPECT_TRUE(parsed.has_value());

//     auto &parsed_value = parsed.value();
//     EXPECT_EQ(parsed_value.size(), 6);

//     auto indexed = h.indexJobs(parsed_value);
//     EXPECT_TRUE(indexed.has_value());
//     auto &indexedValue = indexed.value();
//     EXPECT_EQ(indexedValue.size(), 6);

//     auto adjList = h.generateAdjacencyList(indexedValue);
//     EXPECT_EQ(adjList.size(), 3);

//     for (const auto&[k,v] : adjList) {
//       std::cout <<  k <<  ": [";
//       for (const auto& vv : v) {
//         std::cout << vv << " ,";
//       }
//       std::cout <<  " ]"  << std::endl;
//     }

//     auto results = h.generateReport(adjList,indexedValue);
//     EXPECT_TRUE(results.has_value());
//     EXPECT_EQ(results.value().size(), 4);
//     for (const auto& result : results.value()) {
//       std::cout << result;
//     }
// }

// TEST_F(TestHL1, test1) {
//   HL1 h;
//   std::vector<std::string> inputs {
//       "1,2,3",
//       "2,5,8",
//       "5,0,5",
//       "3,2,5",
//       "6,5,8",
//       "10,0,10",
//       "11,10,11",
//       "12,11,12"
//   };

//   auto parsed = h.parseJobs(inputs);
//   EXPECT_TRUE(parsed.has_value());

//   auto &parsed_value = parsed.value();
//   EXPECT_EQ(parsed_value.size(), 8);

//   auto indexed = h.indexJobs(parsed_value);
//   EXPECT_TRUE(indexed.has_value());
//   auto &indexedValue = indexed.value();
//   EXPECT_EQ(indexedValue.size(), 8);

//   auto adjList = h.generateAdjacencyList(indexedValue);
//   EXPECT_EQ(adjList.size(), 5);

//   for (const auto&[k,v] : adjList) {
//     std::cout <<  k <<  ": [";
//     for (const auto& vv : v) {
//       std::cout << vv << " ,";
//     }
//     std::cout <<  " ]"  << std::endl;
//   }

//   auto results = h.generateReport(adjList,indexedValue);
//   EXPECT_TRUE(results.has_value());
//   EXPECT_EQ(results.value().size(), 4);
//   for (const auto& result : results.value()) {
//     std::cout << result;
//   }
// }

// TEST_F(TestHL1, testCycle) {
//   HL1 h;
//   std::vector<std::string> inputs{"10,12,10",
//                                   "11,10,11",
//                                   "12,11,12",
//                                   "7,6,7",
//                                   "6,0,6",
//                                   "9,12,9"};
//   auto parsed = h.parseJobs(inputs);
//   EXPECT_TRUE(parsed.has_value());

//   auto &parsed_value = parsed.value();
//   EXPECT_EQ(parsed_value.size(), 6);

//   auto indexed = h.indexJobs(parsed_value);
//   EXPECT_TRUE(indexed.has_value());
//   auto &indexedValue = indexed.value();
//   EXPECT_EQ(indexedValue.size(), 6);

//   auto adjList = h.generateAdjacencyList(indexedValue);
//   EXPECT_EQ(adjList.size(), 5);

//   for (const auto&[k,v] : adjList) {
//     std::cout <<  k <<  ": [";
//     for (const auto& vv : v) {
//       std::cout << vv << " ,";
//     }
//     std::cout <<  " ]"  << std::endl;
//   }

//   auto results = h.generateReport(adjList,indexedValue);
//   EXPECT_TRUE(results.has_value());
//   EXPECT_EQ(results.value().size(), 1);
//   for (const auto& result : results.value()) {
//     std::cout << result;
//   }
// }

