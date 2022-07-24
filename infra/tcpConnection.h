#ifndef GENERALSOCKET_H
#define GENERALSOCKET_H

class tcpConnection{
    private :
        int tcpSocket;

    public :
        tcpConnection();
        void setTcpSocket(int socketDescriptor);
        void in(char* buffer,int len);
        void out(char* message);
};

#endif