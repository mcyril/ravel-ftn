extern	Boolean	needfilter;extern	Str255	replyaddr;void	callFilter ( Handle text );void	forwardFilter (Handle text);void	parseForInternetReply ( Handle text, char *toname, addr *to );short	parseForCC (Handle text);