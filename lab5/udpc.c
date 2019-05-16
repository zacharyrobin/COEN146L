/*
 * Name: Xinyu Chen
 * Date: 4/24/2019
 * Title: Lab3 - Part 4
 * Description: This program mimic a udp server that send file to the udp server. the file name can be provided in the command line
 */

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
#include "TFv2.h"
Packet createpacket(char*buff, int n);
void client_send(int sockfd,struct sockaddr*address,socklen_t addrlen,Packet packet);
int seq=0;
/********************
 * main
 ********************/
int main(int argc,char* argv[])
{
	FILE *input;										//the input file pointer 
	input=fopen(argv[1],"rb");							//open the file name from the command line
	int sock;											//socket
	struct sockaddr_in server_addr;
	struct hostent *host;
	Packet packet;
	int count;
	char buff[10];

	printf("inside the client main\n");
	
	socklen_t addr_len=sizeof(server_addr);
	host= (struct hostent *) gethostbyname((char *)"127.0.0.1");

	// open socket
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		perror("socket");
		exit(1);
	}

	// set address
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(5012);
	server_addr.sin_addr = *((struct in_addr *)host->h_addr);

	while (1)
	{
		if (!feof(input))
		{
			count=fread(&buff,1,sizeof(buff),input);
		}
		else
		{
			count=0;
		}
		printf("read file successfully, and the count is %d, the context read in is: %s\n\n", count,buff);
		
		if (count==0){
			printf("we send a null file to tell the server to stop\n");
			packet=createpacket("",0);														//if the number of byter is zero, we purposely send a null data
			if(sendto(sock,&packet,sizeof(Packet),0,(struct sockaddr*)&server_addr,addr_len)==-1)
			{
				perror("send a null packet");
				exit(1);
			}			//the send to funtion send sock, a NULL data,in 0 length.
			break;
		}

		packet=createpacket(buff, count);
		client_send(sock,(struct sockaddr*)&server_addr,addr_len,packet);
       	/*sendto(sock, send_data, count, 0,
              (struct sockaddr *)&server_addr, sizeof(struct sockaddr)); //send to server*/
   	}
	close(sock);//close the socket


}


void client_send(int sockfd,struct sockaddr*address,socklen_t addrlen,Packet packet)
{
	Packet recv;
	if(sendto(sockfd,&packet,sizeof(Packet),0,address,addrlen)==-1)
	{
		perror("sendto");
		exit(1);
	}
	printf("send the packet, with context: %s\n", packet.data);
	while (recvfrom(sockfd,&recv,sizeof(Packet),0,NULL,NULL)!=0)
	{
		printf("receive from worked\n");
		if (recv.header.seq_ack==seq)
		{
			printf("inside the if\n");
			break;
		}
		if (sendto(sockfd,&packet,sizeof(Packet),0,address,addrlen)==-1)
		{
			perror("second sendto");
			exit(1);
		}
	}
	seq=!seq;
	printf("the client send finished\n\n\n");
};


Packet createpacket(char *buff, int n)
{
	printf("inside the createpacket function\n");
	Packet packet;
	strcpy(packet.data,buff);
	packet.header.seq_ack=seq;
	packet.header.len=n;
	packet.header.cksum=0;
	packet.header.cksum=get_cksum(packet);
	return (packet);
}
