# Generated from 'MacWindows.h'def FOUR_CHAR_CODE(x): return xkAlertWindowClass = 1LkMovableAlertWindowClass = 2LkModalWindowClass = 3LkMovableModalWindowClass = 4LkFloatingWindowClass = 5LkDocumentWindowClass = 6LkDesktopWindowClass = 7L# kAllWindowClasses = (unsigned long)0xFFFFFFFF     kWindowNoAttributes = 0LkWindowCloseBoxAttribute = (1L << 0)kWindowHorizontalZoomAttribute = (1L << 1)kWindowVerticalZoomAttribute = (1L << 2)kWindowFullZoomAttribute = (kWindowVerticalZoomAttribute | kWindowHorizontalZoomAttribute)kWindowCollapseBoxAttribute = (1L << 3)kWindowResizableAttribute = (1L << 4)kWindowSideTitlebarAttribute = (1L << 5)kWindowNoUpdatesAttribute = (1L << 16)kWindowNoActivatesAttribute = (1L << 17)kWindowNoBufferingAttribute = (1L << 20)kWindowHideOnSuspendAttribute = (1L << 24)kWindowStandardHandlerAttribute = (1L << 25)kWindowStandardDocumentAttributes = (kWindowCloseBoxAttribute | kWindowFullZoomAttribute | kWindowCollapseBoxAttribute | kWindowResizableAttribute)kWindowStandardFloatingAttributes = (kWindowCloseBoxAttribute | kWindowCollapseBoxAttribute)kWindowDefProcType = FOUR_CHAR_CODE('WDEF')kStandardWindowDefinition = 0kRoundWindowDefinition = 1kFloatingWindowDefinition = 124                           kDocumentWindowVariantCode = 0kModalDialogVariantCode = 1kPlainDialogVariantCode = 2kShadowDialogVariantCode = 3kMovableModalDialogVariantCode = 5kAlertVariantCode = 7kMovableAlertVariantCode = 9kSideFloaterVariantCode = 8documentProc = 0dBoxProc = 1plainDBox = 2altDBoxProc = 3noGrowDocProc = 4movableDBoxProc = 5zoomDocProc = 8zoomNoGrow = 12floatProc = 1985floatGrowProc = 1987floatZoomProc = 1989floatZoomGrowProc = 1991floatSideProc = 1993floatSideGrowProc = 1995floatSideZoomProc = 1997floatSideZoomGrowProc = 1999rDocProc = 16kWindowDocumentDefProcResID = 64kWindowDialogDefProcResID = 65kWindowUtilityDefProcResID = 66kWindowUtilitySideTitleDefProcResID = 67kWindowDocumentProc = 1024kWindowGrowDocumentProc = 1025kWindowVertZoomDocumentProc = 1026kWindowVertZoomGrowDocumentProc = 1027kWindowHorizZoomDocumentProc = 1028kWindowHorizZoomGrowDocumentProc = 1029kWindowFullZoomDocumentProc = 1030kWindowFullZoomGrowDocumentProc = 1031kWindowPlainDialogProc = 1040kWindowShadowDialogProc = 1041kWindowModalDialogProc = 1042kWindowMovableModalDialogProc = 1043kWindowAlertProc = 1044kWindowMovableAlertProc = 1045kWindowMovableModalGrowProc = 1046kWindowFloatProc = 1057kWindowFloatGrowProc = 1059kWindowFloatVertZoomProc = 1061kWindowFloatVertZoomGrowProc = 1063kWindowFloatHorizZoomProc = 1065kWindowFloatHorizZoomGrowProc = 1067kWindowFloatFullZoomProc = 1069kWindowFloatFullZoomGrowProc = 1071kWindowFloatSideProc = 1073kWindowFloatSideGrowProc = 1075kWindowFloatSideVertZoomProc = 1077kWindowFloatSideVertZoomGrowProc = 1079kWindowFloatSideHorizZoomProc = 1081kWindowFloatSideHorizZoomGrowProc = 1083kWindowFloatSideFullZoomProc = 1085kWindowFloatSideFullZoomGrowProc = 1087kWindowNoPosition = 0x0000kWindowDefaultPosition = 0x0000kWindowCenterMainScreen = 0x280AkWindowAlertPositionMainScreen = 0x300AkWindowStaggerMainScreen = 0x380AkWindowCenterParentWindow = 0xA80AkWindowAlertPositionParentWindow = 0xB00AkWindowStaggerParentWindow = 0xB80AkWindowCenterParentWindowScreen = 0x680AkWindowAlertPositionParentWindowScreen = 0x700AkWindowStaggerParentWindowScreen = 0x780AkWindowCenterOnMainScreen = 0x00000001kWindowCenterOnParentWindow = 0x00000002kWindowCenterOnParentWindowScreen = 0x00000003kWindowCascadeOnMainScreen = 0x00000004kWindowCascadeOnParentWindow = 0x00000005kWindowCascadeOnParentWindowScreen = 0x00000006kWindowAlertPositionOnMainScreen = 0x00000007kWindowAlertPositionOnParentWindow = 0x00000008kWindowAlertPositionOnParentWindowScreen = 0x00000009kWindowTitleBarRgn = 0kWindowTitleTextRgn = 1kWindowCloseBoxRgn = 2kWindowZoomBoxRgn = 3kWindowDragRgn = 5kWindowGrowRgn = 6kWindowCollapseBoxRgn = 7kWindowTitleProxyIconRgn = 8kWindowStructureRgn = 32kWindowContentRgn = 33kWindowUpdateRgn = 34kWindowGlobalPortRgn = 40                            dialogKind = 2userKind = 8kDialogWindowKind = 2kApplicationWindowKind = 8inDesk = 0inNoWindow = 0inMenuBar = 1inSysWindow = 2inContent = 3inDrag = 4inGrow = 5inGoAway = 6inZoomIn = 7inZoomOut = 8inCollapseBox = 11inProxyIcon = 12                            wNoHit = 0wInContent = 1wInDrag = 2wInGrow = 3wInGoAway = 4wInZoomIn = 5wInZoomOut = 6wInCollapseBox = 9wInProxyIcon = 10                            kWindowMsgDraw = 0kWindowMsgHitTest = 1kWindowMsgCalculateShape = 2kWindowMsgInitialize = 3kWindowMsgCleanUp = 4kWindowMsgDrawGrowOutline = 5kWindowMsgDrawGrowBox = 6kWindowMsgGetFeatures = 7kWindowMsgGetRegion = 8kWindowMsgDragHilite = 9kWindowMsgModified = 10kWindowMsgDrawInCurrentPort = 11kWindowMsgSetupProxyDragImage = 12kWindowMsgStateChanged = 13kWindowMsgMeasureTitle = 14                            kWindowMsgGetGrowImageRegion = 19                           wDraw = 0wHit = 1wCalcRgns = 2wNew = 3wDispose = 4wGrow = 5wDrawGIcon = 6kWindowStateTitleChanged = (1 << 0)kWindowGrowSideTop = 0x01kWindowGrowSideLeft = 0x02kWindowGrowSideBottom = 0x04kWindowGrowSideRight = 0x08kWindowCanGrow = (1 << 0)kWindowCanZoom = (1 << 1)kWindowCanCollapse = (1 << 2)kWindowIsModal = (1 << 3)kWindowCanGetWindowRegion = (1 << 4)kWindowIsAlert = (1 << 5)kWindowHasTitleBar = (1 << 6)kWindowSupportsDragHilite = (1 << 7)kWindowSupportsModifiedBit = (1 << 8)kWindowCanDrawInCurrentPort = (1 << 9)kWindowCanSetupProxyDragImage = (1 << 10)kWindowCanMeasureTitle = (1 << 11)kWindowWantsDisposeAtProcessDeath = (1 << 12)kWindowSupportsSetGrowImageRegion = (1 << 13)kWindowDefSupportsColorGrafPort = 0x40000002                deskPatID = 16wContentColor = 0wFrameColor = 1wTextColor = 2wHiliteColor = 3wTitleBarColor = 4# kMouseUpOutOfSlop = (long)0x80008000kWindowDefinitionVersionOne = 1kWindowDefinitionVersionTwo = 2kWindowIsCollapsedState = (1 << 0L)kStoredWindowSystemTag = FOUR_CHAR_CODE('appl')kStoredBasicWindowDescriptionID = FOUR_CHAR_CODE('sbas')kStoredWindowPascalTitleID = FOUR_CHAR_CODE('s255')        kWindowDefProcPtr = 0kWindowDefObjectClass = 1                             kWindowPaintProcOptionsNone = 0kScrollWindowNoOptions = 0kScrollWindowInvalidate = (1L << 0)kScrollWindowEraseToPortBackground = (1L << 1)              kWindowZoomTransitionEffect = 1                             kWindowShowTransitionAction = 1kWindowHideTransitionAction = 2                             kWindowPropertyPersistent = 0x00000001                    