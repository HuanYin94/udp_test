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
#define BYTENUM 16

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
    float mag_pose_x;
    float mag_pose_y;
    float mag_heading;
    float wheel_velocity_FL;
    float wheel_velocity_FR;
    float wheel_velocity_RL;
    float wheel_velocity_RR;
    float wheel_angle_FL;
    float wheel_angle_FR;
    float wheel_angle_RL;
    float wheel_angle_RR;
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
     	
	unsigned int sec = 1000000;
	
    msg Message;

    Message.Header.flag = 0xcece;
    Message.Header.type = 0x0001;
    Message.Header.ID = 0x0000;
    Message.Header.length = 16;
    Message.Header.sec = 0x1111;
    Message.Header.miliSec = 0x2222;

    Message.mag_pose_x = 0;
    Message.mag_pose_y = 0;
    Message.mag_heading = 0;

    Message.wheel_velocity_FL = 0;
    Message.wheel_velocity_FR = 0;
    Message.wheel_velocity_RL = 0;
    Message.wheel_velocity_RR = 0;

    Message.wheel_angle_FL = 0;
    Message.wheel_angle_FR = 0;
    Message.wheel_angle_RL = 0;
    Message.wheel_angle_RR = 0;

	int cnt = 0;
	while(true)
	{	
        // change the id when sending. ID ++
        Header.ID = cnt + 1;
        memcpy(buffer, &Header, BYTENUM);

    	sendto(sockfd, (const char *)buffer, strlen(hello), 
    	    MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
    	        sizeof(servaddr)); 

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
