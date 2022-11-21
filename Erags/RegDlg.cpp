// RegDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"
#include "RegDlg.h"

#include "DataManager.h"
#include "RNames.h"
#include "SecReg.h"
#include "xMachine.h"
#include "LogThread.h"
#include "..\Common\Crypto.h"
#include "..\Common\CyrString.h"
#include "..\Common\FHelpers.h"
#include "..\Common\RDF32.h"
#include "..\Controls\CPPTooltip\PPTooltip.h"

#include "..\ZipArchive\ZLIB\zlib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL IsValidRDF();

#ifndef FREE_LICENCE

#define NEW_REG

int g_MaxDates   = 120;
int g_MaxRecords = 150;

struct REG_CODE {
  BYTE  Size;           // 1  2  2
  BYTE  RagsType;       // 1  2  4  В=виконком), Р = РАЦС
  BYTE  r1, r2;
  DWORD dwRagsKey;      // 4  8 12
  DWORD GeoHash;        // 4  8 20
  DWORD RagsHash;       // 4  8 28
  DWORD XorValue;       // 4  8 36
};

CString        GetCity(LPCTSTR szCity, bool fTypeCity=false);
ValidOwner     g_ValidOwner;
ValidationInfo g_ValidationInfo;


BOOL Normalize(ValidOwner* pFDest, ValidOwner* pF1, ValidOwner* pF2) {
  BOOL fRet = false;
  if ( pF1->FirstStartDate != pF2->FirstStartDate ) {
    pFDest->FirstStartDate = min(pF1->FirstStartDate, pF2->FirstStartDate);
    if ( 0==pFDest->FirstStartDate )
      pFDest->FirstStartDate = max(pF1->FirstStartDate, pF2->FirstStartDate);
    fRet = true;
  }
  if ( pF1->TotalRecords != pF2->TotalRecords ) {
    pFDest->TotalRecords = max(pF1->TotalRecords, pF2->TotalRecords);
    fRet = true;
  }
  if ( pF1->dwValidGeoRecords != pF2->dwValidGeoRecords ) {
    pFDest->dwValidGeoRecords    = max(pF1->dwValidGeoRecords, pF2->dwValidGeoRecords);
    fRet = true;
  }
  if ( pF1->dwInvalidGeoRecors != pF2->dwInvalidGeoRecors ) {
    pFDest->dwInvalidGeoRecors = max(pF1->dwInvalidGeoRecors, pF2->dwInvalidGeoRecors);
    fRet = true;
  }
  if ( pF1->dwValidRagsRecords != pF2->dwValidRagsRecords ) {
    pFDest->dwValidRagsRecords = max(pF1->dwValidRagsRecords, pF2->dwValidRagsRecords);
    fRet = true;
  }
  if ( pF1->dwVyconcom != pF2->dwVyconcom ) {
    pFDest->dwVyconcom = max(pF1->dwVyconcom, pF2->dwVyconcom);
    fRet = true;
  }
  return fRet;
}

DWORD GetStrHashKey(LPCTSTR key) {
	DWORD nHash = 0;
	while (*key)
		nHash = (nHash<<5) + nHash + *key++;
	return nHash;
}

static char hexBuf[16] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
static char cyrBuf[16] = { '1','Б','Ф','Г','Д','Т','К','Л','М','Р','8','5','2','4','7','9' };

char HexToMyHex(char hex) {
  for( int i(0); i < sizeof(hexBuf); i++ )
    if ( hexBuf[i]==hex )
      return cyrBuf[i];
  return 0;
}
char MyHexToHex(char MyHex) {
  for( int i(0); i < sizeof(cyrBuf); i++ )
    if ( cyrBuf[i]==MyHex )
      return hexBuf[i];
  return 0;
}

CString ByteToMyHex(BYTE b) {
  CString s;
  char buf[8];
#if _MFC_VER < 0x0800
  sprintf(buf, "%02X", b);
#else
  sprintf_s(buf, sizeof(buf), "%02X", b);
#endif
  for( int i(0); i < 2; i++ )
    s += HexToMyHex(buf[i]);
  return s;
}
BYTE MyHexToByte(LPCTSTR szHex) {
  BYTE b = 0;
  char szBuf[4];
  memset(szBuf, 0, sizeof(szBuf));
  szBuf[0] = MyHexToHex(szHex[0]);
  szBuf[1] = MyHexToHex(szHex[1]);
#if _MFC_VER < 0x0800
  sscanf(szBuf, "%02X", &b);
#else
  sscanf_s(szBuf, "%02X", &b);
#endif
  return b;
}
CString BinToMyHex(LPTSTR szBin, int size, DWORD dwXor) {
  CString s;
  BYTE xor[4], xi = 0;
  memcpy(&xor, &dwXor, sizeof(xor));
  for( int i(0); i < size; i++ ) {
    //szBin[i] = szBin[i] ^ xor[xi];
    //s += ByteToMyHex( szBin[i] );
    s += ByteToMyHex( (BYTE)(szBin[i]) ^ xor[xi] );
    if ( ++xi== 4 )
      xi = 0;
    if ( i & 1 ) s += '-';
  }
  s.TrimRight('-');
  return s;
}
void HexToMyBin(LPTSTR szBin, LPCTSTR szHex, int binSize, DWORD dwXor) {
  BYTE xor[4], xi = 0;
  memcpy(&xor, &dwXor, sizeof(xor));
  for( int i(0); i < binSize; i++ ) {
    szBin[i] = MyHexToByte(CString(szHex+i*2, 2)) ^ xor[xi];
    if ( ++xi== 4 )
      xi = 0;
  }
}

