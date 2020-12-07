#include "checkers.h"

enum CombinationType {
    HIGH_CARD = 1, PAIR, TWO_PAIR, THREE_OF_KIND,
    STRAIGHT, FLUSH, FULL_HOUSE, FOUR_OF_KIND, STRAIGHT_FLUSH
};

struct Combination {
    CombinationType type = HIGH_CARD;
    std::vector<Card> combination;
    std::vector<Card> hand;
};

bool CardComparator(Card lhs, Card rhs) {
    return lhs.rank < rhs.rank;
}

Combination getStraight(std::vector<Card> &hand) {
    Combination combination;
    std::vector<Card> stack;
    stack.insert(stack.begin(), hand.begin(), hand.end());
    std::vector<Card> answer = {stack.back()};

    Card prev{};
    Card current = stack.back();
    stack.pop_back();
    while (stack.size() != 1) {
        if (answer.size() == 5) {
            combination.combination = answer;
            break;
        }
        prev = current;
        current = stack.back();
        stack.pop_back();
        if (prev.rank == current.rank + 1) {
            answer.push_back(current);
        } else if (prev.rank == current.rank) {
            continue;
        } else {
            answer.clear();
            answer.push_back(current);
        }
    }

    if (combination.combination.size() != 5) {
        combination.combination.clear();
        combination.combination.push_back(hand.back());
        for (auto &el : hand) {
            if (combination.combination.size() == 5) {
                break;
            } else if (combination.combination.back().rank != el.rank) {
                combination.combination.push_back(el);
            }
        }
    }
    return combination;
}

