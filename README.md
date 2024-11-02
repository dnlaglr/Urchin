# Urchin - Dependency Visualizer
An open-source CLI & GUI visualizer for your C/C++ project dependencies.

## Table of Contents
- [About](#about)
- [How to Build](#how-to-build)
- [Contributing](#contributing)

## About
**Urchin** is an open-source C++ project designed to provide a comprehensive overview of your project dependencies and how they link together. 
Urchin can generate CLI dependency maps and GUI dependency trees for your entire C/C++ project, or respective to a specified file.

## How to Build
To build Urchin, follow these steps:

```
# Clone the repository
git clone https://github.com/dnlaglr/Urchin.git

# Navigate to the project directory
cd Urchin/urchin

# Build CLI, GUI or both
make # Builds both CLI and GUI
make cli # Builds CLI only
make gui # Builds GUI only

# Run Urchin
./bin/urchinCLI [command] # Runs Urchin CLI entry
./bin/urchinGUI # Runs Urchin GUI entry
```

## Contributing
**Urchin** is currently only compatible with Unix-based systems! Any contributions to expand Urchin's uses or compatible systems is greatly appreciated.

> [!IMPORTANT]
> Any feedback on features, bugs, or suggestions for enhancements are instrumental to Urchin's development! If you have an idea please feel free to contribute by submitting an issue or creating a pull request.

## License
Urchin is distributed under the MIT license. You can review the full license agreement [here.](LICENSE.md)