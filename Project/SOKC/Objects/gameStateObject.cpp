


class State{
enum States{
    READY,
    GAME_START_BUFFER,
    GAME,
    VOTE_START_BUFFER,
    VOTING,
    VOTE_END_BUFFER,
    GAME_END_BUFFER,
};
private:
    
    States nowState;
public:
    States getState(){
        return nowState;
    }
    void setState(States state){
        this->nowState=state;
    }
};