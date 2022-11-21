#if !defined(EXPORT_H_INCLUDED)
#define EXPORT_H_INCLUDED

//
// Export.h
//

class CExportColumn {
public:
  CExportColumn();
  ~CExportColumn();
private:
  VARTYPE   m_ColumnType;
  CString   m_szColumnDBName;
  CString   m_szColumnAltName;
public:
  void            SetColumn(VARTYPE ColumnType, LPCTSTR szColumnDBName, LPCTSTR m_szColumnAltName=NULL);
  const CString&  GetDBName()  { return m_szColumnDBName;  }
  const CString&  GetAltName() { return m_szColumnAltName; }
};

class CExportCell {
public:
  CExportCell();
  CExportCell(const COleVariant& var);
  ~CExportCell();
// Data members
private:
  COleVariant m_data;
// Methods:
public:
  void        SetData(const COleVariant& var);
  COleVariant GetData() { return m_data; }
};

class CExportRow {
public:
  CExportRow(int nColumns);
  ~CExportRow();
private:
  CPtrArray m_Cells;
// Methods:
public:
  void        SetAt(int nCol, const COleVariant& var);
  COleVariant GetAt(int nCol);
  void        DeleteCell(int nCol);
};


class CExportTable {
public:
  CExportTable(int nCols);
  ~CExportTable();

// Data members
private:
  CPtrArray m_Columns;
  CPtrArray m_Rows;
// Methods
public:
  void  DeleteColumn(int nCol);
  void  DeleteColumn(LPCTSTR szColumnName);
  int   GetColumnCount()  { return m_Columns.GetSize(); }
  int   GetRowCount()     { return m_Rows.GetSize();    }
  int   AddRow(); // returns zero-based row index
  void  SetColumn(int nCol, VARTYPE ColumnType, LPCTSTR szColumnDBName, LPCTSTR szColumnAltName=NULL);
  void  SetData(int nCol, int nRow, const COleVariant& var);

  const CString& GetColumnName(int nCol);
  const CString& GetColumnAltName(int nCol);

  COleVariant GetCellData(int nCol, int nRow);
};

#endif // EXPORT_H_INCLUDED