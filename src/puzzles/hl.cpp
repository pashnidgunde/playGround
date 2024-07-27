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

// using namespace std;

// struct Job {
//     int _id;
//     int _runtime;
//     int _next;

//     Job(int id, int runtime, int next) : _id(id), _runtime(runtime), _next(next) {
//     }
// };

// std::optional<Job> parse(std::string csv) {
//    std::vector<int> r;
//    std::stringstream ss(csv);
//    for (int i; ss >>i;) {
//        r.push_back(i);
//        if(ss.peek() == ',') {
//            ss.ignore();
//        }
//    }

//    if (r.size() != 3) {
//        return nullopt;
//    }

//    return Job(r[0], r[1], r[2]);
// }

// std::vector<Job> createJobs(std::vector<std::string> inputLines) {
//     std::vector<Job> jobs;
//     for (const auto& inputLine : inputLines) {
//         auto job = parse(inputLine);
//         if (!job) {
//             std::cout << "Malformed Input" << std::endl;
//             continue;
//         }
//         jobs.push_back(job.value());
//     }

//     return jobs;
// }

// using LinkedJobs = std::unordered_map<int,std::pair<int,int>>;
// LinkedJobs linkJobs(const std::vector<Job>& jobs )
// {
//     LinkedJobs j;
//     for(const auto& job : jobs)
//     {
//         j[job._id] = {job._runtime,job._next};
//     }
//     return j;
// }

// struct Summary{
//     int startId = 0;
//     int lastId = 0;
//     int count = 0;
//     int runtimeInSeconds = 0;
//     int average = 0;
//     bool valid = true;
// };

// std::string toHoursMinsSec(const int runtime) {
//     int seconds = runtime;
//     int hours = seconds / 3600;
//     int minutes = (seconds % 3600) / 60;
//     int second = seconds % 60;

//     char timestring[9];
//     sprintf(timestring, "%02d:%02d:%02d", hours,minutes,second);
//     return string(timestring);
// }

// void printSummary(const Summary& s)
// {
//     std::cout <<"start_job: " << s.startId << std::endl;
//     std::cout <<"last_job: " << s.lastId << std::endl;
//     std::cout <<"number_of_jobs: " << s.count << std::endl;
//     std::cout <<"job_chain_runtime: " << toHoursMinsSec(s.runtimeInSeconds) << std::endl;
//     std::cout <<"average_job_time: " << toHoursMinsSec(s.average) << std::endl;
// }

// Summary createSummary(int id, const LinkedJobs& linkedJobs) {
//     Summary s;
//     s.startId = id;

//     do {
//         auto it = linkedJobs.find(id);
//         if (it == linkedJobs.end()) {
//             s.valid = false;
//             return s;
//         }
//         s.count += 1;
//         s.runtimeInSeconds += it->second.first;
//         s.lastId = id;
//         id = it->second.second;
//     } while(id != 0);

//     if (s.count > 0) {
//         s.average = s.runtimeInSeconds / s.count;
//     }
//     return s;

// }

// int headlands_main() {
//     /* Enter your code here. Read input from STDIN. Print output to STDOUT */
//     std::string inputLine;
//     std::string header;
//     getline(cin, header);
//     std::vector<std::string> inputLines;
//     while(getline(cin,inputLine)) {
//         inputLines.push_back(inputLine);
//     }

//     std::vector<Job> jobs = createJobs(inputLines);

//     /*for (const auto& job : jobs) {
//         std::cout << job.id << ", " << job.runtime << ", " << job.next << std::endl;
//     }*/

//     auto linkedJobs = linkJobs(jobs);
//     bool printLast = true;

//     for (const auto& job : jobs) {
//         if (job._next == 0) {
//             continue;
//         }

//         Summary s = createSummary(job._id, linkedJobs);
//         if (s.valid) {
//             std::cout << "-" << std::endl;
//             printSummary(s);

//         }
//         else {
//             std::cout << "Malformed Input" << std::endl;
//             printLast = false;
//         }
//     }

//     if (printLast)
//         std::cout << "-" << std::endl;

//     return 0;
// }


struct HL {
  struct Job {
    size_t _id{0};
    size_t _runtime{0};
    size_t _next{0};

    Job() = default;
    Job(size_t id, size_t runtime, size_t next) : _id(id) , _runtime(runtime) , _next(next) {
    }
  };

  struct Result{
    size_t begin{0};
    size_t end{0};
    size_t total{0};
    size_t count{0};
  };

  using JobsById = std::unordered_map<size_t, Job>;
  using AdjacencyList = std::unordered_map<size_t, std::list<size_t>>;
  using ResultsById = std::unordered_map<size_t, Result>;

