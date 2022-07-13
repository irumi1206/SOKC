#include <iostream>
#include "Controller.cpp"

int main(void){

    // Game game;
    // std::string json_example1 = "{\"Header\": 1,\"Player\": {\"id\": 4533 ,\"Name\":\"광오\"}}";
    // std::string json_example2 = "{\"Header\": 1,\"Player\": {\"id\": 4856 ,\"Name\":\"Youngmin\"}}";
    // std::string json_example3 = "{\"Header\": 2,\"Score\": {\"id\": 4856 ,\"data\": \"Kill\", \"value\":1}}";
    // std::string json_example4 = "{\"Header\": 3,\"Score\": {\"id\": 4856 ,\"data\": \"Mission\", \"value\":1},\"Player\": {\"id\": 9561 ,\"Name\":\"Sung Ha\"}}";
    // std::string json_example5 = "{\"Header\": 2,\"Score\": {\"id\": 4856 ,\"data\": \"Vote\", \"value\":1}}";
    // std::string json_example6 = "{\"Header\": 2,\"Score\": {\"id\": 4856 ,\"data\": \"Kill\", \"value\":1}}";
    // std::string json_example7 = "{\"Header\": 2,\"Score\": {\"id\": 4856 ,\"data\": \"Vote\", \"value\":0}}";
    // std::string json_example8 = "{\"Header\": 2,\"Score\": {\"id\": 4856 ,\"data\": \"Vote\", \"value\":0}}";
    // std::string json_example9 = "{\"Header\": 2,\"Score\": {\"id\": 4856 ,\"data\": \"Vote\", \"value\":0}}";
    // std::string json_example10 = "{\"Header\": 4,\"Kill\": {\"id\": 4856 ,\"victim\": 4533}}";
    // game.control(json_example1);
    // game.control(json_example2);
    // //game.flagcontrol(toJson(json_example3));
    // game.control(json_example4);
    // game.control(json_example5);
    // //game.flagcontrol(toJson(json_example6));
    // game.control(json_example7);
    // game.control(json_example8);
    // game.control(json_example9);
    // game.control(json_example10);

    



    // return 0;

    Game game=Game();
    game.makeRoom();
    game.control("{\"Header\": 0,\"roomId\": 100}");
    game.control("{\"Header\": 0,\"roomId\": 10}");
    game.control("{\"Header\": 1,\"roomId\":100,\"name\": \"youngman\"}");
    return 0;
}