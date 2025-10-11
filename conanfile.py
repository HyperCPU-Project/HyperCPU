from conan import ConanFile
from conan.tools.cmake import cmake_layout


class HyperCPU(ConanFile):
    name = "HyperCPU"
    version = "0.5.0"
    settings = ["os", "compiler", "build_type", "arch"]
    author = "HyperCPU Project"
    requires = [
        "abseil/20240116.1",
        "gtest/1.14.0",
        "spdlog/1.15.0",
        "argparse/3.2",
        "eternal/1.0.1",
        "fmt/11.0.2",
        "re2/20250722"
    ]
    generators = ["CMakeToolchain", "CMakeDeps"]

    def layout(self) -> None:
        cmake_layout(self)
