#pragma once
#include <SFML/Graphics.hpp>
#include "card.h"
#include <string>
#include "game.h"
#include "ComputerPlayer.h"
#include "Player.h"
using namespace sf;




RenderWindow UNO (VideoMode(1380, 720), "UNO!");
Texture backgroundFile, buttonFile, cardFile;
Texture cardOutlineFile, cardChangeColorFile, cardNoTurnFile, cardReverseFile;
Sprite background, button, card, cardOutline;
Font letterFont;
Text unoText, takeCard;
Vector2i mousePos;
Event gameLoop;

Card selectedcard;
bool vsPc=false;
int numHumPlayers=2;
bool verificar = false;
Player player1 = Player("Jugador 1");
Player player2 = Player("Jugador 2");

Card globalCard;
int delay = 0;
int turn;

int iterCard;
void loopRefresh()
{

	while (UNO.pollEvent(gameLoop)) {
		if (gameLoop.type == Event::Closed) {
			UNO.close();
		}
	}
}
int getPlayerCardSelection(const Player& player) {

	Vector2i mousePos = Mouse::getPosition(UNO);


	float x = 50.0f;
	float y = 500.0f;


	float cardWidth = 100.0f;
	float cardHeight = 150.0f;


	for (size_t i = 0; i < player.getHand().size(); ++i) {

		if (mousePos.x >= x && mousePos.x <= x + cardWidth &&
			mousePos.y >= y && mousePos.y <= y + cardHeight) {
			return static_cast<int>(i);
		}


		x += 30.0f;
	}

	return -1;
}
void drawCardL(const Card& card, float x, float y) {
	
	Texture cardTexture;
	cardTexture.loadFromFile("Texturas/UnoCard.png");

	
	Sprite cardSprite(cardTexture);

	
	cardSprite.setPosition(x, y);

	
	UNO.draw(cardSprite);
}
int getPlayerCardSelection(const Player& player, RenderWindow& window) {
	Vector2i mousePos = Mouse::getPosition(window);


	const vector<Card>& hand = player.getHand();


	float x = 50.0f;
	float y = 500.0f;


	const float cardWidth = 100.0f;
	const float cardHeight = 150.0f;


	for (size_t i = 0; i < hand.size(); ++i) {

		if (mousePos.x >= x && mousePos.x <= x + cardWidth &&
			mousePos.y >= y && mousePos.y <= y + cardHeight) {
			return static_cast<int>(i);
		}


		x += 30.0f;
	}


	return -1;
}
bool mouseDetect(Vector2i mousePos, Vector2f topPos, Vector2f bottomPos)
{

	mousePos = Mouse::getPosition(UNO);

	bool isInTop = false;
	bool isInBottom = false;

	if ((mousePos.x > topPos.x) && (mousePos.x < topPos.y)) {
		isInTop = true;
	}
	else {
		isInTop = false;
	}

	if ((mousePos.y > bottomPos.x) && (mousePos.y < bottomPos.y)) {
		isInBottom = true;
	}
	else {
		isInBottom = false;
	}

	if (isInTop && isInBottom) {
		return true;
	}
	else {
		return false;
	}
}
void refreshWindow(const Player& currentPlayer) {

	UNO.clear();


	UNO.draw(background);
	UNO.draw(button);
	UNO.draw(unoText);


	takeCard.setRotation(310);
	takeCard.setPosition(59, 380);
	takeCard.setFillColor(Color::Black);
	UNO.draw(takeCard);
	takeCard.setPosition(62, 379);
	takeCard.setFillColor(Color(255, 218, 0, 255));
	UNO.draw(takeCard);


	float x = 50.0f;
	float y = 500.0f;

	for (const Card& card : currentPlayer.getHand()) {
		drawCardL(card, x, y);
		x += 30.0f;
	}


	drawCardL(globalCard, 600, 300);


	UNO.display();
}


