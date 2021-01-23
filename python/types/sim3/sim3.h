#include <g2o/types/sim3/sim3.h>
#include <pybind11/eigen.h>
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>

#include "python/core/base_edge.h"
#include "python/core/base_vertex.h"

namespace py = pybind11;
using namespace pybind11::literals;

namespace g2o {

void declareSim3(py::module& m) {
  py::class_<Sim3>(m, "Sim3")
      .def(py::init<>())
      .def(py::init<const Eigen::Quaterniond&, const Eigen::Vector3d&, double>())
      .def(py::init<const Eigen::Matrix3d&, const Eigen::Vector3d&, double>())
      .def(py::init<const Vector7&>())

      .def("map", &Sim3::map)
      .def("log", &Sim3::log)
      .def("inverse", &Sim3::inverse)

      .def("__getitem__", (double& (Sim3::*)(int)) & Sim3::operator[])
      .def(py::self * py::self)
      .def(py::self *= py::self)

      .def("normalize_rotation", &Sim3::normalizeRotation)

      .def("translation", (Eigen::Vector3d & (Sim3::*)()) & Sim3::translation)
      .def("rotation", (Eigen::Quaterniond & (Sim3::*)()) & Sim3::rotation)
      .def("scale", (double& (Sim3::*)()) & Sim3::scale);

  templatedBaseVertex<7, Sim3>(m, "_7_Sim3");
  templatedBaseEdge<7, Sim3>(m, "_7_Sim3");
}

}  // namespace g2o