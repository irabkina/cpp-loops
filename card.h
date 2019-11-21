#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <vector>
#include <unistd.h>
using namespace std;

std::random_device rd;

vector<string> suits = {"hearts","diamonds","clubs","spades"};
vector<string> ranks = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};

std::map<string, string> cardSymbols = {
    {"clubs", "♣"},
    {"diamonds", "♦"},
    {"hearts", "♥"},
    {"spades", "♠"}
};

class Card{
    public:
    string suit;
    string rank;
    int value;
    
    // Overload output stream operator
    friend ostream& operator << (ostream &os, const Card &c);
    
    friend bool operator == (const Card &c1, const Card &c2);
    friend bool operator != (const Card &c1, const Card &c2);
    friend bool operator > (const Card &c1, const Card &c2);
    friend bool operator < (const Card &c1, const Card &c2);
    
   
    // Constructor
    Card(string s, string r){
        suit = s;
        rank = r;
        value = distance(ranks.begin(), find(ranks.begin(), ranks.end(), r)) + 1;
    }
    
};

ostream& operator << (ostream &os, const Card &c){
    return os << cardSymbols[c.suit] << c.rank;
};

bool operator == (const Card &c1, const Card &c2){
    return c1.value == c2.value;
}

bool operator != (const Card &c1, const Card &c2){
    return !(c1 == c2);
}

bool operator > (const Card &c1, const Card &c2){
    return c1.value > c2.value;
}

bool operator < (const Card &c1, const Card &c2){
    return c1.value < c2.value;
}

// Create deck of cards
std::vector<Card> full_deck(){
    vector<Card> deck;
    for (int i=0; i < suits.size(); i++) {
        for (int j=0; j < ranks.size(); j++) {
            Card card = Card(suits[i], ranks[j]);
            deck.push_back( card );
        }
    }
    return deck;
}

std::vector<Card> deck_from_tuples(vector<tuple<string, string> > v){
    vector<Card> deck;
    for (int i = 0; i < v.size(); i++)  {
        Card card = Card(get<0>(v[i]), get<1>(v[i]));
        deck.push_back(card);
    }
    return deck;
}

/**
 * Shuffle the vector of Cards.
 *
 * @param deck Container whose values are shuffled.
 */
void shuffle_deck(vector<Card>& deck){
    auto rng = default_random_engine(rd());
    shuffle(begin(deck), end(deck), rng);
    
    return;
}


/**
 * Create small random vector of Cards.
 *
 * @param size Size of vector to return.
 */
std::vector<Card> small_random_deck (int size){
    vector<Card> deck = full_deck();
    shuffle_deck(deck);
    if (size>52) size=52;
    vector<Card> subdeck(deck.begin(), deck.begin()+size);
    return subdeck;
}

template<typename T>
void pop_front(std::vector<T>& vec)
{
    assert(!vec.empty());
    vec.erase(vec.begin());
}