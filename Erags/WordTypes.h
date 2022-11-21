#if !defined(WORDTYPES_H_INCLUDED)
#define WORDTYPES_H_INCLUDED

typedef enum {
    wdNoMailSystem = 0,
    wdMAPI = 1,
    wdPowerTalk = 2,
    wdMAPIandPowerTalk = 3
} WdMailSystem;

typedef enum {
    wdNormalTemplate = 0,
    wdGlobalTemplate = 1,
    wdAttachedTemplate = 2
} WdTemplateType;

typedef enum {
    wdContinueDisabled = 0,
    wdResetList = 1,
    wdContinueList = 2
} WdContinue;

typedef enum {
    wdIMEModeNoControl = 0,
    wdIMEModeOn = 1,
    wdIMEModeOff = 2,
    wdIMEModeHiragana = 4,
    wdIMEModeKatakana = 5,
    wdIMEModeKatakanaHalf = 6,
    wdIMEModeAlphaFull = 7,
    wdIMEModeAlpha = 8,
    wdIMEModeHangulFull = 9,
    wdIMEModeHangul = 10
} WdIMEMode;

typedef enum {
    wdBaselineAlignTop = 0,
    wdBaselineAlignCenter = 1,
    wdBaselineAlignBaseline = 2,
    wdBaselineAlignFarEast50 = 3,
    wdBaselineAlignAuto = 4
} WdBaselineAlignment;

typedef enum {
    wdIndexFilterNone = 0,
    wdIndexFilterAiueo = 1,
    wdIndexFilterAkasatana = 2,
    wdIndexFilterChosung = 3,
    wdIndexFilterLow = 4,
    wdIndexFilterMedium = 5,
    wdIndexFilterFull = 6
} WdIndexFilter;

typedef enum {
    wdIndexSortByStroke = 0,
    wdIndexSortBySyllable = 1
} WdIndexSortBy;

typedef enum {
    wdJustificationModeExpand = 0,
    wdJustificationModeCompress = 1,
    wdJustificationModeCompressKana = 2
} WdJustificationMode;

typedef enum {
    wdFarEastLineBreakLevelNormal = 0,
    wdFarEastLineBreakLevelStrict = 1,
    wdFarEastLineBreakLevelCustom = 2
} WdFarEastLineBreakLevel;

typedef enum {
    wdHangulToHanja = 0,
    wdHanjaToHangul = 1
} WdMultipleWordConversionsMode;

typedef enum {
    wdAuto = 0,
    wdBlack = 1,
    wdBlue = 2,
    wdTurquoise = 3,
    wdBrightGreen = 4,
    wdPink = 5,
    wdRed = 6,
    wdYellow = 7,
    wdWhite = 8,
    wdDarkBlue = 9,
    wdTeal = 10,
    wdGreen = 11,
    wdViolet = 12,
    wdDarkRed = 13,
    wdDarkYellow = 14,
    wdGray50 = 15,
    wdGray25 = 16,
    wdByAuthor = -1,
    wdNoHighlight = 0
} WdColorIndex;

typedef enum {
    wdTextureNone = 0,
    wdTexture2Pt5Percent = 25,
    wdTexture5Percent = 50,
    wdTexture7Pt5Percent = 75,
    wdTexture10Percent = 100,
    wdTexture12Pt5Percent = 125,
    wdTexture15Percent = 150,
    wdTexture17Pt5Percent = 175,
    wdTexture20Percent = 200,
    wdTexture22Pt5Percent = 225,
    wdTexture25Percent = 250,
    wdTexture27Pt5Percent = 275,
    wdTexture30Percent = 300,
    wdTexture32Pt5Percent = 325,
    wdTexture35Percent = 350,
    wdTexture37Pt5Percent = 375,
    wdTexture40Percent = 400,
    wdTexture42Pt5Percent = 425,
    wdTexture45Percent = 450,
    wdTexture47Pt5Percent = 475,
    wdTexture50Percent = 500,
    wdTexture52Pt5Percent = 525,
    wdTexture55Percent = 550,
    wdTexture57Pt5Percent = 575,
    wdTexture60Percent = 600,
    wdTexture62Pt5Percent = 625,
    wdTexture65Percent = 650,
    wdTexture67Pt5Percent = 675,
    wdTexture70Percent = 700,
    wdTexture72Pt5Percent = 725,
    wdTexture75Percent = 750,
    wdTexture77Pt5Percent = 775,
    wdTexture80Percent = 800,
    wdTexture82Pt5Percent = 825,
    wdTexture85Percent = 850,
    wdTexture87Pt5Percent = 875,
    wdTexture90Percent = 900,
    wdTexture92Pt5Percent = 925,
    wdTexture95Percent = 950,
    wdTexture97Pt5Percent = 975,
    wdTextureSolid = 1000,
    wdTextureDarkHorizontal = -1,
    wdTextureDarkVertical = -2,
    wdTextureDarkDiagonalDown = -3,
    wdTextureDarkDiagonalUp = -4,
    wdTextureDarkCross = -5,
    wdTextureDarkDiagonalCross = -6,
    wdTextureHorizontal = -7,
    wdTextureVertical = -8,
    wdTextureDiagonalDown = -9,
    wdTextureDiagonalUp = -10,
    wdTextureCross = -11,
    wdTextureDiagonalCross = -12
} WdTextureIndex;

typedef enum {
    wdUnderlineNone = 0,
    wdUnderlineSingle = 1,
    wdUnderlineWords = 2,
    wdUnderlineDouble = 3,
    wdUnderlineDotted = 4,
    wdUnderlineThick = 6,
    wdUnderlineDash = 7,
    wdUnderlineDotDash = 9,
    wdUnderlineDotDotDash = 10,
    wdUnderlineWavy = 11
} WdUnderline;

typedef enum {
    wdEmphasisMarkNone = 0,
    wdEmphasisMarkOverSolidCircle = 1,
    wdEmphasisMarkOverComma = 2,
    wdEmphasisMarkOverWhiteCircle = 3,
    wdEmphasisMarkUnderSolidCircle = 4
} WdEmphasisMark;

typedef enum {
    wdListSeparator = 17,
    wdDecimalSeparator = 18,
    wdThousandsSeparator = 19,
    wdCurrencyCode = 20,
    wd24HourClock = 21,
    wdInternationalAM = 22,
    wdInternationalPM = 23,
    wdTimeSeparator = 24,
    wdDateSeparator = 25,
    wdProductLanguageID = 26
} WdInternationalIndex;

typedef enum {
    wdAutoExec = 0,
    wdAutoNew = 1,
    wdAutoOpen = 2,
    wdAutoClose = 3,
    wdAutoExit = 4
} WdAutoMacros;

typedef enum {
    wdCaptionPositionAbove = 0,
    wdCaptionPositionBelow = 1
} WdCaptionPosition;

typedef enum {
    wdUS = 1,
    wdCanada = 2,
    wdLatinAmerica = 3,
    wdNetherlands = 31,
    wdFrance = 33,
    wdSpain = 34,
    wdItaly = 39,
    wdUK = 44,
    wdDenmark = 45,
    wdSweden = 46,
    wdNorway = 47,
    wdGermany = 49,
    wdPeru = 51,
    wdMexico = 52,
    wdArgentina = 54,
    wdBrazil = 55,
    wdChile = 56,
    wdVenezuela = 58,
    wdJapan = 81,
    wdTaiwan = 886,
    wdChina = 86,
    wdKorea = 82,
    wdFinland = 358,
    wdIceland = 354
} WdCountry;

typedef enum {
    wdHeadingSeparatorNone = 0,
    wdHeadingSeparatorBlankLine = 1,
    wdHeadingSeparatorLetter = 2,
    wdHeadingSeparatorLetterLow = 3,
    wdHeadingSeparatorLetterFull = 4
} WdHeadingSeparator;

typedef enum {
    wdSeparatorHyphen = 0,
    wdSeparatorPeriod = 1,
    wdSeparatorColon = 2,
    wdSeparatorEmDash = 3,
    wdSeparatorEnDash = 4
} WdSeparatorType;

typedef enum {
    wdAlignPageNumberLeft = 0,
    wdAlignPageNumberCenter = 1,
    wdAlignPageNumberRight = 2,
    wdAlignPageNumberInside = 3,
    wdAlignPageNumberOutside = 4
} WdPageNumberAlignment;

typedef enum {
    wdBorderTop = -1,
    wdBorderLeft = -2,
    wdBorderBottom = -3,
    wdBorderRight = -4,
    wdBorderHorizontal = -5,
    wdBorderVertical = -6
} WdBorderType;

typedef enum {
    wdBorderDiagonalDown = -7,
    wdBorderDiagonalUp = -8
} WdBorderTypeHID;

typedef enum {
    wdFrameTop = -999999,
    wdFrameLeft = -999998,
    wdFrameBottom = -999997,
    wdFrameRight = -999996,
    wdFrameCenter = -999995,
    wdFrameInside = -999994,
    wdFrameOutside = -999993
} WdFramePosition;

typedef enum {
    wdAnimationNone = 0,
    wdAnimationLasVegasLights = 1,
    wdAnimationBlinkingBackground = 2,
    wdAnimationSparkleText = 3,
    wdAnimationMarchingBlackAnts = 4,
    wdAnimationMarchingRedAnts = 5,
    wdAnimationShimmer = 6
} WdAnimation;

typedef enum {
    wdNextCase = -1,
    wdLowerCase = 0,
    wdUpperCase = 1,
    wdTitleWord = 2,
    wdTitleSentence = 4,
    wdToggleCase = 5
} WdCharacterCase;

typedef enum {
    wdHalfWidth = 6,
    wdFullWidth = 7,
    wdKatakana = 8,
    wdHiragana = 9
} WdCharacterCaseHID;

typedef enum {
    wdSummaryModeHighlight = 0,
    wdSummaryModeHideAllButSummary = 1,
    wdSummaryModeInsert = 2,
    wdSummaryModeCreateNew = 3
} WdSummaryMode;

typedef enum {
    wd10Sentences = -2,
    wd20Sentences = -3,
    wd100Words = -4,
    wd500Words = -5,
    wd10Percent = -6,
    wd25Percent = -7,
    wd50Percent = -8,
    wd75Percent = -9
} WdSummaryLength;

typedef enum {
    wdStyleTypeParagraph = 1,
    wdStyleTypeCharacter = 2
} WdStyleType;

typedef enum {
    wdCharacter = 1,
    wdWord = 2,
    wdSentence = 3,
    wdParagraph = 4,
    wdLine = 5,
    wdStory = 6,
    wdScreen = 7,
    wdSection = 8,
    wdColumn = 9,
    wdRow = 10,
    wdWindow = 11,
    wdCell = 12,
    wdCharacterFormatting = 13,
    wdParagraphFormatting = 14,
    wdTable = 15,
    wdItem = 16
} WdUnits;

typedef enum {
    wdGoToBookmark = -1,
    wdGoToSection = 0,
    wdGoToPage = 1,
    wdGoToTable = 2,
    wdGoToLine = 3,
    wdGoToFootnote = 4,
    wdGoToEndnote = 5,
    wdGoToComment = 6,
    wdGoToField = 7,
    wdGoToGraphic = 8,
    wdGoToObject = 9,
    wdGoToEquation = 10,
    wdGoToHeading = 11,
    wdGoToPercent = 12,
    wdGoToSpellingError = 13,
    wdGoToGrammaticalError = 14,
    wdGoToProofreadingError = 15
} WdGoToItem;

