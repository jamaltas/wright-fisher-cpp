#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <random>

#include "robin_hood.h"

static std::random_device randiv;
static std::mt19937 generator(randiv());

void offspring_step(robin_hood::unordered_node_map<std::string, int> &pop, const int pop_size, robin_hood::unordered_node_map<std::string, double> &fitness);

std::vector<int> get_offspring_counts(const robin_hood::unordered_node_map<std::string, int> &pop, const int pop_size, robin_hood::unordered_node_map<std::string, double> &fitness);