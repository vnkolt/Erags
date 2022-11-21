#if !defined(MYBTNST_H_INCLUDED)
#define MYBTNST_H_INCLUDED

#include "BtnST.h"

class CMyButtonST : public CButtonST {
public:
	virtual DWORD OnDrawBackground(CDC* pDC, CRect* pRect);
};

#endif // MYBTNST_H_INCLUDED