typedef enum {
    wdGoToFirst = 1,
    wdGoToLast = -1,
    wdGoToNext = 2,
    wdGoToRelative = 2,
    wdGoToPrevious = 3,
    wdGoToAbsolute = 1
} WdGoToDirection;

typedef enum {
    wdCollapseStart = 1,
    wdCollapseEnd = 0
} WdCollapseDirection;

typedef enum {
    wdRowHeightAuto = 0,
    wdRowHeightAtLeast = 1,
    wdRowHeightExactly = 2
} WdRowHeightRule;

typedef enum {
    wdFrameAuto = 0,
    wdFrameAtLeast = 1,
    wdFrameExact = 2
} WdFrameSizeRule;

typedef enum {
    wdInsertCellsShiftRight = 0,
    wdInsertCellsShiftDown = 1,
    wdInsertCellsEntireRow = 2,
    wdInsertCellsEntireColumn = 3
} WdInsertCells;

typedef enum {
    wdDeleteCellsShiftLeft = 0,
    wdDeleteCellsShiftUp = 1,
    wdDeleteCellsEntireRow = 2,
    wdDeleteCellsEntireColumn = 3
} WdDeleteCells;

typedef enum {
    wdListApplyToWholeList = 0,
    wdListApplyToThisPointForward = 1,
    wdListApplyToSelection = 2
} WdListApplyTo;

typedef enum {
    wdAlertsNone = 0,
    wdAlertsMessageBox = -2,
    wdAlertsAll = -1
} WdAlertLevel;

typedef enum {
    wdCursorWait = 0,
    wdCursorIBeam = 1,
    wdCursorNormal = 2,
    wdCursorNorthwestArrow = 3
} WdCursorType;

typedef enum {
    wdCancelDisabled = 0,
    wdCancelInterrupt = 1
} WdEnableCancelKey;

typedef enum {
    wdAdjustNone = 0,
    wdAdjustProportional = 1,
    wdAdjustFirstColumn = 2,
    wdAdjustSameWidth = 3
} WdRulerStyle;

typedef enum {
    wdAlignParagraphLeft = 0,
    wdAlignParagraphCenter = 1,
    wdAlignParagraphRight = 2,
    wdAlignParagraphJustify = 3
} WdParagraphAlignment;

typedef enum {
    wdAlignParagraphDistribute = 4
} WdParagraphAlignmentHID;

typedef enum {
    wdListLevelAlignLeft = 0,
    wdListLevelAlignCenter = 1,
    wdListLevelAlignRight = 2
} WdListLevelAlignment;

typedef enum {
    wdAlignRowLeft = 0,
    wdAlignRowCenter = 1,
    wdAlignRowRight = 2
} WdRowAlignment;

typedef enum {
    wdAlignTabLeft = 0,
    wdAlignTabCenter = 1,
    wdAlignTabRight = 2,
    wdAlignTabDecimal = 3,
    wdAlignTabBar = 4,
    wdAlignTabList = 6
} WdTabAlignment;

typedef enum {
    wdAlignVerticalTop = 0,
    wdAlignVerticalCenter = 1,
    wdAlignVerticalJustify = 2,
    wdAlignVerticalBottom = 3
} WdVerticalAlignment;

typedef enum {
    wdCellAlignVerticalTop = 0,
    wdCellAlignVerticalCenter = 1,
    wdCellAlignVerticalBottom = 3
} WdCellVerticalAlignment;

typedef enum {
    wdTrailingTab = 0,
    wdTrailingSpace = 1,
    wdTrailingNone = 2
} WdTrailingCharacter;

typedef enum {
    wdBulletGallery = 1,
    wdNumberGallery = 2,
    wdOutlineNumberGallery = 3
} WdListGalleryType;

typedef enum {
    wdListNumberStyleArabic = 0,
    wdListNumberStyleUppercaseRoman = 1,
    wdListNumberStyleLowercaseRoman = 2,
    wdListNumberStyleUppercaseLetter = 3,
    wdListNumberStyleLowercaseLetter = 4,
    wdListNumberStyleOrdinal = 5,
    wdListNumberStyleCardinalText = 6,
    wdListNumberStyleOrdinalText = 7,
    wdListNumberStyleArabicLZ = 22,
    wdListNumberStyleBullet = 23,
    wdListNumberStyleLegal = 253,
    wdListNumberStyleLegalLZ = 254,
    wdListNumberStyleNone = 255
} WdListNumberStyle;

typedef enum {
    wdListNumberStyleKanji = 10,
    wdListNumberStyleKanjiDigit = 11,
    wdListNumberStyleAiueoHalfWidth = 12,
    wdListNumberStyleIrohaHalfWidth = 13,
    wdListNumberStyleArabicFullWidth = 14,
    wdListNumberStyleKanjiTraditional = 16,
    wdListNumberStyleKanjiTraditional2 = 17,
    wdListNumberStyleNumberInCircle = 18,
    wdListNumberStyleAiueo = 20,
    wdListNumberStyleIroha = 21,
    wdListNumberStyleGanada = 24,
    wdListNumberStyleChosung = 25,
    wdListNumberStyleGBNum1 = 26,
    wdListNumberStyleGBNum2 = 27,
    wdListNumberStyleGBNum3 = 28,
    wdListNumberStyleGBNum4 = 29,
    wdListNumberStyleZodiac1 = 30,
    wdListNumberStyleZodiac2 = 31,
    wdListNumberStyleZodiac3 = 32,
    wdListNumberStyleTradChinNum1 = 33,
    wdListNumberStyleTradChinNum2 = 34,
    wdListNumberStyleTradChinNum3 = 35,
    wdListNumberStyleTradChinNum4 = 36,
    wdListNumberStyleSimpChinNum1 = 37,
    wdListNumberStyleSimpChinNum2 = 38,
    wdListNumberStyleSimpChinNum3 = 39,
    wdListNumberStyleSimpChinNum4 = 40,
    wdListNumberStyleHanjaRead = 41,
    wdListNumberStyleHanjaReadDigit = 42,
    wdListNumberStyleHangul = 43,
    wdListNumberStyleHanja = 44
} WdListNumberStyleHID;

typedef enum {
    wdNoteNumberStyleArabic = 0,
    wdNoteNumberStyleUppercaseRoman = 1,
    wdNoteNumberStyleLowercaseRoman = 2,
    wdNoteNumberStyleUppercaseLetter = 3,
    wdNoteNumberStyleLowercaseLetter = 4,
    wdNoteNumberStyleSymbol = 9
} WdNoteNumberStyle;

typedef enum {
    wdNoteNumberStyleArabicFullWidth = 14,
    wdNoteNumberStyleKanji = 10,
    wdNoteNumberStyleKanjiDigit = 11,
    wdNoteNumberStyleKanjiTraditional = 16,
    wdNoteNumberStyleNumberInCircle = 18,
    wdNoteNumberStyleHanjaRead = 41,
    wdNoteNumberStyleHanjaReadDigit = 42,
    wdNoteNumberStyleTradChinNum1 = 33,
    wdNoteNumberStyleTradChinNum2 = 34,
    wdNoteNumberStyleSimpChinNum1 = 37,
    wdNoteNumberStyleSimpChinNum2 = 38
} WdNoteNumberStyleHID;

typedef enum {
    wdCaptionNumberStyleArabic = 0,
    wdCaptionNumberStyleUppercaseRoman = 1,
    wdCaptionNumberStyleLowercaseRoman = 2,
    wdCaptionNumberStyleUppercaseLetter = 3,
    wdCaptionNumberStyleLowercaseLetter = 4
} WdCaptionNumberStyle;

typedef enum {
    wdCaptionNumberStyleArabicFullWidth = 14,
    wdCaptionNumberStyleKanji = 10,
    wdCaptionNumberStyleKanjiDigit = 11,
    wdCaptionNumberStyleKanjiTraditional = 16,
    wdCaptionNumberStyleNumberInCircle = 18,
    wdCaptionNumberStyleGanada = 24,
    wdCaptionNumberStyleChosung = 25,
    wdCaptionNumberStyleZodiac1 = 30,
    wdCaptionNumberStyleZodiac2 = 31,
    wdCaptionNumberStyleHanjaRead = 41,
    wdCaptionNumberStyleHanjaReadDigit = 42,
    wdCaptionNumberStyleTradChinNum2 = 34,
    wdCaptionNumberStyleTradChinNum3 = 35,
    wdCaptionNumberStyleSimpChinNum2 = 38,
    wdCaptionNumberStyleSimpChinNum3 = 39
} WdCaptionNumberStyleHID;

typedef enum {
    wdPageNumberStyleArabic = 0,
    wdPageNumberStyleUppercaseRoman = 1,
    wdPageNumberStyleLowercaseRoman = 2,
    wdPageNumberStyleUppercaseLetter = 3,
    wdPageNumberStyleLowercaseLetter = 4
} WdPageNumberStyle;

typedef enum {
    wdPageNumberStyleArabicFullWidth = 14,
    wdPageNumberStyleKanji = 10,
    wdPageNumberStyleKanjiDigit = 11,
    wdPageNumberStyleKanjiTraditional = 16,
    wdPageNumberStyleNumberInCircle = 18,
    wdPageNumberStyleHanjaRead = 41,
    wdPageNumberStyleHanjaReadDigit = 42,
    wdPageNumberStyleTradChinNum1 = 33,
    wdPageNumberStyleTradChinNum2 = 34,
    wdPageNumberStyleSimpChinNum1 = 37,
    wdPageNumberStyleSimpChinNum2 = 38
} WdPageNumberStyleHID;

typedef enum {
    wdStatisticWords = 0,
    wdStatisticLines = 1,
    wdStatisticPages = 2,
    wdStatisticCharacters = 3,
    wdStatisticParagraphs = 4,
    wdStatisticCharactersWithSpaces = 5
} WdStatistic;

typedef enum {
    wdStatisticFarEastCharacters = 6
} WdStatisticHID;

typedef enum {
    wdPropertyTitle = 1,
    wdPropertySubject = 2,
    wdPropertyAuthor = 3,
    wdPropertyKeywords = 4,
    wdPropertyComments = 5,
    wdPropertyTemplate = 6,
    wdPropertyLastAuthor = 7,
    wdPropertyRevision = 8,
    wdPropertyAppName = 9,
    wdPropertyTimeLastPrinted = 10,
    wdPropertyTimeCreated = 11,
    wdPropertyTimeLastSaved = 12,
    wdPropertyVBATotalEdit = 13,
    wdPropertyPages = 14,
    wdPropertyWords = 15,
    wdPropertyCharacters = 16,
    wdPropertySecurity = 17,
    wdPropertyCategory = 18,
    wdPropertyFormat = 19,
    wdPropertyManager = 20,
    wdPropertyCompany = 21,
    wdPropertyBytes = 22,
    wdPropertyLines = 23,
    wdPropertyParas = 24,
    wdPropertySlides = 25,
    wdPropertyNotes = 26,
    wdPropertyHiddenSlides = 27,
    wdPropertyMMClips = 28,
    wdPropertyHyperlinkBase = 29,
    wdPropertyCharsWSpaces = 30
} WdBuiltInProperty;

typedef enum {
    wdLineSpaceSingle = 0,
    wdLineSpace1pt5 = 1,
    wdLineSpaceDouble = 2,
    wdLineSpaceAtLeast = 3,
    wdLineSpaceExactly = 4,
    wdLineSpaceMultiple = 5
} WdLineSpacing;

