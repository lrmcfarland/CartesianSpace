// ==========================================================
// Filename:    space.cpp
//
// Description: Contains the python wrappers for the Cartesian::space
//              objects.
//
//              Hand written in C/C++ with a lot of repition, but
//              this is a proof of concept demonstration.
//
//              Consider boost.python or SWIG for production.
//
//              This demonstrates a C++ way around the python wrapped
//              in C using staticforward. new_SpaceType(Space** a_space)
//              wraps PyObject_New(Space, &SpaceType) so as_number
//              operators defined in SpaceType can hold a reference for
//              how to construct a new SpaceType before the definition
//              SpaceType is complete. Similarlly for is_SpaceType().
//
//
// See also:    http://docs.python.org/extending/newtypes.html
//              http://docs.python.org/c-api/complex.html
//              https://docs.python.org/2/reference/datamodel.html
//
// Author:      L.R. McFarland
// Created:     2011aug14
// ==========================================================

#include <Python.h> // must be first
#include <structmember.h> // part of python

#include <sstream>

#include <space.h>


// ===================
// ===== statics =====
// ===================

static PyObject* sSpaceException; // exception holder

// char* kwlist[] init strings
static char sXstr[] = "x";
static char sYstr[] = "y";
static char sZstr[] = "z";

// TODO: make precision configuralble on build, not hardcoded.
static const unsigned int sPrintPrecision(12); // matches defaut %s precision for unit test


// ========================
// ===== constructors =====
// ========================

// Space object definition.
typedef struct {
  PyObject_HEAD
  Cartesian::space m_space;
} Space;

// Forward declarations for as_number methods. Wraps SpaceType definition.
static void new_SpaceType(Space** a_space);
static int is_SpaceType(PyObject* a_space);

static PyObject* Space_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
  Space* self(NULL);
  self = (Space*)type->tp_alloc(type, 0);
  return (PyObject*)self;
}

static int Space_init(Space* self, PyObject* args, PyObject* kwds) {

  double x(0);
  double y(0);
  double z(0);

  static char* kwlist[] = {sXstr, sYstr, sZstr, NULL};

  if (! PyArg_ParseTupleAndKeywords(args, kwds, "|ddd", kwlist, &x, &y, &z))
    return -1;

  self->m_space.x(x);
  self->m_space.y(y);
  self->m_space.z(z);

  return 0;
}

static void Space_dealloc(Space* self) {
  self->ob_type->tp_free((PyObject*)self);
}

// =================
// ===== print =====
// =================

PyObject* Space_str(PyObject* self) {
  std::stringstream result;
  result.precision(sPrintPrecision);
  result << ((Space*)self)->m_space;
  return PyString_FromString(result.str().c_str());
}

PyObject* Space_repr(PyObject* self) {
  const Cartesian::space& a_space(((Space*)self)->m_space);
  std::stringstream result;
  result.precision(sPrintPrecision);
  result << "("
         << a_space.x() << ", "
         << a_space.y() << ", "
         << a_space.z() << ")";
  return PyString_FromString(result.str().c_str());
}

// ===============================
// ===== getters and setters =====
// ===============================

// -------------
// ----- X -----
// -------------

static PyObject* Space_getx(Space* self, void* closure) {
  return PyFloat_FromDouble(self->m_space.x());
}

static int Space_setx(Space* self, PyObject* value, void* closure) {

  if (value == NULL) {
    PyErr_SetString(sSpaceException, "Cannot delete x");
    return 0;
  }

  if (!PyFloat_Check(value) && !PyInt_Check(value)) {
    PyErr_SetString(sSpaceException, "x must be a float");
    return 0;
  }

  self->m_space.x(PyFloat_AsDouble(value));

  return 0;
}

// -------------
// ----- Y -----
// -------------

static PyObject* Space_gety(Space* self, void* closure) {
  return PyFloat_FromDouble(self->m_space.y());
}

