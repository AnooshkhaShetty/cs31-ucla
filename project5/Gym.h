#ifndef GYM_H
#define GYM_H

#include <string>
#include "GymMember.h"

class Gym {
   private:
    std::string mName;
    std::string mLocation;
    Kind mKind;
    // Gym objects should not have any features by default, since they aren't
    // specified by the constructor but must be manually set with setFeatures()
    bool hasCardio = false;
    bool hasWeights = false;
    bool hasPool = false;
    bool hasTrack = false;

   public:
    Gym(std::string name, std::string location, Kind kind);

    void setFeatures(bool cardio, bool weights, bool pool, bool track);

    bool canWorkoutHere(GymMember m);

    bool checkin(GymMember& m, bool wantsCardio, bool wantsWeights,
                 bool wantsPool, bool wantsTrack);

    bool hasCardioFeatures();

    bool hasWeightsFeatures();

    bool hasPoolFeatures();

    bool hasTrackFeatures();

    Kind getKind();

    std::string getKindAsString();

    std::string getLocation();

    std::string getName();
};

#endif
