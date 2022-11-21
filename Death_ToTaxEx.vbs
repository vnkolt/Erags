'
' Внимание!!!
'
' Этот скрипт служит для сохдания выходного файла для налоговой инспекции.
'
' Данный скрипт отличается от Death_ToTax.vbs тем, что даёт дополнительную
' информацию (паспортные данные). Налоговая инспекция не может требовать
' эту информацию, однако будет весьма рада её получать.
' 
' Модификация этого скрипта может привести к ошибке во время создания или формирования
' выходного DBF-файла.
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
Const KEM_V_Len    = 30
Const SERIA_Len    = 8
Const NOM_Len      = 6
Const WID_Len      = 8

Dim rsFieldNames, rsFields
' Статические поля (инициализируются один раз)
Dim D_FORM         ' дата подання інформації
Dim C_OKPO         ' код відділу реєстрації актів цивільного стану
Dim CodeTableLen

' Индексы полей в передаваемом массиве имён полей:

Dim iSEX             ' индекс поля "SEX" в массиве rsFieldNames
Dim iDATEREG         ' индекс поля "DATEREG" в массиве rsFieldNames
Dim iRP_REGION       ' индекс поля "RP_REGION" (область проживания) в массиве rsFieldNames
Dim iRP_DISTRICT     ' индекс поля "RP_DISTRICT" (район проживания) в массиве rsFieldNames
Dim iSURNAME         ' индекс поля "SURNAME" (фамилия) в массиве rsFieldNames
Dim iNAME            ' индекс поля "NAME" (имя) в массиве rsFieldNames
Dim iPATRONYMIC      ' индекс поля "PATRONYMIC" (отчество) в массиве rsFieldNames
Dim iTAX_CODE        ' индекс поля "TAX_CODE" (ИНН) в массиве rsFieldNames
Dim iBIRTH_DATE      ' индекс поля "BIRTH_DATE" (дата рождения) в массиве rsFieldNames
Dim iDEATH_DATE      ' индекс поля "DEATH_DATE" (дата смерти) в массиве rsFieldNames
Dim iPASSPORT_BY     ' индекс поля "PASSPORT_BY" (кем выдан паспорт) в массиве rsFieldNames
Dim iPASSPORT_SERIA  ' индекс поля "PASSPORT_SERIA" (серия паспорта) в массиве rsFieldNames
Dim iPASSPORT_NUMBER ' индекс поля "PASSPORT_NUMBER" (номер паспорта) в массиве rsFieldNames
Dim iPASSPORT_DATE   ' индекс поля "PASSPORT_DATE" (дата выдачи паспорта) в массиве rsFieldNames

Dim WinCyrL       ' кодировка Win-1251 (lower-case)
Dim WinCyrU       ' кодировка Win-1251 (upper-case)

Dim RUSCIIL       ' массив соответствия альтернативной кодировки RUSCII (CP866) в Win-1251 (lower-case)
Dim RUSCIIU       ' массив соответствия альтернативной кодировки RUSCII (CP866) в Win-1251 (upper-case)

Const MakeUpper  = 1 ' поставить 0 вместо 1, если НЕ НУЖНО конвертировать в верхний регистр

' call Ini

Function GetRSFieldIndex(fldName, count)
  Dim i
  for i=0 to count
    if ( fldName=rsFieldNames(i) ) then
      GetRSFieldIndex = i
      Exit Function
    end if
  next
  GetRSFieldIndex = -1 ' элемент не найден
End Function

Private Function FieldNotFound(fldName)
  FieldNotFound = "Помилка: поле " & fldName & " не є полем вхідного набору записів."
End Function