int getPlayerCardSelection(Player& player) {

	Vector2i mousePos = Mouse::getPosition(UNO);


	float x = 50.0f;
	float y = 500.0f;


	float cardWidth = 100.0f;
	float cardHeight = 150.0f;


	for (size_t i = 0; i < player.getHand().size(); ++i) {

		if (mousePos.x >= x && mousePos.x <= x + cardWidth &&
			mousePos.y >= y && mousePos.y <= y + cardHeight) {
			return static_cast<int>(i);
		}


		x += 30.0f;
	}

	return -1;
}
void showWinner(RenderWindow& window, const Game& game, Player& currentPlayer) {



	const Player* winner = game.getWinner(currentPlayer);


	window.clear();


	Font font;
	font.loadFromFile("letras/l_u.ttf");

	Text resultText;
	if (winner) {
		resultText.setString("¡" + winner->getName() + " ha ganado!");
		resultText.setFillColor(Color::Green);
	}
	else {
		resultText.setString("¡Ha habido un empate!");
		resultText.setFillColor(Color::Blue);
	}
	resultText.setFont(font);
	resultText.setCharacterSize(40);


	FloatRect textBounds = resultText.getLocalBounds();
	resultText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
	resultText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);


	window.draw(resultText);


	window.display();


	sleep(seconds(5));
}

void displayPlayerHand(Player& player, RenderWindow& window) {
	
	window.clear();

	
	const vector<Card>& hand = player.getHand();

	
	float x = 50.0f;
	float y = 500.0f;

	
	const float cardWidth = 100.0f;
	const float cardHeight = 150.0f;

	
	for (const Card& card : hand) {
		
		Sprite cardSprite;
		Texture cardTexture;

		
		string texturePath = "Texturas/";
		switch (card.getColor()) {
		case Card::Color::RED:
			texturePath += "Red";
			break;
		case Card::Color::BLUE:
			texturePath += "Blue";
			break;
		case Card::Color::GREEN:
			texturePath += "Green";
			break;
		case Card::Color::YELLOW:
			texturePath += "Yellow";
			break;
		default:
			texturePath += "Special"; 
			break;
		}

		texturePath += to_string(card.getNumber()) + ".png";

		
		if (!cardTexture.loadFromFile(texturePath)) {
			cerr << "Error al cargar la textura de la carta." << endl;
			
		}

		
		cardSprite.setTexture(cardTexture);
		cardSprite.setPosition(x, y);

		
		window.draw(cardSprite);

		
		x += 30.0f; 
	}

	
	window.display();
}
Card tomarCartaDelMazo(vector<Card>& unoDeck) {
	if (!unoDeck.empty()) {

		Card cartaTomada = unoDeck.back();


		unoDeck.pop_back();

		return cartaTomada;
	}
}

void initializeGame() {



	if (!backgroundFile.loadFromFile("Texturas/Background.jpg")) {
		cerr << "Error al cargar la textura de fondo." << endl;
		return;
	}

	if (!buttonFile.loadFromFile("Texturas/Button.png")) {
		cerr << "Error al cargar la textura del botón." << endl;
		return;
	}

	if (!letterFont.loadFromFile("letras/l_u.ttf")) {
		cerr << "Error al cargar la fuente de letras." << endl;
		return;
	}

	if (!cardChangeColorFile.loadFromFile("Texturas/UnocardChangeColor.png")) {
		cerr << "Error al cargar la textura de carta de cambio de color." << endl;
		return;
	}

	if (!cardNoTurnFile.loadFromFile("Texturas/UnocardNoTurn.png")) {
		cerr << "Error al cargar la textura de carta de no girar." << endl;
		return;
	}

	if (!cardReverseFile.loadFromFile("Texturas/UnocardReverse.png")) {
		cerr << "Error al cargar la textura de carta de reversa." << endl;
		return;
	}

	if (!cardFile.loadFromFile("Texturas/UnoCard.png")) {
		cerr << "Error al cargar la textura de las cartas de juego." << endl;
		return;
	}

	if (!cardOutlineFile.loadFromFile("Texturas/UnocardOutline.png")) {
		cerr << "Error al cargar la textura del contorno de la carta." << endl;
		return;
	}
	if (!letterFont.loadFromFile("letras/l_u.ttf")) {
		cerr << "Error al cargar la fuente de letras." << endl;
		return;
	}


	background.setTexture(backgroundFile);
	button.setTexture(buttonFile);



	UNO.setFramerateLimit(24);

	vector<Card> deck;


	for (int color = Card::BLUE; color <= Card::YELLOW; ++color) {
		for (int number = 0; number <= 9; ++number) {
			deck.push_back(Card(Card::NUMBER, static_cast<Card::Color>(color), number));
		}
	}


	for (int color = Card::BLUE; color <= Card::YELLOW; ++color) {
		for (int i = 0; i < 2; ++i) {
			deck.push_back(Card(Card::SKIP, static_cast<Card::Color>(color), 0));
			deck.push_back(Card(Card::REVERSE, static_cast<Card::Color>(color), 0));
			deck.push_back(Card(Card::DRAW_TWO, static_cast<Card::Color>(color), 0));
		}
	}


	for (int i = 0; i < 4; ++i) {
		deck.push_back(Card(Card::WILD));
		deck.push_back(Card(Card::WILD_DRAW_FOUR));
	}





	std::random_device rd;
	std::mt19937 gen(rd());
	std::shuffle(deck.begin(), deck.end(), gen);


	for (int i = 0; i < numHumPlayers; i++) {
		Player* currentPlayer;

		for (int j = 0; j < 8; j++) {
			Player* currentPlayer = &player1;
			currentPlayer->addCard(tomarCartaDelMazo(deck));
		}
	}



	Card globalCard = tomarCartaDelMazo(deck);
}

