// EnvelopeDlg.cpp : implementation file
//
#include "stdafx.h"
#include "Erags.h"
#include "EnvelopeDlg.h"

#include "DataManager.h"
#include "RList.h"
#include "RNames.h"

#include "..\Common\CyrString.h"
#include "..\Common\MDB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TRANSF_WORD   1 // Word
#define TRANSF_BOS    2 // Begion of string
#define TRANSF_EOS    3 // End of string
#define TRANSF_SUBS   4 // Substrings

CString g_szSender_Region;
CString g_szSender_Index;
CString g_szSender_Country;
CString g_szSender_City;
CString g_szSender_Address;
CString g_szSender;
CString g_szAddressee;
CString g_szAddressee_Region;
CString g_szAddressee_Index;
CString g_szAddressee_Country;
CString g_szAddressee_City;
CString g_szAddressee_Address;

CString MakeCRC(const CString& sKey, BOOL fSender) {
  CString s, sCRC;
  CString szCountry, szRegion, szCity;
  sCRC.Format(_T(" %s "), Trim(sKey));
  if ( fSender ) {
    szCountry = g_szSender_Country;
    szRegion  = g_szSender_Region;
    szCity    = g_szSender_City;
  }
  else {
    szCountry = g_szAddressee_Country;
    szRegion  = g_szAddressee_Region;
    szCity    = g_szAddressee_City;
  }
  s.Format(_T(" %s, "), Trim(szCountry));
  sCRC.Replace(_T(" Д "), s);

  s.Format(_T(" %s, "), Trim(szRegion));
  sCRC.Replace(_T(" О "), s);

  s.Format(_T(" %s, "), Trim(szCity));
  sCRC.Replace(_T(" М "), s);

  if ( sCRC.Left(5)==_T(" ВІД ")) {
    sCRC = sCRC.Mid(5);
  }
  else if ( sCRC.Left(4)==_T(" ОД ")) {
    sCRC = sCRC.Mid(4);
  }
  for( int i(0); i < 3; i++ ) {
    sCRC = Trim(sCRC);
    sCRC.Replace(_T("  "), _T(" "));
    sCRC.Replace(_T(",,"), _T(","));
    sCRC.TrimLeft(',');
    sCRC.TrimRight(',');
  }
  return sCRC;
}

CString GetCityBefore(const CString& s, int offset) {
  CString sToken;
  while ( offset >= 0 ) {
    sToken = s.Mid(offset);
    if ( sToken.GetLength() && (sToken.GetAt(0)==' ' || sToken.GetAt(0)=='.') ) {
      sToken.TrimLeft('.');
      sToken.TrimLeft(' ');
      return GetTok(sToken, 0, ",.");
    }
    offset--;
  }
  sToken.TrimLeft('.');
  sToken.TrimLeft(' ');
  return GetTok(sToken, 0, " ");
}

CString GetIndexFromAddress(const CString& sAddress) {
  CString sIndex;
  int nTok = 0;
  while ( true ) {
    CString sTok = GetTok(sAddress, nTok++, _T("., \t") );
    int nLen = sTok.GetLength();
    if ( 5 <= nLen && nLen <= 6 && IsDigit(sTok) ) {
      sIndex = sTok;
      break;
    }
    if ( sTok.IsEmpty() )
      break;
  }
  return sIndex;
}

