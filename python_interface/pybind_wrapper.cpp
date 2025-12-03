#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "nasch_core.h"

namespace py = pybind11;
// Esto permite que Python vea el struct Auto y sus atributos
PYBIND11_MODULE(nasch_core, m) {
    m.doc() = "Kernel NaSch en C++ optimizado listo para que Python lo utilice";
    // Le pasamos las clases y las funciones/metodos que los acompanan
    py::class_<Auto>(m, "Auto")
        .def(py::init<int, int>(), py::arg("position") = 0, py::arg("velocity") = 0)
        .def_readwrite("pos", &Auto::pos)
        .def_readwrite("vel", &Auto::vel)
        .def("accelerate", &Auto::accelerate)
        .def("brake_to_gap", &Auto::brake_to_gap)
        .def("random_slow", &Auto::random_slow);

    // Funciones principales del modelo creadas en C++
    m.def("init_random_position", &int_random_position,
          py::arg("N"), py::arg("L"), py::arg("seed"));

    m.def("step_nasch", &step_nasch,
          py::arg("cars"), py::arg("L"), py::arg("v_max"),
          py::arg("p"), py::arg("seed"));

    m.def("run_simulation", &run_simulation,
          py::arg("N"), py::arg("L"), py::arg("v_max"),
          py::arg("p"), py::arg("T"), py::arg("seed"));
}
