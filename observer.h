#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include <string>

class Observer {
 public:
  virtual void play() = 0;
  virtual void printResults() = 0;
  virtual void addCard(std::string) = 0;
  virtual int getScore() = 0;
  virtual ~Observer() = default;
};

#endif
