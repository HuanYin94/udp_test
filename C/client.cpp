// Client side implementation of UDP client-server model 
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

struct msg
{
	struct header Header;
	
};


  
// Driver code 
int main(int argc, char **argv) {
    int sockfd; 
    char buffer[MAXLINE]; 
    char *hello = "Hello from client"; 
    struct sockaddr_in     servaddr; 
  
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
  
    memset(&servaddr, 0, sizeof(servaddr)); 
      
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = inet_addr("10.12.218.65");
//    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  
    int n, len; 
   	
	unsigned int sec = 1000000;
	
	header Header;
	Header.flag = 0xcece;
	Header.type = 0x0001;
	Header.ID = 0x0001;
	Header.length = 0x0010;
	Header.sec = 0;
	Header.miliSec = 0;
	
	int cnt = 0;
	while(true)
	{	
        // change the id when sending
        Header.ID = cnt + 1;
        memcpy(buffer, &Header, sizeof(Header));

    	sendto(sockfd, (const char *)buffer, strlen(hello), 
    	    MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
    	        sizeof(servaddr)); 

		printf("%d\n", cnt);		
		usleep(sec);
		cnt ++;
	}
//    printf("Hello message sent.\n"); 
          
//    n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
//                MSG_WAITALL, (struct sockaddr *) &servaddr, 
//                &len); 
//    buffer[n] = '\0'; 
//    printf("Server : %s\n", buffer); 
  
    close(sockfd); 
    return 0; 
} 
