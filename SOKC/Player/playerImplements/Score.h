#ifndef SCORE_H
#define SCORE_H
#include <iostream>
#include <vector>

class PlayerScore
{
public:
    int voting_valid;
    int voting_invalid;
    int killScore;
    int missionScore;
    std::vector<int> missionClearScore;
    int benefitTaken;
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
    float averageMissionClear();
};
#endif