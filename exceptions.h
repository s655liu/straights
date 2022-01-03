#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

class Exception {
	virtual std::string message () const = 0;
};

class InvalidState : public Exception {
	char state;
   public:
	InvalidState(char state);
	std::string message() const override;
};

class InvalidCommand : public Exception {
	std::string command;
   public:
	InvalidCommand(std::string command);
	std::string message() const override;
};

class InvalidCard : public Exception {
	std::string card;
   public:
	InvalidCard(std::string card);
	std::string message() const override;
};

class InvalidInput : public Exception {
	std::string input;
    public:
	InvalidInput(std::string input);
	std::string message() const override;
};

#endif
