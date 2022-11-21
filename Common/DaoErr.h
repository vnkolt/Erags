#if !defined(DAOERR_H_INCLUDED)
#define DAOERR_H_INCLUDED

void ResetDaoError();
BOOL IsDaoError();

void    DaoError(CDaoException* e, LPCTSTR szFieldName=NULL, CDaoRecordset* prs=NULL, int nField=-1);
CString FormatDaoError(CDaoException* e);

#endif // DAOERR_H_INCLUDED