#include <iostream>
#include "game.h"

Game::Game() {
	cardValues['A'] = 1;
	for (char c = '2'; c <= '9'; ++c) {
		cardValues[c] = c - 48;
	}
	cardValues['T'] = 10;
	cardValues['J'] = 11;
	cardValues['Q'] = 12;
	cardValues['K'] = 13;
}
Game::~Game() {}

void Game::printDeck() {
	for (int i = 0; i < 52; ++i) {
		std::cout << cardDeck[i];
		if ((i + 1) % 13 == 0) {
			std::cout << std::endl;
		} else {
			std::cout << " ";
		}
	}
}

void Game::printPile() {
	std::vector<std::string> suits = {"Clubs", "Diamonds", "Hearts", "Spades"};
	std::vector<char> s = {'C', 'D', 'H', 'S'};
	std::cout << "Cards on the table:" << std::endl;
	for (int j = 0; j < suits.size(); ++j) { // list of suits
		std::cout << suits[j] << ":";
		for (int k = 1; k <= 13; ++k) {
			for (int i = 0; i < cardPile.size(); ++i) { 
				int value = cardValues[cardPile[i][0]];
				char suit = cardPile[i][1];
				if (suit == s[j] && value == k) {
					std::cout << " " << cardPile[i][0];
					continue;
				}	
			}
		}
		std::cout << std::endl;
	}
}

void Game::clearPile() {
	cardPile.erase(cardPile.begin(), cardPile.end());
	cardCount = 0;
}

int Game::getCardCount() {
	return cardCount;
}

int Game::getPileSize() {
	return cardPile.size();
}

void Game::addCard(std::string card, std::string place) {
	if (place == "pile") {
		cardPile.emplace_back(card);
		cardCount++;
	} else if(place == "discard") {
		cardCount++;
	} else {
		cardDeck.emplace_back(card);
	}
}

void Game::shuffleCards(std::default_random_engine rng) {
	std::shuffle(cardDeck.begin(), cardDeck.end(), rng);
}

std::string Game::getCard(int index, std::string place) {
	if (place == "pile") {
		return cardPile[index];
	} else {
		return cardDeck[index];
	}
}

bool Game::getGameStatus() {
	return done;
}

void Game::endGame() {
	done = true;
}