CString GetRegionFromAddress(const CString& sAddress) {
  CString sRegion;
  int offs = sAddress.Find(_T("обл."));
  if ( offs > 0 ) {
    sRegion = GetTokenBefore(sAddress, offs-6);
    if ( FALSE==sRegion.IsEmpty() )
      sRegion += _T(" обл.");
  }
  else {
    offs = sAddress.Find(_T("область"));
    if ( offs  > 0 ) {
      sRegion = GetTokenBefore(sAddress, offs-9);
      if ( FALSE==sRegion.IsEmpty() )
        sRegion += _T(" область");
    }
    else {
      offs = sAddress.Find(_T("Крим,"));
      if ( offs >= 0 )
        sRegion = _T("АР Крим");
    }
  }
  return sRegion;
}
CString GetCityFromAddress(const CString& sAddress) {
  CString sCity;
  LPCTSTR szTypes[] = { _T("м."), _T("місто "), _T("смт."), _T("смт"), _T("с."),  _T("сел."),  _T("с-ще"), _T("селище") };

  for (int i(0); i < sizeof(szTypes)/sizeof(szTypes[0]); i++ ) {
    int offs = sAddress.Find(szTypes[i]);
    if ( offs >= 0 ) {
      CString s = GetCityBefore(sAddress, offs+strlen(szTypes[i])+2);
      sCity.Format(_T("%s %s"), szTypes[i], s);
      sCity.Replace(_T("  "), _T(" "));
      sCity.TrimRight(',');
      LPCTSTR szDistrictWord = _T(" р-н");

      int nDistrict = sAddress.Find(szDistrictWord);
      if ( -1==nDistrict ) {
        szDistrictWord = _T(" район");
        nDistrict = sAddress.Find(szDistrictWord);
      }
      if ( nDistrict >=0 && nDistrict < offs ) {
        CString szDistrict = GetDistrictFromAddress(sAddress, nDistrict);
        if ( nDistrict < offs ) {
          CString s;
          s.Format(_T("%s, %s %s"), sCity, szDistrict, Trim(szDistrictWord));
          return s;
        }
      }
      
      break;
    }
  }
  return sCity;
}

CString GetAddressFromAddress(const CString& sAddress) {
  CString sCity;
  LPCTSTR szTypes[] = { _T("вул."),  _T("вул-ця"), _T("вулиця"),
                        _T("бул."),  _T("б-р"),    _T("бульвар"),
                        _T("пр."),   _T("пр-кт"),  _T("пр-т"),  _T("проспект"),
                        _T("пл"),    _T("пл."),    _T("площа"),
                        _T("пр."),   _T("пр-д"),   _T("проїзд"),
                        _T("пров."), _T("провулок"),
                        _T("спуск"),
                        _T("м-р"),   _T("м-н"),    _T("мікрорайон"),
                        _T("кв."),   _T("кв-л"),   _T("квартал"),
                        _T("Будинок Рад"),
                        _T("шосе")
                         };

  for (int i(0); i < sizeof(szTypes)/sizeof(szTypes[0]); i++ ) {
    int offs = sAddress.Find(szTypes[i]);
    if ( offs >= 0 ) {
      CString s = sAddress.Left(offs);
      offs = s.ReverseFind(',');
      if ( offs >= 0 ) {
        sCity = sAddress.Mid(offs+1);
        sCity.TrimLeft();
        sCity.TrimRight();
        sCity.TrimLeft(',');
      }
      break;
    }
  }
  return sCity;
}

/////////////////////////////////////////////////////////////////////////////
// CTransList
int TransRecCmp(const void *a1, const void *a2) {
  TransRecord *p1 = *(TransRecord**)a1,
              *p2 = *(TransRecord**)a2;

  if ( p1->szUkr.GetLength() != p2->szUkr.GetLength() ) {
    return p2->szUkr.GetLength() - p1->szUkr.GetLength();
  }
  return CyrCompare(p1->szUkr, p2->szUkr);
}
CTransList::CTransList() {
}
CTransList::~CTransList() {
  Clear(m_Words);
  Clear(m_Begins);
  Clear(m_Ends);
  Clear(m_Subs);
}
void CTransList::Clear(CPtrArray& array) {
  for( int i(0); i < array.GetSize(); i++ ) {
    TransRecord* pRecord = (TransRecord*)array.GetAt(i);
    delete pRecord;
  }
  array.RemoveAll();
}
void CTransList::Sort(CPtrArray& array) {
  qsort( array.GetData(), array.GetSize(), sizeof(TransRecord*), TransRecCmp);
}
BOOL CTransList::Load() {
  CWaitCursor wc;
  if ( FALSE==theDataManager.m_dbLists.IsOpen() ) {
    return FALSE;
  }
  CDaoRecordset rs(&theDataManager.m_dbLists);
  try {
    rs.Open(dbOpenTable, "[TRANSLATOR]", dbReadOnly);
    while ( !rs.IsEOF() ) {
      TransRecord* pRecord = new TransRecord;
      pRecord->lType = GetFieldLong(&rs,  _T("TYPE"));
      pRecord->szUkr = GetFieldString(&rs, _T("UKR"));
      pRecord->szRus = GetFieldString(&rs, _T("RUS"));
      switch(pRecord->lType) {
        case TRANSF_WORD:     // 1 Word
          m_Words.Add ( pRecord );
          break;
        case TRANSF_BOS :     // 2 Begion of string
          m_Begins.Add ( pRecord );
          break;
        case TRANSF_EOS :     // 3 End of string
          m_Ends.Add ( pRecord );
          break;
        case TRANSF_SUBS:     // 4 Substrings
          m_Subs.Add ( pRecord );
          break;
        default:
          delete pRecord;
          break;
      }
      rs.MoveNext();
    }
  }
  catch (CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError(); // to do logstring
    #endif
    e->Delete();
  }
  Sort(m_Words);
  Sort(m_Begins);
  Sort(m_Ends);
  Sort(m_Subs);
  return TRUE;
}

