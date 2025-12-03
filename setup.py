from setuptools import setup, Extension
import pybind11
import os # Para ubicar carpetas

# Rutas base
ROOT = os.path.dirname(os.path.abspath(__file__))
CPP_CORE = os.path.join(ROOT, "cpp_core")
SRC_DIR = os.path.join(CPP_CORE, "src")
INC_DIR = os.path.join(CPP_CORE, "include")
PY_IFACE = os.path.join(ROOT, "python_interface")

# Extensión para pybind11
module = Extension(
    "nasch_core",
    sources=[
        os.path.join(PY_IFACE, "pybind_wrapper.cpp"),
        os.path.join(SRC_DIR, "nasch_core.cpp"),
        #os.path.join(SRC_DIR, "helpers.cpp"),
    ],
    include_dirs=[
        INC_DIR,
        pybind11.get_include()
    ],
    language="c++",
    extra_compile_args=["/std:c++17" if os.name == 'nt' else "-std=c++17" ]
)

setup(
    name="nasch_simulator",
    version="0.1",
    author="tu_nombre",
    ext_modules=[module],
)
