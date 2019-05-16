#include "TFv2.h"
int get_cksum(Packet packet)
{
	int i;
	int cksum = 0;
	packet.header.cksum=0;
	char *p= (char *)&packet;
	if(rand()%2 == 1) //Corrupt if even
	{
		for (i=0;i<sizeof(Header)+packet.header.len;i++)
		{
			cksum ^= *p;
			p++;
		}
		return cksum;
	}
	return 0;
}
