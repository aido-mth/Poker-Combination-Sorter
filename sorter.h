#include <sstream>
#include <iostream>
#include "getCombinations.h"
#include "split.h"

bool CombinationComparator(Combination lhs, Combination rhs) {
    if (lhs.type == rhs.type) {
        switch (lhs.type) {
            case CombinationType::STRAIGHT_FLUSH:
                return lhs.combination.back().rank < rhs.combination.back().rank;
            case CombinationType::FOUR_OF_KIND:
                if (lhs.combination[0].rank == rhs.combination[0].rank) {
                    return lhs.combination.back().rank < rhs.combination.back().rank;
                }
                return lhs.combination[0].rank < rhs.combination[0].rank;
            case CombinationType::FULL_HOUSE:
                if (lhs.combination[0].rank == rhs.combination[0].rank) {
                    return lhs.combination[3].rank < rhs.combination[3].rank;
                }
                return lhs.combination[0].rank < rhs.combination[0].rank;
            case CombinationType::FLUSH:
                for (size_t i = 0; i < 5; ++i) {
                    if (lhs.combination[i].rank == rhs.combination[i].rank) {
                        continue;
                    }
                    return lhs.combination[i].rank < rhs.combination[i].rank;
                }
                return lhs.combination.back().rank < rhs.combination.back().rank;
            case CombinationType::STRAIGHT:
                return lhs.combination.back().rank < rhs.combination.back().rank;
            case CombinationType::THREE_OF_KIND:
                if (lhs.combination[0].rank == rhs.combination[0].rank) {
                    if (lhs.combination[3].rank == rhs.combination[3].rank) {
                        return lhs.combination[4].rank < rhs.combination[4].rank;
                    }
                    return lhs.combination[3].rank < rhs.combination[3].rank;
                }
                return lhs.combination[0].rank < rhs.combination[0].rank;
            case CombinationType::TWO_PAIR:
                if (lhs.combination[0].rank == rhs.combination[0].rank) {
                    if (lhs.combination[2].rank == rhs.combination[2].rank) {
                        return lhs.combination[4].rank < rhs.combination[4].rank;
                    }
                    return lhs.combination[2].rank < rhs.combination[2].rank;
                }
                return lhs.combination[0].rank < rhs.combination[0].rank;
            case CombinationType::PAIR:
                if (lhs.combination[0].rank == rhs.combination[0].rank) {
                    for (size_t i = 2; i < 5; ++i) {
                        if (lhs.combination[i].rank == rhs.combination[i].rank) {
                            continue;
                        }
                        return lhs.combination[i].rank < rhs.combination[i].rank;
                    }
                    return lhs.combination.back().rank < rhs.combination.back().rank;
                }
                return lhs.combination[0].rank < rhs.combination[0].rank;
            case CombinationType::HIGH_CARD:
                for (size_t i = 0; i < 5; ++i) {
                    if (lhs.combination[i].rank == rhs.combination[i].rank) {
                        continue;
                    }
                    return lhs.combination[i].rank < rhs.combination[i].rank;
                }
                return lhs.combination.back().rank < rhs.combination.back().rank;
        }
    }
    return lhs.type < rhs.type;
}

bool CheckEqual(const Combination& lhs, const Combination& rhs) {
    return !CombinationComparator(lhs, rhs) && !CombinationComparator(rhs, lhs);
}

void SortCombinations() {
    std::string line;
    while (std::getline(std::cin, line)) {
        try {
            auto combinations = getHigherCombinations(ParseLine(Split(line)));
            std::stable_sort(combinations.begin(), combinations.end(), CombinationComparator);
            std::cout << handToString(combinations[0].hand);
            for (size_t i = 1; i < combinations.size() - 1; ++i) {
                if (CheckEqual(combinations[i - 1], combinations[i])) {
                    std::cout << "=";
                } else {
                    std::cout << " ";
                }
                std::cout << handToString(combinations[i].hand);
            }
            if (CheckEqual(combinations.back(), combinations[combinations.size() - 2])) {
                std::cout << "=";
            } else {
                std::cout << " ";
            }
            std::cout << handToString(combinations.back().hand) << '\n';
        } catch (ParseException& e) {
            std::cout << "Error: " << e.what() << '\n';
        }

    }
}