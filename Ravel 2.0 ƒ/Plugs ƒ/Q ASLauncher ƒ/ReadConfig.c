//	ReadConfig.c#include "ReadConfig.h"#include "ravel_ftn.h"#include "generalparser.h"#include <stdio.h>#include <stdlib.h>#include <string.h>static	token_desc	gTokens[] = {	"Script",		0,	"External",		0,	"Launch",		0,	"Bg",			1,	"Unlock",		2,	"AllowUnconditionalUnlock", 0,	NULL,			0};		lex_data	*gLexData = NULL;static	lex_data	*gLastLexData = NULL;static void clear_lex_data(lex_data *ld){	memset(ld, 0, sizeof(lex_data));}static void add_lex_data(lex_data *ld){	if (gLexData == NULL)	{		gLexData = gLastLexData = calloc(1, sizeof(lex_data));	}	else	{		gLastLexData->next = calloc(1, sizeof(lex_data));		gLastLexData = gLastLexData->next;	}	gLastLexData->next = NULL;	gLastLexData->mode = ld->mode;	strcpy(gLastLexData->menuname, ld->menuname);	strcpy(gLastLexData->exename, ld->exename);	gLastLexData->flags = ld->flags;}short count_lex_data(lex_data *ld){	lex_data	*cld = ld;	short		result = 0;	while (cld)	{		result++;		cld = cld->next;	}		return result;}void free_lex_data(lex_data *ld){	lex_data	*cld = ld, *cld1;	while (cld)	{		cld1 = cld->next;		free(cld);		cld = cld1;	}}lex_data *find_lex_data(lex_data *ld, char *str){	lex_data	*cld = ld;	while (cld)	{		if (strcasecmp(str, cld->cmpname) == 0)			return cld;		cld = cld->next;	}		return NULL;}static int CallbackConfig(long tokenclass, long associated_info, fetched_info *info, void *refcon){	lex_data	*pLexData = (lex_data *)refcon;	switch (tokenclass & kGPBMASK)	{	case kLITERAL:				if (info->literal == NULL || info->literal[0] == 0)			return kERR;				if (pLexData->menuname[0] == 0)			strcpy(pLexData->menuname, info->literal);		else		if (pLexData->exename[0] == 0)			strcpy(pLexData->exename, info->literal);		else			return kERR;				break;	case kCMDTOKEN:				switch (associated_info)		{		case 0:					if (pLexData->mode)				return kERR;						pLexData->mode = tokenclass & 0x00FFFFFF;			break;				case 1:						if (pLexData->mode == 0 ||				pLexData->exename[0] == 0 ||				(pLexData->flags & 4) != 0)				return kERR;						pLexData->flags |= 1 | 4;			break;				case 2:					if (pLexData->mode == 0 ||				pLexData->exename[0] == 0 ||				(pLexData->flags & 8) != 0)				return kERR;						pLexData->flags |= 2 | 8;						break;		}		break;		case kCMDTOKEN | kNOTFOUND:	default:			return kERR;	}		return kOK;}short ReadConfig(StringPtr cfgname){	char		cfgpath[256], buff[512];	FILE		*cfgfile;	short		result = 0;	lex_data	CurLexData;		memcpy(cfgpath, &cfgname[1], cfgname[0]);	cfgpath[cfgname[0]] = 0;		cfgfile = fopen(cfgpath, "r");	if (cfgfile)	{		while (fgets (buff, 510, cfgfile) != NULL && result >= 0)		{			if (!buff[0] || buff[0] == ';')				continue;						clear_lex_data(&CurLexData);			if (parseoneline(buff, gTokens, NULL, &CurLexData, CallbackConfig))				add_lex_data(&CurLexData);			else				result = -1;		}				fclose(cfgfile);	}	else		result = -1;		return result;}