#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

#include "Job.hpp"
using namespace std;

struct ComputeCompletion : public std::unary_function<Job, void> {
    ComputeCompletion()
      : time(0),
        weighted_time(0)
    {}

    int time;
    long long weighted_time;

    void operator()(const Job &job) {
        time += job.len;
        weighted_time += (job.weight * time);
//        printf("Working on task (%d %d %d %.2g), end at %d, weighted_time %lld\n",
//                job.weight, job.len, (job.weight - job.len), (static_cast<double>(job.weight) / static_cast<double>(job.len)),
//                time, weighted_time);
    }
};

typedef vector<Job> T_Jobs;

template <class T_Sorter>
void sort_n_print(T_Jobs &jobs, T_Sorter sorter)
{
    sort(jobs.begin(), jobs.end(), sorter);

    ComputeCompletion compute;

    compute = for_each(jobs.rbegin(), jobs.rend(), compute);

    printf("Total time: %d, Weighted Completion time: %lld\n", compute.time, compute.weighted_time);
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s <input_file>", argv[0]);
        exit(EXIT_FAILURE);
    }

    T_Jobs jobs;
    int count, weight, len;

    string file_name(argv[1]);
    ifstream in_file;
    in_file.open(file_name.c_str(), ifstream::in);
    in_file >> count;
    jobs.resize(count);

    for (int i = 0; i < count; ++i) {
        in_file >> weight >> len;
        jobs[i] = Job(weight, len);
    }

    printf("Q1 (weight - length)");
    sort_n_print(jobs, LessWeightLenDiff());

    printf("------------------------\n");

    printf("Q2 (weight / length)");
    sort_n_print(jobs, LessWeightLenRatio());

    exit(EXIT_SUCCESS);
}
