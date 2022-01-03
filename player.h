#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <vector>
#include <memory>
#include "observer.h"
#include "game.h"

class Player: public Observer {
	Game *subject;
	int playerNum;
	char state; // human (h) or computer (c)
	std::vector<std::string> hand;
	std::vector<std::string> discardPile;
	int discardSum = 0; 
	int oldScore = 0;
	bool hasLegalPlay;
	bool successfulPlay;
	bool successfulDiscard;

	void printLegalPlay();
	bool legalPlay(std::string card) const;
	void playCard(std::string card);
	void computerPlay();
	void discard(std::string card);
	void computerDiscard();
	void printHand() const;
	void rageQuit();
    public:

	Player(Game *g, int playerNum, char state);
	~Player();

	void addCard(std::string card) override;
	void play() override;
	void printResults() override;
	int getScore() override;
};

#endif
