#pragma once


// CDlgErrorMessage dialog

class CDlgErrorMessage : public CDialog
{
	DECLARE_DYNAMIC(CDlgErrorMessage)

public:
	CDlgErrorMessage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgErrorMessage();

// Dialog Data
	enum { IDD = IDD_ERROR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString strDate;
	CString strTime;
	int nFunc;
	CString strApp;
	int nErrCode;
	int nServ;
	int nX;
	int nY;
	int nValue1;
	int nValue2;
	int nValue3;
	int nValue4;
	int nValue5;
};
