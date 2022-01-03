#include <string>
#include <sstream>
#include "exceptions.h"

// Invalid state

char checkState(char state) {
	if (state == 'c' || state == 'h') {
		return state;
	} else {
		throw InvalidState{state};
	}
}

InvalidState::InvalidState( char state ): state{state} {}

std::string InvalidState::message() const {
	std::ostringstream ss;
	ss << "Invalid input: " << state << ". Not human (h) or computer (c)";
	return ss.str();
}

// Invalid Input for human or computer

InvalidInput::InvalidInput(std::string input) : input{input} {}

std::string InvalidInput::message() const {
	std::ostringstream ss;
	ss << "Invalid input: " << input << ". Enter human (h) or computer (c)";
	return ss.str();
}

// Invalid Command

std::string checkCommand(std::string command) {
	std::istringstream ss{command};
	std::string move;
	std::string card;
	std::string other;
	ss >> move;
	if ((move == "deck" || move == "ragequit" || move == "quit") && !(ss >> card)) {
		return command;
	} else if ((move == "play" || move == "discard") && (ss >> card) && !(ss >> other)) {
		return command;
	} else {
		throw InvalidCommand{command};
	}
}

InvalidCommand::InvalidCommand(std::string command): command{command} {}

std::string InvalidCommand::message() const {
	std::ostringstream ss;
	ss << "Invalid command: " << command << ". Valid commands: play <card>, discard <card>, deck, quit, ragequit.";
	return ss.str();
}

// Invalid Card

std::string checkCard(std::string card) {
	char num = card[0];
	char suit = card[1];
	if (suit != 'C' && suit != 'D' && suit != 'H' && suit != 'S') {
		throw InvalidCard{card};
	} else if ((num >= '2' && num <= '9') || num == 'A' || num == 'T' || num == 'J' || num == 'Q' || num == 'K') {
		return card;
	} else {
		throw InvalidCard{card};
	}
}

InvalidCard::InvalidCard(std::string card): card{card} {}

std::string InvalidCard::message() const {
	std::ostringstream ss;
	ss << "Invalid card syntax: " << card;
	return ss.str();
}
