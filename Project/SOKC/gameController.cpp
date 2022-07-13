#include <iostream>
#include "Objects/gameObject.cpp"
#include "jsonparser/jsonparser.cpp"
#include <vector>
#include <algorithm>

class GameController
{
private:
std::vector<Room> roomList;
public:
    void makeRoom(){
        roomList.push_back(Room());
    }
    int checkRoom(int id){
        int temp=-1;
        std::for_each(roomList.begin(), roomList.end(), [&](Room room){
            if(room.getId()==id){
                if(room.playerCount()<16){
                    temp=1;
                }
            }
        });
        return temp;
    }
    Room& findRoom(int roomId){
        for(int i=0; i<roomList.size();i++){
            if(roomList[i].getId()==roomId){
                return roomList[i];
            }
        }
    }
    
};