#ifndef TCPSERVICE_H
#define TCPSERVICE_H
#include <vector>
#include <thread>
#include "TcpConnection.h"
#include "/home/ubuntu/GameProject/SOKC/Controller.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>

class TcpService{
    public :
        int clientNum;
        int connectedNum;
        //Controller
        Controller controller;
        Json::Value null;
        //tcp
        std::vector<TcpConnection> connectedClients;
        std::vector<bool> alive;
        void contollerLogic(Json::Value jsonRequest,int Id);
        void toAll(std::string out);
        void toOne(int ind,std::string out);
        void toOthers(int ind,std::string out);
        void toEach(Json::Value out);
        //udp
        void sendPosition(int sock);
        std::vector<struct sockaddr_in> udpStorage;
        

    public :
        TcpService();
        
};




#endif