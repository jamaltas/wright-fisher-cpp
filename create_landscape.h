#pragma once
#include <string>
#include <random>
#include <iostream>

#include "robin_hood.h"


static std::random_device rdd;
static std::mt19937 genny(rdd());


std::vector<double> create_landscape(const int seq_length, const double sigma);

