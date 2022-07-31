#ifndef TCPSERVICE_H
#define TCPSERVICE_H
#include <vector>
#include <thread>
#include "TcpConnectionSocket.h"
#include "TcpConnection.h"
#include "/home/ubuntu/GameProject/SOKC/Controller.h"

class TcpService{
    private :
        int clientNum;
        // //==추가==//
        Controller controller;
        Json::Value null;
        // //==여기==//
        TcpConnectionSocket masterSocket;
        std::vector<TcpConnection> connectedClients;
        std::vector<std::thread> threads;
        std::vector<int> alive;
        void clientLogic(int clientIndex);
        void toAll(std::string out);
        void toOne(int ind,std::string out);
        void toOthers(int ind,std::string out);

    public :
        TcpService();
        void setPort(int portNum);
        void start();
        
        

};




#endif