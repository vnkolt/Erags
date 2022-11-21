// UkraineMap.cpp : implementation file
//

#include "stdafx.h"
#include "EraWiz.h"
#include "UkraineMap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define CLR_CHERKASSY   RGB(0xB5, 0x90, 0xFF)
#define CLR_CHERNYGOV   RGB(0x24, 0xFF, 0xFF)
#define CLR_CHERNOVTSY  RGB(0xFF, 0x90, 0xFF)
#define CLR_DNEPR       RGB(0xFF, 0xB4, 0xFF)
#define CLR_DONETSK     RGB(0x6C, 0x9D, 0xFF)
#define CLR_FRANKOVSK   RGB(0xFF, 0x6D, 0x24)
#define CLR_KHEMLNYTSKY RGB(0x9D, 0x6C, 0xFF)
#define CLR_ZAPORIZHIE  RGB(0xFF, 0xFF, 0xB4)
#define CLR_ZHITOMYR    RGB(0xB4, 0xE6, 0xFF)
#define CLR_KIEV        RGB(0xFF, 0xE6, 0xB4)
#define CLR_NIKOLAEV    RGB(0x90, 0xDA, 0xFF)
#define CLR_LVOV        RGB(0x48, 0xFF, 0xC2)
#define CLR_LUGANSK     RGB(0x00, 0xBA, 0xBA)
#define CLR_LUTSK       RGB(0xFF, 0xCE, 0x6C)
#define CLR_KHARKOV     RGB(0x6C, 0xFF, 0xFF)
#define CLR_KHERSON     RGB(0x00, 0xD9, 0x00)
#define CLR_KIROVOGRAD  RGB(0xF0, 0xAA, 0x00)
#define CLR_KRYM        RGB(0xFF, 0xB4, 0xB4)
#define CLR_POLTAVA     RGB(0xB4, 0xFF, 0xB4)
#define CLR_ROVNO       RGB(0xFF, 0x90, 0xB5)
#define CLR_ODESSA      RGB(0xFF, 0x6C, 0x9D)
#define CLR_SUMMY       RGB(0x55, 0xF0, 0x00)
#define CLR_TERNOPOL    RGB(0xFF, 0xC2, 0x48)
#define CLR_VINNITSA    RGB(0x90, 0xFF, 0xB5)
#define CLR_UZHGOROD    RGB(0x00, 0xD9, 0x46)
#define CLR_KIEV_CITY   RGB(0x9B, 0x00, 0x00)
#define CLR_SEVASTOPOL  RGB(0x9B, 0x00, 0x69)

#define CLR_TOP         RGB(0x48, 0x48, 0xFF)
#define CLR_BOTTOM      RGB(0xFF, 0xFF, 0x00)

#define CLR_BLACK       0x000000
#define CLR_CITY        RGB(128,0,0)



BOOL GetBitmapAndPalette(UINT nIDResource, CBitmap &bitmap, CPalette &pal, PALETTEENTRY* palEntries) {
	LPCTSTR lpszResourceName = (LPCTSTR)nIDResource;

	HBITMAP hBmp = (HBITMAP)::LoadImage( AfxGetInstanceHandle(),
			lpszResourceName, IMAGE_BITMAP, 0,0, LR_CREATEDIBSECTION );

	if( hBmp == NULL )
		return FALSE;

	bitmap.Attach( hBmp );

	// Create a logical palette for the bitmap
	DIBSECTION ds;
	BITMAPINFOHEADER &bmInfo = ds.dsBmih;
	bitmap.GetObject( sizeof(ds), &ds );

	int nColors = bmInfo.biClrUsed ? bmInfo.biClrUsed : 1 << bmInfo.biBitCount;

	// Create a halftone palette if colors > 256. 
	CClientDC dc(NULL);			// Desktop DC
	if( nColors > 256 )
		pal.CreateHalftonePalette( &dc );
	else
	{
		// Create the palette

		RGBQUAD *pRGB = new RGBQUAD[nColors];
		CDC memDC;
		memDC.CreateCompatibleDC(&dc);

		memDC.SelectObject( &bitmap );
		::GetDIBColorTable( memDC, 0, nColors, pRGB );

		UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * nColors);
		LOGPALETTE *pLP = (LOGPALETTE *) new BYTE[nSize];

		pLP->palVersion = 0x300;
		pLP->palNumEntries = nColors;

		for( int i=0; i < nColors; i++)
		{
			pLP->palPalEntry[i].peRed = pRGB[i].rgbRed;
			pLP->palPalEntry[i].peGreen = pRGB[i].rgbGreen;
			pLP->palPalEntry[i].peBlue = pRGB[i].rgbBlue;
			pLP->palPalEntry[i].peFlags = 0;
		}
    memcpy(palEntries, pLP->palPalEntry, sizeof(PALETTEENTRY)*256);

		pal.CreatePalette( pLP );

		delete[] pLP;
		delete[] pRGB;
	}

	return TRUE;
}