typedef enum {
    wdNumberParagraph = 1,
    wdNumberListNum = 2,
    wdNumberAllNumbers = 3
} WdNumberType;

typedef enum {
    wdListNoNumbering = 0,
    wdListListNumOnly = 1,
    wdListBullet = 2,
    wdListSimpleNumbering = 3,
    wdListOutlineNumbering = 4,
    wdListMixedNumbering = 5
} WdListType;

typedef enum {
    wdMainTextStory = 1,
    wdFootnotesStory = 2,
    wdEndnotesStory = 3,
    wdCommentsStory = 4,
    wdTextFrameStory = 5,
    wdEvenPagesHeaderStory = 6,
    wdPrimaryHeaderStory = 7,
    wdEvenPagesFooterStory = 8,
    wdPrimaryFooterStory = 9,
    wdFirstPageHeaderStory = 10,
    wdFirstPageFooterStory = 11
} WdStoryType;

typedef enum {
    wdFormatDocument = 0,
    wdFormatTemplate = 1,
    wdFormatText = 2,
    wdFormatTextLineBreaks = 3,
    wdFormatDOSText = 4,
    wdFormatDOSTextLineBreaks = 5,
    wdFormatRTF = 6,
    wdFormatUnicodeText = 7
} WdSaveFormat;

typedef enum {
    wdOpenFormatAuto = 0,
    wdOpenFormatDocument = 1,
    wdOpenFormatTemplate = 2,
    wdOpenFormatRTF = 3,
    wdOpenFormatText = 4,
    wdOpenFormatUnicodeText = 5
} WdOpenFormat;

typedef enum {
    wdHeaderFooterPrimary = 1,
    wdHeaderFooterFirstPage = 2,
    wdHeaderFooterEvenPages = 3
} WdHeaderFooterIndex;

typedef enum {
    wdTOCTemplate = 0,
    wdTOCClassic = 1,
    wdTOCDistinctive = 2,
    wdTOCFancy = 3,
    wdTOCModern = 4,
    wdTOCFormal = 5,
    wdTOCSimple = 6
} WdTocFormat;

typedef enum {
    wdTOFTemplate = 0,
    wdTOFClassic = 1,
    wdTOFDistinctive = 2,
    wdTOFCentered = 3,
    wdTOFFormal = 4,
    wdTOFSimple = 5
} WdTofFormat;

typedef enum {
    wdTOATemplate = 0,
    wdTOAClassic = 1,
    wdTOADistinctive = 2,
    wdTOAFormal = 3,
    wdTOASimple = 4
} WdToaFormat;

typedef enum {
    wdLineStyleNone = 0,
    wdLineStyleSingle = 1,
    wdLineStyleDot = 2,
    wdLineStyleDashSmallGap = 3,
    wdLineStyleDashLargeGap = 4,
    wdLineStyleDashDot = 5,
    wdLineStyleDashDotDot = 6,
    wdLineStyleDouble = 7,
    wdLineStyleTriple = 8,
    wdLineStyleThinThickSmallGap = 9,
    wdLineStyleThickThinSmallGap = 10,
    wdLineStyleThinThickThinSmallGap = 11,
    wdLineStyleThinThickMedGap = 12,
    wdLineStyleThickThinMedGap = 13,
    wdLineStyleThinThickThinMedGap = 14,
    wdLineStyleThinThickLargeGap = 15,
    wdLineStyleThickThinLargeGap = 16,
    wdLineStyleThinThickThinLargeGap = 17,
    wdLineStyleSingleWavy = 18,
    wdLineStyleDoubleWavy = 19,
    wdLineStyleDashDotStroked = 20,
    wdLineStyleEmboss3D = 21,
    wdLineStyleEngrave3D = 22
} WdLineStyle;

typedef enum {
    wdLineWidth025pt = 2,
    wdLineWidth050pt = 4,
    wdLineWidth075pt = 6,
    wdLineWidth100pt = 8,
    wdLineWidth150pt = 12,
    wdLineWidth225pt = 18,
    wdLineWidth300pt = 24,
    wdLineWidth450pt = 36,
    wdLineWidth600pt = 48
} WdLineWidth;

typedef enum {
    wdSectionBreakNextPage = 2,
    wdSectionBreakContinuous = 3,
    wdSectionBreakEvenPage = 4,
    wdSectionBreakOddPage = 5,
    wdLineBreak = 6,
    wdPageBreak = 7,
    wdColumnBreak = 8
} WdBreakType;

typedef enum {
    wdTabLeaderSpaces = 0,
    wdTabLeaderDots = 1,
    wdTabLeaderDashes = 2,
    wdTabLeaderLines = 3
} WdTabLeader;

typedef enum {
    wdTabLeaderHeavy = 4,
    wdTabLeaderMiddleDot = 5
} WdTabLeaderHID;

typedef enum {
    wdInches = 0,
    wdCentimeters = 1,
    wdPoints = 3,
    wdPicas = 4
} WdMeasurementUnits;

typedef enum {
    wdMillimeters = 2
} WdMeasurementUnitsHID;

typedef enum {
    wdDropNone = 0,
    wdDropNormal = 1,
    wdDropMargin = 2
} WdDropPosition;

typedef enum {
    wdRestartContinuous = 0,
    wdRestartSection = 1,
    wdRestartPage = 2
} WdNumberingRule;

typedef enum {
    wdBottomOfPage = 0,
    wdBeneathText = 1
} WdFootnoteLocation;

typedef enum {
    wdEndOfSection = 0,
    wdEndOfDocument = 1
} WdEndnoteLocation;

typedef enum {
    wdSortSeparateByTabs = 0,
    wdSortSeparateByCommas = 1,
    wdSortSeparateByDefaultTableSeparator = 2
} WdSortSeparator;

typedef enum {
    wdSeparateByParagraphs = 0,
    wdSeparateByTabs = 1,
    wdSeparateByCommas = 2,
    wdSeparateByDefaultListSeparator = 3
} WdTableFieldSeparator;

typedef enum {
    wdSortFieldAlphanumeric = 0,
    wdSortFieldNumeric = 1,
    wdSortFieldDate = 2
} WdSortFieldType;

typedef enum {
    wdSortFieldSyllable = 3,
    wdSortFieldJapanJIS = 4,
    wdSortFieldStroke = 5,
    wdSortFieldKoreaKS = 6
} WdSortFieldTypeHID;

typedef enum {
    wdSortOrderAscending = 0,
    wdSortOrderDescending = 1
} WdSortOrder;

typedef enum {
    wdTableFormatNone = 0,
    wdTableFormatSimple1 = 1,
    wdTableFormatSimple2 = 2,
    wdTableFormatSimple3 = 3,
    wdTableFormatClassic1 = 4,
    wdTableFormatClassic2 = 5,
    wdTableFormatClassic3 = 6,
    wdTableFormatClassic4 = 7,
    wdTableFormatColorful1 = 8,
    wdTableFormatColorful2 = 9,
    wdTableFormatColorful3 = 10,
    wdTableFormatColumns1 = 11,
    wdTableFormatColumns2 = 12,
    wdTableFormatColumns3 = 13,
    wdTableFormatColumns4 = 14,
    wdTableFormatColumns5 = 15,
    wdTableFormatGrid1 = 16,
    wdTableFormatGrid2 = 17,
    wdTableFormatGrid3 = 18,
    wdTableFormatGrid4 = 19,
    wdTableFormatGrid5 = 20,
    wdTableFormatGrid6 = 21,
    wdTableFormatGrid7 = 22,
    wdTableFormatGrid8 = 23,
    wdTableFormatList1 = 24,
    wdTableFormatList2 = 25,
    wdTableFormatList3 = 26,
    wdTableFormatList4 = 27,
    wdTableFormatList5 = 28,
    wdTableFormatList6 = 29,
    wdTableFormatList7 = 30,
    wdTableFormatList8 = 31,
    wdTableFormat3DEffects1 = 32,
    wdTableFormat3DEffects2 = 33,
    wdTableFormat3DEffects3 = 34,
    wdTableFormatContemporary = 35,
    wdTableFormatElegant = 36,
    wdTableFormatProfessional = 37,
    wdTableFormatSubtle1 = 38,
    wdTableFormatSubtle2 = 39
} WdTableFormat;

typedef enum {
    wdTableFormatApplyBorders = 1,
    wdTableFormatApplyShading = 2,
    wdTableFormatApplyFont = 4,
    wdTableFormatApplyColor = 8,
    wdTableFormatApplyAutoFit = 16,
    wdTableFormatApplyHeadingRows = 32,
    wdTableFormatApplyLastRow = 64,
    wdTableFormatApplyFirstColumn = 128,
    wdTableFormatApplyLastColumn = 256
} WdTableFormatApply;

typedef enum {
    wdLanguageNone = 0,
    wdNoProofing = 1024,
    wdDanish = 1030,
    wdGerman = 1031,
    wdSwissGerman = 2055,
    wdEnglishAUS = 3081,
    wdEnglishUK = 2057,
    wdEnglishUS = 1033,
    wdEnglishCanadian = 4105,
    wdEnglishNewZealand = 5129,
    wdEnglishSouthAfrica = 7177,
    wdSpanish = 1034,
    wdFrench = 1036,
    wdFrenchCanadian = 3084,
    wdItalian = 1040,
    wdDutch = 1043,
    wdNorwegianBokmol = 1044,
    wdNorwegianNynorsk = 2068,
    wdBrazilianPortuguese = 1046,
    wdPortuguese = 2070,
    wdFinnish = 1035,
    wdSwedish = 1053,
    wdCatalan = 1027,
    wdGreek = 1032,
    wdTurkish = 1055,
    wdRussian = 1049,
    wdCzech = 1029,
    wdHungarian = 1038,
    wdPolish = 1045,
    wdSlovenian = 1060,
    wdBasque = 1069,
    wdMalaysian = 1086,
    wdJapanese = 1041,
    wdKorean = 1042,
    wdSimplifiedChinese = 2052,
    wdTraditionalChinese = 1028,
    wdSwissFrench = 4108,
    wdSesotho = 1072,
    wdTsonga = 1073,
    wdTswana = 1074,
    wdVenda = 1075,
    wdXhosa = 1076,
    wdZulu = 1077,
    wdAfrikaans = 1078,
    wdArabic = 1025,
    wdHebrew = 1037,
    wdSlovak = 1051,
    wdFarsi = 1065,
    wdRomanian = 1048,
    wdCroatian = 1050,
    wdUkrainian = 1058,
    wdByelorussian = 1059,
    wdEstonian = 1061,
    wdLatvian = 1062,
    wdMacedonian = 1071,
    wdSerbianLatin = 2074,
    wdSerbianCyrillic = 3098,
    wdIcelandic = 1039,
    wdBelgianFrench = 2060,
    wdBelgianDutch = 2067,
    wdBulgarian = 1026,
    wdMexicanSpanish = 2058,
    wdSpanishModernSort = 3082,
    wdSwissItalian = 2064
} WdLanguageID;