void startGame(int numHumanPlayers, bool vsComputer) {
    Game game(numHumanPlayers, vsComputer);
    initializeGame(); 

	while (!game.isGameOver()) {
		Player& currentPlayer = game.getCurrentPlayer();

		
		displayPlayerHand(currentPlayer, UNO);

		
		bool hasPlayableCards = false;
		for (const Card& card : currentPlayer.getHand()) {
			if (card.canPlayOn(game.getTopCard())) {
				hasPlayableCards = true;
				break;
			}
		}

		if (!hasPlayableCards) {
			currentPlayer.drawCard(game.getUnoDeck());
			refreshWindow(currentPlayer);
		}
		else {
			int selectedCardIndex = getPlayerCardSelection(currentPlayer, UNO);

			if (selectedCardIndex != -1) {
				const Card& selectedCard = currentPlayer.getHand()[selectedCardIndex];
				if (selectedCard.canPlayOn(game.getTopCard())) {
					game.applyRules(selectedCard);
					currentPlayer.playCard(selectedCard);
					game.setTopCard(selectedCard);
				}
				else {
					
				}
			}

			game.moveToNextPlayer();

			if (game.isGameOver()) {
				showWinner(UNO, game, currentPlayer);
				UNO.close();
            }
        }
    }
}




void displayTopCard(const Card& topCard, RenderWindow& window) {
	
	Texture cardTexture;

	
	string texturePath = "Texturas/";

	switch (topCard.getColor()) {
	case Card::Color::RED:
		texturePath += "Red";
		break;
	case Card::Color::BLUE:
		texturePath += "Blue";
		break;
	case Card::Color::GREEN:
		texturePath += "Green";
		break;
	case Card::Color::YELLOW:
		texturePath += "Yellow";
		break;
	default:
		
		texturePath += "Special"; 
		break;
	}

	
	texturePath += std::to_string(topCard.getNumber()) + ".png";

	
	if (!cardTexture.loadFromFile(texturePath)) {
		
		cerr << "Error al cargar la textura de la carta superior." << endl;
		return;
	}

	
	Sprite cardSprite(cardTexture);


	cardSprite.setPosition(200.0f, 200.0f);

	
	window.draw(cardSprite);
}


void displayInvalidCardMessage(RenderWindow& window) {

	window.clear();


	Font font;
	font.loadFromFile("letras/l_u.ttf");

	Text message("¡Carta no válida!", font, 40);
	message.setFillColor(Color::Red);


	FloatRect textBounds = message.getLocalBounds();
	message.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
	message.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);


	window.draw(message);


	window.display();


	sleep(seconds(2));
}

