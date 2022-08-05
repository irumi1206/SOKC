#ifndef VOTINGSTATUS_H
#define VOTINGSTATUS_H

class VotingStatus{
    public :
        int votingPlayerId;
        int votedPlayerId;

    public :
        VotingStatus();
        VotingStatus(int votingPlayerId,int votedPlayerId);
        void setValue(int votingPlayerId,int votedPlayerId);
};


#endif