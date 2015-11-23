/*--------------------------------------------------------------------------*//* WaZOO                                                                    *//*--------------------------------------------------------------------------*/#ifndef ACK#define ACK    0x06#endif#ifndef NAK#define NAK    0x15#endif#ifndef ENQ#define ENQ    0x05#endif#ifndef YOOHOO#define YOOHOO 0x00f1#endif#ifndef  TSYNC#define  TSYNC 0x00ae#endifstruct _Hello{	unsigned short	signal;				/* always 'o'     (0x6f)                   */	unsigned short	hello_version;		/* currently 1    (0x01)                   */	unsigned short	product;			/* product code                            */	unsigned short	product_maj;		/* major revision of the product           */	unsigned short	product_min;		/* minor revision of the product           */	char			my_name[60];		/* Other end's name                        */	char			sysop[20];			/* sysop's name                            */	unsigned short	my_zone;			/* 0== not supported                       */	unsigned short	my_net;				/* out primary net number                  */	unsigned short	my_node;			/* our primary node number                 */	unsigned short	my_point;			/* 0== not supported                       */	unsigned char	my_password[8];		/* ALL 8 CHARACTERS ARE SIGNIFICANT !!!!!  */	unsigned char	reserved2[8];		/* reserved by Opus                        */	unsigned short	capabilities;		/* see below                               */	unsigned char	reserved3[12];		/* available to non-Opus                   */										/* systems by prior "approval" of 124/108. */};										/* size 128 bytes *//*--------------------------------------------------------------------------*//* YOOHOO<tm> CAPABILITY VALUES                                             *//*--------------------------------------------------------------------------*/#define Y_DIETIFNA	0x0001#define FTB_USER	0x0002#define ZED_ZIPPER	0x0004#define ZED_ZAPPER	0x0008#define DOES_IANUS	0x0010#define DOES_HYDRA	0x0020#define Bit_6		0x0040#define Bit_7		0x0080#define Bit_8		0x0100#define Bit_9		0x0200#define Bit_a		0x0400#define Bit_b		0x0800#define DIR_ZAPPER	0x1000#define Bit_d		0x2000#define DO_DOMAIN	0x4000#define WZ_FREQ		0x8000/*--------------------------------------------------------------------------*//* EMSI                                                                     *//*--------------------------------------------------------------------------*//* Indexes into the emsistr array for use by EMSI parsing */#define EMSI_REQ   0#define EMSI_DAT   1#define EMSI_HBT   2#define EMSI_NAK   3#define EMSI_ACK   4#define EMSI_INQ   5#define EMSI_CLI   6#define EMSI_LEN   14     /* longest emsi string */#define EMSI_MAX   6      /* highest emsi string */