typedef enum {
    wdFieldEmpty = -1,
    wdFieldRef = 3,
    wdFieldIndexEntry = 4,
    wdFieldFootnoteRef = 5,
    wdFieldSet = 6,
    wdFieldIf = 7,
    wdFieldIndex = 8,
    wdFieldTOCEntry = 9,
    wdFieldStyleRef = 10,
    wdFieldRefDoc = 11,
    wdFieldSequence = 12,
    wdFieldTOC = 13,
    wdFieldInfo = 14,
    wdFieldTitle = 15,
    wdFieldSubject = 16,
    wdFieldAuthor = 17,
    wdFieldKeyWord = 18,
    wdFieldComments = 19,
    wdFieldLastSavedBy = 20,
    wdFieldCreateDate = 21,
    wdFieldSaveDate = 22,
    wdFieldPrintDate = 23,
    wdFieldRevisionNum = 24,
    wdFieldEditTime = 25,
    wdFieldNumPages = 26,
    wdFieldNumWords = 27,
    wdFieldNumChars = 28,
    wdFieldFileName = 29,
    wdFieldTemplate = 30,
    wdFieldDate = 31,
    wdFieldTime = 32,
    wdFieldPage = 33,
    wdFieldExpression = 34,
    wdFieldQuote = 35,
    wdFieldInclude = 36,
    wdFieldPageRef = 37,
    wdFieldAsk = 38,
    wdFieldFillIn = 39,
    wdFieldData = 40,
    wdFieldNext = 41,
    wdFieldNextIf = 42,
    wdFieldSkipIf = 43,
    wdFieldMergeRec = 44,
    wdFieldDDE = 45,
    wdFieldDDEAuto = 46,
    wdFieldGlossary = 47,
    wdFieldPrint = 48,
    wdFieldFormula = 49,
    wdFieldGoToButton = 50,
    wdFieldMacroButton = 51,
    wdFieldAutoNumOutline = 52,
    wdFieldAutoNumLegal = 53,
    wdFieldAutoNum = 54,
    wdFieldImport = 55,
    wdFieldLink = 56,
    wdFieldSymbol = 57,
    wdFieldEmbed = 58,
    wdFieldMergeField = 59,
    wdFieldUserName = 60,
    wdFieldUserInitials = 61,
    wdFieldUserAddress = 62,
    wdFieldBarCode = 63,
    wdFieldDocVariable = 64,
    wdFieldSection = 65,
    wdFieldSectionPages = 66,
    wdFieldIncludePicture = 67,
    wdFieldIncludeText = 68,
    wdFieldFileSize = 69,
    wdFieldFormTextInput = 70,
    wdFieldFormCheckBox = 71,
    wdFieldNoteRef = 72,
    wdFieldTOA = 73,
    wdFieldTOAEntry = 74,
    wdFieldMergeSeq = 75,
    wdFieldPrivate = 77,
    wdFieldDatabase = 78,
    wdFieldAutoText = 79,
    wdFieldCompare = 80,
    wdFieldAddin = 81,
    wdFieldSubscriber = 82,
    wdFieldFormDropDown = 83,
    wdFieldAdvance = 84,
    wdFieldDocProperty = 85,
    wdFieldOCX = 87,
    wdFieldHyperlink = 88,
    wdFieldAutoTextList = 89,
    wdFieldListNum = 90,
    wdFieldHTMLActiveX = 91
} WdFieldType;

typedef enum {
    wdStyleNormal = -1,
    wdStyleEnvelopeAddress = -37,
    wdStyleEnvelopeReturn = -38,
    wdStyleBodyText = -67,
    wdStyleHeading1 = -2,
    wdStyleHeading2 = -3,
    wdStyleHeading3 = -4,
    wdStyleHeading4 = -5,
    wdStyleHeading5 = -6,
    wdStyleHeading6 = -7,
    wdStyleHeading7 = -8,
    wdStyleHeading8 = -9,
    wdStyleHeading9 = -10,
    wdStyleIndex1 = -11,
    wdStyleIndex2 = -12,
    wdStyleIndex3 = -13,
    wdStyleIndex4 = -14,
    wdStyleIndex5 = -15,
    wdStyleIndex6 = -16,
    wdStyleIndex7 = -17,
    wdStyleIndex8 = -18,
    wdStyleIndex9 = -19,
    wdStyleTOC1 = -20,
    wdStyleTOC2 = -21,
    wdStyleTOC3 = -22,
    wdStyleTOC4 = -23,
    wdStyleTOC5 = -24,
    wdStyleTOC6 = -25,
    wdStyleTOC7 = -26,
    wdStyleTOC8 = -27,
    wdStyleTOC9 = -28,
    wdStyleNormalIndent = -29,
    wdStyleFootnoteText = -30,
    wdStyleCommentText = -31,
    wdStyleHeader = -32,
    wdStyleFooter = -33,
    wdStyleIndexHeading = -34,
    wdStyleCaption = -35,
    wdStyleTableOfFigures = -36,
    wdStyleFootnoteReference = -39,
    wdStyleCommentReference = -40,
    wdStyleLineNumber = -41,
    wdStylePageNumber = -42,
    wdStyleEndnoteReference = -43,
    wdStyleEndnoteText = -44,
    wdStyleTableOfAuthorities = -45,
    wdStyleMacroText = -46,
    wdStyleTOAHeading = -47,
    wdStyleList = -48,
    wdStyleListBullet = -49,
    wdStyleListNumber = -50,
    wdStyleList2 = -51,
    wdStyleList3 = -52,
    wdStyleList4 = -53,
    wdStyleList5 = -54,
    wdStyleListBullet2 = -55,
    wdStyleListBullet3 = -56,
    wdStyleListBullet4 = -57,
    wdStyleListBullet5 = -58,
    wdStyleListNumber2 = -59,
    wdStyleListNumber3 = -60,
    wdStyleListNumber4 = -61,
    wdStyleListNumber5 = -62,
    wdStyleTitle = -63,
    wdStyleClosing = -64,
    wdStyleSignature = -65,
    wdStyleDefaultParagraphFont = -66,
    wdStyleBodyTextIndent = -68,
    wdStyleListContinue = -69,
    wdStyleListContinue2 = -70,
    wdStyleListContinue3 = -71,
    wdStyleListContinue4 = -72,
    wdStyleListContinue5 = -73,
    wdStyleMessageHeader = -74,
    wdStyleSubtitle = -75,
    wdStyleSalutation = -76,
    wdStyleDate = -77,
    wdStyleBodyTextFirstIndent = -78,
    wdStyleBodyTextFirstIndent2 = -79,
    wdStyleNoteHeading = -80,
    wdStyleBodyText2 = -81,
    wdStyleBodyText3 = -82,
    wdStyleBodyTextIndent2 = -83,
    wdStyleBodyTextIndent3 = -84,
    wdStyleBlockQuotation = -85,
    wdStyleHyperlink = -86,
    wdStyleHyperlinkFollowed = -87,
    wdStyleStrong = -88,
    wdStyleEmphasis = -89,
    wdStyleNavPane = -90,
    wdStylePlainText = -91
} WdBuiltinStyle;

typedef enum {
    wdDialogToolsOptionsTabView = 204,
    wdDialogToolsOptionsTabGeneral = 203,
    wdDialogToolsOptionsTabEdit = 224,
    wdDialogToolsOptionsTabPrint = 208,
    wdDialogToolsOptionsTabSave = 209,
    wdDialogToolsOptionsTabProofread = 211,
    wdDialogToolsOptionsTabTrackChanges = 386,
    wdDialogToolsOptionsTabUserInfo = 213,
    wdDialogToolsOptionsTabCompatibility = 525,
    wdDialogToolsOptionsTabFileLocations = 225,
    wdDialogFilePageSetupTabMargins = 150000,
    wdDialogFilePageSetupTabPaperSize = 150001,
    wdDialogFilePageSetupTabPaperSource = 150002,
    wdDialogFilePageSetupTabLayout = 150003,
    wdDialogInsertSymbolTabSymbols = 200000,
    wdDialogInsertSymbolTabSpecialCharacters = 200001,
    wdDialogNoteOptionsTabAllFootnotes = 300000,
    wdDialogNoteOptionsTabAllEndnotes = 300001,
    wdDialogInsertIndexAndTablesTabIndex = 400000,
    wdDialogInsertIndexAndTablesTabTableOfContents = 400001,
    wdDialogInsertIndexAndTablesTabTableOfFigures = 400002,
    wdDialogInsertIndexAndTablesTabTableOfAuthorities = 400003,
    wdDialogOrganizerTabStyles = 500000,
    wdDialogOrganizerTabAutoText = 500001,
    wdDialogOrganizerTabCommandBars = 500002,
    wdDialogOrganizerTabMacros = 500003,
    wdDialogFormatFontTabFont = 600000,
    wdDialogFormatFontTabCharacterSpacing = 600001,
    wdDialogFormatFontTabAnimation = 600002,
    wdDialogFormatBordersAndShadingTabBorders = 700000,
    wdDialogFormatBordersAndShadingTabPageBorder = 700001,
    wdDialogFormatBordersAndShadingTabShading = 700002,
    wdDialogToolsEnvelopesAndLabelsTabEnvelopes = 800000,
    wdDialogToolsEnvelopesAndLabelsTabLabels = 800001,
    wdDialogFormatParagraphTabIndentsAndSpacing = 1000000,
    wdDialogFormatParagraphTabTextFlow = 1000001,
    wdDialogFormatDrawingObjectTabColorsAndLines = 1200000,
    wdDialogFormatDrawingObjectTabSize = 1200001,
    wdDialogFormatDrawingObjectTabPosition = 1200002,
    wdDialogFormatDrawingObjectTabWrapping = 1200003,
    wdDialogFormatDrawingObjectTabPicture = 1200004,
    wdDialogFormatDrawingObjectTabTextbox = 1200005,
    wdDialogToolsAutoCorrectExceptionsTabFirstLetter = 1400000,
    wdDialogToolsAutoCorrectExceptionsTabInitialCaps = 1400001,
    wdDialogFormatBulletsAndNumberingTabBulleted = 1500000,
    wdDialogFormatBulletsAndNumberingTabNumbered = 1500001,
    wdDialogFormatBulletsAndNumberingTabOutlineNumbered = 1500002,
    wdDialogLetterWizardTabLetterFormat = 1600000,
    wdDialogLetterWizardTabRecipientInfo = 1600001,
    wdDialogLetterWizardTabOtherElements = 1600002,
    wdDialogLetterWizardTabSenderInfo = 1600003,
    wdDialogToolsAutoManagerTabAutoCorrect = 1700000,
    wdDialogToolsAutoManagerTabAutoFormatAsYouType = 1700001,
    wdDialogToolsAutoManagerTabAutoText = 1700002,
    wdDialogToolsAutoManagerTabAutoFormat = 1700003
} WdWordDialogTab;

typedef enum {
    wdDialogToolsOptionsTabTypography = 739,
    wdDialogToolsOptionsTabFuzzy = 790,
    wdDialogToolsOptionsTabHangulHanjaConversion = 786,
    wdDialogFilePageSetupTabCharsLines = 150004,
    wdDialogFormatParagraphTabTeisai = 1000002,
    wdDialogToolsAutoCorrectExceptionsTabHangulAndAlphabet = 1400002
} WdWordDialogTabHID;

