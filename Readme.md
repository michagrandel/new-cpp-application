# C++ Application Template

A cross-platform C++20 console application template for starting new projects
with CMake, Ninja, and vcpkg. It includes VS Code and Visual Studio integration
and a runnable example of colored, UTF-8-capable logging.

Dependencies include [CLI11](https://github.com/CLIUtils/CLI11) for future
command-line parsing and [spdlog](https://github.com/gabime/spdlog) for logging,
with fmt provided transitively. The current example demonstrates logging only.

> **What to write:** Replace the title with your project's name. In one or two
> sentences, explain what it does, who it is for, and why it is useful. Replace
> the template details above with your application's main capabilities.

## Installation

### Prerequisites

- A C++20-capable compiler: MSVC on Windows, GCC or Clang on Linux, or Apple
  Clang on macOS.
- [CMake](https://cmake.org/download/) 3.21 or newer and
  [Ninja](https://ninja-build.org/).
- [vcpkg](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started):
  follow its setup instructions, including bootstrapping it.
- Either VS Code with the **C/C++** and **CMake Tools** extensions, or Visual
  Studio with C++ and CMake support installed.
- Git if you want to clone the repository.

### Start a new project

Copy this template into your new repository, or clone it as a starting point:

```powershell
git clone https://github.com/michagrandel/new-cpp-application.git my-cpp-app
Set-Location my-cpp-app
```

A clone retains this template's Git history and remote. If you clone it, update
the remote to your own repository before pushing.

Before developing your application:

1. Change the project name and version in [CMakeLists.txt](CMakeLists.txt).
2. Update the package name, version, and dependencies in [vcpkg.json](vcpkg.json).
3. Update the executable paths in [.vscode/launch.json](.vscode/launch.json)
   when renaming `HelloWorld`.
4. Replace the example in [src/main.cpp](src/main.cpp) with your application.
5. Customize this README and choose a license.

### Configure and build

Set `VCPKG_ROOT` to your vcpkg installation before opening your IDE. For example,
on Windows:

```powershell
$env:VCPKG_ROOT = "C:\tools\vcpkg"
code .
```

Replace the example path with your actual installation. This environment
variable applies to the current terminal and applications launched from it.
On Linux and macOS, set the same variable using your shell's syntax.

In VS Code, use **CMake: Select Configure Preset**, choose the matching preset,
then run **CMake: Configure** and **CMake: Build** from the Command Palette.
vcpkg restores the declared dependencies during configuration.

| Preset | Platform and compiler |
| --- | --- |
| `default` | Windows x64, MSVC, static libraries and runtime |
| `linux-gcc` | Linux, GCC |
| `linux-clang` | Linux, Clang |
| `macos-clang` | macOS, Clang |

On Windows, CMake Tools prepares the MSVC developer environment. In Visual
Studio, open the project folder, select the applicable CMake preset, and build
using its CMake integration.

All presets use the same `build` directory. Use **CMake: Delete Cache and
Reconfigure** before switching compilers to avoid reusing an incompatible cache.

> **What to write:** List supported platforms, minimum tool versions, required
> dependencies, and exact setup steps. Replace the repository URL and template
> customization checklist with your own installation instructions. If you
> distribute binaries, explain how to download and install them.

## Usage

After building, run the example from the project root on Windows:

```powershell
.\build\HelloWorld.exe
```

On Linux and macOS, run the `HelloWorld` executable in the `build` directory.
The example prints timestamped messages at info, warning, error, and debug
levels with colors and UTF-8 text. The warning and error messages are demo
output, not startup failures; the program exits successfully.

You can also use **CMake: Run Without Debugging** in VS Code. For Windows
debugging, select the **Debug** launch configuration and press **F5**. The
**Debug (GDB)** configuration requires GDB to be installed and available;
macOS users may need a debugger configuration appropriate for their toolchain.

> **What to write:** Show the smallest useful example first, followed by expected
> output or results. Document actual arguments, configuration, and common use
> cases as your application grows. Keep examples runnable, and remove the demo
> description once you replace it.

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

Please make sure to update tests as appropriate. This template does not yet
configure automated tests, linters, or formatters; add relevant tests alongside
new functionality and document how to run them.

Keep changes compatible with Windows, Linux, and macOS. Put shared build logic
in CMake rather than IDE-specific files, and manage dependencies through vcpkg.
Before submitting a pull request, build with the applicable preset and run the
application to check the affected behavior.

### Code documentation skill

The project includes the Copilot skill
[document-code](.github/skills/document-code/SKILL.md). Invoke it with
`/document-code` and specify the files or symbols to document; Copilot can also
load it automatically for relevant documentation tasks.

The skill requires English Microsoft-style XML documentation (`///`) for all
declarations in the requested scope, including classes, functions, and variables.
Each source file starts with a short English purpose comment followed by a blank
line.
It favors readable code over implementation comments. Such comments use `//`,
contain no code, and explain only why a complex, multiline block is necessary.
Every implementation comment is preceded by a blank line.
XML extraction support depends on the declaration and documentation tool.

> **What to write:** Explain how to report bugs, propose features, set up a
> development environment, and validate changes. Add your test commands and
> coding conventions when established, and link to a contribution guide if
> needed.

## License

No project license has been selected or included yet.

> **What to write:** Choose a license you are authorized to apply, add its full
> text in a `LICENSE` file, and replace this section with the license name and
> a link to that file. For example, if you choose MIT, use
> `[MIT](LICENSE)`. See [Choose a License](https://choosealicense.com/) for
> guidance. Check dependency licenses separately; they do not license your own
> project.
