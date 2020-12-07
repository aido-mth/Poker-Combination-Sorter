#include "parsers.h"
#include <string>

std::string handToString(const std::vector<Card>& hand) {
    std::string answer;
    for (auto &card : hand) {
        switch (card.rank) {
            case CardRank::ACE:
                answer.push_back('A');
                break;
            case CardRank::KING:
                answer.push_back('K');
                break;
            case CardRank::QUEEN:
                answer.push_back('Q');
                break;
            case CardRank::JACK:
                answer.push_back('J');
                break;
            case CardRank::TEN:
                answer.push_back('T');
                break;
            default:
                answer.push_back('0' + card.rank);
        }
        switch (card.suit) {
            case CardSuit::HEART:
                answer.push_back('h');
                break;
            case CardSuit::DIAMOND:
                answer.push_back('d');
                break;
            case CardSuit::SPADE:
                answer.push_back('s');
                break;
            case CardSuit::CLUB:
                answer.push_back('c');
                break;
        }
    }
    return answer;
}