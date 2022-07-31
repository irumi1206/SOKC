#ifndef TCPSERVICE_H
#define TCPSERVICE_H
#include <vector>
#include <thread>
#include "tcpConnectionSocket.h"
#include "tcpConnection.h"
// //==추가==//
#include "/home/ubuntu/GameProject/SOKC/Controller.h"
// //==여기까지==//

class tcpService{
    private :
        int clientNum;
        // //==추가==//
        Controller controller;
        // //==여기==//
        tcpConnectionSocket masterSocket;
        std::vector<tcpConnection> connectedClients;
        std::vector<std::thread> threads;
        void clientLogic(int clientIndex);
    public :
        tcpService();
        void setPort(int portNum);
        void start();
        
        

};




#endif