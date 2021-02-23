#pragma once
#include <string>
#include <unordered_map>
#include <random>

#include "robin_hood.h"

static std::random_device rd;
static std::mt19937 gen(rd());

void get_mutant(std::string &haplotype, const int seq_length, const char alphabet[2]);

std::string get_random_haplotype(robin_hood::unordered_node_map<std::string, int> &pop, const int pop_size);

void mutation_step(robin_hood::unordered_node_map<std::string, int> &pop, const double mutation_rate, const int pop_size, const int seq_length, const char alphabet[2]);

int get_mutation_count(const double mutation_rate, const int pop_size, const int seq_length);

void mutation_event(robin_hood::unordered_node_map<std::string, int> &pop, const int pop_size, const int seq_lenght, const char alphabet[2]);


//old code that is slower. There is an old get_random_haplotype to pair with this old function as well. New code is just faster, however.
//std::string random_hap_choice(std::vector<std::string>& haplotypes, std::vector<double>& frequencies);