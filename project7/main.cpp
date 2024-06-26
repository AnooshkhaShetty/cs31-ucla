#include <iostream>
#include <string>
#include <cassert>
#include "Die.h"
#include "Player.h"
#include "Bunco.h"

int main() {
    using namespace std;
    using namespace cs31;

    // Die class
    // Test randomness is between 1 and 6, inclusive
    Die d;
    for (int i = 1; i <= 100; i++) {
        d.roll();
        int value = d.getValue();
        assert(value >= 1 && value <= 6);
    }

    // Player class
    // Tests dice rolling and score
    Player p;
    for (int i = 1; i <= 6; i++) {
        p.setRound(i);
        assert(p.getScore() == 0);
        assert(p.roll(i) == i);
        assert(p.getScore() == 1);
    }

    Die d1;
    d1.setValue(1);
    Die d2;
    d2.setValue(2);
    Die d3;
    d3.setValue(3);
    Die d4;
    d4.setValue(4);
    Die d5;
    d5.setValue(5);
    Die d6;
    d6.setValue(6);

    Die dies[] = {d1, d2, d3, d4, d5, d6};

    // Bunco class
    // Test game 1: Human wins every round, wins game
    Bunco b_h;
    for (int i = 0; i < 6; i++) {
        b_h.humanPlay(dies[i]);
        b_h.computerPlay(dies[i]);
        b_h.endTurn();
        assert(b_h.determineRoundOutcome() == Bunco::NOTDECIDED);

        // Human wins
        b_h.humanPlay(dies[i]);
        b_h.computerPlay(
            dies[(i + 1) % 6]);  // When i + 1 is greater than 5, wraps to 1
        b_h.endTurn();
        assert(b_h.determineRoundOutcome() == Bunco::HUMANWON);

        // Check if game is over before last round is played
        if (i < 5) {
            assert(b_h.determineGameOutcome() == Bunco::GAMENOTOVER);
        }

        b_h.nextRound();
    }
    assert(b_h.determineGameOutcome() == Bunco::HUMANWONGAME);

    // Test game 2: Computer wins every round, wins game
    Bunco b_c;
    for (int j = 0; j < 6; j++) {
        assert(b_c.determineGameOutcome() == Bunco::GAMENOTOVER);

        // Human and computer both get the same roll
        b_c.humanPlay(dies[j]);
        b_c.computerPlay(dies[j]);
        b_c.endTurn();
        assert(b_c.determineRoundOutcome() == Bunco::NOTDECIDED);

        // Computer wins
        b_c.humanPlay(
            dies[(j + 1) % 6]);  // When i + 1 is greater than 5, wraps to 1
        b_c.computerPlay(dies[j]);
        b_c.endTurn();
        assert(b_c.determineRoundOutcome() == Bunco::COMPUTERWON);

        b_c.nextRound();
    }
    assert(b_c.determineGameOutcome() == Bunco::COMPUTERWONGAME);

    // Test game 3: Player wins odd rounds, computer wins even rounds, game is
    // tied
    Bunco b_t;
    for (int k = 0; k < 6; k++) {
        assert(b_t.determineGameOutcome() == Bunco::GAMENOTOVER);

        // Human and computer both get the same roll
        b_t.humanPlay(dies[k]);
        b_t.computerPlay(dies[k]);
        b_t.endTurn();
        assert(b_t.determineRoundOutcome() == Bunco::NOTDECIDED);

        if (k % 2 == 1) {
            // Human wins odd rounds
            b_t.humanPlay(dies[k]);
            b_t.computerPlay(
                dies[(k + 1) % 6]);  // When i + 1 is greater than 5, wraps to 0
            b_t.endTurn();
            assert(b_t.determineRoundOutcome() == Bunco::HUMANWON);
        } else {
            // Computer wins even rounds
            b_t.humanPlay(
                dies[(k + 1) % 6]);  // When i + 1 is greater than 5, wraps to 0
            b_t.computerPlay(dies[k]);
            b_t.endTurn();
            assert(b_t.determineRoundOutcome() == Bunco::COMPUTERWON);
        }

        b_t.nextRound();
    }
    assert(b_t.determineGameOutcome() == Bunco::TIEDGAME);

    cerr << "All tests passed! (ﾉ◕ヮ◕)ﾉ*:･ﾟ✧" << endl;
    return 0;
}
