#include "Gym.h"

// Uses initializer list, as recommended by the official C++ FAQ
// (https://isocpp.org/wiki/faq/ctors#init-list)
Gym::Gym(std::string name, std::string location, Kind kind)
    : mName(name), mLocation(location), mKind(kind) {}

void Gym::setFeatures(bool cardio, bool weights, bool pool, bool track) {
    hasCardio = cardio;
    hasWeights = weights;
    hasPool = pool;
    hasTrack = track;
}

bool Gym::canWorkoutHere(GymMember m) {
    switch (m.getKind()) {
        case EXECUTIVE:
            return mKind == EXECUTIVE || mKind == PREMIER || mKind == REGULAR;
            break;
        case PREMIER:
            return mKind == PREMIER || mKind == REGULAR;
            break;
        case REGULAR:
            return mKind == REGULAR;
            break;
        case OTHER:
            // OTHER can only match with OTHER, according to the instructions
            return mKind == OTHER;
            break;
        default:
            return false;
    }
}

bool Gym::checkin(GymMember& m, bool wantsCardio, bool wantsWeights,
                  bool wantsPool, bool wantsTrack) {
    if (!canWorkoutHere(m)) {
        return false;
    }

    // Checks that features the gym member wants are present. Only returns false
    // when the gym member requests a feature that is not present.
    if (!(wantsCardio && hasCardio == false) &&
        !(wantsWeights && hasWeights == false) &&
        !(wantsPool && hasPool == false) &&
        !(wantsTrack && hasTrack == false)) {
        m.newWorkout();
        return true;
    } else {
        return false;
    }
}

bool Gym::hasCardioFeatures() { return hasCardio; }

bool Gym::hasWeightsFeatures() { return hasWeights; }

bool Gym::hasPoolFeatures() { return hasPool; }

bool Gym::hasTrackFeatures() { return hasTrack; }

Kind Gym::getKind() { return mKind; }

std::string Gym::getKindAsString() {
    switch (mKind) {
        case OTHER:
            return "OTHER";
            break;
        case REGULAR:
            return "REGULAR";
            break;
        case PREMIER:
            return "PREMIER";
            break;
        case EXECUTIVE:
            return "EXECUTIVE";
            break;
        default:
            // Should never run unless new enums are added or an invalid integer
            // is somehow passed to the function
            return "SOMETHING_HAS_GONE_TERRIBLY_WRONG";
            break;
    }
}

std::string Gym::getLocation() { return mLocation; }

std::string Gym::getName() { return mName; }
