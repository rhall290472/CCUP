/*
!==============================================================================!
!\                                                                            /!
!\\                                                                          //!
! \##########################################################################/ !
!  #         This is Proprietary Software of Pioneer Simulation             #  !
!  ##########################################################################  !
!  #                                                                        #  !
!  #  FILE NAME   :  version.cpp                                            #  !
!  #                                                                        #  !
!  #  DESCRIPTION :  Class MSKVersionInfo                                   #  !
!  #                 Handles accessing the VERSIONINFO resource             #  !
!  #                 More complete info is given in Version.h               #  !
!  #                                                                        #  !
!  #  REFERENCES  :                                                         #  !
!  #                                                                        #  !
!  #                                                                        #  !
!  #  CHANGE HISTORY ;                                                      #  !
!  #                                                                        #  !
!  ##########################################################################  !
!  #                                                                        #  !
!  #                                                                        #  !
!  #   Copyright 2005 - Pioneer Simulation                                  #  !
!  #                                                                        #  !
!  #   The information contained herein is the property of Pioneer          #  !
!  #   Simulation, and shall not be copied, in whole or in part, or         #  !
!  #   disclosed to others in any manner without the express written        #  !
!  #   authorization of Pioneer Simulation.                                 #  !
!  #                                                                        #  !
!  #                                                                        #  !
! /##########################################################################\ !
!//                                                                          \\!
!/                                                                            \!
!==============================================================================!
*/
#include <stdafx.h>
#include "Version.h"
     
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
// MSKVersionInfo ctor
//
// Takes as it's parameter the name of the module to extract 
// the version information from.  If NULL or defaulted,
// get the information from the current EXE.
     
//#############################################################################
//
// 
//
//#############################################################################
MSKVersionInfo::MSKVersionInfo(LPCTSTR lpszModuleName /* = NULL */)
        : m_VerData(NULL)
{
    HMODULE     hModule;
    if (lpszModuleName == NULL) {
        hModule = AfxGetInstanceHandle();
    } else {
        hModule = GetModuleHandle(lpszModuleName);
        if (hModule == NULL)
            AfxThrowUserException();
    }

	TCHAR name[_MAX_PATH];
    GetModuleFileName(hModule, name, sizeof(name));

    DWORD   hInfo;
    DWORD   dwLen;
    dwLen = GetFileVersionInfoSize(name, &hInfo);

    if (dwLen == 0)
        AfxThrowUserException();

    m_VerData = (void *) new char[dwLen];
    if (m_VerData == NULL)
        AfxThrowMemoryException();

    GetFileVersionInfo(name, hInfo,  dwLen, m_VerData);


    struct {
        WORD    first;
        WORD    second;
    } *lpBuffer;
     
    VerQueryValue(m_VerData, _T("\\VarFileInfo\\Translation"),
            (LPVOID*) &lpBuffer,(unsigned int *) &dwLen);
     
    if (dwLen==0)
        AfxThrowUserException();
     
    wsprintf(name, _T("\\StringFileInfo\\%04x%04x\\"), 
                    lpBuffer->first, lpBuffer->second);
    m_sSubBlockHead = name;
}

//#############################################################################
//
// 
//
//#############################################################################
MSKVersionInfo::~MSKVersionInfo()
{
	//TRACE0("MSKVersionInfo::~MSKVersionInfo()\n");

	delete m_VerData;
}
     
//#############################################################################
//
// 
//
//#############################################################################
CString MSKVersionInfo::GetValue(CString const sSubBlock)
{
    CString sBlock = m_sSubBlockHead + sSubBlock; 
    CString sRet;
     
    unsigned int    uSize;
    LPCTSTR         lpBuffer;
    BOOL bRet = VerQueryValue(m_VerData, 
                    ((LPCTSTR) sBlock), 
                    (void**)&lpBuffer, &uSize);
     
    if (bRet)
        sRet = lpBuffer;
     
    return sRet;
}
//#############################################################################
//
// 
//
//#############################################################################
// End of File
