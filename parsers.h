#include <vector>
#include <string>

enum CardSuit {
    DIAMOND, CLUB, HEART, SPADE
};
enum CardRank {
    TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE
};
enum GameType {
    HOLDEM, OMAHA, FIVE_CARD_DRAW, UNKNOWN
};

struct Card {
    CardRank rank;
    CardSuit suit;

    bool operator<(Card card) const {
        return rank < card.rank;
    }
};

struct Game {
    GameType type = UNKNOWN;
    std::vector<Card> board;
    std::vector<std::vector<Card>> players_cards;
};

class ParseException : public std::exception {
public:
    explicit ParseException(const char *ex_message) : message(std::string(ex_message)) {
    }

    ~ParseException() throw() override {}

    virtual const char *what() const throw() {
        return message.c_str();
    }

private:
    std::string message;
};

std::vector<Card> ParseHand(std::string hand) {
    std::vector<Card> answer;
    CardRank rank;
    CardSuit suit;
    if (hand.length() == 4 || hand.length() == 8 || hand.length() == 10) {
        for (size_t i = 0; i < hand.length(); i += 2) {
            Card card{};
            // Getting card rank
            if (hand[i] > '0' && hand[i] <= '9') {
                rank = static_cast<CardRank>(hand[i] - '0');
            } else {
                switch (hand[i]) {
                    case 'T':
                        rank = CardRank::TEN;
                        break;
                    case 'J':
                        rank = CardRank::JACK;
                        break;
                    case 'Q':
                        rank = CardRank::QUEEN;
                        break;
                    case 'K':
                        rank = CardRank::KING;
                        break;
                    case 'A':
                        rank = CardRank::ACE;
                        break;
                    default:
                        throw ParseException("Unknown card rank");
                }
            }

            // Getting card suit
            switch (hand[i + 1]) {
                case 'h':
                    suit = CardSuit::HEART;
                    break;
                case 'd':
                    suit = CardSuit::DIAMOND;
                    break;
                case 'c':
                    suit = CardSuit::CLUB;
                    break;
                case 's':
                    suit = CardSuit::SPADE;
                    break;
                default:
                    throw ParseException("Unknown suit");
            }
            card.suit = suit;
            card.rank = rank;
            answer.push_back(card);
        }
    } else {
        throw ParseException("Can't parse hand, cause of hand string length");
    }
    return answer;
}

std::vector<std::vector<Card>> GetHands(std::vector<std::string> lines, size_t start, size_t hand_size) {
    std::vector<std::vector<Card>> hands;
    for (size_t i = start; i < lines.size(); ++i) {
        std::vector<Card> hand = ParseHand(lines[i]);
        if (hand.size() != hand_size) {
            throw ParseException("Invalid holdem hand");
        }
        hands.push_back(hand);
    }
    return hands;
}

Game ParseLine(std::vector<std::string> parsed_line) {
    Game game;

    if (parsed_line.empty() or parsed_line.size() < 3) {
        throw ParseException("Nothing to parse");
    }

    // Checking game type
    if (parsed_line[0] == "texas-holdem") {
        game.type = GameType::HOLDEM;
        game.board = ParseHand(parsed_line[1]);
        if (game.board.size() != 5) {
            throw ParseException("Invalid holdem table");
        }
        game.players_cards = GetHands(parsed_line, 2, 2);
    } else if (parsed_line[0] == "omaha-holdem") {
        game.type = GameType::OMAHA;
        game.board = ParseHand(parsed_line[1]);
        if (game.board.size() != 5) {
            throw ParseException("Invalid omaha table");
        }
        game.players_cards = GetHands(parsed_line, 2, 4);
    } else if (parsed_line[0] == "five-card-draw") {
        game.type = GameType::FIVE_CARD_DRAW;
        game.players_cards = GetHands(parsed_line, 1, 5);
    } else {
        throw ParseException("Unknown game type");
    }

    return game;
}