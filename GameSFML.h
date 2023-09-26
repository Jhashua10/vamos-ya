#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "card.h"  
using namespace sf;
class GameSFML {
public:
    GameSFML() : window(sf::VideoMode(800, 600), "Juego de UNO con SFML"), currentPlayerIndex(0), gameDirection(true), validPlay(false) {
        // Cargar la fuente para el texto
        if (!font.loadFromFile("arial.ttf")) {
            // Manejar errores al cargar la fuente
            std::cerr << "Error al cargar la fuente." << std::endl;
        }

        // Configurar la posición de la mano del jugador en la ventana
        playerHandPosition = sf::Vector2f(100, 500);
        computerHandPosition = sf::Vector2f(100, 50);
    }

    void run() {
        // Bucle principal
        while (window.isOpen()) {
            // Manejar eventos de SFML
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                // Manejar eventos de clic del mouse
                if (event.type == sf::Event::MouseButtonReleased) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        handleMouseClick(event.mouseButton.x, event.mouseButton.y);
                    }
                }
            }

            // Actualizar la lógica del juego aquí
            // Por ejemplo, verificar si el jugador actual hizo una jugada válida

            // Limpiar la ventana
            window.clear();

            // Dibujar elementos en la ventana aquí
            drawHands();
            drawTopCard();
            drawPlayerTurnMessage();

            // Mostrar el contenido en la ventana
            window.display();
        }
    }

private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Vector2f playerHandPosition;
    sf::Vector2f computerHandPosition;
    int currentPlayerIndex;
    bool gameDirection;
    bool validPlay;

    std::vector<Card> playerHand;
    std::vector<Card> computerHand;
    Card topCard;

    void handleMouseClick(int x, int y) {
        // Implementa la lógica para manejar los clics del mouse aquí
        // Puedes detectar si el jugador hizo clic en una carta y luego intentar jugarla
    }

    void drawHands() {
        // Dibujar la mano del jugador
        float xOffset = 0;
        for (const Card& card : playerHand) {
            // Crea un objeto gráfico (sf::RectangleShape) para representar la carta
            sf::RectangleShape cardShape(sf::Vector2f(80, 120));
            cardShape.setFillColor(sf::Color::White);
            cardShape.setOutlineColor(sf::Color::Black);
            cardShape.setOutlineThickness(2);
            cardShape.setPosition(playerHandPosition.x + xOffset, playerHandPosition.y);

            // Dibuja el objeto gráfico en la ventana
            window.draw(cardShape);

            // Actualiza la posición x para la siguiente carta
            xOffset += 90;
        }

        // Dibujar la mano de la computadora (puedes hacerlo de manera similar)
    }

    void drawTopCard() {
        // Dibujar la carta superior en la mesa (similar a cómo dibujamos las cartas de la mano)
    }

    void drawPlayerTurnMessage() {
        // Dibujar un mensaje que indique de quién es el turno y si deben robar cartas, etc.
        sf::Text message;
        message.setFont(font);
        message.setCharacterSize(24);
        message.setFillColor(sf::Color::White);
        message.setPosition(20, 20);

        // Componer el mensaje según la lógica actual del juego
        std::string playerMessage = "Turno del Jugador ";
        playerMessage += (currentPlayerIndex == 0) ? "Humano" : "Computadora";
        if (!validPlay) {
            playerMessage += " (Debes robar una carta)";
        }

        message.setString(playerMessage);
        window.draw(message);
    }
};

int main() {
    GameSFML game;
    game.run();
    return 0;
}