typedef enum {
    wdDialogHelpAbout = 9,
    wdDialogHelpWordPerfectHelp = 10,
    wdDialogHelpWordPerfectHelpOptions = 511,
    wdDialogFormatChangeCase = 322,
    wdDialogToolsWordCount = 228,
    wdDialogDocumentStatistics = 78,
    wdDialogFileNew = 79,
    wdDialogFileOpen = 80,
    wdDialogMailMergeOpenDataSource = 81,
    wdDialogMailMergeOpenHeaderSource = 82,
    wdDialogMailMergeUseAddressBook = 779,
    wdDialogFileSaveAs = 84,
    wdDialogFileSummaryInfo = 86,
    wdDialogToolsTemplates = 87,
    wdDialogOrganizer = 222,
    wdDialogFilePrint = 88,
    wdDialogMailMerge = 676,
    wdDialogMailMergeCheck = 677,
    wdDialogMailMergeQueryOptions = 681,
    wdDialogMailMergeFindRecord = 569,
    wdDialogMailMergeInsertIf = 4049,
    wdDialogMailMergeInsertNextIf = 4053,
    wdDialogMailMergeInsertSkipIf = 4055,
    wdDialogMailMergeInsertFillIn = 4048,
    wdDialogMailMergeInsertAsk = 4047,
    wdDialogMailMergeInsertSet = 4054,
    wdDialogMailMergeHelper = 680,
    wdDialogLetterWizard = 821,
    wdDialogFilePrintSetup = 97,
    wdDialogFileFind = 99,
    wdDialogMailMergeCreateDataSource = 642,
    wdDialogMailMergeCreateHeaderSource = 643,
    wdDialogEditPasteSpecial = 111,
    wdDialogEditFind = 112,
    wdDialogEditReplace = 117,
    wdDialogEditGoToOld = 811,
    wdDialogEditGoTo = 896,
    wdDialogCreateAutoText = 872,
    wdDialogEditAutoText = 985,
    wdDialogEditLinks = 124,
    wdDialogEditObject = 125,
    wdDialogConvertObject = 392,
    wdDialogTableToText = 128,
    wdDialogTextToTable = 127,
    wdDialogTableInsertTable = 129,
    wdDialogTableInsertCells = 130,
    wdDialogTableInsertRow = 131,
    wdDialogTableDeleteCells = 133,
    wdDialogTableSplitCells = 137,
    wdDialogTableFormula = 348,
    wdDialogTableAutoFormat = 563,
    wdDialogTableFormatCell = 612,
    wdDialogViewZoom = 577,
    wdDialogNewToolbar = 586,
    wdDialogInsertBreak = 159,
    wdDialogInsertFootnote = 370,
    wdDialogInsertSymbol = 162,
    wdDialogInsertPicture = 163,
    wdDialogInsertFile = 164,
    wdDialogInsertDateTime = 165,
    wdDialogInsertField = 166,
    wdDialogInsertDatabase = 341,
    wdDialogInsertMergeField = 167,
    wdDialogInsertBookmark = 168,
    wdDialogMarkIndexEntry = 169,
    wdDialogMarkCitation = 463,
    wdDialogEditTOACategory = 625,
    wdDialogInsertIndexAndTables = 473,
    wdDialogInsertIndex = 170,
    wdDialogInsertTableOfContents = 171,
    wdDialogMarkTableOfContentsEntry = 442,
    wdDialogInsertTableOfFigures = 472,
    wdDialogInsertTableOfAuthorities = 471,
    wdDialogInsertObject = 172,
    wdDialogFormatCallout = 610,
    wdDialogDrawSnapToGrid = 633,
    wdDialogDrawAlign = 634,
    wdDialogToolsEnvelopesAndLabels = 607,
    wdDialogToolsCreateEnvelope = 173,
    wdDialogToolsCreateLabels = 489,
    wdDialogToolsProtectDocument = 503,
    wdDialogToolsProtectSection = 578,
    wdDialogToolsUnprotectDocument = 521,
    wdDialogFormatFont = 174,
    wdDialogFormatParagraph = 175,
    wdDialogFormatSectionLayout = 176,
    wdDialogFormatColumns = 177,
    wdDialogFileDocumentLayout = 178,
    wdDialogFileMacPageSetup = 685,
    wdDialogFilePrintOneCopy = 445,
    wdDialogFileMacPageSetupGX = 444,
    wdDialogFileMacCustomPageSetupGX = 737,
    wdDialogFilePageSetup = 178,
    wdDialogFormatTabs = 179,
    wdDialogFormatStyle = 180,
    wdDialogFormatStyleGallery = 505,
    wdDialogFormatDefineStyleFont = 181,
    wdDialogFormatDefineStylePara = 182,
    wdDialogFormatDefineStyleTabs = 183,
    wdDialogFormatDefineStyleFrame = 184,
    wdDialogFormatDefineStyleBorders = 185,
    wdDialogFormatDefineStyleLang = 186,
    wdDialogFormatPicture = 187,
    wdDialogToolsLanguage = 188,
    wdDialogFormatBordersAndShading = 189,
    wdDialogFormatDrawingObject = 960,
    wdDialogFormatFrame = 190,
    wdDialogFormatDropCap = 488,
    wdDialogFormatBulletsAndNumbering = 824,
    wdDialogToolsHyphenation = 195,
    wdDialogToolsBulletsNumbers = 196,
    wdDialogToolsHighlightChanges = 197,
    wdDialogToolsAcceptRejectChanges = 506,
    wdDialogToolsMergeDocuments = 435,
    wdDialogToolsCompareDocuments = 198,
    wdDialogTableSort = 199,
    wdDialogToolsCustomizeMenuBar = 615,
    wdDialogToolsCustomize = 152,
    wdDialogToolsCustomizeKeyboard = 432,
    wdDialogToolsCustomizeMenus = 433,
    wdDialogListCommands = 723,
    wdDialogToolsOptions = 974,
    wdDialogToolsOptionsGeneral = 203,
    wdDialogToolsAdvancedSettings = 206,
    wdDialogToolsOptionsCompatibility = 525,
    wdDialogToolsOptionsPrint = 208,
    wdDialogToolsOptionsSave = 209,
    wdDialogToolsOptionsSpellingAndGrammar = 211,
    wdDialogToolsSpellingAndGrammar = 828,
    wdDialogToolsThesaurus = 194,
    wdDialogToolsOptionsUserInfo = 213,
    wdDialogToolsOptionsAutoFormat = 959,
    wdDialogToolsOptionsTrackChanges = 386,
    wdDialogToolsOptionsEdit = 224,
    wdDialogToolsMacro = 215,
    wdDialogInsertPageNumbers = 294,
    wdDialogFormatPageNumber = 298,
    wdDialogNoteOptions = 373,
    wdDialogCopyFile = 300,
    wdDialogFormatAddrFonts = 103,
    wdDialogFormatRetAddrFonts = 221,
    wdDialogToolsOptionsFileLocations = 225,
    wdDialogToolsCreateDirectory = 833,
    wdDialogUpdateTOC = 331,
    wdDialogInsertFormField = 483,
    wdDialogFormFieldOptions = 353,
    wdDialogInsertCaption = 357,
    wdDialogInsertAutoCaption = 359,
    wdDialogInsertAddCaption = 402,
    wdDialogInsertCaptionNumbering = 358,
    wdDialogInsertCrossReference = 367,
    wdDialogToolsManageFields = 631,
    wdDialogToolsAutoManager = 915,
    wdDialogToolsAutoCorrect = 378,
    wdDialogToolsAutoCorrectExceptions = 762,
    wdDialogConnect = 420,
    wdDialogToolsOptionsView = 204,
    wdDialogInsertSubdocument = 583,
    wdDialogFileRoutingSlip = 624,
    wdDialogFontSubstitution = 581,
    wdDialogEditCreatePublisher = 732,
    wdDialogEditSubscribeTo = 733,
    wdDialogEditPublishOptions = 735,
    wdDialogEditSubscribeOptions = 736,
    wdDialogControlRun = 235,
    wdDialogFileVersions = 945,
    wdDialogToolsAutoSummarize = 874,
    wdDialogFileSaveVersion = 1007,
    wdDialogWindowActivate = 220,
    wdDialogToolsMacroRecord = 214,
    wdDialogToolsRevisions = 197
} WdWordDialog;

typedef enum {
    wdDialogToolsOptionsFuzzy = 790,
    wdDialogToolsOptionsTypography = 739,
    wdDialogToolsOptionsAutoFormatAsYouType = 778
} WdWordDialogHID;

typedef enum {
    wdFieldKindNone = 0,
    wdFieldKindHot = 1,
    wdFieldKindWarm = 2,
    wdFieldKindCold = 3
} WdFieldKind;

typedef enum {
    wdRegularText = 0,
    wdNumberText = 1,
    wdDateText = 2,
    wdCurrentDateText = 3,
    wdCurrentTimeText = 4,
    wdCalculationText = 5
} WdTextFormFieldType;

typedef enum {
    wdNeverConvert = 0,
    wdAlwaysConvert = 1,
    wdAskToNotConvert = 2,
    wdAskToConvert = 3
} WdChevronConvertRule;

typedef enum {
    wdNotAMergeDocument = -1,
    wdFormLetters = 0,
    wdMailingLabels = 1,
    wdEnvelopes = 2,
    wdCatalog = 3
} WdMailMergeMainDocType;

typedef enum {
    wdNormalDocument = 0,
    wdMainDocumentOnly = 1,
    wdMainAndDataSource = 2,
    wdMainAndHeader = 3,
    wdMainAndSourceAndHeader = 4,
    wdDataSource = 5
} WdMailMergeState;

typedef enum {
    wdSendToNewDocument = 0,
    wdSendToPrinter = 1,
    wdSendToEmail = 2,
    wdSendToFax = 3
} WdMailMergeDestination;

typedef enum {
    wdNoActiveRecord = -1,
    wdNextRecord = -2,
    wdPreviousRecord = -3,
    wdFirstRecord = -4,
    wdLastRecord = -5
} WdMailMergeActiveRecord;

typedef enum {
    wdDefaultFirstRecord = 1,
    wdDefaultLastRecord = -16
} WdMailMergeDefaultRecord;

typedef enum {
    wdNoMergeInfo = -1,
    wdMergeInfoFromWord = 0,
    wdMergeInfoFromAccessDDE = 1,
    wdMergeInfoFromExcelDDE = 2,
    wdMergeInfoFromMSQueryDDE = 3,
    wdMergeInfoFromODBC = 4
} WdMailMergeDataSource;

typedef enum {
    wdMergeIfEqual = 0,
    wdMergeIfNotEqual = 1,
    wdMergeIfLessThan = 2,
    wdMergeIfGreaterThan = 3,
    wdMergeIfLessThanOrEqual = 4,
    wdMergeIfGreaterThanOrEqual = 5,
    wdMergeIfIsBlank = 6,
    wdMergeIfIsNotBlank = 7
} WdMailMergeComparison;

typedef enum {
    wdSortByName = 0,
    wdSortByLocation = 1
} WdBookmarkSortBy;

typedef enum {
    wdWindowStateNormal = 0,
    wdWindowStateMaximize = 1,
    wdWindowStateMinimize = 2
} WdWindowState;

typedef enum {
    wdLinkNone = 0,
    wdLinkDataInDoc = 1,
    wdLinkDataOnDisk = 2
} WdPictureLinkType;

typedef enum {
    wdLinkTypeOLE = 0,
    wdLinkTypePicture = 1,
    wdLinkTypeText = 2,
    wdLinkTypeReference = 3,
    wdLinkTypeInclude = 4,
    wdLinkTypeImport = 5,
    wdLinkTypeDDE = 6,
    wdLinkTypeDDEAuto = 7
} WdLinkType;

typedef enum {
    wdWindowDocument = 0,
    wdWindowTemplate = 1
} WdWindowType;

