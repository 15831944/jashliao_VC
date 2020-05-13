//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include <string>
using namespace std;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

class Base
{
    public:
        string ImageFileName;
        char *Buffer;
        int Row,Col;

    public:
        Base(string argName)
        {
            ImageFileName=argName;
            Buffer=NULL;
            Row=0;Col=0;
        }
        void Algorithm()
        {
            //this->LoadImage();  //Algorithm�|�ھ�this�M�w�I�s���@��LoadImage
            LoadImage();
            //�� Buffer �@�ʧ@
        }
        //��l������LoadImage
        virtual void LoadImage(){};
};

TForm1 *Form1;
class bcbBase:public Base
{
    public:
        Classes::TComponent* Owner;
    public:
        bcbBase(Classes::TComponent* AOwner,string FileName)
         :Base(FileName)
        {
            Owner=AOwner;
        }
        //BCB������ Load Image
        void LoadImage()
        {
            TImage *Image=new TImage(Owner);
            AnsiString ansiStr=String(ImageFileName.c_str());
            Image->Picture->LoadFromFile(ansiStr);
            Form1->Image1->Picture->LoadFromFile(ansiStr);
            Row=Image->Picture->Height;
            Col=Image->Picture->Width;

            Buffer=new char[Row*Col];

            
            //�N��ƶ�JBuffer��
            long int offset;
            for(int y=0;y<Row;y++)
                for(int x=0;x<Col;x++)
                {
                    offset=y*Col+x;
                    *(Buffer+offset)=GetRValue(Image->Picture->Bitmap->Canvas->Pixels[x][y]);
                }

        }
};

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button1Click(TObject *Sender)
{
    bcbBase bcbObject(this,"test01.bmp");
    bcbObject.Algorithm();
}
//---------------------------------------------------------------------------
