#include <iostream>
#include <random>
#include <string>

using namespace std;

class Service {
public:
    int getRandomNumber() {
        random_device dev;
        mt19937 rng(dev());
        uniform_int_distribution<mt19937::result_type> dist6(2,14);
        return dist6(rng);
    }

    int getRandomCard() {
        int card = getRandomNumber();
        if (card > 11) card = 10;
        return card;
    }

    bool isHigherthen21(int cardSum) {
        if (cardSum > 21) return true;
        return false;
    }

};

class User {
private:
    Service service;
    int card1;
    int card2;
public:
    User() {
        card1 = service.getRandomCard();
        card2 = service.getRandomCard();
    }

    int getCard1() {
        return this->card1 ;
    }

    int getCard2() {
        return this->card2;
    }

    int getNewCard() {
        return service.getRandomCard();
    }
};

class Dealer {
private:
    int cardSum = 0;
    Service service;
public:
    int setCardSum() {
        this->cardSum +=  service.getRandomCard();
        if (this->cardSum < 17) {
            setCardSum();
        }
    }

    int getCardSum() {
        return this->cardSum;
    }
};

class Game {
private:
    User user;
    Dealer dealer;
    Service service;
    int cardSum;
    char result;
public:
    void start() {
        cout << "Your cards are: " << user.getCard1() << " and " << user.getCard2() << endl;
        cardSum = user.getCard1() + user.getCard2();
        cout << "In sum you have: " << cardSum << endl;
        if (service.isHigherthen21(cardSum)) {
            cout << "You lost!" << endl;
            return;
        }
        // TODO: dealer gets one card that will be print
        // TODO: get users ass card (if he wants 1 or 11)
        checkUserWantNewCard();

        // TODO: dealer gets cards until he has 17 or more
        dealer.setCardSum();
        checkWinner();
    }

    void checkUserWantNewCard() {
        cout << "Do you want a new card? (y/n)" << endl;
        cin >> result;

        if (result == 'y') {
            int card = service.getRandomCard();
            cout << "Your new card is: " << card << endl;
            cardSum += card;
            cout << "In sum you have: " << cardSum << endl;
            if (service.isHigherthen21(cardSum)) {
                return;
            } if (cardSum == 21) {
                checkWinner();
            }
            checkUserWantNewCard();
        }
    }

    void checkWinner() {
        if (service.isHigherthen21(cardSum)) {
            cout << "You lost!" << endl;
            return;
        } else if (cardSum == 21) {
            cout << "You won!" << endl;
            return;
        }
        cout << "Cards from Dealer are: " << dealer.getCardSum() << endl;
        if (service.isHigherthen21(dealer.getCardSum())) {
            cout << "You win!" << endl;
            return;
        } else if (cardSum > dealer.getCardSum()) {
            cout << "You won!" << endl;
            return ;
        } else if (cardSum == dealer.getCardSum()) {
            cout << "tie!" << endl;
            return ;
        } else {
            cout << "You lost!" << endl;
            return ;
        }
    }
};

int main() {
    Game game;
    game.start();
    return 0;
}
