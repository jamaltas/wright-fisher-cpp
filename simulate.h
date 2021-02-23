#pragma once
#include <unordered_map>
#include <string>

#include "time_step.h"
#include "robin_hood.h"

void simulate(robin_hood::unordered_node_map<std::string, int> &pop, const int generations, const double mutation_rate, const int pop_size, const int seq_length, robin_hood::unordered_node_map<std::string, double> fitness, char alphabet[2]);