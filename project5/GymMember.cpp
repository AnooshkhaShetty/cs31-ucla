#include "GymMember.h"

// Uses initializer list, as recommended by the official C++ FAQ
// (https://isocpp.org/wiki/faq/ctors#init-list)
GymMember::GymMember(std::string name, std::string accountnumber, Kind kind)
    : mName(name), mAccountNumber(accountnumber), mKind(kind) {}

int GymMember::workoutsThisMonth() { return mWorkoutCount; }

// Workout count is tracked month by month
void GymMember::startNewMonth() { mWorkoutCount = 0; }

void GymMember::newWorkout() { mWorkoutCount++; }

Kind GymMember::getKind() { return mKind; }

std::string GymMember::getKindAsString() {
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

std::string GymMember::getName() { return mName; }

std::string GymMember::getAccountNumber() { return mAccountNumber; }
