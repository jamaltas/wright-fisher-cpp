#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "robin_hood.h"


double calculate_evolvability(const robin_hood::unordered_node_map<std::string, int>& pop, const std::vector<std::string>& haplotype_binaries, robin_hood::unordered_node_map<std::string, double>& fitness_drug);