CString DWORDToMyHex(DWORD dw) {
  CString s;
  char buf[32];
#if _MFC_VER < 0x0800
  sprintf(buf, "%08X", dw);
#else
  sprintf_s(buf, sizeof(buf), "%08X", dw);
#endif
  for( int i(0); i < 8; i++ )
    s += HexToMyHex(buf[i]);
  return s;
}
DWORD GetXorValue(int nHours) {
  CString s;
  GetSystemDirectory(s.GetBuffer(MAX_PATH), MAX_PATH);
  s.ReleaseBuffer();
  WIN32_FIND_DATA fd;
  HANDLE hFind = FindFirstFile(s, &fd);
  if ( hFind ) {
    SYSTEMTIME st;
    FindNextFile(hFind, &fd);
    FindClose(hFind);
    FileTimeToSystemTime(&fd.ftCreationTime, &st);
    union {
      struct {
        int M:4;
        int D:7;
        int h:7;
        int m:7;
        int s:7;
      };
      DWORD t;
    } xt;
    COleDateTime odt(st);
    odt += COleDateTimeSpan(0, nHours, 0, 0);
/*    
    xt.M = st.wMonth;
    xt.D = st.wDay;
    xt.h = st.wHour;
    xt.m = st.wMinute;
    xt.s = st.wSecond;
*/
    xt.M = odt.GetMonth();
    xt.D = odt.GetDay();
    xt.h = odt.GetHour();
    xt.m = odt.GetMinute();
    xt.s = odt.GetSecond();
    return xt.t;
  }
  return 0;
}

CString GetGeoKey(LPCTSTR szGeoname) {
  CCyrString sKey(GetTokSpace(szGeoname,0));
  return sKey.GetKeyLetters();
}
DWORD GetGeoHashKey(LPCTSTR szRegion, LPCTSTR szDistrict, LPCTSTR szCity) {
  CString s;
  s.Format(_T("%s%s%s"), GetGeoKey(szRegion), GetGeoKey(szDistrict), GetGeoKey(szCity));
  return GetStrHashKey(s);
}
DWORD GetRagsHashKey(const CString& szRags) {
  CString s( MakeKeysForRagsName(szRags));
  s.Replace(_T(" "), _T(""));
  s = MakeCanonicalName((LPCTSTR)s);
  return GetStrHashKey(s);
}

#ifdef _DEBUG
CString MakeLICCode(LIC_KEY& lc,
                    LPCTSTR szRegion,
                    LPCTSTR szDistrict,
                    LPCTSTR szCity,
                    LPCTSTR szRags,
                    DWORD RagsKey,
                    DWORD XorValue) {

  CCyrString sRegion(szRegion),
             sDistrict(szDistrict),
             sCity(szCity),
             sRags(MakeKeysForRagsName(szRags));
  CString sRegKey  = sRegion.GetKeyLetters().Left(4),
          sDistKey = sDistrict.GetKeyLetters().Left(4),
          sCityKey = sCity.GetKeyLetters().Left(4),
          sRagsKey = sRags.GetKeyLetters().Left(4);

  int mSize;
  memset(&lc, 0, sizeof(lc));

  CString szByte = ByteToMyHex( 0xF7 );
  BYTE b = MyHexToByte(szByte);

  mSize = min(sRegKey.GetLength(),4);  memcpy(&lc.RegionKey,   sRegKey,  mSize);
  mSize = min(sDistKey.GetLength(),4); memcpy(&lc.DistrictKey, sDistKey, mSize);
  mSize = min(sCityKey.GetLength(),4); memcpy(&lc.CityKey,     sCityKey, mSize);
  mSize = min(sRagsKey.GetLength(),4); memcpy(&lc.RagsKey,     sRagsKey, mSize);
  char* p = (char*)&lc;
  for ( int i(0); i < sizeof(lc)-sizeof(lc.rcSum); i++ ) {
    lc.rcSum += *p++;
  }
  //CString s = BinToMyHex((LPCTSTR)&lc, sizeof(lc), XorValue);
  CString s = BinToMyHex((LPTSTR)&lc, sizeof(lc), XorValue);
  s.Replace("-", "");
  LIC_KEY lcDecode;
  HexToMyBin((LPTSTR)&lcDecode, s, sizeof(lc)-sizeof(lc.rcSum), XorValue);
  return s;
}
#endif


BOOL IsValidLicenceKey(const CString& sKey) {

  for( int i(-1); i < 2; i++ ) {
    LIC_KEY lc;
    HexToMyBin((LPTSTR)&lc, sKey, sizeof(lc)-sizeof(lc.rcSum), GetXorValue(i));

    CCyrString sRegion(theIniCache.GetREGION()),
               sDistrict(theIniCache.GetDISTRICT()),
               sCity(MakeKeysForRagsName(theIniCache.GetCITY_())),
               sRags(MakeKeysForRagsName(theIniCache.GetRAGS()));

    CString sRegKey  = sRegion.GetKeyLetters().Left(4),
            sDistKey = sDistrict.GetKeyLetters().Left(4),
            sCityKey = sCity.GetKeyLetters().Left(4),
            sRagsKey = sRags.GetKeyLetters().Left(4);

    if ( sRegKey  == CString((LPCTSTR)lc.RegionKey,4)   && 
         sDistKey == CString((LPCTSTR)lc.DistrictKey,4) &&
         sCityKey == CString((LPCTSTR)lc.CityKey,4)     &&
         sRagsKey == CString((LPCTSTR)lc.RagsKey,4) )
      return true;
  }
  return false;
}
/////////////////////////////////////////////////////////////////////////////
// CRegDlg dialog
CRegDlg::CRegDlg(CWnd* pParent /*=NULL*/)
	      :CDialogEx(CRegDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CRegDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  m_nDates = 0;
  m_RTF_ID = 0;
  m_pValidLC = NULL;
}

void CRegDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRegDlg)
	DDX_Control(pDX, IDC_INFO, m_InfoText);
	DDX_Control(pDX, IDC_REG_LATER, m_btnLater);
  DDX_Control(pDX, IDC_START_DATE, m_StartDate);
  DDX_Control(pDX, IDC_PERIOD, m_cmbPeriod);
	//}}AFX_DATA_MAP
  for( int i(0); i < 6; i++ ) {
  	DDX_Text(pDX, IDC_KEY1+i, m_key[i]);
	  DDV_MaxChars(pDX, m_key[i], 6);
  }
}

LK_VALUE CRegDlg::CheckNewLicKey(LPCTSTR szLicKey) {
  CString szNewLicKey = szLicKey;
  if ( IsDigit(szNewLicKey) ) {
    return theIniCache.IsValidDigitLKey(szNewLicKey);
  }
  return LK_INVALID_LICENCE;
}

BEGIN_MESSAGE_MAP(CRegDlg, CDialogEx)
	//{{AFX_MSG_MAP(CRegDlg)
  ON_WM_CTLCOLOR()
  ON_WM_KEYDOWN()
	ON_EN_CHANGE(IDC_KEY1, OnChangeKey1)
	ON_EN_CHANGE(IDC_KEY2, OnChangeKey2)
	ON_EN_CHANGE(IDC_KEY3, OnChangeKey3)
	ON_EN_CHANGE(IDC_KEY4, OnChangeKey4)
	ON_EN_CHANGE(IDC_KEY5, OnChangeKey5)
	ON_EN_CHANGE(IDC_KEY6, OnChangeKey6)
	ON_BN_CLICKED(IDYES, OnYes)
  ON_BN_CLICKED(IDC_REG_LATER, OnRegLater)
  ON_NOTIFY(DTN_DATETIMECHANGE, IDC_START_DATE, OnStartDateChange)
  ON_CBN_SELENDOK(IDC_PERIOD, OnSelendokPeriod)
	//}}AFX_MSG_MAP
  ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
END_MESSAGE_MAP()