typedef enum {
    wdNormalView = 1,
    wdOutlineView = 2,
    wdPageView = 3,
    wdPrintPreview = 4,
    wdMasterView = 5,
    wdOnlineView = 6
} WdViewType;

typedef enum {
    wdSeekMainDocument = 0,
    wdSeekPrimaryHeader = 1,
    wdSeekFirstPageHeader = 2,
    wdSeekEvenPagesHeader = 3,
    wdSeekPrimaryFooter = 4,
    wdSeekFirstPageFooter = 5,
    wdSeekEvenPagesFooter = 6,
    wdSeekFootnotes = 7,
    wdSeekEndnotes = 8,
    wdSeekCurrentPageHeader = 9,
    wdSeekCurrentPageFooter = 10
} WdSeekView;

typedef enum {
    wdPaneNone = 0,
    wdPanePrimaryHeader = 1,
    wdPaneFirstPageHeader = 2,
    wdPaneEvenPagesHeader = 3,
    wdPanePrimaryFooter = 4,
    wdPaneFirstPageFooter = 5,
    wdPaneEvenPagesFooter = 6,
    wdPaneFootnotes = 7,
    wdPaneEndnotes = 8,
    wdPaneFootnoteContinuationNotice = 9,
    wdPaneFootnoteContinuationSeparator = 10,
    wdPaneFootnoteSeparator = 11,
    wdPaneEndnoteContinuationNotice = 12,
    wdPaneEndnoteContinuationSeparator = 13,
    wdPaneEndnoteSeparator = 14,
    wdPaneComments = 15,
    wdPaneCurrentPageHeader = 16,
    wdPaneCurrentPageFooter = 17
} WdSpecialPane;

typedef enum {
    wdPageFitNone = 0,
    wdPageFitFullPage = 1,
    wdPageFitBestFit = 2
} WdPageFit;

typedef enum {
    wdBrowsePage = 1,
    wdBrowseSection = 2,
    wdBrowseComment = 3,
    wdBrowseFootnote = 4,
    wdBrowseEndnote = 5,
    wdBrowseField = 6,
    wdBrowseTable = 7,
    wdBrowseGraphic = 8,
    wdBrowseHeading = 9,
    wdBrowseEdit = 10,
    wdBrowseFind = 11,
    wdBrowseGoTo = 12
} WdBrowseTarget;

typedef enum {
    wdPrinterDefaultBin = 0,
    wdPrinterUpperBin = 1,
    wdPrinterOnlyBin = 1,
    wdPrinterLowerBin = 2,
    wdPrinterMiddleBin = 3,
    wdPrinterManualFeed = 4,
    wdPrinterEnvelopeFeed = 5,
    wdPrinterManualEnvelopeFeed = 6,
    wdPrinterAutomaticSheetFeed = 7,
    wdPrinterTractorFeed = 8,
    wdPrinterSmallFormatBin = 9,
    wdPrinterLargeFormatBin = 10,
    wdPrinterLargeCapacityBin = 11,
    wdPrinterPaperCassette = 14,
    wdPrinterFormSource = 15
} WdPaperTray;

typedef enum {
    wdOrientPortrait = 0,
    wdOrientLandscape = 1
} WdOrientation;

typedef enum {
    wdNoSelection = 0,
    wdSelectionIP = 1,
    wdSelectionNormal = 2,
    wdSelectionFrame = 3,
    wdSelectionColumn = 4,
    wdSelectionRow = 5,
    wdSelectionBlock = 6,
    wdSelectionInlineShape = 7,
    wdSelectionShape = 8
} WdSelectionType;

typedef enum {
    wdCaptionFigure = -1,
    wdCaptionTable = -2,
    wdCaptionEquation = -3
} WdCaptionLabelID;

typedef enum {
    wdRefTypeNumberedItem = 0,
    wdRefTypeHeading = 1,
    wdRefTypeBookmark = 2,
    wdRefTypeFootnote = 3,
    wdRefTypeEndnote = 4
} WdReferenceType;

typedef enum {
    wdContentText = -1,
    wdNumberRelativeContext = -2,
    wdNumberNoContext = -3,
    wdNumberFullContext = -4,
    wdEntireCaption = 2,
    wdOnlyLabelAndNumber = 3,
    wdOnlyCaptionText = 4,
    wdFootnoteNumber = 5,
    wdEndnoteNumber = 6,
    wdPageNumber = 7,
    wdPosition = 15,
    wdFootnoteNumberFormatted = 16,
    wdEndnoteNumberFormatted = 17
} WdReferenceKind;

typedef enum {
    wdIndexTemplate = 0,
    wdIndexClassic = 1,
    wdIndexFancy = 2,
    wdIndexModern = 3,
    wdIndexBulleted = 4,
    wdIndexFormal = 5,
    wdIndexSimple = 6
} WdIndexFormat;

typedef enum {
    wdIndexIndent = 0,
    wdIndexRunin = 1
} WdIndexType;

typedef enum {
    wdWrapNever = 0,
    wdWrapAlways = 1,
    wdWrapAsk = 2
} WdRevisionsWrap;

typedef enum {
    wdNoRevision = 0,
    wdRevisionInsert = 1,
    wdRevisionDelete = 2,
    wdRevisionProperty = 3,
    wdRevisionParagraphNumber = 4,
    wdRevisionDisplayField = 5,
    wdRevisionReconcile = 6,
    wdRevisionConflict = 7,
    wdRevisionStyle = 8,
    wdRevisionReplace = 9
} WdRevisionType;

typedef enum {
    wdOneAfterAnother = 0,
    wdAllAtOnce = 1
} WdRoutingSlipDelivery;

typedef enum {
    wdNotYetRouted = 0,
    wdRouteInProgress = 1,
    wdRouteComplete = 2
} WdRoutingSlipStatus;

typedef enum {
    wdSectionContinuous = 0,
    wdSectionNewColumn = 1,
    wdSectionNewPage = 2,
    wdSectionEvenPage = 3,
    wdSectionOddPage = 4
} WdSectionStart;

typedef enum {
    wdDoNotSaveChanges = 0,
    wdSaveChanges = -1,
    wdPromptToSaveChanges = -2
} WdSaveOptions;

typedef enum {
    wdDocumentNotSpecified = 0,
    wdDocumentLetter = 1,
    wdDocumentEmail = 2
} WdDocumentKind;

typedef enum {
    wdTypeDocument = 0,
    wdTypeTemplate = 1
} WdDocumentType;

typedef enum {
    wdWordDocument = 0,
    wdOriginalDocumentFormat = 1,
    wdPromptUser = 2
} WdOriginalFormat;

typedef enum {
    wdRelocateUp = 0,
    wdRelocateDown = 1
} WdRelocate;

typedef enum {
    wdInsertedTextMarkNone = 0,
    wdInsertedTextMarkBold = 1,
    wdInsertedTextMarkItalic = 2,
    wdInsertedTextMarkUnderline = 3,
    wdInsertedTextMarkDoubleUnderline = 4
} WdInsertedTextMark;

typedef enum {
    wdRevisedLinesMarkNone = 0,
    wdRevisedLinesMarkLeftBorder = 1,
    wdRevisedLinesMarkRightBorder = 2,
    wdRevisedLinesMarkOutsideBorder = 3
} WdRevisedLinesMark;

typedef enum {
    wdDeletedTextMarkHidden = 0,
    wdDeletedTextMarkStrikeThrough = 1,
    wdDeletedTextMarkCaret = 2,
    wdDeletedTextMarkPound = 3
} WdDeletedTextMark;

typedef enum {
    wdRevisedPropertiesMarkNone = 0,
    wdRevisedPropertiesMarkBold = 1,
    wdRevisedPropertiesMarkItalic = 2,
    wdRevisedPropertiesMarkUnderline = 3,
    wdRevisedPropertiesMarkDoubleUnderline = 4
} WdRevisedPropertiesMark;

typedef enum {
    wdFieldShadingNever = 0,
    wdFieldShadingAlways = 1,
    wdFieldShadingWhenSelected = 2
} WdFieldShading;

typedef enum {
    wdDocumentsPath = 0,
    wdPicturesPath = 1,
    wdUserTemplatesPath = 2,
    wdWorkgroupTemplatesPath = 3,
    wdUserOptionsPath = 4,
    wdAutoRecoverPath = 5,
    wdToolsPath = 6,
    wdTutorialPath = 7,
    wdStartupPath = 8,
    wdProgramPath = 9,
    wdGraphicsFiltersPath = 10,
    wdTextConvertersPath = 11,
    wdProofingToolsPath = 12,
    wdTempFilePath = 13,
    wdCurrentFolderPath = 14,
    wdStyleGalleryPath = 15,
    wdBorderArtPath = 19
} WdDefaultFilePath;

typedef enum {
    wdNoTabHangIndent = 1,
    wdNoSpaceRaiseLower = 2,
    wdPrintColBlack = 3,
    wdWrapTrailSpaces = 4,
    wdNoColumnBalance = 5,
    wdConvMailMergeEsc = 6,
    wdSuppressSpBfAfterPgBrk = 7,
    wdSuppressTopSpacing = 8,
    wdOrigWordTableRules = 9,
    wdTransparentMetafiles = 10,
    wdShowBreaksInFrames = 11,
    wdSwapBordersFacingPages = 12,
    wdLeaveBackslashAlone = 13,
    wdExpandShiftReturn = 14,
    wdDontULTrailSpace = 15,
    wdDontBalanceSingleByteDoubleByteWidth = 16,
    wdSuppressTopSpacingMac5 = 17,
    wdSpacingInWholePoints = 18,
    wdPrintBodyTextBeforeHeader = 19,
    wdNoLeading = 20,
    wdNoSpaceForUL = 21,
    wdMWSmallCaps = 22,
    wdNoExtraLineSpacing = 23,
    wdTruncateFontHeight = 24,
    wdSubFontBySize = 25,
    wdUsePrinterMetrics = 26,
    wdWW6BorderRules = 27,
    wdExactOnTop = 28,
    wdSuppressBottomSpacing = 29,
    wdWPSpaceWidth = 30,
    wdWPJustification = 31,
    wdLineWrapLikeWord6 = 32
} WdCompatibility;

typedef enum {
    wdPaper10x14 = 0,
    wdPaper11x17 = 1,
    wdPaperLetter = 2,
    wdPaperLetterSmall = 3,
    wdPaperLegal = 4,
    wdPaperExecutive = 5,
    wdPaperA3 = 6,
    wdPaperA4 = 7,
    wdPaperA4Small = 8,
    wdPaperA5 = 9,
    wdPaperB4 = 10,
    wdPaperB5 = 11,
    wdPaperCSheet = 12,
    wdPaperDSheet = 13,
    wdPaperESheet = 14,
    wdPaperFanfoldLegalGerman = 15,
    wdPaperFanfoldStdGerman = 16,
    wdPaperFanfoldUS = 17,
    wdPaperFolio = 18,
    wdPaperLedger = 19,
    wdPaperNote = 20,
    wdPaperQuarto = 21,
    wdPaperStatement = 22,
    wdPaperTabloid = 23,
    wdPaperEnvelope9 = 24,
    wdPaperEnvelope10 = 25,
    wdPaperEnvelope11 = 26,
    wdPaperEnvelope12 = 27,
    wdPaperEnvelope14 = 28,
    wdPaperEnvelopeB4 = 29,
    wdPaperEnvelopeB5 = 30,
    wdPaperEnvelopeB6 = 31,
    wdPaperEnvelopeC3 = 32,
    wdPaperEnvelopeC4 = 33,
    wdPaperEnvelopeC5 = 34,
    wdPaperEnvelopeC6 = 35,
    wdPaperEnvelopeC65 = 36,
    wdPaperEnvelopeDL = 37,
    wdPaperEnvelopeItaly = 38,
    wdPaperEnvelopeMonarch = 39,
    wdPaperEnvelopePersonal = 40,
    wdPaperCustom = 41
} WdPaperSize;

