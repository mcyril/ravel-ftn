typedef struct __times {	Byte	hour;	Byte	minute;	} _times;typedef struct __perod {	_times	Start;	_times	End;} _period;typedef _period one_evt[7];typedef one_evt **eventsHndl;typedef struct _behave {	short		evtNum;	short		mode;	short		nodeNum;	char		cmd[10];	} behave;typedef struct _bahavior {	short		countOfBehave;		behave		behavior[];	} behaviorType, *behaviorPtr, **behaviorHndl;void	InitEvents (void);long	GotCurrentEvtMask (void);Boolean	inPeriod (_times, eventsHndl, short);Boolean	CheckHappened (void);char	*printEvent (long, char *);Boolean CheckEventNow ( long );void	doCommandForSHUFFLER (char *);Boolean	Misbehave (void);Boolean	letsMisbehave (void);Boolean	ApplicationLaunch ( StringPtr );