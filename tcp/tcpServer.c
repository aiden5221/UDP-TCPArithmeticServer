#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr
   
// Function designed for chat between client and server.
void func(int fd)
{
    char buff[MAX];
    char firNum[MAX];
    char secNum[MAX];
    int n,k,j,w,x,y;
    
    // infinite loop for chat
    for (;;) {
    	n,k,j,w,x,y = 0;
        bzero(buff, MAX);
        bzero(firNum, MAX);
        bzero(secNum, MAX);
   	
        // read the message from client and copy it in buffer
        read(fd, buff, sizeof(buff));
        read(fd, firNum, sizeof(firNum));
        read(fd, secNum, sizeof(secNum));
        
	x = atoi(firNum);
    	y = atoi(secNum);

    // switch case used to determine the operation type
	switch (buff[0]){
		case 'a':
			w=x+y;
			break;
		case 's':
			w=x-y;
			break;
		case 'd':
			w = (y==0) ? :x/y;
			
			break;
		case 'm':
			w=x*y;
			break;
		default:
			break;
	}      

        printf("Operation:%s\n", buff);
        printf("First Number:%s\n", firNum);
        printf("Second Number:%s\n", secNum);
        printf("Result:%d\n",w);
        
        bzero(buff, MAX);
        bzero(firNum, MAX);
        bzero(secNum, MAX);

        write(fd, &w, sizeof(w));
   
        if (strncmp("exit", buff, 4) == 0) {
            printf("Server Exit...\n");
            break;
        }
    }
}
   

int main()
{
    int fd, connfd, len;
    struct sockaddr_in addr, cli;
   
    // socket create and verification
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&addr, sizeof(addr));
   
    // Assign ip and port
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(PORT);
   
    // Bind to new socket
    if ((bind(fd, (SA*)&addr, sizeof(addr))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");
   
    // Server is now ready
    if ((listen(fd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
    len = sizeof(cli);
   
    // Accept data from client and do verification
    connfd = accept(fd, (SA*)&cli, &len);
    if (connfd < 0) {
        printf("server accept failed...\n");
        exit(0);
    }
    else
        printf("server accept the client...\n");
   
    // calls function to begin calculations
    func(connfd);
    close(fd);
}