'
' Initialize - обязательная функция для этого скрипта.
' Параметры: fldNames - строка с именами полей набора записей разделенных символом ASCII 1
'            OKPO - код ОКПО отдела
' Поля входящего набора записей соотетствуют полям в таблице DEATH файла БД ЭРАГС (см. dbTemplate.mdb)
'
Public Function Initialize(fldNames, OKPO)
  rsFieldNames = Split(fldNames, Chr(1), -1, 0)
  rsFields     = UBound(rsFieldNames)
  D_FORM       = CStr(Year(Now)) & Right("0" & CStr(Month(Now)),2) & Right("0" & CStr(Day(Now)),2)
  C_OKPO       = OKPO
  if ( Len(C_OKPO) <> C_OKPO_Len ) then
    Initialize = "Помилка: поле C_OKPO повинно бути довжиною " & CStr(C_OKPO_Len) & " байт."
    Exit Function
  end if
  iSEX         = GetRSFieldIndex("SEX"         , rsFields)
  if ( iSEX = -1 ) then
    Initialize = FieldNotFound("SEX")
    Exit Function
  end if
  iDATEREG     = GetRSFieldIndex("DATEREG"     , rsFields)
  if ( iDATEREG = -1 ) then
    Initialize = FieldNotFound("DATEREG")
    Exit Function
  end if
  iRP_REGION   = GetRSFieldIndex("RP_REGION"   , rsFields)
  if ( iRP_REGION = -1 ) then
    Initialize = FieldNotFound("RP_REGION")
    Exit Function
  end if
  iRP_DISTRICT = GetRSFieldIndex("RP_DISTRICT" , rsFields)
  if ( iRP_DISTRICT = -1 ) then
    Initialize = FieldNotFound("RP_DISTRICT")
    Exit Function
  end if
  iSURNAME     = GetRSFieldIndex("SURNAME"     , rsFields)
  if ( iSURNAME = -1 ) then
    Initialize = FieldNotFound("SURNAME")
    Exit Function
  end if
  iNAME        = GetRSFieldIndex("NAME"        , rsFields)
  if ( iNAME = -1 ) then
    Initialize = FieldNotFound("NAME")
    Exit Function
  end if
  iPATRONYMIC  = GetRSFieldIndex("PATRONYMIC"  , rsFields)
  if ( iPATRONYMIC = -1 ) then
    Initialize = FieldNotFound("PATRONYMIC")
    Exit Function
  end if
  iTAX_CODE    = GetRSFieldIndex("TAX_CODE"    , rsFields)
  if ( iTAX_CODE = -1 ) then
    Initialize = FieldNotFound("TAX_CODE")
    Exit Function
  end if
  iBIRTH_DATE  = GetRSFieldIndex("BIRTH_DATE"  , rsFields)
  if ( iBIRTH_DATE = -1 ) then
    Initialize = FieldNotFound("BIRTH_DATE")
    Exit Function
  end if
  iDEATH_DATE  = GetRSFieldIndex("DEATH_DATE"  , rsFields)
  if ( iDEATH_DATE = -1 ) then
    Initialize = FieldNotFound("DEATH_DATE")
    Exit Function
  end if

  iPASSPORT_BY  = GetRSFieldIndex("PASSPORT_BY"  , rsFields)
  if ( iPASSPORT_BY = -1 ) then
    Initialize = FieldNotFound("PASSPORT_BY")
    Exit Function
  end if

  iPASSPORT_SERIA  = GetRSFieldIndex("PASSPORT_SERIA"  , rsFields)
  if ( iPASSPORT_SERIA = -1 ) then
    Initialize = FieldNotFound("PASSPORT_SERIA")
    Exit Function
  end if

  iPASSPORT_NUMBER  = GetRSFieldIndex("PASSPORT_NUMBER"  , rsFields)
  if ( iPASSPORT_NUMBER = -1 ) then
    Initialize = FieldNotFound("PASSPORT_NUMBER")
    Exit Function
  end if

  iPASSPORT_DATE  = GetRSFieldIndex("PASSPORT_DATE"  , rsFields)
  if ( iPASSPORT_DATE = -1 ) then
    Initialize = FieldNotFound("PASSPORT_DATE")
    Exit Function
  end if

  WinCyrL = Array("а", "б", "в", "г", "д", "е", "ж", "з", "и", "й", "к", "л", "м", "н", "о", "п", _
                  "р", "с", "т", "у", "ф", "х", "ц", "ч", "ш", "щ", "ъ", "ы", "ь", "э", "ю", "я", _
                  "ё", "ѓ", "ґ", "є", "і", "ї", "№")

  WinCyrU = Array("А", "Б", "В", "Г", "Д", "Е", "Ж", "З", "И", "Й", "К", "Л", "М", "Н", "О", "П", _
                  "Р", "С", "Т", "У", "Ф", "Х", "Ц", "Ч", "Ш", "Щ", "Ъ", "Ы", "Ь", "Э", "Ю", "Я", _
                  "Ё", "Ѓ", "Ґ", "Є", "І", "Ї", "№")

  ' http://ru.wikipedia.org/wiki/Альтернативная_кодировка

                 ' а    б    в    г    д    е    ж    з    и    й    к    л    м    н    о    п
                 ' р    с    т    у    ф    х    ц    Ч    ш    щ    ъ    ы    ь    э    ю    я,
                 ' ё    ѓ    ґ    є    і    ї    №
   RUSCIIL = Array(&hA0,&hA1,&hA2,&hA3,&hA4,&hA5,&hA6,&hA7,&hA8,&hA9,&hAA,&hAB,&hAC,&hAD,&hAE,&hAF, _
                   &hE0,&hE1,&hE2,&hE3,&hE4,&hE5,&hE6,&hE7,&hE8,&hE9,&hEA,&hEB,&hEC,&hED,&hEE,&hEF, _
                   &hF1,&hF3,&hF3,&hF5,&hF7,&hF9,&hFC)

                 ' А    Б    В    Г    Д    Е    Ж    З    И    Й    К    Л    М    Н    О    П
                 ' Р    С    Т    У    Ф    Х    Ц    Ч    Ш    Щ    Ъ    Ы    Ь    Э    Ю    Я
                 ' Ё    Ѓ    Ґ    Є    І    Ї    №
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
' OnRecord - обязательная функция для этого скрипта.
' Параметр fldValues - строка со значениями полей набора записей разделенных символом ASCII 1
' Последовательность значений полей соответствует последовательности имён полей, переданных
' в фукцию Initialize.
'
' Возвращаемое значение должно соответствовать структуре DBF-файла которую возвращает
' фунция GetDBFFields
'
' Поля дат передаются в формате YYYYMMDD
' Логические поля передаются в виде '0' (ложь) или '1' (истина)
' Прочие поля, в том числе и числовые передаются в символьном виде.
'
Public Function OnRecord(fldValues)
  Dim aValues, nValues
  Dim DPeriod, Gender, dbfRec
  aValues = Split(fldValues, Chr(1), -1, 0)
  nValues = UBound(aValues)
  if ( nValues <> rsFields ) then ' количество переданых имён полей в запросе должно совпадать с количеством передаваемых значений
    OnRecord = "Кількість полей і кількість значень не співпадає."
    Exit Function
  end if
  ' определяем период (D_PERIOD)
  DPeriod = Mid(aValues(iDATEREG), 3, D_PERIOD_Len) ' дата передается в формате YYYYMMDD, а нам надо только YYMM
  ' определяем пол (передается как "0" - женский, "1" - мужской, что, кстати, более соответствует физиологии полов)
  Gender = Chr(Asc(aValues(iSEX)) + 1) ' а надо: "1" - женский и "2" - мужской
  ' формируем буфер для текущей записи
  dbfRec = " "                                                         ' пробельчик для '*' (record deleted)
  dbfRec = dbfRec & D_FORM & DPeriod & C_OKPO                          ' поля D_FORM, D_PERIOD и C_OKPO
  dbfRec = dbfRec & MakeDBFString(aValues(iRP_REGION),   REG_Len)      ' поле REG
  dbfRec = dbfRec & MakeDBFString(aValues(iRP_DISTRICT), DIST_Len)     ' поле DIST
  dbfRec = dbfRec & Gender                                             ' поле POL
  dbfRec = dbfRec & MakeDBFString(aValues(iSURNAME)    , FULLNAME_Len) ' поле FULLNAME
  dbfRec = dbfRec & MakeDBFString(aValues(iNAME)       , NAME_Len)     ' поле NAME
  dbfRec = dbfRec & MakeDBFString(aValues(iPATRONYMIC) , FULLOT_Len)   ' поле FULLOT
  dbfRec = dbfRec & MakeDBFString(aValues(iTAX_CODE)   , TIN_Len)      ' поле TIN
  dbfRec = dbfRec & MakeDBFString(aValues(iBIRTH_DATE) , D_ROG_Len)    ' поле D_ROG
  dbfRec = dbfRec & MakeDBFString(aValues(iDEATH_DATE) , D_REEST_Len)  ' поле D_REEST (странное название поля для даты смерти, может хотели дату регистрации?)
                                                                       ' если да, то вместо iDEATH_DATE надо поставить iDATEREG
  dbfRec = dbfRec & MakeDBFString(aValues(iPASSPORT_BY)   , KEM_V_Len) ' поле KEM_V
  dbfRec = dbfRec & MakeDBFString(aValues(iPASSPORT_SERIA), SERIA_Len) ' поле SERIA
  dbfRec = dbfRec & MakeDBFString(aValues(iPASSPORT_NUMBER),NOM_Len)   ' поле NOM
  dbfRec = dbfRec & MakeDBFString(aValues(iPASSPORT_DATE),  WID_Len)   ' поле WID
  OnRecord  = dbfRec
End Function

'
' GetDBFFields - обязательная функция для этого скрипта.
' Пареметров нет, возвращаемое значение - строка, которая описывает
' структуру создаваемого DBF-файла.
' Для каждого поля предусматриваются четыре свойства: имя, тип, длина, кол-во десятичных знаков (для числовых поле)
' Все свойства должны быть разделены пробелами и/или запятыми.
' Имя поля не может превышать 11 символов.
' Допустимые значения для типов: D (поле даты), N (числовое поле), C (символьное поле)
' Длина поля не может превышать 255 символов.
' Длина поля даты должна быть 8.
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
                 "D_REEST ,D, 8,0 " & _
                 "KEM_V   ,C,30,0 " & _
                 "SERIA   ,C, 8,0 " & _
                 "NOM     ,N, 6,0 " & _
                 "WID     ,D, 8,0 "
End Function