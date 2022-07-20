#ifndef GENERALSOCKET_H
#define GENERALSOCKET_H

class tcpConnection{
    private :
        int tcpSocket;

    public :
        tcpConnection();
        void setTcpSocket(int socketDescriptor);
        void in(char8_t* buffer,int len);
        void out(char8_t* message);
};

#endif