  bool read(const std::vector<std::string>& inputs) {
    char c1;
    char c2;
    for (auto& input : inputs) {
      std::stringstream stream(input);
      Job j;
      stream >> j._id >> c1 >> j._next >> c2 >> j._runtime;
      if (_jobs_by_id.find(j._id) != _jobs_by_id.end()) {
        _jobs_by_id.clear();
        _adj_list.clear();
        std::cout << "Malformed input";
        return false;
      }
      _adj_list[j._next].push_back(j._id);
      _jobs_by_id.emplace(j._id,j);
    }

    for (const auto& job : _jobs_by_id) {
      uniqueJobIds.insert(job.first);
      uniqueJobIds.insert(job.second._next);
    }


    return true;
  }

  static void formatted(Result result) {
    std::cout << result.begin << " , "
              << result.end << " , "
              << result.total << " , "
              << result.count << std::endl;
  }

  /*
      Algorithm: start at 0 and work upwards
  */
  void generateResults() {
    std::queue<size_t> ids;
    ids.push(0);

    while(!ids.empty()) {
      size_t current{ids.front()};
      ids.pop();

      //            if (uniqueJobIds.find(current) == uniqueJobIds.end()) {
      //              // No found
      //              std::cout << "PN : Malformed input";
      //            }
      uniqueJobIds.erase(current);


      auto& current_result {_results_by_id[current]};
      auto& fromIds{_adj_list[current]};
      if (fromIds.empty()) {
        results.push_back(current_result);
      }
      else {
        for(const auto& from : fromIds) {
          auto &result{_results_by_id[from]};
          result.begin = from;
          result.end = current_result.end == 0 ? from : current_result.end;
          result.total = current_result.total + _jobs_by_id[from]._runtime;
          result.count = current_result.count + 1;

          ids.push(from);
        }
      }
    }

    if (!uniqueJobIds.empty()) {
      std::cout << "Malformed input";
    }
    else {
      for (const auto& result : results) {
        formatted(result);
      }
    }
  }

  JobsById _jobs_by_id;
  [[nodiscard]] JobsById indexedJobs() const { return _jobs_by_id; }

  AdjacencyList _adj_list;
  [[nodiscard]] AdjacencyList adjList() const { return _adj_list; }

  ResultsById _results_by_id;

  std::unordered_set<size_t> uniqueJobIds;
  std::list<Result> results;

};

class TestHL : public ::testing::Test {
protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(TestHL, simpleCase) {

  HL h;
  std::vector<std::string> inputs {
      "1,2,1",
      "2,3,1",
      "3,4,1",
      "4,5,6",
  };

  EXPECT_TRUE(h.read(inputs));
  EXPECT_EQ(h.indexedJobs().size(),4);
  EXPECT_EQ(h.adjList().size(),4);
}

TEST_F(TestHL, malformed) {

  HL h;
  std::vector<std::string> inputs {
      "1,2,1",
      "2,3,1",
      "3,4,1",
      "4,5,6",
      "2,5,8"
  };

  EXPECT_FALSE(h.read(inputs));
  EXPECT_EQ(h.indexedJobs().size(),0);
  EXPECT_EQ(h.adjList().size(),0);
}

TEST_F(TestHL, ajsList) {

  HL h;
  std::vector<std::string> inputs {
      "1,2,3",
      "2,5,8",
      "5,0,5",
      "3,2,5",
      "6,5,8",
      "10,0,10"
  };

  EXPECT_TRUE(h.read(inputs));
  EXPECT_EQ(h.indexedJobs().size(),6);
  EXPECT_EQ(h.adjList().size(),3);
  h.generateResults();
}

TEST_F(TestHL, test1) {

  HL h;
  std::vector<std::string> inputs {
      "1,2,3",
      "2,5,8",
      "5,0,5",
      "3,2,5",
      "6,5,8",
      "10,0,10",
      "11,10,11",
      "12,11,12"

  };

  EXPECT_TRUE(h.read(inputs));
  EXPECT_EQ(h.indexedJobs().size(),8);
  EXPECT_EQ(h.adjList().size(),5);
  h.generateResults();
}

TEST_F(TestHL, testCycle) {

  HL h;
  std::vector<std::string> inputs{"10,12,10",
                                  "11,10,11",
                                  "12,11,12",
                                  "7,6,7",
                                  "6,0,6",
                                  "9,12,9"};

  EXPECT_TRUE(h.read(inputs));
  EXPECT_EQ(h.indexedJobs().size(),6);
  EXPECT_EQ(h.adjList().size(),5);
  h.generateResults();
}

