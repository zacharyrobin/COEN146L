/* 
* Name: Zachary Robin
* Date: 4/25/2019
* Title: Lab4
* Description: 1. To build a concurrent server using TCP/IP socket to accept connections from multiple clients at the same time
*/

/**************************
*  TCP socket example, server
***************************/
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>
#define NCONNS 100
FILE *fileAddress; //global
void *start_routine(void *arg);
pthread_t tids[NCONNS];
/*********************
*  main
*********************/
int main()
{
    // Parent procelsss
    int sock,  true = 1, i;
    struct sockaddr_in server_addr, client_addr;
    int sin_size;
    //Open socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Socket");
        exit(1);
    }
    //Set address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5000);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    //Bind socket
   if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("Unable to bind");
        exit(1);
    }
    printf("\nTCPServer Waiting for client on port 5000: \t");
    //Listen
    if (listen(sock, 5) == -1)
    {
        perror("Listen");
        exit(1);
    }

    for(i=0; i <= NCONNS ; i++){
        int *CONN = malloc(sizeof(int));
        *CONN = accept(sock, (struct sockaddr *)&client_addr, (socklen_t *)&sin_size);
        pthread_create(&tids, NULL, start_routine, CONN);    
    }
    fclose(fileAddress);
     close(sock);
    return 0;
}

void *start_routine(void *arg){
    char  recv_data[1024];
    int bytes_recieved;
    int connfd = *(int*)arg;
    while((bytes_recieved = recv(connfd, recv_data, 1024, 0)) > 0)
    {    
            printf("\t\t\t\t Server: ");
            // write(connected, "", 7);
            // Open global file for writing 
            fileAddress = fopen("out.txt", "a");

            if (!feof(fileAddress))
            {
                fwrite(recv_data,1, bytes_recieved, fileAddress);
            }
            else
            {
                printf("\n Unable to Create or Open the Sample.txt File");
            }
            fflush(fileAddress);  //changed to fflush
        }
         
    }
  


