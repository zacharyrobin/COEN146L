#include "TFv2.h"
int get_checksum(Packet packet)
{
	int checksum = 0;
	packet.header.checksum=0;
	char* ptr= (char *)&packet;
	char* ptr2 = ptr;
	srand(time(0));
	if(rand()%2 == 1) //Corrupt if even
	{
		for (ptr; ptr < ptr2 + sizeof(packet.header)+ packet.header.len; ptr++)
		{
			checksum ^= *ptr;
		}
		return checksum;
	}
	return 0;
}
