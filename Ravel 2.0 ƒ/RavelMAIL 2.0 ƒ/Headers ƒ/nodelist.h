void ReadNodeList (void);void CloseNodeList (void);Boolean GetNodeInfo (addr *, StringPtr);Boolean GetNameFromAddr (addr *, StringPtr);Boolean GetPhoneFromAddr (addr *address, StringPtr result);Boolean GetInfoFromAddr (addr *address, StringPtr result);Boolean GetTimesFromAddr (addr *address, _period *result);Boolean yep (void);short adjust (addr *tempaddr);short ZoneByIndex (short);short NetByIndex (short inx, addr *address);short NodeByIndex (short inx, addr *address);short PointByIndex (short inx, addr *address);long lookupZoneIndex (short);long lookupNetIndex (long, short);long lookupNodeIndex (long, short);short gotline (short nl_level, addr *nl_addr);Boolean hasSequence (short, addr *);