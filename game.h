#ifndef _GAME_H_
#define _GAME_H_
#include <string>
#include <vector>
#include <map>
#include <random>
#include <chrono>
#include <algorithm>
#include "subject.h"

class Game: public Subject {
	int cardCount = 0;
	bool done = false;
	std::vector<std::string> cardPile;
	std::vector<std::string> cardDeck;
    public:
	std::map<char, int> cardValues;

	Game();
	~Game();

	void printDeck();
	void printPile();
	void clearPile();
	int getCardCount();
	int getPileSize();
	void addCard(std::string card, std::string place);
	void shuffleCards(std::default_random_engine rng);
	std::string getCard(int index, std::string place);
	bool getGameStatus();
	void endGame();
};


#endif
