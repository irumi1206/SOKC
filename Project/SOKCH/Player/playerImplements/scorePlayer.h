#ifndef SCOREPLAYER_H
#define SCOREPLAYER_H
#include <iostream>

class PlayerScore
{
public:
    int voting_valid;
    int voting_invalid;
    int killScore;
    int missionScore;
    int POTG;
    int SOTG;
    PlayerScore();
    PlayerScore(const PlayerScore& other);
    float votingAccuracy();
    int getKill();
    int getMission();
    void addKill(int score);
    void addMission(int score);
    void reset();
    void addVotingAc(int score);
    void addVotingMi(int score);
    void addPOTG(int score);
    void addSOTG(int score);
    int getPOTG();
    int getSOTG();
};
#endif