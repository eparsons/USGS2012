#include "main.h"
#include <stdio.h>
#include "setup.c"
#include "go.c"
#include "patch.c"
#include "cleanup.c"

/* Bind Python function names to our C functions */
static PyMethodDef MainModule_methods[] = {
    {"goCommand", py_goCommand, METH_VARARGS},
    {NULL, NULL}
};

/** 
 * TODO: update the comments of this function
 * Computes the tss value and returns twice as much 
 * @param self: the python object calling this C function
 * @param args: the TSS slider value
 * @return 2*TSS
 */
static PyObject* py_goCommand(PyObject* self, PyObject* args) {

    //TODO: remove this section
    int tss;
    PyArg_ParseTuple(args, "i", &tss);
    tss = 2*tss;

    int day;
    setup();
    while( (day = (hours / 24)) < gui_days_to_run)
    {
	    go();
    }
    PyObject* data = (PyObject*)build_data();                                                  
    cleanup();
    return data;
}

PyObject* build_data(){
    int size = MAP_WIDTH*MAP_HEIGHT + 1;
    int index;
    PyObject* list = PyList_New(size);
    if(!list)
        return NULL;

    PyObject* num =  Py_BuildValue("i", MAP_WIDTH);
    PyList_SET_ITEM(list, 0, num);
    for(index = 1; index < size; index++)
    {
        num = Py_BuildValue("i", colorValues[(index-1)%MAP_WIDTH][(index-1)/MAP_WIDTH]);
        PyList_SET_ITEM(list, index, num);
    }
    return list;
}

/* Python calls this function to let us initialize our module */
void initMainModule() {
    (void) Py_InitModule("MainModule", MainModule_methods);
}
