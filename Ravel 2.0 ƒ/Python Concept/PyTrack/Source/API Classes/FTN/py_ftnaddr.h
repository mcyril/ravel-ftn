//	�	py_ftnaddr.h#ifndef	_FTNADDR_H#define	_FTNADDR_H#include "PyPlug.h"#if PYTRACK_STANDALONE#include "stringutl.h"#endif#ifdef __cplusplusextern "C" {#endiftypedef struct{	PyObject_HEAD		daddr	address;} PyFtnAddrObject;extern	DL_IMPORT(PyTypeObject)	PyFtnAddr_Type;extern	DL_EXPORT(PyObject *)	initftnaddr(void);PyObject *PyFtnAddr_New(PyObject *args);PyObject *PyFtnAddr_NewStr(char *str);PyObject *PyFtnAddr_NewAddr(addr *address);#ifdef __cplusplus}#endif#endif