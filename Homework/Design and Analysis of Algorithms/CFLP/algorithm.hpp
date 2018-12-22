#ifndef __ALGORITHM_HPP__
#define __ALGORITHM_HPP__

#include "types.hpp"

Result Greedy(const std::vector<Facility> &f, const std::vector<Customer> &c);
Result BadLocalSearch(const std::vector<Facility> &f, const std::vector<Customer> &c);
Result LocalSearch(const std::vector<Facility> &f, const std::vector<Customer> &c);
Result SimulatedAnnealing(const std::vector<Facility> &f, const std::vector<Customer> &c);

#endif // __ALGORITHM_HPP__
