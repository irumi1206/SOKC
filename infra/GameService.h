#ifndef GAMESERVICE_H
#define GAMESERVICE_H
#include "TcpConnectionSocket.h"
#include "TcpService.h"
#include "/home/ubuntu/GameProject/SOKC/jsonParser/JsonParser.h"
#include <queue>
#include <condition_variable>
#include <cstring>
#include <mutex>
#include <unistd.h>
#include <chrono>
#include <ctime>


class GameService{
    public :
        int tcpPort;
        int udpPort;
        TcpService tcpServices[16];
        TcpConnectionSocket connectionSocket;
        std::vector<std::thread> threads;
        std::mutex queueMutex;
        std::queue<std::pair<TcpConnection,Json::Value>> processingQueue;
        std::condition_variable queueCondition;
        std::map<TcpConnection,int> mapConnectionRoom;

        void initialConnectionLogic(int clientNum, TcpConnection tcpConnection);
        void processQueue();
        void showconnectedClients();
        void getUdp();
        void sendTcp(TcpConnection tcpConnection,std::string inp);
        void push(std::pair<TcpConnection,Json::Value> element);
        std::pair<TcpConnection,Json::Value> pop();

        


        //udp
        int udpSocket;
        struct sockaddr_in serverAddress;
        void udpGet();
        void udpSend(int ind);


        GameService();
        void setting(int tcpPort,int udpPort);
        void start();
    
};
#endif