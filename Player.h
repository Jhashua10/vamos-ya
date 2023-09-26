#pragma once
#include <vector>
#include "card.h" 

class Player {
public:
    vector<Card> hand;
    vector<Card>::iterator handIterator; 
    string name;

  
    

    Player() {}

    Player(const string& playerName) : name(playerName) {
        handIterator = hand.begin(); 
    }
    
    const vector<Card>& getHand() const {
        return hand;
    }
    bool hasOnlyOneCard() const {
        return hand.size() == 1;
    }
    void removeCard(const Card& cardToRemove) {

        auto it = find(hand.begin(), hand.end(), cardToRemove);


        if (it != hand.end()) {

            hand.erase(it);
        }
    }
    Player& getNextPlayer(std::vector<Player>& players) {
        
        auto it = find(players.begin(), players.end(), *this);

        if (it != players.end()) {
            
            ++it;
            if (it == players.end()) {
                
                it = players.begin();
            }

            return *it;
        }
        else {
            
            return *this;
        }
    }
   
    bool playCard(const Card& cardToPlay) {
        
        for (vector<Card>::iterator it = hand.begin(); it != hand.end(); ++it) {
            if (it->canPlayOn(cardToPlay)) {
                
                hand.erase(it);
                handIterator = hand.begin(); 
                return true; 
            }
        }
        return false; 
    }
    
    void drawCard( vector<Card>& unoDeck) {
        
        if (!unoDeck.empty()) {
            
            hand.push_back(unoDeck.back());

            
            unoDeck.pop_back();
        }
    }

   






    void addCard(const Card& card) {
        hand.push_back(card);
    }
    void nextCard() {
        if (handIterator != hand.end()) {
            ++handIterator;
        }
    }
    string getName() const {
        return name;
    }
   

    int getHandSize() const {
        return hand.size();
    }
    
    void prevCard() {
        if (handIterator != hand.begin()) {
            --handIterator;
        }
    }
    
    bool hasWon() const {
        return hand.empty(); 
    }
};