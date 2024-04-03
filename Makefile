# Specify the default compiler
CXX = g++

# Specify the -fpic flag
CXXFLAGS += -fpic

# Additional LDFLAGS for WARPFNS library
WARPFNS_LDFLAGS = -L${HOME}/FSL-Flirt/warpfns  -L${HOME}/FSL-Flirt/meshclass -L${HOME}/FSL-Flirt/basisfield -L${HOME}/FSL-Flirt/miscmaths -lfsl-warpfns -lfsl-meshclass -lfsl-basisfield -lfsl-miscmaths

# Additional LDFLAGS for znzlib library
ZNZLIB_LDFLAGS = -L${HOME}/FSL-Flirt/znzlib -lfsl-znz

# Define source files
SRCS = applyxfm4D.cc avscale.cc convert_xfm.cc flirt.cc img2imgcoord.cc img2stdcoord.cc makerot.cc midtrans.cc pointflirt.cc rmsdiff.cc std2imgcoord.cc

# Define object files
OBJS = $(SRCS:.cc=.o)

# Define library source files and directories
LIB_DIRS = warpfns basisfield miscmaths newimage NewNifti utils cprob znzlib meshclass
LIB_SRCS = $(foreach dir,$(LIB_DIRS),$(wildcard $(dir)/*.cc))
LIB_OBJS = $(LIB_SRCS:.cc=.o)

# Define targets
all: flirt applyxfm4D avscale convert_xfm img2imgcoord img2stdcoord makerot midtrans pointflirt rmsdiff std2imgcoord

# Compile the final executable
flirt: libraries globaloptions.o flirt.o $(LIB_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ globaloptions.o flirt.o $(LIB_OBJS) $(LDFLAGS) $(ZNZLIB_LDFLAGS)  -lblas -llapack -lz

applyxfm4D: libraries globaloptions.o applyxfm4D.o $(LIB_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ globaloptions.o applyxfm4D.o $(LIB_OBJS) $(LDFLAGS) $(ZNZLIB_LDFLAGS)  -lblas -llapack -lz

avscale: libraries globaloptions.o avscale.o $(LIB_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ globaloptions.o avscale.o $(LIB_OBJS) $(LDFLAGS) $(ZNZLIB_LDFLAGS)  -lblas -llapack -lz

convert_xfm: libraries globaloptions.o convert_xfm.o $(LIB_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ globaloptions.o convert_xfm.o $(LIB_OBJS) $(LDFLAGS) $(ZNZLIB_LDFLAGS)  -lblas -llapack -lz

img2imgcoord: libraries globaloptions.o img2imgcoord.o $(LIB_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ globaloptions.o img2imgcoord.o $(LIB_OBJS) $(LDFLAGS) $(WARPFNS_LDFLAGS) $(ZNZLIB_LDFLAGS)  -lblas -llapack -lz

img2stdcoord: libraries globaloptions.o img2stdcoord.o $(LIB_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ globaloptions.o img2stdcoord.o $(LIB_OBJS) $(LDFLAGS) $(WARPFNS_LDFLAGS) $(ZNZLIB_LDFLAGS)  -lblas -llapack -lz

makerot: libraries globaloptions.o makerot.o $(LIB_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ globaloptions.o makerot.o $(LIB_OBJS) $(LDFLAGS) $(ZNZLIB_LDFLAGS)  -lblas -llapack -lz

midtrans: libraries globaloptions.o midtrans.o $(LIB_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ globaloptions.o midtrans.o  $(LIB_OBJS) $(LDFLAGS) $(ZNZLIB_LDFLAGS)  -lblas -llapack -lz

pointflirt: libraries globaloptions.o pointflirt.o $(LIB_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ globaloptions.o pointflirt.o $(LIB_OBJS) $(LDFLAGS) $(ZNZLIB_LDFLAGS)  -lblas -llapack -lz

rmsdiff: libraries globaloptions.o rmsdiff.o $(LIB_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ globaloptions.o rmsdiff.o $(LIB_OBJS) $(LDFLAGS) $(ZNZLIB_LDFLAGS)  -lblas -llapack -lz

std2imgcoord: libraries globaloptions.o std2imgcoord.o $(LIB_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ globaloptions.o std2imgcoord.o $(LIB_OBJS) $(LDFLAGS) $(WARPFNS_LDFLAGS) $(ZNZLIB_LDFLAGS)  -lblas -llapack -lz




# Rule to build object files
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Phony target to build all libraries
.PHONY: libraries
libraries:
	@for dir in $(LIB_DIRS); do \
	$(MAKE) -C $$dir CXX=$(CXX) CXXFLAGS='$(CXXFLAGS)' LDFLAGS='$(LDFLAGS)'; \
	done

# Clean rule
clean:
	rm -f flirt $(OBJS) $(LIB_OBJS) $(shell find . -type f \( -name "*.o" -o -name "*.so" \))
