/***********************************************************Copyright 1991, 1992, 1993, 1994 by Stichting Mathematisch Centrum,Amsterdam, The Netherlands.                        All Rights ReservedPermission to use, copy, modify, and distribute this software and its documentation for any purpose and without fee is hereby granted, provided that the above copyright notice appear in all copies and thatboth that copyright notice and this permission notice appear in supporting documentation, and that the names of Stichting MathematischCentrum or CWI not be used in advertising or publicity pertaining todistribution of the software without specific, written prior permission.STICHTING MATHEMATISCH CENTRUM DISCLAIMS ALL WARRANTIES WITH REGARD TOTHIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY ANDFITNESS, IN NO EVENT SHALL STICHTING MATHEMATISCH CENTRUM BE LIABLEFOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGESWHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN ANACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUTOF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.******************************************************************//*** Currently you cannot do anything interesting with the imgformat** objects (except use them in object-identity comparisons).**** Eventually, you should be able to ask things like type (rgb, cmap),** bits/pixel, pixel alignment, row alignment, direction, etc.***//* Imgformat objects */#include "Python.h"typedef struct {	PyObject_HEAD	char    *name;	PyObject	*descr;} imgformatobject;staticforward PyTypeObject Imgformattype;#define is_imgformatobject(v)		((v)->ob_type == &Imgformattype)char doc_format[] =  "An image-format object completely identifies the way image-data\n"  "is stored in-core. The 'name' attribute has a textual name, the\n"  "'descr' attribute is a dictionary listing various attributes\n";static PyObject *dict;			/* Dictionary of known types */static PyObject *errobject;static imgformatobject *newimgformatobject(char *name, PyObject *descr){	imgformatobject *xp;	xp = PyObject_NEW(imgformatobject, &Imgformattype);	if (xp == NULL)		return NULL;	if( (xp->name = (char *) malloc(strlen(name)+1)) == NULL ) {	    PyMem_DEL(xp);	    return (imgformatobject *)PyErr_NoMemory();	}	strcpy(xp->name, name);	xp->descr = descr;	return xp;}/* Imgformat methods */static voidimgformat_dealloc(imgformatobject *xp){	free(xp->name);	PyMem_DEL(xp);}static PyObject *imgformat_repr(imgformatobject *self){	char buf[100];	sprintf(buf, "<imgformat '%.70s' at %x>", self->name, self);	return PyString_FromString(buf);}static struct PyMethodDef imgformat_methods[] = {	{NULL,		NULL}		/* sentinel */};static PyObject *imgformat_getattr(imgformatobject *self, char *attr){	if ( strcmp(attr, "name") == 0 )	    return PyString_FromString(self->name);	if ( strcmp(attr, "__doc__") == 0 )	    return PyString_FromString(doc_format);	if ( strcmp(attr, "descr") == 0 ) {		Py_INCREF(self->descr);		return self->descr;	}	return Py_FindMethod(imgformat_methods, (PyObject *)self, attr);}static PyTypeObject Imgformattype = {	PyObject_HEAD_INIT(&PyType_Type)	0,			/*ob_size*/	"imgformat",		/*tp_name*/	sizeof(imgformatobject), /*tp_basicsize*/	0,			/*tp_itemsize*/	/* methods */	(destructor)imgformat_dealloc, /*tp_dealloc*/	0,			/*tp_print*/	(getattrfunc)imgformat_getattr,	 /*tp_getattr*/	0,			 /*tp_setattr*/	0,			/*tp_compare*/	(reprfunc)imgformat_repr, /*tp_repr*/	0,			/*tp_as_number*/	0,			/*tp_as_sequence*/	0,			/*tp_as_mapping*/	0,			/*tp_hash*/};static char doc_new[] = "Create a new format object. Arguments are name, description_text and\n" "an optional attribute dictionary\n";static PyObject *imgformat_new(PyObject *self, PyObject *args){	char *name, *descrtext;	PyObject *descrobj;	PyObject *obj;		descrobj = NULL;	if (!PyArg_ParseTuple(args, "ss|O", &name, &descrtext, &descrobj))		return NULL;	if ( !descrobj )		descrobj = Py_None;	Py_INCREF(descrobj);	obj = (PyObject *)newimgformatobject(descrtext, descrobj);	if (obj == NULL)		return NULL;	if (PyDict_SetItemString(dict, name, obj) != 0) {		Py_DECREF(obj);		Py_DECREF(descrobj);		return NULL;	}	return obj;}/* Helper function for other modules, to obtain imgformat-by-name */PyObject *getimgformat(char *name){	return PyDict_GetItemString(dict, name);}/* List of functions defined in the module */static struct PyMethodDef imgformat_module_methods[] = {	{"new",		imgformat_new,	1,	doc_new},	{NULL,		NULL}		/* sentinel */};/* Initialization function for the module (*must* be called initimgformat) */static char doc_imgformat[] = "Container module for known image formats";#ifdef __cplusplusextern "C"#endif#ifdef _WINDOWS__declspec(dllexport)#endifvoidinitimgformat(){	PyObject *m, *x, *o;	/* Create the module and add the functions */	m = Py_InitModule("imgformat", imgformat_module_methods);	dict = PyModule_GetDict(m);	x = PyString_FromString(doc_imgformat);	PyDict_SetItemString(dict, "__doc__", x);	errobject = PyString_FromString("imgformat.error");	PyDict_SetItemString(dict, "error", errobject);	/* 32 bit RGB pixels with R in low-order bits */	o = Py_BuildValue("{s:s,s:i,s:i,s:i,s:((ii)(ii)(ii)(ii))}", "type", "rgb",		    "b2t", 0, "size", 32, "align", 32,		    "comp", 0, 8, 8, 8, 16, 8, 24, 8);	x = (PyObject *)newimgformatobject("SGI 32bit RGB(A)", o);	PyDict_SetItemString(dict, "rgb", x);	o = Py_BuildValue("{s:s,s:i,s:i,s:i,s:((ii)(ii)(ii)(ii))}", "type", "rgb",		    "b2t", 1, "size", 32, "align", 32,		    "comp", 0, 8, 8, 8, 16, 8, 24, 8);	x = (PyObject *)newimgformatobject("SGI 32bit RGB(A) bottom-to-top", o);	PyDict_SetItemString(dict, "rgb_b2t", x);	/* 32 bit RGB pixels with B in low-order bits */	o = Py_BuildValue("{s:s,s:i,s:i,s:i,s:((ii)(ii)(ii))}", "type", "rgb",		    "b2t", 0, "size", 32, "align", 32,		    "comp", 16, 8, 8, 8, 0, 8);	x = (PyObject *)newimgformatobject("Macintosh 32bit RGB", o);	PyDict_SetItemString(dict, "macrgb", x);	/* 15 bit RGB pixels with B in low-order bits */	o = Py_BuildValue("{s:s,s:i,s:i,s:i,s:((ii)(ii)(ii))}", "type", "rgb",		    "b2t", 0, "size", 16, "align", 16,		    "comp", 10, 5, 5, 5, 0, 5);	x = (PyObject *)newimgformatobject("Macintosh 15bit RGB", o);	PyDict_SetItemString(dict, "macrgb16", x);	/* 16 bit RGB pixels with B in low-order bits */	o = Py_BuildValue("{s:s,s:i,s:i,s:i,s:((ii)(ii)(ii))}", "type", "rgb",		    "b2t", 0, "size", 16, "align", 16,		    "comp", 11, 5, 5, 6, 0, 5);	x = (PyObject *)newimgformatobject("XFree 16bit RGB", o);	PyDict_SetItemString(dict, "xfreergb16", x);	/* 16 bit RGB pixels with B in low-order bits */	o = Py_BuildValue("{s:s,s:i,s:i,s:i,s:((ii)(ii)(ii))}", "type", "rgb",		    "b2t", 0, "size", 16, "align", 32,		    "comp", 11, 5, 5, 6, 0, 5);	x = (PyObject *)newimgformatobject("XFree 16bit RGB 32bit align", o);	PyDict_SetItemString(dict, "xfreergb16a32", x);	/* 24 bit RGB pixels with B in low-order bits */	o = Py_BuildValue("{s:s,s:i,s:i,s:i,s:((ii)(ii)(ii))}", "type", "rgb",		    "b2t", 0, "size", 24, "align", 32,		    "comp", 16, 8, 8, 8, 0, 8);	x = (PyObject *)newimgformatobject("BMP 24bit RGB little-endian", o);	PyDict_SetItemString(dict, "bmprgble", x);	/* 24 bit RGB pixels with B in high-order bits */	o = Py_BuildValue("{s:s,s:i,s:i,s:i,s:((ii)(ii)(ii))}", "type", "rgb",		    "b2t", 0, "size", 24, "align", 32,		    "comp", 0, 8, 8, 8, 16, 8);	x = (PyObject *)newimgformatobject("BMP 24bit RGB big-endian", o);	PyDict_SetItemString(dict, "bmprgbbe", x);	/* 24 bit RGB pixels with B in low-order bits, bottom-to-top */	o = Py_BuildValue("{s:s,s:i,s:i,s:i,s:((ii)(ii)(ii))}", "type", "rgb",		    "b2t", 1, "size", 24, "align", 32,		    "comp", 16, 8, 8, 8, 0, 8);	x = (PyObject *)newimgformatobject("BMP 24bit RGB bottom-to-top little-endian", o);	PyDict_SetItemString(dict, "bmprgble_b2t", x);	/* 24 bit RGB pixels with B in high-order bits, bottom-to-top */	o = Py_BuildValue("{s:s,s:i,s:i,s:i,s:((ii)(ii)(ii))}", "type", "rgb",		    "b2t", 1, "size", 24, "align", 32,		    "comp", 0, 8, 8, 8, 16, 8);	x = (PyObject *)newimgformatobject("BMP 24bit RGB bottom-to-top big-endian", o);	PyDict_SetItemString(dict, "bmprgbbe_b2t", x);	/* 24 bit RGB pixels with B in low-order bits */	o = Py_BuildValue("{s:s,s:i,s:i,s:i,s:((ii)(ii)(ii))}", "type", "rgb",		    "b2t", 0, "size", 24, "align", 24,		    "comp", 16, 8, 8, 8, 0, 8);	x = (PyObject *)newimgformatobject("BMP 24bit RGB little-endian unaligned", o);	PyDict_SetItemString(dict, "bmprgble_noalign", x);	/* 24 bit RGB pixels with B in high-order bits */	o = Py_BuildValue("{s:s,s:i,s:i,s:i,s:((ii)(ii)(ii))}", "type", "rgb",		    "b2t", 0, "size", 24, "align", 24,		    "comp", 0, 8, 8, 8, 16, 8);	x = (PyObject *)newimgformatobject("BMP 24bit RGB big-endian unaligned", o);	PyDict_SetItemString(dict, "bmprgbbe_noalign", x);	/* 24 bit RGB pixels with B in low-order bits, bottom-to-top */	o = Py_BuildValue("{s:s,s:i,s:i,s:i,s:((ii)(ii)(ii))}", "type", "rgb",		    "b2t", 1, "size", 24, "align", 24,		    "comp", 16, 8, 8, 8, 0, 8);	x = (PyObject *)newimgformatobject("BMP 24bit RGB bottom-to-top little-endian unaligned", o);	PyDict_SetItemString(dict, "bmprgble_noalign_b2t", x);	/* 24 bit RGB pixels with B in high-order bits, bottom-to-top */	o = Py_BuildValue("{s:s,s:i,s:i,s:i,s:((ii)(ii)(ii))}", "type", "rgb",		    "b2t", 1, "size", 24, "align", 24,		    "comp", 0, 8, 8, 8, 16, 8);	x = (PyObject *)newimgformatobject("BMP 24bit RGB bottom-to-top big-endian unaligned", o);	PyDict_SetItemString(dict, "bmprgbbe_noalign_b2t", x);	/* 8 bit RRRBBGGG pixels, with 32bit aligned rows */	o = Py_BuildValue("{s:s,s:i,s:i,s:i,s:((ii)(ii)(ii))}", "type", "rgb",		    "b2t", 0, "size", 8, "align", 32,		    "comp", 5, 3, 0, 3, 3, 2);	x = (PyObject *)newimgformatobject("SGI 3:3:2 RGB", o);	PyDict_SetItemString(dict, "rgb8", x);	o = Py_BuildValue("{s:s,s:i,s:i,s:i,s:((ii)(ii)(ii))}", "type", "rgb",		    "b2t", 1, "size", 8, "align", 32,		    "comp", 5, 3, 0, 3, 3, 2);	x = (PyObject *)newimgformatobject("SGI 3:3:2 RGB bottom-to-top", o);	PyDict_SetItemString(dict, "rgb8_b2t", x);	/* 8 bit greyscale pixels with 32bit aligned rows */	o = Py_BuildValue("{s:s,s:i,s:i,s:i,s:((ii))}", "type", "grey",		    "b2t", 0, "size", 8, "align", 32,		    "comp", 0, 8);	x = (PyObject *)newimgformatobject("SGI 8bit grey", o);	PyDict_SetItemString(dict, "grey", x);	o = Py_BuildValue("{s:s,s:i,s:i,s:i,s:((ii))}", "type", "grey",		    "b2t", 1, "size", 8, "align", 32,		    "comp", 0, 8);	x = (PyObject *)newimgformatobject("SGI 8bit grey bottom-to-top", o);	PyDict_SetItemString(dict, "grey_b2t", x);	/* 8bit colormap pixels with 32bit aligned rows */	o = Py_BuildValue("{s:s,s:i,s:i,s:i,s:((ii))}", "type", "mapped",		    "b2t", 0, "size", 8, "align", 32,		    "comp", 0, 8);	x = (PyObject *)newimgformatobject("SGI 8bit colormap", o);	PyDict_SetItemString(dict, "colormap", x);	o = Py_BuildValue("{s:s,s:i,s:i,s:i,s:((ii))}", "type", "mapped",		    "b2t", 1, "size", 8, "align", 32,		    "comp", 0, 8);	x = (PyObject *)newimgformatobject("SGI 8bit colormap bottom-to-top", o);	PyDict_SetItemString(dict, "colormap_b2t", x);	/* 8 bit RRRBBGGG pixels, without alignment */	o = Py_BuildValue("{s:s,s:i,s:i,s:i,s:((ii)(ii)(ii))}", "type", "rgb",		    "b2t", 0, "size", 8, "align", 8,		    "comp", 5, 3, 0, 3, 3, 2);	x = (PyObject *)newimgformatobject("X 3:3:2 RGB", o);	PyDict_SetItemString(dict, "xrgb8", x);	o = Py_BuildValue("{s:s,s:i,s:i,s:i,s:((ii)(ii)(ii))}", "type", "rgb",		    "b2t", 1, "size", 8, "align", 8,		    "comp", 5, 3, 0, 3, 3, 2);	x = (PyObject *)newimgformatobject("X 3:3:2 RGB bottom-to-top", o);	PyDict_SetItemString(dict, "xrgb8_b2t", x);	/* 8 bit greyscale pixels without alignment */	o = Py_BuildValue("{s:s,s:i,s:i,s:i,s:((ii))}", "type", "grey",		    "b2t", 0, "size", 8, "align", 8,		    "comp", 0, 8);	x = (PyObject *)newimgformatobject("X 8bit grey", o);	PyDict_SetItemString(dict, "xgrey", x);	/* 8 bit greyscale pixels without alignment */	o = Py_BuildValue("{s:s,s:i,s:i,s:i,s:((ii))}", "type", "grey",		    "b2t", 1, "size", 8, "align", 8,		    "comp", 0, 8);	x = (PyObject *)newimgformatobject("X 8bit grey bottom-to-top", o);	PyDict_SetItemString(dict, "xgrey_b2t", x);	/* 8bit colormap pixels without alignment */	o = Py_BuildValue("{s:s,s:i,s:i,s:i,s:((ii))}", "type", "mapped",		    "b2t", 0, "size", 8, "align", 8,		    "comp", 0, 8);	x = (PyObject *)newimgformatobject("X 8bit colormap", o);	PyDict_SetItemString(dict, "xcolormap", x);	/* bitmap stored as a pixel per byte in low-order bit */	o = Py_BuildValue("{s:s,s:i,s:i,s:i,s:((ii))}", "type", "grey",		    "b2t", 0, "size", 8, "align", 8,		    "comp", 0, 1);	x = (PyObject *)newimgformatobject("pbm-style bitmap", o);	PyDict_SetItemString(dict, "pbmbitmap", x);		/* X packed bitmap */	o = Py_BuildValue("{s:s,s:i,s:i,s:i,s:i,s:i}", "type", "packed",			"b2t", 0, "size", 1, "align", 8, "shift", 0, "step", 1);	x = (PyObject *)newimgformatobject("xbm bitmap", o);	PyDict_SetItemString(dict, "xbmpacked", x);	/* BMP packed bitmap, bottom-to-top */	o = Py_BuildValue("{s:s,s:i,s:i,s:i,s:i,s:i}", "type", "packed",			"b2t", 1, "size", 1, "align", 32, "shift", 7, "step", -1);	x = (PyObject *)newimgformatobject("bmp bitmap, bottom-to-top", o);	PyDict_SetItemString(dict, "bmppacked_b2t", x);	/* BMP packed bitmap */	o = Py_BuildValue("{s:s,s:i,s:i,s:i,s:i,s:i}", "type", "packed",			"b2t", 0, "size", 1, "align", 32, "shift", 7, "step", -1);	x = (PyObject *)newimgformatobject("bmp bitmap, bottom-to-top", o);	PyDict_SetItemString(dict, "bmppacked", x);	/* BMP 4-bit packed pixelmap, bottom-to-top */	o = Py_BuildValue("{s:s,s:i,s:i,s:i,s:i,s:i}", "type", "packed",			"b2t", 1, "size", 4, "align", 32, "shift", 4, "step", -4);	x = (PyObject *)newimgformatobject("bmp 4bit pixmap, bottom-to-top", o);	PyDict_SetItemString(dict, "bmppacked4_b2t", x);	/* BMP 4-bit packed pixelmap */	o = Py_BuildValue("{s:s,s:i,s:i,s:i,s:i,s:i}", "type", "packed",			"b2t", 0, "size", 4, "align", 32, "shift", 4, "step", -4);	x = (PyObject *)newimgformatobject("bmp 4bit pixmap", o);	PyDict_SetItemString(dict, "bmppacked4", x);	/* Check for errors */	if (PyErr_Occurred())		Py_FatalError("can't initialize module imgformat");}