#ifndef TFv2_h
#define TFv2_h

typedef struct
{	
	int seq_ack;
	int len;
	int checksum;
}Header;

typedef struct
{
	Header header;
	char data[10];
}Packet;


int get_checksum(Packet);
#endif 
