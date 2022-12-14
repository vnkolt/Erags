// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// _Application wrapper class

namespace Word {

class _Application : public COleDispatchDriver
{
public:
	_Application() {}		// Calls COleDispatchDriver default constructor
	_Application(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_Application(const _Application& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	CString GetName();
	LPDISPATCH GetDocuments();
	LPDISPATCH GetWindows();
	LPDISPATCH GetActiveDocument();
	LPDISPATCH GetActiveWindow();
	LPDISPATCH GetSelection();
	LPDISPATCH GetWordBasic();
	LPDISPATCH GetRecentFiles();
	LPDISPATCH GetNormalTemplate();
	LPDISPATCH GetSystem();
	LPDISPATCH GetAutoCorrect();
	LPDISPATCH GetFontNames();
	LPDISPATCH GetLandscapeFontNames();
	LPDISPATCH GetPortraitFontNames();
	LPDISPATCH GetLanguages();
	LPDISPATCH GetAssistant();
	LPDISPATCH GetBrowser();
	LPDISPATCH GetFileConverters();
	LPDISPATCH GetMailingLabel();
	LPDISPATCH GetDialogs();
	LPDISPATCH GetCaptionLabels();
	LPDISPATCH GetAutoCaptions();
	LPDISPATCH GetAddIns();
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	CString GetVersion();
	BOOL GetScreenUpdating();
	void SetScreenUpdating(BOOL bNewValue);
	BOOL GetPrintPreview();
	void SetPrintPreview(BOOL bNewValue);
	LPDISPATCH GetTasks();
	BOOL GetDisplayStatusBar();
	void SetDisplayStatusBar(BOOL bNewValue);
	BOOL GetSpecialMode();
	long GetUsableWidth();
	long GetUsableHeight();
	BOOL GetMathCoprocessorAvailable();
	BOOL GetMouseAvailable();
	VARIANT GetInternational(long Index);
	CString GetBuild();
	BOOL GetCapsLock();
	BOOL GetNumLock();
	CString GetUserName_();
	void SetUserName(LPCTSTR lpszNewValue);
	CString GetUserInitials();
	void SetUserInitials(LPCTSTR lpszNewValue);
	CString GetUserAddress();
	void SetUserAddress(LPCTSTR lpszNewValue);
	LPDISPATCH GetMacroContainer();
	BOOL GetDisplayRecentFiles();
	void SetDisplayRecentFiles(BOOL bNewValue);
	LPDISPATCH GetCommandBars();
	LPDISPATCH GetSynonymInfo(LPCTSTR Word, VARIANT* LanguageID);
	LPDISPATCH GetVbe();
	CString GetDefaultSaveFormat();
	void SetDefaultSaveFormat(LPCTSTR lpszNewValue);
	LPDISPATCH GetListGalleries();
	CString GetActivePrinter();
	void SetActivePrinter(LPCTSTR lpszNewValue);
	LPDISPATCH GetTemplates();
	LPDISPATCH GetCustomizationContext();
	void SetCustomizationContext(LPDISPATCH newValue);
	LPDISPATCH GetKeyBindings();
	LPDISPATCH GetKeysBoundTo(long KeyCategory, LPCTSTR Command, VARIANT* CommandParameter);
	LPDISPATCH GetFindKey(long KeyCode, VARIANT* KeyCode2);
	CString GetCaption();
	void SetCaption(LPCTSTR lpszNewValue);
	CString GetPath();
	BOOL GetDisplayScrollBars();
	void SetDisplayScrollBars(BOOL bNewValue);
	CString GetStartupPath();
	void SetStartupPath(LPCTSTR lpszNewValue);
	long GetBackgroundSavingStatus();
	long GetBackgroundPrintingStatus();
	long GetLeft();
	void SetLeft(long nNewValue);
	long GetTop();
	void SetTop(long nNewValue);
	long GetWidth();
	void SetWidth(long nNewValue);
	long GetHeight();
	void SetHeight(long nNewValue);
	long GetWindowState();
	void SetWindowState(long nNewValue);
	BOOL GetDisplayAutoCompleteTips();
	void SetDisplayAutoCompleteTips(BOOL bNewValue);
	LPDISPATCH GetOptions();
	long GetDisplayAlerts();
	void SetDisplayAlerts(long nNewValue);
	LPDISPATCH GetCustomDictionaries();
	CString GetPathSeparator();
	void SetStatusBar(LPCTSTR lpszNewValue);
	BOOL GetMAPIAvailable();
	BOOL GetDisplayScreenTips();
	void SetDisplayScreenTips(BOOL bNewValue);
	long GetEnableCancelKey();
	void SetEnableCancelKey(long nNewValue);
	BOOL GetUserControl();
	LPDISPATCH GetFileSearch();
	long GetMailSystem();
	CString GetDefaultTableSeparator();
	void SetDefaultTableSeparator(LPCTSTR lpszNewValue);
	BOOL GetShowVisualBasicEditor();
	void SetShowVisualBasicEditor(BOOL bNewValue);
	CString GetBrowseExtraFileTypes();
	void SetBrowseExtraFileTypes(LPCTSTR lpszNewValue);
	BOOL GetIsObjectValid(LPDISPATCH Object);
	LPDISPATCH GetMailMessage();
	BOOL GetFocusInMailHeader();
	void Quit(VARIANT* SaveChanges, VARIANT* OriginalFormat, VARIANT* RouteDocument);
	void ScreenRefresh();
	void PrintOut(VARIANT* Background, VARIANT* Append, VARIANT* Range, VARIANT* OutputFileName, VARIANT* From, VARIANT* To, VARIANT* Item, VARIANT* Copies, VARIANT* Pages, VARIANT* PageType, VARIANT* PrintToFile, VARIANT* Collate, 
		VARIANT* FileName, VARIANT* ActivePrinterMacGX, VARIANT* ManualDuplexPrint);
	void LookupNameProperties(LPCTSTR Name);
	void SubstituteFont(LPCTSTR UnavailableFont, LPCTSTR SubstituteFont);
	BOOL Repeat(VARIANT* Times);
	void DDEExecute(long Channel, LPCTSTR Command);
	long DDEInitiate(LPCTSTR App, LPCTSTR Topic);
	void DDEPoke(long Channel, LPCTSTR Item, LPCTSTR Data);
	CString DDERequest(long Channel, LPCTSTR Item);
	void DDETerminate(long Channel);
	void DDETerminateAll();
	long BuildKeyCode(long Arg1, VARIANT* Arg2, VARIANT* Arg3, VARIANT* Arg4);
	CString KeyString(long KeyCode, VARIANT* KeyCode2);
	void OrganizerCopy(LPCTSTR Source, LPCTSTR Destination, LPCTSTR Name, long Object);
	void OrganizerDelete(LPCTSTR Source, LPCTSTR Name, long Object);
	void OrganizerRename(LPCTSTR Source, LPCTSTR Name, LPCTSTR NewName, long Object);
	// method 'AddAddress' not emitted because of invalid return type or parameter type
	CString GetAddress(VARIANT* Name, VARIANT* AddressProperties, VARIANT* UseAutoText, VARIANT* DisplaySelectDialog, VARIANT* SelectDialog, VARIANT* CheckNamesDialog, VARIANT* RecentAddressesChoice, VARIANT* UpdateRecentAddresses);
	BOOL CheckGrammar(LPCTSTR String);
	BOOL CheckSpelling(LPCTSTR Word, VARIANT* CustomDictionary, VARIANT* IgnoreUppercase, VARIANT* MainDictionary, VARIANT* CustomDictionary2, VARIANT* CustomDictionary3, VARIANT* CustomDictionary4, VARIANT* CustomDictionary5, 
		VARIANT* CustomDictionary6, VARIANT* CustomDictionary7, VARIANT* CustomDictionary8, VARIANT* CustomDictionary9, VARIANT* CustomDictionary10);
	void ResetIgnoreAll();
	LPDISPATCH GetSpellingSuggestions(LPCTSTR Word, VARIANT* CustomDictionary, VARIANT* IgnoreUppercase, VARIANT* MainDictionary, VARIANT* SuggestionMode, VARIANT* CustomDictionary2, VARIANT* CustomDictionary3, VARIANT* CustomDictionary4, 
		VARIANT* CustomDictionary5, VARIANT* CustomDictionary6, VARIANT* CustomDictionary7, VARIANT* CustomDictionary8, VARIANT* CustomDictionary9, VARIANT* CustomDictionary10);
	void GoBack();
	void Help(VARIANT* HelpType);
	void AutomaticChange();
	void ShowMe();
	void HelpTool();
	LPDISPATCH NewWindow();
	void ListCommands(BOOL ListAllCommands);
	void ShowClipboard();
	void OnTime(VARIANT* When, LPCTSTR Name, VARIANT* Tolerance);
	void NextLetter();
	short MountVolume(LPCTSTR Zone, LPCTSTR Server, LPCTSTR Volume, VARIANT* User, VARIANT* UserPassword, VARIANT* VolumePassword);
	CString CleanString(LPCTSTR String);
	void SendFax();
	void ChangeFileOpenDirectory(LPCTSTR Path);
	void Run(LPCTSTR MacroName);
	void GoForward();
	void Move(long Left, long Top);
	void Resize(long Width, long Height);
	float InchesToPoints(float Inches);
	float CentimetersToPoints(float Centimeters);
	float MillimetersToPoints(float Millimeters);
	float PicasToPoints(float Picas);
	float LinesToPoints(float Lines);
	float PointsToInches(float Points);
	float PointsToCentimeters(float Points);
	float PointsToMillimeters(float Points);
	float PointsToPicas(float Points);
	float PointsToLines(float Points);
	void Activate();
};
/////////////////////////////////////////////////////////////////////////////
// _Global wrapper class

class _Global : public COleDispatchDriver
{
public:
	_Global() {}		// Calls COleDispatchDriver default constructor
	_Global(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_Global(const _Global& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	CString GetName();
	LPDISPATCH GetDocuments();
	LPDISPATCH GetWindows();
	LPDISPATCH GetActiveDocument();
	LPDISPATCH GetActiveWindow();
	LPDISPATCH GetSelection();
	LPDISPATCH GetWordBasic();
	BOOL GetPrintPreview();
	void SetPrintPreview(BOOL bNewValue);
	LPDISPATCH GetRecentFiles();
	LPDISPATCH GetNormalTemplate();
	LPDISPATCH GetSystem();
	LPDISPATCH GetAutoCorrect();
	LPDISPATCH GetFontNames();
	LPDISPATCH GetLandscapeFontNames();
	LPDISPATCH GetPortraitFontNames();
	LPDISPATCH GetLanguages();
	LPDISPATCH GetAssistant();
	LPDISPATCH GetFileConverters();
	LPDISPATCH GetDialogs();
	LPDISPATCH GetCaptionLabels();
	LPDISPATCH GetAutoCaptions();
	LPDISPATCH GetAddIns();
	LPDISPATCH GetTasks();
	LPDISPATCH GetMacroContainer();
	LPDISPATCH GetCommandBars();
	LPDISPATCH GetSynonymInfo(LPCTSTR Word, VARIANT* LanguageID);
	LPDISPATCH GetVbe();
	LPDISPATCH GetListGalleries();
	CString GetActivePrinter();
	void SetActivePrinter(LPCTSTR lpszNewValue);
	LPDISPATCH GetTemplates();
	LPDISPATCH GetCustomizationContext();
	void SetCustomizationContext(LPDISPATCH newValue);
	LPDISPATCH GetKeyBindings();
	LPDISPATCH GetKeysBoundTo(long KeyCategory, LPCTSTR Command, VARIANT* CommandParameter);
	LPDISPATCH GetFindKey(long KeyCode, VARIANT* KeyCode2);
	LPDISPATCH GetOptions();
	LPDISPATCH GetCustomDictionaries();
	void SetStatusBar(LPCTSTR lpszNewValue);
	BOOL GetShowVisualBasicEditor();
	void SetShowVisualBasicEditor(BOOL bNewValue);
	BOOL GetIsObjectValid(LPDISPATCH Object);
	BOOL Repeat(VARIANT* Times);
	void DDEExecute(long Channel, LPCTSTR Command);
	long DDEInitiate(LPCTSTR App, LPCTSTR Topic);
	void DDEPoke(long Channel, LPCTSTR Item, LPCTSTR Data);
	CString DDERequest(long Channel, LPCTSTR Item);
	void DDETerminate(long Channel);
	void DDETerminateAll();
	long BuildKeyCode(long Arg1, VARIANT* Arg2, VARIANT* Arg3, VARIANT* Arg4);
	CString KeyString(long KeyCode, VARIANT* KeyCode2);
	BOOL CheckSpelling(LPCTSTR Word, VARIANT* CustomDictionary, VARIANT* IgnoreUppercase, VARIANT* MainDictionary, VARIANT* CustomDictionary2, VARIANT* CustomDictionary3, VARIANT* CustomDictionary4, VARIANT* CustomDictionary5, 
		VARIANT* CustomDictionary6, VARIANT* CustomDictionary7, VARIANT* CustomDictionary8, VARIANT* CustomDictionary9, VARIANT* CustomDictionary10);
	LPDISPATCH GetSpellingSuggestions(LPCTSTR Word, VARIANT* CustomDictionary, VARIANT* IgnoreUppercase, VARIANT* MainDictionary, VARIANT* SuggestionMode, VARIANT* CustomDictionary2, VARIANT* CustomDictionary3, VARIANT* CustomDictionary4, 
		VARIANT* CustomDictionary5, VARIANT* CustomDictionary6, VARIANT* CustomDictionary7, VARIANT* CustomDictionary8, VARIANT* CustomDictionary9, VARIANT* CustomDictionary10);
	void Help(VARIANT* HelpType);
	LPDISPATCH NewWindow();
	CString CleanString(LPCTSTR String);
	void ChangeFileOpenDirectory(LPCTSTR Path);
	float InchesToPoints(float Inches);
	float CentimetersToPoints(float Centimeters);
	float MillimetersToPoints(float Millimeters);
	float PicasToPoints(float Picas);
	float LinesToPoints(float Lines);
	float PointsToInches(float Points);
	float PointsToCentimeters(float Points);
	float PointsToMillimeters(float Points);
	float PointsToPicas(float Points);
	float PointsToLines(float Points);
};
/////////////////////////////////////////////////////////////////////////////
// FontNames wrapper class

class FontNames : public COleDispatchDriver
{
public:
	FontNames() {}		// Calls COleDispatchDriver default constructor
	FontNames(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	FontNames(const FontNames& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	CString Item(long Index);
};
/////////////////////////////////////////////////////////////////////////////
// Languages wrapper class

class Languages : public COleDispatchDriver
{
public:
	Languages() {}		// Calls COleDispatchDriver default constructor
	Languages(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Languages(const Languages& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH Item(VARIANT* Index);
};
/////////////////////////////////////////////////////////////////////////////
// Language wrapper class

class Language : public COleDispatchDriver
{
public:
	Language() {}		// Calls COleDispatchDriver default constructor
	Language(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Language(const Language& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetId();
	CString GetNameLocal();
	CString GetName();
	LPDISPATCH GetActiveGrammarDictionary();
	LPDISPATCH GetActiveHyphenationDictionary();
	LPDISPATCH GetActiveSpellingDictionary();
	LPDISPATCH GetActiveThesaurusDictionary();
	CString GetDefaultWritingStyle();
	void SetDefaultWritingStyle(LPCTSTR lpszNewValue);
	VARIANT GetWritingStyleList();
	long GetSpellingDictionaryType();
	void SetSpellingDictionaryType(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// Documents wrapper class

class Documents : public COleDispatchDriver
{
public:
	Documents() {}		// Calls COleDispatchDriver default constructor
	Documents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Documents(const Documents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH Item(VARIANT* Index);
	void Close(VARIANT* SaveChanges, VARIANT* OriginalFormat, VARIANT* RouteDocument);
	LPDISPATCH Add(VARIANT* Template, VARIANT* NewTemplate);
	LPDISPATCH Open(VARIANT* FileName, VARIANT* ConfirmConversions, VARIANT* ReadOnly, VARIANT* AddToRecentFiles, VARIANT* PasswordDocument, VARIANT* PasswordTemplate, VARIANT* Revert, VARIANT* WritePasswordDocument, 
		VARIANT* WritePasswordTemplate, VARIANT* Format);
	void Save(VARIANT* NoPrompt, VARIANT* OriginalFormat);
};
/////////////////////////////////////////////////////////////////////////////
// _Document wrapper class

class _Document : public COleDispatchDriver
{
public:
	_Document() {}		// Calls COleDispatchDriver default constructor
	_Document(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_Document(const _Document& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetName();
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH GetBuiltInDocumentProperties();
	LPDISPATCH GetCustomDocumentProperties();
	CString GetPath();
	LPDISPATCH GetBookmarks();
	LPDISPATCH GetTables();
	LPDISPATCH GetFootnotes();
	LPDISPATCH GetEndnotes();
	LPDISPATCH GetComments();
	long GetType();
	BOOL GetAutoHyphenation();
	void SetAutoHyphenation(BOOL bNewValue);
	BOOL GetHyphenateCaps();
	void SetHyphenateCaps(BOOL bNewValue);
	long GetHyphenationZone();
	void SetHyphenationZone(long nNewValue);
	long GetConsecutiveHyphensLimit();
	void SetConsecutiveHyphensLimit(long nNewValue);
	LPDISPATCH GetSections();
	LPDISPATCH GetParagraphs();
	LPDISPATCH GetWords();
	LPDISPATCH GetSentences();
	LPDISPATCH GetCharacters();
	LPDISPATCH GetFields();
	LPDISPATCH GetFormFields();
	LPDISPATCH GetStyles();
	LPDISPATCH GetFrames();
	LPDISPATCH GetTablesOfFigures();
	LPDISPATCH GetVariables();
	LPDISPATCH GetMailMerge();
	LPDISPATCH GetEnvelope();
	CString GetFullName();
	LPDISPATCH GetRevisions();
	LPDISPATCH GetTablesOfContents();
	LPDISPATCH GetTablesOfAuthorities();
	LPDISPATCH GetPageSetup();
	void SetPageSetup(LPDISPATCH newValue);
	LPDISPATCH GetWindows();
	BOOL GetHasRoutingSlip();
	void SetHasRoutingSlip(BOOL bNewValue);
	LPDISPATCH GetRoutingSlip();
	BOOL GetRouted();
	LPDISPATCH GetTablesOfAuthoritiesCategories();
	LPDISPATCH GetIndexes();
	BOOL GetSaved();
	void SetSaved(BOOL bNewValue);
	LPDISPATCH GetContent();
	LPDISPATCH GetActiveWindow();
	long GetKind();
	void SetKind(long nNewValue);
	BOOL GetReadOnly();
	LPDISPATCH GetSubdocuments();
	BOOL GetIsMasterDocument();
	float GetDefaultTabStop();
	void SetDefaultTabStop(float newValue);
	BOOL GetEmbedTrueTypeFonts();
	void SetEmbedTrueTypeFonts(BOOL bNewValue);
	BOOL GetSaveFormsData();
	void SetSaveFormsData(BOOL bNewValue);
	BOOL GetReadOnlyRecommended();
	void SetReadOnlyRecommended(BOOL bNewValue);
	BOOL GetSaveSubsetFonts();
	void SetSaveSubsetFonts(BOOL bNewValue);
	BOOL GetCompatibility(long Type);
	void SetCompatibility(long Type, BOOL bNewValue);
	LPDISPATCH GetStoryRanges();
	LPDISPATCH GetCommandBars();
	BOOL GetIsSubdocument();
	long GetSaveFormat();
	long GetProtectionType();
	LPDISPATCH GetHyperlinks();
	LPDISPATCH GetShapes();
	LPDISPATCH GetListTemplates();
	LPDISPATCH GetLists();
	BOOL GetUpdateStylesOnOpen();
	void SetUpdateStylesOnOpen(BOOL bNewValue);
	VARIANT GetAttachedTemplate();
	void SetAttachedTemplate(VARIANT* newValue);
	LPDISPATCH GetInlineShapes();
	LPDISPATCH GetBackground();
	void SetBackground(LPDISPATCH newValue);
	BOOL GetGrammarChecked();
	void SetGrammarChecked(BOOL bNewValue);
	BOOL GetSpellingChecked();
	void SetSpellingChecked(BOOL bNewValue);
	BOOL GetShowGrammaticalErrors();
	void SetShowGrammaticalErrors(BOOL bNewValue);
	BOOL GetShowSpellingErrors();
	void SetShowSpellingErrors(BOOL bNewValue);
	LPDISPATCH GetVersions();
	BOOL GetShowSummary();
	void SetShowSummary(BOOL bNewValue);
	long GetSummaryViewMode();
	void SetSummaryViewMode(long nNewValue);
	long GetSummaryLength();
	void SetSummaryLength(long nNewValue);
	BOOL GetPrintFractionalWidths();
	void SetPrintFractionalWidths(BOOL bNewValue);
	BOOL GetPrintPostScriptOverText();
	void SetPrintPostScriptOverText(BOOL bNewValue);
	LPDISPATCH GetContainer();
	BOOL GetPrintFormsData();
	void SetPrintFormsData(BOOL bNewValue);
	LPDISPATCH GetListParagraphs();
	void SetPassword(LPCTSTR lpszNewValue);
	void SetWritePassword(LPCTSTR lpszNewValue);
	BOOL GetHasPassword();
	BOOL GetWriteReserved();
	CString GetActiveWritingStyle(VARIANT* LanguageID);
	void SetActiveWritingStyle(VARIANT* LanguageID, LPCTSTR lpszNewValue);
	BOOL GetUserControl();
	void SetUserControl(BOOL bNewValue);
	BOOL GetHasMailer();
	void SetHasMailer(BOOL bNewValue);
	LPDISPATCH GetMailer();
	LPDISPATCH GetReadabilityStatistics();
	LPDISPATCH GetGrammaticalErrors();
	LPDISPATCH GetSpellingErrors();
	LPDISPATCH GetVBProject();
	BOOL GetFormsDesign();
	CString Get_CodeName();
	void Set_CodeName(LPCTSTR lpszNewValue);
	CString GetCodeName();
	BOOL GetTrackRevisions();
	void SetTrackRevisions(BOOL bNewValue);
	BOOL GetPrintRevisions();
	void SetPrintRevisions(BOOL bNewValue);
	BOOL GetShowRevisions();
	void SetShowRevisions(BOOL bNewValue);
	void Close(VARIANT* SaveChanges, VARIANT* OriginalFormat, VARIANT* RouteDocument);
	void SaveAs(VARIANT* FileName, VARIANT* FileFormat, VARIANT* LockComments, VARIANT* Password, VARIANT* AddToRecentFiles, VARIANT* WritePassword, VARIANT* ReadOnlyRecommended, VARIANT* EmbedTrueTypeFonts, VARIANT* SaveNativePictureFormat, 
		VARIANT* SaveFormsData, VARIANT* SaveAsAOCELetter);
	void Repaginate();
	void FitToPages();
	void ManualHyphenation();
	void Select();
	void DataForm();
	void Route();
	void Save();
	void PrintOut(VARIANT* Background, VARIANT* Append, VARIANT* Range, VARIANT* OutputFileName, VARIANT* From, VARIANT* To, VARIANT* Item, VARIANT* Copies, VARIANT* Pages, VARIANT* PageType, VARIANT* PrintToFile, VARIANT* Collate, 
		VARIANT* ActivePrinterMacGX, VARIANT* ManualDuplexPrint);
	void SendMail();
	LPDISPATCH Range(VARIANT* Start, VARIANT* End);
	void RunAutoMacro(long Which);
	void Activate();
	void PrintPreview();
	LPDISPATCH GoTo(VARIANT* What, VARIANT* Which, VARIANT* Count, VARIANT* Name);
	BOOL Undo(VARIANT* Times);
	BOOL Redo(VARIANT* Times);
	long ComputeStatistics(long Statistic, VARIANT* IncludeFootnotesAndEndnotes);
	void MakeCompatibilityDefault();
	void Protect(long Type, VARIANT* NoReset, VARIANT* Password);
	void Unprotect(VARIANT* Password);
	void EditionOptions(long Type, long Option, LPCTSTR Name, VARIANT* Format);
	void RunLetterWizard(VARIANT* LetterContent, VARIANT* WizardMode);
	LPDISPATCH GetLetterContent();
	void SetLetterContent(VARIANT* LetterContent);
	void CopyStylesFromTemplate(LPCTSTR Template);
	void UpdateStyles();
	void CheckGrammar();
	void CheckSpelling(VARIANT* CustomDictionary, VARIANT* IgnoreUppercase, VARIANT* AlwaysSuggest, VARIANT* CustomDictionary2, VARIANT* CustomDictionary3, VARIANT* CustomDictionary4, VARIANT* CustomDictionary5, VARIANT* CustomDictionary6, 
		VARIANT* CustomDictionary7, VARIANT* CustomDictionary8, VARIANT* CustomDictionary9, VARIANT* CustomDictionary10);
	void FollowHyperlink(VARIANT* Address, VARIANT* SubAddress, VARIANT* NewWindow, VARIANT* AddHistory, VARIANT* ExtraInfo, VARIANT* Method, VARIANT* HeaderInfo);
	void AddToFavorites();
	void Reload();
	LPDISPATCH AutoSummarize(VARIANT* Length, VARIANT* Mode, VARIANT* UpdateProperties);
	void RemoveNumbers(VARIANT* NumberType);
	void ConvertNumbersToText(VARIANT* NumberType);
	long CountNumberedItems(VARIANT* NumberType, VARIANT* Level);
	void Post();
	void ToggleFormsDesign();
	void Compare(LPCTSTR Name);
	void UpdateSummaryProperties();
	VARIANT GetCrossReferenceItems(VARIANT* ReferenceType);
	void AutoFormat();
	void ViewCode();
	void ViewPropertyBrowser();
	void ForwardMailer();
	void Reply();
	void ReplyAll();
	void SendMailer(VARIANT* FileFormat, VARIANT* Priority);
	void UndoClear();
	void PresentIt();
	void SendFax(LPCTSTR Address, VARIANT* Subject);
	void Merge(LPCTSTR FileName);
	void ClosePrintPreview();
	LPDISPATCH CreateLetterContent(LPCTSTR DateFormat, BOOL IncludeHeaderFooter, LPCTSTR PageDesign, long LetterStyle, BOOL Letterhead, long LetterheadLocation, float LetterheadSize, LPCTSTR RecipientName, LPCTSTR RecipientAddress, 
		LPCTSTR Salutation, long SalutationType, LPCTSTR RecipientReference, LPCTSTR MailingInstructions, LPCTSTR AttentionLine, LPCTSTR Subject, LPCTSTR CCList, LPCTSTR ReturnAddress, LPCTSTR SenderName, LPCTSTR Closing, LPCTSTR SenderCompany, 
		LPCTSTR SenderJobTitle, LPCTSTR SenderInitials, long EnclosureNumber, VARIANT* InfoBlock, VARIANT* RecipientCode, VARIANT* RecipientGender, VARIANT* ReturnAddressShortForm, VARIANT* SenderCity, VARIANT* SenderCode, VARIANT* SenderGender, 
		VARIANT* SenderReference);
	void AcceptAllRevisions();
	void RejectAllRevisions();
};
/////////////////////////////////////////////////////////////////////////////
// Template wrapper class

class Template : public COleDispatchDriver
{
public:
	Template() {}		// Calls COleDispatchDriver default constructor
	Template(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Template(const Template& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetName();
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	CString GetPath();
	LPDISPATCH GetAutoTextEntries();
	long GetLanguageID();
	void SetLanguageID(long nNewValue);
	BOOL GetSaved();
	void SetSaved(BOOL bNewValue);
	long GetType();
	CString GetFullName();
	LPDISPATCH GetBuiltInDocumentProperties();
	LPDISPATCH GetCustomDocumentProperties();
	LPDISPATCH GetListTemplates();
	long GetLanguageIDFarEast();
	void SetLanguageIDFarEast(long nNewValue);
	LPDISPATCH GetVBProject();
	LPDISPATCH OpenAsDocument();
	void Save();
};
/////////////////////////////////////////////////////////////////////////////
// Templates wrapper class

class Templates : public COleDispatchDriver
{
public:
	Templates() {}		// Calls COleDispatchDriver default constructor
	Templates(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Templates(const Templates& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetCount();
	LPUNKNOWN Get_NewEnum();
	LPDISPATCH Item(VARIANT* Index);
};
/////////////////////////////////////////////////////////////////////////////
// RoutingSlip wrapper class

class RoutingSlip : public COleDispatchDriver
{
public:
	RoutingSlip() {}		// Calls COleDispatchDriver default constructor
	RoutingSlip(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	RoutingSlip(const RoutingSlip& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	CString GetSubject();
	void SetSubject(LPCTSTR lpszNewValue);
	CString GetMessage();
	void SetMessage(LPCTSTR lpszNewValue);
	long GetDelivery();
	void SetDelivery(long nNewValue);
	BOOL GetTrackStatus();
	void SetTrackStatus(BOOL bNewValue);
	long GetProtect();
	void SetProtect(long nNewValue);
	BOOL GetReturnWhenDone();
	void SetReturnWhenDone(BOOL bNewValue);
	long GetStatus();
	VARIANT GetRecipients(VARIANT* Index);
	void Reset();
	void AddRecipient(LPCTSTR Recipient);
};
/////////////////////////////////////////////////////////////////////////////
// Bookmark wrapper class

class Bookmark : public COleDispatchDriver
{
public:
	Bookmark() {}		// Calls COleDispatchDriver default constructor
	Bookmark(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Bookmark(const Bookmark& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetName();
	LPDISPATCH GetRange();
	BOOL GetEmpty();
	long GetStart();
	void SetStart(long nNewValue);
	long GetEnd();
	void SetEnd(long nNewValue);
	BOOL GetColumn();
	long GetStoryType();
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	void Select();
	void Delete();
	LPDISPATCH Copy(LPCTSTR Name);
};
/////////////////////////////////////////////////////////////////////////////
// Bookmarks wrapper class

class Bookmarks : public COleDispatchDriver
{
public:
	Bookmarks() {}		// Calls COleDispatchDriver default constructor
	Bookmarks(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Bookmarks(const Bookmarks& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	long GetDefaultSorting();
	void SetDefaultSorting(long nNewValue);
	BOOL GetShowHidden();
	void SetShowHidden(BOOL bNewValue);
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH Item(VARIANT* Index);
	LPDISPATCH Add(LPCTSTR Name, VARIANT* Range);
	BOOL Exists(LPCTSTR Name);
};
/////////////////////////////////////////////////////////////////////////////
// Variable wrapper class

class Variable : public COleDispatchDriver
{
public:
	Variable() {}		// Calls COleDispatchDriver default constructor
	Variable(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Variable(const Variable& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	CString GetName();
	CString GetValue();
	void SetValue(LPCTSTR lpszNewValue);
	long GetIndex();
	void Delete();
};
/////////////////////////////////////////////////////////////////////////////
// Variables wrapper class

class Variables : public COleDispatchDriver
{
public:
	Variables() {}		// Calls COleDispatchDriver default constructor
	Variables(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Variables(const Variables& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH Item(VARIANT* Index);
	LPDISPATCH Add(LPCTSTR Name, VARIANT* Value);
};
/////////////////////////////////////////////////////////////////////////////
// RecentFile wrapper class

class RecentFile : public COleDispatchDriver
{
public:
	RecentFile() {}		// Calls COleDispatchDriver default constructor
	RecentFile(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	RecentFile(const RecentFile& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	CString GetName();
	long GetIndex();
	BOOL GetReadOnly();
	void SetReadOnly(BOOL bNewValue);
	CString GetPath();
	LPDISPATCH Open();
	void Delete();
};
/////////////////////////////////////////////////////////////////////////////
// RecentFiles wrapper class

class RecentFiles : public COleDispatchDriver
{
public:
	RecentFiles() {}		// Calls COleDispatchDriver default constructor
	RecentFiles(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	RecentFiles(const RecentFiles& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	long GetMaximum();
	void SetMaximum(long nNewValue);
	LPDISPATCH Item(long Index);
	LPDISPATCH Add(VARIANT* Document, VARIANT* ReadOnly);
};
/////////////////////////////////////////////////////////////////////////////
// Window wrapper class

class Window : public COleDispatchDriver
{
public:
	Window() {}		// Calls COleDispatchDriver default constructor
	Window(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Window(const Window& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH GetActivePane();
	LPDISPATCH GetDocument();
	LPDISPATCH GetPanes();
	LPDISPATCH GetSelection();
	long GetLeft();
	void SetLeft(long nNewValue);
	long GetTop();
	void SetTop(long nNewValue);
	long GetWidth();
	void SetWidth(long nNewValue);
	long GetHeight();
	void SetHeight(long nNewValue);
	BOOL GetSplit();
	void SetSplit(BOOL bNewValue);
	long GetSplitVertical();
	void SetSplitVertical(long nNewValue);
	CString GetCaption();
	void SetCaption(LPCTSTR lpszNewValue);
	long GetWindowState();
	void SetWindowState(long nNewValue);
	BOOL GetDisplayRulers();
	void SetDisplayRulers(BOOL bNewValue);
	BOOL GetDisplayVerticalRuler();
	void SetDisplayVerticalRuler(BOOL bNewValue);
	LPDISPATCH GetView();
	long GetType();
	LPDISPATCH GetNext();
	LPDISPATCH GetPrevious();
	long GetWindowNumber();
	BOOL GetDisplayVerticalScrollBar();
	void SetDisplayVerticalScrollBar(BOOL bNewValue);
	BOOL GetDisplayHorizontalScrollBar();
	void SetDisplayHorizontalScrollBar(BOOL bNewValue);
	float GetStyleAreaWidth();
	void SetStyleAreaWidth(float newValue);
	BOOL GetDisplayScreenTips();
	void SetDisplayScreenTips(BOOL bNewValue);
	long GetHorizontalPercentScrolled();
	void SetHorizontalPercentScrolled(long nNewValue);
	long GetVerticalPercentScrolled();
	void SetVerticalPercentScrolled(long nNewValue);
	BOOL GetDocumentMap();
	void SetDocumentMap(BOOL bNewValue);
	BOOL GetActive();
	long GetDocumentMapPercentWidth();
	void SetDocumentMapPercentWidth(long nNewValue);
	long GetIndex();
	void Activate();
	void Close(VARIANT* SaveChanges, VARIANT* RouteDocument);
	void LargeScroll(VARIANT* Down, VARIANT* Up, VARIANT* ToRight, VARIANT* ToLeft);
	void SmallScroll(VARIANT* Down, VARIANT* Up, VARIANT* ToRight, VARIANT* ToLeft);
	LPDISPATCH NewWindow();
	void PrintOut(VARIANT* Background, VARIANT* Append, VARIANT* Range, VARIANT* OutputFileName, VARIANT* From, VARIANT* To, VARIANT* Item, VARIANT* Copies, VARIANT* Pages, VARIANT* PageType, VARIANT* PrintToFile, VARIANT* Collate, 
		VARIANT* ActivePrinterMacGX, VARIANT* ManualDuplexPrint);
	void PageScroll(VARIANT* Down, VARIANT* Up);
};
/////////////////////////////////////////////////////////////////////////////
// Windows wrapper class

class Windows : public COleDispatchDriver
{
public:
	Windows() {}		// Calls COleDispatchDriver default constructor
	Windows(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Windows(const Windows& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH Item(VARIANT* Index);
	LPDISPATCH Add(VARIANT* Window);
	void Arrange(VARIANT* ArrangeStyle);
};
/////////////////////////////////////////////////////////////////////////////
// Pane wrapper class

class Pane : public COleDispatchDriver
{
public:
	Pane() {}		// Calls COleDispatchDriver default constructor
	Pane(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Pane(const Pane& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH GetDocument();
	LPDISPATCH GetSelection();
	BOOL GetDisplayRulers();
	void SetDisplayRulers(BOOL bNewValue);
	BOOL GetDisplayVerticalRuler();
	void SetDisplayVerticalRuler(BOOL bNewValue);
	LPDISPATCH GetZooms();
	long GetIndex();
	LPDISPATCH GetView();
	LPDISPATCH GetNext();
	LPDISPATCH GetPrevious();
	long GetHorizontalPercentScrolled();
	void SetHorizontalPercentScrolled(long nNewValue);
	long GetVerticalPercentScrolled();
	void SetVerticalPercentScrolled(long nNewValue);
	long GetMinimumFontSize();
	void SetMinimumFontSize(long nNewValue);
	BOOL GetBrowseToWindow();
	void SetBrowseToWindow(BOOL bNewValue);
	long GetBrowseWidth();
	void Activate();
	void Close();
	void LargeScroll(VARIANT* Down, VARIANT* Up, VARIANT* ToRight, VARIANT* ToLeft);
	void SmallScroll(VARIANT* Down, VARIANT* Up, VARIANT* ToRight, VARIANT* ToLeft);
	void AutoScroll(long Velocity);
	void PageScroll(VARIANT* Down, VARIANT* Up);
};
/////////////////////////////////////////////////////////////////////////////
// Panes wrapper class

class Panes : public COleDispatchDriver
{
public:
	Panes() {}		// Calls COleDispatchDriver default constructor
	Panes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Panes(const Panes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH Item(long Index);
	LPDISPATCH Add(VARIANT* SplitVertical);
};
/////////////////////////////////////////////////////////////////////////////
// Range wrapper class

class Range : public COleDispatchDriver
{
public:
	Range() {}		// Calls COleDispatchDriver default constructor
	Range(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Range(const Range& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	LPDISPATCH GetFormattedText();
	void SetFormattedText(LPDISPATCH newValue);
	long GetStart();
	void SetStart(long nNewValue);
	long GetEnd();
	void SetEnd(long nNewValue);
	LPDISPATCH GetFont();
	void SetFont(LPDISPATCH newValue);
	LPDISPATCH GetDuplicate();
	long GetStoryType();
	LPDISPATCH GetTables();
	LPDISPATCH GetWords();
	LPDISPATCH GetSentences();
	LPDISPATCH GetCharacters();
	LPDISPATCH GetFootnotes();
	LPDISPATCH GetEndnotes();
	LPDISPATCH GetComments();
	LPDISPATCH GetCells();
	LPDISPATCH GetSections();
	LPDISPATCH GetParagraphs();
	LPDISPATCH GetBorders();
	void SetBorders(LPDISPATCH newValue);
	LPDISPATCH GetShading();
	LPDISPATCH GetTextRetrievalMode();
	void SetTextRetrievalMode(LPDISPATCH newValue);
	LPDISPATCH GetFields();
	LPDISPATCH GetFormFields();
	LPDISPATCH GetFrames();
	LPDISPATCH GetParagraphFormat();
	void SetParagraphFormat(LPDISPATCH newValue);
	LPDISPATCH GetListFormat();
	LPDISPATCH GetBookmarks();
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetBold();
	void SetBold(long nNewValue);
	long GetItalic();
	void SetItalic(long nNewValue);
	long GetUnderline();
	void SetUnderline(long nNewValue);
	LPDISPATCH GetRevisions();
	VARIANT GetStyle();
	void SetStyle(VARIANT* newValue);
	long GetStoryLength();
	long GetLanguageID();
	void SetLanguageID(long nNewValue);
	LPDISPATCH GetSynonymInfo();
	LPDISPATCH GetHyperlinks();
	LPDISPATCH GetListParagraphs();
	LPDISPATCH GetSubdocuments();
	BOOL GetGrammarChecked();
	void SetGrammarChecked(BOOL bNewValue);
	BOOL GetSpellingChecked();
	void SetSpellingChecked(BOOL bNewValue);
	long GetHighlightColorIndex();
	void SetHighlightColorIndex(long nNewValue);
	LPDISPATCH GetColumns();
	LPDISPATCH GetRows();
	BOOL GetIsEndOfRowMark();
	long GetBookmarkID();
	long GetPreviousBookmarkID();
	LPDISPATCH GetFind();
	LPDISPATCH GetPageSetup();
	void SetPageSetup(LPDISPATCH newValue);
	LPDISPATCH GetShapeRange();
	long GetCase();
	void SetCase(long nNewValue);
	VARIANT GetInformation(long Type);
	LPDISPATCH GetReadabilityStatistics();
	LPDISPATCH GetGrammaticalErrors();
	LPDISPATCH GetSpellingErrors();
	long GetOrientation();
	void SetOrientation(long nNewValue);
	LPDISPATCH GetInlineShapes();
	LPDISPATCH GetNextStoryRange();
	long GetLanguageIDFarEast();
	void SetLanguageIDFarEast(long nNewValue);
	long GetLanguageIDOther();
	void SetLanguageIDOther(long nNewValue);
	void Select();
	void SetRange(long Start, long End);
	void Collapse(VARIANT* Direction);
	void InsertBefore(LPCTSTR Text);
	void InsertAfter(LPCTSTR Text);
	LPDISPATCH Next(VARIANT* Unit, VARIANT* Count);
	LPDISPATCH Previous(VARIANT* Unit, VARIANT* Count);
	long StartOf(VARIANT* Unit, VARIANT* Extend);
	long EndOf(VARIANT* Unit, VARIANT* Extend);
	long Move(VARIANT* Unit, VARIANT* Count);
	long MoveStart(VARIANT* Unit, VARIANT* Count);
	long MoveEnd(VARIANT* Unit, VARIANT* Count);
	long MoveWhile(VARIANT* Cset, VARIANT* Count);
	long MoveStartWhile(VARIANT* Cset, VARIANT* Count);
	long MoveEndWhile(VARIANT* Cset, VARIANT* Count);
	long MoveUntil(VARIANT* Cset, VARIANT* Count);
	long MoveStartUntil(VARIANT* Cset, VARIANT* Count);
	long MoveEndUntil(VARIANT* Cset, VARIANT* Count);
	void Cut();
	void Copy();
	void Paste();
	void InsertBreak(VARIANT* Type);
	void InsertFile(LPCTSTR FileName, VARIANT* Range, VARIANT* ConfirmConversions, VARIANT* Link, VARIANT* Attachment);
	BOOL InStory(LPDISPATCH Range);
	BOOL InRange(LPDISPATCH Range);
	long Delete(VARIANT* Unit, VARIANT* Count);
	void WholeStory();
	long Expand(VARIANT* Unit);
	void InsertParagraph();
	void InsertParagraphAfter();
	LPDISPATCH ConvertToTable(VARIANT* Separator, VARIANT* NumRows, VARIANT* NumColumns, VARIANT* InitialColumnWidth, VARIANT* Format, VARIANT* ApplyBorders, VARIANT* ApplyShading, VARIANT* ApplyFont, VARIANT* ApplyColor, 
		VARIANT* ApplyHeadingRows, VARIANT* ApplyLastRow, VARIANT* ApplyFirstColumn, VARIANT* ApplyLastColumn, VARIANT* AutoFit);
	void InsertDateTime(VARIANT* DateTimeFormat, VARIANT* InsertAsField, VARIANT* InsertAsFullWidth);
	void InsertSymbol(long CharacterNumber, VARIANT* Font, VARIANT* Unicode, VARIANT* Bias);
	void InsertCrossReference(VARIANT* ReferenceType, long ReferenceKind, VARIANT* ReferenceItem, VARIANT* InsertAsHyperlink, VARIANT* IncludePosition);
	void InsertCaption(VARIANT* Label, VARIANT* Title, VARIANT* TitleAutoText, VARIANT* Position);
	void CopyAsPicture();
	void Sort(VARIANT* ExcludeHeader, VARIANT* FieldNumber, VARIANT* SortFieldType, VARIANT* SortOrder, VARIANT* FieldNumber2, VARIANT* SortFieldType2, VARIANT* SortOrder2, VARIANT* FieldNumber3, VARIANT* SortFieldType3, VARIANT* SortOrder3, 
		VARIANT* SortColumn, VARIANT* Separator, VARIANT* CaseSensitive, VARIANT* LanguageID);
	void SortAscending();
	void SortDescending();
	BOOL IsEqual(LPDISPATCH Range);
	float Calculate();
	LPDISPATCH GoTo(VARIANT* What, VARIANT* Which, VARIANT* Count, VARIANT* Name);
	LPDISPATCH GoToNext(long What);
	LPDISPATCH GoToPrevious(long What);
	void PasteSpecial(VARIANT* IconIndex, VARIANT* Link, VARIANT* Placement, VARIANT* DisplayAsIcon, VARIANT* DataType, VARIANT* IconFileName, VARIANT* IconLabel);
	void LookupNameProperties();
	long ComputeStatistics(long Statistic);
	void Relocate(long Direction);
	void CheckSynonyms();
	void SubscribeTo(LPCTSTR Edition, VARIANT* Format);
	void CreatePublisher(VARIANT* Edition, VARIANT* ContainsPICT, VARIANT* ContainsRTF, VARIANT* ContainsText);
	void InsertAutoText();
	void InsertDatabase(VARIANT* Format, VARIANT* Style, VARIANT* LinkToSource, VARIANT* Connection, VARIANT* SQLStatement, VARIANT* SQLStatement1, VARIANT* PasswordDocument, VARIANT* PasswordTemplate, VARIANT* WritePasswordDocument, 
		VARIANT* WritePasswordTemplate, VARIANT* DataSource, VARIANT* From, VARIANT* To, VARIANT* IncludeFields);
	void AutoFormat();
	void CheckGrammar();
	void CheckSpelling(VARIANT* CustomDictionary, VARIANT* IgnoreUppercase, VARIANT* AlwaysSuggest, VARIANT* CustomDictionary2, VARIANT* CustomDictionary3, VARIANT* CustomDictionary4, VARIANT* CustomDictionary5, VARIANT* CustomDictionary6, 
		VARIANT* CustomDictionary7, VARIANT* CustomDictionary8, VARIANT* CustomDictionary9, VARIANT* CustomDictionary10);
	LPDISPATCH GetSpellingSuggestions(VARIANT* CustomDictionary, VARIANT* IgnoreUppercase, VARIANT* MainDictionary, VARIANT* SuggestionMode, VARIANT* CustomDictionary2, VARIANT* CustomDictionary3, VARIANT* CustomDictionary4, 
		VARIANT* CustomDictionary5, VARIANT* CustomDictionary6, VARIANT* CustomDictionary7, VARIANT* CustomDictionary8, VARIANT* CustomDictionary9, VARIANT* CustomDictionary10);
	void InsertParagraphBefore();
	void NextSubdocument();
	void PreviousSubdocument();
};
/////////////////////////////////////////////////////////////////////////////
// ListFormat wrapper class

class ListFormat : public COleDispatchDriver
{
public:
	ListFormat() {}		// Calls COleDispatchDriver default constructor
	ListFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ListFormat(const ListFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetListLevelNumber();
	void SetListLevelNumber(long nNewValue);
	LPDISPATCH GetList();
	LPDISPATCH GetListTemplate();
	long GetListValue();
	BOOL GetSingleList();
	BOOL GetSingleListTemplate();
	long GetListType();
	CString GetListString();
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long CanContinuePreviousList(LPDISPATCH ListTemplate);
	void RemoveNumbers(VARIANT* NumberType);
	void ConvertNumbersToText(VARIANT* NumberType);
	long CountNumberedItems(VARIANT* NumberType, VARIANT* Level);
	void ApplyBulletDefault();
	void ApplyNumberDefault();
	void ApplyOutlineNumberDefault();
	void ApplyListTemplate(LPDISPATCH ListTemplate, VARIANT* ContinuePreviousList, VARIANT* ApplyTo);
	void ListOutdent();
	void ListIndent();
};
/////////////////////////////////////////////////////////////////////////////
// Find wrapper class

class Find : public COleDispatchDriver
{
public:
	Find() {}		// Calls COleDispatchDriver default constructor
	Find(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Find(const Find& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	BOOL GetForward();
	void SetForward(BOOL bNewValue);
	LPDISPATCH GetFont();
	void SetFont(LPDISPATCH newValue);
	BOOL GetFound();
	BOOL GetMatchAllWordForms();
	void SetMatchAllWordForms(BOOL bNewValue);
	BOOL GetMatchCase();
	void SetMatchCase(BOOL bNewValue);
	BOOL GetMatchWildcards();
	void SetMatchWildcards(BOOL bNewValue);
	BOOL GetMatchSoundsLike();
	void SetMatchSoundsLike(BOOL bNewValue);
	BOOL GetMatchWholeWord();
	void SetMatchWholeWord(BOOL bNewValue);
	LPDISPATCH GetParagraphFormat();
	void SetParagraphFormat(LPDISPATCH newValue);
	VARIANT GetStyle();
	void SetStyle(VARIANT* newValue);
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	long GetLanguageID();
	void SetLanguageID(long nNewValue);
	long GetHighlight();
	void SetHighlight(long nNewValue);
	LPDISPATCH GetReplacement();
	LPDISPATCH GetFrame();
	long GetWrap();
	void SetWrap(long nNewValue);
	BOOL GetFormat();
	void SetFormat(BOOL bNewValue);
	long GetLanguageIDFarEast();
	void SetLanguageIDFarEast(long nNewValue);
	long GetLanguageIDOther();
	void SetLanguageIDOther(long nNewValue);
	BOOL Execute(VARIANT* FindText, VARIANT* MatchCase, VARIANT* MatchWholeWord, VARIANT* MatchWildcards, VARIANT* MatchSoundsLike, VARIANT* MatchAllWordForms, VARIANT* Forward, VARIANT* Wrap, VARIANT* Format, VARIANT* ReplaceWith, 
		VARIANT* Replace);
	void ClearFormatting();
};
/////////////////////////////////////////////////////////////////////////////
// Replacement wrapper class

class Replacement : public COleDispatchDriver
{
public:
	Replacement() {}		// Calls COleDispatchDriver default constructor
	Replacement(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Replacement(const Replacement& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH GetFont();
	void SetFont(LPDISPATCH newValue);
	LPDISPATCH GetParagraphFormat();
	void SetParagraphFormat(LPDISPATCH newValue);
	VARIANT GetStyle();
	void SetStyle(VARIANT* newValue);
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	long GetLanguageID();
	void SetLanguageID(long nNewValue);
	long GetHighlight();
	void SetHighlight(long nNewValue);
	LPDISPATCH GetFrame();
	long GetLanguageIDFarEast();
	void SetLanguageIDFarEast(long nNewValue);
	void ClearFormatting();
};
/////////////////////////////////////////////////////////////////////////////
// Characters wrapper class

class Characters : public COleDispatchDriver
{
public:
	Characters() {}		// Calls COleDispatchDriver default constructor
	Characters(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Characters(const Characters& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH GetFirst();
	LPDISPATCH GetLast();
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH Item(long Index);
};
/////////////////////////////////////////////////////////////////////////////
// Words wrapper class

class Words : public COleDispatchDriver
{
public:
	Words() {}		// Calls COleDispatchDriver default constructor
	Words(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Words(const Words& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH GetFirst();
	LPDISPATCH GetLast();
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH Item(long Index);
};
/////////////////////////////////////////////////////////////////////////////
// Sentences wrapper class

class Sentences : public COleDispatchDriver
{
public:
	Sentences() {}		// Calls COleDispatchDriver default constructor
	Sentences(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Sentences(const Sentences& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH GetFirst();
	LPDISPATCH GetLast();
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH Item(long Index);
};
/////////////////////////////////////////////////////////////////////////////
// Sections wrapper class

class Sections : public COleDispatchDriver
{
public:
	Sections() {}		// Calls COleDispatchDriver default constructor
	Sections(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Sections(const Sections& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH GetFirst();
	LPDISPATCH GetLast();
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH GetPageSetup();
	void SetPageSetup(LPDISPATCH newValue);
	LPDISPATCH Item(long Index);
	LPDISPATCH Add(VARIANT* Range, VARIANT* Start);
};
/////////////////////////////////////////////////////////////////////////////
// Section wrapper class

class Section : public COleDispatchDriver
{
public:
	Section() {}		// Calls COleDispatchDriver default constructor
	Section(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Section(const Section& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetRange();
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH GetPageSetup();
	void SetPageSetup(LPDISPATCH newValue);
	LPDISPATCH GetHeaders();
	LPDISPATCH GetFooters();
	BOOL GetProtectedForForms();
	void SetProtectedForForms(BOOL bNewValue);
	long GetIndex();
	LPDISPATCH GetBorders();
	void SetBorders(LPDISPATCH newValue);
};
/////////////////////////////////////////////////////////////////////////////
// Paragraphs wrapper class

class Paragraphs : public COleDispatchDriver
{
public:
	Paragraphs() {}		// Calls COleDispatchDriver default constructor
	Paragraphs(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Paragraphs(const Paragraphs& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH GetFirst();
	LPDISPATCH GetLast();
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH GetFormat();
	void SetFormat(LPDISPATCH newValue);
	LPDISPATCH GetTabStops();
	void SetTabStops(LPDISPATCH newValue);
	LPDISPATCH GetBorders();
	void SetBorders(LPDISPATCH newValue);
	VARIANT GetStyle();
	void SetStyle(VARIANT* newValue);
	long GetAlignment();
	void SetAlignment(long nNewValue);
	long GetKeepTogether();
	void SetKeepTogether(long nNewValue);
	long GetKeepWithNext();
	void SetKeepWithNext(long nNewValue);
	long GetPageBreakBefore();
	void SetPageBreakBefore(long nNewValue);
	long GetNoLineNumber();
	void SetNoLineNumber(long nNewValue);
	float GetRightIndent();
	void SetRightIndent(float newValue);
	float GetLeftIndent();
	void SetLeftIndent(float newValue);
	float GetFirstLineIndent();
	void SetFirstLineIndent(float newValue);
	float GetLineSpacing();
	void SetLineSpacing(float newValue);
	long GetLineSpacingRule();
	void SetLineSpacingRule(long nNewValue);
	float GetSpaceBefore();
	void SetSpaceBefore(float newValue);
	float GetSpaceAfter();
	void SetSpaceAfter(float newValue);
	long GetHyphenation();
	void SetHyphenation(long nNewValue);
	long GetWidowControl();
	void SetWidowControl(long nNewValue);
	LPDISPATCH GetShading();
	long GetOutlineLevel();
	void SetOutlineLevel(long nNewValue);
	LPDISPATCH Item(long Index);
	LPDISPATCH Add(VARIANT* Range);
	void CloseUp();
	void OpenUp();
	void OpenOrCloseUp();
	void TabHangingIndent(short Count);
	void TabIndent(short Count);
	void Reset();
	void Space1();
	void Space15();
	void Space2();
	void OutlinePromote();
	void OutlineDemote();
	void OutlineDemoteToBody();
	void Indent();
	void Outdent();
};
/////////////////////////////////////////////////////////////////////////////
// Paragraph wrapper class

class Paragraph : public COleDispatchDriver
{
public:
	Paragraph() {}		// Calls COleDispatchDriver default constructor
	Paragraph(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Paragraph(const Paragraph& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetRange();
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH GetFormat();
	void SetFormat(LPDISPATCH newValue);
	LPDISPATCH GetTabStops();
	void SetTabStops(LPDISPATCH newValue);
	LPDISPATCH GetBorders();
	void SetBorders(LPDISPATCH newValue);
	LPDISPATCH GetDropCap();
	VARIANT GetStyle();
	void SetStyle(VARIANT* newValue);
	long GetAlignment();
	void SetAlignment(long nNewValue);
	long GetKeepTogether();
	void SetKeepTogether(long nNewValue);
	long GetKeepWithNext();
	void SetKeepWithNext(long nNewValue);
	long GetPageBreakBefore();
	void SetPageBreakBefore(long nNewValue);
	long GetNoLineNumber();
	void SetNoLineNumber(long nNewValue);
	float GetRightIndent();
	void SetRightIndent(float newValue);
	float GetLeftIndent();
	void SetLeftIndent(float newValue);
	float GetFirstLineIndent();
	void SetFirstLineIndent(float newValue);
	float GetLineSpacing();
	void SetLineSpacing(float newValue);
	long GetLineSpacingRule();
	void SetLineSpacingRule(long nNewValue);
	float GetSpaceBefore();
	void SetSpaceBefore(float newValue);
	float GetSpaceAfter();
	void SetSpaceAfter(float newValue);
	long GetHyphenation();
	void SetHyphenation(long nNewValue);
	long GetWidowControl();
	void SetWidowControl(long nNewValue);
	LPDISPATCH GetShading();
	long GetOutlineLevel();
	void SetOutlineLevel(long nNewValue);
	void CloseUp();
	void OpenUp();
	void OpenOrCloseUp();
	void TabHangingIndent(short Count);
	void TabIndent(short Count);
	void Reset();
	void Space1();
	void Space15();
	void Space2();
	LPDISPATCH Next(VARIANT* Count);
	LPDISPATCH Previous(VARIANT* Count);
	void OutlinePromote();
	void OutlineDemote();
	void OutlineDemoteToBody();
	void Indent();
	void Outdent();
};
/////////////////////////////////////////////////////////////////////////////
// DropCap wrapper class

class DropCap : public COleDispatchDriver
{
public:
	DropCap() {}		// Calls COleDispatchDriver default constructor
	DropCap(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DropCap(const DropCap& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetPosition();
	void SetPosition(long nNewValue);
	CString GetFontName();
	void SetFontName(LPCTSTR lpszNewValue);
	long GetLinesToDrop();
	void SetLinesToDrop(long nNewValue);
	float GetDistanceFromText();
	void SetDistanceFromText(float newValue);
	void Clear();
	void Enable();
};
/////////////////////////////////////////////////////////////////////////////
// TabStops wrapper class

class TabStops : public COleDispatchDriver
{
public:
	TabStops() {}		// Calls COleDispatchDriver default constructor
	TabStops(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	TabStops(const TabStops& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH Item(VARIANT* Index);
	LPDISPATCH Add(float Position, VARIANT* Alignment, VARIANT* Leader);
	void ClearAll();
	LPDISPATCH Before(float Position);
	LPDISPATCH After(float Position);
};
/////////////////////////////////////////////////////////////////////////////
// TabStop wrapper class

class TabStop : public COleDispatchDriver
{
public:
	TabStop() {}		// Calls COleDispatchDriver default constructor
	TabStop(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	TabStop(const TabStop& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetAlignment();
	void SetAlignment(long nNewValue);
	long GetLeader();
	void SetLeader(long nNewValue);
	float GetPosition();
	void SetPosition(float newValue);
	BOOL GetCustomTab();
	LPDISPATCH GetNext();
	LPDISPATCH GetPrevious();
	void Clear();
};
/////////////////////////////////////////////////////////////////////////////
// _ParagraphFormat wrapper class

class _ParagraphFormat : public COleDispatchDriver
{
public:
	_ParagraphFormat() {}		// Calls COleDispatchDriver default constructor
	_ParagraphFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_ParagraphFormat(const _ParagraphFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH GetDuplicate();
	VARIANT GetStyle();
	void SetStyle(VARIANT* newValue);
	long GetAlignment();
	void SetAlignment(long nNewValue);
	long GetKeepTogether();
	void SetKeepTogether(long nNewValue);
	long GetKeepWithNext();
	void SetKeepWithNext(long nNewValue);
	long GetPageBreakBefore();
	void SetPageBreakBefore(long nNewValue);
	long GetNoLineNumber();
	void SetNoLineNumber(long nNewValue);
	float GetRightIndent();
	void SetRightIndent(float newValue);
	float GetLeftIndent();
	void SetLeftIndent(float newValue);
	float GetFirstLineIndent();
	void SetFirstLineIndent(float newValue);
	float GetLineSpacing();
	void SetLineSpacing(float newValue);
	long GetLineSpacingRule();
	void SetLineSpacingRule(long nNewValue);
	float GetSpaceBefore();
	void SetSpaceBefore(float newValue);
	float GetSpaceAfter();
	void SetSpaceAfter(float newValue);
	long GetHyphenation();
	void SetHyphenation(long nNewValue);
	long GetWidowControl();
	void SetWidowControl(long nNewValue);
	LPDISPATCH GetTabStops();
	void SetTabStops(LPDISPATCH newValue);
	LPDISPATCH GetBorders();
	void SetBorders(LPDISPATCH newValue);
	LPDISPATCH GetShading();
	long GetOutlineLevel();
	void SetOutlineLevel(long nNewValue);
	void CloseUp();
	void OpenUp();
	void OpenOrCloseUp();
	void TabHangingIndent(short Count);
	void TabIndent(short Count);
	void Reset();
	void Space1();
	void Space15();
	void Space2();
};
/////////////////////////////////////////////////////////////////////////////
// _Font wrapper class

class _Font : public COleDispatchDriver
{
public:
	_Font() {}		// Calls COleDispatchDriver default constructor
	_Font(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_Font(const _Font& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH GetDuplicate();
	long GetBold();
	void SetBold(long nNewValue);
	long GetItalic();
	void SetItalic(long nNewValue);
	long GetHidden();
	void SetHidden(long nNewValue);
	long GetSmallCaps();
	void SetSmallCaps(long nNewValue);
	long GetAllCaps();
	void SetAllCaps(long nNewValue);
	long GetStrikeThrough();
	void SetStrikeThrough(long nNewValue);
	long GetDoubleStrikeThrough();
	void SetDoubleStrikeThrough(long nNewValue);
	long GetColorIndex();
	void SetColorIndex(long nNewValue);
	long GetSubscript();
	void SetSubscript(long nNewValue);
	long GetSuperscript();
	void SetSuperscript(long nNewValue);
	long GetUnderline();
	void SetUnderline(long nNewValue);
	float GetSize();
	void SetSize(float newValue);
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	long GetPosition();
	void SetPosition(long nNewValue);
	float GetSpacing();
	void SetSpacing(float newValue);
	long GetScaling();
	void SetScaling(long nNewValue);
	long GetShadow();
	void SetShadow(long nNewValue);
	long GetOutline();
	void SetOutline(long nNewValue);
	long GetEmboss();
	void SetEmboss(long nNewValue);
	float GetKerning();
	void SetKerning(float newValue);
	long GetEngrave();
	void SetEngrave(long nNewValue);
	long GetAnimation();
	void SetAnimation(long nNewValue);
	LPDISPATCH GetBorders();
	void SetBorders(LPDISPATCH newValue);
	LPDISPATCH GetShading();
	CString GetNameFarEast();
	void SetNameFarEast(LPCTSTR lpszNewValue);
	CString GetNameAscii();
	void SetNameAscii(LPCTSTR lpszNewValue);
	CString GetNameOther();
	void SetNameOther(LPCTSTR lpszNewValue);
	void Grow();
	void Shrink();
	void Reset();
	void SetAsTemplateDefault();
};
/////////////////////////////////////////////////////////////////////////////
// Table wrapper class

class Table : public COleDispatchDriver
{
public:
	Table() {}		// Calls COleDispatchDriver default constructor
	Table(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Table(const Table& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetRange();
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH GetColumns();
	LPDISPATCH GetRows();
	LPDISPATCH GetBorders();
	void SetBorders(LPDISPATCH newValue);
	LPDISPATCH GetShading();
	BOOL GetUniform();
	long GetAutoFormatType();
	void Select();
	void Delete();
	void Sort(VARIANT* ExcludeHeader, VARIANT* FieldNumber, VARIANT* SortFieldType, VARIANT* SortOrder, VARIANT* FieldNumber2, VARIANT* SortFieldType2, VARIANT* SortOrder2, VARIANT* FieldNumber3, VARIANT* SortFieldType3, VARIANT* SortOrder3, 
		VARIANT* CaseSensitive, VARIANT* LanguageID);
	void SortAscending();
	void SortDescending();
	void AutoFormat(VARIANT* Format, VARIANT* ApplyBorders, VARIANT* ApplyShading, VARIANT* ApplyFont, VARIANT* ApplyColor, VARIANT* ApplyHeadingRows, VARIANT* ApplyLastRow, VARIANT* ApplyFirstColumn, VARIANT* ApplyLastColumn, VARIANT* AutoFit);
	void UpdateAutoFormat();
	LPDISPATCH ConvertToText(VARIANT* Separator);
	LPDISPATCH Cell(long Row, long Column);
	LPDISPATCH Split(VARIANT* BeforeRow);
};
/////////////////////////////////////////////////////////////////////////////
// Row wrapper class

class Row : public COleDispatchDriver
{
public:
	Row() {}		// Calls COleDispatchDriver default constructor
	Row(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Row(const Row& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetRange();
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetAllowBreakAcrossPages();
	void SetAllowBreakAcrossPages(long nNewValue);
	long GetAlignment();
	void SetAlignment(long nNewValue);
	long GetHeadingFormat();
	void SetHeadingFormat(long nNewValue);
	float GetSpaceBetweenColumns();
	void SetSpaceBetweenColumns(float newValue);
	float GetHeight();
	void SetHeight(float newValue);
	long GetHeightRule();
	void SetHeightRule(long nNewValue);
	float GetLeftIndent();
	void SetLeftIndent(float newValue);
	BOOL GetIsLast();
	BOOL GetIsFirst();
	long GetIndex();
	LPDISPATCH GetCells();
	LPDISPATCH GetBorders();
	void SetBorders(LPDISPATCH newValue);
	LPDISPATCH GetShading();
	LPDISPATCH GetNext();
	LPDISPATCH GetPrevious();
	void Select();
	void Delete();
	void SetLeftIndent(float LeftIndent, long RulerStyle);
	void SetHeight(float RowHeight, long HeightRule);
	LPDISPATCH ConvertToText(VARIANT* Separator);
};
/////////////////////////////////////////////////////////////////////////////
// Column wrapper class

class Column : public COleDispatchDriver
{
public:
	Column() {}		// Calls COleDispatchDriver default constructor
	Column(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Column(const Column& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	float GetWidth();
	void SetWidth(float newValue);
	BOOL GetIsFirst();
	BOOL GetIsLast();
	long GetIndex();
	LPDISPATCH GetCells();
	LPDISPATCH GetBorders();
	void SetBorders(LPDISPATCH newValue);
	LPDISPATCH GetShading();
	LPDISPATCH GetNext();
	LPDISPATCH GetPrevious();
	void Select();
	void Delete();
	void SetWidth(float ColumnWidth, long RulerStyle);
	void AutoFit();
	void Sort(VARIANT* ExcludeHeader, VARIANT* SortFieldType, VARIANT* SortOrder, VARIANT* CaseSensitive, VARIANT* LanguageID);
};
/////////////////////////////////////////////////////////////////////////////
// Cell wrapper class

class Cell : public COleDispatchDriver
{
public:
	Cell() {}		// Calls COleDispatchDriver default constructor
	Cell(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Cell(const Cell& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetRange();
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetRowIndex();
	long GetColumnIndex();
	float GetWidth();
	void SetWidth(float newValue);
	float GetHeight();
	void SetHeight(float newValue);
	long GetHeightRule();
	void SetHeightRule(long nNewValue);
	long GetVerticalAlignment();
	void SetVerticalAlignment(long nNewValue);
	LPDISPATCH GetColumn();
	LPDISPATCH GetRow();
	LPDISPATCH GetNext();
	LPDISPATCH GetPrevious();
	LPDISPATCH GetShading();
	LPDISPATCH GetBorders();
	void SetBorders(LPDISPATCH newValue);
	void Select();
	void Delete(VARIANT* ShiftCells);
	void Formula(VARIANT* Formula, VARIANT* NumFormat);
	void SetWidth(float ColumnWidth, long RulerStyle);
	void SetHeight(VARIANT* RowHeight, long HeightRule);
	void Merge(LPDISPATCH MergeTo);
	void Split(VARIANT* NumRows, VARIANT* NumColumns);
	void AutoSum();
};
/////////////////////////////////////////////////////////////////////////////
// Tables wrapper class

class Tables : public COleDispatchDriver
{
public:
	Tables() {}		// Calls COleDispatchDriver default constructor
	Tables(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Tables(const Tables& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH Item(long Index);
	LPDISPATCH Add(LPDISPATCH Range, long NumRows, long NumColumns);
};
/////////////////////////////////////////////////////////////////////////////
// Rows wrapper class

class Rows : public COleDispatchDriver
{
public:
	Rows() {}		// Calls COleDispatchDriver default constructor
	Rows(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Rows(const Rows& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	long GetAllowBreakAcrossPages();
	void SetAllowBreakAcrossPages(long nNewValue);
	long GetAlignment();
	void SetAlignment(long nNewValue);
	long GetHeadingFormat();
	void SetHeadingFormat(long nNewValue);
	float GetSpaceBetweenColumns();
	void SetSpaceBetweenColumns(float newValue);
	float GetHeight();
	void SetHeight(float newValue);
	long GetHeightRule();
	void SetHeightRule(long nNewValue);
	float GetLeftIndent();
	void SetLeftIndent(float newValue);
	LPDISPATCH GetFirst();
	LPDISPATCH GetLast();
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH GetBorders();
	void SetBorders(LPDISPATCH newValue);
	LPDISPATCH GetShading();
	LPDISPATCH Item(long Index);
	LPDISPATCH Add(VARIANT* BeforeRow);
	void Select();
	void Delete();
	void SetLeftIndent(float LeftIndent, long RulerStyle);
	void SetHeight(float RowHeight, long HeightRule);
	LPDISPATCH ConvertToText(VARIANT* Separator);
	void DistributeHeight();
};
/////////////////////////////////////////////////////////////////////////////
// Columns wrapper class

class Columns : public COleDispatchDriver
{
public:
	Columns() {}		// Calls COleDispatchDriver default constructor
	Columns(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Columns(const Columns& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH GetFirst();
	LPDISPATCH GetLast();
	float GetWidth();
	void SetWidth(float newValue);
	LPDISPATCH GetBorders();
	void SetBorders(LPDISPATCH newValue);
	LPDISPATCH GetShading();
	LPDISPATCH Item(long Index);
	LPDISPATCH Add(VARIANT* BeforeColumn);
	void Select();
	void Delete();
	void SetWidth(float ColumnWidth, long RulerStyle);
	void AutoFit();
	void DistributeWidth();
};
/////////////////////////////////////////////////////////////////////////////
// Cells wrapper class

class Cells : public COleDispatchDriver
{
public:
	Cells() {}		// Calls COleDispatchDriver default constructor
	Cells(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Cells(const Cells& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	float GetWidth();
	void SetWidth(float newValue);
	float GetHeight();
	void SetHeight(float newValue);
	long GetHeightRule();
	void SetHeightRule(long nNewValue);
	long GetVerticalAlignment();
	void SetVerticalAlignment(long nNewValue);
	LPDISPATCH GetBorders();
	void SetBorders(LPDISPATCH newValue);
	LPDISPATCH GetShading();
	LPDISPATCH Item(long Index);
	LPDISPATCH Add(VARIANT* BeforeCell);
	void Delete(VARIANT* ShiftCells);
	void SetWidth(float ColumnWidth, long RulerStyle);
	void SetHeight(VARIANT* RowHeight, long HeightRule);
	void Merge();
	void Split(VARIANT* NumRows, VARIANT* NumColumns, VARIANT* MergeBeforeSplit);
	void DistributeHeight();
	void DistributeWidth();
	void AutoFit();
};
/////////////////////////////////////////////////////////////////////////////
// AutoCorrect wrapper class

class AutoCorrect : public COleDispatchDriver
{
public:
	AutoCorrect() {}		// Calls COleDispatchDriver default constructor
	AutoCorrect(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	AutoCorrect(const AutoCorrect& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	BOOL GetCorrectDays();
	void SetCorrectDays(BOOL bNewValue);
	BOOL GetCorrectInitialCaps();
	void SetCorrectInitialCaps(BOOL bNewValue);
	BOOL GetCorrectSentenceCaps();
	void SetCorrectSentenceCaps(BOOL bNewValue);
	BOOL GetReplaceText();
	void SetReplaceText(BOOL bNewValue);
	LPDISPATCH GetEntries();
	LPDISPATCH GetFirstLetterExceptions();
	BOOL GetFirstLetterAutoAdd();
	void SetFirstLetterAutoAdd(BOOL bNewValue);
	LPDISPATCH GetTwoInitialCapsExceptions();
	BOOL GetTwoInitialCapsAutoAdd();
	void SetTwoInitialCapsAutoAdd(BOOL bNewValue);
	BOOL GetCorrectCapsLock();
	void SetCorrectCapsLock(BOOL bNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// AutoCorrectEntries wrapper class

class AutoCorrectEntries : public COleDispatchDriver
{
public:
	AutoCorrectEntries() {}		// Calls COleDispatchDriver default constructor
	AutoCorrectEntries(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	AutoCorrectEntries(const AutoCorrectEntries& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH Item(VARIANT* Index);
	LPDISPATCH Add(LPCTSTR Name, LPCTSTR Value);
	LPDISPATCH AddRichText(LPCTSTR Name, LPDISPATCH Range);
};
/////////////////////////////////////////////////////////////////////////////
// AutoCorrectEntry wrapper class

class AutoCorrectEntry : public COleDispatchDriver
{
public:
	AutoCorrectEntry() {}		// Calls COleDispatchDriver default constructor
	AutoCorrectEntry(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	AutoCorrectEntry(const AutoCorrectEntry& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetIndex();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	CString GetValue();
	void SetValue(LPCTSTR lpszNewValue);
	BOOL GetRichText();
	void Delete();
	void Apply(LPDISPATCH Range);
};
/////////////////////////////////////////////////////////////////////////////
// FirstLetterExceptions wrapper class

class FirstLetterExceptions : public COleDispatchDriver
{
public:
	FirstLetterExceptions() {}		// Calls COleDispatchDriver default constructor
	FirstLetterExceptions(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	FirstLetterExceptions(const FirstLetterExceptions& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH Item(VARIANT* Index);
	LPDISPATCH Add(LPCTSTR Name);
};
/////////////////////////////////////////////////////////////////////////////
// FirstLetterException wrapper class

class FirstLetterException : public COleDispatchDriver
{
public:
	FirstLetterException() {}		// Calls COleDispatchDriver default constructor
	FirstLetterException(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	FirstLetterException(const FirstLetterException& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetIndex();
	CString GetName();
	void Delete();
};
/////////////////////////////////////////////////////////////////////////////
// TwoInitialCapsExceptions wrapper class

class TwoInitialCapsExceptions : public COleDispatchDriver
{
public:
	TwoInitialCapsExceptions() {}		// Calls COleDispatchDriver default constructor
	TwoInitialCapsExceptions(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	TwoInitialCapsExceptions(const TwoInitialCapsExceptions& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH Item(VARIANT* Index);
	LPDISPATCH Add(LPCTSTR Name);
};
/////////////////////////////////////////////////////////////////////////////
// TwoInitialCapsException wrapper class

class TwoInitialCapsException : public COleDispatchDriver
{
public:
	TwoInitialCapsException() {}		// Calls COleDispatchDriver default constructor
	TwoInitialCapsException(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	TwoInitialCapsException(const TwoInitialCapsException& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetIndex();
	CString GetName();
	void Delete();
};
/////////////////////////////////////////////////////////////////////////////
// Footnotes wrapper class

class Footnotes : public COleDispatchDriver
{
public:
	Footnotes() {}		// Calls COleDispatchDriver default constructor
	Footnotes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Footnotes(const Footnotes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetLocation();
	void SetLocation(long nNewValue);
	long GetNumberStyle();
	void SetNumberStyle(long nNewValue);
	long GetStartingNumber();
	void SetStartingNumber(long nNewValue);
	long GetNumberingRule();
	void SetNumberingRule(long nNewValue);
	LPDISPATCH GetSeparator();
	LPDISPATCH GetContinuationSeparator();
	LPDISPATCH GetContinuationNotice();
	LPDISPATCH Item(long Index);
	LPDISPATCH Add(LPDISPATCH Range, VARIANT* Reference, VARIANT* Text);
	void Convert();
	void SwapWithEndnotes();
	void ResetSeparator();
	void ResetContinuationSeparator();
	void ResetContinuationNotice();
};
/////////////////////////////////////////////////////////////////////////////
// Endnotes wrapper class

class Endnotes : public COleDispatchDriver
{
public:
	Endnotes() {}		// Calls COleDispatchDriver default constructor
	Endnotes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Endnotes(const Endnotes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetLocation();
	void SetLocation(long nNewValue);
	long GetNumberStyle();
	void SetNumberStyle(long nNewValue);
	long GetStartingNumber();
	void SetStartingNumber(long nNewValue);
	long GetNumberingRule();
	void SetNumberingRule(long nNewValue);
	LPDISPATCH GetSeparator();
	LPDISPATCH GetContinuationSeparator();
	LPDISPATCH GetContinuationNotice();
	LPDISPATCH Item(long Index);
	LPDISPATCH Add(LPDISPATCH Range, VARIANT* Reference, VARIANT* Text);
	void Convert();
	void SwapWithFootnotes();
	void ResetSeparator();
	void ResetContinuationSeparator();
	void ResetContinuationNotice();
};
/////////////////////////////////////////////////////////////////////////////
// Comments wrapper class

class Comments : public COleDispatchDriver
{
public:
	Comments() {}		// Calls COleDispatchDriver default constructor
	Comments(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Comments(const Comments& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	CString GetShowBy();
	void SetShowBy(LPCTSTR lpszNewValue);
	LPDISPATCH Item(long Index);
	LPDISPATCH Add(LPDISPATCH Range, VARIANT* Text);
};
/////////////////////////////////////////////////////////////////////////////
// Footnote wrapper class

class Footnote : public COleDispatchDriver
{
public:
	Footnote() {}		// Calls COleDispatchDriver default constructor
	Footnote(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Footnote(const Footnote& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH GetRange();
	LPDISPATCH GetReference();
	long GetIndex();
	void Delete();
};
/////////////////////////////////////////////////////////////////////////////
// Endnote wrapper class

class Endnote : public COleDispatchDriver
{
public:
	Endnote() {}		// Calls COleDispatchDriver default constructor
	Endnote(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Endnote(const Endnote& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH GetRange();
	LPDISPATCH GetReference();
	long GetIndex();
	void Delete();
};
/////////////////////////////////////////////////////////////////////////////
// Comment wrapper class

class Comment : public COleDispatchDriver
{
public:
	Comment() {}		// Calls COleDispatchDriver default constructor
	Comment(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Comment(const Comment& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH GetRange();
	LPDISPATCH GetReference();
	LPDISPATCH GetScope();
	long GetIndex();
	CString GetAuthor();
	void SetAuthor(LPCTSTR lpszNewValue);
	CString GetInitial();
	void SetInitial(LPCTSTR lpszNewValue);
	BOOL GetShowTip();
	void SetShowTip(BOOL bNewValue);
	void Delete();
};
/////////////////////////////////////////////////////////////////////////////
// Borders wrapper class

class Borders : public COleDispatchDriver
{
public:
	Borders() {}		// Calls COleDispatchDriver default constructor
	Borders(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Borders(const Borders& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	long GetEnable();
	void SetEnable(long nNewValue);
	long GetDistanceFromTop();
	void SetDistanceFromTop(long nNewValue);
	BOOL GetShadow();
	void SetShadow(BOOL bNewValue);
	long GetInsideLineStyle();
	void SetInsideLineStyle(long nNewValue);
	long GetOutsideLineStyle();
	void SetOutsideLineStyle(long nNewValue);
	long GetInsideLineWidth();
	void SetInsideLineWidth(long nNewValue);
	long GetOutsideLineWidth();
	void SetOutsideLineWidth(long nNewValue);
	long GetInsideColorIndex();
	void SetInsideColorIndex(long nNewValue);
	long GetOutsideColorIndex();
	void SetOutsideColorIndex(long nNewValue);
	long GetDistanceFromLeft();
	void SetDistanceFromLeft(long nNewValue);
	long GetDistanceFromBottom();
	void SetDistanceFromBottom(long nNewValue);
	long GetDistanceFromRight();
	void SetDistanceFromRight(long nNewValue);
	BOOL GetAlwaysInFront();
	void SetAlwaysInFront(BOOL bNewValue);
	BOOL GetSurroundHeader();
	void SetSurroundHeader(BOOL bNewValue);
	BOOL GetSurroundFooter();
	void SetSurroundFooter(BOOL bNewValue);
	BOOL GetJoinBorders();
	void SetJoinBorders(BOOL bNewValue);
	BOOL GetHasHorizontal();
	BOOL GetHasVertical();
	long GetDistanceFrom();
	void SetDistanceFrom(long nNewValue);
	BOOL GetEnableFirstPageInSection();
	void SetEnableFirstPageInSection(BOOL bNewValue);
	BOOL GetEnableOtherPagesInSection();
	void SetEnableOtherPagesInSection(BOOL bNewValue);
	LPDISPATCH Item(long Index);
	void ApplyPageBordersToAllSections();
};
/////////////////////////////////////////////////////////////////////////////
// Border wrapper class

class Border : public COleDispatchDriver
{
public:
	Border() {}		// Calls COleDispatchDriver default constructor
	Border(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Border(const Border& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	long GetColorIndex();
	void SetColorIndex(long nNewValue);
	BOOL GetInside();
	long GetLineStyle();
	void SetLineStyle(long nNewValue);
	long GetLineWidth();
	void SetLineWidth(long nNewValue);
	long GetArtStyle();
	void SetArtStyle(long nNewValue);
	long GetArtWidth();
	void SetArtWidth(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// Shading wrapper class

class Shading : public COleDispatchDriver
{
public:
	Shading() {}		// Calls COleDispatchDriver default constructor
	Shading(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Shading(const Shading& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetForegroundPatternColorIndex();
	void SetForegroundPatternColorIndex(long nNewValue);
	long GetBackgroundPatternColorIndex();
	void SetBackgroundPatternColorIndex(long nNewValue);
	long GetTexture();
	void SetTexture(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// TextRetrievalMode wrapper class

class TextRetrievalMode : public COleDispatchDriver
{
public:
	TextRetrievalMode() {}		// Calls COleDispatchDriver default constructor
	TextRetrievalMode(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	TextRetrievalMode(const TextRetrievalMode& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetViewType();
	void SetViewType(long nNewValue);
	LPDISPATCH GetDuplicate();
	BOOL GetIncludeHiddenText();
	void SetIncludeHiddenText(BOOL bNewValue);
	BOOL GetIncludeFieldCodes();
	void SetIncludeFieldCodes(BOOL bNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// AutoTextEntries wrapper class

class AutoTextEntries : public COleDispatchDriver
{
public:
	AutoTextEntries() {}		// Calls COleDispatchDriver default constructor
	AutoTextEntries(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	AutoTextEntries(const AutoTextEntries& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH Item(VARIANT* Index);
	LPDISPATCH Add(LPCTSTR Name, LPDISPATCH Range);
	LPDISPATCH AppendToSpike(LPDISPATCH Range);
};
/////////////////////////////////////////////////////////////////////////////
// AutoTextEntry wrapper class

class AutoTextEntry : public COleDispatchDriver
{
public:
	AutoTextEntry() {}		// Calls COleDispatchDriver default constructor
	AutoTextEntry(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	AutoTextEntry(const AutoTextEntry& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetIndex();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	CString GetStyleName();
	CString GetValue();
	void SetValue(LPCTSTR lpszNewValue);
	void Delete();
	LPDISPATCH Insert(LPDISPATCH Where, VARIANT* RichText);
};
/////////////////////////////////////////////////////////////////////////////
// System wrapper class

class System : public COleDispatchDriver
{
public:
	System() {}		// Calls COleDispatchDriver default constructor
	System(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	System(const System& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	CString GetOperatingSystem();
	CString GetProcessorType();
	CString GetVersion();
	long GetFreeDiskSpace();
	long GetCountry();
	CString GetLanguageDesignation();
	long GetHorizontalResolution();
	long GetVerticalResolution();
	CString GetProfileString(LPCTSTR Section, LPCTSTR Key);
	void SetProfileString(LPCTSTR Section, LPCTSTR Key, LPCTSTR lpszNewValue);
	CString GetPrivateProfileString(LPCTSTR FileName, LPCTSTR Section, LPCTSTR Key);
	void SetPrivateProfileString(LPCTSTR FileName, LPCTSTR Section, LPCTSTR Key, LPCTSTR lpszNewValue);
	BOOL GetMathCoprocessorInstalled();
	CString GetComputerType();
	CString GetMacintoshName();
	BOOL GetQuickDrawInstalled();
	long GetCursor();
	void SetCursor(long nNewValue);
	void MSInfo();
	void Connect(LPCTSTR Path, VARIANT* Drive, VARIANT* Password);
};
/////////////////////////////////////////////////////////////////////////////
// OLEFormat wrapper class

class OLEFormat : public COleDispatchDriver
{
public:
	OLEFormat() {}		// Calls COleDispatchDriver default constructor
	OLEFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	OLEFormat(const OLEFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	CString GetClassType();
	void SetClassType(LPCTSTR lpszNewValue);
	BOOL GetDisplayAsIcon();
	void SetDisplayAsIcon(BOOL bNewValue);
	CString GetIconName();
	void SetIconName(LPCTSTR lpszNewValue);
	CString GetIconPath();
	long GetIconIndex();
	void SetIconIndex(long nNewValue);
	CString GetIconLabel();
	void SetIconLabel(LPCTSTR lpszNewValue);
	CString GetLabel();
	LPDISPATCH GetObject();
	CString GetProgID();
	void Activate();
	void Edit();
	void Open();
	void DoVerb(VARIANT* VerbIndex);
	void ConvertTo(VARIANT* ClassType, VARIANT* DisplayAsIcon, VARIANT* IconFileName, VARIANT* IconIndex, VARIANT* IconLabel);
	void ActivateAs(LPCTSTR ClassType);
};
/////////////////////////////////////////////////////////////////////////////
// LinkFormat wrapper class

class LinkFormat : public COleDispatchDriver
{
public:
	LinkFormat() {}		// Calls COleDispatchDriver default constructor
	LinkFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	LinkFormat(const LinkFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	BOOL GetAutoUpdate();
	void SetAutoUpdate(BOOL bNewValue);
	CString GetSourceName();
	CString GetSourcePath();
	BOOL GetLocked();
	void SetLocked(BOOL bNewValue);
	long GetType();
	CString GetSourceFullName();
	void SetSourceFullName(LPCTSTR lpszNewValue);
	BOOL GetSavePictureWithDocument();
	void SetSavePictureWithDocument(BOOL bNewValue);
	void BreakLink();
	void Update();
};
/////////////////////////////////////////////////////////////////////////////
// _OLEControl wrapper class

class _OLEControl : public COleDispatchDriver
{
public:
	_OLEControl() {}		// Calls COleDispatchDriver default constructor
	_OLEControl(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_OLEControl(const _OLEControl& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	float GetLeft();
	void SetLeft(float newValue);
	float GetTop();
	void SetTop(float newValue);
	float GetHeight();
	void SetHeight(float newValue);
	float GetWidth();
	void SetWidth(float newValue);
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	LPDISPATCH GetAutomation();
	void Select();
	void Copy();
	void Cut();
	void Delete();
	void Activate();
};
/////////////////////////////////////////////////////////////////////////////
// Fields wrapper class

class Fields : public COleDispatchDriver
{
public:
	Fields() {}		// Calls COleDispatchDriver default constructor
	Fields(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Fields(const Fields& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetCount();
	long GetLocked();
	void SetLocked(long nNewValue);
	LPUNKNOWN Get_NewEnum();
	LPDISPATCH Item(long Index);
	void ToggleShowCodes();
	long Update();
	void Unlink();
	void UpdateSource();
	LPDISPATCH Add(LPDISPATCH Range, VARIANT* Type, VARIANT* Text, VARIANT* PreserveFormatting);
};
/////////////////////////////////////////////////////////////////////////////
// Field wrapper class

class Field : public COleDispatchDriver
{
public:
	Field() {}		// Calls COleDispatchDriver default constructor
	Field(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Field(const Field& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH GetCode();
	void SetCode(LPDISPATCH newValue);
	long GetType();
	BOOL GetLocked();
	void SetLocked(BOOL bNewValue);
	long GetKind();
	LPDISPATCH GetResult();
	void SetResult(LPDISPATCH newValue);
	CString GetData();
	void SetData(LPCTSTR lpszNewValue);
	LPDISPATCH GetNext();
	LPDISPATCH GetPrevious();
	long GetIndex();
	BOOL GetShowCodes();
	void SetShowCodes(BOOL bNewValue);
	LPDISPATCH GetLinkFormat();
	LPDISPATCH GetOLEFormat();
	LPDISPATCH GetInlineShape();
	void Select();
	BOOL Update();
	void Unlink();
	void UpdateSource();
	void DoClick();
	void Copy();
	void Cut();
	void Delete();
};
/////////////////////////////////////////////////////////////////////////////
// Browser wrapper class

class Browser : public COleDispatchDriver
{
public:
	Browser() {}		// Calls COleDispatchDriver default constructor
	Browser(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Browser(const Browser& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetTarget();
	void SetTarget(long nNewValue);
	void Next();
	void Previous();
};
/////////////////////////////////////////////////////////////////////////////
// Styles wrapper class

class Styles : public COleDispatchDriver
{
public:
	Styles() {}		// Calls COleDispatchDriver default constructor
	Styles(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Styles(const Styles& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH Item(VARIANT* Index);
	LPDISPATCH Add(LPCTSTR Name, VARIANT* Type);
};
/////////////////////////////////////////////////////////////////////////////
// Style wrapper class

class Style : public COleDispatchDriver
{
public:
	Style() {}		// Calls COleDispatchDriver default constructor
	Style(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Style(const Style& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	CString GetNameLocal();
	void SetNameLocal(LPCTSTR lpszNewValue);
	VARIANT GetBaseStyle();
	void SetBaseStyle(VARIANT* newValue);
	CString GetDescription();
	long GetType();
	BOOL GetBuiltIn();
	VARIANT GetNextParagraphStyle();
	void SetNextParagraphStyle(VARIANT* newValue);
	BOOL GetInUse();
	LPDISPATCH GetShading();
	LPDISPATCH GetBorders();
	void SetBorders(LPDISPATCH newValue);
	LPDISPATCH GetParagraphFormat();
	void SetParagraphFormat(LPDISPATCH newValue);
	LPDISPATCH GetFont();
	void SetFont(LPDISPATCH newValue);
	LPDISPATCH GetFrame();
	long GetLanguageID();
	void SetLanguageID(long nNewValue);
	BOOL GetAutomaticallyUpdate();
	void SetAutomaticallyUpdate(BOOL bNewValue);
	LPDISPATCH GetListTemplate();
	long GetListLevelNumber();
	long GetLanguageIDFarEast();
	void SetLanguageIDFarEast(long nNewValue);
	void Delete();
	void LinkToListTemplate(LPDISPATCH ListTemplate, VARIANT* ListLevelNumber);
};
/////////////////////////////////////////////////////////////////////////////
// Frames wrapper class

class Frames : public COleDispatchDriver
{
public:
	Frames() {}		// Calls COleDispatchDriver default constructor
	Frames(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Frames(const Frames& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH Item(long Index);
	LPDISPATCH Add(LPDISPATCH Range);
	void Delete();
};
/////////////////////////////////////////////////////////////////////////////
// Frame wrapper class

class Frame : public COleDispatchDriver
{
public:
	Frame() {}		// Calls COleDispatchDriver default constructor
	Frame(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Frame(const Frame& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetHeightRule();
	void SetHeightRule(long nNewValue);
	long GetWidthRule();
	void SetWidthRule(long nNewValue);
	float GetHorizontalDistanceFromText();
	void SetHorizontalDistanceFromText(float newValue);
	float GetHeight();
	void SetHeight(float newValue);
	float GetHorizontalPosition();
	void SetHorizontalPosition(float newValue);
	BOOL GetLockAnchor();
	void SetLockAnchor(BOOL bNewValue);
	long GetRelativeHorizontalPosition();
	void SetRelativeHorizontalPosition(long nNewValue);
	long GetRelativeVerticalPosition();
	void SetRelativeVerticalPosition(long nNewValue);
	float GetVerticalDistanceFromText();
	void SetVerticalDistanceFromText(float newValue);
	float GetVerticalPosition();
	void SetVerticalPosition(float newValue);
	float GetWidth();
	void SetWidth(float newValue);
	BOOL GetTextWrap();
	void SetTextWrap(BOOL bNewValue);
	LPDISPATCH GetShading();
	LPDISPATCH GetBorders();
	void SetBorders(LPDISPATCH newValue);
	LPDISPATCH GetRange();
	void Delete();
	void Select();
	void Copy();
	void Cut();
};
/////////////////////////////////////////////////////////////////////////////
// FormFields wrapper class

class FormFields : public COleDispatchDriver
{
public:
	FormFields() {}		// Calls COleDispatchDriver default constructor
	FormFields(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	FormFields(const FormFields& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetCount();
	BOOL GetShaded();
	void SetShaded(BOOL bNewValue);
	LPUNKNOWN Get_NewEnum();
	LPDISPATCH Item(VARIANT* Index);
	LPDISPATCH Add(LPDISPATCH Range, long Type);
};
/////////////////////////////////////////////////////////////////////////////
// FormField wrapper class

class FormField : public COleDispatchDriver
{
public:
	FormField() {}		// Calls COleDispatchDriver default constructor
	FormField(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	FormField(const FormField& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetType();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	CString GetEntryMacro();
	void SetEntryMacro(LPCTSTR lpszNewValue);
	CString GetExitMacro();
	void SetExitMacro(LPCTSTR lpszNewValue);
	BOOL GetOwnHelp();
	void SetOwnHelp(BOOL bNewValue);
	BOOL GetOwnStatus();
	void SetOwnStatus(BOOL bNewValue);
	CString GetHelpText();
	void SetHelpText(LPCTSTR lpszNewValue);
	CString GetStatusText();
	void SetStatusText(LPCTSTR lpszNewValue);
	BOOL GetEnabled();
	void SetEnabled(BOOL bNewValue);
	CString GetResult();
	void SetResult(LPCTSTR lpszNewValue);
	LPDISPATCH GetTextInput();
	LPDISPATCH GetCheckBox();
	LPDISPATCH GetDropDown();
	LPDISPATCH GetNext();
	LPDISPATCH GetPrevious();
	BOOL GetCalculateOnExit();
	void SetCalculateOnExit(BOOL bNewValue);
	LPDISPATCH GetRange();
	void Select();
	void Copy();
	void Cut();
	void Delete();
};
/////////////////////////////////////////////////////////////////////////////
// TextInput wrapper class

class TextInput : public COleDispatchDriver
{
public:
	TextInput() {}		// Calls COleDispatchDriver default constructor
	TextInput(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	TextInput(const TextInput& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	BOOL GetValid();
	CString GetDefault();
	void SetDefault(LPCTSTR lpszNewValue);
	long GetType();
	CString GetFormat();
	long GetWidth();
	void SetWidth(long nNewValue);
	void Clear();
	void EditType(long Type, VARIANT* Default, VARIANT* Format, VARIANT* Enabled);
};
/////////////////////////////////////////////////////////////////////////////
// CheckBox wrapper class

class CheckBox : public COleDispatchDriver
{
public:
	CheckBox() {}		// Calls COleDispatchDriver default constructor
	CheckBox(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CheckBox(const CheckBox& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	BOOL GetValid();
	BOOL GetAutoSize();
	void SetAutoSize(BOOL bNewValue);
	float GetSize();
	void SetSize(float newValue);
	BOOL GetDefault();
	void SetDefault(BOOL bNewValue);
	BOOL GetValue();
	void SetValue(BOOL bNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// DropDown wrapper class

class DropDown : public COleDispatchDriver
{
public:
	DropDown() {}		// Calls COleDispatchDriver default constructor
	DropDown(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DropDown(const DropDown& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	BOOL GetValid();
	long GetDefault();
	void SetDefault(long nNewValue);
	long GetValue();
	void SetValue(long nNewValue);
	LPDISPATCH GetListEntries();
};
/////////////////////////////////////////////////////////////////////////////
// ListEntries wrapper class

class ListEntries : public COleDispatchDriver
{
public:
	ListEntries() {}		// Calls COleDispatchDriver default constructor
	ListEntries(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ListEntries(const ListEntries& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH Item(VARIANT* Index);
	LPDISPATCH Add(LPCTSTR Name, VARIANT* Index);
	void Clear();
};
/////////////////////////////////////////////////////////////////////////////
// ListEntry wrapper class

class ListEntry : public COleDispatchDriver
{
public:
	ListEntry() {}		// Calls COleDispatchDriver default constructor
	ListEntry(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ListEntry(const ListEntry& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetIndex();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	void Delete();
};
/////////////////////////////////////////////////////////////////////////////
// TablesOfFigures wrapper class

class TablesOfFigures : public COleDispatchDriver
{
public:
	TablesOfFigures() {}		// Calls COleDispatchDriver default constructor
	TablesOfFigures(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	TablesOfFigures(const TablesOfFigures& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	long GetFormat();
	void SetFormat(long nNewValue);
	LPDISPATCH Item(long Index);
	LPDISPATCH Add(LPDISPATCH Range, VARIANT* Caption, VARIANT* IncludeLabel, VARIANT* UseHeadingStyles, VARIANT* UpperHeadingLevel, VARIANT* LowerHeadingLevel, VARIANT* UseFields, VARIANT* TableID, VARIANT* RightAlignPageNumbers, 
		VARIANT* IncludePageNumbers, VARIANT* AddedStyles);
	LPDISPATCH MarkEntry(LPDISPATCH Range, VARIANT* Entry, VARIANT* EntryAutoText, VARIANT* TableID, VARIANT* Level);
};
/////////////////////////////////////////////////////////////////////////////
// TableOfFigures wrapper class

class TableOfFigures : public COleDispatchDriver
{
public:
	TableOfFigures() {}		// Calls COleDispatchDriver default constructor
	TableOfFigures(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	TableOfFigures(const TableOfFigures& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	CString GetCaption();
	void SetCaption(LPCTSTR lpszNewValue);
	BOOL GetIncludeLabel();
	void SetIncludeLabel(BOOL bNewValue);
	BOOL GetRightAlignPageNumbers();
	void SetRightAlignPageNumbers(BOOL bNewValue);
	BOOL GetUseHeadingStyles();
	void SetUseHeadingStyles(BOOL bNewValue);
	long GetLowerHeadingLevel();
	void SetLowerHeadingLevel(long nNewValue);
	long GetUpperHeadingLevel();
	void SetUpperHeadingLevel(long nNewValue);
	BOOL GetIncludePageNumbers();
	void SetIncludePageNumbers(BOOL bNewValue);
	LPDISPATCH GetRange();
	BOOL GetUseFields();
	void SetUseFields(BOOL bNewValue);
	CString GetTableID();
	void SetTableID(LPCTSTR lpszNewValue);
	LPDISPATCH GetHeadingStyles();
	long GetTabLeader();
	void SetTabLeader(long nNewValue);
	void Delete();
	void UpdatePageNumbers();
	void Update();
};
/////////////////////////////////////////////////////////////////////////////
// MailMerge wrapper class

class MailMerge : public COleDispatchDriver
{
public:
	MailMerge() {}		// Calls COleDispatchDriver default constructor
	MailMerge(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	MailMerge(const MailMerge& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetMainDocumentType();
	void SetMainDocumentType(long nNewValue);
	long GetState();
	long GetDestination();
	void SetDestination(long nNewValue);
	LPDISPATCH GetDataSource();
	LPDISPATCH GetFields();
	long GetViewMailMergeFieldCodes();
	void SetViewMailMergeFieldCodes(long nNewValue);
	BOOL GetSuppressBlankLines();
	void SetSuppressBlankLines(BOOL bNewValue);
	BOOL GetMailAsAttachment();
	void SetMailAsAttachment(BOOL bNewValue);
	CString GetMailAddressFieldName();
	void SetMailAddressFieldName(LPCTSTR lpszNewValue);
	CString GetMailSubject();
	void SetMailSubject(LPCTSTR lpszNewValue);
	void CreateDataSource(VARIANT* Name, VARIANT* PasswordDocument, VARIANT* WritePasswordDocument, VARIANT* HeaderRecord, VARIANT* MSQuery, VARIANT* SQLStatement, VARIANT* SQLStatement1, VARIANT* Connection, VARIANT* LinkToSource);
	void CreateHeaderSource(LPCTSTR Name, VARIANT* PasswordDocument, VARIANT* WritePasswordDocument, VARIANT* HeaderRecord);
	void OpenDataSource(LPCTSTR Name, VARIANT* Format, VARIANT* ConfirmConversions, VARIANT* ReadOnly, VARIANT* LinkToSource, VARIANT* AddToRecentFiles, VARIANT* PasswordDocument, VARIANT* PasswordTemplate, VARIANT* Revert, 
		VARIANT* WritePasswordDocument, VARIANT* WritePasswordTemplate, VARIANT* Connection, VARIANT* SQLStatement, VARIANT* SQLStatement1);
	void OpenHeaderSource(LPCTSTR Name, VARIANT* Format, VARIANT* ConfirmConversions, VARIANT* ReadOnly, VARIANT* AddToRecentFiles, VARIANT* PasswordDocument, VARIANT* PasswordTemplate, VARIANT* Revert, VARIANT* WritePasswordDocument, 
		VARIANT* WritePasswordTemplate);
	void Execute(VARIANT* Pause);
	void Check();
	void EditDataSource();
	void EditHeaderSource();
	void EditMainDocument();
	void UseAddressBook(LPCTSTR Type);
};
/////////////////////////////////////////////////////////////////////////////
// MailMergeFields wrapper class

class MailMergeFields : public COleDispatchDriver
{
public:
	MailMergeFields() {}		// Calls COleDispatchDriver default constructor
	MailMergeFields(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	MailMergeFields(const MailMergeFields& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH Item(long Index);
	LPDISPATCH Add(LPDISPATCH Range, LPCTSTR Name);
	LPDISPATCH AddAsk(LPDISPATCH Range, LPCTSTR Name, VARIANT* Prompt, VARIANT* DefaultAskText, VARIANT* AskOnce);
	LPDISPATCH AddFillIn(LPDISPATCH Range, VARIANT* Prompt, VARIANT* DefaultFillInText, VARIANT* AskOnce);
	LPDISPATCH AddIf(LPDISPATCH Range, LPCTSTR MergeField, long Comparison, VARIANT* CompareTo, VARIANT* TrueAutoText, VARIANT* TrueText, VARIANT* FalseAutoText, VARIANT* FalseText);
	LPDISPATCH AddMergeRec(LPDISPATCH Range);
	LPDISPATCH AddMergeSeq(LPDISPATCH Range);
	LPDISPATCH AddNext(LPDISPATCH Range);
	LPDISPATCH AddNextIf(LPDISPATCH Range, LPCTSTR MergeField, long Comparison, VARIANT* CompareTo);
	LPDISPATCH AddSet(LPDISPATCH Range, LPCTSTR Name, VARIANT* ValueText, VARIANT* ValueAutoText);
	LPDISPATCH AddSkipIf(LPDISPATCH Range, LPCTSTR MergeField, long Comparison, VARIANT* CompareTo);
};
/////////////////////////////////////////////////////////////////////////////
// MailMergeField wrapper class

class MailMergeField : public COleDispatchDriver
{
public:
	MailMergeField() {}		// Calls COleDispatchDriver default constructor
	MailMergeField(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	MailMergeField(const MailMergeField& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetType();
	BOOL GetLocked();
	void SetLocked(BOOL bNewValue);
	LPDISPATCH GetCode();
	void SetCode(LPDISPATCH newValue);
	LPDISPATCH GetNext();
	LPDISPATCH GetPrevious();
	void Select();
	void Copy();
	void Cut();
	void Delete();
};
/////////////////////////////////////////////////////////////////////////////
// MailMergeDataSource wrapper class

class MailMergeDataSource : public COleDispatchDriver
{
public:
	MailMergeDataSource() {}		// Calls COleDispatchDriver default constructor
	MailMergeDataSource(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	MailMergeDataSource(const MailMergeDataSource& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	CString GetName();
	CString GetHeaderSourceName();
	long GetType();
	long GetHeaderSourceType();
	CString GetConnectString();
	CString GetQueryString();
	void SetQueryString(LPCTSTR lpszNewValue);
	long GetActiveRecord();
	void SetActiveRecord(long nNewValue);
	long GetFirstRecord();
	void SetFirstRecord(long nNewValue);
	long GetLastRecord();
	void SetLastRecord(long nNewValue);
	LPDISPATCH GetFieldNames();
	LPDISPATCH GetDataFields();
	BOOL FindRecord(LPCTSTR FindText, LPCTSTR Field);
};
/////////////////////////////////////////////////////////////////////////////
// MailMergeFieldNames wrapper class

class MailMergeFieldNames : public COleDispatchDriver
{
public:
	MailMergeFieldNames() {}		// Calls COleDispatchDriver default constructor
	MailMergeFieldNames(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	MailMergeFieldNames(const MailMergeFieldNames& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH Item(VARIANT* Index);
};
/////////////////////////////////////////////////////////////////////////////
// MailMergeFieldName wrapper class

class MailMergeFieldName : public COleDispatchDriver
{
public:
	MailMergeFieldName() {}		// Calls COleDispatchDriver default constructor
	MailMergeFieldName(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	MailMergeFieldName(const MailMergeFieldName& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	CString GetName();
	long GetIndex();
};
/////////////////////////////////////////////////////////////////////////////
// MailMergeDataFields wrapper class

class MailMergeDataFields : public COleDispatchDriver
{
public:
	MailMergeDataFields() {}		// Calls COleDispatchDriver default constructor
	MailMergeDataFields(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	MailMergeDataFields(const MailMergeDataFields& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH Item(VARIANT* Index);
};
/////////////////////////////////////////////////////////////////////////////
// MailMergeDataField wrapper class

class MailMergeDataField : public COleDispatchDriver
{
public:
	MailMergeDataField() {}		// Calls COleDispatchDriver default constructor
	MailMergeDataField(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	MailMergeDataField(const MailMergeDataField& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	CString GetValue();
	CString GetName();
	long GetIndex();
};
/////////////////////////////////////////////////////////////////////////////
// Envelope wrapper class

class Envelope : public COleDispatchDriver
{
public:
	Envelope() {}		// Calls COleDispatchDriver default constructor
	Envelope(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Envelope(const Envelope& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH GetAddress();
	LPDISPATCH GetReturnAddress();
	BOOL GetDefaultPrintBarCode();
	void SetDefaultPrintBarCode(BOOL bNewValue);
	BOOL GetDefaultPrintFIMA();
	void SetDefaultPrintFIMA(BOOL bNewValue);
	float GetDefaultHeight();
	void SetDefaultHeight(float newValue);
	float GetDefaultWidth();
	void SetDefaultWidth(float newValue);
	CString GetDefaultSize();
	void SetDefaultSize(LPCTSTR lpszNewValue);
	BOOL GetDefaultOmitReturnAddress();
	void SetDefaultOmitReturnAddress(BOOL bNewValue);
	long GetFeedSource();
	void SetFeedSource(long nNewValue);
	float GetAddressFromLeft();
	void SetAddressFromLeft(float newValue);
	float GetAddressFromTop();
	void SetAddressFromTop(float newValue);
	float GetReturnAddressFromLeft();
	void SetReturnAddressFromLeft(float newValue);
	float GetReturnAddressFromTop();
	void SetReturnAddressFromTop(float newValue);
	LPDISPATCH GetAddressStyle();
	LPDISPATCH GetReturnAddressStyle();
	long GetDefaultOrientation();
	void SetDefaultOrientation(long nNewValue);
	BOOL GetDefaultFaceUp();
	void SetDefaultFaceUp(BOOL bNewValue);
	void Insert(VARIANT* ExtractAddress, VARIANT* Address, VARIANT* AutoText, VARIANT* OmitReturnAddress, VARIANT* ReturnAddress, VARIANT* ReturnAutoText, VARIANT* PrintBarCode, VARIANT* PrintFIMA, VARIANT* Size, VARIANT* Height, VARIANT* Width, 
		VARIANT* FeedSource, VARIANT* AddressFromLeft, VARIANT* AddressFromTop, VARIANT* ReturnAddressFromLeft, VARIANT* ReturnAddressFromTop, VARIANT* DefaultFaceUp, VARIANT* DefaultOrientation);
	void PrintOut(VARIANT* ExtractAddress, VARIANT* Address, VARIANT* AutoText, VARIANT* OmitReturnAddress, VARIANT* ReturnAddress, VARIANT* ReturnAutoText, VARIANT* PrintBarCode, VARIANT* PrintFIMA, VARIANT* Size, VARIANT* Height, 
		VARIANT* Width, VARIANT* FeedSource, VARIANT* AddressFromLeft, VARIANT* AddressFromTop, VARIANT* ReturnAddressFromLeft, VARIANT* ReturnAddressFromTop, VARIANT* DefaultFaceUp, VARIANT* DefaultOrientation);
	void UpdateDocument();
};
/////////////////////////////////////////////////////////////////////////////
// MailingLabel wrapper class

class MailingLabel : public COleDispatchDriver
{
public:
	MailingLabel() {}		// Calls COleDispatchDriver default constructor
	MailingLabel(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	MailingLabel(const MailingLabel& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	BOOL GetDefaultPrintBarCode();
	void SetDefaultPrintBarCode(BOOL bNewValue);
	long GetDefaultLaserTray();
	void SetDefaultLaserTray(long nNewValue);
	LPDISPATCH GetCustomLabels();
	CString GetDefaultLabelName();
	void SetDefaultLabelName(LPCTSTR lpszNewValue);
	LPDISPATCH CreateNewDocument(VARIANT* Name, VARIANT* Address, VARIANT* AutoText, VARIANT* ExtractAddress, VARIANT* LaserTray);
	void PrintOut(VARIANT* Name, VARIANT* Address, VARIANT* ExtractAddress, VARIANT* LaserTray, VARIANT* SingleLabel, VARIANT* Row, VARIANT* Column);
};
/////////////////////////////////////////////////////////////////////////////
// CustomLabels wrapper class

class CustomLabels : public COleDispatchDriver
{
public:
	CustomLabels() {}		// Calls COleDispatchDriver default constructor
	CustomLabels(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CustomLabels(const CustomLabels& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH Item(VARIANT* Index);
	LPDISPATCH Add(LPCTSTR Name, VARIANT* DotMatrix);
};
/////////////////////////////////////////////////////////////////////////////
// CustomLabel wrapper class

class CustomLabel : public COleDispatchDriver
{
public:
	CustomLabel() {}		// Calls COleDispatchDriver default constructor
	CustomLabel(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CustomLabel(const CustomLabel& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetIndex();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	float GetTopMargin();
	void SetTopMargin(float newValue);
	float GetSideMargin();
	void SetSideMargin(float newValue);
	float GetHeight();
	void SetHeight(float newValue);
	float GetWidth();
	void SetWidth(float newValue);
	float GetVerticalPitch();
	void SetVerticalPitch(float newValue);
	float GetHorizontalPitch();
	void SetHorizontalPitch(float newValue);
	long GetNumberAcross();
	void SetNumberAcross(long nNewValue);
	long GetNumberDown();
	void SetNumberDown(long nNewValue);
	BOOL GetDotMatrix();
	long GetPageSize();
	void SetPageSize(long nNewValue);
	BOOL GetValid();
	void Delete();
};
/////////////////////////////////////////////////////////////////////////////
// TablesOfContents wrapper class

class TablesOfContents : public COleDispatchDriver
{
public:
	TablesOfContents() {}		// Calls COleDispatchDriver default constructor
	TablesOfContents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	TablesOfContents(const TablesOfContents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	long GetFormat();
	void SetFormat(long nNewValue);
	LPDISPATCH Item(long Index);
	LPDISPATCH Add(LPDISPATCH Range, VARIANT* UseHeadingStyles, VARIANT* UpperHeadingLevel, VARIANT* LowerHeadingLevel, VARIANT* UseFields, VARIANT* TableID, VARIANT* RightAlignPageNumbers, VARIANT* IncludePageNumbers, VARIANT* AddedStyles);
	LPDISPATCH MarkEntry(LPDISPATCH Range, VARIANT* Entry, VARIANT* EntryAutoText, VARIANT* TableID, VARIANT* Level);
};
/////////////////////////////////////////////////////////////////////////////
// TableOfContents wrapper class

class TableOfContents : public COleDispatchDriver
{
public:
	TableOfContents() {}		// Calls COleDispatchDriver default constructor
	TableOfContents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	TableOfContents(const TableOfContents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	BOOL GetUseHeadingStyles();
	void SetUseHeadingStyles(BOOL bNewValue);
	BOOL GetUseFields();
	void SetUseFields(BOOL bNewValue);
	long GetUpperHeadingLevel();
	void SetUpperHeadingLevel(long nNewValue);
	long GetLowerHeadingLevel();
	void SetLowerHeadingLevel(long nNewValue);
	CString GetTableID();
	void SetTableID(LPCTSTR lpszNewValue);
	LPDISPATCH GetHeadingStyles();
	BOOL GetRightAlignPageNumbers();
	void SetRightAlignPageNumbers(BOOL bNewValue);
	BOOL GetIncludePageNumbers();
	void SetIncludePageNumbers(BOOL bNewValue);
	LPDISPATCH GetRange();
	long GetTabLeader();
	void SetTabLeader(long nNewValue);
	void Delete();
	void UpdatePageNumbers();
	void Update();
};
/////////////////////////////////////////////////////////////////////////////
// TablesOfAuthorities wrapper class

class TablesOfAuthorities : public COleDispatchDriver
{
public:
	TablesOfAuthorities() {}		// Calls COleDispatchDriver default constructor
	TablesOfAuthorities(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	TablesOfAuthorities(const TablesOfAuthorities& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	long GetFormat();
	void SetFormat(long nNewValue);
	LPDISPATCH Item(long Index);
	LPDISPATCH Add(LPDISPATCH Range, VARIANT* Category, VARIANT* Bookmark, VARIANT* Passim, VARIANT* KeepEntryFormatting, VARIANT* Separator, VARIANT* IncludeSequenceName, VARIANT* EntrySeparator, VARIANT* PageRangeSeparator, 
		VARIANT* IncludeCategoryHeader, VARIANT* PageNumberSeparator);
	void NextCitation(LPCTSTR ShortCitation);
	LPDISPATCH MarkCitation(LPDISPATCH Range, LPCTSTR ShortCitation, VARIANT* LongCitation, VARIANT* LongCitationAutoText, VARIANT* Category);
	void MarkAllCitations(LPCTSTR ShortCitation, VARIANT* LongCitation, VARIANT* LongCitationAutoText, VARIANT* Category);
};
/////////////////////////////////////////////////////////////////////////////
// TableOfAuthorities wrapper class

class TableOfAuthorities : public COleDispatchDriver
{
public:
	TableOfAuthorities() {}		// Calls COleDispatchDriver default constructor
	TableOfAuthorities(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	TableOfAuthorities(const TableOfAuthorities& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	BOOL GetPassim();
	void SetPassim(BOOL bNewValue);
	BOOL GetKeepEntryFormatting();
	void SetKeepEntryFormatting(BOOL bNewValue);
	long GetCategory();
	void SetCategory(long nNewValue);
	CString GetBookmark();
	void SetBookmark(LPCTSTR lpszNewValue);
	CString GetSeparator();
	void SetSeparator(LPCTSTR lpszNewValue);
	CString GetIncludeSequenceName();
	void SetIncludeSequenceName(LPCTSTR lpszNewValue);
	CString GetEntrySeparator();
	void SetEntrySeparator(LPCTSTR lpszNewValue);
	CString GetPageRangeSeparator();
	void SetPageRangeSeparator(LPCTSTR lpszNewValue);
	BOOL GetIncludeCategoryHeader();
	void SetIncludeCategoryHeader(BOOL bNewValue);
	CString GetPageNumberSeparator();
	void SetPageNumberSeparator(LPCTSTR lpszNewValue);
	LPDISPATCH GetRange();
	long GetTabLeader();
	void SetTabLeader(long nNewValue);
	void Delete();
	void Update();
};
/////////////////////////////////////////////////////////////////////////////
// Dialogs wrapper class

class Dialogs : public COleDispatchDriver
{
public:
	Dialogs() {}		// Calls COleDispatchDriver default constructor
	Dialogs(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Dialogs(const Dialogs& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH Item(long Index);
};
/////////////////////////////////////////////////////////////////////////////
// Dialog wrapper class

class Dialog : public COleDispatchDriver
{
public:
	Dialog() {}		// Calls COleDispatchDriver default constructor
	Dialog(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Dialog(const Dialog& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetDefaultTab();
	void SetDefaultTab(long nNewValue);
	long GetType();
	long Show(VARIANT* TimeOut);
	long Display(VARIANT* TimeOut);
	void Execute();
	void Update();
};
/////////////////////////////////////////////////////////////////////////////
// PageSetup wrapper class

class PageSetup : public COleDispatchDriver
{
public:
	PageSetup() {}		// Calls COleDispatchDriver default constructor
	PageSetup(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PageSetup(const PageSetup& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	float GetTopMargin();
	void SetTopMargin(float newValue);
	float GetBottomMargin();
	void SetBottomMargin(float newValue);
	float GetLeftMargin();
	void SetLeftMargin(float newValue);
	float GetRightMargin();
	void SetRightMargin(float newValue);
	float GetGutter();
	void SetGutter(float newValue);
	float GetPageWidth();
	void SetPageWidth(float newValue);
	float GetPageHeight();
	void SetPageHeight(float newValue);
	long GetOrientation();
	void SetOrientation(long nNewValue);
	long GetFirstPageTray();
	void SetFirstPageTray(long nNewValue);
	long GetOtherPagesTray();
	void SetOtherPagesTray(long nNewValue);
	long GetVerticalAlignment();
	void SetVerticalAlignment(long nNewValue);
	long GetMirrorMargins();
	void SetMirrorMargins(long nNewValue);
	float GetHeaderDistance();
	void SetHeaderDistance(float newValue);
	float GetFooterDistance();
	void SetFooterDistance(float newValue);
	long GetSectionStart();
	void SetSectionStart(long nNewValue);
	long GetOddAndEvenPagesHeaderFooter();
	void SetOddAndEvenPagesHeaderFooter(long nNewValue);
	long GetDifferentFirstPageHeaderFooter();
	void SetDifferentFirstPageHeaderFooter(long nNewValue);
	long GetSuppressEndnotes();
	void SetSuppressEndnotes(long nNewValue);
	LPDISPATCH GetLineNumbering();
	void SetLineNumbering(LPDISPATCH newValue);
	LPDISPATCH GetTextColumns();
	void SetTextColumns(LPDISPATCH newValue);
	long GetPaperSize();
	void SetPaperSize(long nNewValue);
	void TogglePortrait();
	void SetAsTemplateDefault();
};
/////////////////////////////////////////////////////////////////////////////
// LineNumbering wrapper class

class LineNumbering : public COleDispatchDriver
{
public:
	LineNumbering() {}		// Calls COleDispatchDriver default constructor
	LineNumbering(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	LineNumbering(const LineNumbering& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetRestartMode();
	void SetRestartMode(long nNewValue);
	long GetStartingNumber();
	void SetStartingNumber(long nNewValue);
	float GetDistanceFromText();
	void SetDistanceFromText(float newValue);
	long GetCountBy();
	void SetCountBy(long nNewValue);
	long GetActive();
	void SetActive(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// TextColumns wrapper class

class TextColumns : public COleDispatchDriver
{
public:
	TextColumns() {}		// Calls COleDispatchDriver default constructor
	TextColumns(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	TextColumns(const TextColumns& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetEvenlySpaced();
	void SetEvenlySpaced(long nNewValue);
	long GetLineBetween();
	void SetLineBetween(long nNewValue);
	float GetWidth();
	void SetWidth(float newValue);
	float GetSpacing();
	void SetSpacing(float newValue);
	LPDISPATCH Item(long Index);
	LPDISPATCH Add(VARIANT* Width, VARIANT* Spacing, VARIANT* EvenlySpaced);
	void SetCount(long NumColumns);
};
/////////////////////////////////////////////////////////////////////////////
// TextColumn wrapper class

class TextColumn : public COleDispatchDriver
{
public:
	TextColumn() {}		// Calls COleDispatchDriver default constructor
	TextColumn(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	TextColumn(const TextColumn& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	float GetWidth();
	void SetWidth(float newValue);
	float GetSpaceAfter();
	void SetSpaceAfter(float newValue);
};
/////////////////////////////////////////////////////////////////////////////
// Selection wrapper class

class Selection : public COleDispatchDriver
{
public:
	Selection() {}		// Calls COleDispatchDriver default constructor
	Selection(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Selection(const Selection& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	LPDISPATCH GetFormattedText();
	void SetFormattedText(LPDISPATCH newValue);
	long GetStart();
	void SetStart(long nNewValue);
	long GetEnd();
	void SetEnd(long nNewValue);
	LPDISPATCH GetFont();
	void SetFont(LPDISPATCH newValue);
	long GetType();
	long GetStoryType();
	VARIANT GetStyle();
	void SetStyle(VARIANT* newValue);
	LPDISPATCH GetTables();
	LPDISPATCH GetWords();
	LPDISPATCH GetSentences();
	LPDISPATCH GetCharacters();
	LPDISPATCH GetFootnotes();
	LPDISPATCH GetEndnotes();
	LPDISPATCH GetComments();
	LPDISPATCH GetCells();
	LPDISPATCH GetSections();
	LPDISPATCH GetParagraphs();
	LPDISPATCH GetBorders();
	void SetBorders(LPDISPATCH newValue);
	LPDISPATCH GetShading();
	LPDISPATCH GetFields();
	LPDISPATCH GetFormFields();
	LPDISPATCH GetFrames();
	LPDISPATCH GetParagraphFormat();
	void SetParagraphFormat(LPDISPATCH newValue);
	LPDISPATCH GetPageSetup();
	void SetPageSetup(LPDISPATCH newValue);
	LPDISPATCH GetBookmarks();
	long GetStoryLength();
	long GetLanguageID();
	void SetLanguageID(long nNewValue);
	long GetLanguageIDFarEast();
	void SetLanguageIDFarEast(long nNewValue);
	long GetLanguageIDOther();
	void SetLanguageIDOther(long nNewValue);
	LPDISPATCH GetHyperlinks();
	LPDISPATCH GetColumns();
	LPDISPATCH GetRows();
	LPDISPATCH GetHeaderFooter();
	BOOL GetIsEndOfRowMark();
	long GetBookmarkID();
	long GetPreviousBookmarkID();
	LPDISPATCH GetFind();
	LPDISPATCH GetRange();
	VARIANT GetInformation(long Type);
	long GetFlags();
	void SetFlags(long nNewValue);
	BOOL GetActive();
	BOOL GetStartIsActive();
	void SetStartIsActive(BOOL bNewValue);
	BOOL GetIPAtEndOfLine();
	BOOL GetExtendMode();
	void SetExtendMode(BOOL bNewValue);
	BOOL GetColumnSelectMode();
	void SetColumnSelectMode(BOOL bNewValue);
	long GetOrientation();
	void SetOrientation(long nNewValue);
	LPDISPATCH GetInlineShapes();
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH GetDocument();
	LPDISPATCH GetShapeRange();
	void Select();
	void SetRange(long Start, long End);
	void Collapse(VARIANT* Direction);
	void InsertBefore(LPCTSTR Text);
	void InsertAfter(LPCTSTR Text);
	LPDISPATCH Next(VARIANT* Unit, VARIANT* Count);
	LPDISPATCH Previous(VARIANT* Unit, VARIANT* Count);
	long StartOf(VARIANT* Unit, VARIANT* Extend);
	long EndOf(VARIANT* Unit, VARIANT* Extend);
	long Move(VARIANT* Unit, VARIANT* Count);
	long MoveStart(VARIANT* Unit, VARIANT* Count);
	long MoveEnd(VARIANT* Unit, VARIANT* Count);
	long MoveWhile(VARIANT* Cset, VARIANT* Count);
	long MoveStartWhile(VARIANT* Cset, VARIANT* Count);
	long MoveEndWhile(VARIANT* Cset, VARIANT* Count);
	long MoveUntil(VARIANT* Cset, VARIANT* Count);
	long MoveStartUntil(VARIANT* Cset, VARIANT* Count);
	long MoveEndUntil(VARIANT* Cset, VARIANT* Count);
	void Cut();
	void Copy();
	void Paste();
	void InsertBreak(VARIANT* Type);
	void InsertFile(LPCTSTR FileName, VARIANT* Range, VARIANT* ConfirmConversions, VARIANT* Link, VARIANT* Attachment);
	BOOL InStory(LPDISPATCH Range);
	BOOL InRange(LPDISPATCH Range);
	long Delete(VARIANT* Unit, VARIANT* Count);
	long Expand(VARIANT* Unit);
	void InsertParagraph();
	void InsertParagraphAfter();
	LPDISPATCH ConvertToTable(VARIANT* Separator, VARIANT* NumRows, VARIANT* NumColumns, VARIANT* InitialColumnWidth, VARIANT* Format, VARIANT* ApplyBorders, VARIANT* ApplyShading, VARIANT* ApplyFont, VARIANT* ApplyColor, 
		VARIANT* ApplyHeadingRows, VARIANT* ApplyLastRow, VARIANT* ApplyFirstColumn, VARIANT* ApplyLastColumn, VARIANT* AutoFit);
	void InsertDateTime(VARIANT* DateTimeFormat, VARIANT* InsertAsField, VARIANT* InsertAsFullWidth);
	void InsertSymbol(long CharacterNumber, VARIANT* Font, VARIANT* Unicode, VARIANT* Bias);
	void InsertCrossReference(VARIANT* ReferenceType, long ReferenceKind, VARIANT* ReferenceItem, VARIANT* InsertAsHyperlink, VARIANT* IncludePosition);
	void InsertCaption(VARIANT* Label, VARIANT* Title, VARIANT* TitleAutoText, VARIANT* Position);
	void CopyAsPicture();
	void Sort(VARIANT* ExcludeHeader, VARIANT* FieldNumber, VARIANT* SortFieldType, VARIANT* SortOrder, VARIANT* FieldNumber2, VARIANT* SortFieldType2, VARIANT* SortOrder2, VARIANT* FieldNumber3, VARIANT* SortFieldType3, VARIANT* SortOrder3, 
		VARIANT* SortColumn, VARIANT* Separator, VARIANT* CaseSensitive, VARIANT* LanguageID);
	void SortAscending();
	void SortDescending();
	BOOL IsEqual(LPDISPATCH Range);
	float Calculate();
	LPDISPATCH GoTo(VARIANT* What, VARIANT* Which, VARIANT* Count, VARIANT* Name);
	LPDISPATCH GoToNext(long What);
	LPDISPATCH GoToPrevious(long What);
	void PasteSpecial(VARIANT* IconIndex, VARIANT* Link, VARIANT* Placement, VARIANT* DisplayAsIcon, VARIANT* DataType, VARIANT* IconFileName, VARIANT* IconLabel);
	LPDISPATCH PreviousField();
	LPDISPATCH NextField();
	void InsertParagraphBefore();
	void InsertCells(VARIANT* ShiftCells);
	void Extend(VARIANT* Character);
	void Shrink();
	long MoveLeft(VARIANT* Unit, VARIANT* Count, VARIANT* Extend);
	long MoveRight(VARIANT* Unit, VARIANT* Count, VARIANT* Extend);
	long MoveUp(VARIANT* Unit, VARIANT* Count, VARIANT* Extend);
	long MoveDown(VARIANT* Unit, VARIANT* Count, VARIANT* Extend);
	long HomeKey(VARIANT* Unit, VARIANT* Extend);
	long EndKey(VARIANT* Unit, VARIANT* Extend);
	void EscapeKey();
	void TypeText(LPCTSTR Text);
	void CopyFormat();
	void PasteFormat();
	void TypeParagraph();
	void TypeBackspace();
	void NextSubdocument();
	void PreviousSubdocument();
	void SelectColumn();
	void SelectCurrentFont();
	void SelectCurrentAlignment();
	void SelectCurrentSpacing();
	void SelectCurrentIndent();
	void SelectCurrentTabs();
	void SelectCurrentColor();
	void CreateTextbox();
	void WholeStory();
	void SelectRow();
	void SplitTable();
	void InsertRows(VARIANT* NumRows);
	void InsertColumns();
	void InsertFormula(VARIANT* Formula, VARIANT* NumberFormat);
	LPDISPATCH NextRevision(VARIANT* Wrap);
	LPDISPATCH PreviousRevision(VARIANT* Wrap);
};
/////////////////////////////////////////////////////////////////////////////
// TablesOfAuthoritiesCategories wrapper class

class TablesOfAuthoritiesCategories : public COleDispatchDriver
{
public:
	TablesOfAuthoritiesCategories() {}		// Calls COleDispatchDriver default constructor
	TablesOfAuthoritiesCategories(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	TablesOfAuthoritiesCategories(const TablesOfAuthoritiesCategories& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH Item(VARIANT* Index);
};
/////////////////////////////////////////////////////////////////////////////
// TableOfAuthoritiesCategory wrapper class

class TableOfAuthoritiesCategory : public COleDispatchDriver
{
public:
	TableOfAuthoritiesCategory() {}		// Calls COleDispatchDriver default constructor
	TableOfAuthoritiesCategory(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	TableOfAuthoritiesCategory(const TableOfAuthoritiesCategory& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	long GetIndex();
};
/////////////////////////////////////////////////////////////////////////////
// CaptionLabels wrapper class

class CaptionLabels : public COleDispatchDriver
{
public:
	CaptionLabels() {}		// Calls COleDispatchDriver default constructor
	CaptionLabels(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CaptionLabels(const CaptionLabels& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH Item(VARIANT* Index);
	LPDISPATCH Add(LPCTSTR Name);
};
/////////////////////////////////////////////////////////////////////////////
// CaptionLabel wrapper class

class CaptionLabel : public COleDispatchDriver
{
public:
	CaptionLabel() {}		// Calls COleDispatchDriver default constructor
	CaptionLabel(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CaptionLabel(const CaptionLabel& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	CString GetName();
	BOOL GetBuiltIn();
	long GetId();
	BOOL GetIncludeChapterNumber();
	void SetIncludeChapterNumber(BOOL bNewValue);
	long GetNumberStyle();
	void SetNumberStyle(long nNewValue);
	long GetChapterStyleLevel();
	void SetChapterStyleLevel(long nNewValue);
	long GetSeparator();
	void SetSeparator(long nNewValue);
	long GetPosition();
	void SetPosition(long nNewValue);
	void Delete();
};
/////////////////////////////////////////////////////////////////////////////
// AutoCaptions wrapper class

class AutoCaptions : public COleDispatchDriver
{
public:
	AutoCaptions() {}		// Calls COleDispatchDriver default constructor
	AutoCaptions(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	AutoCaptions(const AutoCaptions& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH Item(VARIANT* Index);
	void CancelAutoInsert();
};
/////////////////////////////////////////////////////////////////////////////
// AutoCaption wrapper class

class AutoCaption : public COleDispatchDriver
{
public:
	AutoCaption() {}		// Calls COleDispatchDriver default constructor
	AutoCaption(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	AutoCaption(const AutoCaption& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	CString GetName();
	BOOL GetAutoInsert();
	void SetAutoInsert(BOOL bNewValue);
	long GetIndex();
	VARIANT GetCaptionLabel();
	void SetCaptionLabel(VARIANT* newValue);
};
/////////////////////////////////////////////////////////////////////////////
// Indexes wrapper class

class Indexes : public COleDispatchDriver
{
public:
	Indexes() {}		// Calls COleDispatchDriver default constructor
	Indexes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Indexes(const Indexes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	long GetFormat();
	void SetFormat(long nNewValue);
	LPDISPATCH Item(long Index);
	LPDISPATCH Add(LPDISPATCH Range, VARIANT* HeadingSeparator, VARIANT* RightAlignPageNumbers, VARIANT* Type, VARIANT* NumberOfColumns, VARIANT* AccentedLetters);
	LPDISPATCH MarkEntry(LPDISPATCH Range, VARIANT* Entry, VARIANT* EntryAutoText, VARIANT* CrossReference, VARIANT* CrossReferenceAutoText, VARIANT* BookmarkName, VARIANT* Bold, VARIANT* Italic, VARIANT* Reading);
	void MarkAllEntries(LPDISPATCH Range, VARIANT* Entry, VARIANT* EntryAutoText, VARIANT* CrossReference, VARIANT* CrossReferenceAutoText, VARIANT* BookmarkName, VARIANT* Bold, VARIANT* Italic);
	void AutoMarkEntries(LPCTSTR ConcordanceFileName);
};
/////////////////////////////////////////////////////////////////////////////
// Index wrapper class

class Index : public COleDispatchDriver
{
public:
	Index() {}		// Calls COleDispatchDriver default constructor
	Index(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Index(const Index& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetHeadingSeparator();
	void SetHeadingSeparator(long nNewValue);
	BOOL GetRightAlignPageNumbers();
	void SetRightAlignPageNumbers(BOOL bNewValue);
	long GetType();
	void SetType(long nNewValue);
	long GetNumberOfColumns();
	void SetNumberOfColumns(long nNewValue);
	LPDISPATCH GetRange();
	long GetTabLeader();
	void SetTabLeader(long nNewValue);
	BOOL GetAccentedLetters();
	void SetAccentedLetters(BOOL bNewValue);
	void Delete();
	void Update();
};
/////////////////////////////////////////////////////////////////////////////
// AddIn wrapper class

class AddIn : public COleDispatchDriver
{
public:
	AddIn() {}		// Calls COleDispatchDriver default constructor
	AddIn(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	AddIn(const AddIn& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	CString GetName();
	long GetIndex();
	CString GetPath();
	BOOL GetInstalled();
	void SetInstalled(BOOL bNewValue);
	BOOL GetCompiled();
	BOOL GetAutoload();
	void Delete();
};
/////////////////////////////////////////////////////////////////////////////
// AddIns wrapper class

class AddIns : public COleDispatchDriver
{
public:
	AddIns() {}		// Calls COleDispatchDriver default constructor
	AddIns(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	AddIns(const AddIns& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH Item(VARIANT* Index);
	LPDISPATCH Add(LPCTSTR FileName, VARIANT* Install);
	void Unload(BOOL RemoveFromList);
};
/////////////////////////////////////////////////////////////////////////////
// Revisions wrapper class

class Revisions : public COleDispatchDriver
{
public:
	Revisions() {}		// Calls COleDispatchDriver default constructor
	Revisions(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Revisions(const Revisions& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH Item(long Index);
	void AcceptAll();
	void RejectAll();
};
/////////////////////////////////////////////////////////////////////////////
// Revision wrapper class

class Revision : public COleDispatchDriver
{
public:
	Revision() {}		// Calls COleDispatchDriver default constructor
	Revision(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Revision(const Revision& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	CString GetAuthor();
	DATE GetDate();
	LPDISPATCH GetRange();
	long GetType();
	long GetIndex();
	void Accept();
	void Reject();
};
/////////////////////////////////////////////////////////////////////////////
// Task wrapper class

class Task : public COleDispatchDriver
{
public:
	Task() {}		// Calls COleDispatchDriver default constructor
	Task(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Task(const Task& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	CString GetName();
	long GetLeft();
	void SetLeft(long nNewValue);
	long GetTop();
	void SetTop(long nNewValue);
	long GetWidth();
	void SetWidth(long nNewValue);
	long GetHeight();
	void SetHeight(long nNewValue);
	long GetWindowState();
	void SetWindowState(long nNewValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	void Activate(VARIANT* Wait);
	void Close();
	void Move(long Left, long Top);
	void Resize(long Width, long Height);
	void SendWindowMessage(long Message, long wParam, long lParam);
};
/////////////////////////////////////////////////////////////////////////////
// Tasks wrapper class

class Tasks : public COleDispatchDriver
{
public:
	Tasks() {}		// Calls COleDispatchDriver default constructor
	Tasks(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Tasks(const Tasks& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH Item(VARIANT* Index);
	BOOL Exists(LPCTSTR Name);
	void ExitWindows_();
};
/////////////////////////////////////////////////////////////////////////////
// HeadersFooters wrapper class

class HeadersFooters : public COleDispatchDriver
{
public:
	HeadersFooters() {}		// Calls COleDispatchDriver default constructor
	HeadersFooters(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	HeadersFooters(const HeadersFooters& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH Item(long Index);
};
/////////////////////////////////////////////////////////////////////////////
// HeaderFooter wrapper class

class HeaderFooter : public COleDispatchDriver
{
public:
	HeaderFooter() {}		// Calls COleDispatchDriver default constructor
	HeaderFooter(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	HeaderFooter(const HeaderFooter& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH GetRange();
	long GetIndex();
	BOOL GetIsHeader();
	BOOL GetExists();
	void SetExists(BOOL bNewValue);
	LPDISPATCH GetPageNumbers();
	BOOL GetLinkToPrevious();
	void SetLinkToPrevious(BOOL bNewValue);
	LPDISPATCH GetShapes();
};
/////////////////////////////////////////////////////////////////////////////
// PageNumbers wrapper class

class PageNumbers : public COleDispatchDriver
{
public:
	PageNumbers() {}		// Calls COleDispatchDriver default constructor
	PageNumbers(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PageNumbers(const PageNumbers& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	long GetNumberStyle();
	void SetNumberStyle(long nNewValue);
	BOOL GetIncludeChapterNumber();
	void SetIncludeChapterNumber(BOOL bNewValue);
	long GetHeadingLevelForChapter();
	void SetHeadingLevelForChapter(long nNewValue);
	long GetChapterPageSeparator();
	void SetChapterPageSeparator(long nNewValue);
	BOOL GetRestartNumberingAtSection();
	void SetRestartNumberingAtSection(BOOL bNewValue);
	long GetStartingNumber();
	void SetStartingNumber(long nNewValue);
	BOOL GetShowFirstPageNumber();
	void SetShowFirstPageNumber(BOOL bNewValue);
	LPDISPATCH Item(long Index);
	LPDISPATCH Add(VARIANT* PageNumberAlignment, VARIANT* FirstPage);
};
/////////////////////////////////////////////////////////////////////////////
// PageNumber wrapper class

class PageNumber : public COleDispatchDriver
{
public:
	PageNumber() {}		// Calls COleDispatchDriver default constructor
	PageNumber(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PageNumber(const PageNumber& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetIndex();
	long GetAlignment();
	void SetAlignment(long nNewValue);
	void Select();
	void Copy();
	void Cut();
	void Delete();
};
/////////////////////////////////////////////////////////////////////////////
// Subdocuments wrapper class

class Subdocuments : public COleDispatchDriver
{
public:
	Subdocuments() {}		// Calls COleDispatchDriver default constructor
	Subdocuments(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Subdocuments(const Subdocuments& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetCount();
	LPUNKNOWN Get_NewEnum();
	BOOL GetExpanded();
	void SetExpanded(BOOL bNewValue);
	LPDISPATCH Item(long Index);
	LPDISPATCH AddFromFile(VARIANT* Name, VARIANT* ConfirmConversions, VARIANT* ReadOnly, VARIANT* PasswordDocument, VARIANT* PasswordTemplate, VARIANT* Revert, VARIANT* WritePasswordDocument, VARIANT* WritePasswordTemplate);
	LPDISPATCH AddFromRange(LPDISPATCH Range);
	void Merge(VARIANT* FirstSubdocument, VARIANT* LastSubdocument);
	void Delete();
	void Select();
};
/////////////////////////////////////////////////////////////////////////////
// Subdocument wrapper class

class Subdocument : public COleDispatchDriver
{
public:
	Subdocument() {}		// Calls COleDispatchDriver default constructor
	Subdocument(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Subdocument(const Subdocument& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	BOOL GetLocked();
	void SetLocked(BOOL bNewValue);
	LPDISPATCH GetRange();
	CString GetName();
	CString GetPath();
	BOOL GetHasFile();
	long GetLevel();
	void Delete();
	void Split(LPDISPATCH Range);
	LPDISPATCH Open();
};
/////////////////////////////////////////////////////////////////////////////
// HeadingStyles wrapper class

class HeadingStyles : public COleDispatchDriver
{
public:
	HeadingStyles() {}		// Calls COleDispatchDriver default constructor
	HeadingStyles(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	HeadingStyles(const HeadingStyles& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH Item(long Index);
	LPDISPATCH Add(VARIANT* Style, short Level);
};
/////////////////////////////////////////////////////////////////////////////
// HeadingStyle wrapper class

class HeadingStyle : public COleDispatchDriver
{
public:
	HeadingStyle() {}		// Calls COleDispatchDriver default constructor
	HeadingStyle(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	HeadingStyle(const HeadingStyle& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	VARIANT GetStyle();
	void SetStyle(VARIANT* newValue);
	short GetLevel();
	void SetLevel(short nNewValue);
	void Delete();
};
/////////////////////////////////////////////////////////////////////////////
// StoryRanges wrapper class

class StoryRanges : public COleDispatchDriver
{
public:
	StoryRanges() {}		// Calls COleDispatchDriver default constructor
	StoryRanges(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	StoryRanges(const StoryRanges& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH Item(long Index);
};
/////////////////////////////////////////////////////////////////////////////
// ListLevel wrapper class

class ListLevel : public COleDispatchDriver
{
public:
	ListLevel() {}		// Calls COleDispatchDriver default constructor
	ListLevel(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ListLevel(const ListLevel& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetIndex();
	CString GetNumberFormat();
	void SetNumberFormat(LPCTSTR lpszNewValue);
	long GetTrailingCharacter();
	void SetTrailingCharacter(long nNewValue);
	long GetNumberStyle();
	void SetNumberStyle(long nNewValue);
	float GetNumberPosition();
	void SetNumberPosition(float newValue);
	long GetAlignment();
	void SetAlignment(long nNewValue);
	float GetTextPosition();
	void SetTextPosition(float newValue);
	float GetTabPosition();
	void SetTabPosition(float newValue);
	BOOL GetResetOnHigher();
	void SetResetOnHigher(BOOL bNewValue);
	long GetStartAt();
	void SetStartAt(long nNewValue);
	CString GetLinkedStyle();
	void SetLinkedStyle(LPCTSTR lpszNewValue);
	LPDISPATCH GetFont();
	void SetFont(LPDISPATCH newValue);
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
};
/////////////////////////////////////////////////////////////////////////////
// ListLevels wrapper class

class ListLevels : public COleDispatchDriver
{
public:
	ListLevels() {}		// Calls COleDispatchDriver default constructor
	ListLevels(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ListLevels(const ListLevels& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH Item(long Index);
};
/////////////////////////////////////////////////////////////////////////////
// ListTemplate wrapper class

class ListTemplate : public COleDispatchDriver
{
public:
	ListTemplate() {}		// Calls COleDispatchDriver default constructor
	ListTemplate(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ListTemplate(const ListTemplate& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	BOOL GetOutlineNumbered();
	void SetOutlineNumbered(BOOL bNewValue);
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	LPDISPATCH GetListLevels();
	LPDISPATCH Convert(VARIANT* Level);
};
/////////////////////////////////////////////////////////////////////////////
// ListTemplates wrapper class

class ListTemplates : public COleDispatchDriver
{
public:
	ListTemplates() {}		// Calls COleDispatchDriver default constructor
	ListTemplates(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ListTemplates(const ListTemplates& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH Item(VARIANT* Index);
	LPDISPATCH Add(VARIANT* OutlineNumbered, VARIANT* Name);
};
/////////////////////////////////////////////////////////////////////////////
// ListParagraphs wrapper class

class ListParagraphs : public COleDispatchDriver
{
public:
	ListParagraphs() {}		// Calls COleDispatchDriver default constructor
	ListParagraphs(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ListParagraphs(const ListParagraphs& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH Item(long Index);
};
/////////////////////////////////////////////////////////////////////////////
// List wrapper class

class List : public COleDispatchDriver
{
public:
	List() {}		// Calls COleDispatchDriver default constructor
	List(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	List(const List& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetRange();
	LPDISPATCH GetListParagraphs();
	BOOL GetSingleListTemplate();
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	void ConvertNumbersToText(VARIANT* NumberType);
	void RemoveNumbers(VARIANT* NumberType);
	long CountNumberedItems(VARIANT* NumberType, VARIANT* Level);
	void ApplyListTemplate(LPDISPATCH ListTemplate, VARIANT* ContinuePreviousList);
	long CanContinuePreviousList(LPDISPATCH ListTemplate);
};
/////////////////////////////////////////////////////////////////////////////
// Lists wrapper class

class Lists : public COleDispatchDriver
{
public:
	Lists() {}		// Calls COleDispatchDriver default constructor
	Lists(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Lists(const Lists& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH Item(long Index);
};
/////////////////////////////////////////////////////////////////////////////
// ListGallery wrapper class

class ListGallery : public COleDispatchDriver
{
public:
	ListGallery() {}		// Calls COleDispatchDriver default constructor
	ListGallery(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ListGallery(const ListGallery& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetListTemplates();
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	BOOL GetModified(long Index);
	void Reset(long Index);
};
/////////////////////////////////////////////////////////////////////////////
// ListGalleries wrapper class

class ListGalleries : public COleDispatchDriver
{
public:
	ListGalleries() {}		// Calls COleDispatchDriver default constructor
	ListGalleries(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ListGalleries(const ListGalleries& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH Item(long Index);
};
/////////////////////////////////////////////////////////////////////////////
// KeyBindings wrapper class

class KeyBindings : public COleDispatchDriver
{
public:
	KeyBindings() {}		// Calls COleDispatchDriver default constructor
	KeyBindings(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	KeyBindings(const KeyBindings& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH GetContext();
	LPDISPATCH Item(long Index);
	LPDISPATCH Add(long KeyCategory, LPCTSTR Command, long KeyCode, VARIANT* KeyCode2, VARIANT* CommandParameter);
	void ClearAll();
	LPDISPATCH Key(long KeyCode, VARIANT* KeyCode2);
};
/////////////////////////////////////////////////////////////////////////////
// KeysBoundTo wrapper class

class KeysBoundTo : public COleDispatchDriver
{
public:
	KeysBoundTo() {}		// Calls COleDispatchDriver default constructor
	KeysBoundTo(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	KeysBoundTo(const KeysBoundTo& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	long GetKeyCategory();
	CString GetCommand();
	CString GetCommandParameter();
	LPDISPATCH GetContext();
	LPDISPATCH Item(long Index);
	LPDISPATCH Key(long KeyCode, VARIANT* KeyCode2);
};
/////////////////////////////////////////////////////////////////////////////
// KeyBinding wrapper class

class KeyBinding : public COleDispatchDriver
{
public:
	KeyBinding() {}		// Calls COleDispatchDriver default constructor
	KeyBinding(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	KeyBinding(const KeyBinding& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	CString GetCommand();
	CString GetKeyString();
	BOOL GetProtected();
	long GetKeyCategory();
	long GetKeyCode();
	long GetKeyCode2();
	CString GetCommandParameter();
	LPDISPATCH GetContext();
	void Clear();
	void Disable();
	void Execute();
	void Rebind(long KeyCategory, LPCTSTR Command, VARIANT* CommandParameter);
};
/////////////////////////////////////////////////////////////////////////////
// FileConverter wrapper class

class FileConverter : public COleDispatchDriver
{
public:
	FileConverter() {}		// Calls COleDispatchDriver default constructor
	FileConverter(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	FileConverter(const FileConverter& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	CString GetFormatName();
	CString GetClassName();
	long GetSaveFormat();
	long GetOpenFormat();
	BOOL GetCanSave();
	BOOL GetCanOpen();
	CString GetPath();
	CString GetName();
	CString GetExtensions();
};
/////////////////////////////////////////////////////////////////////////////
// FileConverters wrapper class

class FileConverters : public COleDispatchDriver
{
public:
	FileConverters() {}		// Calls COleDispatchDriver default constructor
	FileConverters(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	FileConverters(const FileConverters& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetCount();
	LPUNKNOWN Get_NewEnum();
	long GetConvertMacWordChevrons();
	void SetConvertMacWordChevrons(long nNewValue);
	LPDISPATCH Item(VARIANT* Index);
};
/////////////////////////////////////////////////////////////////////////////
// SynonymInfo wrapper class

class SynonymInfo : public COleDispatchDriver
{
public:
	SynonymInfo() {}		// Calls COleDispatchDriver default constructor
	SynonymInfo(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	SynonymInfo(const SynonymInfo& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	CString GetWord();
	BOOL GetFound();
	long GetMeaningCount();
	VARIANT GetMeaningList();
	VARIANT GetPartOfSpeechList();
	VARIANT GetSynonymList(VARIANT* Meaning);
	VARIANT GetAntonymList();
	VARIANT GetRelatedExpressionList();
	VARIANT GetRelatedWordList();
};
/////////////////////////////////////////////////////////////////////////////
// Hyperlinks wrapper class

class Hyperlinks : public COleDispatchDriver
{
public:
	Hyperlinks() {}		// Calls COleDispatchDriver default constructor
	Hyperlinks(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Hyperlinks(const Hyperlinks& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetCount();
	LPUNKNOWN Get_NewEnum();
	LPDISPATCH Item(VARIANT* Index);
	LPDISPATCH Add(LPDISPATCH Anchor, VARIANT* Address, VARIANT* SubAddress);
};
/////////////////////////////////////////////////////////////////////////////
// Hyperlink wrapper class

class Hyperlink : public COleDispatchDriver
{
public:
	Hyperlink() {}		// Calls COleDispatchDriver default constructor
	Hyperlink(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Hyperlink(const Hyperlink& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	CString GetName();
	CString GetAddress();
	long GetType();
	LPDISPATCH GetRange();
	LPDISPATCH GetShape();
	CString GetSubAddress();
	BOOL GetExtraInfoRequired();
	void Delete();
	void Follow(VARIANT* NewWindow, VARIANT* AddHistory, VARIANT* ExtraInfo, VARIANT* Method, VARIANT* HeaderInfo);
	void AddToFavorites();
};
/////////////////////////////////////////////////////////////////////////////
// Shapes wrapper class

class Shapes : public COleDispatchDriver
{
public:
	Shapes() {}		// Calls COleDispatchDriver default constructor
	Shapes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Shapes(const Shapes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetCount();
	LPUNKNOWN Get_NewEnum();
	LPDISPATCH Item(VARIANT* Index);
	LPDISPATCH AddCallout(long Type, float Left, float Top, float Width, float Height, VARIANT* Anchor);
	LPDISPATCH AddCurve(VARIANT* SafeArrayOfPoints, VARIANT* Anchor);
	LPDISPATCH AddLabel(long Orientation, float Left, float Top, float Width, float Height, VARIANT* Anchor);
	LPDISPATCH AddLine(float BeginX, float BeginY, float EndX, float EndY, VARIANT* Anchor);
	LPDISPATCH AddPicture(LPCTSTR FileName, VARIANT* LinkToFile, VARIANT* SaveWithDocument, VARIANT* Left, VARIANT* Top, VARIANT* Width, VARIANT* Height, VARIANT* Anchor);
	LPDISPATCH AddPolyline(VARIANT* SafeArrayOfPoints, VARIANT* Anchor);
	LPDISPATCH AddShape(long Type, float Left, float Top, float Width, float Height, VARIANT* Anchor);
	LPDISPATCH AddTextEffect(long PresetTextEffect, LPCTSTR Text, LPCTSTR FontName, float FontSize, long FontBold, long FontItalic, float Left, float Top, VARIANT* Anchor);
	LPDISPATCH AddTextbox(long Orientation, float Left, float Top, float Width, float Height, VARIANT* Anchor);
	LPDISPATCH BuildFreeform(long EditingType, float X1, float Y1);
	LPDISPATCH Range(VARIANT* Index);
	void SelectAll();
	LPDISPATCH AddOLEObject(VARIANT* ClassType, VARIANT* FileName, VARIANT* LinkToFile, VARIANT* DisplayAsIcon, VARIANT* IconFileName, VARIANT* IconIndex, VARIANT* IconLabel, VARIANT* Left, VARIANT* Top, VARIANT* Width, VARIANT* Height, 
		VARIANT* Anchor);
	LPDISPATCH AddOLEControl(VARIANT* ClassType, VARIANT* Left, VARIANT* Top, VARIANT* Width, VARIANT* Height, VARIANT* Anchor);
};
/////////////////////////////////////////////////////////////////////////////
// ShapeRange wrapper class

class ShapeRange : public COleDispatchDriver
{
public:
	ShapeRange() {}		// Calls COleDispatchDriver default constructor
	ShapeRange(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ShapeRange(const ShapeRange& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetCount();
	LPUNKNOWN Get_NewEnum();
	LPDISPATCH GetAdjustments();
	long GetAutoShapeType();
	void SetAutoShapeType(long nNewValue);
	LPDISPATCH GetCallout();
	LPDISPATCH GetFill();
	LPDISPATCH GetGroupItems();
	float GetHeight();
	void SetHeight(float newValue);
	long GetHorizontalFlip();
	float GetLeft();
	void SetLeft(float newValue);
	LPDISPATCH GetLine();
	long GetLockAspectRatio();
	void SetLockAspectRatio(long nNewValue);
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	LPDISPATCH GetNodes();
	float GetRotation();
	void SetRotation(float newValue);
	LPDISPATCH GetPictureFormat();
	LPDISPATCH GetShadow();
	LPDISPATCH GetTextEffect();
	LPDISPATCH GetTextFrame();
	LPDISPATCH GetThreeD();
	float GetTop();
	void SetTop(float newValue);
	long GetType();
	long GetVerticalFlip();
	VARIANT GetVertices();
	long GetVisible();
	void SetVisible(long nNewValue);
	float GetWidth();
	void SetWidth(float newValue);
	long GetZOrderPosition();
	LPDISPATCH GetHyperlink();
	long GetRelativeHorizontalPosition();
	void SetRelativeHorizontalPosition(long nNewValue);
	long GetRelativeVerticalPosition();
	void SetRelativeVerticalPosition(long nNewValue);
	long GetLockAnchor();
	void SetLockAnchor(long nNewValue);
	LPDISPATCH GetWrapFormat();
	LPDISPATCH GetAnchor();
	LPDISPATCH Item(VARIANT* Index);
	void Align(long Align, long RelativeTo);
	void Apply();
	void Delete();
	void Distribute(long Distribute, long RelativeTo);
	LPDISPATCH Duplicate();
	void Flip(long FlipCmd);
	void IncrementLeft(float Increment);
	void IncrementRotation(float Increment);
	void IncrementTop(float Increment);
	LPDISPATCH Group();
	void PickUp();
	LPDISPATCH Regroup();
	void ScaleHeight(float Factor, long RelativeToOriginalSize, long Scale);
	void ScaleWidth(float Factor, long RelativeToOriginalSize, long Scale);
	void Select(VARIANT* Replace);
	void SetShapesDefaultProperties();
	LPDISPATCH Ungroup();
	void ZOrder(long ZOrderCmd);
	LPDISPATCH ConvertToFrame();
	LPDISPATCH ConvertToInlineShape();
	void Activate();
};
/////////////////////////////////////////////////////////////////////////////
// GroupShapes wrapper class

class GroupShapes : public COleDispatchDriver
{
public:
	GroupShapes() {}		// Calls COleDispatchDriver default constructor
	GroupShapes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	GroupShapes(const GroupShapes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetCount();
	LPUNKNOWN Get_NewEnum();
	LPDISPATCH Item(VARIANT* Index);
};
/////////////////////////////////////////////////////////////////////////////
// Shape wrapper class

class Shape : public COleDispatchDriver
{
public:
	Shape() {}		// Calls COleDispatchDriver default constructor
	Shape(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Shape(const Shape& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH GetAdjustments();
	long GetAutoShapeType();
	void SetAutoShapeType(long nNewValue);
	LPDISPATCH GetCallout();
	LPDISPATCH GetFill();
	LPDISPATCH GetGroupItems();
	float GetHeight();
	void SetHeight(float newValue);
	long GetHorizontalFlip();
	float GetLeft();
	void SetLeft(float newValue);
	LPDISPATCH GetLine();
	long GetLockAspectRatio();
	void SetLockAspectRatio(long nNewValue);
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	LPDISPATCH GetNodes();
	float GetRotation();
	void SetRotation(float newValue);
	LPDISPATCH GetPictureFormat();
	LPDISPATCH GetShadow();
	LPDISPATCH GetTextEffect();
	LPDISPATCH GetTextFrame();
	LPDISPATCH GetThreeD();
	float GetTop();
	void SetTop(float newValue);
	long GetType();
	long GetVerticalFlip();
	VARIANT GetVertices();
	long GetVisible();
	void SetVisible(long nNewValue);
	float GetWidth();
	void SetWidth(float newValue);
	long GetZOrderPosition();
	LPDISPATCH GetHyperlink();
	long GetRelativeHorizontalPosition();
	void SetRelativeHorizontalPosition(long nNewValue);
	long GetRelativeVerticalPosition();
	void SetRelativeVerticalPosition(long nNewValue);
	long GetLockAnchor();
	void SetLockAnchor(long nNewValue);
	LPDISPATCH GetWrapFormat();
	LPDISPATCH GetOLEFormat();
	LPDISPATCH GetAnchor();
	LPDISPATCH GetLinkFormat();
	void Apply();
	void Delete();
	LPDISPATCH Duplicate();
	void Flip(long FlipCmd);
	void IncrementLeft(float Increment);
	void IncrementRotation(float Increment);
	void IncrementTop(float Increment);
	void PickUp();
	void ScaleHeight(float Factor, long RelativeToOriginalSize, long Scale);
	void ScaleWidth(float Factor, long RelativeToOriginalSize, long Scale);
	void Select(VARIANT* Replace);
	void SetShapesDefaultProperties();
	LPDISPATCH Ungroup();
	void ZOrder(long ZOrderCmd);
	LPDISPATCH ConvertToInlineShape();
	LPDISPATCH ConvertToFrame();
	void Activate();
};
/////////////////////////////////////////////////////////////////////////////
// TextFrame wrapper class

class TextFrame : public COleDispatchDriver
{
public:
	TextFrame() {}		// Calls COleDispatchDriver default constructor
	TextFrame(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	TextFrame(const TextFrame& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	float GetMarginBottom();
	void SetMarginBottom(float newValue);
	float GetMarginLeft();
	void SetMarginLeft(float newValue);
	float GetMarginRight();
	void SetMarginRight(float newValue);
	float GetMarginTop();
	void SetMarginTop(float newValue);
	long GetOrientation();
	void SetOrientation(long nNewValue);
	LPDISPATCH GetTextRange();
	LPDISPATCH GetContainingRange();
	LPDISPATCH GetNext();
	void SetNext(LPDISPATCH newValue);
	LPDISPATCH GetPrevious();
	void SetPrevious(LPDISPATCH newValue);
	BOOL GetOverflowing();
	long GetHasText();
	void BreakForwardLink();
	BOOL ValidLinkTarget(LPDISPATCH TargetTextFrame);
};
/////////////////////////////////////////////////////////////////////////////
// _LetterContent wrapper class

class _LetterContent : public COleDispatchDriver
{
public:
	_LetterContent() {}		// Calls COleDispatchDriver default constructor
	_LetterContent(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_LetterContent(const _LetterContent& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH GetDuplicate();
	CString GetDateFormat();
	void SetDateFormat(LPCTSTR lpszNewValue);
	BOOL GetIncludeHeaderFooter();
	void SetIncludeHeaderFooter(BOOL bNewValue);
	CString GetPageDesign();
	void SetPageDesign(LPCTSTR lpszNewValue);
	long GetLetterStyle();
	void SetLetterStyle(long nNewValue);
	BOOL GetLetterhead();
	void SetLetterhead(BOOL bNewValue);
	long GetLetterheadLocation();
	void SetLetterheadLocation(long nNewValue);
	float GetLetterheadSize();
	void SetLetterheadSize(float newValue);
	CString GetRecipientName();
	void SetRecipientName(LPCTSTR lpszNewValue);
	CString GetRecipientAddress();
	void SetRecipientAddress(LPCTSTR lpszNewValue);
	CString GetSalutation();
	void SetSalutation(LPCTSTR lpszNewValue);
	long GetSalutationType();
	void SetSalutationType(long nNewValue);
	CString GetRecipientReference();
	void SetRecipientReference(LPCTSTR lpszNewValue);
	CString GetMailingInstructions();
	void SetMailingInstructions(LPCTSTR lpszNewValue);
	CString GetAttentionLine();
	void SetAttentionLine(LPCTSTR lpszNewValue);
	CString GetSubject();
	void SetSubject(LPCTSTR lpszNewValue);
	long GetEnclosureNumber();
	void SetEnclosureNumber(long nNewValue);
	CString GetCCList();
	void SetCCList(LPCTSTR lpszNewValue);
	CString GetReturnAddress();
	void SetReturnAddress(LPCTSTR lpszNewValue);
	CString GetSenderName();
	void SetSenderName(LPCTSTR lpszNewValue);
	CString GetClosing();
	void SetClosing(LPCTSTR lpszNewValue);
	CString GetSenderCompany();
	void SetSenderCompany(LPCTSTR lpszNewValue);
	CString GetSenderJobTitle();
	void SetSenderJobTitle(LPCTSTR lpszNewValue);
	CString GetSenderInitials();
	void SetSenderInitials(LPCTSTR lpszNewValue);
	BOOL GetInfoBlock();
	void SetInfoBlock(BOOL bNewValue);
	CString GetRecipientCode();
	void SetRecipientCode(LPCTSTR lpszNewValue);
	long GetRecipientGender();
	void SetRecipientGender(long nNewValue);
	CString GetReturnAddressShortForm();
	void SetReturnAddressShortForm(LPCTSTR lpszNewValue);
	CString GetSenderCity();
	void SetSenderCity(LPCTSTR lpszNewValue);
	CString GetSenderCode();
	void SetSenderCode(LPCTSTR lpszNewValue);
	long GetSenderGender();
	void SetSenderGender(long nNewValue);
	CString GetSenderReference();
	void SetSenderReference(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// View wrapper class

class View : public COleDispatchDriver
{
public:
	View() {}		// Calls COleDispatchDriver default constructor
	View(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	View(const View& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetType();
	void SetType(long nNewValue);
	BOOL GetFullScreen();
	void SetFullScreen(BOOL bNewValue);
	BOOL GetDraft();
	void SetDraft(BOOL bNewValue);
	BOOL GetShowAll();
	void SetShowAll(BOOL bNewValue);
	BOOL GetShowFieldCodes();
	void SetShowFieldCodes(BOOL bNewValue);
	BOOL GetMailMergeDataView();
	void SetMailMergeDataView(BOOL bNewValue);
	BOOL GetMagnifier();
	void SetMagnifier(BOOL bNewValue);
	BOOL GetShowFirstLineOnly();
	void SetShowFirstLineOnly(BOOL bNewValue);
	BOOL GetShowFormat();
	void SetShowFormat(BOOL bNewValue);
	LPDISPATCH GetZoom();
	BOOL GetShowObjectAnchors();
	void SetShowObjectAnchors(BOOL bNewValue);
	BOOL GetShowTextBoundaries();
	void SetShowTextBoundaries(BOOL bNewValue);
	BOOL GetShowHighlight();
	void SetShowHighlight(BOOL bNewValue);
	BOOL GetShowDrawings();
	void SetShowDrawings(BOOL bNewValue);
	BOOL GetShowTabs();
	void SetShowTabs(BOOL bNewValue);
	BOOL GetShowSpaces();
	void SetShowSpaces(BOOL bNewValue);
	BOOL GetShowParagraphs();
	void SetShowParagraphs(BOOL bNewValue);
	BOOL GetShowHyphens();
	void SetShowHyphens(BOOL bNewValue);
	BOOL GetShowHiddenText();
	void SetShowHiddenText(BOOL bNewValue);
	BOOL GetWrapToWindow();
	void SetWrapToWindow(BOOL bNewValue);
	BOOL GetShowPicturePlaceHolders();
	void SetShowPicturePlaceHolders(BOOL bNewValue);
	BOOL GetShowBookmarks();
	void SetShowBookmarks(BOOL bNewValue);
	long GetFieldShading();
	void SetFieldShading(long nNewValue);
	BOOL GetShowAnimation();
	void SetShowAnimation(BOOL bNewValue);
	BOOL GetTableGridlines();
	void SetTableGridlines(BOOL bNewValue);
	long GetEnlargeFontsLessThan();
	void SetEnlargeFontsLessThan(long nNewValue);
	BOOL GetShowMainTextLayer();
	void SetShowMainTextLayer(BOOL bNewValue);
	long GetSeekView();
	void SetSeekView(long nNewValue);
	long GetSplitSpecial();
	void SetSplitSpecial(long nNewValue);
	long GetBrowseToWindow();
	void SetBrowseToWindow(long nNewValue);
	void CollapseOutline(VARIANT* Range);
	void ExpandOutline(VARIANT* Range);
	void ShowAllHeadings();
	void ShowHeading(long Level);
	void PreviousHeaderFooter();
	void NextHeaderFooter();
};
/////////////////////////////////////////////////////////////////////////////
// Zoom wrapper class

class Zoom : public COleDispatchDriver
{
public:
	Zoom() {}		// Calls COleDispatchDriver default constructor
	Zoom(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Zoom(const Zoom& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetPercentage();
	void SetPercentage(long nNewValue);
	long GetPageFit();
	void SetPageFit(long nNewValue);
	long GetPageRows();
	void SetPageRows(long nNewValue);
	long GetPageColumns();
	void SetPageColumns(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// Zooms wrapper class

class Zooms : public COleDispatchDriver
{
public:
	Zooms() {}		// Calls COleDispatchDriver default constructor
	Zooms(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Zooms(const Zooms& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH Item(long Index);
};
/////////////////////////////////////////////////////////////////////////////
// InlineShape wrapper class

class InlineShape : public COleDispatchDriver
{
public:
	InlineShape() {}		// Calls COleDispatchDriver default constructor
	InlineShape(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	InlineShape(const InlineShape& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH GetBorders();
	void SetBorders(LPDISPATCH newValue);
	LPDISPATCH GetRange();
	LPDISPATCH GetLinkFormat();
	LPDISPATCH GetField();
	LPDISPATCH GetOLEFormat();
	long GetType();
	LPDISPATCH GetHyperlink();
	float GetHeight();
	void SetHeight(float newValue);
	float GetWidth();
	void SetWidth(float newValue);
	float GetScaleHeight();
	void SetScaleHeight(float newValue);
	float GetScaleWidth();
	void SetScaleWidth(float newValue);
	long GetLockAspectRatio();
	void SetLockAspectRatio(long nNewValue);
	LPDISPATCH GetLine();
	LPDISPATCH GetFill();
	LPDISPATCH GetPictureFormat();
	void SetPictureFormat(LPDISPATCH newValue);
	void Activate();
	void Reset();
	void Delete();
	void Select();
	LPDISPATCH ConvertToShape();
};
/////////////////////////////////////////////////////////////////////////////
// InlineShapes wrapper class

class InlineShapes : public COleDispatchDriver
{
public:
	InlineShapes() {}		// Calls COleDispatchDriver default constructor
	InlineShapes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	InlineShapes(const InlineShapes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetCount();
	LPUNKNOWN Get_NewEnum();
	LPDISPATCH Item(long Index);
	LPDISPATCH AddPicture(LPCTSTR FileName, VARIANT* LinkToFile, VARIANT* SaveWithDocument, VARIANT* Range);
	LPDISPATCH AddOLEObject(VARIANT* ClassType, VARIANT* FileName, VARIANT* LinkToFile, VARIANT* DisplayAsIcon, VARIANT* IconFileName, VARIANT* IconIndex, VARIANT* IconLabel, VARIANT* Range);
	LPDISPATCH AddOLEControl(VARIANT* ClassType, VARIANT* Range);
	LPDISPATCH New(LPDISPATCH Range);
};
/////////////////////////////////////////////////////////////////////////////
// SpellingSuggestions wrapper class

class SpellingSuggestions : public COleDispatchDriver
{
public:
	SpellingSuggestions() {}		// Calls COleDispatchDriver default constructor
	SpellingSuggestions(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	SpellingSuggestions(const SpellingSuggestions& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	long GetSpellingErrorType();
	LPDISPATCH Item(long Index);
};
/////////////////////////////////////////////////////////////////////////////
// SpellingSuggestion wrapper class

class SpellingSuggestion : public COleDispatchDriver
{
public:
	SpellingSuggestion() {}		// Calls COleDispatchDriver default constructor
	SpellingSuggestion(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	SpellingSuggestion(const SpellingSuggestion& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	CString GetName();
};
/////////////////////////////////////////////////////////////////////////////
// Dictionaries wrapper class

class Dictionaries : public COleDispatchDriver
{
public:
	Dictionaries() {}		// Calls COleDispatchDriver default constructor
	Dictionaries(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Dictionaries(const Dictionaries& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	long GetMaximum();
	LPDISPATCH GetActiveCustomDictionary();
	void SetActiveCustomDictionary(LPDISPATCH newValue);
	LPDISPATCH Item(VARIANT* Index);
	LPDISPATCH Add(LPCTSTR FileName);
	void ClearAll();
};
/////////////////////////////////////////////////////////////////////////////
// HangulHanjaConversionDictionaries wrapper class

class HangulHanjaConversionDictionaries : public COleDispatchDriver
{
public:
	HangulHanjaConversionDictionaries() {}		// Calls COleDispatchDriver default constructor
	HangulHanjaConversionDictionaries(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	HangulHanjaConversionDictionaries(const HangulHanjaConversionDictionaries& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	long GetMaximum();
	LPDISPATCH GetActiveCustomDictionary();
	void SetActiveCustomDictionary(LPDISPATCH newValue);
	LPDISPATCH GetBuiltinDictionary();
	LPDISPATCH Item(VARIANT* Index);
	LPDISPATCH Add(LPCTSTR FileName);
	void ClearAll();
};
/////////////////////////////////////////////////////////////////////////////
// Dictionary wrapper class

class Dictionary : public COleDispatchDriver
{
public:
	Dictionary() {}		// Calls COleDispatchDriver default constructor
	Dictionary(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Dictionary(const Dictionary& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	CString GetName();
	CString GetPath();
	long GetLanguageID();
	void SetLanguageID(long nNewValue);
	BOOL GetReadOnly();
	long GetType();
	BOOL GetLanguageSpecific();
	void SetLanguageSpecific(BOOL bNewValue);
	void Delete();
};
/////////////////////////////////////////////////////////////////////////////
// ReadabilityStatistics wrapper class

class ReadabilityStatistics : public COleDispatchDriver
{
public:
	ReadabilityStatistics() {}		// Calls COleDispatchDriver default constructor
	ReadabilityStatistics(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ReadabilityStatistics(const ReadabilityStatistics& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH Item(VARIANT* Index);
};
/////////////////////////////////////////////////////////////////////////////
// ReadabilityStatistic wrapper class

class ReadabilityStatistic : public COleDispatchDriver
{
public:
	ReadabilityStatistic() {}		// Calls COleDispatchDriver default constructor
	ReadabilityStatistic(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ReadabilityStatistic(const ReadabilityStatistic& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	CString GetName();
	float GetValue();
};
/////////////////////////////////////////////////////////////////////////////
// Versions wrapper class

class Versions : public COleDispatchDriver
{
public:
	Versions() {}		// Calls COleDispatchDriver default constructor
	Versions(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Versions(const Versions& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	long GetAutoVersion();
	void SetAutoVersion(long nNewValue);
	LPDISPATCH Item(long Index);
	void Save(VARIANT* Comment);
};
/////////////////////////////////////////////////////////////////////////////
// Version wrapper class

class Version : public COleDispatchDriver
{
public:
	Version() {}		// Calls COleDispatchDriver default constructor
	Version(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Version(const Version& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	CString GetSavedBy();
	CString GetComment();
	DATE GetDate();
	long GetIndex();
	void Open();
	void Delete();
};
/////////////////////////////////////////////////////////////////////////////
// Options wrapper class

class Options : public COleDispatchDriver
{
public:
	Options() {}		// Calls COleDispatchDriver default constructor
	Options(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Options(const Options& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	BOOL GetAllowAccentedUppercase();
	void SetAllowAccentedUppercase(BOOL bNewValue);
	BOOL GetWPHelp();
	void SetWPHelp(BOOL bNewValue);
	BOOL GetWPDocNavKeys();
	void SetWPDocNavKeys(BOOL bNewValue);
	BOOL GetPagination();
	void SetPagination(BOOL bNewValue);
	BOOL GetBlueScreen();
	void SetBlueScreen(BOOL bNewValue);
	BOOL GetEnableSound();
	void SetEnableSound(BOOL bNewValue);
	BOOL GetConfirmConversions();
	void SetConfirmConversions(BOOL bNewValue);
	BOOL GetUpdateLinksAtOpen();
	void SetUpdateLinksAtOpen(BOOL bNewValue);
	BOOL GetSendMailAttach();
	void SetSendMailAttach(BOOL bNewValue);
	long GetMeasurementUnit();
	void SetMeasurementUnit(long nNewValue);
	long GetButtonFieldClicks();
	void SetButtonFieldClicks(long nNewValue);
	BOOL GetShortMenuNames();
	void SetShortMenuNames(BOOL bNewValue);
	BOOL GetRTFInClipboard();
	void SetRTFInClipboard(BOOL bNewValue);
	BOOL GetUpdateFieldsAtPrint();
	void SetUpdateFieldsAtPrint(BOOL bNewValue);
	BOOL GetPrintProperties();
	void SetPrintProperties(BOOL bNewValue);
	BOOL GetPrintFieldCodes();
	void SetPrintFieldCodes(BOOL bNewValue);
	BOOL GetPrintComments();
	void SetPrintComments(BOOL bNewValue);
	BOOL GetPrintHiddenText();
	void SetPrintHiddenText(BOOL bNewValue);
	BOOL GetEnvelopeFeederInstalled();
	BOOL GetUpdateLinksAtPrint();
	void SetUpdateLinksAtPrint(BOOL bNewValue);
	BOOL GetPrintBackground();
	void SetPrintBackground(BOOL bNewValue);
	BOOL GetPrintDrawingObjects();
	void SetPrintDrawingObjects(BOOL bNewValue);
	CString GetDefaultTray();
	void SetDefaultTray(LPCTSTR lpszNewValue);
	long GetDefaultTrayID();
	void SetDefaultTrayID(long nNewValue);
	BOOL GetCreateBackup();
	void SetCreateBackup(BOOL bNewValue);
	BOOL GetAllowFastSave();
	void SetAllowFastSave(BOOL bNewValue);
	BOOL GetSavePropertiesPrompt();
	void SetSavePropertiesPrompt(BOOL bNewValue);
	BOOL GetSaveNormalPrompt();
	void SetSaveNormalPrompt(BOOL bNewValue);
	long GetSaveInterval();
	void SetSaveInterval(long nNewValue);
	BOOL GetBackgroundSave();
	void SetBackgroundSave(BOOL bNewValue);
	long GetInsertedTextMark();
	void SetInsertedTextMark(long nNewValue);
	long GetDeletedTextMark();
	void SetDeletedTextMark(long nNewValue);
	long GetRevisedLinesMark();
	void SetRevisedLinesMark(long nNewValue);
	long GetInsertedTextColor();
	void SetInsertedTextColor(long nNewValue);
	long GetDeletedTextColor();
	void SetDeletedTextColor(long nNewValue);
	long GetRevisedLinesColor();
	void SetRevisedLinesColor(long nNewValue);
	CString GetDefaultFilePath(long Path);
	void SetDefaultFilePath(long Path, LPCTSTR lpszNewValue);
	BOOL GetOvertype();
	void SetOvertype(BOOL bNewValue);
	BOOL GetReplaceSelection();
	void SetReplaceSelection(BOOL bNewValue);
	BOOL GetAllowDragAndDrop();
	void SetAllowDragAndDrop(BOOL bNewValue);
	BOOL GetAutoWordSelection();
	void SetAutoWordSelection(BOOL bNewValue);
	BOOL GetINSKeyForPaste();
	void SetINSKeyForPaste(BOOL bNewValue);
	BOOL GetSmartCutPaste();
	void SetSmartCutPaste(BOOL bNewValue);
	BOOL GetTabIndentKey();
	void SetTabIndentKey(BOOL bNewValue);
	CString GetPictureEditor();
	void SetPictureEditor(LPCTSTR lpszNewValue);
	BOOL GetAnimateScreenMovements();
	void SetAnimateScreenMovements(BOOL bNewValue);
	BOOL GetVirusProtection();
	void SetVirusProtection(BOOL bNewValue);
	long GetRevisedPropertiesMark();
	void SetRevisedPropertiesMark(long nNewValue);
	long GetRevisedPropertiesColor();
	void SetRevisedPropertiesColor(long nNewValue);
	BOOL GetSnapToGrid();
	void SetSnapToGrid(BOOL bNewValue);
	BOOL GetSnapToShapes();
	void SetSnapToShapes(BOOL bNewValue);
	float GetGridDistanceHorizontal();
	void SetGridDistanceHorizontal(float newValue);
	float GetGridDistanceVertical();
	void SetGridDistanceVertical(float newValue);
	float GetGridOriginHorizontal();
	void SetGridOriginHorizontal(float newValue);
	float GetGridOriginVertical();
	void SetGridOriginVertical(float newValue);
	BOOL GetAutoFormatApplyHeadings();
	void SetAutoFormatApplyHeadings(BOOL bNewValue);
	BOOL GetAutoFormatApplyLists();
	void SetAutoFormatApplyLists(BOOL bNewValue);
	BOOL GetAutoFormatApplyBulletedLists();
	void SetAutoFormatApplyBulletedLists(BOOL bNewValue);
	BOOL GetAutoFormatApplyOtherParas();
	void SetAutoFormatApplyOtherParas(BOOL bNewValue);
	BOOL GetAutoFormatReplaceQuotes();
	void SetAutoFormatReplaceQuotes(BOOL bNewValue);
	BOOL GetAutoFormatReplaceSymbols();
	void SetAutoFormatReplaceSymbols(BOOL bNewValue);
	BOOL GetAutoFormatReplaceOrdinals();
	void SetAutoFormatReplaceOrdinals(BOOL bNewValue);
	BOOL GetAutoFormatReplaceFractions();
	void SetAutoFormatReplaceFractions(BOOL bNewValue);
	BOOL GetAutoFormatReplacePlainTextEmphasis();
	void SetAutoFormatReplacePlainTextEmphasis(BOOL bNewValue);
	BOOL GetAutoFormatPreserveStyles();
	void SetAutoFormatPreserveStyles(BOOL bNewValue);
	BOOL GetAutoFormatAsYouTypeApplyHeadings();
	void SetAutoFormatAsYouTypeApplyHeadings(BOOL bNewValue);
	BOOL GetAutoFormatAsYouTypeApplyBorders();
	void SetAutoFormatAsYouTypeApplyBorders(BOOL bNewValue);
	BOOL GetAutoFormatAsYouTypeApplyBulletedLists();
	void SetAutoFormatAsYouTypeApplyBulletedLists(BOOL bNewValue);
	BOOL GetAutoFormatAsYouTypeApplyNumberedLists();
	void SetAutoFormatAsYouTypeApplyNumberedLists(BOOL bNewValue);
	BOOL GetAutoFormatAsYouTypeReplaceQuotes();
	void SetAutoFormatAsYouTypeReplaceQuotes(BOOL bNewValue);
	BOOL GetAutoFormatAsYouTypeReplaceSymbols();
	void SetAutoFormatAsYouTypeReplaceSymbols(BOOL bNewValue);
	BOOL GetAutoFormatAsYouTypeReplaceOrdinals();
	void SetAutoFormatAsYouTypeReplaceOrdinals(BOOL bNewValue);
	BOOL GetAutoFormatAsYouTypeReplaceFractions();
	void SetAutoFormatAsYouTypeReplaceFractions(BOOL bNewValue);
	BOOL GetAutoFormatAsYouTypeReplacePlainTextEmphasis();
	void SetAutoFormatAsYouTypeReplacePlainTextEmphasis(BOOL bNewValue);
	BOOL GetAutoFormatAsYouTypeFormatListItemBeginning();
	void SetAutoFormatAsYouTypeFormatListItemBeginning(BOOL bNewValue);
	BOOL GetAutoFormatAsYouTypeDefineStyles();
	void SetAutoFormatAsYouTypeDefineStyles(BOOL bNewValue);
	BOOL GetAutoFormatPlainTextWordMail();
	void SetAutoFormatPlainTextWordMail(BOOL bNewValue);
	BOOL GetAutoFormatAsYouTypeReplaceHyperlinks();
	void SetAutoFormatAsYouTypeReplaceHyperlinks(BOOL bNewValue);
	BOOL GetAutoFormatReplaceHyperlinks();
	void SetAutoFormatReplaceHyperlinks(BOOL bNewValue);
	long GetDefaultHighlightColorIndex();
	void SetDefaultHighlightColorIndex(long nNewValue);
	long GetDefaultBorderLineStyle();
	void SetDefaultBorderLineStyle(long nNewValue);
	BOOL GetCheckSpellingAsYouType();
	void SetCheckSpellingAsYouType(BOOL bNewValue);
	BOOL GetCheckGrammarAsYouType();
	void SetCheckGrammarAsYouType(BOOL bNewValue);
	BOOL GetIgnoreInternetAndFileAddresses();
	void SetIgnoreInternetAndFileAddresses(BOOL bNewValue);
	BOOL GetShowReadabilityStatistics();
	void SetShowReadabilityStatistics(BOOL bNewValue);
	BOOL GetIgnoreUppercase();
	void SetIgnoreUppercase(BOOL bNewValue);
	BOOL GetIgnoreMixedDigits();
	void SetIgnoreMixedDigits(BOOL bNewValue);
	BOOL GetSuggestFromMainDictionaryOnly();
	void SetSuggestFromMainDictionaryOnly(BOOL bNewValue);
	BOOL GetSuggestSpellingCorrections();
	void SetSuggestSpellingCorrections(BOOL bNewValue);
	long GetDefaultBorderLineWidth();
	void SetDefaultBorderLineWidth(long nNewValue);
	BOOL GetCheckGrammarWithSpelling();
	void SetCheckGrammarWithSpelling(BOOL bNewValue);
	long GetDefaultOpenFormat();
	void SetDefaultOpenFormat(long nNewValue);
	BOOL GetPrintDraft();
	void SetPrintDraft(BOOL bNewValue);
	BOOL GetPrintReverse();
	void SetPrintReverse(BOOL bNewValue);
	BOOL GetMapPaperSize();
	void SetMapPaperSize(BOOL bNewValue);
	BOOL GetAutoFormatAsYouTypeApplyTables();
	void SetAutoFormatAsYouTypeApplyTables(BOOL bNewValue);
	long GetDefaultBorderColorIndex();
	void SetDefaultBorderColorIndex(long nNewValue);
	void SetWPHelpOptions(VARIANT* CommandKeyHelp, VARIANT* DocNavigationKeys, VARIANT* MouseSimulation, VARIANT* DemoGuidance, VARIANT* DemoSpeed, VARIANT* HelpType);
};
/////////////////////////////////////////////////////////////////////////////
// MailMessage wrapper class

class MailMessage : public COleDispatchDriver
{
public:
	MailMessage() {}		// Calls COleDispatchDriver default constructor
	MailMessage(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	MailMessage(const MailMessage& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	void CheckName();
	void Delete();
	void DisplayMoveDialog();
	void DisplayProperties();
	void DisplaySelectNamesDialog();
	void Forward();
	void GoToNext();
	void GoToPrevious();
	void Reply();
	void ReplyAll();
	void ToggleHeader();
};
/////////////////////////////////////////////////////////////////////////////
// ProofreadingErrors wrapper class

class ProofreadingErrors : public COleDispatchDriver
{
public:
	ProofreadingErrors() {}		// Calls COleDispatchDriver default constructor
	ProofreadingErrors(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ProofreadingErrors(const ProofreadingErrors& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	long GetType();
	LPDISPATCH Item(long Index);
};
/////////////////////////////////////////////////////////////////////////////
// Mailer wrapper class

class Mailer : public COleDispatchDriver
{
public:
	Mailer() {}		// Calls COleDispatchDriver default constructor
	Mailer(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Mailer(const Mailer& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	VARIANT GetBCCRecipients();
	void SetBCCRecipients(VARIANT* newValue);
	VARIANT GetCCRecipients();
	void SetCCRecipients(VARIANT* newValue);
	VARIANT GetRecipients();
	void SetRecipients(VARIANT* newValue);
	VARIANT GetEnclosures();
	void SetEnclosures(VARIANT* newValue);
	CString GetSender();
	DATE GetSendDateTime();
	BOOL GetReceived();
	CString GetSubject();
	void SetSubject(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// WrapFormat wrapper class

class WrapFormat : public COleDispatchDriver
{
public:
	WrapFormat() {}		// Calls COleDispatchDriver default constructor
	WrapFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	WrapFormat(const WrapFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetType();
	void SetType(long nNewValue);
	long GetSide();
	void SetSide(long nNewValue);
	float GetDistanceTop();
	void SetDistanceTop(float newValue);
	float GetDistanceBottom();
	void SetDistanceBottom(float newValue);
	float GetDistanceLeft();
	void SetDistanceLeft(float newValue);
	float GetDistanceRight();
	void SetDistanceRight(float newValue);
};
/////////////////////////////////////////////////////////////////////////////
// HangulAndAlphabetExceptions wrapper class

class HangulAndAlphabetExceptions : public COleDispatchDriver
{
public:
	HangulAndAlphabetExceptions() {}		// Calls COleDispatchDriver default constructor
	HangulAndAlphabetExceptions(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	HangulAndAlphabetExceptions(const HangulAndAlphabetExceptions& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPUNKNOWN Get_NewEnum();
	long GetCount();
	LPDISPATCH Item(VARIANT* Index);
	LPDISPATCH Add(LPCTSTR Name);
};
/////////////////////////////////////////////////////////////////////////////
// HangulAndAlphabetException wrapper class

class HangulAndAlphabetException : public COleDispatchDriver
{
public:
	HangulAndAlphabetException() {}		// Calls COleDispatchDriver default constructor
	HangulAndAlphabetException(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	HangulAndAlphabetException(const HangulAndAlphabetException& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetIndex();
	CString GetName();
	void Delete();
};
/////////////////////////////////////////////////////////////////////////////
// Adjustments wrapper class

class Adjustments : public COleDispatchDriver
{
public:
	Adjustments() {}		// Calls COleDispatchDriver default constructor
	Adjustments(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Adjustments(const Adjustments& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetCount();
	float GetItem(long Index);
	void SetItem(long Index, float newValue);
};
/////////////////////////////////////////////////////////////////////////////
// CalloutFormat wrapper class

class CalloutFormat : public COleDispatchDriver
{
public:
	CalloutFormat() {}		// Calls COleDispatchDriver default constructor
	CalloutFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CalloutFormat(const CalloutFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetAccent();
	void SetAccent(long nNewValue);
	long GetAngle();
	void SetAngle(long nNewValue);
	long GetAutoAttach();
	void SetAutoAttach(long nNewValue);
	long GetAutoLength();
	long GetBorder();
	void SetBorder(long nNewValue);
	float GetDrop();
	long GetDropType();
	float GetGap();
	void SetGap(float newValue);
	float GetLength();
	long GetType();
	void SetType(long nNewValue);
	void AutomaticLength();
	void CustomDrop(float Drop);
	void CustomLength(float Length);
	void PresetDrop(long DropType);
};
/////////////////////////////////////////////////////////////////////////////
// ColorFormat wrapper class

class ColorFormat : public COleDispatchDriver
{
public:
	ColorFormat() {}		// Calls COleDispatchDriver default constructor
	ColorFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ColorFormat(const ColorFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetRgb();
	void SetRgb(long nNewValue);
	long GetType();
};
/////////////////////////////////////////////////////////////////////////////
// ConnectorFormat wrapper class

class ConnectorFormat : public COleDispatchDriver
{
public:
	ConnectorFormat() {}		// Calls COleDispatchDriver default constructor
	ConnectorFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ConnectorFormat(const ConnectorFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	long GetBeginConnected();
	LPDISPATCH GetBeginConnectedShape();
	long GetBeginConnectionSite();
	long GetEndConnected();
	LPDISPATCH GetEndConnectedShape();
	long GetEndConnectionSite();
	LPDISPATCH GetParent();
	long GetType();
	void SetType(long nNewValue);
	void BeginConnect(LPDISPATCH* ConnectedShape, long ConnectionSite);
	void BeginDisconnect();
	void EndConnect(LPDISPATCH* ConnectedShape, long ConnectionSite);
	void EndDisconnect();
};
/////////////////////////////////////////////////////////////////////////////
// FillFormat wrapper class

class FillFormat : public COleDispatchDriver
{
public:
	FillFormat() {}		// Calls COleDispatchDriver default constructor
	FillFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	FillFormat(const FillFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH GetBackColor();
	LPDISPATCH GetForeColor();
	long GetGradientColorType();
	float GetGradientDegree();
	long GetGradientStyle();
	long GetGradientVariant();
	long GetPattern();
	long GetPresetGradientType();
	long GetPresetTexture();
	CString GetTextureName();
	long GetTextureType();
	float GetTransparency();
	void SetTransparency(float newValue);
	long GetType();
	long GetVisible();
	void SetVisible(long nNewValue);
	void OneColorGradient(long Style, long Variant, float Degree);
	void Patterned(long Pattern);
	void PresetGradient(long Style, long Variant, long PresetGradientType);
	void PresetTextured(long PresetTexture);
	void Solid();
	void TwoColorGradient(long Style, long Variant);
	void UserPicture(LPCTSTR PictureFile);
	void UserTextured(LPCTSTR TextureFile);
};
/////////////////////////////////////////////////////////////////////////////
// FreeformBuilder wrapper class

class FreeformBuilder : public COleDispatchDriver
{
public:
	FreeformBuilder() {}		// Calls COleDispatchDriver default constructor
	FreeformBuilder(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	FreeformBuilder(const FreeformBuilder& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	void AddNodes(long SegmentType, long EditingType, float X1, float Y1, float X2, float Y2, float X3, float Y3);
	LPDISPATCH ConvertToShape(VARIANT* Anchor);
};
/////////////////////////////////////////////////////////////////////////////
// LineFormat wrapper class

class LineFormat : public COleDispatchDriver
{
public:
	LineFormat() {}		// Calls COleDispatchDriver default constructor
	LineFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	LineFormat(const LineFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH GetBackColor();
	long GetBeginArrowheadLength();
	void SetBeginArrowheadLength(long nNewValue);
	long GetBeginArrowheadStyle();
	void SetBeginArrowheadStyle(long nNewValue);
	long GetBeginArrowheadWidth();
	void SetBeginArrowheadWidth(long nNewValue);
	long GetDashStyle();
	void SetDashStyle(long nNewValue);
	long GetEndArrowheadLength();
	void SetEndArrowheadLength(long nNewValue);
	long GetEndArrowheadStyle();
	void SetEndArrowheadStyle(long nNewValue);
	long GetEndArrowheadWidth();
	void SetEndArrowheadWidth(long nNewValue);
	LPDISPATCH GetForeColor();
	long GetPattern();
	void SetPattern(long nNewValue);
	long GetStyle();
	void SetStyle(long nNewValue);
	float GetTransparency();
	void SetTransparency(float newValue);
	long GetVisible();
	void SetVisible(long nNewValue);
	float GetWeight();
	void SetWeight(float newValue);
};
/////////////////////////////////////////////////////////////////////////////
// PictureFormat wrapper class

class PictureFormat : public COleDispatchDriver
{
public:
	PictureFormat() {}		// Calls COleDispatchDriver default constructor
	PictureFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PictureFormat(const PictureFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	float GetBrightness();
	void SetBrightness(float newValue);
	long GetColorType();
	void SetColorType(long nNewValue);
	float GetContrast();
	void SetContrast(float newValue);
	float GetCropBottom();
	void SetCropBottom(float newValue);
	float GetCropLeft();
	void SetCropLeft(float newValue);
	float GetCropRight();
	void SetCropRight(float newValue);
	float GetCropTop();
	void SetCropTop(float newValue);
	long GetTransparencyColor();
	void SetTransparencyColor(long nNewValue);
	long GetTransparentBackground();
	void SetTransparentBackground(long nNewValue);
	void IncrementBrightness(float Increment);
	void IncrementContrast(float Increment);
};
/////////////////////////////////////////////////////////////////////////////
// ShadowFormat wrapper class

class ShadowFormat : public COleDispatchDriver
{
public:
	ShadowFormat() {}		// Calls COleDispatchDriver default constructor
	ShadowFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ShadowFormat(const ShadowFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH GetForeColor();
	long GetObscured();
	void SetObscured(long nNewValue);
	float GetOffsetX();
	void SetOffsetX(float newValue);
	float GetOffsetY();
	void SetOffsetY(float newValue);
	float GetTransparency();
	void SetTransparency(float newValue);
	long GetType();
	void SetType(long nNewValue);
	long GetVisible();
	void SetVisible(long nNewValue);
	void IncrementOffsetX(float Increment);
	void IncrementOffsetY(float Increment);
};
/////////////////////////////////////////////////////////////////////////////
// ShapeNode wrapper class

class ShapeNode : public COleDispatchDriver
{
public:
	ShapeNode() {}		// Calls COleDispatchDriver default constructor
	ShapeNode(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ShapeNode(const ShapeNode& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetEditingType();
	VARIANT GetPoints();
	long GetSegmentType();
};
/////////////////////////////////////////////////////////////////////////////
// ShapeNodes wrapper class

class ShapeNodes : public COleDispatchDriver
{
public:
	ShapeNodes() {}		// Calls COleDispatchDriver default constructor
	ShapeNodes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ShapeNodes(const ShapeNodes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetCount();
	LPUNKNOWN Get_NewEnum();
	void Delete(long Index);
	LPDISPATCH Item(VARIANT* Index);
	void SetEditingType(long Index, long EditingType);
	void SetPosition(long Index, float X1, float Y1);
	void SetSegmentType(long Index, long SegmentType);
	void Insert(long Index, long SegmentType, long EditingType, float X1, float Y1, float X2, float Y2, float X3, float Y3);
};
/////////////////////////////////////////////////////////////////////////////
// TextEffectFormat wrapper class

class TextEffectFormat : public COleDispatchDriver
{
public:
	TextEffectFormat() {}		// Calls COleDispatchDriver default constructor
	TextEffectFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	TextEffectFormat(const TextEffectFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetAlignment();
	void SetAlignment(long nNewValue);
	long GetFontBold();
	void SetFontBold(long nNewValue);
	long GetFontItalic();
	void SetFontItalic(long nNewValue);
	CString GetFontName();
	void SetFontName(LPCTSTR lpszNewValue);
	float GetFontSize();
	void SetFontSize(float newValue);
	long GetKernedPairs();
	void SetKernedPairs(long nNewValue);
	long GetNormalizedHeight();
	void SetNormalizedHeight(long nNewValue);
	long GetPresetShape();
	void SetPresetShape(long nNewValue);
	long GetPresetTextEffect();
	void SetPresetTextEffect(long nNewValue);
	long GetRotatedChars();
	void SetRotatedChars(long nNewValue);
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	float GetTracking();
	void SetTracking(float newValue);
	void ToggleVerticalText();
};
/////////////////////////////////////////////////////////////////////////////
// ThreeDFormat wrapper class

class ThreeDFormat : public COleDispatchDriver
{
public:
	ThreeDFormat() {}		// Calls COleDispatchDriver default constructor
	ThreeDFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ThreeDFormat(const ThreeDFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	float GetDepth();
	void SetDepth(float newValue);
	LPDISPATCH GetExtrusionColor();
	long GetExtrusionColorType();
	void SetExtrusionColorType(long nNewValue);
	long GetPerspective();
	void SetPerspective(long nNewValue);
	long GetPresetExtrusionDirection();
	long GetPresetLightingDirection();
	void SetPresetLightingDirection(long nNewValue);
	long GetPresetLightingSoftness();
	void SetPresetLightingSoftness(long nNewValue);
	long GetPresetMaterial();
	void SetPresetMaterial(long nNewValue);
	long GetPresetThreeDFormat();
	float GetRotationX();
	void SetRotationX(float newValue);
	float GetRotationY();
	void SetRotationY(float newValue);
	long GetVisible();
	void SetVisible(long nNewValue);
	void IncrementRotationX(float Increment);
	void IncrementRotationY(float Increment);
	void ResetRotation();
	void SetExtrusionDirection(long PresetExtrusionDirection);
	void SetThreeDFormat(long PresetThreeDFormat);
};
/////////////////////////////////////////////////////////////////////////////
// ApplicationEvents wrapper class

class ApplicationEvents : public COleDispatchDriver
{
public:
	ApplicationEvents() {}		// Calls COleDispatchDriver default constructor
	ApplicationEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ApplicationEvents(const ApplicationEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void Quit();
	void DocumentChange();
};
/////////////////////////////////////////////////////////////////////////////
// DocumentEvents wrapper class

class DocumentEvents : public COleDispatchDriver
{
public:
	DocumentEvents() {}		// Calls COleDispatchDriver default constructor
	DocumentEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DocumentEvents(const DocumentEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void New();
	void Open();
	void Close();
};
/////////////////////////////////////////////////////////////////////////////
// OCXEvents wrapper class

class OCXEvents : public COleDispatchDriver
{
public:
	OCXEvents() {}		// Calls COleDispatchDriver default constructor
	OCXEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	OCXEvents(const OCXEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void GotFocus();
	void LostFocus();
};

}; // namespace Word