void CTransList::FillTokenArray(const char* szSrc, CStringArray& tokens) {
  CString s(szSrc), sToken;
  for( int i(0); i < s.GetLength(); i++ ) {
    TCHAR c = s[i];
    if ( c==' ' ) {
      if ( FALSE==sToken.IsEmpty() ) {
        tokens.Add( sToken );
        sToken.Empty();
        continue;
      }
      tokens.Add( CString(c) );
    }
    else {
      sToken += c;
    }
  }
  if ( FALSE==sToken.IsEmpty() ) {
    tokens.Add( sToken );
  }
}

void CTransList::Translate(CEraEdit* pEdit) {
  CString s = pEdit->GetText();
  // Susbstrings:
  // Words
  int nWordsProcessed = 0, i;
  for( i = 0; i < m_Subs.GetSize(); i++ ) {
    TransRecord* pRecord = (TransRecord*)m_Subs.GetAt(i);
    // s.Replace(pRecord->szUkr, pRecord->szRus);
    if ( s.Find(pRecord->szUkr) >= 0 ) {
      s.Replace(pRecord->szUkr, pRecord->szRus);
      // if ( TRANSF_WORD==pRecord->lType ) {
        nWordsProcessed++;
      //}
    }
  }
  CStringArray Tokens;
  FillTokenArray(s, Tokens);
  for( i = 0; i < m_Words.GetSize(); i++ ) {
    TransRecord* pRecord = (TransRecord*)m_Words.GetAt(i);
    for( int t(0); t < Tokens.GetSize(); t++ ) {
      CString sToken = Tokens.GetAt(t);
      if ( CyrStriCmp(sToken, pRecord->szUkr)==0 ) {
        if ( IsCyrUpper(sToken[0]) ) { // первая буква большая?
          sToken = MakeCanonicalName(pRecord->szRus);
        }
        else {
          sToken = pRecord->szRus;
        }
        Tokens.SetAt(t, sToken);
        nWordsProcessed++;
      }
    }
  }
  if ( nWordsProcessed < Tokens.GetSize() ) {
    // BOS
    for(  i = 0; i < m_Begins.GetSize(); i++ ) {
      TransRecord* pRecord = (TransRecord*)m_Begins.GetAt(i);
      for( int t(0); t < Tokens.GetSize(); t++ ) {
        int size = pRecord->szUkr.GetLength();
        CString sToken = Tokens.GetAt(t);
        if ( sToken.Left(size)==pRecord->szUkr ) {
          sToken.Format(_T("%s%s"), pRecord->szRus, sToken.Mid(size));
          Tokens.SetAt(t, sToken);
          nWordsProcessed++;
        }
      }
    }
  }
  if ( nWordsProcessed < Tokens.GetSize() ) {
    // EOS
    for(  i = 0; i < m_Ends.GetSize(); i++ ) {
      TransRecord* pRecord = (TransRecord*)m_Ends.GetAt(i);
      for( int t(0); t < Tokens.GetSize(); t++ ) {
        int size = pRecord->szUkr.GetLength();
        CString sToken = Tokens.GetAt(t);
        CString szComa;
        if ( sToken.Right(1)==_T(",") ) {
          szComa = _T(",");
          sToken.TrimRight(_T(","));
        }
        if ( sToken.Right(size)==pRecord->szUkr ) {
          sToken.Format(_T("%s%s%s"), sToken.Left(sToken.GetLength()-size), pRecord->szRus, szComa);
          Tokens.SetAt(t, sToken);
        }
      }
    }
  }

  s.Empty();
  for( i = 0; i < Tokens.GetSize(); i++ ) {
    s += Tokens.GetAt(i);
    s += ' ';
  }
  s.Replace(_T("І"), _T("И"));  s.Replace(_T("і"), _T("и"));
  s.Replace(_T("Ї"), _T("И"));  s.Replace(_T("ї"), _T("и"));
  s.Replace(_T("Є"), _T("Е"));  s.Replace(_T("є"), _T("е"));
  s.Replace(_T("Ґ"), _T("Г"));  s.Replace(_T("ґ"), _T("г"));  // ’' '
  s.Replace(_T("'"), _T("ь"));
  s = Trim(s);
  pEdit->SetWindowText(s);
}
/////////////////////////////////////////////////////////////////////////////
// CEnvelopeDlg dialog
CEnvelopeDlg::CEnvelopeDlg(UINT nPrintID, CWnd* pParent /*=NULL*/)
          	:CDialogEx(CEnvelopeDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CEnvelopeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  m_pRecord = NULL;
  switch(nPrintID) {
    case ID_PRINT_ENVELOPE_A4_RUS:
    case ID_PRINT_ENVELOPE_DL_RUS:
    case ID_PRINT_ENVELOPE_229x162_RUS:
    case ID_PRINT_ENVELOPE_229x114_RUS:
    case ID_PRINT_ENVELOPE_162x114_RUS:
      m_fTranslate = TRUE;
      break;
    default:
      m_fTranslate = FALSE;
      break;
  }
}

void CEnvelopeDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEnvelopeDlg)
  DDX_Control(pDX, IDC_FRAME1, m_Frame1);
  DDX_Control(pDX, IDC_FRAME2, m_Frame2);
	DDX_Control(pDX, IDC_SENDER_REGION, m_Sender_Region);
	DDX_Control(pDX, IDC_SENDER_INDEX, m_Sender_Index);
	DDX_Control(pDX, IDC_SENDER_COUNTRY, m_Sender_Coutry);
	DDX_Control(pDX, IDC_SENDER_CITY, m_Sender_City);
	DDX_Control(pDX, IDC_SENDER_ADDRESS, m_Sender_Address);
	DDX_Control(pDX, IDC_SENDER, m_Sender);
	DDX_Control(pDX, IDC_ADDRESSEE, m_Addressee);
	DDX_Control(pDX, IDC_ADDRESSEE_REGION, m_Addressee_Region);
	DDX_Control(pDX, IDC_ADDRESSEE_INDEX, m_Addressee_Index);
	DDX_Control(pDX, IDC_ADDRESSEE_COUNTRY, m_Addressee_Coutry);
	DDX_Control(pDX, IDC_ADDRESSEE_CITY, m_Addressee_City);
	DDX_Control(pDX, IDC_ADDRESSEE_ADDRESS, m_Addressee_Address);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEnvelopeDlg, CDialogEx)
	//{{AFX_MSG_MAP(CEnvelopeDlg)
	ON_BN_CLICKED(IDYES, OnYes)
	//}}AFX_MSG_MAP
	ON_WM_HELPINFO()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEnvelopeDlg message handlers
