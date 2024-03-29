#include "GameService.h"

GameService::GameService(){
}

void GameService::setting(int tcpPort, int udpPort){
    this->tcpPort=tcpPort;
    this->udpPort=udpPort;
    connectionSocket.setPort(tcpPort);
    connectionSocket.getReady();
}

void GameService::push(std::pair<TcpConnection,Json::Value> element){
    processingQueue.push(element);
}

std::pair<TcpConnection,Json::Value> GameService::pop(){
    std::pair<TcpConnection,Json::Value> popElement = processingQueue.front();
    processingQueue.pop();
    return popElement;
}

void GameService::processQueue(){

    while(1){

        //std::unique_lock<std::mutex> lock(queueMutex);
        //queueCondition.wait(lock);
        if(processingQueue.empty()) continue;

        std::pair<TcpConnection,Json::Value> popElement=pop();
        TcpConnection tcpConnection=popElement.first;
        Json::Value data=popElement.second;

        std::cout<<"connection : "<<tcpConnection.getTcpSocket()<<" input\n";
        std::cout<<data.toStyledString()<<"\n";
        //header 1 check room to enter
        if(data["Header"].asInt()==1){

            //data
            int roomIndex=data["Content"]["roomId"].asInt()-100;

            //output
            Json::Value out;
            out["Header"]=1;
            if(roomIndex>=0 && roomIndex<=15 && tcpServices[roomIndex].connectedNum<16 && tcpServices[roomIndex].controller.enterAllow){
                out["Content"]["serverConnect"]=1; 
            }
            else{
                out["Content"]["serverConnect"]=-1;
            }
            std::cout<<out.toStyledString()<<"\n";
            sendTcp(tcpConnection,out.toStyledString()+"$");

        }
        else if (data["Header"].asInt()==6){
            if(mapConnectionRoom.find(tcpConnection)==mapConnectionRoom.end()) {
                std::cout<<"already deleted\n";
                continue;
            }
            int currentId=mapConnectionRoom[tcpConnection];
            int kickingId=data["Content"]["id"].asInt();
            int roomIndex=currentId/100-100;
            int currentIndex=currentId%100;
            int kickingIndex=kickingId%100;

            if(kickingId<10000) continue;

            if(tcpServices[roomIndex].alive[kickingIndex]==true){
                tcpServices[roomIndex].contollerLogic(data,kickingId);
                TcpConnection tcpKickingConnection=tcpServices[roomIndex].connectedClients[kickingIndex];
                tcpServices[roomIndex].alive[kickingIndex]=false;
                //tcpKickingConnection.closeSocket();
                tcpServices[roomIndex].connectedNum--;
                mapConnectionRoom.erase(tcpKickingConnection);
            }
            else{
                std::cout<<"info is already erased\n";
                continue;
            }

            // if(mapConnectionRoom.find(tcpConnection)!=mapConnectionRoom.end()){
            //     int id=data["Content"]["id"].asInt();
            //     int roomIndex=id/100-100;
            //     int clientId=id%100;
            //     tcpServices[roomIndex].alive[clientId]=false;
            //     tcpServices[roomIndex].connectedNum--;
            //     Json::Value out;
            //     out["Header"]=6;
            //     out["Content"]["id"]=id;
            //     try{
            //         sendTcp(tcpServices[roomIndex].connectedClients[clientId],out.toStyledString());
            //     }
            //     catch(...){}
            //     tcpServices[roomIndex].connectedClients[clientId].closeSocket();
            //     mapConnectionRoom.erase(tcpConnection);
            //     std::cout<<"\nplayer left, erase info\n";
            //     tcpServices[roomIndex].contollerLogic(data,id);
            // }
            // else{
            //     std::cout<<"\n already exited, but reqeust came to queue\n";
            // }
        }
        //disconnection
        // else if(data["Header"].asInt()==-1){
        //     if(mapConnectionRoom.find(tcpConnection)!=mapConnectionRoom.end()){
        //         int id=mapConnectionRoom[tcpConnection];
        //         int roomIndex=id/100-100;
        //         int clientId=id%100;
        //         tcpServices[roomIndex].alive[clientId]=false;
        //         tcpServices[roomIndex].connectedNum--;
        //         mapConnectionRoom.erase(tcpConnection);
        //         std::cout<<"\nplayer left by diconnection, erase info\n";
        //         tcpServices[roomIndex].contollerLogic(data,id);
        //         tcpConnection.closeSocket();
        //     }
        //     else{
        //         std::cout<<"\n already exited, but reqeust came to queue\n";
        //     }
        // }

        //header 2 entering the room
        else if(data["Header"].asInt()==2){

            if(data["Content"]["name"].asString()==""){
                std::cout<<"null was inputed";
                continue;
            }

            if(mapConnectionRoom.find(tcpConnection)!=mapConnectionRoom.end()) {
                continue;
            }

            int roomIndex=data["Content"]["roomId"].asInt()-100;
            int roomId=roomIndex+100;
            std::string name=data["Content"]["name"].asString();
            int clientIndex=tcpServices[roomIndex].clientNum;
            int id=roomId*100+clientIndex;
            mapConnectionRoom[tcpConnection]=id;
            //tcp
            tcpServices[roomIndex].connectedClients.push_back(tcpConnection);
            tcpServices[roomIndex].alive.push_back(true);
            tcpServices[roomIndex].clientNum++;
            tcpServices[roomIndex].connectedNum++;
            //udp
            int customUdpPort=data["Content"]["udpPort"].asInt();
            struct sockaddr_in udpaddr;
            int sock=tcpConnection.getTcpSocket();
            socklen_t serv_len = sizeof(udpaddr);
            int serv_peer_err = getpeername(sock, (struct sockaddr *)&udpaddr, &serv_len);
            udpaddr.sin_port=htons(customUdpPort);
            tcpServices[roomIndex].udpStorage.push_back(udpaddr);
            //setting & transfer
            tcpServices[roomIndex].contollerLogic(data,id);
        }
        //other header than 1,2
        else{
            if(mapConnectionRoom.find(tcpConnection)==mapConnectionRoom.end()) continue;
            int id=mapConnectionRoom[tcpConnection];
            int roomIndex=id/100-100;
            tcpServices[id/100-100].contollerLogic(data,id);
        }

    }

    std::cout<<"end queueing";
    
}

