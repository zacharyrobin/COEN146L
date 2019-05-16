#ifndef TFv2_h
#define TFv2_h

typedef struct
{
	Header header;
	char data[10];
}Packet;

typedef struct
{	
	int seq_ack;
	int len;
	int cksum;
}Header;


int get_cksum(Packet);
#endif 
