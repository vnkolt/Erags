/
// EraControls.cpp
//
#include "stdafx.h"
#include "EraControls.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CEraControlProperties::CEraControlProperties() {
  m_clrBackColor = g_clrBackColor;
  m_clrForeColor = g_clrForeColor;
  m_clrFocusBackColor = g_clrFocusBackColor;
  m_clrFocusForeColor = g_clrFocusForeColor;
}

CEraControlProperties::~CEraControlProperties() {
}

void SendKeys(BYTE bKey, BYTE bCtrlKey, BYTE bShiftKey/*=0*/) {
//  BYTE keyState[256];
//  GetKeyboardState((LPBYTE)&keyState);
  if ( bCtrlKey )
    keybd_event( bCtrlKey, 0, KEYEVENTF_EXTENDEDKEY | 0, 0 );

  if ( bShiftKey )
    keybd_event( bShiftKey, 0, KEYEVENTF_EXTENDEDKEY | 0, 0 );

  // Simulate a key press
  if ( bKey )
    keybd_event( bKey, 0, KEYEVENTF_EXTENDEDKEY | 0, 0 );


  // Simulate a key release
  if ( bKey )
    keybd_event( bKey, 0, KEYEVENTF_EXTENDEDKEY | 0, 0 );

  // Simulate a key release
  if ( bShiftKey )
    keybd_event( bShiftKey, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);

  // Simulate a key release
  if ( bCtrlKey )
    keybd_event( bCtrlKey, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
}
