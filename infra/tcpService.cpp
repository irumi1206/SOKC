#include "tcpService.h"
#include <thread>
 tcpService::tcpService(){
     client_num=0;
 };

 void tcpService::setPort(int portNum){
     masterSocket.setPort(portNum);
     masterSocket.getReady();
 }

 void tcpService::clientLogic(int clientNum,int socketDescriptor,std::vector<int> socketDescriptors){
    char buffer[1024]={0};
    const char* response="server received message";
    while(1){
        char buffer[1024]={0};
        int valread = read(socketDescriptor, buffer, 1024);
        printf("client %d : %s\n", clientNum, buffer);
        send(socketDescriptor, response, strlen(response), 0);
        // for(int i=0;i<socketDescriptors.size();++i){
        //     if(socketDescriptors[i]==socketDescriptor) continue;
        //     send(socketDescriptors[i],buffer,strlen(buffer),0);
        // }
    }
}

 void tcpService::start(){
    while(1){
        tcpConnection connectedClient=masterSocket.getConnectedSocket();
        clientNum++;
        connectedClients.push_back(connectedClient);
        
 }
