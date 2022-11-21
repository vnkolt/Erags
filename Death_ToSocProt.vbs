'
' ��������!!!
'
' ���� ������ ������ ��� �������� ��������� ����� � ������� DBF ��� ������ ���������� ������ ���������.
'
' � ������ ������������ ���� ������ ��������������
' 
'                  � � � � � 
' 
'          18.05.2006  N 188/43/5
' 
'       ��� ������������ ������� ��������� ������� 
'         ��������� ���� ��������� ����� ������� 
'          ����� �� ����������� ������� ��������� 
'           ���������� ��� ��������, �� ������� 
' 
'      http://zakon1.rada.gov.ua/cgi-bin/laws/main.cgi?nreg=z0590-06
'
' ����������� ����� ������� ����� �������� � ������ �� ����� �������� ��� ������������
' ��������� DBF-�����.
'
'
Const D_FORM_Len   = 8
Const D_PERIOD_Len = 4
Const C_OKPO_Len   = 8
Const REG_Len      = 42
Const DIST_Len     = 55
Const POL_Len      = 1
Const FULLNAME_Len = 30
Const NAME_Len     = 15
Const FULLOT_Len   = 20
Const TIN_Len      = 10
Const D_ROG_Len    = 8
Const D_REEST_Len  = 8

Dim rsFieldNames, rsFields
' ����������� ���� (���������������� ���� ���)
Dim D_FORM       ' ���� ������� ����������
Dim C_OKPO       ' ��� ����� ��������� ���� ��������� �����
Dim CodeTableLen

' ������� ����� � ������������ ������� ��� �����:

Dim iSEX         ' ������ ���� "SEX" � ������� rsFieldNames
Dim iDATEREG     ' ������ ���� "DATEREG" � ������� rsFieldNames
Dim iRP_REGION   ' ������ ���� "RP_REGION" (������� ����������) � ������� rsFieldNames
Dim iRP_DISTRICT ' ������ ���� "RP_DISTRICT" (����� ����������) � ������� rsFieldNames
Dim iSURNAME     ' ������ ���� "SURNAME" (�������) � ������� rsFieldNames
Dim iNAME        ' ������ ���� "NAME" (���) � ������� rsFieldNames
Dim iPATRONYMIC  ' ������ ���� "PATRONYMIC" (��������) � ������� rsFieldNames
Dim iTAX_CODE    ' ������ ���� "TAX_CODE" (���) � ������� rsFieldNames
Dim iBIRTH_DATE  ' ������ ���� "BIRTH_DATE" (���� ��������) � ������� rsFieldNames
Dim iDEATH_DATE  ' ������ ���� "DEATH_DATE" (���� ������) � ������� rsFieldNames

Dim WinCyrL      ' ��������� Win-1251 (lower-case)
Dim WinCyrU      ' ��������� Win-1251 (upper-case)

Dim RUSCIIL      ' ������ ������������ �������������� ��������� RUSCII (CP866) � Win-1251 (lower-case)
Dim RUSCIIU      ' ������ ������������ �������������� ��������� RUSCII (CP866) � Win-1251 (upper-case)

Const MakeUpper  = 1 ' ��������� 0 ������ 1, ���� �� ����� �������������� � ������� �������

Function GetRSFieldIndex(fldName, count)
  Dim i
  for i=0 to count
    if ( fldName=rsFieldNames(i) ) then
      GetRSFieldIndex = i
      Exit Function
    end if
  next
  GetRSFieldIndex = -1 ' ������� �� ������
End Function

Private Function FieldNotFound(fldName)
  FieldNotFound = "�������: ���� " & fldName & " �� � ����� �������� ������ ������."
End Function

