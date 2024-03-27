# FLIRT (FMRIB's Linear Image Registration Tool) - Compilation and Usage Guide

## Introduction
Welcome to FLIRT, a robust and accurate tool for linear (affine) intra- and inter-modal brain image registration. This guide will walk you through the process of compiling the FLIRT tool and utilizing its functionalities for image registration tasks.

## Compilation
To compile FLIRT, follow these steps:
- Install Required Libraries:
Ensure that all necessary libraries are installed on your system. Use the following commands to install dependencies:
```bash
sudo apt-get install libblas-dev libblas3
sudo apt-get install liblapack-dev liblapack3
sudo apt-get install zlib1g zlib1g-dev
```

- Modify Makefile:
 After installing the necessary tools, modify the makefile to include additional LDFLAGS for the required libraries. For example, if using warfns library,basisfield library,meshclass library,miscmaths library and zlib, add the following line to the makefile:
```bash
  WARPFNS_LDFLAGS = -L/path/to/your/warpfns/library  -L/path/to/your/meshclass/library -L/path/to/your/basisfield/library -L/path/to/your/miscmaths/library -lfsl-warpfns -lfsl-meshclass -lfsl-basisfield -lfsl-miscmaths
  ZNZLIB_LDFLAGS = -L/path/to/your/znzlib/directory -lfsl-znz
```
  Replace `Path to your library` with the actual path to your directories. Make sure you added `$(WARPFNS_LDFLAGS)`,`$(ZNZLIB_LDFLAGS)` in the compile step of the makefile.

- Compile Source Code:
Execute the appropriate compile command to build the FLIRT tool. For example:
```bash
make clean
make
```
This command will compile the source code and generate the executable file for FLIRT.

## Usage
Once FLIRT is successfully compiled, you can use it for image registration tasks. Follow these steps to utilize FLIRT:
- Execute the ./flirt command with the required options and input files. Here is the basic syntax:
```bash
  ./flirt [options] -in <inputvol> -ref <refvol> -out <outputvol>
```
Replace `<inputvol>` and `<refvol>` with the paths to your input and reference volumes, respectively.

- Specify Options:
Customize the behavior of FLIRT by providing additional options as needed. Refer to the usage guide provided in the documentation for a list of available options and their descriptions.

## Conclusion
You have now successfully compiled FLIRT and learned how to utilize it for image registration tasks. Follow the provided instructions to compile the tool and run FLIRT commands with your desired options. If you encounter any issues or have further questions, refer to the provided documentation or seek assistance from the project maintainers.