static int Space_sety(Space* self, PyObject* value, void* closure) {

  if (value == NULL) {
    PyErr_SetString(sSpaceException, "Cannot delete y");
    return 0;
  }

  if (!PyFloat_Check(value) && !PyInt_Check(value)) {
    PyErr_SetString(sSpaceException, "y must be a float");
    return 0;
  }

  self->m_space.y(PyFloat_AsDouble(value));

  return 0;
}

// -------------
// ----- Z -----
// -------------

static PyObject* Space_getz(Space* self, void* closure) {
  return PyFloat_FromDouble(self->m_space.z());
}

static int Space_setz(Space* self, PyObject* value, void* closure) {

  if (value == NULL) {
    PyErr_SetString(sSpaceException, "Cannot delete z");
    return 0;
  }

  if (!PyFloat_Check(value) && !PyInt_Check(value)) {
    PyErr_SetString(sSpaceException, "z must be a float");
    return 0;
  }

  self->m_space.z(PyFloat_AsDouble(value));

  return 0;
}

// ==========================
// ===== number methods =====
// ==========================


static PyObject* nb_add(PyObject* o1, PyObject* o2) {

  if (!is_SpaceType(o1) || !is_SpaceType(o2)) {
    Py_INCREF(Py_NotImplemented);
    return Py_NotImplemented;
  }

  Space* result_space(NULL);

  new_SpaceType(&result_space);

  if (result_space == NULL) {
    PyErr_SetString(sSpaceException, "add failed to create space");
    return NULL;
  }

  Cartesian::space the_sum(((Space*)o1)->m_space + ((Space*)o2)->m_space);

  // copy because m_space constructor has already run.
  result_space->m_space = the_sum;

  return (PyObject*) result_space;

}


static PyObject* nb_subtract(PyObject* o1, PyObject* o2) {

  if (!is_SpaceType(o1) || !is_SpaceType(o2)) {
    Py_INCREF(Py_NotImplemented);
    return Py_NotImplemented;
  }

  Space* result_space(NULL);

  new_SpaceType(&result_space);

  if (result_space == NULL) {
    PyErr_SetString(sSpaceException, "subtract failed to create space");
    return NULL;
  }

  Cartesian::space the_difference(((Space*)o1)->m_space - ((Space*)o2)->m_space);

  // copy because m_space constructor has already run.
  result_space->m_space = the_difference;

  return (PyObject*) result_space;

}


static PyObject* nb_negative(PyObject* o1) {
  // Unitary minus

  if (!is_SpaceType(o1)) {
    Py_INCREF(Py_NotImplemented);
    return Py_NotImplemented;
  }

  Space* result_space(NULL);

  new_SpaceType(&result_space);

  if (result_space == NULL) {
    PyErr_SetString(sSpaceException, "negative failed to create space");
    return NULL;
  }

  Cartesian::space the_inverse = -((Space*)o1)->m_space;

  // copy because m_space constructor has already run.
  result_space->m_space = the_inverse;

  return (PyObject*) result_space;
}


static PyObject* nb_multiply(PyObject* o1, PyObject* o2) {
  // This returns the dot product of the space vectors as a double.
  // This will not act as scale since it returns a double not a Space
  // object.

  if (!is_SpaceType(o1) || !is_SpaceType(o2)) {
    Py_INCREF(Py_NotImplemented);
    return Py_NotImplemented;
  }
  double a_dot_product(((Space*)o1)->m_space * ((Space*)o2)->m_space);
  return Py_BuildValue("d", a_dot_product);
}


static PyObject* nb_divide(PyObject* o1, PyObject* o2) {
  // This returns a Space object scaled by the divisor.  o1 must be
  // SpaceType, o2 a float or int otherwise this will raise a
  // NotImplemented error.

  Space* result_space(NULL);
  new_SpaceType(&result_space);

  if (result_space == NULL) {
    PyErr_SetString(sSpaceException, "divide failed to create space");
    return NULL;
  }

  if (is_SpaceType(o1) && (PyFloat_Check(o2) || PyInt_Check(o2))) {

    try {
      result_space->m_space = ((Space*)o1)->m_space / PyFloat_AsDouble(o2);
    } catch (Cartesian::DivideZeroError& err) {
      Py_DECREF(result_space);
      PyErr_SetString(sSpaceException, "divide attempted divide by zero");
      return NULL;
    }

  } else {
    Py_DECREF(result_space);
    Py_INCREF(Py_NotImplemented);
    return Py_NotImplemented;
  }

  return (PyObject*) result_space;
}