bool detectSelectedCard(const Player& player, RenderWindow& window, Card& selectedCard) {
	
	Vector2i mousePos = Mouse::getPosition(window);

	
	const vector<Card>& hand = player.getHand();

	
	float x = 50.0f;
	float y = 500.0f;

	
	float cardWidth = 100.0f;
	float cardHeight = 150.0f;

	
	for (size_t i = 0; i < hand.size(); ++i) {
		
		if (mousePos.x >= x && mousePos.x <= x + cardWidth &&
			mousePos.y >= y && mousePos.y <= y + cardHeight) {
			selectedCard = hand[i]; 
			return true; 
		}

	
		x += 30.0f;
	}

	return false; 
}






void startMenu()
{

	while (UNO.isOpen()) {

		loopRefresh();

		backgroundFile.loadFromFile("Texturas/Background.jpg");
		buttonFile.loadFromFile("Texturas/Button.png");
		letterFont.loadFromFile("letras/l_u.ttf");
		cardChangeColorFile.loadFromFile("Texturas/UnocardChangeColor.png");
		cardNoTurnFile.loadFromFile("Texturas/UnocardNoTurn.png");
		cardReverseFile.loadFromFile("Texturas/UnocardReverse.png");
		background.setTexture(backgroundFile);
		button.setTexture(buttonFile);

		cardFile.loadFromFile("Texturas/UnoCard.png");
		cardOutlineFile.loadFromFile("Texturas/UnocardOutline.png");
		card.setTexture(cardFile);
		cardOutline.setTexture(cardOutlineFile);

		Text menuText("¡JUEGA UNO EN C++!", letterFont, 90), buttonText("Empezar", letterFont, 60);

		button.setPosition(460, 280);
		menuText.setPosition(240, 70);
		buttonText.setPosition(530, 315);

		menuText.setFillColor(Color::Black);
		buttonText.setFillColor(Color::Black);

			UNO.setFramerateLimit(24);

		bool isInTop = false;
		bool isInBottom = false;
		bool isButtonPressed = false;

		while (isButtonPressed == false) {

			loopRefresh();

			UNO.draw(background);
			UNO.draw(menuText);
			UNO.draw(button);
			UNO.draw(buttonText);
			UNO.display();

			Vector2f top(460, 820), bottom(280, 440);

			if (mouseDetect(mousePos, top, bottom)) {
				buttonText.setFillColor(Color::White);
			}
			else {
				buttonText.setFillColor(Color::Black);
			}

			if (Mouse::isButtonPressed(Mouse::Left) && mouseDetect(mousePos, top, bottom)) {
				while (isButtonPressed == false) {
					if (Mouse::isButtonPressed(Mouse::Left) != true) {
						isButtonPressed = true;
					}
					loopRefresh();
				}
			}
		}

		startGame(numHumPlayers,vsPc);
		system("pause");
	}






}

void printCard(const Card& card, Sprite cardSprite, Sprite cardOutline, int x, int y) {
	
	Texture cardTexture;
	cardTexture.loadFromFile("Texturas/UnoCard.png");

	
	cardSprite.setTexture(cardTexture);
	cardSprite.setPosition(static_cast<float>(x), static_cast<float>(y));

	
	UNO.draw(cardSprite);

	
	UNO.draw(cardOutline);
}

bool isClickingCard(int xPosCard, int yPosCard) {

	double minX = xPosCard;
	double maxX = xPosCard + (400 * 0.2);
	double minY = yPosCard;
	double maxY = minY + (600 * 0.2);

	Vector2f top(minX, maxX);
	Vector2f bottom(minY, maxY);

	bool isButtonPressed = false;

	if (Mouse::isButtonPressed(Mouse::Left) && (mouseDetect(mousePos, top, bottom))) {
		while (isButtonPressed == false) {
			if (Mouse::isButtonPressed(Mouse::Left) != true) {
				isButtonPressed = true;
			}
			loopRefresh();
		}
		return true;
	}
	return false;
}
bool verifyCard(const Card& card, Sprite cardSprite, Sprite cardOutline, int x, int y) {
	
	Texture cardTexture;
	cardTexture.loadFromFile("Texturas/UnoCard.png");

	
	cardSprite.setTexture(cardTexture);
	cardSprite.setPosition(static_cast<float>(x), static_cast<float>(y));

	
	Font font;
	font.loadFromFile("letras/l_u.ttf");
	Text cardNumberText(to_string(card.getNumber()), font, 30);
	cardNumberText.setPosition(static_cast<float>(x + 10), static_cast<float>(y + 10));
	cardNumberText.setFillColor(Color::White);

	
	string colorText;
	switch (card.getColor()) {
	case Card::Color::RED:
		colorText = "RED";
		break;
	case Card::Color::BLUE:
		colorText = "BLUE";
		break;
	case Card::Color::GREEN:
		colorText = "GREEN";
		break;
	case Card::Color::YELLOW:
		colorText = "YELLOW";
		break;
	default:
		colorText = "SPECIAL"; 
		break;
	}

	Text cardColorText(colorText, font, 20);
	cardColorText.setPosition(static_cast<float>(x + 10), static_cast<float>(y + 60));
	cardColorText.setFillColor(Color::White);

	

	
	return false;
}

