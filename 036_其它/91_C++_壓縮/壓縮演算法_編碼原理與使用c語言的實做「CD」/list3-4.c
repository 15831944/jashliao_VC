#include <stdio.h>

char mbuf[256];
int readmode;

#define FALSE 0
#define TRUE 1

#define N 512
#define NODATA 2100000000

// �N�ҰҾ�
int l_node[2*N],r_node[2*N];
int parent[2*N];

int readData(unsigned char *data,int len,FILE *fp)
{
   return fread(data,len,sizeof(char),fp);
}

int getLong(FILE *fp)
{
	unsigned char buf[16];

	readData(buf,4,fp);
	return (buf[0]<<24) |(buf[1]<<16) | (buf[2]<<8) | buf[3];
}

// -------------------------------------------------------

// -------------------------------------------------------

static int bits=0;
static int bdata=0;

int fgetBitInit()
{
	bits=0;
	bdata=0;
}

// ��X1�줸
int fgetBit(FILE *fp)
{
	unsigned char bbuf;
	char buf[100];
	int val;

	if(bits==0) {
		readData(&bbuf,1,fp);
		bdata=bbuf;
	}
	val=(bdata>>7)&1;
	bdata=(bdata<<1) & 0xff;
	bits++;
	if(bits>=8) {
		bits=0;
		bdata=0;
	}
	return val;
}

// �q�ɮר��o�X�{�W�v��
int inputHist(int *hist,int nn,FILE *fp)
{
	int i;

	for(i=0;i<nn;i++)
		hist[i]=getLong(fp);
	return TRUE;
}

// �D�X�W�v�̤p�����
int getMin2(int *hist,int hm,int *d1,int *d2)
{
	int i;
	int min;

	min=NODATA-1;
	*d1= *d2= -100;
	for(i=0;i<hm;i++) {
		if(hist[i]<min) {
			*d1=i;
			min=hist[i];
		}
	}
	min=NODATA-1;
	for(i=0;i<hm;i++) {
		if(i!=(*d1) && hist[i]<min) {
			*d2=i;
			min=hist[i];
		}
	}
}

int makeTree(int *hist,int n)
{
	int hm_data;
	int d1,d2,i;

	hm_data=n;

	// ��l��
	for(i=0;i<2+N;i++) {
		l_node[i]=r_node[i]=parent[i]=0;
	}

	while(1) {
		// �D�X�W�v�̤p�����
		getMin2(hist,hm_data,&d1,&d2);
		// �Y�S���̤p�ȡA�h����
		if(d1<0 || d2<0) break;
		l_node[hm_data]=d1;
		r_node[hm_data]=d2;
		parent[d1]=hm_data;
		parent[d2]= -hm_data;
		hist[hm_data]=hist[d1]+hist[d2];
		hist[d1]=NODATA;
		hist[d2]=NODATA;
		hm_data++;
	}
	return hm_data;
}

int getValue(int datas,FILE *fp)
{
	int rt,bit;

	rt=datas-1;
	while(rt>=N) {
		bit=fgetBit(fp);
		if(bit==0) {
			rt=l_node[rt];
		}
		else {
			rt=r_node[rt];
		}
	}
	return rt;
}

long decode(FILE *fp,int mx)
{
	int x,y;
	int dx,x2;
	int dr,dg,db;
	int at_first;
	int now;
	int datas;

	int hist[2*N];

	inputHist(hist,N,fp);

	datas=makeTree(hist,N);

	fgetBitInit();
	dx=1;
	x2=0;
	at_first=TRUE;
	for(x=0;x<mx;x++) {
		if(at_first) {
			now=fgetc(fp);
			at_first=FALSE;
		}
		else {
			dr=getValue(datas,fp)-255;
			(now)+=dr;
		}
		printf("%c",now);
	}
}

int main(int ac,char *av[])
{
	FILE *fp;
	int c,size;

	if ((fp = fopen(av[1],"rb"))==NULL)
		return 6;
	size=getLong(fp);
	decode(fp,size);
}
