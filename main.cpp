#include <iostream>
#include <string>

class Card {
public:
    enum Rank {
        TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
        JACK, QUEEN, KING, ACE
    };

    enum Suit {
        HEARTS, DIAMONDS, CLUBS, SPADES
    };

    Card(Rank r, Suit s) : rank(r), suit(s) {}

    std::string toString() const {
        static const std::string RANKS[] = {
            "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"
        };
        static const std::string SUITS[] = {
            "Hearts", "Diamonds", "Clubs", "Spades"
        };

        return RANKS[rank - 2] + " of " + SUITS[suit];
    }

    int getValue() const {
        if (rank >= TWO && rank <= TEN) return rank;
        if (rank >= JACK && rank <= KING) return 10;
        return 11; // ACE
    }

private:
    Rank rank;
    Suit suit;
};

int main() {
    std::cout << "Welcome to the game of 21!" << std::endl;
    return 0;
}
