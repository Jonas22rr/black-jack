#include <iostream>
#include <random>
#include <string>

// verwendet den namespace std
// ohne das müsste man immer std::cout, std::cin, ... schreiben
using namespace std;

// Klasse Service
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
    // ein boolischer Wert liefert true oder false zurück
    bool isHigherThan21(int cardSum) {
        if (cardSum > 21) return true;
        return false;
    }
};

class User {
    // private Methoden können nur innerhalb der Klasse aufgerufen werden
private:
    // Sercice ist das Objekt der Klasse Service
    Service service;
    int card1;
    int card2;
    int cardSum;
    double depositedMoney = 0;
    // public Methoden können von außen aufgerufen werden (z.B. in main oder anderen Klassen)
public:
    void setFirstTwoCards() {
        this->card1 = service.getRandomCard();
        this->card2 = service.getRandomCard();
    }

    int getCardSum() {
        return this->cardSum;
    }

    void setCardSumFromFirstTwoCards() {
        this->cardSum = this->card1 + this->card2;
    }

    void setCardSum(int card) {
        this->cardSum += card;
    }

    // Methode mit einem Rückgabewert vom Typ int
    int getCard1() {
        // this ist ein Zeiger auf das aktuelle Objekt
        // mit this greift man auf globale Variablen zu
        return this->card1;
    }

    void setCard1(int card) {
        this->card1 = card;
    }

    int getCard2() {
        return this->card2;
    }

    void setCard2(int card) {
        this->card2 = card;
    }

    int getChoosedCard() {
        int choosedCard;
        cout << "You got a Ass. Choose 1 or 11" << endl;
        cin >> choosedCard;
        if (choosedCard == 1) {
            return 1;
        } else if (choosedCard == 11) {
            return 11;
        } else {
            cout << "It must be a 1 or 11" << endl;
            return getChoosedCard();
        }
    }

    void setDeposite() {
        double deposite;
        cout << "How much money do they want to deposit?" << endl;
        cin >> deposite;
        this->depositedMoney = deposite;
    }

    double getDeposite() {
        return this->depositedMoney;
    }
};

class Dealer {
private:
    int cardSum = 0;
    int firstCard = 0;
    int secondCard = 0;
    Service service;
public:
    void setCardSum() {
        if (this->cardSum > 17) return;
        // shortcut cardSum = cardSum + service.getRandomCard();
        int card = service.getRandomCard();
        this->cardSum +=  card;
        cout << "Dealer draws a " << card << endl;
        cout << "Dealer has " << this->cardSum << " in sum"<< endl;
        if (this->cardSum < 17) {
            setCardSum();
        }
    }

    void setFirstTwoCards() {
        setFirstCard();
        setSecondCard();
    }

    void setFirstCard() {
        int card = service.getRandomCard();
        this->cardSum = card;
        this->firstCard = card;
    }

    void setSecondCard() {
        int card = service.getRandomCard();
        this->cardSum += card;
        this->secondCard = card;
    }

    int getCardSum() {
        return this->cardSum;
    }

    int getFirstCard() {
        return this->firstCard;
    }

    int getSecondCard() {
        return this->secondCard;
    }
};

class Game {
private:
    // objekt der Klasse User
    User user;
    Dealer dealer;
    Service service;
    int cardSum;
    char result;
    string winner;
public:
    // void == Methode -> liefert nichts zurück
    void start() {
        user.setDeposite();
        user.setFirstTwoCards();
        // endl ist ein Zeilenumbruch (wie \n)
        cout << "Your cards are: " << user.getCard1() << " and " << user.getCard2() << endl;
        cout << "In sum you have: " << user.getCard1() + user.getCard2() << endl;
        if (user.getCard1() == 11 ) {
            user.setCard1(user.getChoosedCard());
        } else if (user.getCard2() == 11) {
            user.setCard2(user.getChoosedCard());
        }
        user.setCardSumFromFirstTwoCards();

        if (service.isHigherThan21(cardSum)) {
            cout << "You lost!" << endl;
            return;
        }
        // TODO: dealer gets one card that will be print
        // TODO: get users ass card (if he wants 1 or 11)
        dealer.setFirstTwoCards();
        cout << "The dealers first Card is: " << dealer.getFirstCard() << endl;
        // folgendes ist eine recursive Funktion (Funktion / Method ist das selbe)
        checkUserWantNewCard();

        cout << "The dealers second Card is: " << dealer.getSecondCard() << endl;
        dealer.setCardSum();
        checkWinner();
        cout << "The winner is: " << winner << endl;
        if (winner == "You") {
            cout << "You won " << user.getDeposite() * 1.5 << "€" << endl;
        } else {
            cout << "You lost " << user.getDeposite() << "€" << endl;
        }
        if (playAgain()) {
            start();
        }
    }

    void checkUserWantNewCard() {
        cout << "Do you want a new card? (y/n)" << endl;
        cin >> result;
        if (result == 'y') {
            int card = service.getRandomCard();
            if (card == 11) {
                card = user.getChoosedCard();
            }
            cout << "Your new card is: " << card << endl;
            user.setCardSum(card);
            cout << "In sum you have: " << user.getCardSum() << endl;
            if (service.isHigherThan21(user.getCardSum())) {
                return;
            } if (user.getCardSum() == 21) {
                return;
            }
            checkUserWantNewCard();
        }
    }

    void checkWinner() {
        if (service.isHigherThan21(user.getCardSum())) {
            this->winner = "Dealer";
            return;
        } else if (cardSum == 21) {
            this->winner = "You";
            return;
        }
        cout << "Cards from Dealer are: " << dealer.getCardSum() << endl;
        if (service.isHigherThan21(dealer.getCardSum())) {
            this->winner = "You";
            return;
        } else if (user.getCardSum() > dealer.getCardSum()) {
            this->winner = "You";
            return ;
        } else if (user.getCardSum() == dealer.getCardSum()) {
            this->winner = "Nobody";
            return ;
        } else {
            this->winner = "Dealer";
            return ;
        }
    }

    bool playAgain() {
        cout << "Do you want to play again? (y/n)" << endl;
        cin >> result;
        if (result == 'y') {
            return true;
        }
        return false;
    }
};

int main() {
    Game game;
    string gameStart;
    cout << "Welcome to BlackJack!" << endl;
    cout << "Do you want to start the game? (y/n)" << endl;
    cin >> gameStart;
    if (gameStart == "y") {
        game.start();
    }
    return 0;
}

/*class Test {
private:
    int a;
public:
    int getA(int a) {
        this->a = a + 2;
        return a + 1;
    }
    void test1() {
        a = 1;
        int b = getA(a);
        a
    }
};*/

// int result = 0;
// -> cout ist die ausgabe von Hello, World!
// cout << "Hello, World!" << endl;
// -> cin ist die eingabe des Users (z.B. 1)
// cin >> result;
// -> Ausgabe von hello 1
// cout << "hello " << result << endl;
