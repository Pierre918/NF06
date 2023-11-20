#include <C:\Users\kaspa\AppData\Local\Programs\Python\Python312\include\Python.h>


static PyObject* dire_bonjour(PyObject* self, PyObject* args) {
    const char* name;
    if (!PyArg_ParseTuple(args, "s", &name)) {
        return NULL;
    }
    printf("Bonjour, %s!\n", name);
    Py_RETURN_NONE;
}

static PyMethodDef MonModuleMethods[] = {
    {"dire_bonjour",  dire_bonjour, METH_VARARGS, "Saluer quelqu'un"},
    {NULL, NULL, 0, NULL}  /* Sentinel */
};

static struct PyModuleDef monmodule = {
    PyModuleDef_HEAD_INIT,
    "monmodule",   /* nom du module */
    NULL, /* documentation du module, peut être NULL */
    -1,   /* taille du module state, -1 signifie que le module garde un état global */
    MonModuleMethods
};

PyMODINIT_FUNC PyInit_monmodule(void) {
    return PyModule_Create(&monmodule);
}
int main(){
    printf("coucou");
    return 0;
}