#pragma once
#include "funciones.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace std;
class Card {
public:




    enum Color { BLUE, RED, GREEN, YELLOW,NONE };
    enum Type { NUMBER, SKIP, REVERSE, DRAW_TWO, WILD, WILD_DRAW_FOUR,VACIO };
    
    Type type;
    Color color;
    int number;
    
    Card() {
        
    }
    Card(Type type, Color color, int number) : type(type), color(color), number(number) {}

    
    Card(Type type) : type(type), color(NONE), number(0) {}
    

    
    bool isWildCard() const {
        return (type == WILD || type == WILD_DRAW_FOUR);
    }

    
    bool canPlayOn(const Card& otherCard) const {
        if (type == WILD || type == WILD_DRAW_FOUR) {
            
            return true;
        }
        return (color == otherCard.color || type == otherCard.type || number == otherCard.number);
    }
    Color getColor() const {
        return color;
    }
    Type getType() const {
        return type;
    }

    int getNumber() const {

        return number;
    }
    
    string toString() const {
        string typeStr;
        switch (type) {
        case NUMBER: typeStr = "Number"; break;
        case SKIP: typeStr = "Skip"; break;
        case REVERSE: typeStr = "Reverse"; break;
        case DRAW_TWO: typeStr = "Draw Two"; break;
        case WILD: typeStr = "Wild"; break;
        case WILD_DRAW_FOUR: typeStr = "Wild Draw Four"; break;
        default: typeStr = "Unknown"; break;
        }

        string colorStr;
        switch (color) {
        case BLUE: colorStr = "Blue"; break;
        case RED: colorStr = "Red"; break;
        case GREEN: colorStr = "Green"; break;
        case YELLOW: colorStr = "Yellow"; break;
        default: colorStr = "None"; break;
        }

        if (type == NUMBER) {
            return colorStr + " " + to_string(number);
        }
        else {
            return colorStr + " " + typeStr;
        }
    }
    Card findTopCard(const vector<Card>& cardDeck) {
        if (!cardDeck.empty()) {
            return cardDeck.back(); 
        }
        else {
            
            return (Card::Color::NONE, 0, Card::Type::VACIO);
        }
    }
    bool isValid(const Card& topCard) const {
        
        if (color == topCard.color || number == topCard.number) {
            return true;
        }
        
        if (type == WILD || type == WILD_DRAW_FOUR) {
            return true;
        }
        

        return false; 
    }
   
    bool operator==(const Card& other) const {
        return (type == other.type && color == other.color && number == other.number);
    }
   
    
   

};