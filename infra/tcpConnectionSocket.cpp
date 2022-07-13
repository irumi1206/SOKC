#include "tcpConnectionSocket.h"
#include <vector>
#include <netinet/in.h>
#include <sys/socket.h>
#include <iostream>
#include "tcpConnection.h"
tcpConnectionSocket::tcpConnectionSocket(){
    port=-1;
    initialSocketDescriptor=-1;
}

void tcpConnectionSocket::setPort(int portNum){
    port=portNum;
    if((initialSocketDescriptor=socket(AF_INET,SOCK_STREAM,0))==-1){
        std::cout<<"failed to create initial socket\n";
    }
    std::cout<<"success creating initial socket\n";
}

void tcpConnectionSocket::getReady(){
    setSocketOption();
    setAddress();
    bindAddress();
    setSocketStatePassive();
    std::cout<<"socket is ready to get connection...\n";
}

void tcpConnectionSocket::setSocketOption(){
    int opt=1;
    if(setsockopt(initialSocketDescriptor,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt))==-1){
        std::cout<<"failed to set socket option\n";
    }
    std::cout<<"success on setting socket option\n";
}

void tcpConnectionSocket::setAddress(){
    serverAddress.sin_family=AF_INET;
    serverAddress.sin_addr.s_addr=INADDR_ANY;
    serverAddress.sin_port=htons(port);
    std::cout<<"success on setting socket address\n";
}

void tcpConnectionSocket:: bindAddress(){
    if(bind(initialSocketDescriptor, (struct sockaddr*) &serverAddress,sizeof(serverAddress))==-1){
        std::cout<<"failed to bind socket\n";
    }
    std::cout<<"success on binding socket\n";
}

void tcpConnectionSocket::setSocketStatePassive(){
    if(listen(initialSocketDescriptor,16)==-1){
        std::cout<<"failed to set socket to passvie mode\n";
    }
    std::cout<<"success on setting socket to passive mode\n";
}

tcpConnection tcpConnectionSocket::getConnectedSocket(){
    tcpConnection temp=tcpConnection();
    int connectionSocket;
    int serverAddressLen=sizeof(serverAddress);
    if((connectionSocket=accept(initialSocketDescriptor, (struct sockaddr*) &serverAddress, (socklen_t*) &serverAddressLen))==-1){
        std::cout<<"failed to get socket connection\n";
    }
    std::cout<<"success on getting socket connection\n";
    temp.setTcpSocket(connectionSocket);
    connectedSockets.push_back(connectionSocket);

    return temp;
}