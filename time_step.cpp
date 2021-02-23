#include "time_step.h"



void time_step(robin_hood::unordered_node_map<std::string, int> &pop, const double mutation_rate, const int pop_size, const int seq_length, robin_hood::unordered_node_map<std::string, double> fitness, char alphabet[2]) {

	mutation_step(pop, mutation_rate, pop_size, seq_length, alphabet);
	offspring_step(pop, pop_size, fitness);

}
