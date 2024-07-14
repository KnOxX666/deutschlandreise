#include "PermutationCreator.h"
#include <iostream>
#include <algorithm>

using namespace std;


void print(const std::vector<std::string>& v)
{
    for (auto& e : v) {
        std::cout << " " << e;
    }
    std::cout << std::endl;
}

void PermutationCreator::CalculatePermutations(const std::vector<std::string>& _transitCities)
{
    std::vector<std::string> transitCities = _transitCities;
    do {
        print(transitCities);
    } while (std::next_permutation(transitCities.begin(), transitCities.end()));
}