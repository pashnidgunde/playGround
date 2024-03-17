#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <iomanip>
#include <optional>

using namespace std;

struct Job {
    int _id;
    int _runtime;
    int _next;

    Job(int id, int runtime, int next) : _id(id), _runtime(runtime), _next(next) {
    }
};

std::optional<Job> parse(std::string csv) {
   std::vector<int> r;
   std::stringstream ss(csv);
   for (int i; ss >>i;) {
       r.push_back(i);
       if(ss.peek() == ',') {
           ss.ignore();
       }
   }

   if (r.size() != 3) {
       return nullopt;
   }

   return Job(r[0], r[1], r[2]);
}

std::vector<Job> createJobs(std::vector<std::string> inputLines) {
    std::vector<Job> jobs;
    for (const auto& inputLine : inputLines) {
        auto job = parse(inputLine);
        if (!job) {
            std::cout << "Malformed Input" << std::endl;
            continue;
        }
        jobs.push_back(job.value());
    }

    return jobs;
}

using LinkedJobs = std::unordered_map<int,std::pair<int,int>>;
LinkedJobs linkJobs(const std::vector<Job>& jobs )
{
    LinkedJobs j;
    for(const auto& job : jobs)
    {
        j[job._id] = {job._runtime,job._next};
    }
    return j;
}

struct Summary{
    int startId = 0;
    int lastId = 0;
    int count = 0;
    int runtimeInSeconds = 0;
    int average = 0;
    bool valid = true;
};

std::string toHoursMinsSec(const int runtime) {
    int seconds = runtime;
    int hours = seconds / 3600;
    int minutes = (seconds % 3600) / 60;
    int second = seconds % 60;

    char timestring[9];
    sprintf(timestring, "%02d:%02d:%02d", hours,minutes,second);
    return string(timestring);
}

void printSummary(const Summary& s)
{
    std::cout <<"start_job: " << s.startId << std::endl;
    std::cout <<"last_job: " << s.lastId << std::endl;
    std::cout <<"number_of_jobs: " << s.count << std::endl;
    std::cout <<"job_chain_runtime: " << toHoursMinsSec(s.runtimeInSeconds) << std::endl;
    std::cout <<"average_job_time: " << toHoursMinsSec(s.average) << std::endl;
}

Summary createSummary(int id, const LinkedJobs& linkedJobs) {
    Summary s;
    s.startId = id;

    do {
        auto it = linkedJobs.find(id);
        if (it == linkedJobs.end()) {
            s.valid = false;
            return s;
        }
        s.count += 1;
        s.runtimeInSeconds += it->second.first;
        s.lastId = id;
        id = it->second.second;
    } while(id != 0);

    if (s.count > 0) {
        s.average = s.runtimeInSeconds / s.count;
    }
    return s;

}

int headlands_main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    std::string inputLine;
    std::string header;
    getline(cin, header);
    std::vector<std::string> inputLines;
    while(getline(cin,inputLine)) {
        inputLines.push_back(inputLine);
    }

    std::vector<Job> jobs = createJobs(inputLines);

    /*for (const auto& job : jobs) {
        std::cout << job.id << ", " << job.runtime << ", " << job.next << std::endl;
    }*/

    auto linkedJobs = linkJobs(jobs);
    bool printLast = true;

    for (const auto& job : jobs) {
        if (job._next == 0) {
            continue;
        }

        Summary s = createSummary(job._id, linkedJobs);
        if (s.valid) {
            std::cout << "-" << std::endl;
            printSummary(s);

        }
        else {
            std::cout << "Malformed Input" << std::endl;
            printLast = false;
        }
    }

    if (printLast)
        std::cout << "-" << std::endl;

    return 0;
}