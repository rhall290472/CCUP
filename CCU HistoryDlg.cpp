/*
!==============================================================================!
!\                                                                            /!
!\\                                                                          //!
! \##########################################################################/ !
!  #         This is Proprietary Software of Richard Hall                   #  !
!  ##########################################################################  !
!  #                                                                        #  !
!  #  FILE NAME   :  CCUDlgpp                                               #  !
!  #                                                                        #  !
!  #  DESCRIPTION :  Defines the class behaviors for the application.       #  !
!  #                                                                        #  !
!  #                                                                        #  !
!  #  REFERENCES  :                                                         #  !
!  #                                                                        #  !
!  #                                                                        #  !
!  #  CHANGE HISTORY ;                                                      #  !
!  #                                                                        #  !
!  ##########################################################################  !
!  #                                                                        #  !
!  #                                                                        #  !
!  #   Copyright 2010 - Richard Hall                                        #  !
!  #                                                                        #  !
!  #   The information contained herein is the property of Richard          #  !
!  #   Hall, and shall not be copied, in whole or in part, or               #  !
!  #   disclosed to others in any manner without the express written        #  !
!  #   authorization of Richard Hall.                                       #  !
!  #                                                                        #  !
!  #                                                                        #  !
! /##########################################################################\ !
!//                                                                          \\!
!/                                                                            \!
!==============================================================================!
*/
// CCU HistoryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CCU History.h"
#include "CCU HistoryDlg.h"
#include "DlgErrorMessage.h"

#include "version.h"

#define min(a, b)  (((a) < (b)) ? (a) : (b)) 
#define max(a, b)  (((a) > (b)) ? (a) : (b)) 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	CString strAboutProduct;
	CString strCompany;
	CString strCopyRight;
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
, strAboutProduct(_T(""))
, strCompany(_T(""))
, strCopyRight(_T(""))
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PRODUCT, strAboutProduct);
	DDX_Text(pDX, IDC_COMPANY, strCompany);
	DDX_Text(pDX, IDC_COPYRIGHT, strCopyRight);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CCCUHistoryDlg dialog




CCCUHistoryDlg::CCCUHistoryDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCCUHistoryDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	pErr = new CObArray;
}

void CCCUHistoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ERRORFILE, strErrorFile1);
	DDX_Text(pDX, IDC_SIM_DGNFILE, strSIM_DGNFile1);
	DDX_Control(pDX, IDC_LIST1, ctlMessage);
	DDX_Control(pDX, IDC_PROGRESS1, ctlProgress);
	DDX_Control(pDX, IDC_SHOWSOURCE, ctlShowSource);

	DDX_Control(pDX, IDC_APPLICATION, ctlApplication);
	DDX_Control(pDX, IDC_NUMBERERRORS, ctlErrorCountMSG);
	DDX_Control(pDX, IDPRINT, ctlPrint);
}

BEGIN_MESSAGE_MAP(CCCUHistoryDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_FINDERRORFILE, &CCCUHistoryDlg::OnBnClickedFinderrorfile)
	ON_BN_CLICKED(IDC_FINDSIM_DGNFILE, &CCCUHistoryDlg::OnBnClickedFindsimDgnfile)
	ON_LBN_SELCHANGE(IDC_LIST1, &CCCUHistoryDlg::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDOK, &CCCUHistoryDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CCCUHistoryDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_SHOWSOURCE, &CCCUHistoryDlg::OnBnClickedShowsource)
	ON_CBN_SELCHANGE(IDC_APPLICATION, &CCCUHistoryDlg::OnCbnSelchangeApplication)
	ON_BN_CLICKED(IDPRINT, &CCCUHistoryDlg::OnBnClickedPrint)
END_MESSAGE_MAP()


// CCCUHistoryDlg message handlers

