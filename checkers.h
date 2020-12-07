#include "toString.h"
#include<algorithm>
#include <map>
#include <set>

bool CheckFourOfKind(const std::vector<Card> &sorted_cards) {
    std::map<CardRank, size_t> ranks;
    for (auto &card : sorted_cards) {
        ranks[card.rank]++;
    }
    return std::any_of(ranks.begin(), ranks.end(), [](auto x) { return x.second == 4; });
}

bool CheckFullHouse(const std::vector<Card> &sorted_cards) {
    std::map<CardRank, size_t> ranks;
    for (auto &card : sorted_cards) {
        ranks[card.rank]++;
    }

    size_t count_more_than_two = 0;
    bool has_three = false;
    for (auto &p : ranks) {
        if (p.second >= 2) {
            if (p.second == 3) {
                has_three = true;
            }
            count_more_than_two++;
        }
    }
    return count_more_than_two >= 2 && has_three;
}

bool CheckFlush(const std::vector<Card> &sorted_cards) {
    std::map<CardSuit, size_t> suits;
    for (auto &card : sorted_cards) {
        suits[card.suit]++;
    }

    return std::any_of(suits.begin(), suits.end(), [](auto x) { return x.second >= 5; });
}

bool CheckStraight(const std::vector<Card> &sorted_cards) {
    std::set<CardRank> ranks;
    std::set<CardRank> ranksDuplicate;
    for (auto &card : sorted_cards) {
        ranks.insert(card.rank);
        ranksDuplicate.insert(card.rank);
    }
    size_t counter = 1;
    CardRank prev;
    CardRank cur = *ranks.rbegin();
    ranks.erase(*ranks.rbegin());
    while (!ranks.empty()) {
        if (counter == 5) {
            return true;
        }
        prev = cur;
        cur = *ranks.rbegin();
        ranks.erase(*ranks.rbegin());
        if (cur + 1 == prev) {
            counter++;
        } else {
            counter = 1;
        }
    }

    if (counter == 5) {
        return true;
    }

    if (*ranksDuplicate.rbegin() == CardRank::ACE) {
        cur = *ranksDuplicate.begin();
        if (cur != 2) {
            return false;
        }
        ranksDuplicate.erase(*ranksDuplicate.begin());

        for (size_t i = 0; i < 3; ++i) {
            prev = cur;
            cur = *ranksDuplicate.begin();
            ranksDuplicate.erase(*ranksDuplicate.begin());
            if (prev + 1 == cur) {
                continue;
            } else {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool CheckThreeOfKind(const std::vector<Card> &sorted_cards) {
    std::map<CardRank, size_t> ranks;
    for (auto &card : sorted_cards) {
        ranks[card.rank]++;
    }

    return std::any_of(ranks.begin(), ranks.end(), [](auto x) { return x.second == 3; });
}

bool CheckTwoPairs(const std::vector<Card> &sorted_cards) {
    std::map<CardRank, size_t> ranks;
    for (auto &card : sorted_cards) {
        ranks[card.rank]++;
    }

    size_t count_pairs = 0;
    for (auto &p : ranks) {
        if (p.second == 2) {
            count_pairs++;
        }
    }
    return count_pairs >= 2;
}

bool CheckPair(const std::vector<Card> &sorted_cards) {
    std::map<CardRank, size_t> ranks;
    for (auto &card : sorted_cards) {
        ranks[card.rank]++;
    }

    return std::any_of(ranks.begin(), ranks.end(), [](auto x) { return x.second == 2; });
}

bool CheckStraightFlush(const std::vector<Card> &sorted_cards) {
    std::vector<Card> clubs;
    std::vector<Card> diamonds;
    std::vector<Card> hearts;
    std::vector<Card> spades;
    for (auto &el : sorted_cards) {
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

    bool answer = false;
    if (clubs.size() >= 5) {
        answer |= CheckStraight(clubs);
    }

    if (hearts.size() >= 5) {
        answer |= CheckStraight(hearts);
    }

    if (diamonds.size() >= 5) {
        answer |= CheckStraight(diamonds);
    }

    if (spades.size() >= 5) {
        answer |= CheckStraight(spades);
    }

    return answer;
}