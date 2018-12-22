#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <set>
#include <vector>

#include "algorithm.hpp"
#include "types.hpp"

namespace greedy {
    bool check(const std::vector<Facility> &f, const std::vector<Customer> &c, const Result res);
    Result greedyWithFilter(const std::vector<Facility> &f, const std::vector<Customer> &c, std::vector<std::pair<int, size_t>> &capacity, const std::vector<bool> &filter);
}

using namespace greedy;

// 策略1: 将每个人分配到费用最低且容量足够的工厂
// 策略2: 删除消耗最少的工厂，重新执行策略1
Result Greedy(const std::vector<Facility> &f, const std::vector<Customer> &c) {
    std::vector<bool> filter(f.size());
    for (size_t i = 0; i < f.size(); i++) {
        filter[i] = true;
    }
    std::set<size_t> s;
    Result best;
    best.cost = 0;
    size_t last = (size_t) -1;
    while (s.size() != f.size()) {
        std::vector<std::pair<int, size_t>> capacity;
        Result res = greedyWithFilter(f, c, capacity, filter);
        if ((res.cost != 0 && res.cost <= best.cost) || best.cost == 0) {
            best = res;
        } else if (last != (size_t)-1 || res.cost == 0) {
            filter[last] = true;
        }
        std::sort(capacity.begin(), capacity.end(), [](std::pair<int, size_t> a, std::pair<int, size_t> b) -> bool {
            return a.first < b.first;
        });
        size_t index = 0;
        while (index < capacity.size() && (filter[capacity[index].second] == false || s.count(capacity[index].second))) {
            index++;
        }
        if (index == capacity.size()) {
            break;
        }
        last = capacity[index].second;
        filter[last] = false;
        s.insert(last);
    }
    if (check(f, c, best) == false) {
        std::cout << "Error Result" << std::endl;
        std::exit(-1);
    }
    return best;
}

Result greedy::greedyWithFilter(const std::vector<Facility> &f, const std::vector<Customer> &c, std::vector<std::pair<int, size_t>> &capacity, const std::vector<bool> &filter) {
    Result res;
    res.cost = 0;
    res.status = std::vector<bool>(f.size());
    res.assignment = std::vector<size_t>(c.size());
    std::vector<std::vector<std::pair<int, size_t>>> cost(c.size());
    for (size_t i = 0; i < c.size(); i++) {
        for (size_t j = 0; j < c[i].assignmentCost.size(); j++) {
            cost[i].push_back(std::make_pair(c[i].assignmentCost[j], j));
        }
        std::sort(cost[i].begin(), cost[i].end(), [](std::pair<int, size_t> a, std::pair<int, size_t> b) -> bool {
            return a.first < b.first;
        });
    }
    for (size_t i = 0; i < f.size(); i++) {
        capacity.push_back(std::make_pair(0, i));
    }
    for (size_t i = 0; i < c.size(); i++) {
        size_t index = 0;
        while (index < cost[i].size() && (filter[cost[i][index].second] == false ||
            capacity[cost[i][index].second].first + c[i].demand > f[cost[i][index].second].capacity)) {
            index++;
        }
        if (index == cost[i].size()) {
            res.cost = 0;
            break;
        }
        if (res.status[cost[i][index].second] == false) {
            res.status[cost[i][index].second] = true;
            res.cost += f[cost[i][index].second].openingCost;
        }
        res.assignment[i] = cost[i][index].second;
        res.cost += cost[i][index].first;
        capacity[cost[i][index].second].first += c[i].demand;
    }
    return res;
}

bool greedy::check(const std::vector<Facility> &f, const std::vector<Customer> &c, const Result res) {
    int cost = 0, capacity[f.size()] = {0};
    for (size_t i = 0; i < f.size(); i++) {
        if (res.status[i]) {
            cost += f[i].openingCost;
        }
    }
    for (size_t i = 0; i < c.size(); i++) {
        capacity[res.assignment[i]] += c[i].demand;
        if (capacity[res.assignment[i]] > f[res.assignment[i]].capacity) {
            return false;
        }
        cost += c[i].assignmentCost[res.assignment[i]];
    }
    return cost == res.cost;
}
