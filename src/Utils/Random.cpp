//
// Created by seekerses on 06.06.2024.
//

#include "Random.h"

#include <random>

bool randomBoolean() {
	static std::default_random_engine generator(std::random_device{}());
	static std::bernoulli_distribution distribution(0.5);
	return distribution(generator);
}