Combination getCombination(std::vector<Card> hand) {
    Combination combination;
    if (CheckStraightFlush(hand)) {
        std::vector<Card> startHand = combination.hand;
        combination.type = CombinationType::STRAIGHT_FLUSH;
        std::vector<Card> clubs;
        std::vector<Card> diamonds;
        std::vector<Card> hearts;
        std::vector<Card> spades;
        Combination clubsCombination;
        Combination diamondsCombination;
        Combination heartsCombination;
        Combination spadesCombination;
        for (auto &el : hand) {
            switch (el.suit) {
                case CardSuit::CLUB:
                    clubs.push_back(el);
                    break;
                case CardSuit::HEART:
                    hearts.push_back(el);
                    break;
                case CardSuit::DIAMOND:
                    diamonds.push_back(el);
                    break;
                case CardSuit::SPADE:
                    spades.push_back(el);
                    break;
            }
        }

        if (clubs.size() >= 5) {
            combination = getStraight(clubs);
        } else if (hearts.size() >= 5) {
            combination = getStraight(hearts);
        } else if (diamonds.size() >= 5) {
            combination = getStraight(diamonds);
        } else if (spades.size() >= 5) {
            combination = getStraight(spades);
        }
        combination.type = CombinationType::STRAIGHT_FLUSH;
        combination.hand = startHand;
    } else if (CheckFourOfKind(hand)) {
        combination.type = CombinationType::FOUR_OF_KIND;
        std::map<CardRank, size_t> counter;
        std::set<CardRank> fours;
        for (auto &el : hand) {
            counter[el.rank]++;
            if (counter[el.rank] == 4) {
                fours.insert(el.rank);
            }
        }
        for (auto &el : hand) {
            if (el.rank == *fours.rend()) {
                combination.combination.push_back(el);
            }
        }
        for (auto i = hand.rbegin(); i != hand.rend(); ++i) {
            if (combination.combination.size() == 5) {
                break;
            } else if ((*i).rank != *fours.rend()) {
                combination.combination.push_back(*i);
            }
        }
    } else if (CheckFullHouse(hand)) {
        combination.type = CombinationType::FULL_HOUSE;
        std::map<CardRank, size_t> count;
        std::set<CardRank> pairs;
        std::set<CardRank> triplets;
        for (auto &el : hand) {
            count[el.rank]++;
            if (count[el.rank] == 3) {
                triplets.insert(el.rank);
            }
        }
        for (auto &p : count) {
            if (p.second == 2) {
                pairs.insert(p.first);
            }
        }
        CardRank tripletRank = *triplets.rbegin();
        CardRank pairRank = *pairs.rbegin();
        for (auto &el : hand) {
            if (el.rank == tripletRank) {
                combination.combination.push_back(el);
            }
        }

        for (auto &el : hand) {
            if (el.rank == pairRank) {
                combination.combination.push_back(el);
            }
        }

        for (auto i = hand.rbegin(); i != hand.rend(); ++i) {
            if (combination.combination.size() == 5) {
                break;
            } else if ((*i).rank != pairRank && (*i).rank != tripletRank) {
                combination.combination.push_back(*i);
            }
        }
    } else if (CheckFlush(hand)) {
        combination.type = CombinationType::FLUSH;
        std::map<CardSuit, size_t> count;
        CardSuit FlushSuit;
        for (auto &el : hand) {
            count[el.suit]++;
            if (count[el.suit] == 5) {
                FlushSuit = el.suit;
                break;
            }
        }

        for (auto i = hand.rbegin(); i != hand.rend(); ++i) {
            if (combination.combination.size() == 5) {
                break;
            }
            if ((*i).suit == FlushSuit) {
                combination.combination.push_back(*i);
            }
        }
    } else if (CheckStraight(hand)) {
        std::vector<Card> startHand = combination.hand;
        combination = getStraight(hand);
        combination.type = CombinationType::STRAIGHT;
        combination.hand = startHand;
    } else if (CheckThreeOfKind(hand)) {
        combination.type = CombinationType::THREE_OF_KIND;
        std::map<CardRank, size_t> count;
        std::set<CardRank> triplets;
        CardRank TripletRank;
        for (auto &el : hand) {
            count[el.rank]++;
            if (count[el.rank] == 3) {
                triplets.insert(el.rank);
            }
        }
        for (auto &el : triplets) {
            TripletRank = el;
        }
        for (auto &el : hand) {
            if (el.rank == TripletRank) {
                combination.combination.push_back(el);
            }
        }
        for (auto i = hand.rbegin(); i != hand.rend(); ++i) {
            if (combination.combination.size() == 5) {
                break;
            } else if ((*i).rank != TripletRank) {
                combination.combination.push_back(*i);
            }
        }
    } else if (CheckTwoPairs(hand)) {
        combination.type = CombinationType::TWO_PAIR;
        std::map<CardRank, size_t> count;
        std::set<CardRank> pairs;
        for (auto &el : hand) {
            count[el.rank]++;
            if (count[el.rank] == 2) {
                pairs.insert(el.rank);
            }
        }
        while (pairs.size() != 2) {
            pairs.erase(*pairs.begin());
        }
        CardRank smallerRank = (*pairs.begin());
        pairs.erase(pairs.begin());
        CardRank biggerRank = (*pairs.begin());
        pairs.erase(pairs.begin());
        for (auto &el : hand) {
            if (el.rank == biggerRank) {
                combination.combination.push_back(el);
            }
        }

        for (auto &el : hand) {
            if (el.rank == smallerRank) {
                combination.combination.push_back(el);
            }
        }

        for (auto i = hand.rbegin(); i != hand.rend(); ++i) {
            if (combination.combination.size() == 5) {
                break;
            } else if ((*i).rank != smallerRank && (*i).rank != biggerRank) {
                combination.combination.push_back(*i);
            }
        }
    } else if (CheckPair(hand)) {
        combination.type = CombinationType::PAIR;
        std::map<CardRank, size_t> count;
        CardRank PairRank;
        for (auto &el : hand) {
            count[el.rank]++;
            if (count[el.rank] == 2) {
                PairRank = el.rank;
                break;
            }
        }
        for (auto &el : hand) {
            if (el.rank == PairRank) {
                combination.combination.push_back(el);
            }
        }
        for (auto i = hand.rbegin(); i != hand.rend(); ++i) {
            if (combination.combination.size() == 5) {
                break;
            } else if ((*i).rank != PairRank) {
                combination.combination.push_back(*i);
            }
        }
    } else {
        combination.type = CombinationType::HIGH_CARD;
        for (auto i = hand.rbegin(); i != hand.rend(); ++i) {
            if (combination.combination.size() == 5) {
                break;
            }
            combination.combination.push_back(*i);
        }
    }
    return combination;
}

std::vector<Combination> getHigherCombinations(Game game) {
    /*
     * We get combination from hand and board cards
     * that consists of 5 elements that forms higher combination and higher elements,
     * so when players have the same combination we can check higher of them
     */
    std::vector<Combination> combinations;

    for (auto hand: game.players_cards) {
        // Save hand to get it in the end
        std::vector<Card> saved_hand = hand;
        // Mix hand cards with board
        hand.insert(hand.begin(), game.board.begin(), game.board.end());
        // Sort hand by increasing rank
        std::stable_sort(hand.begin(), hand.end(), CardComparator);
        Combination combination = getCombination(hand);
        combination.hand = saved_hand;
        combinations.push_back(combination);
    }

    return combinations;
}