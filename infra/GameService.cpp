#include "GameService.h"

GameService::GameService(){
}

void GameService::setting(int tcpPort, int udpPort){
    this->tcpPort=tcpPort;
    this->udpPort=udpPort;
    connectionSocket.setPort(tcpPort);
    connectionSocket.getReady();
}

void GameService::processQueue(){

    while(1){

        //std::unique_lock<std::mutex> lock(queueMutex);
        //queueCondition.wait(lock);
        if(processingQueue.empty()) continue;

        TcpConnection tcpConnection=processingQueue.front().first;
        Json::Value data=processingQueue.front().second;

        try{
            std::cout<<"\ninput\n";
            std::cout<<"\n"<<data.toStyledString()<<"\n";
            std::cout<<"\noutput\n";
            //header 1 check room to enter
            if(data["Header"].asInt()==1){

                //data
                int roomIndex=data["Content"]["roomId"].asInt()-100;

                //output
                Json::Value out;
                out["Header"]=1;
                if(roomIndex>=0 && roomIndex<=15 && tcpServices[roomIndex].connectedNum<16){
                    out["Content"]["serverConnect"]=1; 
                }
                else{
                    out["Content"]["serverConnect"]=-1;
                }
                std::cout<<"\n"<<out.toStyledString()<<"\n";
                sendTcp(tcpConnection,out.toStyledString()+"$");

            }
            else if (data["Header"].asInt()==6){
                if(mapConnectionRoom.find(tcpConnection)!=mapConnectionRoom.end()){
                    int id=mapConnectionRoom[tcpConnection];
                    int roomIndex=id/100-100;
                    int clientId=id%100;
                    tcpServices[roomIndex].alive[clientId]=false;
                    tcpServices[roomIndex].connectedNum--;
                    mapConnectionRoom.erase(tcpConnection);
                    std::cout<<"\nplayer left by itself, erase info\n";
                    tcpServices[roomIndex].contollerLogic(data,id);
                    tcpConnection.closeSocket();
                }
            }
            //disconnection
            else if(data["Header"].asInt()==-1){
                if(mapConnectionRoom.find(tcpConnection)!=mapConnectionRoom.end()){
                    int id=mapConnectionRoom[tcpConnection];
                    int roomIndex=id/100-100;
                    int clientId=id%100;
                    tcpServices[roomIndex].alive[clientId]=false;
                    tcpServices[roomIndex].connectedNum--;
                    mapConnectionRoom.erase(tcpConnection);
                    std::cout<<"\nplayer left by diconnection, erase info\n";
                    tcpServices[roomIndex].contollerLogic(data,id);
                    tcpConnection.closeSocket();
                }
            }
            else{

                //header 2 entering the room
                if(data["Header"].asInt()==2){
                    int roomIndex=data["Content"]["roomId"].asInt()-100;
                    int roomId=roomIndex+100;
                    std::string name=data["Content"]["name"].asString();
                    int clientIndex=tcpServices[roomIndex].clientNum;
                    int id=roomId*100+clientIndex;
                    mapConnectionRoom[tcpConnection]=id;
                    //tcp
                    tcpServices[roomIndex].connectedClients.push_back(tcpConnection);
                    tcpServices[roomIndex].alive.push_back(true);
                    //udp
                    struct sockaddr_in udpaddr;
                    int sock=tcpConnection.getTcpSocket();
                    socklen_t serv_len = sizeof(udpaddr);
                    int serv_peer_err = getpeername(sock, (struct sockaddr *)&udpaddr, &serv_len);
                    udpaddr.sin_port=htons(udpPort);
                    tcpServices[roomIndex].udpStorage.push_back(udpaddr);
                    //setting & transfer
                    tcpServices[roomIndex].clientNum++;
                    tcpServices[roomIndex].connectedNum++;
                    tcpServices[roomIndex].contollerLogic(data,id);
                }
                //other header than 1,2
                else{
                    int id=mapConnectionRoom[tcpConnection];
                    int roomIndex=id/100-100;
                    tcpServices[id/100-100].contollerLogic(data,id);
                }
            }
        }
        catch(...){
            std::cout<<"\nsomething is wrong with request, disconnect...\n";
            tcpConnection.closeSocket();
        }

        processingQueue.pop();

    }

    std::cout<<"end queueing";
    
}

void GameService::initialConnectionLogic(int clientNum, TcpConnection tcpConnection){

    //validation
    char validationInp[1024]={0};

    try{
        tcpConnection.in(validationInp,1024);
        std::string validationString=std::string(validationInp);
        Json::Value validationJson=toJson(validationString);
        Json::Value checking;
        checking["Header"]=0;

        if(validationJson["Header"]==checking["Header"] && validationJson["Content"]["company"].asString()=="PoolC"){
            Json::Value validationResponse;
            validationResponse["Header"]=0;
            validationResponse["Content"]["accpetance"]=1;
            sendTcp(tcpConnection,validationResponse.toStyledString()+"$");
            // char validationOut[1024]={0};
            // strcpy(validationOut,validationResponse.toStyledString().c_str());
            // tcpConnection.out(validationOut);
            std::cout<<clientNum<<" client success on validation\n";
        }
        else{
            throw std::runtime_error("validation error");
        }
    }
    catch(...){
        std::cout<<clientNum<<" client disconnected due to validation error\n";
        Json::Value validationResponse;
        validationResponse["Header"]=0;
        validationResponse["Content"]["accpetance"]=-1;
        sendTcp(tcpConnection,validationResponse.toStyledString()+"$");
        tcpConnection.closeSocket();
        return;
    }

    //getting recursive input

    while(1){
        Json::Value jsons;

        try{
            char inBuffer[1024]={0};
            tcpConnection.in(inBuffer,1024);
            //std::cout<<"\n\nclient "<<clientNum<<" ?input\n";
            //std::cout<<inBuffer<<"\n\n";
            std::string inp=std::string(inBuffer);
            jsons=toJson(inp);
            if(strlen(inBuffer)==0) throw std::runtime_error("validation error");
            processingQueue.push(std::make_pair(tcpConnection,jsons));
        }
        catch(...){
            Json::Value disconnectJson;
            disconnectJson["Header"]=-1;
            processingQueue.push(std::make_pair(tcpConnection,disconnectJson));
            std::cout<<clientNum<<" client disconnected\n";
            tcpConnection.closeSocket();
            return;
        }

        
        //std::unique_lock<std::mutex> lock(queueMutex);
        //queueCondition.notify_one();
        
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
            std::cout <<std::ctime(&starting)<<"\n";
            
            int id=positionJson["Content"]["id"].asInt();
            int roomId=id/100-100;
            //std::cout<<positionString<<"\n";
            tcpServices[roomId].controller.control(positionString,id);
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
