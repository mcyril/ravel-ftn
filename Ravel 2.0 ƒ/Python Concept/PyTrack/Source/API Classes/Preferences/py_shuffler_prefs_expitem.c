//	�	py_shuffler_prefs_expitem.c#include "py_shuffler_prefs_expitem.h"static voidprefexpitem_dealloc(PyExpItemObject *v){	_Py_Dealloc(v->address);	PyObject_Del(v);}static intprefexpitem_init(PyExpItemObject *v, PyObject *args, PyObject *kwds){	v->address = NULL;	v->diode = 0;		return 0;}static PyObject *prefexpitem_getattr(PyExpItemObject *v, char *name){	if (strcmp(name, "address") == 0)	{		Py_XINCREF(v->address);		return v->address;	}	else if (strcmp(name, "diode") == 0)		return PyInt_FromLong(v->diode);	return NULL;}static intprefexpitem_setattr(PyExpItemObject *v, char *name, PyObject *content){	int res = -1;	return res;}static PyExpItemObject *prefexpitem_new_ex(void){	PyExpItemObject *res = PyObject_New(PyExpItemObject, &PyShufflerExpItem_Type);	if (res != NULL)		prefexpitem_init(res, NULL, NULL);	return res;}PyTypeObject PyShufflerExpItem_Type = {	PyObject_HEAD_INIT(&PyType_Type)	0,	"expitem",	sizeof(PyExpItemObject),	0,	(destructor)prefexpitem_dealloc,						/* tp_dealloc */	0,					/* tp_print */	(getattrfunc)prefexpitem_getattr,						/* tp_getattr */	0 /*(setattrfunc)prefexpitem_setattr*/,						/* tp_setattr */	0,					/* tp_compare */	0,					/* tp_repr */	0,					/* tp_as_number */	0,					/* tp_as_sequence */	0,					/* tp_as_mapping */	0,					/* tp_hash */	0,					/* tp_call */	0,					/* tp_str */	0,					/* tp_getattro */	0,					/* tp_setattro */	0,					/* tp_as_buffer */	Py_TPFLAGS_DEFAULT,	/* tp_flags */	0,					/* tp_doc */	0,					/* tp_traverse */	0,					/* tp_clear */	0,					/* tp_richcompare */	0,					/* tp_weaklistoffset */	0,					/* tp_iter */	0,					/* tp_iternext */	0,					/* tp_methods */	0,					/* tp_members */	0,					/* tp_getset */	0,					/* tp_base */	0,					/* tp_dict */	0,					/* tp_descr_get */	0,					/* tp_descr_set */	0,					/* tp_dictoffset */	0,					/* tp_init */	0,					/* tp_alloc */	0,					/* tp_new */};PyObject *PyExpItem_New(addr *address, short diode){	PyExpItemObject *res = prefexpitem_new_ex();	if(res)	{		res->address = PyFtnAddr_NewAddr(address);		res->diode = diode;	}	return (PyObject *)res;}