static PyObject* tp_richcompare(PyObject* o1, PyObject* o2, int op) {

  if (!is_SpaceType(o1) || !is_SpaceType(o2)) {
    Py_INCREF(Py_NotImplemented);
    return Py_NotImplemented;
  }

  if (op == Py_EQ) {

    if (((Space*)o1)->m_space == ((Space*)o2)->m_space)
      return Py_True;
    else
      return Py_False;

  } else if (op == Py_NE) {

    if (((Space*)o1)->m_space != ((Space*)o2)->m_space)
      return Py_True;
    else
      return Py_False;

  } else {

    PyErr_SetString(PyExc_TypeError, "richcompare op not supported");
    return NULL;

  }

}

// ---------------------------
// ----- inplace methods -----
// ---------------------------

static PyObject* nb_inplace_add(PyObject* o1, PyObject* o2) {
  // TODO can this be implement directly using space::operator+=()?
  // problem with refence going out of scope, segfault.
  return nb_add(o1, o2);
}

static PyObject* nb_inplace_subtract(PyObject* o1, PyObject* o2) {
  // TOOD implement directly?
  return nb_subtract(o1, o2);
}

static PyObject* nb_inplace_multiply(PyObject* o1, PyObject* o2) {
  // TOOD implement directly?
  return nb_multiply(o1, o2);
}

static PyObject* nb_inplace_divide(PyObject* o1, PyObject* o2) {
  // TOOD implement directly?
  return nb_divide(o1, o2);
}

// ==========================
// ===== Python structs =====
// ==========================


static PyMethodDef Space_methods[] = {
    {NULL}  /* Sentinel */
};


static PyMemberDef Space_members[] = {
    {NULL}  /* Sentinel */
};


static PyGetSetDef Space_getseters[] = {
    {sXstr, (getter)Space_getx, (setter)Space_setx, sXstr, NULL},
    {sYstr, (getter)Space_gety, (setter)Space_sety, sYstr, NULL},
    {sZstr, (getter)Space_getz, (setter)Space_setz, sZstr, NULL},
    {NULL}  /* Sentinel */
};

// see http://docs.python.org/c-api/typeobj.html
static PyNumberMethods space_as_number = {
  (binaryfunc) nb_add,
  (binaryfunc) nb_subtract,
  (binaryfunc) nb_multiply,
  (binaryfunc) nb_divide,
  (binaryfunc) 0,  // nb_remainder
  (binaryfunc) 0,  // nb_divmod
  (ternaryfunc) 0, // nb_power
  (unaryfunc) nb_negative,
  (unaryfunc) 0,   // nb_positive
  (unaryfunc) 0,   // nb_absolute
  (inquiry) 0,     // nb_nonzero. Used by PyObject_IsTrue.
  (unaryfunc) 0,   // nb_invert
  (binaryfunc) 0,  // nb_lshift
  (binaryfunc) 0,  // nb_rshift
  (binaryfunc) 0,  // nb_and
  (binaryfunc) 0,  // nb_xor
  (binaryfunc) 0,  // nb_or
  (coercion) 0,    // Used by the coerce() function
  (unaryfunc) 0,   // nb_int
  (unaryfunc) 0,   // nb_long
  (unaryfunc) 0,   // nb_float
  (unaryfunc) 0,   // nb_oct
  (unaryfunc) 0,   // nb_hex

  // added in release 2.0

  (binaryfunc) nb_inplace_add,
  (binaryfunc) nb_inplace_subtract,
  (binaryfunc) nb_inplace_multiply,
  (binaryfunc) nb_inplace_divide,
  (binaryfunc) 0,  // nb_inplace_remainder
  (ternaryfunc) 0, // nb_inplace_power
  (binaryfunc) 0,  // nb_inplace_lshift
  (binaryfunc) 0,  // nb_inplace_rshift
  (binaryfunc) 0,  // nb_inplace_and
  (binaryfunc) 0,  // nb_inplace_xor
  (binaryfunc) 0,  // nb_inplace_or

  // added in release 2.2
  (binaryfunc) 0,  // nb_floor_divide
  (binaryfunc) 0,  // nb_true_divide
  (binaryfunc) 0,  // nb_inplace_floor_divide
  (binaryfunc) 0,  // nb_inplace_true_divide

};


