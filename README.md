<div align="center">
     <picture>
          <source media="(prefers-color-scheme: dark)" srcset="images/logo_dark.png">
          <source media="(prefers-color-scheme: light)" srcset="images/logo.png">
          <img alt="HyperCPU" src="images/logo.png">
     </picture>
</div>

<h4 align="center">HyperCPU — the <i>hyper</i> toolkit for custom <i>hyper</i> ISA</h4>

<p align="center">
     <a href="https://github.com/HyperWinX/HyperCPU/issues">
     <img src="https://img.shields.io/github/issues/HyperWinX/HyperCPU"
          alt="GitHub opened issues"></a>
     <img src="https://img.shields.io/badge/version-0.5.2-red"
          alt="Version">
     <img src="https://img.shields.io/github/actions/workflow/status/HyperWinX/HyperCPU/testing.yml?branch=dev"
          alt="CI status">
     <img src="https://img.shields.io/badge/status-in_development-red"
          alt="Status">
     <img src="https://img.shields.io/github/license/HyperWinX/HyperCPU"
          alt="License">
     <img src="https://img.shields.io/github/stars/HyperWinX/HyperCPU?color=lime"
          alt="Stars">
</p>

>[!IMPORTANT]
> HyperCPU is almost ready for use! Wait for 1.0 release to try it out or build the project yourself, test it and report issues.

<img alt="HyperCPU screenshot" src="images/screenshot.png">

### What is this

HyperCPU is a set of programs created to work with my own simple ISA (instruction set architecture). The project was created for fun, but it took a lot of time (and nerves), and I learned a lot while working on it.

HyperCPU project includes:
* **hCPU emulator** (aka `hcemul`);
* **hASM assembler** (aka `hcasm`);
* ~~**hASM disassembler**~~ (planned).

See [ROADMAP.md](ROADMAP.md) for project ideas and tasks.

### Installation

>[!WARNING]
> HyperCPU supports 64-bit GNU/Linux systems only. It is known to be successfully built and running on `amd64` and `aarch64` architectures.
>
> HyperCPU fails to build and/or work properly under \*BSD systems ­— please do not ask us for support of these systems. Windows support is also not planned.

#### Binaries

Pre-compiled binaries are currently not available. Sorry.

#### Building from sources

Building HyperCPU requires these dependencies to be installed:

* **C++20 compilers:** GCC 12+, Clang 14+.
* **Build system:** Bazel.

Generating the documentation in HTML format requires Python 3 and a few modules (`python3-sphinx`, `python3-sphinx-rtd-theme`) to be installed.

After installing dependencies run these commands in the terminal:

```bash
git clone --recursive https://github.com/HyperCPU-Project/HyperCPU
cd HyperCPU
bazel build //src/... --config=linux-opt
cd docs
make html
```

The compiled binaries should be located in `bazel-out` directory, and the generated documentation should be located in `docs/_build/html` directory. After building the project open `index.html` file and start reading the documentation.

To run the resulting binaries without searching for them in `bazel-out`, use `bazel run`.
```
bazel run //src/Assembler:hcasm -- <args>
bazel run //src/Emulator:hcemul -- <args>
```

Check out [examples](examples) folder for interesting code examples that will help you better understand the syntax of hASM and the power of HyperCPU.

### Usage

#### `hcasm` (hASM assembler)

```bash
$ ./hcasm [-h] [--help] [--version] [-o VAR] [-c] [-V VAR] source
```

* `source` — source code file to be compiled.
* `-h`, `--help` — display help message and exit.
* `--version` — display program version and exit.
* `-o VAR` — specify output binary file name.
* `-c` — generate an object file.
* `-V VAR` — specify verbosity level (`debug`, `info`, `warning`, `error`). Default value is `warning`.

#### `hcemul` (hCPU emulator)

```bash
$ ./hcemul [-h] [--help] [--version] [-v VAR] [-m VAR] [--memory VAR] binary
```

* `binary` — binary file to be executed.
* `-h`, `--help` — display help message and exit.
* `--version` — display program version and exit.
* `-v VAR` — specify verbosity level (`debug`, `info`, `warning`, `error`). Default value is `warning`.
* `-m`, `--memory` — specify max. memory amount to be used. Postfixes are supported. Default value is `8K`.

### Contributing

We will be happy to hear any feedback from you. Do not hesitate to report bugs or suggest any ideas using "Issues" page.

Want to contribute to the project? Read [CONTRIBUTING.md](CONTRIBUTING.md) firstly.

Thank you for your interest in HyperCPU.

### Authors

* **[HyperWin](https://github.com/HyperWinX) (2024 - present time)** — HyperCPU Project founder, lead developer and documentation author.
* **[Ivan Movchan](https://github.com/ivan-movchan) (2025 - present time)** — beta tester, artist and just a contributor.
* **[AshFungor](https://github.com/AshFungor) (2025 - present time)** — good contributor:)

### License

HyperCPU is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.