void addCardAction(Card& cardToAdd, Player& currentPlayer, vector<Card>& unoDeck, RenderWindow& window) {
	
	if (currentPlayer.playCard(cardToAdd)) {
		
		currentPlayer.addCard(cardToAdd);

		
		currentPlayer.removeCard(cardToAdd);
	}
	else {
		
		Card penaltyCard  = tomarCartaDelMazo(unoDeck);

		
		currentPlayer.addCard(penaltyCard);

		
		Font font;
		font.loadFromFile("letras/l_u.ttf"); 

		Text penaltyText("¡" + currentPlayer.getName() + " ha recibido una carta de penalización!", font, 30);
		penaltyText.setFillColor(Color::Red);
		penaltyText.setPosition(10.0f, 10.0f);

		
		window.draw(penaltyText);
		window.display();

		
	}
}

void actionCard(const Card& card, Player& currentPlayer, vector<Card>& unoDeck, RenderWindow& window, Game game) {
	switch (card.getType()) {
	case Card::Type::NUMBER: {

		break;
	}
	case Card::Type::SKIP: {

		void reverseGameDirection();
		break;
	}
	case Card::Type::REVERSE: {

		void reverseGameDirection();

		break;
	}
	case Card::Type::DRAW_TWO: {


		void nextPlayerDrawTwoCards();

		break;
	}

	case Card::Type::WILD: {

		break;
	}
	case Card::Type::WILD_DRAW_FOUR: {
		

		void nextPlayerDrawFourCards();

			break;
	}

	default:
		
		break;
	}

}
	
Card::Color getPlayerSelectedColor(RenderWindow& window) {
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.type == sf::Event::MouseButtonReleased) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);

				if (mousePos.x >= 100 && mousePos.x <= 200 && mousePos.y >= 100 && mousePos.y <= 200) {
					
					return Card::Color::YELLOW;
				}
				else if (mousePos.x >= 300 && mousePos.x <= 400 && mousePos.y >= 100 && mousePos.y <= 200) {
					
					return Card::Color::YELLOW;
				}
				else if (mousePos.x >= 500 && mousePos.x <= 600 && mousePos.y >= 100 && mousePos.y <= 200) {
					
					return Card::Color::YELLOW;
				}
				else if (mousePos.x >= 700 && mousePos.x <= 800 && mousePos.y >= 100 && mousePos.y <= 200) {
					
					return Card::Color::YELLOW;
				}
			}
		}

		window.clear();
		
		RectangleShape redBox(sf::Vector2f(100, 100));
		redBox.setPosition(100, 100);
		redBox.setFillColor(sf::Color::Red);

		RectangleShape blueBox(sf::Vector2f(100, 100));
		blueBox.setPosition(300, 100);
		blueBox.setFillColor(sf::Color::Blue);

		RectangleShape greenBox(sf::Vector2f(100, 100));
		greenBox.setPosition(500, 100);
		greenBox.setFillColor(sf::Color::Green);

		RectangleShape yellowBox(sf::Vector2f(100, 100));
		yellowBox.setPosition(700, 100);
		yellowBox.setFillColor(sf::Color::Yellow);

		window.draw(redBox);
		window.draw(blueBox);
		window.draw(greenBox);
		window.draw(yellowBox);

		window.display();
	}

}

	

