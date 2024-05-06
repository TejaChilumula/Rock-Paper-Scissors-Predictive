#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "Move.h"
#include "Strategy.h"
#include <memory> // For std::unique_ptr
#include <string>

class GameObserver {
public:
  virtual void update(Move playerMove, Move opponentMove) = 0;
  virtual ~GameObserver() {}
};

class Player {
protected:
  std::string name;

public:
  Player(std::string name) : name(name) {}
  virtual ~Player() {}
  virtual std::string getName() = 0; // Pure virtual function
  virtual Move makeMove() = 0;       // Pure virtual function
};

// HumanPlayer class
class HumanPlayer : public Player {
public:
  HumanPlayer() : Player("Human") {}
  HumanPlayer(std::string name) : Player(name) {}
  std::string getName() override { return name; };
  Move makeMove() override;
};

// ComputerPlayer class
class ComputerPlayer : public Player, public GameObserver {
private:
  std::unique_ptr<Strategy> strategy;

public:
  ComputerPlayer(Strategy *strategy)
      : Player(strategy->stratName), strategy(std::move(strategy)) {}
  ComputerPlayer(std::string name, Strategy *strategy)
      : Player(name), strategy(std::move(strategy)) {}

  std::string getName() override { return name; };
  Move makeMove() override { return strategy->chooseMove(); }

  void update(Move playerMove, Move opponentMove) override {
    if (strategy)
      strategy->updateHistory(playerMove, opponentMove);
  }
};

#endif