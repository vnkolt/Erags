#if !defined(CRYPTO_H_INCLUDED)
#define CRYPTO_H_INCLUDED

CString AddToLSection(CString& szSection, TCHAR c1, TCHAR c2, BOOL fAdd);
DWORD   HexStringToBin(const char* string, DWORD cbInSize, void* destBuf, DWORD cbOutSize);
DWORD   BinToHexString(const char* pInBuf, DWORD cbInSize, char* string, DWORD cbOutSize);
CString BinToHexString(const char* pBuf, DWORD cbSize);

struct SCRYPTOS{
  BYTE ucM;  // 0 - xor, 1 - lshift, 2 - rshift
  BYTE ucC;  // cryptochar
};

#pragma warning (disable : 4201)
union BITS {
  struct { int b0:1; int b1:1; int b2:1; int b3:1;
           int b4:1; int b5:1; int b6:1; int b7:1;
  };
  BYTE byte;
};
#pragma warning (default : 4201)

class CCrypto {
public:
  CCrypto();
  ~CCrypto();

// member variables
protected:  
  DWORD     m_nKeyIndex;
  DWORD     m_dwKeySize;
  DWORD     m_dwCheckSum;
  SCRYPTOS *m_pKeyBuffer;
  
// member fuctions
protected:
  void  DeleteCryptoBuffer();
  void  Crypt(BYTE* pSrc, DWORD dwSize, bool bEncrypt);
public:
  static BYTE RotL(BYTE byte, BYTE shift);
  static BYTE RotR(BYTE byte, BYTE shift);
  static BYTE Mirror(BYTE byte);
  static BYTE MirrorXor(BYTE byte, BYTE bXor, bool bEncrypt);

  void  SetKeyIndex(DWORD nIndex);
  void  SetCryptoKey(const void *pBuffer, DWORD dwSize);
  void  SetCheckSum(DWORD dwCheckSum) { m_dwCheckSum = dwCheckSum; }

  DWORD GetCheckSum() { return m_dwCheckSum; }
  void  Encrypt(void* pBuffer, DWORD dwSize);
  void  Decrypt(void* pBuffer, DWORD dwSize);
};


#endif//CRYPTO_H_INCLUDED