typedef enum {
    wdCustomLabelLetter = 0,
    wdCustomLabelLetterLS = 1,
    wdCustomLabelA4 = 2,
    wdCustomLabelA4LS = 3,
    wdCustomLabelA5 = 4,
    wdCustomLabelA5LS = 5,
    wdCustomLabelB5 = 6,
    wdCustomLabelMini = 7,
    wdCustomLabelFanfold = 8
} WdCustomLabelPageSize;

typedef enum {
    wdNoProtection = -1,
    wdAllowOnlyRevisions = 0,
    wdAllowOnlyComments = 1,
    wdAllowOnlyFormFields = 2
} WdProtectionType;

typedef enum {
    wdAdjective = 0,
    wdNoun = 1,
    wdAdverb = 2,
    wdVerb = 3
} WdPartOfSpeech;

typedef enum {
    wdSubscriberBestFormat = 0,
    wdSubscriberRTF = 1,
    wdSubscriberText = 2,
    wdSubscriberPict = 4
} WdSubscriberFormats;

typedef enum {
    wdPublisher = 0,
    wdSubscriber = 1
} WdEditionType;

typedef enum {
    wdCancelPublisher = 0,
    wdSendPublisher = 1,
    wdSelectPublisher = 2,
    wdAutomaticUpdate = 3,
    wdManualUpdate = 4,
    wdChangeAttributes = 5,
    wdUpdateSubscriber = 6,
    wdOpenSource = 7
} WdEditionOption;

typedef enum {
    wdRelativeHorizontalPositionMargin = 0,
    wdRelativeHorizontalPositionPage = 1,
    wdRelativeHorizontalPositionColumn = 2
} WdRelativeHorizontalPosition;

typedef enum {
    wdRelativeVerticalPositionMargin = 0,
    wdRelativeVerticalPositionPage = 1,
    wdRelativeVerticalPositionParagraph = 2
} WdRelativeVerticalPosition;

typedef enum {
    wdHelp = 0,
    wdHelpAbout = 1,
    wdHelpActiveWindow = 2,
    wdHelpContents = 3,
    wdHelpExamplesAndDemos = 4,
    wdHelpIndex = 5,
    wdHelpKeyboard = 6,
    wdHelpPSSHelp = 7,
    wdHelpQuickPreview = 8,
    wdHelpSearch = 9,
    wdHelpUsingHelp = 10
} WdHelpType;

typedef enum {
    wdHelpIchitaro = 11,
    wdHelpPE2 = 12
} WdHelpTypeHID;

typedef enum {
    wdKeyCategoryNil = -1,
    wdKeyCategoryDisable = 0,
    wdKeyCategoryCommand = 1,
    wdKeyCategoryMacro = 2,
    wdKeyCategoryFont = 3,
    wdKeyCategoryAutoText = 4,
    wdKeyCategoryStyle = 5,
    wdKeyCategorySymbol = 6,
    wdKeyCategoryPrefix = 7
} WdKeyCategory;

typedef enum {
    wdNoKey = 255,
    wdKeyShift = 256,
    wdKeyControl = 512,
    wdKeyCommand = 512,
    wdKeyAlt = 1024,
    wdKeyOption = 1024,
    wdKeyA = 65,
    wdKeyB = 66,
    wdKeyC = 67,
    wdKeyD = 68,
    wdKeyE = 69,
    wdKeyF = 70,
    wdKeyG = 71,
    wdKeyH = 72,
    wdKeyI = 73,
    wdKeyJ = 74,
    wdKeyK = 75,
    wdKeyL = 76,
    wdKeyM = 77,
    wdKeyN = 78,
    wdKeyO = 79,
    wdKeyP = 80,
    wdKeyQ = 81,
    wdKeyR = 82,
    wdKeyS = 83,
    wdKeyT = 84,
    wdKeyU = 85,
    wdKeyV = 86,
    wdKeyW = 87,
    wdKeyX = 88,
    wdKeyY = 89,
    wdKeyZ = 90,
    wdKey0 = 48,
    wdKey1 = 49,
    wdKey2 = 50,
    wdKey3 = 51,
    wdKey4 = 52,
    wdKey5 = 53,
    wdKey6 = 54,
    wdKey7 = 55,
    wdKey8 = 56,
    wdKey9 = 57,
    wdKeyBackspace = 8,
    wdKeyTab = 9,
    wdKeyNumeric5Special = 12,
    wdKeyReturn = 13,
    wdKeyPause = 19,
    wdKeyEsc = 27,
    wdKeySpacebar = 32,
    wdKeyPageUp = 33,
    wdKeyPageDown = 34,
    wdKeyEnd = 35,
    wdKeyHome = 36,
    wdKeyInsert = 45,
    wdKeyDelete = 46,
    wdKeyNumeric0 = 96,
    wdKeyNumeric1 = 97,
    wdKeyNumeric2 = 98,
    wdKeyNumeric3 = 99,
    wdKeyNumeric4 = 100,
    wdKeyNumeric5 = 101,
    wdKeyNumeric6 = 102,
    wdKeyNumeric7 = 103,
    wdKeyNumeric8 = 104,
    wdKeyNumeric9 = 105,
    wdKeyNumericMultiply = 106,
    wdKeyNumericAdd = 107,
    wdKeyNumericSubtract = 109,
    wdKeyNumericDecimal = 110,
    wdKeyNumericDivide = 111,
    wdKeyF1 = 112,
    wdKeyF2 = 113,
    wdKeyF3 = 114,
    wdKeyF4 = 115,
    wdKeyF5 = 116,
    wdKeyF6 = 117,
    wdKeyF7 = 118,
    wdKeyF8 = 119,
    wdKeyF9 = 120,
    wdKeyF10 = 121,
    wdKeyF11 = 122,
    wdKeyF12 = 123,
    wdKeyF13 = 124,
    wdKeyF14 = 125,
    wdKeyF15 = 126,
    wdKeyF16 = 127,
    wdKeyScrollLock = 145,
    wdKeySemiColon = 186,
    wdKeyEquals = 187,
    wdKeyComma = 188,
    wdKeyHyphen = 189,
    wdKeyPeriod = 190,
    wdKeySlash = 191,
    wdKeyBackSingleQuote = 192,
    wdKeyOpenSquareBrace = 219,
    wdKeyBackSlash = 220,
    wdKeyCloseSquareBrace = 221,
    wdKeySingleQuote = 222
} WdKey;

typedef enum {
    wdOLELink = 0,
    wdOLEEmbed = 1,
    wdOLEControl = 2
} WdOLEType;

typedef enum {
    wdOLEVerbPrimary = 0,
    wdOLEVerbShow = -1,
    wdOLEVerbOpen = -2,
    wdOLEVerbHide = -3,
    wdOLEVerbUIActivate = -4,
    wdOLEVerbInPlaceActivate = -5,
    wdOLEVerbDiscardUndoState = -6
} WdOLEVerb;

typedef enum {
    wdInLine = 0,
    wdFloatOverText = 1
} WdOLEPlacement;

typedef enum {
    wdLeftPortrait = 0,
    wdCenterPortrait = 1,
    wdRightPortrait = 2,
    wdLeftLandscape = 3,
    wdCenterLandscape = 4,
    wdRightLandscape = 5,
    wdLeftClockwise = 6,
    wdCenterClockwise = 7,
    wdRightClockwise = 8
} WdEnvelopeOrientation;

typedef enum {
    wdFullBlock = 0,
    wdModifiedBlock = 1,
    wdSemiBlock = 2
} WdLetterStyle;

typedef enum {
    wdLetterTop = 0,
    wdLetterBottom = 1,
    wdLetterLeft = 2,
    wdLetterRight = 3
} WdLetterheadLocation;

typedef enum {
    wdSalutationInformal = 0,
    wdSalutationFormal = 1,
    wdSalutationBusiness = 2,
    wdSalutationOther = 3
} WdSalutationType;

typedef enum {
    wdGenderFemale = 0,
    wdGenderMale = 1,
    wdGenderNeutral = 2,
    wdGenderUnknown = 3
} WdSalutationGender;

typedef enum {
    wdMove = 0,
    wdExtend = 1
} WdMovementType;

typedef enum {
    wdUndefined = 9999999,
    wdToggle = 9999998,
    wdForward = 1073741823,
    wdBackward = -1073741823,
    wdAutoPosition = 0,
    wdFirst = 1,
    wdCreatorCode = 1297307460
} WdConstants;

typedef enum {
    wdPasteOLEObject = 0,
    wdPasteRTF = 1,
    wdPasteText = 2,
    wdPasteMetafilePicture = 3,
    wdPasteBitmap = 4,
    wdPasteDeviceIndependentBitmap = 5,
    wdPasteHyperlink = 7,
    wdPasteShape = 8,
    wdPasteEnhancedMetafile = 9
} WdPasteDataType;

typedef enum {
    wdPrintDocumentContent = 0,
    wdPrintProperties = 1,
    wdPrintComments = 2,
    wdPrintStyles = 3,
    wdPrintAutoTextEntries = 4,
    wdPrintKeyAssignments = 5,
    wdPrintEnvelope = 6
} WdPrintOutItem;

typedef enum {
    wdPrintAllPages = 0,
    wdPrintOddPagesOnly = 1,
    wdPrintEvenPagesOnly = 2
} WdPrintOutPages;

typedef enum {
    wdPrintAllDocument = 0,
    wdPrintSelection = 1,
    wdPrintCurrentPage = 2,
    wdPrintFromTo = 3,
    wdPrintRangeOfPages = 4
} WdPrintOutRange;

typedef enum {
    wdSpelling = 0,
    wdGrammar = 1,
    wdThesaurus = 2,
    wdHyphenation = 3,
    wdSpellingComplete = 4,
    wdSpellingCustom = 5,
    wdSpellingLegal = 6,
    wdSpellingMedical = 7
} WdDictionaryType;

typedef enum {
    wdHangulHanjaConversion = 8,
    wdHangulHanjaConversionCustom = 9
} WdDictionaryTypeHID;

typedef enum {
    wdSpellword = 0,
    wdWildcard = 1,
    wdAnagram = 2
} WdSpellingWordType;

typedef enum {
    wdSpellingCorrect = 0,
    wdSpellingNotInDictionary = 1,
    wdSpellingCapitalization = 2
} WdSpellingErrorType;

typedef enum {
    wdSpellingError = 0,
    wdGrammaticalError = 1
} WdProofreadingErrorType;

typedef enum {
    wdInlineShapeEmbeddedOLEObject = 1,
    wdInlineShapeLinkedOLEObject = 2,
    wdInlineShapePicture = 3,
    wdInlineShapeLinkedPicture = 4,
    wdInlineShapeOLEControlObject = 5
} WdInlineShapeType;

typedef enum {
    wdTiled = 0,
    wdIcons = 1
} WdArrangeStyle;

