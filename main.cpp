#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <bitset>
#include <array>

#include "simulate.h"
#include "landscape.h"
#include "analyze_data.h"

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
	const int pop_size = 100000;
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
	robin_hood::unordered_node_map<std::string, double> fitness_drug;

	pop.insert({base_haplotype, pop_size});

	// Create the neutral landscape.
	std::vector<double> neutral_ls(haplotypes, 1.0);

	// Insert the neutral fitness landscape values into the fitness map for simulation.
	for (int i = 0; i < haplotypes; i++) {
		fitness.insert({haplotype_binaries.at(i), neutral_ls.at(i)});
	}

	// Simulates the Wright-Fisher evolution
	simulate(pop, generations, mutation_rate, pop_size, seq_length, fitness, alphabet);

	// Print final evolved population
	// print_map(pop);

	// Create and normalize the drug fitness landscape
	std::vector<double> drug_landscape = create_landscape(seq_length, 1);
	drug_landscape = normalize_landscape(drug_landscape);

	// Insert the drug fitness landscape values into the fitness_drug map for analysis.
	for (int i = 0; i < haplotypes; i++) {
		fitness_drug.insert({ haplotype_binaries.at(i), drug_landscape.at(i) });
	}

	// Create container and calculate "evolvability"
	std::vector<double> evolvability;
	evolvability.push_back(calculate_evolvability(pop, haplotype_binaries, fitness_drug));
	
	std::cout << "Evolvability is: " << evolvability.at(0) << std::endl;



	return 0;
}


