#include "landscape.h"


std::vector<double> create_landscape(const int seq_length, const double sigma) {

	const int total_haplotypes = pow(2, seq_length);

	std::uniform_real_distribution<double> dis(-1.0, 1.0);
	std::normal_distribution<double> distribution(0.0, sigma);

	std::vector<double> fitness_landscape;
	std::vector<double> mutation_fitness;

	fitness_landscape.push_back(0);

	for (int i = 0; i < seq_length; i++) {
		mutation_fitness.push_back(dis(genny));
	}

	for (int j = 0; j < seq_length; j++) {
		int snapshot_size = fitness_landscape.size();
		for (int i = 0; i < snapshot_size; i++) {
			fitness_landscape.push_back(fitness_landscape.at(i) + mutation_fitness.at(j));
		}
	}

	for (int i = 0; i < total_haplotypes; i++) {
		fitness_landscape.at(i) += distribution(genny);
	}

	return fitness_landscape;
}

void print_landscape(std::vector<std::string>& haplotype_binaries, std::vector<double> &drug_landscape) {
	
	// Print out the drug landscape.
	for (int i = 0; i < drug_landscape.size(); i++) {
		std::cout << "{" << haplotype_binaries.at(i) << ": " << drug_landscape.at(i) << "}\n";
	}

}

std::vector<double> normalize_landscape(std::vector<double>& drug_landscape) {
	
	// Grab the min and max for normalization purposes.
	double ls_min = *min_element(drug_landscape.begin(), drug_landscape.end());
	double ls_max = *max_element(drug_landscape.begin(), drug_landscape.end());

	// Normalize to between 0 and 1 (plus some tiny value to avoid errors).
	for (int i = 0; i < drug_landscape.size(); i++) {
		drug_landscape.at(i) = ((drug_landscape.at(i) - ls_min) / (ls_max - ls_min)) + 1e-5;
	}

	return drug_landscape;
}