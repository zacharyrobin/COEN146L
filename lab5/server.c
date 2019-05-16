/* 
* Name: Zachary Robin
* Date: 5/2/2019
* Title: Lab5
* Description: To build a Stop and Wait reliable protocol on top of UDP to provide a reliable transport service
*/
/**************************
UDP socket example, server
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
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h> 
#define SIZE 1024



int main (int, char *[]); 

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
/*********************
*  main
*********************/
int main()
{
    int sock;
    int bytes_read;
    char recv_data[SIZE];
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len;

    //Open socket
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("Socket");
        exit(1);
    }
    // Set address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5000);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    //Bind socket to address
    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("Bind");
        exit(1);
    }
    addr_len = sizeof(struct sockaddr);
    printf("\t\t\t\t\t\t\nUDPServer Waiting for client on port 5000\n");
    while (1)
    {
        //Receive from client
        bytes_read = recvfrom(sock, recv_data, SIZE, 0, (struct sockaddr *)&client_addr, &addr_len);
        recv_data[bytes_read] = '\0';
printf("\t\t\t\t Server: The Client (%s , %d) said: ", inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
printf("%s\n", recv_data);

        // Open another file for writing 
        FILE *fileAddress;
        fileAddress = fopen("out.jpg", "wb");

        if (!feof(fileAddress))
        {
           	 fwrite(recv_data,1, bytes_read, fileAddress);
        }
        else
        {
            printf("\n Unable to Create or Open the Sample.txt File");
        }
         fclose(fileAddress);   
                
    }
    return 0;
}

