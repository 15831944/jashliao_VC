#include <stdio.h>

#define BUFFER_SIZE 102400
#define FALSE 0
#define TRUE 1

typedef unsigned char byte;

unsigned char buffer[BUFFER_SIZE];

int encode(FILE *fp,byte *img,int mx);

int main(int ac,char *av[])
{
	FILE *fp_i,*fp_o;
	int i,c;

	if(ac<3) {
		exit(8);
	}
	fp_i=fopen(av[1],"rb");
	if(fp_i==NULL) {
		fprintf(stderr,"Input File cannot open\n");
		exit(8);
	}
	i=0;
	while(i<BUFFER_SIZE && (c=fgetc(fp_i))!=EOF) {
		buffer[i]=c;
		i++;
	}
	fclose(fp_i);
	fp_o=fopen(av[2],"wb");
	if(fp_o==NULL) {
		fprintf(stderr,"Output File cannot open\n");
		exit(8);
	}
	encode(fp_o,buffer,i);
	fclose(fp_o);
}

int sgni(int x)
{
	if(x<0) return -1;
	if(x>0) return 1;
	return 0;
}

int absi(int x)
{
	if(x<0) return -x;
	return x;
}


int fputLong(long num,FILE *fp)
{
	fputc((num>>24) & 0xff,fp);
	fputc((num>>16) & 0xff,fp);
	fputc((num>>8)  & 0xff,fp);
	fputc((num)     & 0xff,fp);
}

#define N 512
#define NODATA 2100000000

// �N�ҰҾ�
int l_node[2*N],r_node[2*N];
int parent[2*N];

// �N�X�{�W�v���X���ɮ�
int outputHist(int *hist,int nn,FILE *fp)
{
	int i;

	for(i=0;i<nn;i++)
		fputLong(hist[i],fp);
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
		// �Y�S���̤p�Ȫ��ܡA�h����
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

static int bits=0;
static int bdata=0;

int fputBitInit()
{
	bits=0;
	bdata=0;
}

// ��X1�줸
int fputBit(int bit,FILE *fp)
{
	bdata=(bdata<<1)|bit;
	bits++;
	if(bits>=8) {
		fputc(bdata,fp);
		bits=0;
		bdata=0;
	}
}

// �N�h�l���줸��X
int flushBit(FILE *fp)
{
	int i;

	for(i=0;i<7;i++) {
		fputBit(0,fp);
	}
}

// ��X�N�Ұҽs�X
int outputEncode(int val,int end,FILE *fp)
{
	int c;
	int code[100];
	int now,i;
	int s1,a1;
	char buf[100];

	c=0;
	now=val;
	while(1) {
		s1=sgni(parent[now]);
		a1=absi(parent[now]);
		if(s1<0) code[c++]=1;
		else code[c++]=0;
		if(a1==end-1) break;
		now=a1;
	}
	for(i=c-1;i>=0;i--) {
		fputBit(code[i],fp);
	}
}

int encode(FILE *fpo,unsigned char *data,int mx)
{
	int i;
	int x,y;
	int dx,x2;
	int dr,dg,db;
	int at_first;
	int datas;
	int hist[N*2];
	int prev,now;

	dx=1;
	x2=0;
	at_first=TRUE;
	for(i=0;i<N*2;i++) hist[i]=0;
	for(x=0;x<mx;x++) {
		now=data[x];
		if(at_first) {
			at_first=FALSE;
		}
		else {
			dr=now - prev + 255;
			hist[dr]++;
		}
		prev=now;
		x2+=dx;
	}
	fputLong(mx,fpo);
	//for(i=0;i<size;i++) hist[data[i]]++;
	outputHist(hist,N,fpo);

	datas=makeTree(hist,N);
	fputBitInit();
	/*for(i=0;i<size;i++) {
		outputEncode(data[i],datas,fpo);
	}*/
	fputBitInit();
	at_first=TRUE;
	for(x=0;x<mx;x++) {
		now=data[x];
		if(at_first) {
			fputc(now,fpo);
			at_first=FALSE;
		}
		else {
			dr=now - prev + 255;
			outputEncode(dr,datas,fpo);
		}
		prev=now;
	}
	flushBit(fpo);
}
