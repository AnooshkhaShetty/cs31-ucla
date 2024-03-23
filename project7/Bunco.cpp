#include "Bunco.h"
#include <iostream>

namespace cs31 {
Bunco::Bunco() : mRound(1) { setRound(mRound); }

// stringify the game by stringifying the board
std::string Bunco::display(std::string msg) const {
    using namespace std;
    std::string s = mBoard.display();
    s = s + msg;

    if (gameIsOver()) {
        if (determineGameOutcome() == TIEDGAME) {
            s = s + "\n\t\tBunco wound up tied!\n";
        } else if (determineGameOutcome() == HUMANWONGAME) {
            s = s + "\n\t\tyou won Bunco!\n";
        } else {
            s = s + "\n\t\tyou lost Bunco!\n";
        }
    }
    return (s);
}

// set the current round of play, notifying the board and each
// player of the current round
void Bunco::nextRound() {
    // prevent walking off the edge of the Board...
    if (mRound <= 5) {
        mRound = mRound + 1;
        setRound(mRound);
    }
}

// set the current round of play, notifying the board and each
// player of the current round
void Bunco::setRound(int round) {
    mRound = round;
    mBoard.setCurrentRound(round);
    mHuman.setRound(round);
    mComputer.setRound(round);
}

// let the human player randomly play
// randomly roll the human player's die and return what was rolled
int Bunco::humanPlay() {
    const int amount_rolled = mHuman.roll();
    return (amount_rolled);
}

// let the human player cheat
// force a specific roll amount for the human plyaer
int Bunco::humanPlay(const Die& d) {
    // stubbed out for now...
    const int amount_rolled = d.getValue();
    mHuman.roll(amount_rolled);
    return (amount_rolled);
}

// let the computer player play
// randomly roll the computer player's die and return what was rolled
int Bunco::computerPlay() {
    const int amount_rolled = mComputer.roll();
    return (amount_rolled);
}

// let the computer player cheat
// force a specific roll amount for the computer player
int Bunco::computerPlay(const Die& d) {
    const int amount_rolled = d.getValue();
    mComputer.roll(amount_rolled);
    return (amount_rolled);
}

// update the Board now that a turn of play has ended
// if appropriate, mark the Human or Computer player as the winner on the board
void Bunco::endTurn() {
    const int human_score = mHuman.getScore();
    const int computer_score = mComputer.getScore();

    if (human_score == computer_score) {
        return;
    } else if (human_score > computer_score) {
        mBoard.markHumanAsWinner();
    } else {
        mBoard.markComputerAsWinner();
    }
}

// considering each player's score,
//       determine the winner of this round of play
Bunco::ROUNDOUTCOME Bunco::determineRoundOutcome() {
    const int human_score = mHuman.getScore();
    const int computer_score = mComputer.getScore();
    ROUNDOUTCOME result = ROUNDOUTCOME::NOTDECIDED;

    if (human_score == computer_score) {
        return result;
    } else if (human_score > computer_score) {
        result = ROUNDOUTCOME::HUMANWON;
    } else {
        result = ROUNDOUTCOME::COMPUTERWON;
    }

    return result;
}

// count up the number of won rounds by each player
//       to determine the game's outcome
Bunco::GAMEOUTCOME Bunco::determineGameOutcome() const {
    const int human_rounds_won = mBoard.countUpHumanRoundWins();
    const int computer_rounds_won = mBoard.countUpComputerRoundWins();
    GAMEOUTCOME result = GAMEOUTCOME::GAMENOTOVER;

    if (human_rounds_won + computer_rounds_won < 6) {
        return result;
    } else if (human_rounds_won == computer_rounds_won) {
        result = GAMEOUTCOME::TIEDGAME;
    } else if (human_rounds_won > computer_rounds_won) {
        result = GAMEOUTCOME::HUMANWONGAME;
    } else {
        result = GAMEOUTCOME::COMPUTERWONGAME;
    }

    return result;
}

// is the game over?
bool Bunco::gameIsOver() const {
    GAMEOUTCOME result = determineGameOutcome();
    return (result != GAMENOTOVER);
}

Player Bunco::getHuman() const { return (mHuman); }

Player Bunco::getComputer() const { return (mComputer); }

Board Bunco::getBoard() const { return (mBoard); }

}