UKRREGION RegionsClr[] = {
 { CLR_CHERKASSY,  IDB_Cherkaska_Oblast       , IDB_Cherkasy      , _T("Черкас"),            _T("Черкаська")        ,23 },
 { CLR_CHERNOVTSY, IDB_Chernivtska_Oblast     , IDB_Chernovtsy    , _T("Чернівців"),         _T("Чернівецька")      ,24 },
 { CLR_CHERNYGOV,  IDB_Chernihivska_Oblast    , IDB_Chernihiv     , _T("Чернігіва"),         _T("Чернігівська")     ,25 },
 { CLR_DNEPR,      IDB_Dnipropetrovska_Oblast , IDB_Dnipropetrovsk, _T("Дніпропетровська"),  _T("Дніпропетровська") , 3 },
 { CLR_DONETSK,    IDB_Donetska_Oblast        , IDB_Donetsk       , _T("Донецька"),          _T("Донецька")         , 4 },
 { CLR_FRANKOVSK,  IDB_Frankivska_Oblast      , IDB_Frankivsk     , _T("Івано-Франківська"), _T("Івано-Франківська"), 8 },
 { CLR_ZAPORIZHIE, IDB_Zaporizhzhska_Oblast   , IDB_Zaporizha     , _T("Запоріжжя"),         _T("Запорізька")       , 7 },
 { CLR_ZHITOMYR,   IDB_Zhytomyrska_Oblast     , IDB_Zhytomyr      , _T("Житомира"),          _T("Житомирська")      , 5 },
 { CLR_KHARKOV,    IDB_Kharkivska_Oblast      , IDB_Kharkiv       , _T("Харкова"),           _T("Харківська")       ,20 },
 { CLR_KHEMLNYTSKY,IDB_Khmelnytska_Oblast     , IDB_Khmelnitsky   , _T("Хмельницького"),     _T("Хмельницька")      ,22 },
 { CLR_KHERSON,    IDB_Khersonska_Oblast      , IDB_Kherson       , _T("Херсона"),           _T("Херсонська")       ,21 },
 { CLR_KIEV,       IDB_Kyivska_Oblast         , IDB_Kiev          , _T("Київа"),             _T("Київська")         , 9 },
 { CLR_KIROVOGRAD, IDB_Kirovohradska_Oblast   , IDB_Kirovohrad    , _T("Кіровограда"),       _T("Кіровоградська")   ,10 },
 { CLR_KRYM,       IDB_Crimea                 , IDB_Simferopol    , _T("Сімферополя"),       _T("АР Крим")          ,16 },
 { CLR_NIKOLAEV,   IDB_Mykolaivska_Oblast     , IDB_Mykolaiv      , _T("Миколаїва"),         _T("Миколаївська")     ,13 },
 { CLR_LVOV,       IDB_Lvivska_Oblast         , IDB_Lviv          , _T("Львова"),            _T("Львівська")        ,12 },
 { CLR_LUGANSK,    IDB_Luhanska_Oblast        , IDB_Luhansk       , _T("Луганська"),         _T("Луганська")        ,11 },
 { CLR_LUTSK,      IDB_Volynska_Oblast        , IDB_Lutsk         , _T("Луцька"),            _T("Волинська")        , 2 },
 { CLR_POLTAVA,    IDB_Poltavska_Oblast       , IDB_Poltava       , _T("Полтави"),           _T("Полтавська")       ,15 },
 { CLR_ROVNO,      IDB_Rivnenska_Oblast       , IDB_Rivne         , _T("Рівне"),             _T("Рівненська")       ,17 },
 { CLR_ODESSA,     IDB_Odeska_Oblast          , IDB_Odessa        , _T("Одеси"),             _T("Одеська")          ,14 },
 { CLR_SEVASTOPOL, IDB_Sevastopol             , IDB_Sevastopol    , _T("Севастополя"),       _T("міста Севастополя"),27 },
 { CLR_SUMMY,      IDB_Sumska_Oblast          , IDB_Sumy          , _T("Сум"),               _T("Сумська")          ,18 },
 { CLR_TERNOPOL,   IDB_Ternopilska_Oblast     , IDB_Ternopil      , _T("Тернопіля"),         _T("Тернопільська")    ,19 },
 { CLR_VINNITSA,   IDB_Vinnytska_Oblast       , IDB_Vinnytsia     , _T("Вінниці"),           _T("Вінницька")        , 1 },
 { CLR_UZHGOROD,   IDB_Zakarpakska_Oblast     , IDB_Uzhgorod      , _T("Ужгорода"),          _T("Закарпатська")     , 6 },
 { CLR_KIEV_CITY,  IDB_Kiev                   , IDB_Kiev          , _T("Києва"),             _T("міста Києва")      ,26 }
};

