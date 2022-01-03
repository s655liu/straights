#include <iostream>
#include <sstream>
#include "player.h"
#include "exceptions.h"

// exception helper function forward declarations

char checkState(char state);
std::string checkCommand(std::string);
std::string checkCard(std::string);

// Player class

Player::Player(Game *g, int playerNum, char state) : subject{g}, playerNum{playerNum}, state{state} 
{
	subject->attach(this);
}

Player::~Player() {
	subject->detach(this);
}

void Player::addCard(std::string card) {
	hand.emplace_back(card);
}

bool Player::legalPlay(std::string card) const {
	if (subject->getPileSize() == 0) { // start of match
		if (card == "7S") {
			return true;
		} else {
			return false;
		}
	}
	for (int i = 0; i < subject->getPileSize(); ++i) {
		int numHand = subject->cardValues[card[0]];
		char suitHand = card[1];
		std::string cardFromPile = subject->getCard(i, "pile");
		int numPile = subject->cardValues[cardFromPile[0]];
		char suitPile = cardFromPile[1];
		int diff = numPile - numHand;
		if (diff == 0) {
			return true;	
		} else if (suitHand != suitPile) {
			continue;
		} else if ((diff == 1) || (diff == -1)) {
			return true;
		} else {
			continue;
		}
	}
	return false;
}

void Player::printLegalPlay() {
	hasLegalPlay = false;
	std::cout << "Legal plays:";  
	for (int i = 0; i < hand.size(); ++i) {
		bool legal = legalPlay(hand[i]);
		if (legal) {
			std::cout << " " << hand[i];
			hasLegalPlay = true;
		}
	}
	std::cout << std::endl;
}

void Player::playCard(std::string card) {
	bool legal = legalPlay(card);	
	if (legal) {
		successfulPlay = true;
		subject->addCard(card, "pile");
		int index;
		for (int i = 0; i < hand.size(); ++i) {
			if (hand[i] == card) {
				index = i;
				break;
			}
		}
		hand.erase(hand.begin() + index);
		std::cout << "Player" << playerNum << " plays " << card << "." << std::endl;
	} else {
		std::cout << "This is not a legal play." << std::endl;
		successfulPlay = false;
	}

}

void Player::computerPlay() {
	for (int i = 0; i < hand.size(); ++i) {
		if (legalPlay(hand[i])) {
			playCard(hand[i]);
			break;
		}
	}	
}

void Player::discard(std::string card) {
	if (hasLegalPlay) {
		successfulDiscard = false;
		std::cout << "You have a legal play. You may not discard." << std::endl;
	} else {
		successfulDiscard = true;
		int index;
		for (int i = 0; i < hand.size(); ++i) {
			if (hand[i] == card) {
				index = i;
				break;
			}
		}
		hand.erase(hand.begin() + index);
		discardPile.emplace_back(card);
		std::cout << "Player" << playerNum << " discards " << card << std::endl;
		int cardValue = subject->cardValues[card[0]];
		discardSum += cardValue;
		subject->addCard(card, "discard");
	}
}

void Player::computerDiscard() {
	discard(hand[0]);
}

void Player::printResults() {
	std::cout << "Player" << playerNum << "'s discards:";
	for (int i = 0; i < discardPile.size(); ++i) {
		std::cout << " " << discardPile[i];
	}
	std::cout<< std::endl;

	std::cout << "Player" << playerNum << "'s score: " << oldScore << " + " << discardSum << " = " << oldScore + discardSum << std::endl;

	oldScore += discardSum;
	discardSum = 0;
	discardPile.erase(discardPile.begin(), discardPile.end());
	hand.erase(hand.begin(), hand.end());
}

void Player::printHand() const {
	std::cout << "Your hand:";
	for (int i = 0; i < hand.size(); ++i) {
		std::cout << " " << hand[i]; 
	}
	std::cout << std::endl;
}

void Player::rageQuit () {
	std::cout << "Player" << playerNum << " ragequits. A computer will now take over." << std::endl;
	state = 'c';
}

void Player::play() {
	printHand();
	printLegalPlay();
	while (true) { // loop taking care of player making illegal discard or play move
		if (state == 'h') {
			try {
				std::string command;
				getline(std::cin, command);
				std::string action = checkCommand(command);
				std::istringstream ss{command};
				std::string move, card;
				ss >> move;
				if (command == "quit") {
					subject->endGame();
					break;
				} else if (command == "deck") {
					subject->printDeck();
				} else if (command == "ragequit") {
					rageQuit();
				} else {
					try {
						ss >> card;
						std::string check = checkCard(card);
						if (move == "play") {
							playCard(card);
							if (successfulPlay) {
								break;
							}
						} else {
							discard(card);
							if (successfulDiscard) {
								break;
							}
						}
					} catch (InvalidCard iCard) {
						std::cout << iCard.message() << std::endl;
					}
				}
			} catch (InvalidCommand iCommand) {
				std::cout << iCommand.message() << std::endl;
			}	
		}
		if (state == 'c') { // two if statements, this taking care of player rage quit scenario
			if (hasLegalPlay) {
				computerPlay();
				break;
			} else {
				computerDiscard();
				break;
			}
		}
	}

}

int Player::getScore() {
	return oldScore;
}
