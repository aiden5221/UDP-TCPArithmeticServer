#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define PORT	 8080
#define MAXLINE 1024
#define MAX 80



int main() {


	// initialize the required variables
	int fd;
	char final[50];
	struct sockaddr_in servaddr, caddr;
	
	// Create file descriptor for socket
	
	if((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&caddr, 0, sizeof(caddr));
	
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
	
	
	if(bind(fd, (const struct sockaddr *)&servaddr,
			sizeof(servaddr)) < 0 )
	{
		perror("the bind has failed");
		exit(EXIT_FAILURE);
	}
	

	char buffer[MAX];
	char firstNum[MAX];
	char secondNum[MAX];
	

	int j, k, x, y, n, len;

	float result;
	len = sizeof(caddr); 
	// infinite loop to do calculations
	while(1)
	{
	
		bzero(buffer, sizeof(buffer));
		bzero(firstNum, sizeof(firstNum));
		bzero(secondNum, sizeof(secondNum));
		
		j,k,result = 0;
		
		n = recvfrom(fd, (char *)buffer, MAXLINE,
				MSG_WAITALL, ( struct sockaddr *) &caddr,
				&len);
				
		buffer[n] = '\0';
		printf("Client : %s\n", buffer);
		
		x = recvfrom(fd, (char *)firstNum, MAXLINE,
				MSG_WAITALL, ( struct sockaddr *) &caddr,
				&len);
		firstNum[x] = '\0';
		printf("Client : %s\n", firstNum);
		
		y = recvfrom(fd, (char *)secondNum, MAXLINE,
				MSG_WAITALL, ( struct sockaddr *) &caddr,
				&len);
		secondNum[y] = '\0';
		printf("Client : %s\n", secondNum);
		
		//Assign values to variables to work with
		
		j = atoi(firstNum);
		k = atoi(secondNum);
		
		switch(buffer[0])
		{
		
			case '+': result = (float)j + k;
				  sprintf(final, "%f", result);
				  break; 
			case '-': result = (float)j - k; 
				  sprintf(final, "%f", result);
				  break;
			case '*': result = (float)j * k; 
				  sprintf(final, "%f", result);
				  break;
			case '/': 
				// checks if trying to divide by 0
				  if (k==0) 
				  {
				  	strcpy(final,"Sorry, but the denominator can't be zero");
				  }
				  else 
				  {
				  	result = (float)j/k;
				  	sprintf(final, "%f", result);
				  }
				  break;

			default: break;
		
		}
	
	sendto(fd, (const char *)final, strlen(final),
		MSG_CONFIRM, (const struct sockaddr *) &caddr,
			len);
	
	}
	return 0;
}

