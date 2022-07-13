#ifndef TCPCONNECTIONSOCKET_H
#define TCPCONNECTIONSOCKET_H
#include <vector>
#include <netinet/in.h>
#include "tcpConnection.h"

class tcpConnectionSocket{
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
        tcpConnectionSocket();
        void setPort(int portNum);
        void getReady();
        tcpConnection getConnectedSocket();


};

#endif