#include "tcpService.h"
#include <thread>
#include <cstdio>
 tcpService::tcpService(){
     clientNum=0;
 };

 void tcpService::setPort(int portNum){
     masterSocket.setPort(portNum);
     masterSocket.getReady();
 }

 void tcpService::clientLogic(int clientIndex){
    char8_t* response=u8"server received message";

    tcpConnection currentTcpConnection=connectedClients[clientIndex];
    while(1){
        char8_t buffer[1024]={0};
        currentTcpConnection.in(buffer,1024);
        printf("client %d : %s\n", clientNum, buffer);
        currentTcpConnection.out(buffer);
    }
}

 void tcpService::start(){
    while(1){
        tcpConnection connectedClient=masterSocket.getConnectedSocket();
        connectedClients.push_back(connectedClient);
        threads.push_back(std::thread(&tcpService::clientLogic,this,clientNum));
        clientNum++;
        printf("client %d connected\n",clientNum);
    }

        
 }
