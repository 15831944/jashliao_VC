#pragma once
#include "Int32.h"

namespace testWinform {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Form1 ���K�n
	///
	/// ĵ�i: �p�G�z�ܧ�o�����O���W�١A�N�����ܧ�P�o�����O�Ҩ̾ڤ��Ҧ� .resx �ɮ����p��
	///          Managed �귽�sĶ���u�㪺 'Resource File Name' �ݩʡC
	///          �_�h�A�o�ǳ]�p�u��
	///          �N�L�k�P�o�Ӫ�����p����a�y�t�Ƹ귽
	///          ���T���ʡC
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: �b���[�J�غc�禡�{���X
			//
		}

	protected:
		/// <summary>
		/// �M������ϥΤ����귽�C
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  textBox1;
	protected: 
			CInt32 n;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::TextBox^  textBox2;

	private:
		/// <summary>
		/// �]�p�u��һݪ��ܼơC
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �����]�p�u��䴩�һݪ���k - �ФŨϥε{���X�s�边�ק�o�Ӥ�k�����e�C
		///
		/// </summary>
		void InitializeComponent(void)
		{
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(37, 12);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(102, 22);
			this->textBox1->TabIndex = 0;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(210, 49);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(68, 35);
			this->button1->TabIndex = 1;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(37, 49);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(102, 22);
			this->textBox2->TabIndex = 2;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(292, 266);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 String ^s1;
				 CInt32 k;
				 n++;
				 k=n+100;
				 s1=n.Int10toInt2(); 
				 textBox1->Text=s1;
			     textBox2->Text=n.IntToString();
			 }
	};
}