CString CRegDlg::GetNewRegCode() {
  CString szRet = theIniCache.GetNewRegCode();
  for( int i(32-4); i > 3; i -= 4 ) {
    szRet.Insert(i, '-');
  }
  return szRet;
}
void CRegDlg::OnReinit() {
  CString szRags =   MakeKeysForRagsName(theIniCache.GetRAGS());
  REG_CODE reg_code;
  memset(&reg_code, 0, sizeof(reg_code));
  reg_code.Size = (BYTE)sizeof(reg_code);
  reg_code.XorValue = GetXorValue(0);
  reg_code.RagsType = GetRagsType(szRags);
  reg_code.dwRagsKey= theIniCache.GetRagsID();
  reg_code.GeoHash  = GetGeoHashKey(theIniCache.GetREGION(),
                                    theIniCache.GetDISTRICT(),
                                    theIniCache.GetCITY_() );
  reg_code.RagsHash = GetRagsHashKey(szRags );

  REG_CODE rc;
  memcpy(&rc, &reg_code, sizeof(rc) );
  CString sRegKey = BinToMyHex( (LPTSTR)&reg_code, sizeof(reg_code)-sizeof(reg_code.XorValue), reg_code.XorValue );

#ifdef _DEBUG
  sRegKey = _T("5Б81-22ТД-Т8М9-ГГ85-8ТЛ1-22ТД-8ТЛ1-22ТД");
#endif

  g_pMachine->AddCommand( new CIsDebuggerPresent(&m_Brush, this) );

  GetDlgItem(IDC_REGCODE)->SetFont(&m_Font);
  for( int k = 0; k < 6; k++ ) {
    GetDlgItem(IDC_KEY1+k)->SetFont(&m_Font);
  }

#ifdef NEW_REG
  GetDlgItem(IDC_REGCODE)->SetWindowText(GetNewRegCode());
#else
  GetDlgItem(IDC_REGCODE)->SetWindowText(sRegKey);
#endif

  #ifdef _DEBUG
  if( NULL==m_pValidLC ) {
    CString sLC;
  #ifdef NEW_REG
    CString szRC = GetNewRegCode();

    szRC.Replace("-", "");
    CString szPwd    = szRC.Left(8);
    CString szRagsID = RegCrypt(szPwd, szRC.Mid( 8, 8), false);
    CString szRags   = RegCrypt(szPwd, szRC.Mid(16, 8), false);
    CString szRDC    = RegCrypt(szPwd, szRC.Mid(24, 8), false);

    // 1. new pwd = adler(Crypted regkey);
    CString s, szNewPWD;
    uLong adler = adler = adler32(0L, Z_NULL, 0);
    adler = adler32(adler, (const Bytef *)(LPCTSTR)szRC, szRC.GetLength());
    s.Format(_T("%lu"), adler);
    szNewPWD = Pad(s, '0', 8);
    // 2. s = new pwd + Crypt(new pwd, Crypted regkey.Mid(8), true) + szRagsID.Left(4);
    sLC.Format(_T("%s%s%s%s%s"),
               szNewPWD,
               RegCrypt(szNewPWD, szRagsID, true),
               RegCrypt(szNewPWD, szRags,   true),
               RegCrypt(szNewPWD, szRDC,    true),
               szRagsID.Left(4)
              );
     // 3. new LicKey = Reverse(s);
     sLC.MakeReverse();
     m_szRealLicKey = sLC;
  #else
    LIC_KEY lc;
    CString szRegion   = theIniCache.GetREGION();
    CString szDistrict = theIniCache.GetDISTRICT();
    CString szCity     = theIniCache.GetCITY_();
    DWORD   dwRagsID   = theIniCache.GetRagsID();
    DWORD   dwXorValue = GetXorValue(0);
    sLC = MakeLICCode(lc, szRegion, szDistrict, szCity, szRags, dwRagsID,dwXorValue);

  #endif
    for( int i(0); i < 6; i++ ) {
      GetDlgItem(IDC_KEY1+i)->SetWindowText(sLC.Mid(i*6,6));
    }
  }
  #endif
  if ( false==m_szValidRegCode.IsEmpty() ) {
    for( int i(0); i < 6; i++ ) {
      GetDlgItem(IDC_KEY1+i)->SetWindowText(m_szValidRegCode.Mid(i*6,6));
    }
  }

  if ( m_nDates < 160 ) {
    GetDlgItem(IDC_REG_LATER)->ShowWindow(SW_SHOW);
  }
}
/////////////////////////////////////////////////////////////////////////////
// CRegDlg message handlers
BOOL CRegDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();

  m_btnLater.SetIcon(IDI_WATCH);

  if ( 0==m_RTF_ID )
    m_RTF_ID = IDR_RTF1;

	// TODO: Add extra initialization here
  HRSRC hrsrc = ::FindResource(AfxGetResourceHandle(), MAKEINTRESOURCE(m_RTF_ID), "RTF");
  if ( NULL==hrsrc )
    return FALSE;
  
  HGLOBAL hGlobal = ::LoadResource(AfxGetResourceHandle(), hrsrc);
  LPVOID pData = ::LockResource(hGlobal);
  if ( NULL==pData )
    return FALSE;
  
  CString s = (LPCTSTR)pData;
  m_InfoText.SetRTF( s );

  GetDlgItem(IDC_RAGS)    ->SetWindowText(theIniCache.GetRAGS());
  GetDlgItem(IDC_REGION)  ->SetWindowText(theIniCache.GetREGION());
  GetDlgItem(IDC_DISTRICT)->SetWindowText(theIniCache.GetDISTRICT());
  GetDlgItem(IDC_CITY)    ->SetWindowText(theIniCache.GetCITY_());

  m_Brush.CreateSolidBrush(RGB(255, 255, 255));
	m_Font.CreateFont(-12, 0, 0, 0, 
		FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("MS Sans Serif"));


  m_cmbPeriod.AddString(_T("1 тиждень"));
  m_cmbPeriod.AddString(_T("2 тижні"));
  m_cmbPeriod.AddString(_T("5 тижнів (місяць)"));
  m_cmbPeriod.AddString(_T("10 тижнів (2 місяці)"));
  m_cmbPeriod.AddString(_T("26 тижнів (пів-року)"));
  m_cmbPeriod.AddString(_T("52 тижні (рік)"));

  m_cmbPeriod.SetCurSel(0);

  OnReinit();


  if ( g_szLastLDate.GetLength()==8 ) {
    COleDateTime odt;
    odt.SetDateTime( atol(g_szLastLDate.Mid(0,4)), atol(g_szLastLDate.Mid(4,2)), atol(g_szLastLDate.Mid(6,2)), 0, 0, 0);
    m_StartDate.SetTime(odt);

    if ( theIniCache.m_fLimitedLicence && g_nDaysRemaining > 7) {
      m_StartDate.EnableWindow(false);
    }

    CString szLKey = theIniCache.GetLKey();
    if ( szLKey.GetLength()==36 ) {
      for( int i = 0; i < 6; i++ ) {
        CString s  = szLKey.Mid(i*6, 6);
        CWnd* pWnd = GetDlgItem(IDC_KEY1+i);
        pWnd->SetWindowText(s);
        if ( theIniCache.m_fLimitedLicence && g_nDaysRemaining > 7) {
          pWnd->EnableWindow(false);
        }
      }
    }
  }

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CRegDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) {
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

  if ( CTLCOLOR_EDIT==nCtlColor && pWnd->GetDlgCtrlID()==IDC_REGCODE) {
    pDC->SetTextColor(RGB(0, 0, 0));
    pDC->SetBkColor(RGB(255,255,255));
    return m_Brush;
  }
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

LRESULT CRegDlg::OnKickIdle(WPARAM wParam, LPARAM lParam) {
  if ( m_nDates < 140 ) {
     if ( GetKeyState(VK_SHIFT)  < 0 &&
          GetKeyState(VK_CONTROL) < 0 &&
          GetKeyState(VK_MENU)    < 0 ) {
      GetDlgItem(IDC_REG_LATER)->ShowWindow(SW_SHOW);
    }
  }
  return 0;//CDialogEx::OnKickIdle(wParam, lParam);
}
void CRegDlg::OnChangeKey(UINT idKey) {
  CString s;
  GetDlgItem(idKey)->GetWindowText(s);
  if ( s.GetLength()==6 ) {
    CWnd* pNext = GetDlgItem(idKey)->GetWindow(GW_HWNDNEXT);
    if ( pNext )
      pNext->SetFocus();
  }
}
void CRegDlg::OnChangeKey1() { OnChangeKey(IDC_KEY1); }
void CRegDlg::OnChangeKey2() { OnChangeKey(IDC_KEY2); }
void CRegDlg::OnChangeKey3() { OnChangeKey(IDC_KEY3); }
void CRegDlg::OnChangeKey4() { OnChangeKey(IDC_KEY4); }
void CRegDlg::OnChangeKey5() { OnChangeKey(IDC_KEY5); }
void CRegDlg::OnChangeKey6() { OnChangeKey(IDC_KEY6); }

void CRegDlg::OnYes() {
	// TODO: Add extra validation here
  CString sLC, s;
  g_pMachine->AddCommand( new CIsDebuggerAttached(this, &theIniCache) );
  for( int i(0); i < 6; i++ ) {
    GetDlgItem(IDC_KEY1+i)->GetWindowText(s);
    sLC += s;
  }

  if ( CheckNewLicKey(sLC) ) {
    theIniCache.SetLKey(sLC);
	  CDialogEx::OnYes();
    return;
  }
  else if ( IsValidLicenceKey(sLC) ) {
    theIniCache.SetLKey(sLC);
	  CDialogEx::OnYes();
    return;
  }


  COleDateTime odt;
  if ( m_StartDate.GetTime(odt) ) {
    CString szPeriod;
    int iPeriod = m_cmbPeriod.GetCurSel();
    m_cmbPeriod.GetLBText(iPeriod, szPeriod);

    iPeriod = atol(szPeriod)*7;

    
    BYTE baEncrypt[24];
    CString szExpiration, szHexString, szEncryptHex;
    szExpiration.Format(_T("%d%04d%02d%02d%03d"), odt.GetDayOfWeek(), odt.GetYear(), odt.GetMonth(), odt.GetDay(), iPeriod);
    szHexString = BinToHexString(szExpiration, szExpiration.GetLength());
    memcpy(baEncrypt, szHexString, 24);

    CCrypto crypt;    // vnk@ukr.net Vladimir.Koltsov@gmail.com
    //crypt.SetCryptoKey("Vladimir.Koltsov@gmail.com", 26);
    crypt.SetCryptoKey("vnk@ukr.net", 10);
    crypt.Encrypt(baEncrypt, 24);

    BinToHexString((char*)baEncrypt, 24, szEncryptHex.GetBuffer(64), 50);
    szEncryptHex.ReleaseBuffer();

#ifdef _DEBUG
    CString szDate, szHexDate;
    BYTE baDecryptBin[48];
    HexStringToBin(szEncryptHex, szEncryptHex.GetLength(), baDecryptBin, 24);
    CCrypto Decrypt;
    Decrypt.SetCryptoKey("vnk@ukr.net", 10);
    Decrypt.Decrypt(baDecryptBin, 24);
    memcpy(szHexDate.GetBuffer(24), baDecryptBin, 24);
    szHexDate.ReleaseBuffer();
    HexStringToBin(szHexDate, szHexDate.GetLength(), szDate.GetBuffer(12), 12);
    szDate.ReleaseBuffer();
#endif

    CString szLKey, szSaveLKey;
  
    for( int i = 0; i < 6; i++ ) {
      CString s;
      GetDlgItem(IDC_KEY1+i)->GetWindowText(s);
      szSaveLKey += s;
      s = AddToLSection(s, szExpiration[i*2], szExpiration[i*2+1], (i % 2)!=0);
      szLKey += s;
    }

    BOOL fExpired = false;

    switch( CheckNewLicKey(szLKey) ) {
      case LK_INVALID_LICENCE :
        ::MessageBox(AfxGetMainWnd()->m_hWnd, _T("Неправильний ліцензійний ключ. Спробуєте ще раз."), _T("Помилка"), MB_OK|MB_ICONWARNING);
        return;
      case LK_LICENCE_EXPIRED :
        fExpired = true;
        break;
    }

    COleDateTime odtNow = COleDateTime::GetCurrentTime();
    COleDateTime odtExp = odt;
    odtExp += COleDateTimeSpan(iPeriod+1, 0, 0, 0);

    if ( odtNow > odtExp ) {
      fExpired = true;
    }

    if ( fExpired ) {
      ::MessageBox(AfxGetMainWnd()->m_hWnd, _T("Термін дії ліцензійний ключа вичерпано."), _T("Помилка"), MB_OK|MB_ICONWARNING);
      return;
    }

    /*
    if ( false==CheckNewLicKey(szLKey) ) {
      ::MessageBox(AfxGetMainWnd()->m_hWnd, _T("Неправильний ліцензійний ключ. Спробуєте ще раз."), _T("Помилка"), MB_OK|MB_ICONWARNING);
      return;
    }
*/
    theIniCache.SetLastDate(szEncryptHex, _T("LD"));
    theIniCache.SetLKey(szSaveLKey);
    theRegTimer.Reinit(&odt);
    CDialogEx::OnYes();
    return;
  }
  if ( CheckNewLicKey(sLC) ) {
    theIniCache.SetLKey(sLC);
	  CDialogEx::OnYes();
  }
  else if ( IsValidLicenceKey(sLC) ) {
    theIniCache.SetLKey(sLC);
	  CDialogEx::OnYes();
  }
  else {
    ::MessageBox(AfxGetMainWnd()->m_hWnd, _T("Неправильний ліцензійний ключ. Спробуєте ще раз."), _T("Помилка"), MB_OK|MB_ICONWARNING);
  }
}
void CRegDlg::OnRegLater() {
  EndDialog(IDC_REG_LATER);
}


BOOL RegDlg(CPPToolTip* pTooltip) {
  if ( IsValidRDF() ) {
    return true;
  }
/*
  if ( theIniCache.IsValidLKey() ) {
    return true;
  }
*/
  switch( theIniCache.IsValidLKey() ) {
    case LK_VALID_LICENCE       :
      // AfxMessageBox("LK_VALID_LICENCE");
      return true;
    case LK_LICENCE_NOTEXPIRED  :
      // AfxMessageBox("LK_LICENCE_NOTEXPIRED");
      return true;
  }

  // AfxMessageBox("RegDlg 4");
  int nDates = theIniCache.CalcDates();
  if ( nDates < g_MaxDates ) {
    return true;
  }

  // AfxMessageBox("RegDlg 5");

  CRegDlg dlg;
  dlg.m_nDates = nDates;
  pTooltip->HideTooltip();
  switch( dlg.DoModal() ) {
    case IDYES:
    case IDC_REG_LATER:
      return TRUE;
  }
  return FALSE;
}
BOOL CRegDlg::OnCommand(WPARAM wParam, LPARAM lParam) {
	// TODO: Add your specialized code here and/or call the base class
  if ( BN_CLICKED==HIWORD(wParam) ) {
    switch(LOWORD(wParam)) {
      case IDC_REG_LATER:
        OnRegLater();
        return TRUE;
    }
  }
	return CDialogEx::OnCommand(wParam, lParam);
}

#ifdef _DEBUG
void CRegDlg::MakeKey() {
  COleDateTime odt;
  if ( m_StartDate.GetTime(odt) ) {
    CString szPeriod;
    int iPeriod = m_cmbPeriod.GetCurSel();
    m_cmbPeriod.GetLBText(iPeriod, szPeriod);

    iPeriod = atol(szPeriod)*7;
    
    int nLen = 0;
    CString szExpiration, szHexString, szEncryptHex, szDate;
    BYTE baEncrypt[24], baDecryptBin[48];
    szExpiration.Format(_T("%d%04d%02d%02d%03d"), odt.GetDayOfWeek(), odt.GetYear(), odt.GetMonth(), odt.GetDay(), iPeriod);
    szHexString = BinToHexString(szExpiration, szExpiration.GetLength());
    memcpy(baEncrypt, szHexString, 24);
    CCrypto crypt;    // vnk@ukr.net Vladimir.Koltsov@gmail.com
    //crypt.SetCryptoKey("Vladimir.Koltsov@gmail.com", 26);
    crypt.SetCryptoKey("vnk@ukr.net", 10);
    crypt.Encrypt(baEncrypt, 24);
    BinToHexString((char*)baEncrypt, 24, szEncryptHex.GetBuffer(64), 50);
    szEncryptHex.ReleaseBuffer();     // encrypted data. save it into database
    nLen = szEncryptHex.GetLength();
    HexStringToBin(szEncryptHex, szEncryptHex.GetLength(), baDecryptBin, 24);
    CCrypto decrypt;    // vnk@ukr.net Vladimir.Koltsov@gmail.com
    // decrypt.SetCryptoKey("Vladimir.Koltsov@gmail.com", 26);
    decrypt.SetCryptoKey("vnk@ukr.net", 10);
    decrypt.Decrypt(baDecryptBin, 24);

    HexStringToBin((char*)baDecryptBin, 24, szDate.GetBuffer(16), 16);
    szDate.ReleaseBuffer();

    if ( m_szRealLicKey.GetLength()==36 ) {
      for( int i = 0; i < 6; i++ ) {
        CString s = AddToLSection(m_szRealLicKey.Mid(i*6, 6), szDate[i*2], szDate[i*2+1], (i % 2)==0);
        GetDlgItem(IDC_KEY1+i)->SetWindowText(s);
      }
    }
    
  }
}
#endif

void CRegDlg::OnStartDateChange(NMHDR* pNMHDR, LRESULT* pResult) {
#ifdef _DEBUG
  MakeKey();
#endif
}

void CRegDlg::OnSelendokPeriod()  {
#ifdef _DEBUG
	MakeKey();
#endif
}


void InitValidationInfo() {
  CRDF32Reader rdf;
  g_ValidationInfo.RagsType   = 0;
  g_ValidationInfo.FoundInRDF = 0;

  CString szRags     = theIniCache.GetRAGS();
  TCHAR RagsType     = GetRagsType(szRags);
  CString szRegion   = theIniCache.GetREGION();
  CString szCity     = theIniCache.GetCITY_();
  CString szDistrict = theIniCache.GetDISTRICT();
  DWORD RagsNameHash = GetRagsHashKey(szRags);
  if ( RagsType!=TCHAR('Р') ) {
    g_MaxDates   = 20;
    g_MaxRecords = 20;
  }

  CString szRDF = SetFileExt(GetModuleFileName(), _T("rdf"));
  try {
    if ( rdf.Read(szRDF) ) {

      CString szSect;
      int SectIndex = -1;
      int nItem = -1;
      CRDFItems Items;
      if ( false==szRegion.IsEmpty() ) {
        int nAnyIndex = rdf.GetSection("AnyRags");
        if ( nAnyIndex !=-1  && theApp.m_RagsID != -1 && TCHAR('Р')==RagsType ) {
          rdf.GetSectionBody(nAnyIndex, Items);
          nItem = rdf.FindItem(Items, szRegion);
          if ( nItem >=0 ) {
            g_ValidationInfo.szRegion     = szRegion;
            g_ValidationInfo.szRagsKeys   = Items[nItem].m_szValue;
            g_ValidationInfo.RagsNameHash = RagsNameHash;
            g_ValidationInfo.RagsType     = RagsType;
            g_ValidationInfo.FoundInRDF   = OVER_BY_REGION;
          }
        }
        if ( false==g_ValidationInfo.FoundInRDF ) {
          szSect.Format(_T("%c О %s"), RagsType, szRegion); // [Р О Донецька], [В О Донецька], [В О Луганська], etc
          SectIndex  = rdf.GetSection(szSect);
          if ( SectIndex  >= 0 ) {
            rdf.GetSectionBody(SectIndex, Items);
            nItem = rdf.FindItem(Items, szCity, szDistrict);
            if ( nItem >= 0 ) {
              rdf.FillItem(Items.GetAt(nItem), g_ValidationInfo.szCity, g_ValidationInfo.szDistrict, g_ValidationInfo.szRagsKeys, g_ValidationInfo.szCityKeys, g_ValidationInfo.szDistrictKeys);
              g_ValidationInfo.szRegion = szRegion;
              g_ValidationInfo.RagsNameHash = RagsNameHash;
              g_ValidationInfo.RagsType     = RagsType;
              g_ValidationInfo.FoundInRDF   = true;
            }
          }
        }
      }
      if ( -1 == nItem && false==szCity.IsEmpty() ) {
        szSect.Format(_T("%c М %s"), RagsType, szCity); // [Р М Донецьк], [Р М Луганськ], etc
        SectIndex  = rdf.GetSection(szSect);
        if ( SectIndex  >= 0 ) {
          rdf.GetSectionBody(SectIndex, Items);
          nItem = rdf.FindItem(Items, szCity, szDistrict);
          if ( nItem >= 0 ) {
            rdf.FillItem(Items.GetAt(nItem), g_ValidationInfo.szCity, g_ValidationInfo.szDistrict, g_ValidationInfo.szRagsKeys, g_ValidationInfo.szCityKeys, g_ValidationInfo.szDistrictKeys);
            g_ValidationInfo.szRegion = szRegion;
            g_ValidationInfo.RagsNameHash = RagsNameHash;
            g_ValidationInfo.RagsType     = RagsType;
            g_ValidationInfo.FoundInRDF   = true;
          }
        }
      }
    }
/*
    else {
      AfxMessageBox(_T("Компонент ПК ЕРАГС зруйнован або відсутній. Переустановіть ПК ЕРСГС." ));
    }
*/
  }
  catch(...) {
    Log(_T("Нераспознанная ошибка"), _T("IVInfo 1"));
  }

  ValidOwner fromMDB;
  ValidOwner fromReg;
  ValidOwner fromHKLM;
  UINT    nBytes;
  LPBYTE* pData;
  BOOL fWrite = false;

  memset(&fromReg, 0, sizeof(fromReg));
  memset(&fromMDB, 0, sizeof(fromMDB));
  memset(&fromHKLM,0, sizeof(fromHKLM));

  time_t tNow = time(NULL);

  try {
    if ( false==theIniCache.GetPrivateProfileBinary(_T("Settings"), _T("RFLInfo"), &fromMDB, sizeof(fromMDB))) {
      fromMDB.RagsHash       = RagsNameHash;
      fromMDB.FirstStartDate = tNow;
    }
  }
  catch(...) {
    Log(_T("Нераспознанная ошибка"), _T("IVInfo 2"));
  }

  try {
    if(theApp.GetProfileBinary(_T("Settings"), _T("RFLInfo"), (LPBYTE*)&pData, &nBytes)) {
      if ( sizeof(ValidOwner)==nBytes )
        memcpy(&fromReg, pData, sizeof(fromReg));
      delete [] pData;
    }
    else {
      fromMDB.RagsHash       = RagsNameHash;
      fromMDB.FirstStartDate = tNow;
    }
  }
  catch(...) {
    Log(_T("Нераспознанная ошибка"), _T("IVInfo 3"));
  }

  try {
    g_ValidationInfo.RagsNameHash     = RagsNameHash;
    g_ValidOwner.RagsHash             = RagsNameHash;
    if ( g_ValidationInfo.FoundInRDF ) {
      g_ValidOwner.TotalRecords         = min(fromReg.TotalRecords,         fromMDB.TotalRecords);
      g_ValidOwner.dwValidGeoRecords    = min(fromReg.dwValidGeoRecords,    fromMDB.dwValidGeoRecords);
      g_ValidOwner.dwValidRagsRecords   = min(fromReg.dwValidRagsRecords,   fromMDB.dwValidRagsRecords);
      g_ValidOwner.dwInvalidGeoRecors   = max(fromReg.dwInvalidGeoRecors,   fromMDB.dwInvalidGeoRecors);
      g_ValidOwner.dwVyconcom           = max(fromReg.dwVyconcom,           fromMDB.dwVyconcom);
    }
    if ( 0==g_ValidationInfo.RagsNameHash ) {
      g_ValidationInfo.RagsNameHash     = RagsNameHash;
    }
    CSecurityReg sr;
    if ( sr.ReadBinary1(&fromHKLM, sizeof(fromHKLM)) ) {
      if ( 0==fromHKLM.RagsHash ) {
        fWrite = true;
        fromHKLM.RagsHash = RagsNameHash;
      }
      if ( 0==fromMDB.RagsHash ) {
        fWrite = true;
        fromMDB.RagsHash = RagsNameHash;
      }
      Normalize(&g_ValidOwner, &fromHKLM, &fromMDB);
    }
    if ( Normalize(&g_ValidOwner, &fromReg, &fromMDB) || fWrite) {
      theIniCache.WritePrivateProfileBinary(_T("Settings"), _T("RFLInfo"), &g_ValidOwner, sizeof(g_ValidOwner));
      theApp.WriteProfileBinary(_T("Settings"), _T("RFLInfo"), (LPBYTE)&g_ValidOwner, sizeof(g_ValidOwner));
      sr.WriteBinary1(&g_ValidOwner, sizeof(g_ValidOwner));
    }
  }
  catch(...) {
    Log(_T("Нераспознанная ошибка"), _T("IVInfo 4"));
  }
}

void SaveGeoValidation() {
  ValidOwner vo;

  if ( theIniCache.GetPrivateProfileBinary(_T("Settings"), _T("RFLInfo"), &vo, sizeof(vo))) {
    Normalize(&g_ValidOwner, &g_ValidOwner, &vo);
  }
  theIniCache.WritePrivateProfileBinary(_T("Settings"), _T("RFLInfo"), &g_ValidOwner, sizeof(g_ValidOwner));
  theApp.WriteProfileBinary(            _T("Settings"), _T("RFLInfo"), (LPBYTE)&g_ValidOwner, sizeof(g_ValidOwner));


  CSecurityReg sr;
  sr.WriteBinary1(&g_ValidOwner, sizeof(g_ValidOwner));
}
void SaveGeoValidation(const CString& szRegion, const CString& szDistrict, const CString& szCity, BOOL fWrite) {
  if ( IsEmptyText(szRegion) && IsEmptyText(szDistrict) && IsEmptyText(szCity) )
    return;

  CString szCityName = GetCity(szCity, false);
  szCityName.Replace(_T(" м."), _T(" "));
  szCityName.Replace(',', ' ');
  szCityName.Replace(_T("  "), _T(" "));

  g_ValidOwner.TotalRecords++;
  BOOL fGeoValid = true;
  if ( 0==g_ValidOwner.dwVyconcom && OVER_BY_REGION==g_ValidationInfo.FoundInRDF ) { // It's owner in some region
    CString szRags = theIniCache.GetRAGS();
    if ( szRegion != g_ValidationInfo.szRegion || szRags.Find(g_ValidationInfo.szRagsKeys)==-1 ) {
      fGeoValid = false;
    }
  }
  else if ( g_ValidationInfo.FoundInRDF ) { // It's owner
    if ( false==g_ValidationInfo.szRegion.IsEmpty() ) { // It's need to check region
      if ( DBCompare(g_ValidationInfo.szRegion, szRegion) != 0 )
        fGeoValid = false;
    }
    if ( fGeoValid ) {
      /* commented 20110615
      if (false==g_ValidationInfo.szCity.IsEmpty() )      { // It's need to check city
        if ( DBCompare(g_ValidationInfo.szCity, szCityName) !=0 )
          fGeoValid = false;
      }
      */
      if ( false==g_ValidationInfo.szCityKeys.IsEmpty() ) { // It's need to check city keys
        if ( DBFind(g_ValidationInfo.szCityKeys, szCityName)==-1 ) {
          fGeoValid = false;
        }
        /*
        for( int i(0); fGeoValid; i++ ) {
          CString szTok = GetTok(g_ValidationInfo.szCityKeys, i, "&");
          if ( szTok.IsEmpty() )
            break;
          if ( DBFind(szCityName, szTok)==-1 )
            fGeoValid = false;
        }
        */
      }
    }
    if ( fGeoValid ) {
      if (false==g_ValidationInfo.szDistrict.IsEmpty() )      { // It's need to check district
        if ( DBCompare(g_ValidationInfo.szDistrict, szDistrict) !=0 )
          fGeoValid = false;
      }
      if ( false==g_ValidationInfo.szDistrictKeys.IsEmpty() ) { // It's need to check district keys
        for( int i(0); fGeoValid; i++ ) {
          CString szTok = GetTok(g_ValidationInfo.szDistrictKeys, i, "|");
          if ( szTok.IsEmpty() ) {
            fGeoValid = false;
            break;
          }
          if ( DBFind(szDistrict, szTok) >= 0) {
            break;
          }
        }
      }
    }
  }
  if ( fGeoValid )
    g_ValidOwner.dwValidGeoRecords++;
  else
    g_ValidOwner.dwInvalidGeoRecors++;
  if ( fWrite ) {
    SaveGeoValidation();
  }
}

void SaveDateValidation(const COleDateTime& sd, const COleDateTime& odt) {
/*
  if ( odt.GetStatus()==COleDateTime::valid ) {
    COleDateTimeSpan ts = sd - odt;
    if ( ts < 0 ) {
    }
  }
*/
}

void SaveDateValidation(const COleDateTime* pDate1, const COleDateTime* pDate2, const COleDateTime* pDate3) {
  if ( false==theIniCache.m_fLimitedLicence ) {
    return;
  }
  COleDateTime sd = COleDateTime::GetCurrentTime();
  if ( pDate1 ) {
    SaveDateValidation(sd, *pDate1);
  }
  if ( pDate2 ) {
    SaveDateValidation(sd, *pDate2);
  }
  if ( pDate3 ) {
    SaveDateValidation(sd, *pDate3);
  }
}

#endif // FREE_LICENCE

BOOL IsValidRDF() {
#ifndef FREE_LICENCE
  if ( 0==g_ValidationInfo.FoundInRDF )
    return false;
  if ( OVER_BY_REGION==g_ValidationInfo.FoundInRDF && g_ValidOwner.dwVyconcom > 20 ) {
    g_MaxDates   = 20;
    g_MaxRecords = 20;
  }
  if ( g_ValidOwner.TotalRecords < g_MaxRecords )
    return true;
  if ( g_ValidOwner.dwValidGeoRecords < g_ValidOwner.dwInvalidGeoRecors/3 )
    return false;
  if ( OVER_BY_REGION==g_ValidationInfo.FoundInRDF && g_ValidOwner.dwVyconcom > 20 ) {
    return false;
  }
#endif // FREE_LICENCE
  return true;
}
