#ifndef Player_h
#define Player_h
#include "Die.h"

namespace cs31
{
    
    // CS 31 students have been provided this class to represent
    // one of the Bunco Players.  Each Player has its own Die, knows
    // which round is currently being played and knows how to scores
    // it rolled value for the current round.

    class Player
    {
    public:
        Player();
        int roll( );                 // randomly toss the Player's Die
        int roll( int amount );      // force a certain roll
        void setRound( int round );  // set current round, resetting the Player's score
        int  getScore( ) const;      // how many times has Player tossed the current round value?
    private:
        Die mDie;    // the Player's Die
        int mScore;  // the Player's score for this round
        int mRound;  // the current round value, a number between 1 and 6
    };
    
}

#endif /* Player_h */
