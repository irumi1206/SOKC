#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

class TcpConnection{
    private :
        int tcpSocket;

    public :
        TcpConnection();
        int getTcpSocket();
        void setTcpSocket(int socketDescriptor);
        void in(char* buffer,int len);
        void out(char* message);
};

#endif