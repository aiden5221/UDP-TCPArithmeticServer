#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#define MAX 80
#define PORT 8081
#define SA struct sockaddr

void func(int fd)
{
    char buff[MAX];
    char firNum[MAX];
    char secNum[MAX];
    int n,k,j,x,y;
    printf("If you want to disconnect, please enter 'exit'\n");

    // infinite loop created for continuous calculations
    for (;;) {
        bzero(buff, sizeof(buff));
        bzero(firNum, sizeof(firNum));
        bzero(secNum, sizeof(secNum));
        
        n = 0;
        k = 0;
        j = 0;
        
        // collects operation, first num, and second num
        printf("Please enter an operation:");
        while ((buff[n++] = getchar()) != '\n')
            ;
            
        printf("Please enter a value:");
        while ((firNum[k++] = getchar()) != '\n')
                ;
                
        printf("Please another enter a value:");
        while ((secNum[j++] = getchar()) != '\n')
                ;
                
        // checks if a number is being attempted to be divided by 0
        if((strcmp(secNum,'0') == 0) && (strcmp(buff,"div") == 0)){
        	printf("DO NOT DIVIDE A NUMBER BY 0!!");
        }else{
       	write(fd, buff, sizeof(buff));
        	write(fd, firNum, sizeof(firNum));
        	write(fd, secNum, sizeof(secNum));
        }

        	
    
        bzero(buff, sizeof(buff));
        bzero(firNum, sizeof(firNum));
        bzero(secNum, sizeof(secNum));
        
        read(fd, &x, sizeof(x));
        printf("From Server : %d\n", x);
        if (((strncmp(buff, "exit", 4)) == 0) || ((strncmp(secNum, "exit", 4)) == 0) || ((strncmp(firNum, "exit", 4)) == 0)){
            printf("Client Exit...\n");
            break;
        }
    }
}
   
int main()
{
    int fd, connfd;
    struct sockaddr_in addr, cli;
   
    // socket creation
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&addr, sizeof(addr));
   
    // assign the ip and port to socket
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(PORT);
   
    // connect the client socket to server socket
    if (connect(fd, (SA*)&addr, sizeof(addr)) != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");
   
    // calls function to begin calculations
    func(fd);
    close(fd);
}
