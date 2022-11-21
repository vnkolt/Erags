
/*************************************************************************
 FILE       : PersistMDIFrame.cpp

 Author		: Stefan Chekanov (stefant@iname.com)

 Description: Definition of CPersistMDIFrame class used to make MDI Main
			  frames persistent.

Copyright(c) 1998,1999,2000
by Stefan Chekanov (stefant@iname.com)

This code may be used in compiled form in any way you desire. This
file may be redistributed unmodified by any means PROVIDING it is 
not sold for profit without the authors written consent, and 
providing that this notice and the authors name is included. If 
the source code in this file is used in any commercial application 
then a simple email to the author would be nice.

This file is provided "as is" with no expressed or implied warranty.
The author accepts no liability if it causes any damage.

*************************************************************************/
/* #    Revisions    # */


#include "stdafx.h"
#include "PersistMDIFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////
// CPersistMDIFrame

IMPLEMENT_DYNAMIC(CPersistMDIFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CPersistMDIFrame, CMDIFrameWnd)
    //{{AFX_MSG_MAP(CPersistMDIFrame)
    ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////

CPersistMDIFrame::CPersistMDIFrame()
{
	m_persistImpl.SetWindow( this );
	m_persistImpl.SetProfileHeading( "Main Frame" );
}
///////////////////////////////////////////////////////////////

CPersistMDIFrame::~CPersistMDIFrame()
{
}
///////////////////////////////////////////////////////////////

BOOL	CPersistMDIFrame::ShowWindow( int nCmdShow )
{
	m_persistImpl.Load();
	return	CMDIFrameWnd::ShowWindow( m_persistImpl.getCmdShow() );
}
///////////////////////////////////////////////////////////////

void CPersistMDIFrame::OnDestroy()
{
	m_persistImpl.Save();
    CMDIFrameWnd::OnDestroy();
}
///////////////////////////////////////////////////////////////
