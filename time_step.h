#pragma once
#include <unordered_map>
#include <string>

#include "mutation.h"
#include "offspring.h"

void time_step(robin_hood::unordered_node_map<std::string, int> &pop, const double mutation_rate, const int pop_size, const int seq_length, robin_hood::unordered_node_map<std::string, double> fitness, char alphabet[2]);
