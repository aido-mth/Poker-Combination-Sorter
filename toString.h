#include "parsers.h"
#include <string>

std::string handToString(const std::vector<Card> &hand) {
    std::string answer;
    for (auto &card : hand) {
        if (card.rank == ACE) {
            answer.push_back('A');
        } else if (card.rank == KING) {
            answer.push_back('K');
        } else if (card.rank == QUEEN) {
            answer.push_back('Q');
        } else if (card.rank == JACK) {
            answer.push_back('J');
        } else if (card.rank == TEN) {
            answer.push_back('T');
        } else {
            answer.push_back('0' + card.rank);
        }

        if (card.suit == HEART) {
            answer.push_back('h');
        } else if (card.suit == DIAMOND) {
            answer.push_back('d');
        } else if (card.suit == SPADE) {
            answer.push_back('s');
        } else {
            answer.push_back('c');
        }
    }
    return answer;
}