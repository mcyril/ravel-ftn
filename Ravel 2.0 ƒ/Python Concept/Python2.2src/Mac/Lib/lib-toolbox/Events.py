# Generated from 'Events.h'nullEvent = 0mouseDown = 1mouseUp = 2keyDown = 3keyUp = 4autoKey = 5updateEvt = 6diskEvt = 7activateEvt = 8osEvt = 15kHighLevelEvent = 23mDownMask = 1 << mouseDownmUpMask = 1 << mouseUpkeyDownMask = 1 << keyDownkeyUpMask = 1 << keyUpautoKeyMask = 1 << autoKeyupdateMask = 1 << updateEvtdiskMask = 1 << diskEvtactivMask = 1 << activateEvthighLevelEventMask = 0x0400osMask = 1 << osEvteveryEvent = 0xFFFF charCodeMask = 0x000000FFkeyCodeMask = 0x0000FF00adbAddrMask = 0x00FF0000# osEvtMessageMask = (unsigned long)0xFF000000mouseMovedMessage = 0x00FAsuspendResumeMessage = 0x0001resumeFlag = 1     convertClipboardFlag = 2     activeFlagBit = 0btnStateBit = 7cmdKeyBit = 8shiftKeyBit = 9alphaLockBit = 10optionKeyBit = 11controlKeyBit = 12rightShiftKeyBit = 13rightOptionKeyBit = 14rightControlKeyBit = 15    activeFlag = 1 << activeFlagBitbtnState = 1 << btnStateBitcmdKey = 1 << cmdKeyBitshiftKey = 1 << shiftKeyBitalphaLock = 1 << alphaLockBitoptionKey = 1 << optionKeyBitcontrolKey = 1 << controlKeyBitrightShiftKey = 1 << rightShiftKeyBitrightOptionKey = 1 << rightOptionKeyBitrightControlKey = 1 << rightControlKeyBitkNullCharCode = 0kHomeCharCode = 1kEnterCharCode = 3kEndCharCode = 4kHelpCharCode = 5kBellCharCode = 7kBackspaceCharCode = 8kTabCharCode = 9kLineFeedCharCode = 10kVerticalTabCharCode = 11kPageUpCharCode = 11kFormFeedCharCode = 12kPageDownCharCode = 12kReturnCharCode = 13kFunctionKeyCharCode = 16kEscapeCharCode = 27kClearCharCode = 27kLeftArrowCharCode = 28kRightArrowCharCode = 29kUpArrowCharCode = 30kDownArrowCharCode = 31kDeleteCharCode = 127kNonBreakingSpaceCharCode = 202networkEvt = 10driverEvt = 11app1Evt = 12app2Evt = 13app3Evt = 14app4Evt = 15networkMask = 0x0400driverMask = 0x0800app1Mask = 0x1000app2Mask = 0x2000app3Mask = 0x4000app4Mask = 0x8000