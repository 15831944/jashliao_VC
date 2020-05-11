#include <stdlib.h>
#include <stdio.h>


#include <pcap.h>



int main()
{
	pcap_if_t *alldevs;//����һ������ӿڵ�һ���ڵ�
	pcap_if_t *d;
	int i=0,inum=0,j;
	char errbuf[PCAP_ERRBUF_SIZE];
	u_char packet[60];
	pcap_t *adhandle;


	/* ����豸�б� */
	if (pcap_findalldevs(&alldevs, errbuf) == -1)
	{
		fprintf(stderr,"Error in pcap_findalldevs: %s\n", errbuf);
		exit(1);
	}

	/* ��ӡ�б� */
	for(d= alldevs; d != NULL; d= d->next)
	{
		printf("%d. %s", ++i, d->name);
		if (d->description)
		printf(" (%s)\n", d->description);
		else
		printf(" (No description available)\n");
	}

	if (i == 0)
	{
		printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
		return 0;
	}
	printf("Enter the interface number (1-%d):",i);
	scanf("%d", &inum);
	/* ��ת��ѡ�е������� */
	for(d=alldevs, i=0; i< inum-1 ;d=d->next, i++);
	/* �������� */
	if ( (adhandle= pcap_open_live(d->name, // �豸��
								65536, // Ҫ��׽�����ݰ��Ĳ��� 
										// 65535��֤�ܲ��񵽲�ͬ������·���ϵ�ÿ�����ݰ���ȫ������
										1, // ����ģʽ
								1000, // ��ȡ��ʱʱ�� 
								errbuf // ���󻺳��
								) ) == NULL)
	{
		fprintf(stderr,"\nUnable to open the adapter. %s is not supported by WinPcap\n", d->name);
		/* �ͷ��豸�б� */
		pcap_freealldevs(alldevs);
		return -1;
	}

	/* Ŀ�ĵ�ַ��MAC��ַ*/
	printf("��������շ���MAC��ַ����FF:FF:FF:FF:FF:FF��\n");
	scanf("%2x:%2x:%2x:%2x:%2x:%2x",&packet[0],&packet[1],&packet[2],&packet[3],&packet[4],&packet[5]);
	
	/* ����MACԴ��ַ */
	printf("������Դmac��ַ��");
	scanf("%2x:%2x:%2x:%2x:%2x:%2x",&packet[6],&packet[7],&packet[8],&packet[9],&packet[10],&packet[11]);
	
// 	packet[6]=0x00;
// 	packet[7]=0x1b;
// 	packet[8]=0Xfc;
// 	packet[9]=0xc2;
// 	packet[10]=0X1b;
// 	packet[11]=0xb6;

	/* ֡���� */
	packet[12]=0x08;
	packet[13]=0x06;
	/* Ӳ������ */
	packet[14]=0x00;
	packet[15]=0x01;
	/* Э������ */
	packet[16]=0x08;
	packet[17]=0x00;
	/*Ӳ����С*/
	packet[18]=0x06;
	/*Э���С*/
	packet[19]=0x04;
	/* ARP�ظ�Э�� */
	packet[20]=0x00;
	packet[21]=0x02;
	/*���ͷ�MAC��ַ*/
	for(i=22;i<28;i++)
	{
		packet[i]=packet[i-16];
	}
	/*���ͷ�IP��ַ*/
	printf("���ͷ�IP��");
	scanf("%d.%d.%d.%d",&packet[28],&packet[29],&packet[30],&packet[31]);
// 	packet[28]=0xc0;
// 	packet[29]=0xa8;
// 	packet[30]=0x01;
// 	packet[31]=0x6c;
	/*���շ�MAC��ַ*/
	for(i=32;i<38;i++)
	{
		packet[i]=packet[i-32];
	}
	/*���շ�IP��ַ*/
	printf("������Ŀ���ip��ַ\n");
	scanf("%d.%d.%d.%d",&packet[38],&packet[39],&packet[40],&packet[41]);
	/*�������*/
	for(j=42;j<60;j++)
	{
		packet[j]=0x00;
	}


/*�������ݰ� */
/*if (pcap_sendpacket(adhandle, // Adapter
packet, // buffer with the packet
60 // size
) != 0)
{
fprintf(stderr,"\nError sending the packet: \n", pcap_geterr(adhandle));
return 3;
}*/
	int send_num=100;
	i=0;
	printf("���������������(�����밴��100����)\n");
	scanf("%d",send_num);
	while(i<send_num)
	{
		pcap_sendpacket(adhandle, packet,60 );
		printf("OK\n");
		i++;
	} 
	pcap_close(adhandle); 
	return 0;
}
