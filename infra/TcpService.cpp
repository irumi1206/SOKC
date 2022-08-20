#include "TcpService.h"
#include <thread>
#include <cstdio>
#include <string>
#include <cstring>
#include "/home/ubuntu/GameProject/SOKC/Controller.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>

 TcpService::TcpService(){
     clientNum=0;
     connectedNum=0;
 };

//  void TcpService::setPort(int portNum){
//     masterSocket.setPort(portNum);
//     masterSocket.getReady();
//  }

 void TcpService::toAll(std::string out){
    char charOut[1024]={0};
    strcpy(charOut,out.c_str());
    for(int i=0;i<connectedClients.size();++i){
        if(!alive[i]) continue;
        TcpConnection currentConnection=connectedClients[i];
        currentConnection.out(charOut);
    }
 }

 void TcpService::toOne(int ind,std::string out){
    if(!alive[ind]) return;
    char charOut[1024]={0};
    strcpy(charOut,out.c_str());
    TcpConnection currentConnection=connectedClients[ind];
    currentConnection.out(charOut);
 }

 void TcpService::toOthers(int ind,std::string out){
    char charOut[1024]={0};
    strcpy(charOut,out.c_str());
    for(int i=0;i<connectedClients.size();++i){
        if(!alive[i]) continue;
        if(i==ind) continue;
        TcpConnection currentConnection=connectedClients[i];
        currentConnection.out(charOut);
    }
 }
//----------toEach 구현
 void TcpService::toEach(Json::Value out){
    char charOut[1024]={0};
    int size=out.size();
    for(int i=0;i<size;i++){
        Json::Value each=out[i];
        int index=each["recver"].asInt()-10000;
        toOne(index,each["data"].toStyledString()+"$");
    }
 }

 void TcpService::contollerLogic(Json::Value jsonRequest,int id){
    Json::Value jsonResponse=controller.control(jsonRequest.toStyledString(),id);
    std::cout<<jsonResponse.toStyledString()<<std::endl;
    Json::Value One=jsonResponse["toOne"];
    Json::Value All=jsonResponse["toAll"];
    Json::Value Oth=jsonResponse["other"];
    Json::Value Eac=jsonResponse["toEach"];

    int clientIndex=id%100;

    for(int i=0;i<One.size();i++){
        toOne(clientIndex,One[i].toStyledString()+"$");
    }
    for(int i=0;i<All.size();i++){
        toAll(All[i].toStyledString()+"$");
    }
    for(int i=0;i<Oth.size();i++){
        toOthers(clientIndex,Oth[i].toStyledString()+"$");
    }
    for(int i=0;i<Eac.size();i++){
        toEach(Eac[i]);
    }
 }

//-----------
//  void TcpService::clientLogic(int clientIndex){
//     const char* response="server received message";

//     TcpConnection currentTcpConnection=connectedClients[clientIndex];
//     while(1){
//         char buffer[1024]={0};
//         currentTcpConnection.in(buffer,1024);
//         try{
//             // //==추 가==//
//             Json::Value temp=controller.control(std::string(buffer),clientIndex);
//             std::cout<<std::string(buffer)<<std::endl;
//             std::cout<<temp.toStyledString()<<std::endl;
//             Json::Value One=temp["toOne"];
//             Json::Value All=temp["toAll"];
//             Json::Value Oth=temp["other"];
//             Json::Value Eac=temp["toEach"];

//             for(int i=0;i<One.size();i++){
//                 toOne(clientIndex,One[i].toStyledString());
//             }
//             for(int i=0;i<All.size();i++){
//                 toAll(All[i].toStyledString());
//             }
//             for(int i=0;i<Oth.size();i++){
//                 toOthers(clientIndex,Oth[i].toStyledString());
//             }
//             for(int i=0;i<Eac.size();i++){
//                 toEach(Eac.toStyledString());
//             }
//             // //==여기까지==//
//             printf("client %d : %s\n", clientNum, buffer);
            
//         }
//         catch(...){
//             printf("client %d disconnected\n",clientIndex+1);
//             return;
//         }
//     }
// }

// void TcpService::udpLogic(){
//     std::cout<<"udp started!\n";

//     while(1){
        
//         struct sockaddr_in clientAddress;
//         unsigned int len, n; 
//         len = sizeof(clientAddress);
        
//         n=recvfrom(udpSocket, udpBuffer, 1024, MSG_WAITALL, (struct sockaddr *) &clientAddress,&len);
//         udpBuffer[n]='\0';

//         std::string positionJson=std::string(udpBuffer);
//         std::cout<<positionJson<<"\n";
//         controller.control(positionJson,0);
//         //std::cout<<"ip address : "<<inet_ntoa(clientAddress.sin_addr)<<" port : "<<ntohs(clientAddress.sin_port);
//         printf("  udp message: : %s\n\n\n\n",udpBuffer);
//     }
    
// };

void TcpService::sendPosition(int sock){
    while(1){
        usleep(1000000);

        char charOut[1024]={0};
        std::string stringOut=controller.positions().toStyledString();
        strcpy(charOut,controller.positions().toStyledString().c_str());
        // printf("%s\n",charOut);
        //std::cout<<clientNum<<"\n";
        //std::cout<<stringOut<<"\n";

        for(int i=0;i<clientNum;++i){
            if(alive[i]){
                struct sockaddr_in clientAddress=udpStorage[i];
                std::cout<<"ip address : "<<inet_ntoa(clientAddress.sin_addr)<<" port : "<<ntohs(clientAddress.sin_port)<<"\n";
                // std::cout<<controller.positions().toStyledString()<<"\n";
                sendto(sock,charOut,strlen(charOut),MSG_CONFIRM,(const struct sockaddr *) &clientAddress, sizeof(clientAddress));
            }
        }
    }
}

// void TcpService::setUdp(int portNum){
//     memset(&serverAddress, 0, sizeof(serverAddress));
//     serverAddress.sin_family    = AF_INET;
//     serverAddress.sin_addr.s_addr = INADDR_ANY; 
//     serverAddress.sin_port = htons(portNum); 
//     udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
//     if ( bind(udpSocket, (const struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0 ) 
//     { 
//         std::cout<<"fail to bind udp socket\n";
//     }
// }

//  void TcpService::start(){
//     otherThreads.push_back(std::thread(&TcpService::udpLogic,this));
//     otherThreads.push_back(std::thread(&TcpService::looping,this));
//     while(1){
//         //tcp
//         TcpConnection connectedClient=masterSocket.getConnectedSocket();
//         connectedClients.push_back(connectedClient);
//         alive.push_back(1);
//         threads.push_back(std::thread(&TcpService::clientLogic,this,clientNum));
//         //udp

//         struct sockaddr_in ud;
//         int sock=connectedClient.getTcpSocket();
//         socklen_t serv_len = sizeof(ud);
//         int serv_peer_err = getpeername(sock, (struct sockaddr *)&ud, &serv_len);
//         ud.sin_port=htons(8079);
//         udpStorage.push_back(ud);
//         std::cout<<inet_ntoa(ud.sin_addr)<<" port : "<<ntohs(ud.sin_port)<<" ";
        
//         clientNum++;
//         printf("client %d connected\n",clientNum);
//     }

        
//  }
