#include "Utils.h"Boolean GetASCIIZ ( short fromfile, char *dest, short limit ){	char		buff[256];	long		counter;	short		i;	counter = 256L;	FSRead ( fromfile, &counter, &buff );	SetFPos ( fromfile, 3, -counter );		for ( i=0; i<counter; i++ )	{		if (buff[i])			dest[i] = buff[i];		else			break;					if ( i >= limit )		{			i = 0;			break;		}	}	//	if ( !i )//		return FALSE;		dest[i] = 0;	SetFPos ( fromfile, 3, i+1 );		return TRUE;}Boolean GetMSGText ( short fromfile, Handle dest ){	char		buff[256];	long		counter, pos;	short		i;		SetHandleSize ( dest, 0L );	pos = 0L;		do {				counter = 256L;		FSRead ( fromfile, &counter, buff );		if ( counter )		{			for ( i=0; i<counter; i++ )				if (!buff[i])					break;						SetHandleSize ( dest, pos+i );			BlockMove ( buff, *dest+pos, i );			pos += i;						if ( i < counter )				break;		}	} while (counter);//	if (!counter)					//	�	why? Empty message is possible!//	{//		SetHandleSize ( dest, 0L );//		return FALSE;//	}	SetHandleSize ( dest, pos+1 );	*((char *)(*dest+pos)) = 0;	SetFPos ( fromfile, 3, -(counter-i-1) );	return TRUE;}