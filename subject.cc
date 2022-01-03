#include "subject.h"
#include "observer.h"
#include <vector>
#include <iostream>

void Subject::attach(Observer *o) { observers.emplace_back(o); }

void Subject::detach(Observer *o) {
  for (auto it = observers.begin(); it != observers.end();) {
    if (*it == o) it = observers.erase(it);
    else ++it;
  }
}

void Subject::startTurn(int playing) {
	for (int i = 0; i < observers.size(); ++i) {
		if (i == playing) {
			observers[i]->play();
			break;	
		}
	}
}

void Subject::results() {
	for (int i = 0; i < 4; ++i) {
		observers[i]->printResults();
	}
}

void Subject::determineWinner() {
	int lowest = observers[0]->getScore();
	std::vector<int> lowestIndex;
	for (int i = 0; i < observers.size(); ++i) { // determine lowest score
		if (observers[i]->getScore() < lowest) {
			lowest = observers[i]->getScore();
		}	
	}
	for (int i = 0; i < observers.size(); ++i) { // determine  winners
		if (observers[i]->getScore() == lowest) {
			lowestIndex.emplace_back(i + 1);
		}
	}
	for (int i = 0; i < lowestIndex.size(); ++i) {
		std::cout << "Player" << lowestIndex[i] << " wins!" << std::endl;
	}
}
