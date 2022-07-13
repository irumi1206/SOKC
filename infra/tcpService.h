#ifndef TCPSERVICE_H
#define TCPSERVICE_H
#include <vector>
#include "tcpConnectionSocket.h"
#include "tcpConnection.h"

class tcpService{
    private :
        int clientNum;
        tcpConnectionSocket masterSocket;
        std::vector<tcpConnection> connectedClients;

    public :
        tcpService();
        void setPort(int portNum);
        void start();
        
        

};




#endif