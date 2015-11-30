/*** Glue for missing routines.*/#include <Types.h>#include <Errors.h>#define UNDEFINED_TOOLBOX_FUNCTION(name) pascal OSErr name() { return unimpErr; }#ifdef __MC68K__UNDEFINED_TOOLBOX_FUNCTION(GetPixRowBytes) /* This one is funny: it should exist */UNDEFINED_TOOLBOX_FUNCTION(IsAntiAliasedTextEnabled)UNDEFINED_TOOLBOX_FUNCTION(SetAntiAliasedTextEnabled)UNDEFINED_TOOLBOX_FUNCTION(SetUpControlTextColor)UNDEFINED_TOOLBOX_FUNCTION(GetControlViewSize)UNDEFINED_TOOLBOX_FUNCTION(SetControlViewSize)UNDEFINED_TOOLBOX_FUNCTION(GetControl32BitValue)UNDEFINED_TOOLBOX_FUNCTION(SetControl32BitValue)UNDEFINED_TOOLBOX_FUNCTION(GetControl32BitMaximum)UNDEFINED_TOOLBOX_FUNCTION(SetControl32BitMaximum)UNDEFINED_TOOLBOX_FUNCTION(GetControl32BitMinimum)UNDEFINED_TOOLBOX_FUNCTION(SetControl32BitMinimum)UNDEFINED_TOOLBOX_FUNCTION(IsValidControlHandle)UNDEFINED_TOOLBOX_FUNCTION(RemoveControlProperty)UNDEFINED_TOOLBOX_FUNCTION(GetMenuFont)UNDEFINED_TOOLBOX_FUNCTION(SetMenuFont)UNDEFINED_TOOLBOX_FUNCTION(GetMenuExcludesMarkColumn)UNDEFINED_TOOLBOX_FUNCTION(SetMenuExcludesMarkColumn)UNDEFINED_TOOLBOX_FUNCTION(AppendMenuItemText)UNDEFINED_TOOLBOX_FUNCTION(InsertMenuItemText)UNDEFINED_TOOLBOX_FUNCTION(EnableMenuItem)UNDEFINED_TOOLBOX_FUNCTION(DisableMenuItem)UNDEFINED_TOOLBOX_FUNCTION(IsMenuItemEnabled)UNDEFINED_TOOLBOX_FUNCTION(EnableMenuItemIcon)UNDEFINED_TOOLBOX_FUNCTION(DisableMenuItemIcon)UNDEFINED_TOOLBOX_FUNCTION(IsMenuItemIconEnabled)UNDEFINED_TOOLBOX_FUNCTION(GetControlRegion)UNDEFINED_TOOLBOX_FUNCTION(AppendDialogItemList)UNDEFINED_TOOLBOX_FUNCTION(SetDialogTimeout)UNDEFINED_TOOLBOX_FUNCTION(GetDialogTimeout)UNDEFINED_TOOLBOX_FUNCTION(SetModalDialogEventMask)UNDEFINED_TOOLBOX_FUNCTION(GetModalDialogEventMask)UNDEFINED_TOOLBOX_FUNCTION(GetWindowOwnerCount)UNDEFINED_TOOLBOX_FUNCTION(CloneWindow)UNDEFINED_TOOLBOX_FUNCTION(GetWindowClass)UNDEFINED_TOOLBOX_FUNCTION(GetWindowAttributes)UNDEFINED_TOOLBOX_FUNCTION(SetWindowContentColor)UNDEFINED_TOOLBOX_FUNCTION(GetWindowContentColor)UNDEFINED_TOOLBOX_FUNCTION(GetWindowContentPattern)UNDEFINED_TOOLBOX_FUNCTION(SetWindowContentPattern)UNDEFINED_TOOLBOX_FUNCTION(InvalWindowRgn)UNDEFINED_TOOLBOX_FUNCTION(InvalWindowRect)UNDEFINED_TOOLBOX_FUNCTION(ValidWindowRgn)UNDEFINED_TOOLBOX_FUNCTION(ValidWindowRect)UNDEFINED_TOOLBOX_FUNCTION(SetWindowProxyFSSpec)UNDEFINED_TOOLBOX_FUNCTION(GetWindowProxyFSSpec)UNDEFINED_TOOLBOX_FUNCTION(SetWindowProxyAlias)UNDEFINED_TOOLBOX_FUNCTION(GetWindowProxyAlias)UNDEFINED_TOOLBOX_FUNCTION(SetWindowProxyCreatorAndType)UNDEFINED_TOOLBOX_FUNCTION(GetWindowProxyIcon)UNDEFINED_TOOLBOX_FUNCTION(SetWindowProxyIcon)UNDEFINED_TOOLBOX_FUNCTION(RemoveWindowProxy)UNDEFINED_TOOLBOX_FUNCTION(TrackWindowProxyDrag)UNDEFINED_TOOLBOX_FUNCTION(IsWindowModified)UNDEFINED_TOOLBOX_FUNCTION(SetWindowModified)UNDEFINED_TOOLBOX_FUNCTION(IsWindowPathSelectClick)UNDEFINED_TOOLBOX_FUNCTION(HiliteWindowFrameForDrag)UNDEFINED_TOOLBOX_FUNCTION(TransitionWindow)UNDEFINED_TOOLBOX_FUNCTION(RepositionWindow)UNDEFINED_TOOLBOX_FUNCTION(SetWindowBounds)UNDEFINED_TOOLBOX_FUNCTION(GetWindowBounds)UNDEFINED_TOOLBOX_FUNCTION(MoveWindowStructure)UNDEFINED_TOOLBOX_FUNCTION(IsWindowInStandardState)UNDEFINED_TOOLBOX_FUNCTION(ZoomWindowIdeal)UNDEFINED_TOOLBOX_FUNCTION(GetWindowIdealUserState)UNDEFINED_TOOLBOX_FUNCTION(SetWindowIdealUserState)UNDEFINED_TOOLBOX_FUNCTION(IsMenuBarVisible)UNDEFINED_TOOLBOX_FUNCTION(ShowMenuBar)UNDEFINED_TOOLBOX_FUNCTION(HideMenuBar)UNDEFINED_TOOLBOX_FUNCTION(CreateNewWindow)UNDEFINED_TOOLBOX_FUNCTION(CreateWindowFromResource)UNDEFINED_TOOLBOX_FUNCTION(ShowFloatingWindows)UNDEFINED_TOOLBOX_FUNCTION(HideFloatingWindows)UNDEFINED_TOOLBOX_FUNCTION(AreFloatingWindowsVisible)UNDEFINED_TOOLBOX_FUNCTION(FrontNonFloatingWindow)UNDEFINED_TOOLBOX_FUNCTION(IsValidWindowPtr)UNDEFINED_TOOLBOX_FUNCTION(InitFloatingWindows)UNDEFINED_TOOLBOX_FUNCTION(IconServicesTerminate)UNDEFINED_TOOLBOX_FUNCTION(IconRefToIconFamily)UNDEFINED_TOOLBOX_FUNCTION(IconFamilyToIconSuite)UNDEFINED_TOOLBOX_FUNCTION(IconSuiteToIconFamily)UNDEFINED_TOOLBOX_FUNCTION(SetIconFamilyData)UNDEFINED_TOOLBOX_FUNCTION(GetIconFamilyData)UNDEFINED_TOOLBOX_FUNCTION(GetIconRefOwners)UNDEFINED_TOOLBOX_FUNCTION(AcquireIconRef)UNDEFINED_TOOLBOX_FUNCTION(ReleaseIconRef)UNDEFINED_TOOLBOX_FUNCTION(GetIconRefFromFile)UNDEFINED_TOOLBOX_FUNCTION(GetIconRef)UNDEFINED_TOOLBOX_FUNCTION(GetIconRefFromFolder)UNDEFINED_TOOLBOX_FUNCTION(RegisterIconRefFromIconFamily)UNDEFINED_TOOLBOX_FUNCTION(RegisterIconRefFromResource)UNDEFINED_TOOLBOX_FUNCTION(UnregisterIconRef)UNDEFINED_TOOLBOX_FUNCTION(UpdateIconRef)UNDEFINED_TOOLBOX_FUNCTION(OverrideIconRefFromResource)UNDEFINED_TOOLBOX_FUNCTION(OverrideIconRef)UNDEFINED_TOOLBOX_FUNCTION(RemoveIconRefOverride)UNDEFINED_TOOLBOX_FUNCTION(CompositeIconRef)UNDEFINED_TOOLBOX_FUNCTION(IsIconRefComposite)UNDEFINED_TOOLBOX_FUNCTION(IsValidIconRef)UNDEFINED_TOOLBOX_FUNCTION(PlotIconRef)UNDEFINED_TOOLBOX_FUNCTION(PtInIconRef)UNDEFINED_TOOLBOX_FUNCTION(RectInIconRef)UNDEFINED_TOOLBOX_FUNCTION(IconRefToRgn)UNDEFINED_TOOLBOX_FUNCTION(GetIconSizesFromIconRef)UNDEFINED_TOOLBOX_FUNCTION(FlushIconRefs)UNDEFINED_TOOLBOX_FUNCTION(FlushIconRefsByVolume)UNDEFINED_TOOLBOX_FUNCTION(SetCustomIconsEnabled)UNDEFINED_TOOLBOX_FUNCTION(GetCustomIconsEnabled)UNDEFINED_TOOLBOX_FUNCTION(SndGetInfo)UNDEFINED_TOOLBOX_FUNCTION(SndSetInfo)UNDEFINED_TOOLBOX_FUNCTION(GetCompressionInfo)UNDEFINED_TOOLBOX_FUNCTION(SetSoundPreference)UNDEFINED_TOOLBOX_FUNCTION(GetSoundPreference)UNDEFINED_TOOLBOX_FUNCTION(GetCompressionName)UNDEFINED_TOOLBOX_FUNCTION(DrawThemeTabPane)UNDEFINED_TOOLBOX_FUNCTION(GetThemeTabRegion)UNDEFINED_TOOLBOX_FUNCTION(SetThemeCursor)UNDEFINED_TOOLBOX_FUNCTION(SetAnimatedThemeCursor)UNDEFINED_TOOLBOX_FUNCTION(GetThemeScrollBarThumbStyle)UNDEFINED_TOOLBOX_FUNCTION(GetThemeScrollBarArrowStyle)UNDEFINED_TOOLBOX_FUNCTION(GetThemeCheckBoxStyle)UNDEFINED_TOOLBOX_FUNCTION(UseThemeFont)UNDEFINED_TOOLBOX_FUNCTION(DrawThemeScrollBarArrows)UNDEFINED_TOOLBOX_FUNCTION(GetThemeScrollBarTrackRect)UNDEFINED_TOOLBOX_FUNCTION(HitTestThemeScrollBarArrows)UNDEFINED_TOOLBOX_FUNCTION(DrawThemeScrollBarDelimiters)UNDEFINED_TOOLBOX_FUNCTION(PlayThemeSound)UNDEFINED_TOOLBOX_FUNCTION(BeginThemeDragSound)UNDEFINED_TOOLBOX_FUNCTION(EndThemeDragSound)UNDEFINED_TOOLBOX_FUNCTION(DrawThemeTickMark)UNDEFINED_TOOLBOX_FUNCTION(DrawThemeStandaloneGrowBox)UNDEFINED_TOOLBOX_FUNCTION(DrawThemeStandaloneNoGrowBox)UNDEFINED_TOOLBOX_FUNCTION(GetThemeStandaloneGrowBoxBounds)UNDEFINED_TOOLBOX_FUNCTION(NormalizeThemeDrawingState)UNDEFINED_TOOLBOX_FUNCTION(ApplyThemeBackground)UNDEFINED_TOOLBOX_FUNCTION(SetThemeTextColorForWindow)UNDEFINED_TOOLBOX_FUNCTION(IsValidAppearanceFileType)UNDEFINED_TOOLBOX_FUNCTION(GetThemeBrushAsColor)UNDEFINED_TOOLBOX_FUNCTION(GetThemeTextColor)#endif