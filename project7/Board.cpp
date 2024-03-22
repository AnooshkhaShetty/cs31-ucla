//
//  Board.cpp
//  Bunco
//
//  Created by Howard Stahl on 1/27/17.
//  Copyright © 2017 Howard Stahl. All rights reserved.
//

// DOOT means a finished TODO
// It's also very funny
// "DOOT"

#include "Board.h"

namespace cs31 {
Board::Board() : mRound(0) {
    // initialize each BoardRow
    for (int i = 1; i <= 6; i++) {
        mBoardRow[i].setRound(i);
    }
}

void Board::setCurrentRound(int round) {
    // unset the current board row
    if (mRound >= 0 && mRound <= 6) mBoardRow[mRound].setCurrentRound(false);
    mRound = round;
    // set the current board row
    if (mRound >= 0 && mRound <= 6) mBoardRow[mRound].setCurrentRound(true);
}

// DOOT: set the human player to have won this current BoardRow
void Board::markHumanAsWinner() {
    mBoardRow[mRound].setHumanAsWinner();
}

// DOOT: set the computer player to have won this current BoardRow
void Board::markComputerAsWinner() {
    mBoardRow[mRound].setComputerAsWinner();
}

// stringify the Board
std::string Board::display() const {
    std::string s = "\t\t  Bunco Game\n\tHuman\t\t\tComputer\n";

    for (int i = 1; i <= 6; i++) {
        s += mBoardRow[i].display() + "\n";
    }

    return (s);
}

// DOOT: how many rounds has the human player won?
int Board::countUpHumanRoundWins() const {
    int human_wins = 0;
    for (int i = 1; i <= 6; i++) {
        human_wins += mBoardRow[i].didHumanWin();
    }
    return human_wins;
}

// DOOT: how many rounds has the computer player won?
int Board::countUpComputerRoundWins() const {
    int computer_wins = 0;
    for (int i = 1; i <= 6; i++) {
        computer_wins += mBoardRow[i].didComputerWin();
    }
    return computer_wins;
}

}  // namespace cs31
