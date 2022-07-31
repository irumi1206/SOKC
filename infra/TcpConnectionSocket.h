#ifndef TCPCONNECTIONSOCKET_H
#define TCPCONNECTIONSOCKET_H
#include <vector>
#include <netinet/in.h>
#include "TcpConnection.h"

class TcpConnectionSocket{
    private :
        int port;
        int initialSocketDescriptor;
        struct sockaddr_in serverAddress;
        std::vector<int> connectedSockets;
        void setSocketOption();
        void setAddress();
        void bindAddress();
        void setSocketStatePassive();

    public :
        TcpConnectionSocket();
        void setPort(int portNum);
        void getReady();
        TcpConnection getConnectedSocket();


};

#endif