PyTypeObject SpaceType = {
  PyObject_HEAD_INIT(NULL)
  0,                                        /* ob_size */
  "space",                                  /* tp_name */
  sizeof(Space),                            /* tp_basicsize */
  0,                                        /* tp_itemsize */
  (destructor) Space_dealloc,               /* tp_dealloc */
  0,                                        /* tp_print */
  0,                                        /* tp_getattr */
  0,                                        /* tp_setattr */
  0,                                        /* tp_compare */
  Space_repr,                               /* tp_repr */
  &space_as_number,                         /* tp_as_number */
  0,                                        /* tp_as_sequence */
  0,                                        /* tp_as_mapping */
  0,                                        /* tp_hash */
  0,                                        /* tp_call */
  Space_str,                                /* tp_str */
  0,                                        /* tp_getattro */
  0,                                        /* tp_setattro */
  0,                                        /* tp_as_buffer */
  Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_CHECKTYPES, /* tp_flags */
  "Space objects",                          /* tp_doc */
  0,                                        /* tp_traverse */
  0,                                        /* tp_clear */
  tp_richcompare,                           /* tp_richcompare */
  0,                                        /* tp_weaklistoffset */
  0,                                        /* tp_iter */
  0,                                        /* tp_iternext */
  Space_methods,                            /* tp_methods */
  Space_members,                            /* tp_members */
  Space_getseters,                          /* tp_getset */
  0,                                        /* tp_base */
  0,                                        /* tp_dict */
  0,                                        /* tp_descr_get */
  0,                                        /* tp_descr_set */
  0,                                        /* tp_dictoffset */
  (initproc)Space_init,                     /* tp_init */
  0,                                        /* tp_alloc */
  Space_new,                                /* tp_new */
};


// Create new objects with PyObject_New() for binary operators that
// return a new instance of Space, like add.
static void new_SpaceType(Space** a_space) {
  *a_space = PyObject_New(Space, &SpaceType); // alloc and inits?
}

static int is_SpaceType(PyObject* a_space) {
  //wrapper for type check
  return PyObject_TypeCheck(a_space, &SpaceType);
}

// ==========================
// ===== module methods =====
// ==========================

// -------------------------
// ----- cross product -----
// -------------------------

PyDoc_STRVAR(space_cross__doc__, "Returns the cross product of two space objects");

static PyObject* cross(PyObject* self, PyObject *args) {

  Space* first_space(NULL);
  Space* second_space(NULL);
  Space* result_space(NULL);

  // O is borrowed reference
  if (!PyArg_ParseTuple(args, "OO", &first_space, &second_space))
    return NULL;

  result_space = PyObject_New(Space, &SpaceType); // alloc and inits

  if (result_space == NULL) {
    PyErr_SetString(sSpaceException, "cross failed to create space.");
    return NULL;
  }

  Cartesian::space a_cross(Cartesian::cross(first_space->m_space,
					    second_space->m_space));

  result_space->m_space = a_cross;

  return (PyObject*) result_space;

}

// -----------------------
// ----- dot product -----
// -----------------------

PyDoc_STRVAR(space_dot__doc__, "Returns the dot product of two space objects");

static PyObject* dot(PyObject* self, PyObject *args) {

  Space* first_space(NULL);
  Space* second_space(NULL);

  // O is borrowed reference
  if (!PyArg_ParseTuple(args, "OO", &first_space, &second_space))
    return NULL;


  double a_dot_product(Cartesian::dot(first_space->m_space,
		                      second_space->m_space));

  return (PyObject*) Py_BuildValue("d", a_dot_product);

}

// ---------------------
// ----- magnitude -----
// ---------------------

PyDoc_STRVAR(space_magnitude__doc__, "Returns the magnitude of the space object");

