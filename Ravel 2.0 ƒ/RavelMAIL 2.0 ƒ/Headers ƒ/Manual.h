void	AddManual ( addr *, StringPtr, StringPtr, StringPtr, Boolean, short, Boolean );void	OverrideManual (addr *addtoaddr, short tempstop, Boolean do_tempstop, Boolean add_badcount, Boolean kill_badcount, Boolean do_force);void	KillManual ( addr * );void	PathNameFromDirID ( long dirID, short vRefNum, StringPtr fullPathName );void	PathNameFromWD ( long vRefNum, StringPtr pathName );void	ManualRequest ( void );void	ManualAttach ( void );void	KillManualPoll (in_outboundPtr do_over);void	EditManualPoll (in_outboundPtr do_over);void	ManualPoll (in_outboundPtr do_over);void	ChangeFlavorPoll (in_outboundPtr do_over);