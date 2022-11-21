//
// MyBtnST.cpp
//
#include "stdafx.h"
#include "MyBtnST.h"

#include "NewMenu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DWORD CMyButtonST::OnDrawBackground(CDC* pDC, CRect* pRect) {
  CRect r;
  GetClientRect(&r);
  GradientEraseBkgnd(this, GetParent(), pDC, r);
  return BTNST_OK;
}