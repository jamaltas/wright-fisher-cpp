#include "simulate.h"

#include <iostream>
#include <iomanip>
#include <chrono>


class Timer
{
public:
	Timer()
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		Stop();
	}

	void Stop()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::milliseconds>(m_StartTimepoint).time_since_epoch().count();
		auto stop = std::chrono::time_point_cast<std::chrono::milliseconds>(endTimepoint).time_since_epoch().count();

		auto duration = stop - start;

		double seconds = duration * 0.001;

		std::cout << seconds << " seconds\n";
	}

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
};



void simulate(robin_hood::unordered_node_map<std::string, int>& pop, const int generations, const double mutation_rate, const int pop_size, const int seq_length, robin_hood::unordered_node_map<std::string, double> fitness, char alphabet[2])
{

	{
		Timer timer;
		for (int i = 0; i < generations; i++) {
			time_step(pop, mutation_rate, pop_size, seq_length, fitness, alphabet);
	}

	}
}