typedef enum {
    wdSelStartActive = 1,
    wdSelAtEOL = 2,
    wdSelOvertype = 4,
    wdSelActive = 8,
    wdSelReplace = 16
} WdSelectionFlags;

typedef enum {
    wdAutoVersionOff = 0,
    wdAutoVersionOnClose = 1
} WdAutoVersions;

typedef enum {
    wdOrganizerObjectStyles = 0,
    wdOrganizerObjectAutoText = 1,
    wdOrganizerObjectCommandBars = 2,
    wdOrganizerObjectProjectItems = 3
} WdOrganizerObject;

typedef enum {
    wdMatchParagraphMark = 65551,
    wdMatchTabCharacter = 9,
    wdMatchCommentMark = 5,
    wdMatchAnyCharacter = 65599,
    wdMatchAnyDigit = 65567,
    wdMatchAnyLetter = 65583,
    wdMatchCaretCharacter = 11,
    wdMatchColumnBreak = 14,
    wdMatchEmDash = 8212,
    wdMatchEnDash = 8211,
    wdMatchEndnoteMark = 65555,
    wdMatchField = 19,
    wdMatchFootnoteMark = 65554,
    wdMatchGraphic = 1,
    wdMatchManualLineBreak = 65551,
    wdMatchManualPageBreak = 65564,
    wdMatchNonbreakingHyphen = 30,
    wdMatchNonbreakingSpace = 160,
    wdMatchOptionalHyphen = 31,
    wdMatchSectionBreak = 65580,
    wdMatchWhiteSpace = 65655
} WdFindMatch;

typedef enum {
    wdFindStop = 0,
    wdFindContinue = 1,
    wdFindAsk = 2
} WdFindWrap;

typedef enum {
    wdActiveEndAdjustedPageNumber = 1,
    wdActiveEndSectionNumber = 2,
    wdActiveEndPageNumber = 3,
    wdNumberOfPagesInDocument = 4,
    wdHorizontalPositionRelativeToPage = 5,
    wdVerticalPositionRelativeToPage = 6,
    wdHorizontalPositionRelativeToTextBoundary = 7,
    wdVerticalPositionRelativeToTextBoundary = 8,
    wdFirstCharacterColumnNumber = 9,
    wdFirstCharacterLineNumber = 10,
    wdFrameIsSelected = 11,
    wdWithInTable = 12,
    wdStartOfRangeRowNumber = 13,
    wdEndOfRangeRowNumber = 14,
    wdMaximumNumberOfRows = 15,
    wdStartOfRangeColumnNumber = 16,
    wdEndOfRangeColumnNumber = 17,
    wdMaximumNumberOfColumns = 18,
    wdZoomPercentage = 19,
    wdSelectionMode = 20,
    wdCapsLock = 21,
    wdNumLock = 22,
    wdOverType = 23,
    wdRevisionMarking = 24,
    wdInFootnoteEndnotePane = 25,
    wdInCommentPane = 26,
    wdInHeaderFooter = 28,
    wdAtEndOfRowMarker = 31,
    wdReferenceOfType = 32,
    wdHeaderFooterType = 33,
    wdInMasterDocument = 34,
    wdInFootnote = 35,
    wdInEndnote = 36,
    wdInWordMail = 37,
    wdInClipboard = 38
} WdInformation;

typedef enum {
    wdWrapSquare = 0,
    wdWrapTight = 1,
    wdWrapThrough = 2,
    wdWrapNone = 3,
    wdWrapTopBottom = 4
} WdWrapType;

typedef enum {
    wdWrapBoth = 0,
    wdWrapLeft = 1,
    wdWrapRight = 2,
    wdWrapLargest = 3
} WdWrapSideType;

typedef enum {
    wdOutlineLevel1 = 1,
    wdOutlineLevel2 = 2,
    wdOutlineLevel3 = 3,
    wdOutlineLevel4 = 4,
    wdOutlineLevel5 = 5,
    wdOutlineLevel6 = 6,
    wdOutlineLevel7 = 7,
    wdOutlineLevel8 = 8,
    wdOutlineLevel9 = 9,
    wdOutlineLevelBodyText = 10
} WdOutlineLevel;

typedef enum {
    wdTextOrientationHorizontal = 0,
    wdTextOrientationUpward = 2,
    wdTextOrientationDownward = 3
} WdTextOrientation;

typedef enum {
    wdTextOrientationVerticalFarEast = 1,
    wdTextOrientationHorizontalRotatedFarEast = 4
} WdTextOrientationHID;

typedef enum {
    wdArtApples = 1,
    wdArtMapleMuffins = 2,
    wdArtCakeSlice = 3,
    wdArtCandyCorn = 4,
    wdArtIceCreamCones = 5,
    wdArtChampagneBottle = 6,
    wdArtPartyGlass = 7,
    wdArtChristmasTree = 8,
    wdArtTrees = 9,
    wdArtPalmsColor = 10,
    wdArtBalloons3Colors = 11,
    wdArtBalloonsHotAir = 12,
    wdArtPartyFavor = 13,
    wdArtConfettiStreamers = 14,
    wdArtHearts = 15,
    wdArtHeartBalloon = 16,
    wdArtStars3D = 17,
    wdArtStarsShadowed = 18,
    wdArtStars = 19,
    wdArtSun = 20,
    wdArtEarth2 = 21,
    wdArtEarth1 = 22,
    wdArtPeopleHats = 23,
    wdArtSombrero = 24,
    wdArtPencils = 25,
    wdArtPackages = 26,
    wdArtClocks = 27,
    wdArtFirecrackers = 28,
    wdArtRings = 29,
    wdArtMapPins = 30,
    wdArtConfetti = 31,
    wdArtCreaturesButterfly = 32,
    wdArtCreaturesLadyBug = 33,
    wdArtCreaturesFish = 34,
    wdArtBirdsFlight = 35,
    wdArtScaredCat = 36,
    wdArtBats = 37,
    wdArtFlowersRoses = 38,
    wdArtFlowersRedRose = 39,
    wdArtPoinsettias = 40,
    wdArtHolly = 41,
    wdArtFlowersTiny = 42,
    wdArtFlowersPansy = 43,
    wdArtFlowersModern2 = 44,
    wdArtFlowersModern1 = 45,
    wdArtWhiteFlowers = 46,
    wdArtVine = 47,
    wdArtFlowersDaisies = 48,
    wdArtFlowersBlockPrint = 49,
    wdArtDecoArchColor = 50,
    wdArtFans = 51,
    wdArtFilm = 52,
    wdArtLightning1 = 53,
    wdArtCompass = 54,
    wdArtDoubleD = 55,
    wdArtClassicalWave = 56,
    wdArtShadowedSquares = 57,
    wdArtTwistedLines1 = 58,
    wdArtWaveline = 59,
    wdArtQuadrants = 60,
    wdArtCheckedBarColor = 61,
    wdArtSwirligig = 62,
    wdArtPushPinNote1 = 63,
    wdArtPushPinNote2 = 64,
    wdArtPumpkin1 = 65,
    wdArtEggsBlack = 66,
    wdArtCup = 67,
    wdArtHeartGray = 68,
    wdArtGingerbreadMan = 69,
    wdArtBabyPacifier = 70,
    wdArtBabyRattle = 71,
    wdArtCabins = 72,
    wdArtHouseFunky = 73,
    wdArtStarsBlack = 74,
    wdArtSnowflakes = 75,
    wdArtSnowflakeFancy = 76,
    wdArtSkyrocket = 77,
    wdArtSeattle = 78,
    wdArtMusicNotes = 79,
    wdArtPalmsBlack = 80,
    wdArtMapleLeaf = 81,
    wdArtPaperClips = 82,
    wdArtShorebirdTracks = 83,
    wdArtPeople = 84,
    wdArtPeopleWaving = 85,
    wdArtEclipsingSquares2 = 86,
    wdArtHypnotic = 87,
    wdArtDiamondsGray = 88,
    wdArtDecoArch = 89,
    wdArtDecoBlocks = 90,
    wdArtCirclesLines = 91,
    wdArtPapyrus = 92,
    wdArtWoodwork = 93,
    wdArtWeavingBraid = 94,
    wdArtWeavingRibbon = 95,
    wdArtWeavingAngles = 96,
    wdArtArchedScallops = 97,
    wdArtSafari = 98,
    wdArtCelticKnotwork = 99,
    wdArtCrazyMaze = 100,
    wdArtEclipsingSquares1 = 101,
    wdArtBirds = 102,
    wdArtFlowersTeacup = 103,
    wdArtNorthwest = 104,
    wdArtSouthwest = 105,
    wdArtTribal6 = 106,
    wdArtTribal4 = 107,
    wdArtTribal3 = 108,
    wdArtTribal2 = 109,
    wdArtTribal5 = 110,
    wdArtXIllusions = 111,
    wdArtZanyTriangles = 112,
    wdArtPyramids = 113,
    wdArtPyramidsAbove = 114,
    wdArtConfettiGrays = 115,
    wdArtConfettiOutline = 116,
    wdArtConfettiWhite = 117,
    wdArtMosaic = 118,
    wdArtLightning2 = 119,
    wdArtHeebieJeebies = 120,
    wdArtLightBulb = 121,
    wdArtGradient = 122,
    wdArtTriangleParty = 123,
    wdArtTwistedLines2 = 124,
    wdArtMoons = 125,
    wdArtOvals = 126,
    wdArtDoubleDiamonds = 127,
    wdArtChainLink = 128,
    wdArtTriangles = 129,
    wdArtTribal1 = 130,
    wdArtMarqueeToothed = 131,
    wdArtSharksTeeth = 132,
    wdArtSawtooth = 133,
    wdArtSawtoothGray = 134,
    wdArtPostageStamp = 135,
    wdArtWeavingStrips = 136,
    wdArtZigZag = 137,
    wdArtCrossStitch = 138,
    wdArtGems = 139,
    wdArtCirclesRectangles = 140,
    wdArtCornerTriangles = 141,
    wdArtCreaturesInsects = 142,
    wdArtZigZagStitch = 143,
    wdArtCheckered = 144,
    wdArtCheckedBarBlack = 145,
    wdArtMarquee = 146,
    wdArtBasicWhiteDots = 147,
    wdArtBasicWideMidline = 148,
    wdArtBasicWideOutline = 149,
    wdArtBasicWideInline = 150,
    wdArtBasicThinLines = 151,
    wdArtBasicWhiteDashes = 152,
    wdArtBasicWhiteSquares = 153,
    wdArtBasicBlackSquares = 154,
    wdArtBasicBlackDashes = 155,
    wdArtBasicBlackDots = 156,
    wdArtStarsTop = 157,
    wdArtCertificateBanner = 158,
    wdArtHandmade1 = 159,
    wdArtHandmade2 = 160,
    wdArtTornPaper = 161,
    wdArtTornPaperBlack = 162,
    wdArtCouponCutoutDashes = 163,
    wdArtCouponCutoutDots = 164
} WdPageBorderArt;

typedef enum {
    wdBorderDistanceFromText = 0,
    wdBorderDistanceFromPageEdge = 1
} WdBorderDistanceFrom;

typedef enum {
    wdReplaceNone = 0,
    wdReplaceOne = 1,
    wdReplaceAll = 2
} WdReplace;

typedef enum {
    wdFontBiasDontCare = 255,
    wdFontBiasDefault = 0,
    wdFontBiasFareast = 1
} WdFontBias;

#endif // WORDTYPES_H_INCLUDED
