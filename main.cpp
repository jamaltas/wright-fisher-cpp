#include <iostream>
#include <math.h>
#include <vector>
#include <bitset>
#include <array>

#include "simulate.h"



//Function for printing the population at the end.
template<typename K, typename V>
void print_map(robin_hood::unordered_node_map<K, V> const& m)
{
	for (auto const& pair : m) {
		std::cout << "{" << pair.first << ": " << pair.second << "}\n";
	}
}

int main() {

	const int seq_length = 10;
	const int haplotypes = pow(2, seq_length);
	const int generations = 500;
	const int pop_size = 10000;
	const double mutation_rate = 1e-5;

	//Consider using the cppitertools package? Consider using char instead of string?
	std::vector<std::string> haplotype_binaries;

	//Sets the possible base pairs for any haplotype
	//Currently only works for 0s and 1s... change later if needed.
	char alphabet[2] = { '0', '1' };

	//Sets the inital evolving condition to the "0...0" haplotype.
	std::string base_haplotype = std::bitset<seq_length>(0).to_string();

	for (int i = 0; i < haplotypes; i++) {
		haplotype_binaries.push_back (std::bitset<seq_length>(i).to_string());
	}

	// Create unordered hash tables for population and fitness for each haplotype
	robin_hood::unordered_node_map<std::string, int> pop;
	robin_hood::unordered_node_map<std::string, double> fitness;

	pop.insert({base_haplotype, pop_size});

	std::vector<double> A_ls(haplotypes, 1.0);

	for (int i = 0; i < haplotypes; i++) {
		fitness.insert({haplotype_binaries.at(i), A_ls.at(i)});
	}

	//figure out history later
	simulate(pop, generations, mutation_rate, pop_size, seq_length, fitness, alphabet);


	//print_map(pop);

	std::cout << pop.size() << std::endl;

	return 0;
}


