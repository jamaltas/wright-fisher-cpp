#include "offspring.h"
#include <algorithm>
#include <iostream>


void offspring_step(robin_hood::unordered_node_map<std::string, int> &pop, const int pop_size, robin_hood::unordered_node_map<std::string, double> &fitness) {
     
    std::vector<std::string> haplotypes;
    haplotypes.reserve(pop.size());

    for (auto& hap : pop) {
        haplotypes.push_back(hap.first);
    }

    std::vector<int> counts = get_offspring_counts(pop, pop_size, fitness);


    robin_hood::unordered_node_map<std::string, int>::iterator it;
    for (int i = 0; i < haplotypes.size(); i++) {
        it = pop.find(haplotypes.at(i));

        if (counts.at(i) > 0) {
            it->second = counts.at(i);
        }
        else {
            pop.erase(it);
        }
    }
  

    int total2 = 0;
    for (auto it = pop.cbegin(); it != pop.cend(); it++) {
        total2 += it->second;
    }

    if (total2 != pop_size) {
        std::cout << total2 << std::endl;
        std::cout << "offspring_step end" << std::endl;
        exit(1);

    }

}


std::vector<int> get_offspring_counts(const robin_hood::unordered_node_map<std::string, int> &pop, const int pop_size, robin_hood::unordered_node_map<std::string, double> &fitness) {

    std::vector<std::string> haplotypes;
    haplotypes.reserve(pop.size());
    std::vector<double> frequencies;
    frequencies.reserve(pop.size());

    for (auto& hap_freq : pop) {
        haplotypes.push_back(hap_freq.first);
        frequencies.push_back(double(hap_freq.second) / pop_size);
    }

    std::vector<double> fitnesses;
    robin_hood::unordered_node_map<std::string, double>::iterator it;
    for (int i = 0; i < pop.size(); i++) {
        it = fitness.find(haplotypes.at(i));

        fitnesses.push_back(it->second);
    }

    std::vector<double> weights;
    double weight_total = 0;
    for (int i = 0; i < pop.size(); i++) {
        weights.push_back(frequencies.at(i)*fitnesses.at(i));
        weight_total = weight_total + (frequencies.at(i) * fitnesses.at(i));
    }

    std::transform(weights.begin(), weights.end(), weights.begin(), [&weight_total](auto& c) {return c / weight_total; });

    std::vector<int> offspring_counts;

    double next_weight_divider = 1;
    int pop_draw_remain = pop_size;
    for (int i = 0; i < pop.size(); i++) {

        if (weights.at(i) / next_weight_divider < 1) {

            std::binomial_distribution<> d(pop_draw_remain, weights.at(i) / next_weight_divider);
            int drawn_count = d(generator);

            offspring_counts.push_back(drawn_count);
            pop_draw_remain = pop_draw_remain - drawn_count;
            next_weight_divider = next_weight_divider - weights.at(i);
        }
        else {
            int drawn_count = pop_draw_remain;

            offspring_counts.push_back(drawn_count);
        }
        
    }
    return offspring_counts;
}