static PyObject* magnitude(PyObject* self, PyObject *args) {

  Space* a_space(NULL);

  // O is borrowed reference
  if (!PyArg_ParseTuple(args, "O", &a_space))
    return NULL;

  double a_magnitude(a_space->m_space.magnitude());

  return (PyObject*)  Py_BuildValue("d", a_magnitude);

}

// ----------------------
// ----- normalized -----
// ----------------------

PyDoc_STRVAR(space_normalized__doc__, "Returns the normalized version of the space object");

static PyObject* normalized(PyObject* self, PyObject *args) {

  Space* a_space(NULL);
  Space* result_space(NULL);

  // O is borrowed reference
  if (!PyArg_ParseTuple(args, "O", &a_space))
    return NULL;

  result_space = PyObject_New(Space, &SpaceType); // alloc and inits

  if (result_space == NULL) {
    PyErr_SetString(sSpaceException, "normalized failed to create space.");
    return NULL;
  }

  Cartesian::space a_normalized(a_space->m_space.normalized());

  result_space->m_space = a_normalized;

  return (PyObject*) result_space;

}


// -----------------------
// ----- method list -----
// -----------------------

PyMethodDef space_module_methods[] = {
  {"cross", (PyCFunction) cross, METH_VARARGS, space_cross__doc__},
  {"dot", (PyCFunction) dot, METH_VARARGS, space_dot__doc__},
  {"magnitude", (PyCFunction) magnitude, METH_VARARGS, space_magnitude__doc__},
  {"normalized", (PyCFunction) normalized, METH_VARARGS, space_normalized__doc__},
  {NULL, NULL}  /* Sentinel */
};

// ----------------------------
// ----- module constants -----
// ----------------------------


PyObject* space_create(const Cartesian::space& a_space) {
  // Creates a python space object from a Cartesian::space object.
  // Intended for use in the module initorbits function to generate
  // space constants with Oribts::space::U[oxyz]

  // TODO borrowed reference?
  Space* py_space(NULL);

  py_space = PyObject_New(Space, &SpaceType); // alloc and inits

  // TODO exception handle this
  if (py_space == NULL){
    PyErr_SetString(sSpaceException, "failed to create space.");
    return NULL;
  }

  py_space->m_space.x(a_space.x());
  py_space->m_space.y(a_space.y());
  py_space->m_space.z(a_space.z());

  return (PyObject*) py_space;
}


// ================
// ===== init =====
// ================

// PyMODINIT_FUNC declares extern "C" too.
PyMODINIT_FUNC initspace(void) {

  PyObject* m;

  SpaceType.tp_new = PyType_GenericNew;
  if (PyType_Ready(&SpaceType) < 0)
    return;

  m = Py_InitModule3("space", space_module_methods,
		     "python wrappers for space objects.");

  Py_INCREF(&SpaceType);
  PyModule_AddObject(m, "space", (PyObject *)&SpaceType);


  // errors
  char eMsgStr[] = "space.error";
  sSpaceException = PyErr_NewException(eMsgStr, NULL, NULL);
  Py_INCREF(sSpaceException);
  PyModule_AddObject(m, "space_error", sSpaceException);

  // constants
  PyObject* space_Uo(NULL);
  space_Uo = space_create(Cartesian::space::Uo);
  Py_INCREF(space_Uo);
  PyModule_AddObject(m, "Uo", (PyObject*)space_Uo);

  PyObject* space_Ux(NULL);
  space_Ux = space_create(Cartesian::space::Ux);
  Py_INCREF(space_Ux);
  PyModule_AddObject(m, "Ux", (PyObject*)space_Ux);

  PyObject* space_Uy(NULL);
  space_Uy = space_create(Cartesian::space::Uy);
  Py_INCREF(space_Uy);
  PyModule_AddObject(m, "Uy", (PyObject*)space_Uy);

  PyObject* space_Uz(NULL);
  space_Uz = space_create(Cartesian::space::Uz);
  Py_INCREF(space_Uz);
  PyModule_AddObject(m, "Uz", (PyObject*)space_Uz);

}