void GameService::initialConnectionLogic(int clientNum, TcpConnection tcpConnection){

    //validation
    char validationInp[1024]={0};

    try{
        tcpConnection.in(validationInp,1024);
        if(strlen(validationInp)==0) throw std::runtime_error("disconnection error");
        std::string validationString=std::string(validationInp);
        Json::Value validationJson=toJson(validationString);
        Json::Value checking;
        checking["Header"]=0;

        if(validationJson["Header"]==checking["Header"] && validationJson["Content"]["company"].asString()=="PoolC"){
            Json::Value validationResponse;
            validationResponse["Header"]=0;
            validationResponse["Content"]["accpetance"]=1;
            sendTcp(tcpConnection,validationResponse.toStyledString()+"$");
            std::cout<<clientNum<<" client success on validation\n";
        }
        else{
            throw std::runtime_error("validation error");
        }
    }
    catch(...){
        std::cout<<clientNum<<" client disconnected while valiation\n";
        Json::Value validationResponse;
        validationResponse["Header"]=0;
        validationResponse["Content"]["accpetance"]=-1;
        sendTcp(tcpConnection,validationResponse.toStyledString()+"$");
        tcpConnection.closeSocket();
        return;
    }

    //getting recursive input
    bool deleted=false;

    while(1){

        char inBuffer[1024]={0};
        tcpConnection.in(inBuffer,1024);
        

        if(strlen(inBuffer)!=0){

            std::string inp=std::string(inBuffer);
            Json::Value jsons=toJson(inp);
            push(std::make_pair(tcpConnection,jsons));
            if(jsons["Header"].asInt()==6) {
                std::cout<<"deleted head was put to queue\n";
                deleted=true;
            }

        }
        else{
            if(!deleted){
                Json::Value disconnectJson;
                disconnectJson["Header"]=6;
                disconnectJson["Content"]["id"]=mapConnectionRoom[tcpConnection];
                push(std::make_pair(tcpConnection,disconnectJson));
            }
            std::cout<<clientNum<<" client disconnected\n";
            return;
        }
    }
}

void GameService::showconnectedClients(){

}

void GameService::udpGet(){

    char udpBuffer[1024];

    while(1){
        try{
            struct sockaddr_in clientAddress;
            unsigned int len, n; 
            len = sizeof(clientAddress);
            
            n=recvfrom(udpSocket, udpBuffer, 1024, MSG_WAITALL, (struct sockaddr *) &clientAddress,&len);
            udpBuffer[n]='\0';
            std::string positionString=std::string(udpBuffer);
            Json::Value positionJson=toJson(positionString);
            //printf time
            auto start = std::chrono::system_clock::now();
            std::time_t starting = std::chrono::system_clock::to_time_t(start);
            
            std::cout <<"\n"<<std::ctime(&starting)<<"\n";
            std::cout<<"\n"<<positionString<<"\n";
            
            int id=positionJson["Content"]["id"].asInt();
            int roomId=id/100-100;
            tcpServices[roomId].controller.control(positionJson,id);
        } 
        catch(...){}
    }
}
void GameService::udpSend(int ind){
    tcpServices[0].sendPosition(udpSocket);
}

void GameService::start(){

    //udp
    if((udpSocket = socket(AF_INET, SOCK_DGRAM, 0))<0){
        std::cout<<"fail on udp\n";
    }
    serverAddress.sin_family=AF_INET;
    serverAddress.sin_addr.s_addr =INADDR_ANY; 
    serverAddress.sin_port=htons(udpPort);
    if (bind(udpSocket, (const struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0 ) 
    { 
        std::cout<<"fail to bind udp socket\n";
    }
    threads.push_back(std::thread(&GameService::udpGet,this));
    threads.push_back(std::thread(&GameService::udpSend,this,0));

    //tcp
    int num=1;
    threads.push_back(std::thread(&GameService::processQueue,this));
    while(1){
        TcpConnection connectedClient = connectionSocket.getConnectedSocket();
        std::cout<<num<<" client entered\n";
        threads.push_back(std::thread(&GameService::initialConnectionLogic,this,num,connectedClient));
        num++;
    }
    
}

void GameService::sendTcp(TcpConnection tcpConnection,std::string inp){
    char outp[1024];
    strcpy(outp,inp.c_str());
    tcpConnection.out(outp);
}
