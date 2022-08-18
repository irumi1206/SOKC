#ifndef TCPSERVICE_H
#define TCPSERVICE_H
#include <vector>
#include <thread>
#include "TcpConnectionSocket.h"
#include "TcpConnection.h"
#include "/home/ubuntu/GameProject/SOKC/Controller.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>

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
        void toEach(Json::Value out);
        //Udp 부분
        int udpSocket;
        char udpBuffer[1024];
        struct sockaddr_in serverAddress;
        void udpLogic();
        void looping();
        std::vector<std::thread> otherThreads;
        std::vector<struct sockaddr_in> udpStorage;
        

    public :
        TcpService();
        void setPort(int portNum);
        void setUdp(int portNum);
        void start();
        
};




#endif