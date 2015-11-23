
/*
 * COPYRIGHT 1992 SAMUEL H. SMITH
 * ALL RIGHTS RESERVED
 *
 * THIS DOCUMENT CONTAINS CONFIDENTIAL INFORMATION AND TRADE SECRETS
 * PROPRIETARY TO SAMUEL H. SMITH DBA THE TOOL SHOP.
 *
 */


/*
 * hsbuf - HS/Link Buffered File I/O Unit
 *
 */

typedef struct buffered_file {	/* buffered file description record */
	char pathname[256];	/* full name of the file */
	int handle;		/* handle for dos calls */
	unsigned maxrec;	/* maximum number of records */
	unsigned recsiz;	/* record size */
	unsigned bufsiz;	/* size of the data buffer */
        unsigned filerecs;      /* count of records in existing files */
        uchar *buffer;          /* the data buffer */
	unsigned fptr;		/* base record in file for buffer */
	unsigned fnext;		/* next record position in buffer (0=first) */
	unsigned fcount;	/* count of records in buffer */
        uchar dirty;            /* unsaved changes in buffer? */
        uchar berr;             /* error flag - true if read/write failure */
} buffered_file;

pascal void bcreate(char *name);       /* create an empty file; use with
                                        * bopen to open output files */

pascal void bprepare(buffered_file *bfd,
                     int fd,
                     unsigned maxbufm,
                     unsigned recsize); /* enable buffering on an already
					 * open dos handle */

pascal void bopen(buffered_file *bfd,
                  char *name,
                  unsigned maxbufm,
                  unsigned recsize,
                  int openmode);        /* open a buffered file -
                                         * sets 'berr' if not ok */

pascal void bflush(buffered_file *bfd);  /* write buffer, force re-read on
					 * next access */

pascal void bseek(buffered_file *bfd,
                  unsigned recn);      /* set position of buffered file */

pascal void bseekeof(buffered_file *bfd);
                                        /* set position of buffered file to
					 * end-of-file */

pascal unsigned int btell(buffered_file *bfd);
                                        /* tell current record number in
					 * buffered file */

pascal char beof(buffered_file *bfd);   /* check for eof on buffered file */

pascal void bread(buffered_file *bfd,
                  uchar *dest);         /* buffered read */

pascal void bwrite(buffered_file *bfd,
                   uchar *src);         /* buffered write */

pascal void bclose(buffered_file *bfd); /* close a buffered file */

pascal void bclose_set(buffered_file *bfd,
                       long filesize,
                       unsigned long time);
                                        /* close a buffered file, set exact
					 * file size and time stamp */

pascal int bgetline(char *buf, int size, buffered_file *fd);

//pascal void getftime(int handle, unsigned long *time);
pascal void getftime(char *name, unsigned long *time);

//pascal void setftime(int handle, unsigned long time);
pascal void setftime(char *name, unsigned long time);
