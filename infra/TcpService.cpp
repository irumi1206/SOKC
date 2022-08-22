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

 void TcpService::toAll(std::string out){
    char charOut[2048]={0};
    strcpy(charOut,out.c_str());
    for(int i=0;i<connectedClients.size();++i){
        if(!alive[i]) continue;
        TcpConnection currentConnection=connectedClients[i];
        currentConnection.out(charOut);
    }
 }

 void TcpService::toOne(int ind,std::string out){
    if(!alive[ind]) return;
    char charOut[2048]={0};
    strcpy(charOut,out.c_str());
    TcpConnection currentConnection=connectedClients[ind];
    currentConnection.out(charOut);
 }

 void TcpService::toOthers(int ind,std::string out){
    char charOut[2048]={0};
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
    char charOut[2048]={0};
    int size=out.size();
        int index=out["recver"].asInt()-10000;
        toOne(index,out["data"].toStyledString()+"$");
 }

void TcpService::sendWithTimeInternal(Json::Value jsonValue,int id,int second){
    usleep(1000000*second);
    contollerLogic(jsonValue,id);
}

 void TcpService::contollerLogic(Json::Value jsonRequest,int id){
    Json::Value jsonResponse=controller.control(jsonRequest,id);
    std::cout<<jsonResponse.toStyledString()<<std::endl;
    Json::Value One=jsonResponse["toOne"];
    Json::Value All=jsonResponse["toAll"];
    Json::Value Oth=jsonResponse["other"];
    Json::Value Eac=jsonResponse["toEach"];
    Json::Value timer = jsonResponse["timer"];
    if(timer!=null){

        timeIntervalThread.push_back(std::thread(&TcpService::sendWithTimeInternal,this,timer["data"],id,timer["time"].asInt()));
    }

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

void TcpService::sendPosition(int sock){
    //---------------------------------------
    while(1){
        usleep(30000);

        char charOut[1024]={0};
        std::string stringOut=controller.positions().toStyledString();
        strcpy(charOut,controller.positions().toStyledString().c_str());

        for(int i=0;i<clientNum;++i){
            if(alive[i]){
                struct sockaddr_in clientAddress=udpStorage[i];
                //char* en=getenv("positionflag");
                // if(strlen(en)!=0){
                //     std::cout<<"ip address : "<<inet_ntoa(clientAddress.sin_addr)<<" port : "<<ntohs(clientAddress.sin_port)<<"\n";
                //     std::cout<<"/n"<<stringOut<<"/n";
                // }
                sendto(sock,charOut,strlen(charOut),MSG_CONFIRM,(const struct sockaddr *) &clientAddress, sizeof(clientAddress));
            }
        }
    }
    //------------------------------------------------
}