int GetRegionIndex(COLORREF clr) {
  for( int i(0); i < sizeof(RegionsClr)/sizeof(UKRREGION); i++ ) {
    if ( RegionsClr[i].clr==clr )
      return i;
  }
  return -1;
}

/////////////////////////////////////////////////////////////////////////////
// CUkraineMap
CUkraineMap::CUkraineMap() {
  m_hHandCursor = theApp.LoadCursor(IDC_HAND);
  m_hTreeCursor = theApp.LoadCursor(IDC_HTREE);
  m_fRegionDefined = m_fCityDefined = m_fAll = FALSE;
  m_nRegion = -1;
  m_bmpBuffer = NULL;
  if ( GetBitmapAndPalette(IDB_UKRAINE_256, m_Bitmap, m_Palette, m_palEntries) ) {
    m_Bitmap.GetBitmap(&m_bmp); //Get bitmap dimensions into BITMAP structure.    
    m_bmpBuffer = (BYTE*)GlobalAlloc(GPTR, m_bmp.bmWidthBytes*m_bmp.bmHeight);//allocate memory for image byte buffer
    memset(m_bmpBuffer, 0xCC, m_bmp.bmWidthBytes*m_bmp.bmHeight);
    DWORD dwBytes = m_Bitmap.GetBitmapBits(m_bmp.bmWidthBytes*m_bmp.bmHeight, m_bmpBuffer);//Get the bitmap bits into a structure 
  }
}

CUkraineMap::~CUkraineMap() {
}


BEGIN_MESSAGE_MAP(CUkraineMap, CStatic)
	//{{AFX_MSG_MAP(CUkraineMap)
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
  ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_NOTIFY (UDM_TOOLTIP_DISPLAY, NULL, NotifyDisplayTooltip)
END_MESSAGE_MAP()

COLORREF CUkraineMap::getPixel(int x, int y) {
  COLORREF clr;
  int offs = y*(m_bmp.bmWidth + m_bmp.bmWidth%4) + x;
  int clrIndex = m_bmpBuffer[offs];
if ( clrIndex < 256 ) {
    clr = RGB(m_palEntries[clrIndex].peRed, m_palEntries[clrIndex].peGreen, m_palEntries[clrIndex].peBlue);
  }
  return clr;
}
COLORREF CUkraineMap::GetRegionOfCity(CDC* pDC, CPoint p) {
  COLORREF clr = CLR_BLACK;
  for( int offs=4; offs < 6; offs++ ) {
/************************************** : by VK at 21/05/2007 00:25:04 **\
    COLORREF clrL = pDC->GetPixel(p.x-offs, p.y);
    COLORREF clrU = pDC->GetPixel(p.x,      p.y-offs);
    COLORREF clrR = pDC->GetPixel(p.x+offs, p.y);
    COLORREF clrD = pDC->GetPixel(p.x,      p.y+offs);
\************************************** : by VK at 21/05/2007 00:25:07 **/
    COLORREF clrL = getPixel(p.x-offs, p.y);
    COLORREF clrU = getPixel(p.x,      p.y-offs);
    COLORREF clrR = getPixel(p.x+offs, p.y);
    COLORREF clrD = getPixel(p.x,      p.y+offs);
    if ( clrL == clrR && clrL != CLR_TOP && clrL != CLR_BOTTOM && clrL != CLR_BLACK ) {
      return clrL;
    }
    if ( clrU == clrD && clrU != CLR_TOP && clrU != CLR_BOTTOM && clrU != CLR_BLACK ) {
      return clrU;
    }
  }
  return clr;
}
/////////////////////////////////////////////////////////////////////////////
// CUkraineMap message handlers
void CUkraineMap::OnMouseMove(UINT nFlags, CPoint point) {
	// TODO: Add your message handler code here and/or call default
  CRect rc;
  GetClientRect(&rc);
  if ( rc.PtInRect(point) ) {
/************************************** : by VK at 09.07.2005 0:33:48 **\
    TRACKMOUSEEVENT tme;
    tme.cbSize = sizeof(tme);
    tme.dwFlags = TME_LEAVE;
    tme.hwndTrack = m_hWnd;
    _TrackMouseEvent(&tme);
\************************************** : by VK at 09.07.2005 0:33:51 **/
    FindRegion(point);
    if ( m_fRegionDefined ) {
      TRACE2(_T("PtInRect=TRUE, %d,%d\n"), point.x, point.y);
    }
  }
  else {
    TRACE2(_T("PtInRect=FALSE, %d,%d\n"), point.x, point.y);
    m_fRegionDefined = FALSE;
    m_nRegion = -1;
  }
	CStatic::OnMouseMove(nFlags, point);
}
LRESULT CUkraineMap::OnMouseLeave(WPARAM wParam, LPARAM lParam) {
  CPoint point;
  GetCursorPos(&point);
  ScreenToClient(&point);
  OnMouseMove(0, point);
  return 0L;
}

