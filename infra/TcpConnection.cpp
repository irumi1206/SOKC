#include "TcpConnection.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include <stdexcept>

TcpConnection::TcpConnection(){
    tcpSocket=-1;
}

void TcpConnection::setTcpSocket(int socketDescriptor){
    tcpSocket=socketDescriptor;
}

void TcpConnection::in(char* buffer,int len){
    int valread=read(tcpSocket,buffer,len);
    if(valread==0) throw std::runtime_error("disconnected from client");
}

void TcpConnection::out(char* message){

    send(tcpSocket,message,strlen(message),0);
    //std::char_traits<char8_t>::length(message)
}

int TcpConnection::getTcpSocket(){
    return tcpSocket;
}

void TcpConnection::closeSocket(){
    close(tcpSocket);
}