'
' Initialize - ������������ ������� ��� ����� �������.
' ���������: fldNames - ������ � ������� ����� ������ ������� ����������� �������� ASCII 1
'            OKPO - ��� ���� ������
' ���� ��������� ������ ������� ������������ ����� � ������� DEATH ����� �� ����� (��. dbTemplate.mdb)
'
Public Function Initialize(fldNames, OKPO)
  rsFieldNames = Split(fldNames, Chr(1), -1, 0)
  rsFields     = UBound(rsFieldNames)
  D_FORM       = CStr(Year(Now)) & Right("0" & CStr(Month(Now)),2) & Right("0" & CStr(Day(Now)),2)
  C_OKPO       = OKPO
  if ( Len(C_OKPO) <> C_OKPO_Len ) then
    Initialize = "�������: ���� C_OKPO ������� ���� �������� " & CStr(C_OKPO_Len) & " ����."
    Exit Function
  end if
  iSEX         = GetRSFieldIndex("SEX"         , rsFields) ' ��� ���������� ��� '0' (�������) ��� '1' - �������
  if ( iSEX = -1 ) then
    Initialize = FieldNotFound("SEX")
    Exit Function
  end if
  iDATEREG     = GetRSFieldIndex("DATEREG"     , rsFields) ' ���� ����������� ��������� ��� YYYYMMDD
  if ( iDATEREG = -1 ) then
    Initialize = FieldNotFound("DATEREG")
    Exit Function
  end if
  iRP_REGION   = GetRSFieldIndex("RP_REGION"   , rsFields)  ' ������� ����������
  if ( iRP_REGION = -1 ) then
    Initialize = FieldNotFound("RP_REGION")
    Exit Function
  end if
  iRP_DISTRICT = GetRSFieldIndex("RP_DISTRICT" , rsFields)  ' ����� ����������
  if ( iRP_DISTRICT = -1 ) then
    Initialize = FieldNotFound("RP_DISTRICT")
    Exit Function
  end if
  iSURNAME     = GetRSFieldIndex("SURNAME"     , rsFields)  ' �������
  if ( iSURNAME = -1 ) then
    Initialize = FieldNotFound("SURNAME")
    Exit Function
  end if
  iNAME        = GetRSFieldIndex("NAME"        , rsFields)  ' ���
  if ( iNAME = -1 ) then
    Initialize = FieldNotFound("NAME")
    Exit Function
  end if
  iPATRONYMIC  = GetRSFieldIndex("PATRONYMIC"  , rsFields)  ' ��������
  if ( iPATRONYMIC = -1 ) then
    Initialize = FieldNotFound("PATRONYMIC")
    Exit Function
  end if
  iTAX_CODE    = GetRSFieldIndex("TAX_CODE"    , rsFields)  ' ���
  if ( iTAX_CODE = -1 ) then
    Initialize = FieldNotFound("TAX_CODE")
    Exit Function
  end if
  iBIRTH_DATE  = GetRSFieldIndex("BIRTH_DATE"  , rsFields)  ' ���� �������� (YYYYMMDD)
  if ( iBIRTH_DATE = -1 ) then
    Initialize = FieldNotFound("BIRTH_DATE")
    Exit Function
  end if
  iDEATH_DATE  = GetRSFieldIndex("DEATH_DATE"  , rsFields)  ' ���� ������ (YYYYMMDD)

  WinCyrL = Array("�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", _
                  "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", _
                  "�", "�", "�", "�", "�", "�", "�")

  WinCyrU = Array("�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", _
                  "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", _
                  "�", "�", "�", "�", "�", "�", "�")

  ' http://ru.wikipedia.org/wiki/��������������_���������

                 ' �    �    �    �    �    �    �    �    �    �    �    �    �    �    �    �
                 ' �    �    �    �    �    �    �    �    �    �    �    �    �    �    �    �,
                 ' �    �    �    �    �    �    �
   RUSCIIL = Array(&hA0,&hA1,&hA2,&hA3,&hA4,&hA5,&hA6,&hA7,&hA8,&hA9,&hAA,&hAB,&hAC,&hAD,&hAE,&hAF, _
                   &hE0,&hE1,&hE2,&hE3,&hE4,&hE5,&hE6,&hE7,&hE8,&hE9,&hEA,&hEB,&hEC,&hED,&hEE,&hEF, _
                   &hF1,&hF3,&hF3,&hF5,&hF7,&hF9,&hFC)

                 ' �    �    �    �    �    �    �    �    �    �    �    �    �    �    �    �
                 ' �    �    �    �    �    �    �    �    �    �    �    �    �    �    �    �
                 ' �    �    �    �    �    �    �
   RUSCIIU = Array(&h80,&h81,&h82,&h83,&h84,&h85,&h86,&h87,&h88,&h89,&h8A,&h8B,&h8C,&h8D,&h8E,&h8F, _
                   &h90,&h91,&h92,&h93,&h94,&h95,&h96,&h97,&h98,&h99,&h9A,&h9B,&h9C,&h9D,&h9E,&h9F, _
                   &hF0,&hF2,&hF2,&hF4,&hF6,&hF8,&hFC)
   CodeTableLen = UBound(WinCyrL)
   Initialize = "Ok"
End Function

Private Function Win2RUSCII(src)
  Dim srcLen, i, j, c, sRet
  srcLen = Len(src)
  sRet = ""
  for i = 1 to srcLen
    c = Mid(src, i, 1)
    for j = 0 to CodeTableLen
      if ( c=WinCyrL(j) ) then
        c = Chr( RUSCIIL(j) )
        Exit for
      elseif ( c=WinCyrU(j) ) then
        c = Chr( RUSCIIU(j) )
        Exit for
      end if
    next
    sRet = sRet & c
  next
  Win2RUSCII = sRet
End Function

Private Function Win2RUSCII_U(src)
  Dim srcLen, i, j, c, sRet
  srcLen = Len(src)
  sRet = ""
  for i = 1 to srcLen
    c = Mid(src, i, 1)
    for j = 0 to CodeTableLen
      if ( c=WinCyrL(j) Or c=WinCyrU(j) ) then
        c = Chr( RUSCIIU(j) )
        Exit for
      end if
    next
    sRet = sRet & c
  next
  Win2RUSCII_U = sRet
