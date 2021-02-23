#include "mutation.h"
#include <ctime>
#include <iostream>

void get_mutant(std::string &haplotype, const int seq_length, const char alphabet[2]) {
	std::uniform_real_distribution<double> dis(0.0, 1.0);
	int site = int(dis(gen) * seq_length);

	char current_bp = haplotype[site];

	if (current_bp == '0') {
		haplotype[site] = '1';
	}
	else {
		haplotype[site] = '0';
	}
}

std::string get_random_haplotype(robin_hood::unordered_node_map<std::string, int>& pop, const int pop_size) {

	std::uniform_int_distribution<int> dis(0.0, pop_size);
	int x = dis(gen);

	int cumulative = 0;
	auto last = pop.cbegin();

	for (auto it = pop.cbegin(); it != pop.cend(); it++) {
		last = it;
		cumulative += it->second;

		if (x < cumulative) {
			return it->first;
		}

	}
	return last->first;

}


void mutation_event(robin_hood::unordered_node_map<std::string, int> &pop, const int pop_size, const int seq_length, const char alphabet[2]) {
	
	robin_hood::unordered_node_map<std::string, int>::iterator it;
	robin_hood::unordered_node_map<std::string, int>::iterator it2;
	
	std::string haplotype = get_random_haplotype(pop, pop_size);

	it = pop.find(haplotype);
	
	if (it->second > 1) {
		
		it->second--;
		
		get_mutant(haplotype, seq_length, alphabet);
		
		it2 = pop.find(haplotype);
		if (it2 != pop.end()) {
			it2->second++;
		}
		else {
			pop.insert({ haplotype, 1 });
		}
		
	}

}

int get_mutation_count(const double mutation_rate, const int pop_size, const int seq_length) {

	double avg_mut_count = mutation_rate * pop_size * seq_length;

	std::poisson_distribution<int> pd(avg_mut_count);
	return pd(gen);
}

void mutation_step(robin_hood::unordered_node_map<std::string, int> &pop, const double mutation_rate, const int pop_size, const int seq_length, const char alphabet[2]) {

	const int mutation_count = get_mutation_count(mutation_rate, pop_size, seq_length);

	for (int i = 0; i < mutation_count; i++) {
		mutation_event(pop, pop_size, seq_length, alphabet);
	}
}

/*
* old and slow versions below:
* 
std::string random_hap_choice(std::vector<std::string>& haplotypes, std::vector<double>& frequencies) {

	std::uniform_real_distribution<double> dis(0.0, 1.0);
	double x = dis(gen);

	double cumulative = 0;
	for (int i = 0; i < frequencies.size(); i++) {
		cumulative = cumulative + frequencies.at(i);
		if (x < cumulative) {
			return haplotypes.at(i);
		}
	}
	return haplotypes.back();
}


std::string get_random_haplotype(robin_hood::unordered_node_map<std::string, int>& pop, const int pop_size) {

	std::vector<std::string> haplotypes;
	haplotypes.reserve(pop.size());
	std::vector<double> frequencies;
	frequencies.reserve(pop.size());

	double total = 0;
	for (auto& hap_freq : pop) {
		haplotypes.emplace_back(hap_freq.first);
		frequencies.emplace_back(double(hap_freq.second) / pop_size);
		total = total + (double(hap_freq.second) / pop_size);
	}

	std::transform(frequencies.begin(), frequencies.end(), frequencies.begin(), [&total](auto& c) {return c / total; });

	std::string haplotype_to_mutate = random_hap_choice(haplotypes, frequencies);

	return haplotype_to_mutate;

}
*/