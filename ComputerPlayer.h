#pragma once


#include <vector>



#include "card.h" 
using namespace std; 





class ComputerPlayer {
    
private:
    bool unoButtonPressed;  



public:
    vector<Card> hand;

    // Constructor
    ComputerPlayer() : unoButtonPressed(false) {}

    // Método para que la computadora juegue una carta en su turno
    Card playCard(const Card& topCard) {
        // Obtener una lista de cartas jugables
        std::vector<Card> playableCards;
        for (const Card& card : hand) {
            if (card.canPlayOn(topCard)) {
                playableCards.push_back(card);
            }
        }

        if (!playableCards.empty()) {
            // La computadora selecciona una carta jugable (aquí se puede implementar una estrategia más avanzada)
            int randomIndex = rand() % playableCards.size();
            Card selectedCard = playableCards[randomIndex];
            // La carta seleccionada se quita de la mano de la computadora
            hand.erase(hand.begin() + randomIndex);
            return selectedCard;
        }
        else {
            // Si no hay cartas jugables, la computadora pasa su turno
            return Card(); // Retorna una carta "vacia" como señal de pasar el turno
        }
    }
    void addCard(const Card& card) {
        hand.push_back(card);
    }


    // Método para recibir una carta en su turno
    void receiveCards(const std::vector<Card>& cards) {
        for (const Card& card : cards) {
            hand.push_back(card);
        }
    }
    void removeCard(const Card& cardToRemove) {
        // Buscar la carta en la mano del jugador de la computadora y eliminarla
        for (auto it = hand.begin(); it != hand.end(); ++it) {
            if (*it == cardToRemove) {
                hand.erase(it);
                break; // Se encontró y eliminó la carta, podemos salir del bucle
            }
        }
    }
    bool decideCallUNO() const {
    // Verificar si el jugador tiene solo una carta en su mano
    if (hand.size() == 1) {
        // Generar un número aleatorio entre 0 y 1 (0 o 1)
        int randomNumber = rand() % 2;
        
        // La computadora decide llamar "UNO" con una probabilidad del 50%
        return (randomNumber == 0);
    }
    
    // Si no tiene una sola carta en su mano, la computadora no llama "UNO"
    return false;
}
    bool checkUNO() const {
        if (hand.size() == 1 && unoButtonPressed) {
            return true;
        }
        return false;
    }
    bool hasWon() const {
        return hand.empty();
    }
};
    

    