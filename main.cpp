#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include <array>

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
        static const std::array<std::string, 13> RANKS = {
            "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"
        };
        static const std::array<std::string, 4> SUITS = {
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

class Player {
public:
    void addCard(const Card& card) {
        hand.push_back(card);
    }

    int getTotal() const {
        int total = 0;
        int aces = 0;
        for (const auto& card : hand) {
            total += card.getValue();
            if (card.getValue() == 11) ++aces;
        }
        while (total > 21 && aces > 0) {
            total -= 10;
            --aces;
        }
        return total;
    }

    bool isBusted() const {
        return getTotal() > 21;
    }

    void clearHand() {
        hand.clear();
    }

    const std::vector<Card>& getHand() const {
        return hand;
    }

private:
    std::vector<Card> hand;
};

class Dealer : public Player {
public:
    void play(Deck& deck) {
        while (getTotal() < 17) {
            addCard(deck.draw());
        }
    }
};

void playGame() {
    Deck deck;
    deck.shuffle();

    Player player;
    Dealer dealer;

    player.addCard(deck.draw());
    player.addCard(deck.draw());

    dealer.addCard(deck.draw());
    dealer.addCard(deck.draw());

    std::cout << "Dealer's face-up card: " << dealer.getHand()[0].toString() << std::endl;

    bool playerTurn = true;
    while (playerTurn) {
        std::cout << "Your total is: " << player.getTotal() << std::endl;
        if (player.isBusted()) {
            std::cout << "You busted! Dealer wins." << std::endl;
            return;
        }

        std::cout << "Do you want to hit or stand? (h/s): ";
        char choice;
        std::cin >> choice;

        if (choice == 'h') {
            player.addCard(deck.draw());
        } else {
            playerTurn = false;
        }
    }

    std::cout << "Dealer's turn." << std::endl;
    dealer.play(deck);

    std::cout << "Dealer's total is: " << dealer.getTotal() << std::endl;
    if (dealer.isBusted()) {
        std::cout << "Dealer busted! You win." << std::endl;
        return;
    }

    if (player.getTotal() > dealer.getTotal()) {
        std::cout << "You win!" << std::endl;
    } else {
        std::cout << "Dealer wins." << std::endl;
    }
}

int main() {
    std::cout << "Welcome to the game of 21!" << std::endl;
    char playAgain = 'y';
    while (playAgain == 'y') {
        playGame();
        std::cout << "Do you want to play again? (y/n): ";
        std::cin >> playAgain;
    }
    return 0;
}
                    