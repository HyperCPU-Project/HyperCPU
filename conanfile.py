from functools import cached_property, lru_cache
from typing import Callable, Mapping, Any, Iterable

from conan import ConanFile
from conan.tools.google import bazel_layout


class HyperCPU(ConanFile):
    name: "HyperCPU"
    settings = ["os", "compiler", "build_type", "arch"]

    # dynamically set conanfile attributes
    conan_data: Mapping[str, Any]
    requires: Callable[[str], None]

    @cached_property
    def generators(self) -> Iterable[str]:
        return ["BazelToolchain", "BazelDeps"]

    @lru_cache
    def requirements(self) -> None:
        for req, version in self.conan_data["requirements"].items():
            self.requires(f"{req}/{version}")

    def layout(self):
        bazel_layout(self)
