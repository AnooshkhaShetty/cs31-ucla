#include <iostream>
#include <string>

using namespace std;

// Track state of CD player
struct CdPlayerState {
    bool is_valid = false;
    bool is_open = false;
    bool is_cd_inserted = false;
    bool is_playing = false;
    bool is_play_button_pressed =
        false;  // Opening the CD player stops playback, but the "Stop" action
                // is still allowed to occur. Prof. Stahl explicitly confirmed
                // this. To accomplish this, I think of the "Stop" action as
                // deselecting the "Play" action, which either stops playback or
                // does nothing if playback is already stopped.
    int previous_track = 0;
    int current_track = 0;
    int total_tracks_played = 0;
};

CdPlayerState getCdPlayerState(string cd_player_actions) {
    CdPlayerState cd_player;
    cd_player.is_valid = false;

    // Possible CD player actions, excluding tracks
    const char open = 'O';
    const char insert = 'I';
    const char close = 'C';
    const char play = 'P';
    const char stop = 'S';
    const char remove = 'R';

    // Initial check for length and first char, which must be 'O'
    if (cd_player_actions.size() < 1 || cd_player_actions.at(0) != open) {
        return cd_player;
    } else {
        cd_player.is_open = true;
    }

    // Skip first char since it was already checked
    for (size_t i = 1; i < cd_player_actions.size(); i++) {
        const char current_action = cd_player_actions.at(i);

        switch (current_action) {
            case open:
                if (!cd_player.is_open) {
                    cd_player.is_open = true;
                    cd_player.is_playing = false;
                } else {
                    return cd_player;
                }
                break;
            case insert:
                if (cd_player.is_open && !cd_player.is_cd_inserted) {
                    cd_player.is_cd_inserted = true;
                } else {
                    return cd_player;
                }
                break;
            case close:
                if (cd_player.is_open) {
                    cd_player.is_open = false;
                } else {
                    return cd_player;
                }
                break;
            case play:
                if (!cd_player.is_open && cd_player.is_cd_inserted) {
                    cd_player.is_playing = true;
                    cd_player.is_play_button_pressed = true;
                } else {
                    return cd_player;
                }
                break;
            case stop:
                if (cd_player.is_play_button_pressed || cd_player.is_open) {
                    cd_player.is_playing = false;
                    cd_player.is_play_button_pressed = false;
                } else {
                    return cd_player;
                }
                break;
            case remove:
                if (cd_player.is_open && cd_player.is_cd_inserted) {
                    cd_player.is_cd_inserted = false;
                    cd_player.previous_track = 0;
                    cd_player.current_track = 0;
                } else {
                    return cd_player;
                }
                break;
            default:
                // Check if a track is being played
                if (isdigit(current_action) && !cd_player.is_open &&
                    cd_player.is_cd_inserted && cd_player.is_playing) {
                    // Convert char to corresponding integer digit
                    cd_player.current_track = current_action - '0';
                    if (cd_player.current_track !=
                        cd_player.previous_track + 1) {
                        return cd_player;
                    }
                    cd_player.previous_track++;
                    cd_player.total_tracks_played++;
                } else {
                    return cd_player;
                }
                break;
        }
    }

    cd_player.is_valid = true;
    return cd_player;
}

bool isValidCDPlayerString(string cd_player_actions) {
    return getCdPlayerState(cd_player_actions).is_valid;
}

bool isOpen(string cd_player_actions) {
    CdPlayerState cd_player = getCdPlayerState(cd_player_actions);
    return cd_player.is_open && cd_player.is_valid;
}

bool hasCD(string cd_player_actions) {
    CdPlayerState cd_player = getCdPlayerState(cd_player_actions);
    return cd_player.is_cd_inserted && cd_player.is_valid;
}

int totalTracksPlayed(string cd_player_actions) {
    CdPlayerState cd_player = getCdPlayerState(cd_player_actions);
    return cd_player.is_valid ? cd_player.total_tracks_played : -1;
}

int currentTrack(string cd_player_actions) {
    CdPlayerState cd_player = getCdPlayerState(cd_player_actions);
    // Returns the next track that would be played, if valid.
    return cd_player.is_valid && cd_player.is_cd_inserted
               ? cd_player.current_track + 1
               : -1;
}

int main() {
    const string green_text = "\033[32m";
    const string blue_text = "\033[34m";
    const string reset_text = "\033[0m";
    const string valid_tests[] = {
        "OICP123SP456SORICP123",
        "OIRICP123SOR",
        "OICP123ORICP123",
        "OICPO",
        "OICPOR",
        "OICP123O",
        "OICP123SOCP456S",
        "OICP123P456SOR",
        "OICPP123SOR",
        "OICP123SORICP123456SOR",
        "OICP123OC",
        "OICP123OCP",
        "OICP123OCP456",
        "OC",
        "OCOIC",
        "OCOICO",
        "OICP123OS",
        "OICP123ORS",
        "OICP123ORCS",
        "OICP123ORIS",
        "OICPS",
        "OICPSPSPS",
        "OICP123SP456",
        "OICP123OCS",
        "OCOICP1234SOCOCP5678",
        "OCOCOCOC",
        "OICP123ORICS",
        "OICP1P23SOR",
        "OIC",
        "OICORIRIC",
        "OIRIR",
        "OIRICORIC",
        "OICORICPOCPOCPORIRICP",
        "OICP",
        "OICOCORI",
        "OICP1",
        "OICP123456789",
        "OICP123SP",
        "OICP123",
        "OICP12345SOC",
        "OICP123SOR",
        "OICP123SORI",
        "OIRC",
        "OICOCOCOCOCO",
        "OICORIRCOICPSO",
        "OICPP12PPPPPPPPPPS",
        "O",
    };
    const string invalid_tests[] = {
        "xyz",
        "oic",
        "OIC xyz",
        "P123S",
        "OCIP123S",
        "OICR",
        "OCOICC",
        "OCOICOO",
        "OIP123",
        "OCP123",
        "OICS",
        "OP123C",
        "OIR123",
        "OIR123P",
        "OC123P",
        "OICP123ORICP456",
        "OICP147S",
        "OICP123SOCP123S",
        "OICP123P123456SOR",
        "OICS123OC",
        "OICP123ORIC123",
        "OICP123OC456",
        "",
        "    ",
        "OICOI",
        "OOOOcyf",
        "OICP123P45OC6",
        "OIP",
        "OIRIRCP1SOIRC",
    };

    std::cerr << boolalpha;
    for (const string& test : valid_tests) {
        std::cerr << test << "\t"
                  << (isValidCDPlayerString(test) ? green_text : blue_text)
                  << isValidCDPlayerString(test) << reset_text << "\t"
                  << isOpen(test) << "\t" << hasCD(test) << "\t"
                  << totalTracksPlayed(test) << "\t" << currentTrack(test)
                  << "\n";
    }
    std::cerr << "\n==========\n\n";
    for (const string& test : invalid_tests) {
        std::cerr << test << "\t"
                  << (isValidCDPlayerString(test) ? green_text : blue_text)
                  << isValidCDPlayerString(test) << reset_text << "\t"
                  << isOpen(test) << "\t" << hasCD(test) << "\t"
                  << totalTracksPlayed(test) << "\t" << currentTrack(test)
                  << "\n";
    }

    std::cerr << "End of tests" << endl;
    return 0;
}
