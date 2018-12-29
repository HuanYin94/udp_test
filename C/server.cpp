// Server side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
  
#define PORT     9999 
#define MAXLINE 1024 

struct header
{
	unsigned short int flag;
	unsigned short int type;
	unsigned short int ID;
	unsigned short int length;
	unsigned int sec;
	unsigned int miliSec;
};

// Driver code 
int main() { 
    int sockfd; 
    char buffer[MAXLINE]; 
    char *hello = "Hello from server"; 
    struct sockaddr_in servaddr, cliaddr; 
      
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
      
    // Filling server information 
    servaddr.sin_family    = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(PORT); 
      
    // Bind the socket with the server address 
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,  
            sizeof(servaddr)) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    int n;
	socklen_t len; 

	header Header_;


	while(true)
	{
		n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
		            MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
		            &len); 
	   
//	 	printf("Test : %c\n", buffer[0]); 

		buffer[n] = '\0'; 
		printf("Client : %s\n", buffer); 

		memcpy(&Header_, buffer, 16);
		
		printf("%04x\n", Header_.miliSec);
	}
//    sendto(sockfd, (const char *)hello, strlen(hello),  
//        MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
//            len); 
//    printf("Hello message sent.\n");  
      
    return 0; 
} 