BOOL CUkraineMap::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) {
	// TODO: Add your message handler code here and/or call default
  if ( m_fAll ) {
  	::SetCursor(m_hTreeCursor);
	  return TRUE;
  }
  else if ( m_fRegionDefined ) {
  	::SetCursor(m_hHandCursor);
	  return TRUE;
  }
  return CStatic::OnSetCursor(pWnd, nHitTest, message);
}

void CUkraineMap::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	if ( GetSafeHwnd() ) {
    if ( m_tooltip.GetSafeHwnd()==NULL ) {
      CRect r;
      GetClientRect(&r);
      m_tooltip.Create(this);
	    m_tooltip.SetNotify();

    	//Add tooltip to the Map
    	PPTT_INFO ti;
    	ti.nBehaviour = PPTOOLTIP_MULTIPLE_SHOW;
    	ti.nIDTool = IDB_UKRAINE_256;
	    ti.rectBounds = r;
    	ti.sTooltip = "";
    	ti.nMask = PPTOOLTIP_MASK_BEHAVIOUR;
    	m_tooltip.AddTool(this, ti);
    }
  }
	CStatic::PreSubclassWindow();
}

BOOL CUkraineMap::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
  if ( m_fRegionDefined || m_fAll ) {
	  m_tooltip.RelayEvent(pMsg);
  }
	return CStatic::PreTranslateMessage(pMsg);
}

void CUkraineMap::FindRegion(CPoint& p) {
  CDC* pDC = GetDC();
  if ( pDC ) {
    m_fCityDefined = m_fAll = FALSE;
    // COLORREF clr = pDC->GetPixel(p);
    COLORREF clr = getPixel(p.x, p.y);
    if ( CLR_CITY==clr ) {
      clr = GetRegionOfCity(pDC, p);
      m_fCityDefined = TRUE;
    }
    switch( clr ) {
      case CLR_TOP:
      case CLR_BOTTOM:
        m_fAll = TRUE;
        m_fRegionDefined = FALSE;
        m_nRegion = -1;
        break;
      case CLR_BLACK:
        m_fRegionDefined = FALSE;
        m_nRegion = -1;
        break;
      default:
        m_fRegionDefined = TRUE;
        m_nRegion = GetRegionIndex(clr);
        break;
    }
    ReleaseDC(pDC);
  }
}
void CUkraineMap::NotifyDisplayTooltip(NMHDR * pNMHDR, LRESULT * result)
{
	*result = 0;
	NM_PPTOOLTIP_DISPLAY * pNotify = (NM_PPTOOLTIP_DISPLAY*)pNMHDR;

	if (pNotify->ti->nIDTool == IDB_UKRAINE_256 && (m_nRegion != -1 || m_fAll) )
	{
		CPoint pt = *pNotify->pt;
		ScreenToClient(&pt);
    CString str;
		if ( m_fAll ) {
      str = _T("Усі відділи РАЦС України");
    }
    else if ( m_nRegion != -1 ) {
      if ( m_fCityDefined ) {
		    str.Format( _T("Відділи РАЦС міста %s"), RegionsClr[m_nRegion].szCity);
      }
      else {
		    str.Format( _T("Відділи РАЦС %s"), RegionsClr[m_nRegion].szRegion);
        if ( str.Right(2)==_T("ка") ) {
          str.TrimRight('а');
          str += _T("ої області");
        }
      }
    }
    if ( FALSE==str.IsEmpty() )
		  pNotify->ti->sTooltip = str;
	} //if
} //End NotifyDisplayTooltip

void CUkraineMap::OnLButtonDown(UINT nFlags, CPoint point) {
	// TODO: Add your message handler code here and/or call default
  CWnd* pParent = GetParent();
  if ( m_fAll ) {
    pParent->PostMessage(WM_SETRAGSLIST_ALL);
  }
  else if ( m_nRegion != -1 ) {
    if ( m_fCityDefined ) {
      pParent->PostMessage(WM_SETRAGSLIST_CITY, (WPARAM)m_nRegion, (LPARAM)&RegionsClr[m_nRegion]);
    }
    else if ( m_fRegionDefined ) {
      pParent->PostMessage(WM_SETRAGSLIST_REGION, (WPARAM)m_nRegion, (LPARAM)&RegionsClr[m_nRegion]);
    }
  }
	CStatic::OnLButtonDown(nFlags, point);
}

