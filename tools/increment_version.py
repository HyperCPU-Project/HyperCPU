#!/usr/bin/env python3

from dataclasses import dataclass
from pathlib import Path
from typing import Callable, Union
from functools import wraps
from io import StringIO
import re
import argparse
import inspect


# version increment happens to files, so each method
# that updates version has a certain file that it processes
def dispatching_file(file: Union[Path, str]):
    def factory(func: Callable):
        nonlocal file
        if not isinstance(file, Path):
            file = Path(file)
        setattr(func, "is_dispatcher", True)
        setattr(func, "file", file)

        @wraps(func)
        def dispatcher(*args, **kwargs):
            return func(*args, file=file, **kwargs)

        return dispatcher

    return factory


# We follow SemVer: https://semver.org/
@dataclass
class Version:
    major: int
    minor: int
    patch: int

    def __str__(self) -> str:
        return f"{self.major}.{self.minor}.{self.patch}"

    @classmethod
    def from_str(cls, s: str) -> "Version":
        major, minor, patch = map(int, s.split("."))
        return cls(major=major, minor=minor, patch=patch)


class Incrementors:
    def fetch_version(self) -> Version:
        # we fetch current version from bazel module
        with open("MODULE.bazel", "r") as fd:
            contents = fd.read()

        module = self.__bazel_find_module(contents)
        current_version = self.__bazel_find_version(module)

        grouping = r"(.*)=\s*[\'\"](.*)[\'\"]"
        if (result := re.search(grouping, current_version, flags=re.DOTALL)) is None:
            raise ValueError(f"could not apply grouping: {grouping}")

        version_str = result.group(2)
        return Version.from_str(version_str)

    @dispatching_file("src/Common/Version.hpp")
    def update_version_file(self, file: Path, version: Version):
        contents = StringIO()
        version_matches = 0

        with open(file, "r") as fd:
            for line in fd:
                if "HCPU_VERSION" not in line.upper():
                    contents.write(line + "\n")
                    continue

                version_matches += 1
                prefix, _ = line.split("=")
                contents.write(f'{prefix.strip()} = "{str(version)}";\n')

        if version_matches < 1:
            raise ValueError("could not find a line with version string")
        if version_matches > 1:
            raise ValueError(
                f"found {version_matches} lines with version string, expected a single line"
            )

        with open(file, "w") as fd:
            fd.write(contents.getvalue())

    @dispatching_file("MODULE.bazel")
    def update_module_file(self, file: Path, version: Version):
        with open(file, "r") as fd:
            contents = fd.read()

        module = self.__bazel_find_module(contents)
        current_version = self.__bazel_find_version(module)
        newly_versioned_module = module.replace(
            current_version, f'version = "{str(version)}"'
        )
        contents = contents.replace(module, newly_versioned_module)

        with open(file, "w") as fd:
            fd.write(contents)

    @dispatching_file("README.md")
    def update_readme(self, file: Path, version: Version):
        with open(file, "r") as fd:
            content = fd.read()

        new_version = f'<img src="https://img.shields.io/badge/version-{version}-red"'
        pattern = r'<img src=\"https:\/\/img\.shields\.io\/badge\/version-[^"]*\"'
        content = re.sub(pattern, new_version, content)
        with open(file, "w") as fd:
            fd.write(content)

    def __bazel_find_module(self, contents: str) -> str:
        module_pattern = r"module\(.*?\)"
        matches = re.findall(module_pattern, contents, flags=re.DOTALL)
        if len(matches) != 1:
            raise ValueError(
                f"regex {module_pattern} matched {len(matches)} times, expected to match only once"
            )

        return matches[0]

    def __bazel_find_version(self, module: str) -> str:
        version_pattern = r"version\s*=\s*[\'\"].*[\'\"]"
        matches = re.findall(version_pattern, module, flags=re.DOTALL)
        if len(matches) != 1:
            raise ValueError(
                f"regex {version_pattern} matched {len(matches)} times, expected to match only once"
            )

        return matches[0]


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--increment", action="store", dest="target", choices=["patch", "minor"]
    )
    args = parser.parse_args()

    incrementors = Incrementors()
    new_version = incrementors.fetch_version()
    match args.target:
        case "patch":
            new_version.patch += 1
        case "minor":
            new_version.patch = 0
            new_version.minor += 1

    for _, method in inspect.getmembers(incrementors, predicate=inspect.ismethod):
        if hasattr(method, "is_dispatcher"):
            method(version=new_version)

    print(new_version)


if __name__ == "__main__":
    main()
