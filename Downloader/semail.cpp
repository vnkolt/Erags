#include "stdafx.h"
#include "CSmtp.h"
#include <iostream>

#include "semail.h"

#define test_gmail_tls

struct Translit {
  TCHAR   cyr;
  LPCTSTR lat;
};

Translit g_Translit[] = 
{ {'À', "A" }, {'à', "a" },
  {'Á', "B" }, {'á', "b" },
  {'Â', "V" }, {'â', "v" },
  {'Ã', "G" }, {'ã', "g" },
  {'¥', "G" }, {'´', "G" },
  {'Ä', "D" }, {'ä', "d" },
  {'Å', "E" }, {'å', "e" },
  {'ª', "E" }, {'º', "e" },
  {'¨', "E" }, {'¸', "e" },
  {'Æ', "Zh"}, {'æ', "zh"},
  {'Ç', "Z" }, {'ç', "z" },
  {'È', "Y" }, {'è', "y" },
  {'²', "I" }, {'³', "i" },
  {'¯', "Ji"}, {'¿', "ji"},
  {'Ê', "K" }, {'ê', "k" },
  {'Ë', "L" }, {'ë', "l" },
  {'Ì', "M" }, {'ì', "m" },
  {'Í', "N" }, {'í', "n" },
  {'Î', "O" }, {'î', "o" },
  {'Ï', "P" }, {'ï', "P" },
  {'Ð', "R" }, {'ð', "r" },
  {'Ñ', "S" }, {'ñ', "s" },
  {'Ò', "T" }, {'ò', "t" },
  {'Ó', "U" }, {'ó', "u" },
  {'Ô', "F" }, {'ô', "f" },
  {'Õ', "H" }, {'õ', "h" },
  {'Ü', "'" }, {'ü', "'" },
  {'×', "Ch"}, {'÷', "ch"},
  {'Ø', "Sh"}, {'Ø', "sh"},
  {'Ù', "Sh"}, {'ù', "sh"},
  {'Ö', "Ts"}, {'ö', "ts"},
  {'É', "~" }, {'é', "~" },
  {'Û', "Y" }, {'û', "y" },
  {'Ý', "Ye"}, {'ý', "ye"},
  {'Þ', "Yu"}, {'þ', "yu"},
  {'ß', "Ya"}, {'ÿ', "ya"}
};

CString ToTranslit(LPCTSTR sz) {
  CString s;
  int nLen = strlen(sz);
  for( int i(0); i < nLen; i++ ) {
    bool bFound = false;
    for( int j(0); j < sizeof(g_Translit)/sizeof(g_Translit[0]); j++ ) {
      if ( sz[i]==g_Translit[j].cyr ) {
        s += g_Translit[j].lat;
        bFound = true;
        break;
      }
    }
    if ( false==bFound ) {
      s += sz[i];
    }
  }
  return s;
}


TCHAR szPassword[] = { 'E'^17, 'r'^18, 'a'^19, 'g'^20, 's'^21, 'D'^22, 'o'^23, 'w'^24, 'n'^25, 'l'^26, 'o'^27, 'a'^28, 'd'^29, 'e'^30, 'r'^31, 'N'^32, 'o'^33, 't'^34, 'i'^35, 'f'^36, 'i'^37, 'c'^38, 'a'^39, 't'^40, 'i'^41, 'o'^42, 'n'^43 };

TCHAR szLogin[]    = { 'E'^ 4, 'r'^ 5, 'a'^ 6, 'g'^ 7, 's'^ 8, 'N'^ 9, 'o'^10, 't'^11, 'i'^12, 'f'^13, 'i'^14, 'e'^15, 'r'^16 };

//TCHAR szEnglish[]  = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 
TCHAR szEmail[]    = { 'E'^38, 'r'^39, 'a'^40, 'g'^41, 's'^42, 'N'^43, 'o'^44, 't'^45, 'i'^46, 'f'^47, 'i'^48, 'e'^49, 'r'^50, '@'^51, 'g'^52, 'm'^53, 'a'^54, 'i'^55, 'l'^56, '.'^57, 'c'^58, 'o'^59, 'm'^60 };

CString GetSecretWord(LPCTSTR szSource, int nLen, TCHAR xor) {
  CString s;
  for( int i(0); i < nLen; i++ ) {
    TCHAR xchar = szSource[i] ^ xor;
    s += xchar;
    xor++;
  }
  return s;
}

bool sendemail(const CStringArray& sa) {
	bool fOk = true;

	try {
		CSmtp mail;

#if defined(test_gmail_tls)
		mail.SetSMTPServer("smtp.gmail.com",587);
		mail.SetSecurityType(CSmtp::USE_TLS);
#elif defined(test_gmail_ssl)
		mail.SetSMTPServer("smtp.gmail.com",465);
    //mail.SetSMTPServer("smtp.ukr.net",465);
		mail.SetSecurityType(CSmtp::USE_SSL);
#elif defined(test_hotmail_TLS)
		mail.SetSMTPServer("smtp.live.com",25);
		mail.SetSecurityType(CSmtp::USE_TLS);
#elif defined(test_aol_tls)
		mail.SetSMTPServer("smtp.aol.com",587);
		mail.SetSecurityType(CSmtp::USE_TLS);
#elif defined(test_yahoo_ssl)
		mail.SetSMTPServer("plus.smtp.mail.yahoo.com",465);
		mail.SetSecurityType(CSmtp::USE_SSL);
#endif

    //CString s = GetSecretWord(szLogin, sizeof(szLogin), 4);
    //s = GetSecretWord(szPassword, sizeof(szPassword), 17);
    //s = GetSecretWord(szEmail, sizeof(szEmail), 38);

		mail.SetLogin(GetSecretWord(szLogin, sizeof(szLogin), 4));
		mail.SetPassword(GetSecretWord(szPassword, sizeof(szPassword), 17));

  	mail.SetSenderName("ERAGS System");
  	mail.SetSenderMail(GetSecretWord(szEmail, sizeof(szEmail), 38));
  	
    mail.SetReplyTo("erags@ukr.net");
  	mail.SetSubject("ERAGS System Notification");
  	
    mail.AddRecipient("erags@ukr.net");
  	mail.SetXPriority(XPRIORITY_NORMAL);
  	mail.SetXMailer("The Bat! (v3.02) Professional");
  	mail.AddMsgLine("Hello,");
		mail.AddMsgLine("");
    int nSize = sa.GetSize();
    for( int i(0); i < nSize; i++ ) {
		  // mail.AddMsgLine("...");
      mail.AddMsgLine( ToTranslit(sa[i]) );
    }
		mail.AddMsgLine("");
		mail.AddMsgLine("Regards");
		// mail.ModMsgLine(5,"regards");
		// mail.DelMsgLine(2);
		mail.AddMsgLine("User");
		
  		//mail.AddAttachment("../test1.jpg");
  		//mail.AddAttachment("c:\\test2.exe");
		//mail.AddAttachment("c:\\test3.txt");
		mail.Send();
	}
	catch(ECSmtp e) {
		// std::cout << "Error: " << e.GetErrorText().c_str() << ".\n";
		fOk = false;
	}
/*
	if(!bError)
		std::cout << "Mail was send successfully.\n";
*/
	return fOk;
}
