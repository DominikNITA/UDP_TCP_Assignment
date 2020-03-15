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

void main(int argc, char *argv[]) 
{ 
    //sockfd le descripteur de socket 
    int sockfd; 
    //structure d'adresse du serveur 
    struct sockaddr_in serverAddr; 
    //pointeur vers la structure descriptive de machine(hostent) 
    struct hostent *he; 
    //zone dans mémoire destinée à accueillir la chaine entrée au clavier 
    char buffer[SIZE]; 
    //taille de la chaine à envoyer 
    socklen_t addr_size;  
    //Vérification des arguments 
    if(argc != 2) 
    { 
        printf("Usage: %s <hostname>\n", argv[0]); 
        exit(0); 
    }
    //ouverture du socket client UDP 
    sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
    //Récupérer l'adresse IP du serveur à partir de son nom passé en ligne de commande(argument/parametre) 
    if ( (he = gethostbyname(argv[1]) ) == NULL ) 
    { 
        exit(1); /* error */ 
    } 
    //Remplir la structure d'adresse du serveur 
    memset(&serverAddr, '\0', sizeof(serverAddr)); 
    serverAddr.sin_family = AF_INET; 
    serverAddr.sin_port = htons(PORT); 
    memcpy(&serverAddr.sin_addr, he->h_addr_list[0], he->h_length); 
    //Lire une ligne de l'entrée du serveur 
    printf("Type the message: "); 
    fgets(buffer, SIZE, stdin); 
    //Envoyer la chaine lue au serveur 
    sendto(sockfd, buffer, SIZE, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr)); 
    printf("Message sent: %s", buffer);  
} 
