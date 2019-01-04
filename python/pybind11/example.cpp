#include <pybind11/pybind11.h>
#include <string>
namespace py = pybind11;

using std::string;
int add(int i, int j)
{
    return i + j;
}

string show(string &text) {
	return text;
}

PYBIND11_MODULE(example, m)
{
    // optional module docstring
    m.doc() = "pybind11 example plugin";
    // expose add function, and add keyword arguments and default arguments
    m.def("add", &add, "A function which adds two numbers", py::arg("i")=1, py::arg("j")=2);
    m.def("show", &show, "A function which adds two numbers");

}
