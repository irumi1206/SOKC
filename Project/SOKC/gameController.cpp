#include <iostream>
#include "jsonparser/jsonparser.cpp"
#include "Objects/gameObject.cpp"
#include <vector>
#include <algorithm>

class Controller
{
public:
    Game game;
    Controller(){
        this->game=Game();
    }
    Json::Value control(std::string in){
        Json::Value data=toJson(in);
        Json::Value out;
        switch(data["Header"].asInt()){
            case 0:
            {
                Json::Value toOne;
                toOne["Header"]=0;
                if(game.getId()==data["roomId"].asInt() && game.countPlayers()<16){
                    toOne["serverConnect"]=1;
                }else{
                    toOne["serverConnect"]=-1;
                }
                out["toOne"]=toOne;
                return out;
            }
            case 1:
            {
                Json::Value toOne;
                Json::Value toAll;
                toOne["Header"]=1;
                toAll["Header"]=1;
                std::string name=data["name"].asString();
                int id=game.joinPlayer(name);
                toOne["id"]=10003;//id로 바꿔야 함
                toOne["playerList"]=true;//만들어야 함.
                toAll["id"]=10003;//id로 바꿔야 함
                toAll["name"]=name;
                out["toOne"]=toOne;
                out["toAll"]=toAll;
                return out;

            }
            case 2:
            {
                Json::Value toAll;
                toAll["Header"]=2;
                int id=data["id"].asInt();
                int colorId=data["colorId"].asInt();
                game.findPlayer(id).setColor(colorId);
                toAll["id"]=id;
                toAll["colorId"]=colorId;
                out["toAll"]=toAll;
                return out;
            }
            case 5:
            {
                Json::Value toAll;
                toAll["Header"]=5;
                int id=data["id"].asInt();
                game.deletePlayer(id);
                toAll["id"]=id;
                out["toAll"]=toAll;
                return out;
            }
            default:
            {
                return out;
            }
        }
    }
};