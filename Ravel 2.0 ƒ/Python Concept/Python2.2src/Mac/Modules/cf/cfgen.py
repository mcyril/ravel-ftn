# Generated from 'Moes:Applications (Mac OS 9):Metrowerks CodeWarrior 7.0:Metrowerks CodeWarrior:MacOS Support:Universal:Interfaces:CIncludes:CFBase.h'f = Function(CFRange, '__CFRangeMake',    (CFIndex, 'loc', InMode),    (CFIndex, 'len', InMode),)functions.append(f)f = Function(CFTypeID, 'CFAllocatorGetTypeID',)functions.append(f)f = Function(CFIndex, 'CFAllocatorGetPreferredSizeForSize',    (CFAllocatorRef, 'allocator', InMode),    (CFIndex, 'size', InMode),    (CFOptionFlags, 'hint', InMode),)functions.append(f)f = Method(CFTypeID, 'CFGetTypeID',    (CFTypeRef, 'cf', InMode),)CFTypeRef_methods.append(f)f = Function(CFStringRef, 'CFCopyTypeIDDescription',    (CFTypeID, 'type_id', InMode),)functions.append(f)f = Method(CFTypeRef, 'CFRetain',    (CFTypeRef, 'cf', InMode),)CFTypeRef_methods.append(f)f = Method(void, 'CFRelease',    (CFTypeRef, 'cf', InMode),)CFTypeRef_methods.append(f)f = Method(CFIndex, 'CFGetRetainCount',    (CFTypeRef, 'cf', InMode),)CFTypeRef_methods.append(f)f = Method(Boolean, 'CFEqual',    (CFTypeRef, 'cf1', InMode),    (CFTypeRef, 'cf2', InMode),)CFTypeRef_methods.append(f)f = Method(CFHashCode, 'CFHash',    (CFTypeRef, 'cf', InMode),)CFTypeRef_methods.append(f)f = Method(CFStringRef, 'CFCopyDescription',    (CFTypeRef, 'cf', InMode),)CFTypeRef_methods.append(f)f = Function(CFTypeID, 'CFArrayGetTypeID',)functions.append(f)f = MethodSkipArg1(CFArrayRef, 'CFArrayCreateCopy',    (CFAllocatorRef, 'allocator', InMode),    (CFArrayRef, 'theArray', InMode),)CFArrayRef_methods.append(f)f = Function(CFMutableArrayRef, 'CFArrayCreateMutable',    (CFAllocatorRef, 'allocator', InMode),    (CFIndex, 'capacity', InMode),    (CFArrayCallBacks_ptr, 'callBacks', InMode),)functions.append(f)f = Function(CFMutableArrayRef, 'CFArrayCreateMutableCopy',    (CFAllocatorRef, 'allocator', InMode),    (CFIndex, 'capacity', InMode),    (CFArrayRef, 'theArray', InMode),)functions.append(f)f = Method(CFIndex, 'CFArrayGetCount',    (CFArrayRef, 'theArray', InMode),)CFArrayRef_methods.append(f)f = Method(void, 'CFArrayRemoveValueAtIndex',    (CFMutableArrayRef, 'theArray', InMode),    (CFIndex, 'idx', InMode),)CFMutableArrayRef_methods.append(f)f = Method(void, 'CFArrayRemoveAllValues',    (CFMutableArrayRef, 'theArray', InMode),)CFMutableArrayRef_methods.append(f)f = Method(void, 'CFArrayExchangeValuesAtIndices',    (CFMutableArrayRef, 'theArray', InMode),    (CFIndex, 'idx1', InMode),    (CFIndex, 'idx2', InMode),)CFMutableArrayRef_methods.append(f)f = Method(void, 'CFArrayAppendArray',    (CFMutableArrayRef, 'theArray', InMode),    (CFArrayRef, 'otherArray', InMode),    (CFRange, 'otherRange', InMode),)CFMutableArrayRef_methods.append(f)f = Function(CFTypeID, 'CFDataGetTypeID',)functions.append(f)f = Function(CFDataRef, 'CFDataCreate',    (CFAllocatorRef, 'allocator', InMode),    (UcharInBuffer, 'bytes', InMode),)functions.append(f)f = Function(CFDataRef, 'CFDataCreateWithBytesNoCopy',    (CFAllocatorRef, 'allocator', InMode),    (UcharInBuffer, 'bytes', InMode),    (CFAllocatorRef, 'bytesDeallocator', InMode),)functions.append(f)f = MethodSkipArg1(CFDataRef, 'CFDataCreateCopy',    (CFAllocatorRef, 'allocator', InMode),    (CFDataRef, 'theData', InMode),)CFDataRef_methods.append(f)f = Function(CFMutableDataRef, 'CFDataCreateMutable',    (CFAllocatorRef, 'allocator', InMode),    (CFIndex, 'capacity', InMode),)functions.append(f)f = Function(CFMutableDataRef, 'CFDataCreateMutableCopy',    (CFAllocatorRef, 'allocator', InMode),    (CFIndex, 'capacity', InMode),    (CFDataRef, 'theData', InMode),)functions.append(f)f = Method(CFIndex, 'CFDataGetLength',    (CFDataRef, 'theData', InMode),)CFDataRef_methods.append(f)f = Method(void, 'CFDataSetLength',    (CFMutableDataRef, 'theData', InMode),    (CFIndex, 'length', InMode),)CFMutableDataRef_methods.append(f)f = Method(void, 'CFDataIncreaseLength',    (CFMutableDataRef, 'theData', InMode),    (CFIndex, 'extraLength', InMode),)CFMutableDataRef_methods.append(f)f = Method(void, 'CFDataAppendBytes',    (CFMutableDataRef, 'theData', InMode),    (UcharInBuffer, 'bytes', InMode),)CFMutableDataRef_methods.append(f)f = Method(void, 'CFDataReplaceBytes',    (CFMutableDataRef, 'theData', InMode),    (CFRange, 'range', InMode),    (UcharInBuffer, 'newBytes', InMode),)CFMutableDataRef_methods.append(f)f = Method(void, 'CFDataDeleteBytes',    (CFMutableDataRef, 'theData', InMode),    (CFRange, 'range', InMode),)CFMutableDataRef_methods.append(f)f = Function(CFTypeID, 'CFDictionaryGetTypeID',)functions.append(f)f = MethodSkipArg1(CFDictionaryRef, 'CFDictionaryCreateCopy',    (CFAllocatorRef, 'allocator', InMode),    (CFDictionaryRef, 'theDict', InMode),)CFDictionaryRef_methods.append(f)f = Function(CFMutableDictionaryRef, 'CFDictionaryCreateMutable',    (CFAllocatorRef, 'allocator', InMode),    (CFIndex, 'capacity', InMode),    (CFDictionaryKeyCallBacks_ptr, 'keyCallBacks', InMode),    (CFDictionaryValueCallBacks_ptr, 'valueCallBacks', InMode),)functions.append(f)f = Function(CFMutableDictionaryRef, 'CFDictionaryCreateMutableCopy',    (CFAllocatorRef, 'allocator', InMode),    (CFIndex, 'capacity', InMode),    (CFDictionaryRef, 'theDict', InMode),)functions.append(f)f = Method(CFIndex, 'CFDictionaryGetCount',    (CFDictionaryRef, 'theDict', InMode),)CFDictionaryRef_methods.append(f)f = Method(void, 'CFDictionaryRemoveAllValues',    (CFMutableDictionaryRef, 'theDict', InMode),)CFMutableDictionaryRef_methods.append(f)f = Function(CFTypeID, 'CFStringGetTypeID',)functions.append(f)f = Function(CFStringRef, 'CFStringCreateWithPascalString',    (CFAllocatorRef, 'alloc', InMode),    (ConstStr255Param, 'pStr', InMode),    (CFStringEncoding, 'encoding', InMode),)functions.append(f)f = Function(CFStringRef, 'CFStringCreateWithCString',    (CFAllocatorRef, 'alloc', InMode),    (char_ptr, 'cStr', InMode),    (CFStringEncoding, 'encoding', InMode),)functions.append(f)f = Function(CFStringRef, 'CFStringCreateWithPascalStringNoCopy',    (CFAllocatorRef, 'alloc', InMode),    (ConstStr255Param, 'pStr', InMode),    (CFStringEncoding, 'encoding', InMode),    (CFAllocatorRef, 'contentsDeallocator', InMode),)functions.append(f)f = Function(CFStringRef, 'CFStringCreateWithCStringNoCopy',    (CFAllocatorRef, 'alloc', InMode),    (char_ptr, 'cStr', InMode),    (CFStringEncoding, 'encoding', InMode),    (CFAllocatorRef, 'contentsDeallocator', InMode),)functions.append(f)f = MethodSkipArg1(CFStringRef, 'CFStringCreateWithSubstring',    (CFAllocatorRef, 'alloc', InMode),    (CFStringRef, 'str', InMode),    (CFRange, 'range', InMode),)CFStringRef_methods.append(f)f = MethodSkipArg1(CFStringRef, 'CFStringCreateCopy',    (CFAllocatorRef, 'alloc', InMode),    (CFStringRef, 'theString', InMode),)CFStringRef_methods.append(f)f = Function(CFMutableStringRef, 'CFStringCreateMutable',    (CFAllocatorRef, 'alloc', InMode),    (CFIndex, 'maxLength', InMode),)functions.append(f)f = Function(CFMutableStringRef, 'CFStringCreateMutableCopy',    (CFAllocatorRef, 'alloc', InMode),    (CFIndex, 'maxLength', InMode),    (CFStringRef, 'theString', InMode),)functions.append(f)f = Method(CFIndex, 'CFStringGetLength',    (CFStringRef, 'theString', InMode),)CFStringRef_methods.append(f)f = Method(CFIndex, 'CFStringGetBytes',    (CFStringRef, 'theString', InMode),    (CFRange, 'range', InMode),    (CFStringEncoding, 'encoding', InMode),    (UInt8, 'lossByte', InMode),    (Boolean, 'isExternalRepresentation', InMode),    (UInt8, 'buffer', OutMode),    (CFIndex, 'maxBufLen', InMode),    (CFIndex, 'usedBufLen', OutMode),)CFStringRef_methods.append(f)f = Function(CFStringRef, 'CFStringCreateWithBytes',    (CFAllocatorRef, 'alloc', InMode),    (UcharInBuffer, 'bytes', InMode),    (CFStringEncoding, 'encoding', InMode),    (Boolean, 'isExternalRepresentation', InMode),)functions.append(f)f = MethodSkipArg1(CFStringRef, 'CFStringCreateFromExternalRepresentation',    (CFAllocatorRef, 'alloc', InMode),    (CFDataRef, 'data', InMode),    (CFStringEncoding, 'encoding', InMode),)CFDataRef_methods.append(f)f = MethodSkipArg1(CFDataRef, 'CFStringCreateExternalRepresentation',    (CFAllocatorRef, 'alloc', InMode),    (CFStringRef, 'theString', InMode),    (CFStringEncoding, 'encoding', InMode),    (UInt8, 'lossByte', InMode),)CFStringRef_methods.append(f)f = Method(CFStringEncoding, 'CFStringGetSmallestEncoding',    (CFStringRef, 'theString', InMode),)CFStringRef_methods.append(f)f = Method(CFStringEncoding, 'CFStringGetFastestEncoding',    (CFStringRef, 'theString', InMode),)CFStringRef_methods.append(f)f = Function(CFStringEncoding, 'CFStringGetSystemEncoding',)functions.append(f)f = Function(CFIndex, 'CFStringGetMaximumSizeForEncoding',    (CFIndex, 'length', InMode),    (CFStringEncoding, 'encoding', InMode),)functions.append(f)f = Method(CFComparisonResult, 'CFStringCompareWithOptions',    (CFStringRef, 'theString1', InMode),    (CFStringRef, 'theString2', InMode),    (CFRange, 'rangeToCompare', InMode),    (CFOptionFlags, 'compareOptions', InMode),)CFStringRef_methods.append(f)f = Method(CFComparisonResult, 'CFStringCompare',    (CFStringRef, 'theString1', InMode),    (CFStringRef, 'theString2', InMode),    (CFOptionFlags, 'compareOptions', InMode),)CFStringRef_methods.append(f)f = Method(Boolean, 'CFStringFindWithOptions',    (CFStringRef, 'theString', InMode),    (CFStringRef, 'stringToFind', InMode),    (CFRange, 'rangeToSearch', InMode),    (CFOptionFlags, 'searchOptions', InMode),    (CFRange, 'result', OutMode),)CFStringRef_methods.append(f)f = MethodSkipArg1(CFArrayRef, 'CFStringCreateArrayWithFindResults',    (CFAllocatorRef, 'alloc', InMode),    (CFStringRef, 'theString', InMode),    (CFStringRef, 'stringToFind', InMode),    (CFRange, 'rangeToSearch', InMode),    (CFOptionFlags, 'compareOptions', InMode),)CFStringRef_methods.append(f)f = Method(CFRange, 'CFStringFind',    (CFStringRef, 'theString', InMode),    (CFStringRef, 'stringToFind', InMode),    (CFOptionFlags, 'compareOptions', InMode),)CFStringRef_methods.append(f)f = Method(Boolean, 'CFStringHasPrefix',    (CFStringRef, 'theString', InMode),    (CFStringRef, 'prefix', InMode),)CFStringRef_methods.append(f)f = Method(Boolean, 'CFStringHasSuffix',    (CFStringRef, 'theString', InMode),    (CFStringRef, 'suffix', InMode),)CFStringRef_methods.append(f)f = Method(void, 'CFStringGetLineBounds',    (CFStringRef, 'theString', InMode),    (CFRange, 'range', InMode),    (CFIndex, 'lineBeginIndex', OutMode),    (CFIndex, 'lineEndIndex', OutMode),    (CFIndex, 'contentsEndIndex', OutMode),)CFStringRef_methods.append(f)f = MethodSkipArg1(CFStringRef, 'CFStringCreateByCombiningStrings',    (CFAllocatorRef, 'alloc', InMode),    (CFArrayRef, 'theArray', InMode),    (CFStringRef, 'separatorString', InMode),)CFArrayRef_methods.append(f)f = MethodSkipArg1(CFArrayRef, 'CFStringCreateArrayBySeparatingStrings',    (CFAllocatorRef, 'alloc', InMode),    (CFStringRef, 'theString', InMode),    (CFStringRef, 'separatorString', InMode),)CFStringRef_methods.append(f)f = Method(SInt32, 'CFStringGetIntValue',    (CFStringRef, 'str', InMode),)CFStringRef_methods.append(f)f = Method(double, 'CFStringGetDoubleValue',    (CFStringRef, 'str', InMode),)CFStringRef_methods.append(f)f = Method(void, 'CFStringAppend',    (CFMutableStringRef, 'theString', InMode),    (CFStringRef, 'appendedString', InMode),)CFMutableStringRef_methods.append(f)f = Method(void, 'CFStringAppendPascalString',    (CFMutableStringRef, 'theString', InMode),    (ConstStr255Param, 'pStr', InMode),    (CFStringEncoding, 'encoding', InMode),)CFMutableStringRef_methods.append(f)f = Method(void, 'CFStringAppendCString',    (CFMutableStringRef, 'theString', InMode),    (char_ptr, 'cStr', InMode),    (CFStringEncoding, 'encoding', InMode),)CFMutableStringRef_methods.append(f)f = Method(void, 'CFStringInsert',    (CFMutableStringRef, 'str', InMode),    (CFIndex, 'idx', InMode),    (CFStringRef, 'insertedStr', InMode),)CFMutableStringRef_methods.append(f)f = Method(void, 'CFStringDelete',    (CFMutableStringRef, 'theString', InMode),    (CFRange, 'range', InMode),)CFMutableStringRef_methods.append(f)f = Method(void, 'CFStringReplace',    (CFMutableStringRef, 'theString', InMode),    (CFRange, 'range', InMode),    (CFStringRef, 'replacement', InMode),)CFMutableStringRef_methods.append(f)f = Method(void, 'CFStringReplaceAll',    (CFMutableStringRef, 'theString', InMode),    (CFStringRef, 'replacement', InMode),)CFMutableStringRef_methods.append(f)f = Method(void, 'CFStringPad',    (CFMutableStringRef, 'theString', InMode),    (CFStringRef, 'padString', InMode),    (CFIndex, 'length', InMode),    (CFIndex, 'indexIntoPad', InMode),)CFMutableStringRef_methods.append(f)f = Method(void, 'CFStringTrim',    (CFMutableStringRef, 'theString', InMode),    (CFStringRef, 'trimString', InMode),)CFMutableStringRef_methods.append(f)f = Method(void, 'CFStringTrimWhitespace',    (CFMutableStringRef, 'theString', InMode),)CFMutableStringRef_methods.append(f)f = Function(Boolean, 'CFStringIsEncodingAvailable',    (CFStringEncoding, 'encoding', InMode),)functions.append(f)f = Function(CFStringRef, 'CFStringGetNameOfEncoding',    (CFStringEncoding, 'encoding', InMode),)functions.append(f)f = Function(UInt32, 'CFStringConvertEncodingToNSStringEncoding',    (CFStringEncoding, 'encoding', InMode),)functions.append(f)f = Function(CFStringEncoding, 'CFStringConvertNSStringEncodingToEncoding',    (UInt32, 'encoding', InMode),)functions.append(f)f = Function(UInt32, 'CFStringConvertEncodingToWindowsCodepage',    (CFStringEncoding, 'encoding', InMode),)functions.append(f)f = Function(CFStringEncoding, 'CFStringConvertWindowsCodepageToEncoding',    (UInt32, 'codepage', InMode),)functions.append(f)f = Method(CFStringEncoding, 'CFStringConvertIANACharSetNameToEncoding',    (CFStringRef, 'theString', InMode),)CFStringRef_methods.append(f)f = Function(CFStringRef, 'CFStringConvertEncodingToIANACharSetName',    (CFStringEncoding, 'encoding', InMode),)functions.append(f)f = Function(CFStringEncoding, 'CFStringGetMostCompatibleMacStringEncoding',    (CFStringEncoding, 'encoding', InMode),)functions.append(f)f = Method(void, 'CFShow',    (CFTypeRef, 'obj', InMode),)CFTypeRef_methods.append(f)f = Method(void, 'CFShowStr',    (CFStringRef, 'str', InMode),)CFStringRef_methods.append(f)f = Function(CFStringRef, '__CFStringMakeConstantString',    (char_ptr, 'cStr', InMode),)functions.append(f)f = Function(CFTypeID, 'CFURLGetTypeID',)functions.append(f)f = Function(CFURLRef, 'CFURLCreateWithBytes',    (CFAllocatorRef, 'allocator', InMode),    (UcharInBuffer, 'URLBytes', InMode),    (CFStringEncoding, 'encoding', InMode),    (OptionalCFURLRef, 'baseURL', InMode),)functions.append(f)f = MethodSkipArg1(CFDataRef, 'CFURLCreateData',    (CFAllocatorRef, 'allocator', InMode),    (CFURLRef, 'url', InMode),    (CFStringEncoding, 'encoding', InMode),    (Boolean, 'escapeWhitespace', InMode),)CFURLRef_methods.append(f)f = MethodSkipArg1(CFURLRef, 'CFURLCreateWithString',    (CFAllocatorRef, 'allocator', InMode),    (CFStringRef, 'URLString', InMode),    (OptionalCFURLRef, 'baseURL', InMode),)CFStringRef_methods.append(f)f = MethodSkipArg1(CFURLRef, 'CFURLCreateWithFileSystemPath',    (CFAllocatorRef, 'allocator', InMode),    (CFStringRef, 'filePath', InMode),    (CFURLPathStyle, 'pathStyle', InMode),    (Boolean, 'isDirectory', InMode),)CFStringRef_methods.append(f)f = Function(CFURLRef, 'CFURLCreateFromFileSystemRepresentation',    (CFAllocatorRef, 'allocator', InMode),    (UcharInBuffer, 'buffer', InMode),    (Boolean, 'isDirectory', InMode),)functions.append(f)f = MethodSkipArg1(CFURLRef, 'CFURLCreateWithFileSystemPathRelativeToBase',    (CFAllocatorRef, 'allocator', InMode),    (CFStringRef, 'filePath', InMode),    (CFURLPathStyle, 'pathStyle', InMode),    (Boolean, 'isDirectory', InMode),    (OptionalCFURLRef, 'baseURL', InMode),)CFStringRef_methods.append(f)f = Function(CFURLRef, 'CFURLCreateFromFileSystemRepresentationRelativeToBase',    (CFAllocatorRef, 'allocator', InMode),    (UcharInBuffer, 'buffer', InMode),    (Boolean, 'isDirectory', InMode),    (OptionalCFURLRef, 'baseURL', InMode),)functions.append(f)f = Method(Boolean, 'CFURLGetFileSystemRepresentation',    (CFURLRef, 'url', InMode),    (Boolean, 'resolveAgainstBase', InMode),    (UInt8, 'buffer', OutMode),    (CFIndex, 'maxBufLen', InMode),)CFURLRef_methods.append(f)f = Method(CFURLRef, 'CFURLCopyAbsoluteURL',    (CFURLRef, 'relativeURL', InMode),)CFURLRef_methods.append(f)f = Method(CFStringRef, 'CFURLGetString',    (CFURLRef, 'anURL', InMode),)CFURLRef_methods.append(f)f = Method(CFURLRef, 'CFURLGetBaseURL',    (CFURLRef, 'anURL', InMode),)CFURLRef_methods.append(f)f = Method(Boolean, 'CFURLCanBeDecomposed',    (CFURLRef, 'anURL', InMode),)CFURLRef_methods.append(f)f = Method(CFStringRef, 'CFURLCopyScheme',    (CFURLRef, 'anURL', InMode),)CFURLRef_methods.append(f)f = Method(CFStringRef, 'CFURLCopyNetLocation',    (CFURLRef, 'anURL', InMode),)CFURLRef_methods.append(f)f = Method(CFStringRef, 'CFURLCopyPath',    (CFURLRef, 'anURL', InMode),)CFURLRef_methods.append(f)f = Method(CFStringRef, 'CFURLCopyStrictPath',    (CFURLRef, 'anURL', InMode),    (Boolean, 'isAbsolute', OutMode),)CFURLRef_methods.append(f)f = Method(CFStringRef, 'CFURLCopyFileSystemPath',    (CFURLRef, 'anURL', InMode),    (CFURLPathStyle, 'pathStyle', InMode),)CFURLRef_methods.append(f)f = Method(Boolean, 'CFURLHasDirectoryPath',    (CFURLRef, 'anURL', InMode),)CFURLRef_methods.append(f)f = Method(CFStringRef, 'CFURLCopyResourceSpecifier',    (CFURLRef, 'anURL', InMode),)CFURLRef_methods.append(f)f = Method(CFStringRef, 'CFURLCopyHostName',    (CFURLRef, 'anURL', InMode),)CFURLRef_methods.append(f)f = Method(SInt32, 'CFURLGetPortNumber',    (CFURLRef, 'anURL', InMode),)CFURLRef_methods.append(f)f = Method(CFStringRef, 'CFURLCopyUserName',    (CFURLRef, 'anURL', InMode),)CFURLRef_methods.append(f)f = Method(CFStringRef, 'CFURLCopyPassword',    (CFURLRef, 'anURL', InMode),)CFURLRef_methods.append(f)f = Method(CFStringRef, 'CFURLCopyParameterString',    (CFURLRef, 'anURL', InMode),    (CFStringRef, 'charactersToLeaveEscaped', InMode),)CFURLRef_methods.append(f)f = Method(CFStringRef, 'CFURLCopyQueryString',    (CFURLRef, 'anURL', InMode),    (CFStringRef, 'charactersToLeaveEscaped', InMode),)CFURLRef_methods.append(f)f = Method(CFStringRef, 'CFURLCopyFragment',    (CFURLRef, 'anURL', InMode),    (CFStringRef, 'charactersToLeaveEscaped', InMode),)CFURLRef_methods.append(f)f = Method(CFStringRef, 'CFURLCopyLastPathComponent',    (CFURLRef, 'url', InMode),)CFURLRef_methods.append(f)f = Method(CFStringRef, 'CFURLCopyPathExtension',    (CFURLRef, 'url', InMode),)CFURLRef_methods.append(f)f = MethodSkipArg1(CFURLRef, 'CFURLCreateCopyAppendingPathComponent',    (CFAllocatorRef, 'allocator', InMode),    (CFURLRef, 'url', InMode),    (CFStringRef, 'pathComponent', InMode),    (Boolean, 'isDirectory', InMode),)CFURLRef_methods.append(f)f = MethodSkipArg1(CFURLRef, 'CFURLCreateCopyDeletingLastPathComponent',    (CFAllocatorRef, 'allocator', InMode),    (CFURLRef, 'url', InMode),)CFURLRef_methods.append(f)f = MethodSkipArg1(CFURLRef, 'CFURLCreateCopyAppendingPathExtension',    (CFAllocatorRef, 'allocator', InMode),    (CFURLRef, 'url', InMode),    (CFStringRef, 'extension', InMode),)CFURLRef_methods.append(f)f = MethodSkipArg1(CFURLRef, 'CFURLCreateCopyDeletingPathExtension',    (CFAllocatorRef, 'allocator', InMode),    (CFURLRef, 'url', InMode),)CFURLRef_methods.append(f)f = MethodSkipArg1(CFStringRef, 'CFURLCreateStringByReplacingPercentEscapes',    (CFAllocatorRef, 'allocator', InMode),    (CFStringRef, 'originalString', InMode),    (CFStringRef, 'charactersToLeaveEscaped', InMode),)CFStringRef_methods.append(f)f = MethodSkipArg1(CFStringRef, 'CFURLCreateStringByAddingPercentEscapes',    (CFAllocatorRef, 'allocator', InMode),    (CFStringRef, 'originalString', InMode),    (CFStringRef, 'charactersToLeaveUnescaped', InMode),    (CFStringRef, 'legalURLCharactersToBeEscaped', InMode),    (CFStringEncoding, 'encoding', InMode),)CFStringRef_methods.append(f)f = Function(CFURLRef, 'CFURLCreateFromFSRef',    (CFAllocatorRef, 'allocator', InMode),    (FSRef_ptr, 'fsRef', InMode),)functions.append(f)f = Method(Boolean, 'CFURLGetFSRef',    (CFURLRef, 'url', InMode),    (FSRef, 'fsRef', OutMode),)CFURLRef_methods.append(f)