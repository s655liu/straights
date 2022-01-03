#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <memory>
#include <sstream>
#include "game.h"
#include "player.h"
#include "exceptions.h"

using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::vector;
using std::make_shared;
using std::shared_ptr;

int main( int argc, char * argv[] ) {

	// use a time-based seed for the default seed value
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	
	if ( argc > 1 ) {
		try {
			seed = std::stoi( std::string{ argv[1] } );
		} catch( std::invalid_argument & e ) {
			std::cerr << "Invalid seed." << std::endl;
			return 1;
		} catch( std::out_of_range & e ) {
			std::cerr << e.what() << std::endl;
			return -1;
		} // catch
	} // if	
	
	vector<string> values = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K" };
	vector<string> suits = { "C", "D", "H", "S" };
	Game g;
	for (int i = 0; i < 4; ++i) { // initialize deck
		for (int j = 0; j < 13; ++j) {
			g.addCard(values[j] + suits[i], "deck");
		}
	}


	vector<shared_ptr<Player>> players;
	const int numPlayers = 4;
	int playerCount = 1;
	const int totalCardNum = 52;
	const int endScore = 80;

	while (playerCount <= numPlayers) { // initialize player, determine human or computer
		cout << "Is Player" << playerCount << " a human (h) or a computer (c)?" << endl;
		string line;
		getline(cin, line);
		try {
			if (line.size() != 1) {
				throw InvalidInput{line};
			}
			char state = line[0];
			shared_ptr<Player> newPlayer = make_shared<Player>(&g, playerCount, state);
			players.emplace_back(newPlayer);
			playerCount++;
		} catch (InvalidInput iInput) {
			cout << iInput.message() << endl;	
		} catch (InvalidState e) {
			cout << e.message() << endl;
		}
	}
	
	std::default_random_engine rng{seed};
	
	bool exceed80 = false;

	while (!exceed80) { // round starts
		int playing;
		g.shuffleCards(rng);
		for (int i = 0; i < totalCardNum; ++i) { // dealing out cards
			players[i/13]->addCard(g.getCard(i, "deck"));
			if (g.getCard(i, "deck") == "7S") { // determining spade 7
				playing = i/13; 
			} 
		}
		cout << "A new round begins. It's Player" << playing + 1 << "'s turn to play." << endl;
		while (true) { // player takes turn to make command
			g.printPile();
			g.startTurn(playing);
			playing++;            // change player
			if (playing > numPlayers - 1) {
				playing = 0;
			}
			if (g.getGameStatus()) {  // quit command 
				break;
			} else if (g.getCardCount() == totalCardNum) {  // all cards played
				g.results();
				g.clearPile();
				break;
			}
		} // while loop player move
		if (g.getGameStatus()) {
			break;
		}
		for (int i = 0; i < numPlayers; ++i) { // see if game ends
			if (players[i]->getScore() >= endScore) {
				exceed80 = true;
				break;
			}
		}
	} // while loop round

	if (!(g.getGameStatus())) {
		g.determineWinner();	
	}
	return 0;
} // main
