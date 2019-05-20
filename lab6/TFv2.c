#include "TFv2.h"
int get_checksum(Packet packet)
{
	int i;
	int checksum = 0;
	packet.header.checksum=0;
	char *p= (char *)&packet;
	if(rand()%2 == 1) //Corrupt if even
	{
		for (i=0;i<sizeof(Header)+packet.header.len;i++)
		{
			checksum ^= *p;
			p++;
		}
		return checksum;
	}
	return 0;
}