BOOL CEnvelopeDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();
	
	// TODO: Add extra initialization here
  if ( m_fTranslate ) {
    m_fTranslate = m_TransList.Load();

    SetWindowText(_T("Установки печати конверта"));

    GetDlgItem(IDC_FRAME1)->SetWindowText(_T("Адрес отправителя, индекс"));
    GetDlgItem(IDC_FRAME2)->SetWindowText(_T("Адрес получателя, индекс"));

    GetDlgItem(IDC_SENDER_LABEL)    ->SetWindowText(_T("Отправитель"));
    GetDlgItem(IDC_ADDRESSEE_LABEL) ->SetWindowText(_T("Получатель"));

    GetDlgItem(IDC_SENDER_COUNTRY_LABEL   )->SetWindowText(_T("Страна"));
    GetDlgItem(IDC_ADDRESSEE_COUNTRY_LABEL)->SetWindowText(_T("Страна"));

    GetDlgItem(IDC_SENDER_CITY_LABEL      )->SetWindowText(_T("г. (с. п-к)"));
    GetDlgItem(IDC_ADDRESSEE_CITY_LABEL   )->SetWindowText(_T("г. (с. п-к)"));

    GetDlgItem(IDC_SENDER_ADDRESS_LABEL   )->SetWindowText(_T("Адрес"));
    GetDlgItem(IDC_ADDRESSEE_ADDRESS_LABEL)->SetWindowText(_T("Адрес"));

    GetDlgItem(IDC_SENDER_INDEX_LABEL     )->SetWindowText(_T("Индекс"));
    GetDlgItem(IDC_ADDRESSEE_INDEX_LABEL  )->SetWindowText(_T("Индекс"));

    GetDlgItem(IDYES                      )->SetWindowText(_T("Да"));
    GetDlgItem(IDNO                       )->SetWindowText(_T("Нет"));
  
  }
  CString s;

  if ( m_pRecord ) {
    s = DecodeRagsName(m_pRecord->m_Fullname);
    if ( false==s.IsEmpty() ) {
      s.SetAt(0, CyrUpper(s.GetAt(0)) );
    }
    m_Addressee.SetWindowText(s);
    m_Addressee_Index.SetWindowText(GetIndexFromAddress(m_pRecord->m_Address));
    m_Addressee_Region.SetWindowText(GetRegionFromAddress(m_pRecord->m_Address));
    m_Addressee_City.SetWindowText(GetCityFromAddress(m_pRecord->m_Address));
    m_Addressee_Address.SetWindowText(GetAddressFromAddress(m_pRecord->m_Address));
    if ( m_fTranslate ) {
      m_TransList.Translate( &m_Addressee );
      m_TransList.Translate( &m_Addressee_Region );
      m_TransList.Translate( &m_Addressee_City );
      m_TransList.Translate( &m_Addressee_Address );
    }
  }
  if ( theApp.m_RagsID != -1 ) {
    CRListRecord* pRecord = theRList.Lookup(theApp.m_RagsID);
    if ( pRecord ) {
      s = DecodeRagsName(pRecord->m_Fullname);
      if ( false==s.IsEmpty() ) {
        s.SetAt(0, CyrUpper(s.GetAt(0)) );
      }
      m_Sender.SetWindowText(s);
      m_Sender_Index.SetWindowText(GetIndexFromAddress(pRecord->m_Address));
      m_Sender_Region.SetWindowText(GetRegionFromAddress(pRecord->m_Address));
      m_Sender_City.SetWindowText(GetCityFromAddress(pRecord->m_Address));
      m_Sender_Address.SetWindowText(GetAddressFromAddress(pRecord->m_Address));
      if ( m_fTranslate ) {
        m_TransList.Translate( &m_Sender );
        m_TransList.Translate( &m_Sender_Region );
        m_TransList.Translate( &m_Sender_City );
        m_TransList.Translate( &m_Sender_Address );
      }
    }
  }
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEnvelopeDlg::OnYes() {
	// TODO: Add your control notification handler code here
  UpdateData();

  g_szSender         = m_Sender.GetText();
  g_szSender_Country = m_Sender_Coutry.GetText();
  g_szSender_Region  = m_Sender_Region.GetText();
  g_szSender_City    = m_Sender_City.GetText();
  g_szSender_Address = m_Sender_Address.GetText();
  g_szSender_Index   = m_Sender_Index.GetText();
 
  g_szAddressee         = m_Addressee.GetText();
  g_szAddressee_Country = m_Addressee_Coutry.GetText();
  g_szAddressee_Region  = m_Addressee_Region.GetText();
  g_szAddressee_City    = m_Addressee_City.GetText();
  g_szAddressee_Address = m_Addressee_Address.GetText();
  g_szAddressee_Index  = m_Addressee_Index.GetText();

	CDialogEx::OnYes();
}

BOOL CEnvelopeDlg::OnHelpInfo(HELPINFO* pHelpInfo) {
  theApp.OnHelp(_T("PrintEnv"));
  return true;
}
