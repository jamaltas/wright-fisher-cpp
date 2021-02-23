#include "analyze_data.h"


double calculate_evolvability(const robin_hood::unordered_node_map<std::string, int> &pop, const std::vector<std::string> &haplotype_binaries, robin_hood::unordered_node_map<std::string, double> &fitness_drug) {

	// Create containers to store the haplotypes and fitnesses that exist in pop
	std::vector<std::string> population_haplotypes;
	population_haplotypes.reserve(pop.size());
	std::vector<double> occupied_fitnesses;
	occupied_fitnesses.reserve(pop.size());

	// Loop through pop and store the haplotypes with nonzero population.
	for (auto& hap: pop) {
		population_haplotypes.push_back(hap.first);
	}

	// Calculate the average fitness of the population
	// Add the fitness values of occupied states to the container.
	robin_hood::unordered_node_map<std::string, double>::iterator it;
	for (int i = 0; i < population_haplotypes.size(); i++) {
		it = fitness_drug.find(population_haplotypes.at(i));
		occupied_fitnesses.push_back(it->second);
	}

	double evolvability = *max_element(occupied_fitnesses.begin(), occupied_fitnesses.end());

	return evolvability;
}