#define	PMODE_TOUCH		0#define	PMODE_FORBASE	1#define	PMODE_TRANSIT	2#define	PMODE_PREPNEW	3void		parse_kludges (short mode, pktmsg *m, pktmsg **d, juncted *newseen, juncted *newpath, addr *currentAka);void		FreePktMsg ( pktmsg *p );pktmsg		*GetPktMsg (short fp, pktheader *ph);pktmsg		*ClonePktMsg(pktmsg *m);void		AddPKTHeadToPKTFile (short pktRefNum, pktheader *p);void		AddMessageToPKTFile (short pktRefNum, pktmsg *m, addr *from);pktheader	*GetPktHeader ( short fp );void		FreePktHeader ( pktheader *p );Boolean iskfalist ( juncted *kf, addr *f );void add_to_other (pktmsg *m, char *dest, addr *from, char *reason);Boolean		cmp2addrs ( addr *my1, addr *my2 );