//
//  Player.cpp
//  Bunco
//
//  Created by Howard Stahl on 1/27/17.
//  Copyright © 2017 Howard Stahl. All rights reserved.
//

// DOOT means a finished TODO
// It's also very funny
// "DOOT"

#include "Player.h"

namespace cs31 {

Player::Player() : mDie(6), mScore(0), mRound(0) {}

// DOOT: randomly roll the die and adjust the score for the current round
// accordingly increase the score if the amount matches this round's value
int Player::roll() {
    mDie.roll();
    const int die_value = mDie.getValue();

    if (die_value == mRound) {
        mScore++;
    }

    return die_value;
}

// DOOT: allow for cheating
// use the amount argument as this Player's roll
// adjust the score for the current round accordingly
// increase the score if the amount matches this round's value
int Player::roll(int amount) {
    if (amount == mRound) {
        mScore++;
    }
    return amount;
}

// DOOT: set the current round and reset the player's score to 0
void Player::setRound(int round) {
    mRound = round;
    mScore = 0;
}

// DOOT: return the score member variable
int Player::getScore() const { return mScore; }

}  // namespace cs31
