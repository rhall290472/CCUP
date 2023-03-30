// DlgErrorMessage.cpp : implementation file
//

#include "stdafx.h"
#include "CCU History.h"
#include "DlgErrorMessage.h"


// CDlgErrorMessage dialog

IMPLEMENT_DYNAMIC(CDlgErrorMessage, CDialog)

CDlgErrorMessage::CDlgErrorMessage(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgErrorMessage::IDD, pParent)
	, strDate(_T(""))
	, strTime(_T(""))
	, nFunc(0)
	, strApp(_T(""))
	, nErrCode(0)
	, nServ(0)
	, nX(0)
	, nY(0)
	, nValue1(0)
	, nValue2(0)
	, nValue3(0)
	, nValue4(0)
	, nValue5(0)
{

}

CDlgErrorMessage::~CDlgErrorMessage()
{
}

void CDlgErrorMessage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, strDate);
	DDX_Text(pDX, IDC_EDIT2, strTime);
	DDX_Text(pDX, IDC_EDIT3, nFunc);
	DDX_Text(pDX, IDC_EDIT4, strApp);
	DDX_Text(pDX, IDC_EDIT5, nErrCode);
	DDX_Text(pDX, IDC_EDIT6, nServ);
	DDX_Text(pDX, IDC_EDIT7, nX);
	DDX_Text(pDX, IDC_EDIT8, nY);
	DDX_Text(pDX, IDC_EDIT9, nValue1);
	DDX_Text(pDX, IDC_EDIT10, nValue2);
	DDX_Text(pDX, IDC_EDIT11, nValue3);
	DDX_Text(pDX, IDC_EDIT12, nValue4);
	DDX_Text(pDX, IDC_EDIT13, nValue5);
}


BEGIN_MESSAGE_MAP(CDlgErrorMessage, CDialog)
END_MESSAGE_MAP()


// CDlgErrorMessage message handlers
