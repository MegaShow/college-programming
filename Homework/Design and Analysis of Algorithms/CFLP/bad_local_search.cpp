#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

#include "algorithm.hpp"
#include "types.hpp"

namespace bad_local_search {
    std::vector<size_t> generateRandomSolution(const std::vector<Facility> &f, const std::vector<Customer> &c);
    std::vector<size_t> generateNeighborSolution(const std::vector<Facility> &f, const std::vector<Customer> &c, const std::vector<size_t> &index);
    bool check(const std::vector<Facility> &f, const std::vector<Customer> &c, const std::vector<size_t> &index);
    Result getResult(const std::vector<Facility> &f, const std::vector<Customer> &c, const std::vector<size_t> &index);
}

using namespace bad_local_search;

Result BadLocalSearch(const std::vector<Facility> &f, const std::vector<Customer> &c) {
    std::vector<size_t> solution = generateRandomSolution(f, c);
    Result best = getResult(f, c, solution);
    for (int i = 0; i < 1000; i++) {
        solution = generateNeighborSolution(f, c, solution);
        Result res = getResult(f, c, solution);
        if (best.cost > res.cost) {
            best = res;
        }
    }
    return best;
}

std::vector<size_t> bad_local_search::generateRandomSolution(const std::vector<Facility> &f, const std::vector<Customer> &c) {
    std::vector<size_t> solution(f.size() + c.size());
    std::iota(solution.begin(), solution.end(), 0);
    while (true) {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(solution.begin(), solution.end(), std::default_random_engine(seed));
        if (check(f, c, solution)) {
            break;
        }
    }
    return solution;
}

std::vector<size_t> bad_local_search::generateNeighborSolution(const std::vector<Facility> &f, const std::vector<Customer> &c, const std::vector<size_t> &index) {
    std::vector<size_t> solution;
    while (true) {
        solution = index;
        std::default_random_engine random(std::chrono::system_clock::now().time_since_epoch().count());
        size_t i = random() % solution.size(), j = random() % solution.size();
        std::reverse(solution.begin() + i, solution.begin() + j);
        if (check(f, c, solution)) {
            break;
        }
    }
    return solution;
}

bool bad_local_search::check(const std::vector<Facility> &f, const std::vector<Customer> &c, const std::vector<size_t> &index) {
    if (index.front() >= f.size()) {
        return false;
    }
    size_t facility = 0;
    int capacity = 0;
    for (auto &i : index) {
        if (i < f.size()) {
            if (f[facility].capacity < capacity) {
                return false;
            }
            facility = i;
            capacity = 0;
        } else {
            capacity += c[i].demand;
        }
    }
    return true;
}

Result bad_local_search::getResult(const std::vector<Facility> &f, const std::vector<Customer> &c, const std::vector<size_t> &index) {
    Result res;
    res.cost = 0;
    res.status = std::vector<bool>(f.size());
    res.assignment = std::vector<size_t>(c.size());
    size_t facility;
    for (auto &i : index) {
        if (i < f.size()) {
            facility = i;
        } else {
            if (res.status[facility] == false) {
                res.status[facility] = true;
                res.cost += f[facility].openingCost;
            }
            res.assignment[i - f.size()] = facility;
            res.cost += c[i - f.size()].assignmentCost[facility];
        }
    }
    return res;
}
