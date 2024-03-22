#ifndef GYM_MEMBER_H
#define GYM_MEMBER_H

#include <string>
#include "Kind.h"

class GymMember {
   private:
    std::string mName;
    std::string mAccountNumber;
    Kind mKind;
    int mWorkoutCount = 0;

   public:
    GymMember(std::string name, std::string accountnumber, Kind kind);

    int workoutsThisMonth();

    void startNewMonth();

    void newWorkout();

    Kind getKind();

    std::string getKindAsString();

    std::string getName();

    std::string getAccountNumber();
};

#endif
