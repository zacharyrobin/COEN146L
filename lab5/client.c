/* 
* Name: Zachary Robin
* Date: 5/2/2019
* Title: Lab5
* Description: To build a Stop and Wait reliable protocol on top of UDP to provide a reliable transport service
*/
/**************************
UDP socket example, client
**************************/
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h> 
#define SIZE 1024

//update
int main (int argc, char *argv[]);

typedef struct
{
	int seq_ack;
	int length;
	int checksum;
} HEADER;
typedef struct
{
	HEADER header;
	char data[10];
} PACKET;

int checksum(PACKET* pkt, size_t size)
{
	(*pkt).header.checksum = 0;
	char* head = (char*)pkt;
	char sum = head[0];
	
	int i;
	for(i=1; i<size; i++)
		sum ^= head[i];
	
	return (int)sum;
}

/********************
*  main
********************/
    int main()
    {
        int sock;
        struct sockaddr_in server_addr;
        struct hostent *host;
        char send_data[SIZE];
        socklen_t addr_len;
        host = (struct hostent *)gethostbyname((char *)"127.0.0.1");
        FILE *fptr1;
        fptr1 = fopen("cat.jpg", "rb");
         if (fptr1 == NULL) 
    { 
        printf("Cannot open file %s \n"); 
        exit(0); 
    } 
        // open socket
        if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
        {
            perror("socket");
            exit(1);
        }
        // set address
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(5000);
        server_addr.sin_addr = *((struct in_addr *)host->h_addr);
        //reading the file 
        
        while (!feof(fptr1))
        {
            int x = fread(send_data, 1, sizeof(send_data), fptr1);
            if ((strcmp(send_data, "q") == 0) || strcmp(send_data, "Q") == 0)
                break;
            else
                sendto(sock, send_data, x, 0,
                       (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
            //send to server
        }
    }
