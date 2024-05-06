#include "Move.h"
#include "Player.h"
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

class StatisticsTracker : public GameObserver {
private:
  int wins[3]; // 0: Player1 wins, 1: Player2 wins, 2: Ties
  std::string fileName;

public:
  StatisticsTracker(std::string fileName) : fileName(fileName) {
    wins[0] = 0;
    wins[1] = 0;
    wins[2] = 0;
  }

  void update(Move p1Move, Move p2Move);
  void load();
  void save();
  int getWins(int pos) { return wins[pos]; }
};

class Game {
private:
  Player *player1;
  Player *player2;
  StatisticsTracker *stats;

public:
  Game(Player *p1, Player *p2) : player1(p1), player2(p2) {
    std::string filename = p1->getName() + "-" + p2->getName() + "-stats.txt";

    stats = new StatisticsTracker(filename);
    stats->load();
  }
  void playGame();
  void playRound();
  void printResults();
};