End Function

Private Function MakeDBFString(src, srclen)
  if ( 0=MakeUpper ) then
    MakeDBFString = Win2RUSCII(Left(src & Space(srclen), srclen))
  else 
    MakeDBFString = Win2RUSCII_U(Left(src & Space(srclen), srclen))
  end if
End Function

'
' OnRecord - ������������ ������� ��� ����� �������.
' �������� fldValues - ������ �� ���������� ����� ������ ������� ����������� �������� ASCII 1
' ������������������ �������� ����� ������������� ������������������ ��� �����, ����������
' � ������ Initialize.
'
' ������������ �������� ������ ��������������� ��������� DBF-����� ������� ����������
' ������ GetDBFFields
'
' ���� ��� ���������� � ������� YYYYMMDD
' ���������� ���� ���������� � ���� '0' (����) ��� '1' (������)
' ������ ����, � ��� ����� � �������� ���������� � ���������� ����.
'
Public Function OnRecord(fldValues)
  Dim aValues, nValues
  Dim DPeriod, Gender, dbfRec
  aValues = Split(fldValues, Chr(1), -1, 0)
  nValues = UBound(aValues)
  if ( nValues <> rsFields ) then ' ���������� ��������� ��� ����� � ������� ������ ��������� � ����������� ������������ ��������
    OnRecord = "ʳ������ ����� � ������� ������� �� �������."
    Exit Function
  end if
  ' ���������� ������ (D_PERIOD)
  DPeriod = Mid(aValues(iDATEREG), 3, D_PERIOD_Len) ' ���� ���������� � ������� YYYYMMDD, � ��� ���� ������ YYMM
  ' ���������� ��� (���������� ��� "0" - �������, "1" - �������, ���, ������, ����� ������������� ���������� �����)
  Gender = Chr(Asc(aValues(iSEX)) + 1) ' � ����: "1" - ������� � "2" - �������
  ' ��������� ����� ��� ������� ������
  dbfRec = " "                                                         ' ���������� ��� '*' (record deleted)
  dbfRec = dbfRec & D_FORM & DPeriod & C_OKPO                          ' ���� D_FORM, D_PERIOD � C_OKPO
  dbfRec = dbfRec & MakeDBFString(aValues(iRP_REGION),   REG_Len)      ' ���� REG
  dbfRec = dbfRec & MakeDBFString(aValues(iRP_DISTRICT), DIST_Len)     ' ���� DIST
  dbfRec = dbfRec & Gender                                             ' ���� POL
  dbfRec = dbfRec & MakeDBFString(aValues(iSURNAME)    , FULLNAME_Len) ' ���� FULLNAME
  dbfRec = dbfRec & MakeDBFString(aValues(iNAME)       , NAME_Len)     ' ���� NAME
  dbfRec = dbfRec & MakeDBFString(aValues(iPATRONYMIC) , FULLOT_Len)   ' ���� FULLOT
  dbfRec = dbfRec & MakeDBFString(aValues(iTAX_CODE)   , TIN_Len)      ' ���� TIN
  dbfRec = dbfRec & MakeDBFString(aValues(iBIRTH_DATE) , D_ROG_Len)    ' ���� D_ROG
  dbfRec = dbfRec & MakeDBFString(aValues(iDEATH_DATE) , D_REEST_Len)  ' ���� D_REEST (�������� �������� ���� ��� ���� ������, ����� ������ ���� �����������?)
                                                                       ' ���� ��, �� ������ iDEATH_DATE ���� ��������� iDATEREG
  OnRecord  = dbfRec
End Function

'
' GetDBFFields - ������������ ������� ��� ����� �������.
' ���������� ���, ������������ �������� - ������, ������� ���������
' ��������� ������������ DBF-�����.
' ��� ������� ���� ����������������� ������ ��������: ���, ���, �����, ���-�� ���������� ������ (��� �������� ����)
' ��� �������� ������ ���� ��������� ��������� �/��� ��������.
' ��� ���� �� ����� ��������� 11 ��������.
' ���������� �������� ��� �����: D (���� ����), N (�������� ����), C (���������� ����)
' ����� ���� �� ����� ��������� 255 ��������.
' ����� ���� ���� ������ ���� 8.
'
Public Function GetDBFFields()
  GetDBFFields = "D_FORM  ,D, 8,0," & _
                 "D_PERIOD,N, 4,0," & _
                 "C_OKPO  ,C, 8,0," & _
                 "REG     ,C,42,0," & _
                 "DIST    ,C,55,0," & _
                 "POL     ,N, 1,0," & _
                 "FULLNAME,C,30,0," & _
                 "NAME    ,C,15,0," & _
                 "FULLOT  ,C,20,0," & _
                 "TIN     ,C,10,0," & _
                 "D_ROG   ,D, 8,0," & _
                 "D_REEST ,D, 8,0 "
End Function
