#include "TcpConnectionSocket.h"
#include <vector>
#include <netinet/in.h>
#include <sys/socket.h>
#include <iostream>
#include "TcpConnection.h"
TcpConnectionSocket::TcpConnectionSocket(){
    port=-1;
    initialSocketDescriptor=-1;
}

void TcpConnectionSocket::setPort(int portNum){
    port=portNum;
    if((initialSocketDescriptor=socket(AF_INET,SOCK_STREAM,0))==-1){
        std::cout<<"failed to create initial socket\n";
    }
    std::cout<<"success creating initial socket\n";
}

void TcpConnectionSocket::getReady(){
    setSocketOption();
    setAddress();
    bindAddress();
    setSocketStatePassive();
    std::cout<<"socket is ready to get connection...\n";
}

void TcpConnectionSocket::setSocketOption(){
    int opt=1;
    if(setsockopt(initialSocketDescriptor,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt))==-1){
        std::cout<<"failed to set socket option\n";
    }
    std::cout<<"success on setting socket option\n";
}

void TcpConnectionSocket::setAddress(){
    serverAddress.sin_family=AF_INET;
    serverAddress.sin_addr.s_addr=INADDR_ANY;
    serverAddress.sin_port=htons(port);
    std::cout<<"success on setting socket address\n";
}

void TcpConnectionSocket:: bindAddress(){
    if(bind(initialSocketDescriptor, (struct sockaddr*) &serverAddress,sizeof(serverAddress))==-1){
        std::cout<<"failed to bind socket\n";
    }
    std::cout<<"success on binding socket\n";
}

void TcpConnectionSocket::setSocketStatePassive(){
    if(listen(initialSocketDescriptor,16)==-1){
        std::cout<<"failed to set socket to passvie mode\n";
    }
    std::cout<<"success on setting socket to passive mode\n";
}

TcpConnection TcpConnectionSocket::getConnectedSocket(){
    TcpConnection temp=TcpConnection();
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