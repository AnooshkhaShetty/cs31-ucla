#include "GymMember.h"
#include "Gym.h"
#include <iostream>
#include <cassert>

int main() {
    Gym gym("SportsClub", "1800 Sepulveda Boulevard", PREMIER);
    gym.setFeatures(true, false, true, false);

    GymMember me("Howard", "123456", EXECUTIVE);
    assert(me.workoutsThisMonth() == 0);
    me.startNewMonth();
    me.newWorkout();
    assert(me.workoutsThisMonth() == 1);

    if (gym.canWorkoutHere(me)) gym.checkin(me, true, false, true, false);
    assert(me.workoutsThisMonth() == 2);

    GymMember member_other("Anooshkha", "1", OTHER);
    GymMember member_regular("Anoooshkha", "12", REGULAR);
    GymMember member_premier("Anoshkha", "123", PREMIER);
    GymMember member_exec("Anshkha", "20", EXECUTIVE);
    Gym gym_other("BFit", "UCLA", OTHER);
    Gym gym_regular("BFitFit", "UCLA", REGULAR);
    Gym gym_premier("BFitFitFit", "UCLA", PREMIER);
    Gym gym_exec("BFit", "UCLA", EXECUTIVE);

    /* GymMember methods */

    // workoutsThisMonth()
    for (int i = 0; i < 100; i++) {
        member_other.newWorkout();
    }
    assert(member_other.workoutsThisMonth() == 100);

    // startNewMonth()
    member_other.startNewMonth();
    assert(member_other.workoutsThisMonth() == 0);

    // newWorkout()
    member_regular.newWorkout();
    assert(member_regular.workoutsThisMonth() == 1);

    // getKind()
    assert(member_other.getKind() == OTHER);

    // getKindAsString()
    assert(member_other.getKindAsString() == "OTHER");
    assert(member_regular.getKindAsString() == "REGULAR");
    assert(member_premier.getKindAsString() == "PREMIER");
    assert(member_exec.getKindAsString() == "EXECUTIVE");

    // getName()
    assert(member_other.getName() == "Anooshkha");

    // getAccountNumber()
    assert(member_exec.getAccountNumber() == "20");

    /* Gym methods */

    // setFeatures()
    // hasCardioFeatures()
    // hasWeightsFeatures()
    // hasPoolFeatures()
    // hasTrackFeatures()
    gym_other.setFeatures(true, false, false, false);
    gym_regular.setFeatures(false, true, false, false);
    gym_premier.setFeatures(false, false, true, false);
    gym_exec.setFeatures(false, false, false, true);

    assert(gym_other.hasCardioFeatures());
    assert(!gym_regular.hasCardioFeatures());

    assert(gym_regular.hasWeightsFeatures());
    assert(!gym_premier.hasWeightsFeatures());

    assert(gym_premier.hasPoolFeatures());
    assert(!gym_exec.hasPoolFeatures());

    assert(gym_exec.hasTrackFeatures());
    assert(!gym_other.hasTrackFeatures());

    // canWorkoutHere()
    assert(gym_other.canWorkoutHere(member_other));
    assert(!gym_other.canWorkoutHere(member_regular));
    assert(!gym_other.canWorkoutHere(member_premier));
    assert(!gym_other.canWorkoutHere(member_exec));

    assert(!gym_regular.canWorkoutHere(member_other));
    assert(gym_regular.canWorkoutHere(member_regular));
    assert(gym_regular.canWorkoutHere(member_premier));
    assert(gym_regular.canWorkoutHere(member_exec));

    assert(!gym_premier.canWorkoutHere(member_other));
    assert(!gym_premier.canWorkoutHere(member_regular));
    assert(gym_premier.canWorkoutHere(member_premier));
    assert(gym_premier.canWorkoutHere(member_exec));

    assert(!gym_exec.canWorkoutHere(member_other));
    assert(!gym_exec.canWorkoutHere(member_regular));
    assert(!gym_exec.canWorkoutHere(member_premier));
    assert(gym_exec.canWorkoutHere(member_exec));

    // checkin()
    member_other.startNewMonth();
    member_regular.startNewMonth();
    member_premier.startNewMonth();
    member_exec.startNewMonth();

    assert(gym_other.checkin(member_other, true, false, false, false));
    assert(!gym_other.checkin(member_other, true, true, true, true));
    assert(member_other.workoutsThisMonth() == 1);

    assert(gym_regular.checkin(member_regular, false, true, false, false));
    assert(!gym_regular.checkin(member_regular, true, true, true, true));
    assert(member_regular.workoutsThisMonth() == 1);

    assert(gym_premier.checkin(member_premier, false, false, true, false));
    assert(!gym_premier.checkin(member_premier, true, true, true, true));
    assert(member_premier.workoutsThisMonth() == 1);

    assert(gym_exec.checkin(member_exec, false, false, false, true));
    assert(!gym_exec.checkin(member_exec, true, true, true, true));
    assert(member_exec.workoutsThisMonth() == 1);

    // getKind()
    assert(gym_other.getKind() == OTHER);

    // getKindAsString()
    assert(gym_other.getKindAsString() == "OTHER");
    assert(gym_regular.getKindAsString() == "REGULAR");
    assert(gym_premier.getKindAsString() == "PREMIER");
    assert(gym_exec.getKindAsString() == "EXECUTIVE");

    // getLocation()
    assert(gym_other.getLocation() == "UCLA");

    // getName()
    assert(gym_exec.getName() == "BFit");

    std::cerr << "Passed the tests."
              << std::endl;

    return 0;
}
