#include "Game.h"

void StatisticsTracker::update(Move p1Move, Move p2Move) {
  if (p1Move == p2Move) {
    wins[2]++;
  } else if ((p1Move == Move::ROCK && p2Move == Move::SCISSORS) ||
             (p1Move == Move::PAPER && p2Move == Move::ROCK) ||
             (p1Move == Move::SCISSORS && p2Move == Move::PAPER)) {
    wins[0]++;
  } else {
    wins[1]++;
  }
}

void StatisticsTracker::save() {
  std::ofstream file("./output/" + fileName);
  file << wins[0] << " " << wins[1] << " " << wins[2] << std::endl;
  file.close();
}

void StatisticsTracker::load() {
  std::ifstream file("./output/" + fileName);
  if (file) {
    file >> wins[0] >> wins[1] >> wins[2];
  }
  file.close();
}

void Game::playRound() {
  Move player1Move = player1->makeMove();
  Move player2Move = player2->makeMove();

  GameObserver *obsever1 = dynamic_cast<GameObserver *>(player1);
  if (obsever1) {
    obsever1->update(player1Move, player2Move);
  }
  std::cout << player1->getName() << " played " << player1Move.toString()
            << std::endl;

  GameObserver *obsever2 = dynamic_cast<GameObserver *>(player2);
  if (obsever2) {
    obsever2->update(player2Move, player1Move);
  }
  std::cout << player2->getName() << " played " << player2Move.toString()
            << std::endl;

  if (player1Move == player2Move) {
    std::cout << "It's a tie!\n";
  } else if ((player1Move == Move::ROCK && player2Move == Move::SCISSORS) ||
             (player1Move == Move::PAPER && player2Move == Move::ROCK) ||
             (player1Move == Move::SCISSORS && player2Move == Move::PAPER)) {
    std::cout << player1->getName() << " wins the round!\n";

  } else {
    std::cout << player2->getName() << " wins the round!\n";
  }
  stats->update(player1Move, player2Move);
}

void Game::printResults() {
  std::cout << "Final Results:\n";
  std::cout << player1->getName() << " wins: " << stats->getWins(0)
            << std::endl;
  std::cout << player2->getName() << " wins: " << stats->getWins(1)
            << std::endl;
  std::cout << "Ties: " << stats->getWins(2) << std::endl;
}

void Game::playGame() {
  for (int i = 0; i < 20; i++) {
    std::cout << "Round " << i + 1 << "...\n";
    playRound();
    std::cout << "\n" << std::endl;
  }
  stats->save();
  printResults();
}