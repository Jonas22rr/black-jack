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
    // public Methoden können von außen aufgerufen werden (z.B. in main oder anderen Klassen)
public:
    // User ist der Konstruktor der Klasse User
    // Ein Konstruktor wird immer aufgerufen, wenn ein Objekt einer Klasse erstellt wird
    User() {
        // mit dem Punkt "." kann auf die Methoden der Klasse zugegriffen werden
        card1 = service.getRandomCard();
        card2 = service.getRandomCard();
    }
    // Methode mit einem Rückgabewert vom Typ int
    int getCard1() {
        // this ist ein Zeiger auf das aktuelle Objekt
        // mit this greift man auf globale Variablen zu
        return this->card1;
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
    void setCardSum() {
        // shortcut cardSum = cardSum + service.getRandomCard();
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
    // objekt der Klasse User
    User user;
    Dealer dealer;
    Service service;
    int cardSum;
    char result;
public:
    // void == Methode -> liefert nichts zurück
    void start() {
        // endl ist ein Zeilenumbruch (wie \n)
        cout << "Your cards are: " << user.getCard1() << " and " << user.getCard2() << endl;
        cardSum = user.getCard1() + user.getCard2();
        cout << "In sum you have: " << cardSum << endl;
        if (service.isHigherThan21(cardSum)) {
            cout << "You lost!" << endl;
            return;
        }
        // TODO: dealer gets one card that will be print
        // TODO: get users ass card (if he wants 1 or 11)
        // folgendes ist eine recursive Funktion (Funktion / Method ist das selbe)
        checkUserWantNewCard();

        // TODO: dealer gets cards until he has 17 or more
        dealer.setCardSum();
        checkWinner();
        if (playAgain()) {
            start();
        }
    }

    void checkUserWantNewCard() {
        cout << "Do you want a new card? (y/n)" << endl;
        cin >> result;

        if (result == 'y') {
            int card = service.getRandomCard();
            cout << "Your new card is: " << card << endl;
            // shortcut für cardSum = cardSum + card
            cardSum += card;
            cout << "In sum you have: " << cardSum << endl;
            if (service.isHigherThan21(cardSum)) {
                return;
            } if (cardSum == 21) {
                return;
            }
            checkUserWantNewCard();
        }
    }

    void checkWinner() {
        if (service.isHigherThan21(cardSum)) {
            cout << "You lost!" << endl;
            return;
        } else if (cardSum == 21) {
            cout << "You won!" << endl;
            return;
        }
        cout << "Cards from Dealer are: " << dealer.getCardSum() << endl;
        if (service.isHigherThan21(dealer.getCardSum())) {
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
    string result;
    cout << "Welcome to BlackJack!" << endl;
    cout << "Do you want to start the game? (y/n)" << endl;
    cin >> result;
    if (result == "y") {
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
