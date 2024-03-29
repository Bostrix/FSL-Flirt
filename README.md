# FLIRT (FMRIB's Linear Image Registration Tool) - Compilation and Usage Guide

## Introduction
Welcome to FLIRT, a robust and accurate tool for linear (affine) intra- and inter-modal brain image registration. This guide will walk you through the process of compiling the FLIRT tool and utilizing its functionalities for image registration tasks.

## Clone the Repository
Begin by cloning the project repository from GitHub onto your local machine. You can do this by running the following command in your terminal or command prompt:
```bash
https://github.com/Bostrix/FSL-Flirt.git
```
This command will create a local copy of the project in a directory named "FSL-Flirt".

## Navigate to Project Directory
Change your current directory to the newly cloned project directory using the following command:
```bash
cd FSL-Flirt
```
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
  
- Modify Makefile of meshclass:
 modify the makefile of meshclass to include additional LDFLAGS for the required libraries. you are using newimage,miscmaths,NewNifti,cprob,znzlib,utils libraries as LDFLAGS variable in meshclass Makefile. Replace `Path to your appropriate library` with the actual path to your directories.
```bash
LDFLAGS += -L/path/to/your/newimage/directory -L/path/to/your/miscmaths/directory -L/path/to/your/NewNifti/directory -L/path/to/your/cprob/directory -L/path/to/your/znzlib/directory -L/path/to/your/utils/directory
```
Once the modifications have been saved, you may use the following command in your terminal to rebuild the mesh class separately:
```bash
make
```
The command executes the Makefile in the mesh class and rebuilds it separately based on the modified configuration and source code changes. After re-running the make command, return to the main flirt directory by `cd ..` and attempt to rebuild the project again.

- Compile Source Code:
Execute the appropriate compile command to build the FLIRT tool. For example:
```bash
make clean
make
```
This command will compile the source code and generate the executable file for FLIRT.

- Resolving Shared Library Errors:
When running an executable on Linux, you may encounter errors related to missing shared libraries.This typically manifests as messages like:
```bash
./flirt: error while loading shared libraries: libexample.so: cannot open shared object file:No such file or directory
```
To resolve these errors,Pay attention to the names of the missing libraries mentioned in the error message.Locate the missing libraries on your system. If they are not present, you may need to install the corresponding packages.If the libraries are installed in custom directories, you need to specify those directories using the `LD_LIBRARY_PATH` environment variable. For example:
```bash
export LD_LIBRARY_PATH=/path/to/custom/libraries:$LD_LIBRARY_PATH
```
Replace `/path/to/custom/libraries` with the actual path to the directory containing the missing libraries.Once the `LD_LIBRARY_PATH` is set, attempt to run the executable again.If you encounter additional missing library errors, repeat steps until all dependencies are resolved.

- Resolving "The environment variable FSLOUTPUTTYPE is not defined" errors:
If you encounter an error related to the FSLOUTPUTTYPE environment variable not being set.Setting it to `NIFTI_GZ` is a correct solution, as it defines the output format for FSL tools to NIFTI compressed with gzip.Here's how you can resolve:
```bash
export FSLOUTPUTTYPE=NIFTI_GZ
```
By running this command, you've set the `FSLOUTPUTTYPE` environment variable to `NIFTI_GZ`,which should resolve the error you encountered.

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
