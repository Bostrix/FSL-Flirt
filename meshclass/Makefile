# $Id$
#include ${FSLCONFDIR}/default.mk

PROJNAME = meshclass

XFILES=drawmesh selfintersection

LIBS=-lfsl-newimage -lfsl-miscmaths -lfsl-NewNifti -lfsl-cprob -lfsl-znz -lfsl-utils

MESHOBJS=point.o mpoint.o triangle.o mesh.o pt_special.o profile.o
DRAWOBJS=drawmesh.o mpoint.o triangle.o mesh.o point.o pt_special.o
INTEROBJS=selfintersection.o mpoint.o triangle.o mesh.o point.o pt_special.o

all: libfsl-meshclass.so ${XFILES}

libfsl-meshclass.so: ${MESHOBJS}
	$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(LDFLAGS)

drawmesh: ${DRAWOBJS}
	${CXX} ${CXXFLAGS} -o $@ $^ -L${HOME}/FSL-Flirt/newimage -L${HOME}/FSL-Flirt/miscmaths -L${HOME}/FSL-Flirt/NewNifti \
        -L${HOME}/FSL-Flirt/cprob -L${HOME}/FSL-Flirt/znzlib -L${HOME}/FSL-Flirt/utils -lfsl-newimage -lfsl-miscmaths -lfsl-NewNifti -lfsl-cprob -lfsl-znz -lfsl-utils -llapack -lblas -lz

selfintersection: ${INTEROBJS}
	${CXX} ${CXXFLAGS} -o $@ $^ ${LDFLAGS}