BOOL CCCUHistoryDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	bSimDgnRead = false;
	ctlProgress.ShowWindow(SW_HIDE);
	ctlShowSource.ShowWindow(SW_HIDE);
	ctlErrorCountMSG.ShowWindow(SW_HIDE);

	strErrorFile1 = AfxGetApp()->GetProfileString( _T("Paths"), _T("ErrorFile"), NULL );
	strSIM_DGNFile1 = AfxGetApp()->GetProfileString( _T("Paths"), _T("Sim_DgnFile"), NULL );
	
	UpdateData(false);
	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCCUHistoryDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;

			// Set-up the version information..
		MSKVersionInfo VerInfo;
		dlgAbout.strAboutProduct.Format(_T("%s, Version %s"), VerInfo.ProductName(), VerInfo.ProductVersion() );
		dlgAbout.strCompany = VerInfo.CompanyName();
		dlgAbout.strCopyRight = VerInfo.LegalCopyright();
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCCUHistoryDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCCUHistoryDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//#############################################################################
//\brief
//!CCCUHistoryDlg::OnButtonOK
//
//#############################################################################
void CCCUHistoryDlg::OnBnClickedOk()
{
	if(strErrorFile1.IsEmpty())
		GetErrorFileName();
	
	if(!fError.Open(strErrorFile1, CFile::modeRead | CFile::shareDenyNone, &e))
	{
		AfxMessageBox(_T("ERROR"), MB_OK);
	   TRACE(_T("File %s could not be opened %d\n"), strErrorFile1, e.m_cause);
	}

	//Clear out any messages in box
	int nDebug = ctlMessage.GetCount();
	for(int j = ctlMessage.GetCount(); j >= 0; j--)
		ctlMessage.DeleteString(j);
	nDebug = ctlMessage.GetCount();
	for( int i = 0; i < pErr->GetSize(); i++ )
		delete pErr->GetAt(i);
	pErr->RemoveAll();

	bFilterActive = false;

	UpdateData(false);
	ctlProgress.ShowWindow(SW_NORMAL);

	char pbufRead[ERROR_SIZE];

	CString pbufString;
	CString strToken;
	BOOL bFoundSection = false;
	BOOL bFoundError = false;

	CStringArray arrayErrors;

	//Get Current Error and Max Error
	fError.Read(pbufRead, sizeof(pbufRead));
	char seps[]   = " ";
	char *next_token = NULL;

	// Establish string and get the first token:
	int Front;
	int status;
	int Size;
	status = sscanf_s(pbufRead,"%d %d",&Front, &Size);
	Front--;
	if(Front == 0) Front = MAX_ERROR;

	ctlProgress.SetRange32(0, Size);

	char strDate[16];
	char strTime[16];
	char strApp[4];

	for (int i=1; i <= Size; i++) 
	{
		//if(Size == MAX_ERROR) 
		if( i > MAX_ERROR )
		{
			//if (++Front > MAX_ERROR) 
				//Front = 1;
			//fError.Seek(Front*ERROR_SIZE, CFile::begin);
			i = 1;
			fError.Seek(i*ERROR_SIZE, CFile::begin);
		}
		else 
		{
			fError.Seek(i*ERROR_SIZE, CFile::begin);
		}
		fError.Read(pbufRead, sizeof(pbufRead));

		IDSErrroMessage* Err = new IDSErrroMessage;

		status = sscanf_s((const char*)pbufRead, "%s %s %d %s %x %x %x %x %x %x %x %x %x", 
			strDate,  _countof(strDate), 
			strTime, _countof(strTime),
			&Err->nFuncl,
			strApp, _countof(strApp),
			&Err->nErr_code,
			&Err->nSevl,
			&Err->nX1,
			&Err->nY1,
			&Err->nValue[0],
			&Err->nValue[1],
			&Err->nValue[2],
			&Err->nValue[3],
			&Err->nValue[4]);

		Err->nFuncl &= 0x0000ffff;
		Err->nErr_code &= 0x0000ffff;
		Err->nSevl &= 0x0000ffff;
		Err->nX1 &= 0x0000ffff;
		Err->nY1 &= 0x0000ffff;
		Err->strDate	= strDate;
		Err->strTime	= strTime;
		Err->strApp		= strApp;
		if(Err->strApp.GetLength() < 3)
		{
			for(int k = Err->strApp.GetLength(); k < 3; k++)
				Err->strApp.Insert(k, _T(' '));
		}


		pErr->Add(Err);

		strMessage = ids_parse(Err);

		if(Err->nSevl == 2)
			ctlMessage.AddString(strMessage, RGB(255,0,0));
		else if(Err->nSevl == 3)
			ctlMessage.AddString(strMessage, RGB(255,140,0));
		else
			ctlMessage.AddString(strMessage, RGB(0,0,0));

		ctlProgress.SetPos(i);
	}
	UpdateData(false);
	CString strErrorCount;
	strErrorCount.Format(_T("Number of Errors found in file %04d"), Size);
	SetDlgItemText(IDC_NUMBERERRORS, strErrorCount);
	ctlErrorCountMSG.ShowWindow(SW_NORMAL);

	fError.Close();
	
	ctlProgress.ShowWindow(SW_HIDE);
	UpdateData(false);
	ctlMessage.ShowScrollBar(SB_BOTH, true);

	//OnOK();
}
//#############################################################################
//\brief
//!CCCUHistoryDlg::OnButtonCancel
//
//#############################################################################
void CCCUHistoryDlg::OnBnClickedCancel()
{
	for( int i = 0; i < pErr->GetSize(); i++ )
		delete pErr->GetAt(i);
	pErr->RemoveAll();

	delete pErr;

	OnCancel();
}
//#############################################################################
//\brief
//!CCCUHistoryDlg::GetErrorFileName
//
//#############################################################################
HRESULT CCCUHistoryDlg::GetErrorFileName(void)
{
	CFileDialog dlgFile(TRUE);

	const int c_cMaxFiles = 100;
	const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1;
	dlgFile.GetOFN().lpstrFile = strErrorFile1.GetBuffer(c_cbBuffSize);
	dlgFile.GetOFN().nMaxFile = c_cMaxFiles;
	
	//TODO:
	// Add a windows title to the dialog box 
	//dlgFile.SetWindowTextW(_T("Open Error File") );

	dlgFile.DoModal();
	strErrorFile1.ReleaseBuffer();
	AfxGetApp()->WriteProfileString( _T("Paths"), _T("ErrorFile"), strErrorFile1 );

	return S_OK;
}
//#############################################################################
//\brief
//!CCCUHistoryDlg::GetSIM_DGNFileName
//
//#############################################################################
HRESULT CCCUHistoryDlg::GetSIM_DGNFileName(void)
{
	CFileDialog dlgFile(TRUE);

	const int c_cMaxFiles = 100;
	const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1;
	dlgFile.GetOFN().lpstrFile = strSIM_DGNFile1.GetBuffer(c_cbBuffSize);
	dlgFile.GetOFN().nMaxFile = c_cMaxFiles;
	
	//TODO:
	// Save file name in reg..
	// Add a windows title to the dialog box 
	//dlgFile.SetWindowTextW(_T("Open Error File") );

	dlgFile.DoModal();
	strSIM_DGNFile1.ReleaseBuffer();
	AfxGetApp()->WriteProfileString( _T("Paths"), _T("Sim_DgnFile"), strSIM_DGNFile1 );

	bSimDgnRead = false;
	arrayIDSmsg.RemoveAll();

	return S_OK;
}
//#############################################################################
//\brief
//!CCCUHistoryDlg::OnBnClickedFinderrorfile
//
//#############################################################################
void CCCUHistoryDlg::OnBnClickedFinderrorfile()
{
	GetErrorFileName();
	UpdateData(false);

}
//#############################################################################
//\brief
//!CCCUHistoryDlg::OnBnClickedFindsimDgnfile
//
//#############################################################################
void CCCUHistoryDlg::OnBnClickedFindsimDgnfile()
{
	GetSIM_DGNFileName();
	UpdateData(false);

}
//#############################################################################
//\brief
//!CCCUHistoryDlg::ids_parse
//
//#############################################################################
CString CCCUHistoryDlg::ids_parse(IDSErrroMessage* Err)
{
   int i = 0;
   int status;
	  int nFindCount1 = 0;
	  int nFindCount2 = 0;


   /* If this is first pass, load in the data file */
   if (bSimDgnRead == false) 
   {
      bSimDgnRead = true;
		if(strSIM_DGNFile1.IsEmpty())
			GetSIM_DGNFileName();

		if(!fSimDgn.Open(strSIM_DGNFile1, CFile::modeRead | CFile::shareDenyNone, &e))
		{
			AfxMessageBox(_T("ERROR"), MB_OK);
		   TRACE(_T("File %s could not be opened %d\n"), strSIM_DGNFile1, e.m_cause);
		}

	  CString strDGNLine;

      nLast = 0;

	  fSimDgn.SeekToBegin();
      while(nLast < MAX_SIM_DGN_MSG) 
	  {
		  //Skip by all of the comments/header stuff.
		  status = fSimDgn.ReadString(strDGNLine);
		  if( status == NULL || strDGNLine.GetAt(0) == ':') 
		  {
			arrayIDSmsg.Add(strDGNLine);
			if(strDGNLine.Find(_T(":END:")) == -1)
			{
				if(strDGNLine.Find(_T(":"), 1) < 4)
				{
					for(int k = nFindCount1; k < 4; k++)
						strDGNLine.Insert(k, _T(' '));
				}
				arrayApplication.Add(strDGNLine.Mid(1,3));
				ctlApplication.AddString(strDGNLine.Mid(1,3));
			}
			  break;
		  }
      }

      nLast = 1;
	  int j;

      while (nLast < MAX_SIM_DGN_MSG) 
	  {
		  if(status = fSimDgn.ReadString(strDGNLine) == NULL)
			  break;
		 
		  /* strip off the \n */
		  if (strDGNLine.GetAt(strDGNLine.GetLength()) == '\n') 
			  strDGNLine.SetAt(strDGNLine.GetLength(), '\0');
          /* Do not bother to store comments */
		  if (strDGNLine.GetAt(0) != '*')
		  {
			  arrayIDSmsg.Add(strDGNLine);
			  nLast++;
			if(strDGNLine.GetAt(0) == ':' && strDGNLine.Find(_T(":END:")) == -1)
			{
				//Check to ensure that application code does not already exist in the array
				for( j = 0; j < arrayApplication.GetCount(); j++)
				{
					/* Fix any application code that are less than 3 characters */
					nFindCount1 = strDGNLine.Find(_T(":"), 1);
					if( nFindCount1 < 4 )
					{
						for(int k = nFindCount1; k < 4; k++)
							strDGNLine.Insert(k, _T(' '));
					}

					if(arrayApplication.GetAt(j).Find(strDGNLine.Mid(1,3)) != -1)
						break;	// Found it.
				}
			
				if(j == arrayApplication.GetCount())
				{
					ctlApplication.AddString(strDGNLine.Mid(1,3));
					arrayApplication.Add(strDGNLine.Mid(1,3));
				}
			}
		  }
	  }
	  fSimDgn.Close();
   }

   // Find application
   strTempX.Format(_T("? Unknow X"));
   strTempY.Format(_T("? Unknow Y"));

   /* Find the application type   */
	CString strIDSmsg;

	// Locate the App section of the SIM_DGN.DAT file
	for (i = 0; i < arrayIDSmsg.GetCount() ;i++) 
	{
	  strIDSmsg = arrayIDSmsg.GetAt(i);
	  if(strIDSmsg.GetAt(0) == _T(':') && strIDSmsg.Find(_T(":"), 1) < 4)
	  {
		for(int k = strIDSmsg.Find(_T(":"), 1); k < 4; k++)
			strIDSmsg.Insert(k, _T(' '));
	  }

	  if( strIDSmsg.Find(Err->strApp, 0) == 1 )
		  break;
    } 


	int ptr = i;
	bReverse = false;

	CString strReturn;

	if (i >= arrayIDSmsg.GetCount()) 
	{
		strReturn.Format(_T("%s ? Did not find :%s: in sim_dgn.dat file"), Err->strApp, Err->strApp);
	} 
	else 
	{
		/* Find the error code in this list under application      */
		for(i = ptr+1; i < nLast; i++) 
		{
			/* If we find ':' this mean we have a new application exit
			or if the message has a greater value than Max_code
			and we did not find the err_code start the search
			again for the new error_code */
			strIDSmsg = arrayIDSmsg.GetAt(i);
			if (strIDSmsg.GetAt(0) == ':') 
			{
				if ( Err->nErr_code > MAX_CODE) 
				{
					// Here we "reset" the error and output the cleared message
					ptr = i;
					bReverse = true;
				}
				else 
				{
					i = nLast;
					break;
				}
			}

			if ( Err->nErr_code > MAX_CODE) 
				bReverse = true;

			status = strIDSmsg.Find(Err->HexErrorCode(Err->nErr_code));
			 if (status == 0) 
			 {
				strReturn = strIDSmsg.Mid(5);
				break;
			 }
		}
		ptr = i;

		if (i >= nLast) 
		{
			strReturn.Format(_T("%s Error:%s ? Not Found"),  Err->strApp, Err->HexErrorCode(Err->nErr_code));
		}
		else 
		{
         /* find extender strings if needed */
			if (Err->nX1 != 0) 
			{
				strTempX.Format(_T("%s_X"), Err->strApp);
				for(i = ptr+1; i < nLast; i++) 
				{
					strIDSmsg = arrayIDSmsg.GetAt(i);
					status = strIDSmsg.Find(strTempX, 0);
					if (status == 1) 
					{
						ptr = i;
						break;
					}
				}

				for (i = ptr+1; i < nLast; i++) 
				{
					strIDSmsg = arrayIDSmsg.GetAt(i);
					if(strIDSmsg.GetAt(0) == ':')
					{
						i = nLast;
						break;
					}
					status = strIDSmsg.Find(Err->HexErrorCode(Err->nX1));
					if (status == 0) 
					{
						ptr = i;
						strTempX = strIDSmsg.Mid(5);
						break;
					}
				}
			}
			else 
			{
				strTempX.Empty();
			}

			/**************/
			/* Do index Y */
			/**************/
			if(Err->nY1 != 0) 
			{
				if(Err->nFuncl == 1) 
				{
					strTempY.Format(_T("%s_Y"), Err->strApp);
				} 
				else if(Err->nFuncl == 2) 
				{
					strTempY.Format(_T("%s_%s_Y"), Err->strApp, Err->HexErrorCode(Err->nX1));
				} 
				else 
				{
					strTempY.Format(_T("Invalid function in error message %d"), Err->nFuncl);
					ptr = nLast;
				}
				
				for (i = ptr+1; i < nLast; i++) 
				{
					strIDSmsg = arrayIDSmsg.GetAt(i);
					status = strIDSmsg.Find(strTempY, 0);
					if (status == 1) 
					{
						ptr = i;
						break;
					}
				}
				
				for(i = ptr+1; i < nLast; i++) 
				{
					strIDSmsg = arrayIDSmsg.GetAt(i);
					if(strIDSmsg.GetAt(0) == ':')
					{
						i = nLast;
						strIDSmsg.Format(_T("%s could not find error %s"), strTempY.GetBuffer(), Err->HexErrorCode(Err->nY1));
						strTempY = strIDSmsg;
 						break;
					}
					
					status = strIDSmsg.Find(Err->HexErrorCode(Err->nY1));
					if (status == 0) 
					{	
						ptr = i;
						strTempY = strIDSmsg.Mid(5);
						break;
					}
				}
			} 
			else 
			{
				strTempY.Empty();
			}

			// Replace %s with the X and Y string
			status = strReturn.Find(_T("%s") );
			if(status != -1 && !strTempX.IsEmpty())
			{
				strReturn.Delete(status, 2);	// Remove the %s
				strReturn.Insert(status, strTempX);
			}

			status = strReturn.Find(_T("%s") );
			if(status != -1 && !strTempY.IsEmpty())
			{
				strReturn.Delete(status, 2);	// Remove the %s
				strReturn.Insert(status, strTempY);
			}

			// Insert the values
			for(int k = 0; k < 5; k++)
			{
				status = strReturn.Find(_T("%") );
				if(status != -1)
				{
					switch(strReturn.GetAt(status+1))
					{
						case 'd':
							strTemp.Format(_T("%d"), Err->nValue[k]);
							break;
						case 'x':
						case 'X':
							strTemp.Format(_T("%x"), Err->nValue[k]);
							break;
						case 'o':
						case 'O':
							strTemp.Format(_T("%o"), Err->nValue[k]);
							break;
						case 'f':
							strTemp.Format(_T("%f"), Err->nValue[k]);
							break;
						default:
							TRACE("Invalid format character\n");
					}
					strReturn.Delete(status, 2);	// Remove the %s
					strReturn.Insert(status, strTemp);
				}
			}


         /* Append a string to the message 
            This will only happen if the error_code is greater than
            7fff and it was not found in the list of error_code
            if so the error_code will be XOR and with the new 
            error_code we happen a Resolved to it*/
         if (bReverse) 
		 {
			 strReturn.Insert(strReturn.GetLength(), _T(" - Cleared"));
         }
      }
	}

	/* Add severity indicator onto string */
	switch(Err->nSevl) {
		case 1:
			strReturn.Insert(0, _T("   (I)   "));
			break;
		case 2:
			strReturn.Insert(0, _T("   (E)   "));
			break;
		case 3:
			strReturn.Insert(0, _T("   (W)   "));
			break;
		case 4:
			strReturn.Insert(0, _T("   (I)   "));
			break;
	}

   /* Add Application indicator */
	strReturn.Insert(0, Err->strApp);
	strReturn.Insert(0, _T("   "));

	strReturn.Insert(0, Err->strTime);
	strReturn.Insert(0, _T("   "));

	strReturn.Insert(0, Err->strDate);
	strReturn.Insert(0, _T("   "));

	return( strReturn );
}
//#############################################################################
//\brief
//!CCCUHistoryDlg::OnLbnSelchangeList1
//
//#############################################################################
void CCCUHistoryDlg::OnLbnSelchangeList1()
{
	if(bFilterActive)
		ctlShowSource.ShowWindow(SW_HIDE);
	else
		ctlShowSource.ShowWindow(SW_NORMAL);
}
//#############################################################################
//\brief
//!CCCUHistoryDlg::OnBnClickedShowsource
//
//#############################################################################
void CCCUHistoryDlg::OnBnClickedShowsource()
{
	int nSelected = -1;
	nSelected = ctlMessage.GetCurSel();

	IDSErrroMessage* Err;
	Err = (IDSErrroMessage*)pErr->GetAt( nSelected );
	VERIFY( Err != NULL );
	
	CDlgErrorMessage Dlg;

	Dlg.strDate		= Err->strDate;
	Dlg.strTime		= Err->strTime;
	Dlg.nFunc		= Err->nFuncl;
	Dlg.strApp		= Err->strApp;
	Dlg.nErrCode	= Err->nErr_code;
	Dlg.nServ		= Err->nSevl;
	Dlg.nX			= Err->nX1;
	Dlg.nY			= Err->nY1;
	Dlg.nValue1		= Err->nValue[0];
	Dlg.nValue2		= Err->nValue[1];
	Dlg.nValue3		= Err->nValue[2];
	Dlg.nValue4		= Err->nValue[3];
	Dlg.nValue5		= Err->nValue[4];


	Dlg.DoModal();

}
//#############################################################################
//\brief
//!CCCUHistoryDlg::OnCbnSelchangeApplication()
// We get here is the users wants to filter the Application.
//
//#############################################################################
void CCCUHistoryDlg::OnCbnSelchangeApplication()
{
	//Clear out any messages in box
	int nDebug = ctlMessage.GetCount();
	for(int j = ctlMessage.GetCount(); j >= 0; j--)
		ctlMessage.DeleteString(j);
	nDebug = ctlMessage.GetCount();

	int n = ctlApplication.GetCurSel();
	CString strApplication;
	
	ctlShowSource.ShowWindow(SW_HIDE);

	int nSize=0;
	ctlApplication.GetLBText(n, strApplication);

	if( !strApplication.CompareNoCase(_T("ALL")) )
		bFilterActive = false;
	else
		bFilterActive = true;


	IDSErrroMessage* Err = new IDSErrroMessage;
	ctlProgress.ShowWindow(SW_NORMAL);
	ctlProgress.SetRange32(0, pErr->GetCount());

	for( int i = 0; i < pErr->GetCount(); i++)
	{
		Err = (IDSErrroMessage*)pErr->GetAt( i );

		if(!strApplication.CompareNoCase( Err->strApp ) || !bFilterActive )
		{
			nSize++;
			strMessage = ids_parse(Err);

			if(Err->nSevl == 2)
				ctlMessage.AddString(strMessage, RGB(255,0,0));
			else if(Err->nSevl == 3)
				ctlMessage.AddString(strMessage, RGB(255,140,0));
			else
				ctlMessage.AddString(strMessage, RGB(0,0,0));

			ctlProgress.SetPos(i);
		}
	}
	UpdateData(false);
	CString strErrorCount;
	strErrorCount.Format(_T("Number of Errors found in file %04d"), nSize);
	SetDlgItemText(IDC_NUMBERERRORS, strErrorCount);
	ctlErrorCountMSG.ShowWindow(SW_NORMAL);

	
	ctlProgress.ShowWindow(SW_HIDE);
	UpdateData(false);
	ctlMessage.ShowScrollBar(SB_BOTH, true);

}
//#############################################################################
//\brief
//!CCCUHistoryDlg::OnBnClickedPrint()
// 
//
//#############################################################################
void CCCUHistoryDlg::OnBnClickedPrint()
{
	CPrintDialog dlg(FALSE, PD_PAGENUMS | PD_USEDEVMODECOPIES);
	dlg.m_pd.Flags = PD_HIDEPRINTTOFILE | PD_ALLPAGES | PD_NOSELECTION | PD_RETURNDC;
	if (dlg.DoModal() == IDOK)
	{
	   // Get a handle to the printer device context (DC).
	   HDC dc = dlg.GetPrinterDC();
	   ASSERT(dc);

	   CDC PrinterDC;
	   PrinterDC.Attach(dc);

		DOCINFO docInfo;
		docInfo.cbSize = sizeof( DOCINFO );
		docInfo.lpszDocName = _T("CCU History");
		docInfo.lpszOutput = NULL;
	
		int nStartDoc = PrinterDC.StartDocW( &docInfo );
		ASSERT( nStartDoc > 0 );


		PrinterDC.StartPage();
		CString rString;
		TEXTMETRIC tm;
		PrinterDC.GetTextMetrics( &tm );
		int nLineAdv = tm.tmHeight + tm.tmExternalLeading;
		int nYval = 0;	
		
		for( int i = 0; i < ctlMessage.GetCount(); i++ )
		{
			ctlMessage.GetText(i, rString);
			PrinterDC.TextOut( 10, nYval, rString );
		
			nYval += nLineAdv;
		}
	
	
		// Step 4 Each new page NEWFRAME
		PrinterDC.EndPage();
		
		// Step 5 End printing with ENDDOC
		PrinterDC.EndDoc();

	   // Do something with the HDC...

	   // Clean up.
	   CDC::FromHandle(dc)->DeleteDC();
	}
}