#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <iostream>
    
#define PORT     8079 
#define MAXLINE 1024 
    
// Driver code 
int main() { 
    int sockfd; 
    char buffer[MAXLINE]; 
    char *hello = "Hello from client"; 
    struct sockaddr_in servaddr;
    struct sockaddr_in clientAddress;
    unsigned int l=sizeof(clientAddress);
    
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
    
    memset(&servaddr, 0, sizeof(servaddr)); 
        
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
        
    unsigned int n, len; 

    while(1){
        char inp[1024]={0};
        char out[1024]={0};
        //char8_t buffer[1024] = { 0 };
        std::cin.getline(inp, 1024);
        sendto(sockfd, inp, strlen(inp), 0,(const struct sockaddr *) &servaddr,  
            sizeof(servaddr));

        int n=recvfrom(sockfd, out, 1024, MSG_WAITALL, (struct sockaddr *) &clientAddress,&l);
        printf("%s\n",out);
        std::cout<<ntohs(clientAddress.sin_port);
        int valread = read(sockfd, out, 1024);
        printf("%s\n", inp);
    }
    return 0; 
}