/*** mppm3.c - Handle color histograms and hash tables.**** Modified from: libppm3.c - ppm utility library part 3**** Colormap routines.**** Copyright (C) 1989, 1991 by Jef Poskanzer.**** Permission to use, copy, modify, and distribute this software and its** documentation for any purpose and without fee is hereby granted, provided** that the above copyright notice appear in all copies and that both that** copyright notice and this permission notice appear in supporting** documentation.  This software is provided "as is" without express or** implied warranty.*/#include "Python.h"#include "mppmcmap.h"#define HASH_SIZE 20023#define mppm_hashpixel(p) ( ( (int) (p) & 0xffffff ) % HASH_SIZE )colorhist_vectormppm_computecolorhist(pixel* pixels, int cols, int rows, int maxcolors, int* colorsP)    {    colorhash_table cht;    colorhist_vector chv;    cht = mppm_computecolorhash( pixels, cols, rows, maxcolors, colorsP );    if ( cht == (colorhash_table) 0 )	return (colorhist_vector) 0;    chv = mppm_colorhashtocolorhist( cht, maxcolors );    mppm_freecolorhash( cht );    return chv;    }voidmppm_addtocolorhist(colorhist_vector chv, int *colorsP, int maxcolors, pixel *colorP, int value, int position)    {    int i, j;    /* Search colorhist for the color. */    for ( i = 0; i < *colorsP; ++i )	if ( MPPM_EQUAL( chv[i].color, *colorP ) )	    {	    /* Found it - move to new slot. */	    if ( position > i )		{		for ( j = i; j < position; ++j )		    chv[j] = chv[j + 1];		}	    else if ( position < i )		{		for ( j = i; j > position; --j )		    chv[j] = chv[j - 1];		}	    chv[position].color = *colorP;	    chv[position].value = value;	    return;	    }    if ( *colorsP < maxcolors )	{	/* Didn't find it, but there's room to add it; so do so. */	for ( i = *colorsP; i > position; --i )	    chv[i] = chv[i - 1];	chv[position].color = *colorP;	chv[position].value = value;	++(*colorsP);	}    }colorhash_tablemppm_computecolorhash(pixel *pixels, int cols, int rows, int maxcolors, int *colorsP)    {    colorhash_table cht;    register pixel* pP;    colorhist_list chl;    int col, hash;    cht = mppm_alloccolorhash( );    *colorsP = 0;    /* Go through the entire image, building a hash table of colors. */    for ( col = 0, pP = pixels; col < cols*rows; ++col, ++pP )    {	hash = mppm_hashpixel( *pP );	for ( chl = cht[hash]; chl != (colorhist_list) 0; chl = chl->next )	    if ( MPPM_EQUAL( chl->ch.color, *pP ) )		break;	if ( chl != (colorhist_list) 0 )	    ++(chl->ch.value);	else	{	    if ( ++(*colorsP) > maxcolors )	    {		mppm_freecolorhash( cht );		return (colorhash_table) 0;	    }	    chl = (colorhist_list) malloc( sizeof(struct colorhist_list_item) );	    if ( chl == 0 )		pm_error( "out of memory computing hash table" );	    chl->ch.color = *pP;	    chl->ch.value = 1;	    chl->next = cht[hash];	    cht[hash] = chl;	}    }        return cht;    }colorhash_tablemppm_alloccolorhash( )    {    colorhash_table cht;    int i;    cht = (colorhash_table) malloc( HASH_SIZE * sizeof(colorhist_list) );    if ( cht == 0 )	pm_error( "out of memory allocating hash table" );    for ( i = 0; i < HASH_SIZE; ++i )	cht[i] = (colorhist_list) 0;    return cht;    }intmppm_addtocolorhash(colorhash_table cht, pixel *colorP, int value)    {    register int hash;    register colorhist_list chl;    chl = (colorhist_list) malloc( sizeof(struct colorhist_list_item) );    if ( chl == 0 )	return -1;    hash = mppm_hashpixel( *colorP );    chl->ch.color = *colorP;    chl->ch.value = value;    chl->next = cht[hash];    cht[hash] = chl;    return 0;    }colorhist_vectormppm_colorhashtocolorhist(colorhash_table cht, int maxcolors)    {    colorhist_vector chv;    colorhist_list chl;    int i, j;    /* Now collate the hash table into a simple colorhist array. */    chv = (colorhist_vector) malloc( maxcolors * sizeof(struct colorhist_item) );    /* (Leave room for expansion by caller.) */    if ( chv == (colorhist_vector) 0 )	pm_error( "out of memory generating histogram" );    /* Loop through the hash table. */    j = 0;    for ( i = 0; i < HASH_SIZE; ++i )	for ( chl = cht[i]; chl != (colorhist_list) 0; chl = chl->next )	    {	    /* Add the new entry. */	    chv[j] = chl->ch;	    ++j;	    }    /* All done. */    return chv;    }colorhash_tablemppm_colorhisttocolorhash(colorhist_vector chv, int colors)    {    colorhash_table cht;    int i, hash;    pixel color;    colorhist_list chl;    cht = mppm_alloccolorhash( );    for ( i = 0; i < colors; ++i )	{	color = chv[i].color;	hash = mppm_hashpixel( color );	for ( chl = cht[hash]; chl != (colorhist_list) 0; chl = chl->next )	    if ( MPPM_EQUAL( chl->ch.color, color ) )		pm_error(		    "same color found twice - %d %d %d", MPPM_GETR(color),		    MPPM_GETG(color), MPPM_GETB(color) );	chl = (colorhist_list) malloc( sizeof(struct colorhist_list_item) );	if ( chl == (colorhist_list) 0 )	    pm_error( "out of memory" );	chl->ch.color = color;	chl->ch.value = i;	chl->next = cht[hash];	cht[hash] = chl;	}    return cht;    }intmppm_lookupcolor(colorhash_table cht, pixel* colorP)    {    int hash;    colorhist_list chl;    hash = mppm_hashpixel( *colorP );    for ( chl = cht[hash]; chl != (colorhist_list) 0; chl = chl->next )	if ( MPPM_EQUAL( chl->ch.color, *colorP ) )	    return chl->ch.value;    return -1;    }voidmppm_freecolorhist(colorhist_vector chv)    {    free( (char*) chv );    }voidmppm_freecolorhash(colorhash_table cht)    {    int i;    colorhist_list chl, chlnext;    for ( i = 0; i < HASH_SIZE; ++i )	for ( chl = cht[i]; chl != (colorhist_list) 0; chl = chlnext )	    {	    chlnext = chl->next;	    free( (char*) chl );	    }    free( (char*) cht );    }