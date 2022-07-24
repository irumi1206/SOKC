#include "tcpService.h"
#include <thread>
#include <cstdio>
#include <string>
#include <cstring>
#include "/home/ubuntu/GameProject/Project/SOKCH/Controller.h"
//#include <jsoncpp/json/json.h>

 tcpService::tcpService(){
     clientNum=0;
 };

 void tcpService::setPort(int portNum){
     masterSocket.setPort(portNum);
     masterSocket.getReady();
 }

 void tcpService::clientLogic(int clientIndex){
    const char* response="server received message";

    tcpConnection currentTcpConnection=connectedClients[clientIndex];
    while(1){
        char buffer[1024]={0};
        currentTcpConnection.in(buffer,1024);
        // //==추 가==//
        Json::Value temp=controller.control(std::string(buffer));
        std::cout<<std::string(buffer)<<std::endl;
        std::string temp1=temp["toOne"].toStyledString();
        char temp2[1024]={0};
        strcpy(temp2,temp1.c_str());
        // //==여기까지==//
        printf("client %d : %s\n", clientNum, buffer);
        currentTcpConnection.out(temp2);
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
