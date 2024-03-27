#$Id$
#include ${FSLCONFDIR}/default.mk

PROJNAME = meshclass

XFILES=drawmesh selfintersection

LIBS=-lfsl-newimage -lfsl-miscmaths -lfsl-NewNifti -lfsl-cprob -lfsl-znz -lfsl-utils -llapack -lblas -lz

MESHOBJS=point.o mpoint.o triangle.o mesh.o pt_special.o profile.o
DRAWOBJS=drawmesh.o mpoint.o triangle.o mesh.o point.o pt_special.o
INTEROBJS=selfintersection.o mpoint.o triangle.o mesh.o point.o pt_special.o

#Specify the default compiler
CXX = g++

#Specify the flags
CXXFLAGS += -fpic
LDFLAGS += -L/home/ubuntu/flirt/newimage -L/home/ubuntu/flirt/miscmaths -L/home/ubuntu/flirt/NewNifti -L/home/ubuntu/flirt/cprob -L/home/ubuntu/flirt/znzlib -L/home/ubuntu/flirt/utils

#Define targets
all: libfsl-meshclass.so ${XFILES}

#Compile the shared library
libfsl-meshclass.so: ${MESHOBJS}
	$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(LDFLAGS) ${LIBS}

#Compile drawmesh
drawmesh: ${DRAWOBJS}
	${CXX} ${CXXFLAGS} -o $@ $^ ${LDFLAGS} ${LIBS}

#Compile selfintersection
selfintersection: ${INTEROBJS}
	${CXX} ${CXXFLAGS} -o $@ $^ ${LDFLAGS} ${LIBS}

#Rule to build object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

#Clean rule
clean:
	rm -f .o.so ${XFILES}
