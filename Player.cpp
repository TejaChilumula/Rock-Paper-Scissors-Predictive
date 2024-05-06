#include "Player.h"

Move HumanPlayer::makeMove() {
  std::cout << "Enter your move (r = Rock, p = Paper, s = Scissors): ";
  char move;
  std::cin >> move;
  move = std::tolower(move); // convert to lowercase to make it case-insensitive

  switch (move) {
  case 'r':
    return Move::ROCK;
  case 'p':
    return Move::PAPER;
  case 's':
    return Move::SCISSORS;
  default:
    std::cout << "Invalid input. Please enter r, p, or s.\n";
    return makeMove(); // ask for input again if it's invalid
  }
};
