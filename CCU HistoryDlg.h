
// CCU HistoryDlg.h : header file
//

#pragma once

#include "ColorListBox.h"
#include "afxwin.h"

class IDSErrroMessage : public CObject
{
public:
	CString	strDate;
	CString	strTime;
	int		nFuncl;
	CString	strApp;
	int		nErr_code;
	int		nSevl;
	int		nX1;
	int		nY1;
	int		nValue[5];

	/*
	**  Routine:  ids_hex_to_char
	**  Title:    Convert hex to character
	*/
	CString HexErrorCode(int nValue)
	{
		CString str;
		if ( nValue > MAX_CODE) 
			nValue ^= MASK_CODE;
		str.Format(_T("%04x"), nValue);
		return(str);
	}
};
// CCCUHistoryDlg dialog
class CCCUHistoryDlg : public CDialog
{
// Construction
public:
	CCCUHistoryDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CCUHISTORY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
private:
	CObArray*		pErr;

	CFile fError;
	CStdioFile fSimDgn;
	CFileException e;

	BOOL bSimDgnRead;
	BOOL bReverse;
	BOOL bFilterActive;

	CString str;
	CString str2;

	int  nLast;

	CString strErrorFile1;
	CString strSIM_DGNFile1;

	CStringArray arrayIDSmsg;
	CStringArray arrayApplication;
	CString strMessage;
	CString strTempX;
	CString strTempY;
	CString strTemp;

	CColorListBox ctlMessage;
	CProgressCtrl ctlProgress;
	CButton ctlShowSource;

	HRESULT GetErrorFileName(void);
	CString ids_parse(IDSErrroMessage* Err);
	HRESULT GetSIM_DGNFileName(void);

protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedFinderrorfile();
	afx_msg void OnBnClickedFindsimDgnfile();
	afx_msg void OnLbnSelchangeList1();

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedShowsource();
	CComboBox ctlApplication;
	CStatic ctlErrorCountMSG;
	afx_msg void OnCbnSelchangeApplication();
	CButton ctlPrint;
	afx_msg void OnBnClickedPrint();
};
