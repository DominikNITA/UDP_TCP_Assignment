#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <netdb.h>  
#define PORT 9600 
#define SIZE 100 
void main(int argc, char **argv) 
{ 
    //sockfd le descripteur du serveur 
    int sockfd; 
    //structure d'adresse locale du serveur(serverAddr) et du client(clientAddr) 
    struct sockaddr_in serverAddr, clientAddr; 
    //taille de l'adresse du client 
    socklen_t addr_size; 
    char buffer[SIZE];  
    //Ouvrir le socket du serveur 
    sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
    //Remplir la structure d'adresse locale du serveur 
        memset(&serverAddr, '\0', sizeof(serverAddr)); 
        //la famille d'adresse 
        serverAddr.sin_family = AF_INET; 
        //le port 
        serverAddr.sin_port = htons(PORT); 
        //l'adresse IP 
        serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    //Spécifier(bind) l'adresse locale di socket du serveur 
    bind(sockfd, (struct sockaddr*)& serverAddr, sizeof(serverAddr)); 
    addr_size = sizeof(clientAddr); 
    while(1) 
    { 
        recvfrom(sockfd, buffer, SIZE, 0, (struct sockaddr*)& clientAddr, &addr_size); 
        printf("Message received: %s", buffer); 
    } 
} 
