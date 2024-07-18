#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
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

class Deck {
public:
    Deck() {
        for (int s = Card::HEARTS; s <= Card::SPADES; ++s) {
            for (int r = Card::TWO; r <= Card::ACE; ++r) {
                cards.emplace_back(static_cast<Card::Rank>(r), static_cast<Card::Suit>(s));
            }
        }
        currentCard = 0;
    }

    void shuffle() {
        static std::random_device rd;
        static std::mt19937 g(rd());
        std::shuffle(cards.begin(), cards.end(), g);
        currentCard = 0;
    }

    Card draw() {
        if (currentCard < cards.size()) {
            return cards[currentCard++];
        }
        throw std::out_of_range("No more cards in the deck");
    }

private:
    std::vector<Card> cards;    
    int currentCard;
};

int main() {
    std::cout << "Welcome to the game of 21!" << std::endl;
    return 0;
}
