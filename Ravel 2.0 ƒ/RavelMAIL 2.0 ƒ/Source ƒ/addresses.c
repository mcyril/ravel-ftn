#include <ctype.h>#include <stdlib.h>#include <string.h>#include "Ravel_FTN.h"#include "Ravel_Prefs.h"#include "compatible.h"#include "addresses.h"/* * Parse a string for a fidonet address * d is space for a domain string. * * (A better method) */static short find_addr (char *s, ADDR *addr, char *d){    short ret = 0;    register char *s1, *s2;    d[0] = 0;               /* Null the domain */	addr->Domain = NULL;    /* Find Zone */    s1 = strchr(s, ':');    if(s1)    {        addr->Zone = atoi(s);        s = s1+1;        ret++;    }	else		addr->Zone = 0;    /* Find Net */    s1 = strchr(s, '/');    if(s1)    {        addr->Net = atoi(s);        s = s1+1;        ret++;    }    else		addr->Net = 0;    /* Find Node */	if(isdigit(*s))	{	    addr->Node = atoi(s);	    ret++;	}//	else//		addr->Node = alias[0].ad.Node;    /* Find point & domain */    s1 = strchr(s, '.');       s2 = strchr(s, '@');    if(s1 && !(s2 && (s1 > s2)))        /* check if it's a real point*/    {        s = s1+1;        addr->Point = atoi(s);        ret++;    }    else        addr->Point = 0;       if(s2)    {//		s = skip_blanks(s2+1);		/* Polling causes "address @ domain" to be parsed! */				for ( s = s2+1; *s && isspace (*s); s++ );		while(*s && !isspace(*s))			*d++ = *s++;		*d = 0;		ret++;    }    return ret;}/* * Read in an address with wildcards * * Similar to find_addr but accepts ALL as a field * returns number of fields (0=none) * * There must be a neater way to do this! * * Format is: * *  [[[z:]net/]node][.point][@domain[.ext]] *  ALL *  z:ALL *  z:net/ALL *  z:net/node.ALL  * * Any field may be ALL or if ALL is the end of the address all other fields * default to ALL. *short read_wild_ad(char *node, ADKEY *dest){    short ret = 0;    register char *s1, *s2, *s;	s = node;//	* Check for ALL *		if( (strcmp(s, "ALL") == 0) || (strcmp(s, "*") == 0))	{		dest->wild.zone = TRUE;				dest->wild.net = TRUE;				dest->wild.node = TRUE;				dest->wild.point = TRUE;				dest->wild.domain = TRUE;				return 1;	}//	* Find Zone *    s1 = strchr(s, ':');    if(s1)    {    	*s1 = 0;    	if(strcmp(s, "ALL") && (*s != '*'))	        dest->ad.Zone = atoi(s);	    else	    	dest->wild.zone = TRUE;        s = s1+1;        ret++;    }    else		dest->ad.Zone = 0;    	if( (strcmp(s, "ALL") == 0) || (*s == '*'))	{		dest->wild.net = TRUE;				dest->wild.node = TRUE;				dest->wild.point = TRUE;				dest->wild.domain = TRUE;				return 1;	}//	* Find Net *    s1 = strchr(s, '/');    if(s1)    {    	*s1 = 0;    	if(strcmp(s, "ALL") && (*s != '*'))	        dest->ad.Net = atoi(s);	    else	    	dest->wild.net = TRUE;        s = s1+1;        ret++;    }    else		dest->ad.Net = 0;	if( (strcmp(s, "ALL") == 0) || (*s == '*'))	{		dest->wild.node = TRUE;				dest->wild.point = TRUE;				dest->wild.domain = TRUE;				return 1;	}//	* Find Node *	if(strncmp(s, "ALL", 3) && (*s != '*'))	{		if(isdigit(*s))		{		    dest->ad.Node = atoi(s);		    ret++;		}//		else//			dest->ad.Node = alias[0].ad.Node;    }    else    {		dest->wild.node = TRUE;		ret++;    }	if( (strcmp(s, "ALL") == 0) || (*s == '*'))	{		dest->wild.point = TRUE;				dest->wild.domain = TRUE;				return 1;	}//	* Find point & domain *    s1 = strchr(s, '.');       s2 = strchr(s, '@');    if(s1 && !(s2 && (s1 > s2)))        //	* check if it's a real point*    {        s = s1+1;		if(strncmp(s, "ALL", 3) && (*s != '*'))	        dest->ad.Point = atoi(s);	    else	    {	    	dest->wild.point = TRUE;	    	if(!s2)	    		dest->wild.domain = TRUE;	    }        ret++;    }    else        dest->ad.Point = 0;   //	if(s2)//	{//		s = s2+1;////		if(strncmp(s, "ALL", 3) && (*s != '*'))//		{//			while(!isspace(*s2))//				s2++;//			*s2 = 0;//			//			dest->ad.Domain = find_domain(s);//		}//		else//			dest->wild.domain = TRUE;//		ret++;//	}//	else		dest->ad.Domain = NULL;//	 *//	 * Make intelligent guess at address zone and domain if missing//	 *//	 * e.g. 1004/0 should expand to 90:1004/0@nest//	 *       25@n ==> 90:1004/25@nest//	 *       25   ==>  2:25/25@fidonet//	 *		if(!(dest->ad.Domain || dest->wild.domain) ||	   !(dest->ad.Zone || dest->wild.zone) ||	   !(dest->ad.Net || dest->wild.net) )	{		short count = num_addrs;		ADDRESS *ad = alias;				while(count--)		{			if( (!dest->ad.Zone || dest->wild.zone || (ad->ad.Zone == dest->ad.Zone)) &&				(!dest->ad.Domain || dest->wild.domain || (ad->ad.Domain == dest->ad.Domain)) &&				(dest->wild.domain ||dest->ad.Domain ||				 dest->wild.zone || dest->ad.Zone ||				 dest->wild.net || !dest->ad.Net || (ad->ad.Net == dest->ad.Net)) )			{				dest->ad.Zone = ad->ad.Zone;				dest->ad.Domain = ad->ad.Domain;				if(!dest->ad.Net)					dest->ad.Net = ad->ad.Net;				break;			}			ad++;		}		if(!dest->ad.Domain)			dest->ad.Domain = alias[0].ad.Domain;		if(!dest->ad.Zone)			dest->ad.Zone = alias[0].ad.Zone;		if(!dest->ad.Net)			dest->ad.Net = alias[0].ad.Net;	}    return ret;}*//* * Parse an address in text form and put it into the address structure */short parse_address (char *node, ADDR *addr){	short ret;   	char d[100];   	ret = find_addr (node, addr, d);//	if (d[0] != '\0')//	{//		addr->Domain = add_domain (d);//	}	return (ret);}short find_address (char *node, ADDR *addr){	short ret;	char d[100];	char *p;	d[0] = '\0';//	p = skip_blanks (node);		for ( p = node; *p && isspace (*p); p++ );   		if (!isdigit (*p) && (*p != '.'))//	{//		fidouser (p, addr);//		if ((addr->Net == -1) || (addr->Node == -1) || (addr->Zone == -1))//		{			ret = 0;//		}//		else//		{//			ret = 1;//		}//	}	else	{		ret = find_addr (p, addr, d);	}//	if (d[0] != '\0')//	{//		addr->Domain = find_domain (d);//	}	/*	 * Make intelligent guess at address zone and domain if missing	 *	 * e.g. 1004/0 should expand to 90:1004/0@nest	 *       25@n ==> 90:1004/25@nest	 *       25   ==>  2:25/25@fidonet	 *//*		if(!addr->Domain || !addr->Zone || !addr->Net)	{		short count = num_addrs;		ADDRESS *ad = alias;				while(count--)		{			if( (!addr->Zone || (ad->ad.Zone == addr->Zone)) &&				(!addr->Domain || (ad->ad.Domain == addr->Domain)) &&				(addr->Domain || addr->Zone || !addr->Net || (ad->ad.Net == addr->Net)) )			{				addr->Zone = ad->ad.Zone;				addr->Domain = ad->ad.Domain;				if(!addr->Net)					addr->Net = ad->ad.Net;				break;			}			ad++;		}		if(!addr->Domain)			addr->Domain = alias[0].ad.Domain;		if(!addr->Zone)			addr->Zone = alias[0].ad.Zone;		if(!addr->Net)			addr->Net = alias[0].ad.Net;	}*/   	return (ret);}Boolean cmp2addrs ( addr *my1, addr *my2 ){	return ( my1->zone == my2->zone &&			 my1->net == my2->net &&			 my1->node == my2->node &&			 my1->point == my2->point );}Boolean cmp2addrs1 ( addr *my1, ADDR *my2 ){	return ( my1->zone == my2->Zone &&			 my1->net == my2->Net &&			 my1->node == my2->Node &&			 my1->point == my2->Point );}Boolean cmp2addrs2 ( ADDR *my1, ADDR *my2 ){	return ( my1->Zone == my2->Zone &&			 my1->Net == my2->Net &&			 my1->Node == my2->Node &&			 my1->Point == my2->Point );}