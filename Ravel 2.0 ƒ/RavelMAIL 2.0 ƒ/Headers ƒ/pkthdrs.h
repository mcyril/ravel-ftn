#define PKTVER	2struct _pkthdr{        short orig_node;         /* originating node               */        short dest_node;         /* destination node               */        short year;              /* 0..99  when packet was created */        short month;             /* 0..11  when packet was created */        short day;               /* 1..31  when packet was created */        short hour;              /* 0..23  when packet was created */        short minute;            /* 0..59  when packet was created */        short second;            /* 0..59  when packet was created */        short rate;              /* destination's baud rate        */        short ver;               /* packet version                 */        short orig_net;          /* originating network number     */        short dest_net;          /* destination network number     */        char product;           /* product type                   */        char serial;            /* serial number (some systems)   */   /* ------------------------------ */   /* THE FOLLOWING SECTION IS NOT   */   /* THE SAME ACROSS SYSTEM LINES:  */   /* ------------------------------ */        unsigned char password[8];       /* session/pickup password        */        short  orig_zone;        /* originating zone               */        short  dest_zone;        /* Destination zone               */        unsigned char B_fill2[16];        long B_fill3;};struct _pkthdr_o{	short orig_node;				/* originating node               */	short dest_node;				/* destination node               */	short year;						/* 0..99  when packet was created */	short month;					/* 0..11  when packet was created */	short day;						/* 1..31  when packet was created */	short hour;						/* 0..23  when packet was created */	short minute;					/* 0..59  when packet was created */	short second;					/* 0..59  when packet was created */	short rate;						/* destination's baud rate        */	short ver;						/* packet version, must be 2      */	short orig_net;					/* originating network number     */	short dest_net;					/* destination network number     */	char product;					/* product type                   */	char serial;					/* serial number (some systems)   */	unsigned char password[8];		/* session/pickup password        */	short orig_zone;				/* originating zone               */	short dest_zone;				/* Destination zone               */	unsigned char B_fill2[16];	long B_fill3;};struct _pkthdr45					/* FSC-0045 (Type 2.2) packet type*/{	short orig_node;				/* originating node               */	short dest_node;				/* destination node               */	short orig_point;				/* originating point              */	short dest_point;				/* destination point              */	unsigned char b_fill1[8];		/* Unused, must be zero           */	short subver;					/* packet subversion, must be 2   */	short ver;						/* packet version, must be 2      */	short orig_net;					/* originating network number     */	short dest_net;					/* destination network number     */	char product;					/* product type                   */	char serial;					/* serial number (some systems)   */	unsigned char password[8];		/* session/pickup password        */	short orig_zone;				/* originating zone               */	short dest_zone;				/* Destination zone               */	unsigned char orig_domain[8];	/* originating domain             */	unsigned char dest_domain[8];	/* destination domain             */	long B_fill3;};struct _pkthdr39					/* FSC-0039 (Type 2) packet type  */{	short orig_node;				/* originating node               */	short dest_node;				/* destination node               */	short year;						/* 0..99  when packet was created */	short month;					/* 0..11  when packet was created */	short day;						/* 1..31  when packet was created */	short hour;						/* 0..23  when packet was created */	short minute;					/* 0..59  when packet was created */	short second;					/* 0..59  when packet was created */	short rate;						/* destination's baud rate        */	short ver;						/* packet version, must be 2      */	short orig_net;					/* originating network number     */	short dest_net;					/* destination network number     */	unsigned char product_low;		/* FTSC product type (low unsigned char)   */	unsigned char prod_rev_low;		/* product rev (low unsigned char)         */	unsigned char password[8];		/* session/pickup password        */	short zone_ignore[2];			/* Zone info from other software  */	unsigned char B_fill1[2];	short CapValid;					/* CapWord with bytes swapped.    */	unsigned char product_hi;		/* FTSC product type (high unsigned char)  */	unsigned char prod_rev_hi;		/* product rev (hi unsigned char)          */	short CapWord;					/* Capability word                */	short orig_zone;				/* originating zone               */	short dest_zone;				/* Destination zone               */	short orig_point;				/* originating point              */	short dest_point;				/* destination point              */	long ProdData;					/* Product-specific data          */};