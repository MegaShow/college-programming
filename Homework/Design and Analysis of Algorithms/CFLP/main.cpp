#include <chrono>
#include <cstdio>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "algorithm.hpp"
#include "types.hpp"

std::pair<Result, std::pair<std::vector<Facility>, std::vector<Customer>>> input(int testcase) {
    size_t facilityNum, customerNum;
    std::vector<Facility> facilities;
    std::vector<Customer> customers;
    Result result;
    // 数据输入
    std::ifstream in("testcases/p" + std::to_string(testcase));
    in >> facilityNum >> customerNum;
    for (size_t i = 0; i < facilityNum; i++) {
        Facility facility;
        in >> facility.capacity >> facility.openingCost;
        facilities.push_back(facility);
    }
    for (size_t i = 0; i < customerNum; i++) {
        Customer customer;
        double val;
        in >> val;
        customer.demand = (int) val;
        customers.push_back(customer);
    }
    for (size_t i = 0; i < facilityNum; i++) {
        for (size_t j = 0; j < customerNum; j++) {
            double val;
            in >> val;
            customers[j].assignmentCost.push_back((int) val);
        }
    }
    in.close();
    // 当前最优解输入
    std::ifstream rin("best/p" + std::to_string(testcase));
    if (rin.is_open()) {
        rin >> result.cost;
        for (size_t i = 0; i < facilityNum; i++) {
            bool val;
            rin >> val;
            result.status.push_back(val);
        }
        for (size_t i = 0; i < customerNum; i++) {
            size_t val;
            rin >> val;
            result.assignment.push_back(val);
        }
    } else {
        result.cost = 0;
    }
    rin.close();
    return std::make_pair(result, std::make_pair(facilities, customers));
}

void output(int testcase, Result best, Result res) {
    // 解输出
    std::cout << res.cost << std::endl;
    if (res.status.size() != 0) {
        std::cout << res.status[0];
        for (size_t i = 1; i < res.status.size(); i++) {
            std::cout << ' ' << res.status[i];
        }
        std::cout << std::endl;
    }
    if (res.assignment.size() != 0) {
        std::cout << res.assignment[0];
        for (size_t i = 1; i < res.assignment.size(); i++) {
            std::cout << ' ' << res.assignment[i];
        }
        std::cout << std::endl;
    }
    // 对比、存储当前最优解
    if (best.cost < res.cost && best.cost != 0) {
        std::cout << "Compare with best cost " << best.cost << ", percentage " << (float)(res.cost - best.cost) / best.cost * 100 << '%' << std::endl; 
    } else {
        std::cout << "Get the best cost" << std::endl;
        std::ofstream out("best/p" + std::to_string(testcase));
        out << res.cost << std::endl;
        if (res.status.size() != 0) {
            out << res.status[0];
            for (size_t i = 1; i < res.status.size(); i++) {
                out << ' ' << res.status[i];
            }
            out << std::endl;
        }
        if (res.assignment.size() != 0) {
            out << res.assignment[0];
            for (size_t i = 1; i < res.assignment.size(); i++) {
                out << ' ' << res.assignment[i];
            }
            out << std::endl;
        }
        out.close();
    }
}

void test(int testcase, std::function<Result(std::vector<Facility>, std::vector<Customer>)> fn) {
    std::cout << "Test " << testcase << ":" << std::endl;
    std::pair<Result, std::pair<std::vector<Facility>, std::vector<Customer>>> data = input(testcase);
    auto start = std::chrono::system_clock::now();
    Result res = fn(data.second.first, data.second.second);
    auto stop = std::chrono::system_clock::now();
    output(testcase, data.first, res);
    std::ofstream out("best/markdown", std::ios_base::app);
    out << "| p" << testcase << " | " << res.cost << " | " << (double) std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() / 1000 << " |" << std::endl;
    out.close();
    std::cout << std::endl;
}

int main(int argv, char** args) {
    if (argv != 2) {
        std::cout << "Please input algorithm type" << std::endl;
        std::cout << "For example, 'greedy', 'local_search', 'bad_local_search', 'sa'" << std::endl;
        return 2;
    }
    std::string type(args[1]);
    std::function<Result(std::vector<Facility>, std::vector<Customer>)> fn;
    if (type == "greedy") {
        fn = Greedy;
    } else if (type == "local_search") {
        fn = LocalSearch;
    } else if (type == "bad_local_search") {
        fn = BadLocalSearch;
    } else if (type == "sa") {
        fn = SimulatedAnnealing;
    }
    std::remove("best/markdown");
    for (int i = 1; i <= 71; i++) {
        test(i, fn);
    }
}
