/* mppmcmap.h - header file for colormap routines in python img version** of ppm routines.**** Unfortunately, the routines cannot be shared with libppm (which is probably** also loaded if these routines are used), because** 1. Pixel format is different** 2. Storage of images is different (2-dimensional vs 1-dim array).*/typedef long pixel;typedef unsigned char pixval;#define MAXVAL 255#define MPPM_GETR(x) ((x)&0xff)#define MPPM_GETG(x) (((x)>>8) & 0xff)#define MPPM_GETB(x) (((x)>>16) & 0xff)#define MPPM_ASSIGN(p,red,grn,blu) \    (p) = ((pixel) (red)) | ((pixel) (grn) << 8) | ((pixel) (blu) << 16)#define MPPM_EQUAL(p,q) ((p) == (q))#define MPPM_LUMIN(p) \    (0.299*MPPM_GETR(p) + 0.587*MPPM_GETG(p) + 0.114*MPPM_GETB(p))/* Color histogram stuff. */typedef struct colorhist_item* colorhist_vector;struct colorhist_item    {    pixel color;    int value;    };typedef struct colorhist_list_item* colorhist_list;struct colorhist_list_item    {    struct colorhist_item ch;    colorhist_list next;    };/* External interface (from dither.c and genmap.c): */int mppm_genmap(long *pixels, int cols, int rows,		long *colormap, int colormapsize);int mppm_dither(pixel *pixels, int cols, int rows,		long *colormap, int colormapsize, int floyd,		unsigned char *result);/* Internal interfaces (from mppm3.c) */colorhist_vector mppm_computecolorhist( pixel* pixels, int cols, int rows, int maxcolors, int* colorsP );/* Returns a colorhist *colorsP long (with space allocated for maxcolors. */void mppm_addtocolorhist( colorhist_vector chv, int* colorsP, int maxcolors, pixel* colorP, int value, int position );void mppm_freecolorhist( colorhist_vector chv );/* Color hash table stuff. */typedef colorhist_list* colorhash_table;colorhash_table mppm_computecolorhash( pixel* pixels, int cols, int rows, int maxcolors, int* colorsP );int mppm_lookupcolor( colorhash_table cht, pixel* colorP );colorhist_vector mppm_colorhashtocolorhist( colorhash_table cht, int maxcolors );colorhash_table mppm_colorhisttocolorhash( colorhist_vector chv, int colors );int mppm_addtocolorhash( colorhash_table cht, pixel* colorP, int value );/* Returns -1 on failure. */colorhash_table mppm_alloccolorhash( void );void mppm_freecolorhash( colorhash_table cht );