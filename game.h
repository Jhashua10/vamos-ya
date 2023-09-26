#pragma once
#include <vector>
#include "Player.h"
#include "ComputerPlayer.h"
#include "card.h"
#include <random>
#include <iostream>
using namespace std;

class Game {
private:
    vector<Card> playedCards;
    vector<Player> humanPlayers;
    ComputerPlayer computerPlayer;
    vector<Card> unoDeck;
    Card topCard;
    int currentPlayerIndex;
    bool gameDirection;
    int numPlayers;
    bool validPlay;
    int nextPlayerIndex;
    int playerPoints;
    int computerPoints;
    int totalPoints;
    bool unoCalled;

public:
    Game(int numHumanPlayers, bool vsComputer) :
        currentPlayerIndex(0),
        gameDirection(true),
        numPlayers(numHumanPlayers + (vsComputer ? 1 : 0)),
        validPlay(false),
        nextPlayerIndex(0),
        unoCalled(false) {
        

        
        shuffleDeck(unoDeck);

        Card topCard = tomarCartaDelMazo(unoDeck);

        
        for (int i = 0; i < numHumanPlayers; ++i) {
            Player player("Jugador " + to_string(i + 1));
            for (int j = 0; j < 8; ++j) {
                Card card = tomarCartaDelMazo(unoDeck);
                player.addCard(card);
            }
            humanPlayers.push_back(player);
        }
    }

    Player& getCurrentPlayer() {
        return humanPlayers[currentPlayerIndex];
    }

    Card tomarCartaDelMazo(vector<Card>& unoDeck) {
        if (!unoDeck.empty()) {
            Card cartaTomada = unoDeck.back();
            unoDeck.pop_back();
            return cartaTomada;
        }
    }

    void skipNextPlayerTurn() {
        int nextPlayerIndex = (currentPlayerIndex + (gameDirection ? 1 : -1)) % numPlayers;
        if (nextPlayerIndex < 0) {
            nextPlayerIndex += numPlayers;
        }
    }

    void reverseGameDirection() {
        gameDirection = !gameDirection;
    }

    void shuffleDeck(vector<Card>& deck) {
        random_device rd;
        mt19937 rng(rd());
        shuffle(deck.begin(), deck.end(), rng);
    }

    Card drawCardFromDeck() {
        if (!unoDeck.empty()) {
            Card drawnCard = unoDeck.back();
            unoDeck.pop_back();
            return drawnCard;
        }
        else {
            if (playedCards.size() > 1) {
                Card lastPlayedCard = playedCards.back();
                playedCards.pop_back();

                shuffleDeck(playedCards);
                unoDeck.insert(unoDeck.end(), playedCards.begin(), playedCards.end());

                playedCards.clear();
                playedCards.push_back(lastPlayedCard);

                Card drawnCard = unoDeck.back();
                unoDeck.pop_back();
                return drawnCard;
            }
            else {
                return Card();
            }
        }
    }

    int getNumberOfPlayers() const {
        return humanPlayers.size() + 1; // +1 para incluir al jugador de la computadora
    }

    vector<Card>& getUnoDeck() {
        return unoDeck;
    }

    void nextPlayerDrawTwoCards() {
        int nextPlayerIndex = (currentPlayerIndex + (gameDirection ? 1 : -1)) % numPlayers;
        if (nextPlayerIndex < 0) {
            nextPlayerIndex += numPlayers;
        }

        Player& nextPlayer = humanPlayers[nextPlayerIndex];
        for (int i = 0; i < 2; ++i) {
            Card drawnCard = drawCardFromDeck();
            nextPlayer.addCard(drawnCard);
        }
    }

    void nextPlayerDrawFourCards() {
        int nextPlayerIndex = (currentPlayerIndex + (gameDirection ? 1 : -1)) % numPlayers;
        if (nextPlayerIndex < 0) {
            nextPlayerIndex += numPlayers;
        }

        Player& nextPlayer = humanPlayers[nextPlayerIndex];
        for (int i = 0; i < 4; ++i) {
            Card drawnCard = drawCardFromDeck();
            nextPlayer.addCard(drawnCard);
        }
    }

    void applyRules(const Card& card) {
        switch (card.getType()) {
        case Card::NUMBER:
            break;
        case Card::SKIP:
            skipNextPlayerTurn();
            break;
        case Card::REVERSE:
            reverseGameDirection();
            break;
        case Card::DRAW_TWO:
            nextPlayerDrawTwoCards();
            skipNextPlayerTurn();
            break;
        case Card::WILD:
            break;
        case Card::WILD_DRAW_FOUR:
            nextPlayerDrawFourCards();
            skipNextPlayerTurn();
            break;
        default:
            break;
        }
    }

    bool isGameOver() const {
        for (const Player& player : humanPlayers) {
            if (player.hasWon()) {
                return false;
            }
        }

        return false;
    }

    void moveToNextPlayer() {
        if (gameDirection) {
            currentPlayerIndex = (currentPlayerIndex + 1) % numPlayers;
        }
        else {
            currentPlayerIndex = (currentPlayerIndex - 1 + numPlayers) % numPlayers;
        }
    }

    void updatePointsAtEndOfRound(const Player& winner) {
        int points = 0;
        for (const Player& player : humanPlayers) {
            if (&player != &winner) {
                const vector<Card>& hand = player.getHand();
                for (const Card& card : hand) {
                    points += card.number;
                }
            }
        }

        totalPoints += points;
    }

    vector<Card> dealCards(vector<Card>& deck, int numCards) {
        vector<Card> hand;
        for (int i = 0; i < numCards; ++i) {
            hand.push_back(deck.back());
            deck.pop_back();
        }
        return hand;
    }

    void setTopCard(const Card& card) {
        topCard = card;
    }

    const vector<Card>& getUnodeck() const {
        return unoDeck;
    }

    void computerPlayCard() {
        Card cardToPlay = computerPlayer.playCard(topCard);

        if (cardToPlay.isValid(topCard)) {
            if (cardToPlay.canPlayOn(topCard)) {
                applyRules(cardToPlay);

                playedCards.push_back(cardToPlay);

                topCard = cardToPlay;

                computerPlayer.removeCard(cardToPlay);
            }
        }
        else {
            Card drawnCard = drawCardFromDeck();
            computerPlayer.addCard(drawnCard);
        }
    }

    void playCard(const Player& player, const Card& card) {
        if (card.canPlayOn(topCard)) {
            Card SelectedCard = card;
            applyRules(SelectedCard);
        }
        else {
            
        }
    }

    bool checkWin(Player& currentPlayer) {
        return currentPlayer.hasWon();
    }

    const Player* getWinner(Player& currentPlayer) const {
        const Player* winningPlayer = nullptr;
        int minCards = numeric_limits<int>::max();

        if (currentPlayer.getHandSize() == 0) {
            return &currentPlayer;
        }

        return winningPlayer;
    }

    Card getTopCard() const {
        return topCard;
    }

    const vector<Card>& getUnoDeck() const {
        return unoDeck;
    }
};