#include "TcpService.h"
#include <thread>
#include <cstdio>
#include <string>
#include <cstring>
#include "/home/ubuntu/GameProject/SOKC/Controller.h"
//#include <jsoncpp/json/json.h>

 TcpService::TcpService(){
     clientNum=0;
 };

 void TcpService::setPort(int portNum){
    masterSocket.setPort(portNum);
    masterSocket.getReady();
 }

 void TcpService::toAll(std::string out){
    char charOut[1024]={0};
    strcpy(charOut,out.c_str());
    for(int i=0;i<connectedClients.size();++i){
        if(alive[i]==0) continue;
        TcpConnection currentConnection=connectedClients[i];
        currentConnection.out(charOut);
    }
 }

 void TcpService::toOne(int ind,std::string out){
    if(alive[ind]==0) return;
    char charOut[1024]={0};
    strcpy(charOut,out.c_str());
    TcpConnection currentConnection=connectedClients[ind];
    currentConnection.out(charOut);
 }

 void TcpService::toOthers(int ind,std::string out){
    char charOut[1024]={0};
    strcpy(charOut,out.c_str());
    for(int i=0;i<connectedClients.size();++i){
        if(alive[i]==0 ||i==ind) continue;
        TcpConnection currentConnection=connectedClients[i];
        currentConnection.out(charOut);
    }
 }

 void TcpService::clientLogic(int clientIndex){
    const char* response="server received message";

    TcpConnection currentTcpConnection=connectedClients[clientIndex];
    while(1){
        char buffer[1024]={0};
        currentTcpConnection.in(buffer,1024);
        try{
            // //==추 가==//
            Json::Value temp=controller.control(std::string(buffer));
            std::cout<<std::string(buffer)<<std::endl;
            std::cout<<temp.toStyledString()<<std::endl;
            Json::Value One=temp["toOne"];
            Json::Value All=temp["toAll"];
            Json::Value Oth=temp["other"];
            if(One!=null){
                toOne(clientIndex,One.toStyledString());
            }
            if(All!=null){
                toAll(All.toStyledString());
            }
            if(Oth!=null){
                toOthers(clientIndex,Oth.toStyledString());
            }
            if(temp["other2"]!=null){
                toOthers(clientIndex,temp["other2"].toStyledString());
            }
            // //==여기까지==//
            printf("client %d : %s\n", clientNum, buffer);
            
        }
        catch(...){
            printf("client %d disconnected\n",clientIndex+1);
            alive[clientIndex]=0;
            return;
        }
    }
}

 void TcpService::start(){
    while(1){
        TcpConnection connectedClient=masterSocket.getConnectedSocket();
        connectedClients.push_back(connectedClient);
        alive.push_back(1);
        threads.push_back(std::thread(&TcpService::clientLogic,this,clientNum));
        clientNum++;
        printf("client %d connected\n",clientNum);
    }

        
 }
