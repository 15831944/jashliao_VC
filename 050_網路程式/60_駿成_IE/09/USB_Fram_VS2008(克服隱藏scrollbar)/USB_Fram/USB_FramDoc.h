
// USB_FramDoc.h : CUSB_FramDoc ���O������
//


#pragma once


class CUSB_FramDoc : public CDocument
{
protected: // �ȱq�ǦC�ƫإ�
	CUSB_FramDoc();
	DECLARE_DYNCREATE(CUSB_FramDoc)

// �ݩ�
public:

// �@�~
public:

// �мg
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// �{���X��@
public:
	virtual ~CUSB_FramDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ͪ��T�������禡
protected:
	DECLARE_MESSAGE_MAP()
};


