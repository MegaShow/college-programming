#include <chrono>
#include <iostream>
#include <random>
#include <vector>

#include "algorithm.hpp"
#include "types.hpp"

namespace simulated_annealing {
    Result generateNeighborSolution(const std::vector<Facility> &f, const std::vector<Customer> &c, Result best);
    bool setNewCost(const std::vector<Facility> &f, const std::vector<Customer> &c, Result &res);

    const double T_START = 500;  // 初始温度
    const double T_END = 0.000001; // 终止温度
    const double Q = 0.96; // 降温系数
}

using namespace simulated_annealing;


Result SimulatedAnnealing(const std::vector<Facility> &f, const std::vector<Customer> &c) {
    Result best = Greedy(f, c);
    double t = T_START;
    for (size_t i = 0; t > T_END; i++) {
        Result res = generateNeighborSolution(f, c, best);
        if (best.cost > res.cost) {
            best = res;
        } else {
            std::default_random_engine random(std::chrono::system_clock::now().time_since_epoch().count());
            std::uniform_real_distribution<> dist(0, 1);
            double r = dist(random);
            double p = std::exp((double)(best.cost - res.cost) / t);
            if (r < p) {
                best = res;
            }
        }
        t *= Q;
    }
    return best;
}

// 策略1: 移动1个人
// 策略2: 交换2个人
// 策略3: 交换2个设备
Result simulated_annealing::generateNeighborSolution(const std::vector<Facility> &f, const std::vector<Customer> &c, Result best) {
    std::default_random_engine random(std::chrono::system_clock::now().time_since_epoch().count());
    unsigned type = random() % 3;
    Result res;
    size_t count = 0;
    bool flag = false;
    switch (type + 1) {
    case 1: // 移动1个人
        do {
            // i - 人, j - 设备
            size_t i = random() % c.size(), j = random() % f.size();
            if (best.assignment[i] == j) {
                flag = true;
                continue;
            } else {
                flag = false;
            }
            res = best;
            size_t last = res.assignment[i];
            res.assignment[i] = j;
            res.status[j] = true;
            bool empty = true;
            for (size_t k = 0; k < c.size(); k++) {
                if (res.assignment[k] == last) {
                    empty = false;
                    break;
                }
            }
            if (empty) {
                res.status[last] = false;
            }
            count++;
        } while (count < 100 && (flag || setNewCost(f, c, res) == false));
        break;
    case 2: // 交换2个人
        do {
            // i - 人A, j - 人B
            size_t i = random() % c.size(), j = random() % c.size();
            if (i == j || best.assignment[i] == best.assignment[j]) {
                flag = true;
                continue;
            } else {
                flag = false;
            }
            res = best;
            size_t tmp = res.assignment[i];
            res.assignment[i] = res.assignment[j];
            res.assignment[j] = tmp;
            count++;
        } while (count < 100 && (flag || setNewCost(f, c, res) == false));
        break;
    case 3: // 交换2个设备
        do {
            // i - 设备A, j - 设备B
            size_t i = random() % f.size(), j = random() % f.size();
            if (i == j) {
                flag = true;
                continue;
            } else {
                flag = false;
            }
            res = best;
            for (size_t k = 0; k < c.size(); k++) {
                if (res.assignment[k] == i) {
                    res.assignment[k] = j;
                } else if (res.assignment[k] == j) {
                    res.assignment[k] = i;
                }
            }
            if (res.status[i] == true && res.status[j] == false) {
                res.status[i] = false;
                res.status[j] = true;
            } else if (res.status[i] == false && res.status[j] == true) {
                res.status[i] = true;
                res.status[j] = false;
            }
            count++;
        } while (count < 100 && (flag || setNewCost(f, c, res) == false));
        break;
    }
    return res;
}

bool simulated_annealing::setNewCost(const std::vector<Facility> &f, const std::vector<Customer> &c, Result &res) {
    int cost = 0, capacity[f.size()] = {0};
    for (size_t i = 0; i < f.size(); i++) {
        if (res.status[i]) {
            cost += f[i].openingCost;
        }
    }
    for (size_t i = 0; i < c.size(); i++) {
        capacity[res.assignment[i]] += c[i].demand;
        if (capacity[res.assignment[i]] > f[res.assignment[i]].capacity || res.status[res.assignment[i]] == false) {
            return false;
        }
        cost += c[i].assignmentCost[res.assignment[i]];
    }
    res.cost = cost;
    return true;
}
