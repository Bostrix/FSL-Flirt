
# available values are 'armawrap', 'newmat', and 'armadillo'
LIB = armawrap

# point to include dir if not running from source repository
ARMAWRAP_INCLUDE_DIR ?= ../

CXX      ?= g++
CXXFLAGS ?= -Wall -pedantic -std=c++11
CXXFLAGS += --coverage -fno-inline
LDFLAGS  ?=

CXXFLAGS += -DARMAWRAP_API=0
CXXFLAGS += -DARMADILLO_API=1
CXXFLAGS += -DNEWMAT_API=2

ifeq ($(LIB),armawrap)
CXXFLAGS += -DLIB=0
else ifeq ($(LIB),armadillo)
CXXFLAGS += -DLIB=1
else ifeq ($(LIB),newmat)
CXXFLAGS += -DLIB=2
endif

ifeq ($(LIB),newmat)
CXXFLAGS += -Inewmat/
LDFLAGS  += -Lnewmat/
LDFLAGS  += -lnewmat
CXXFLAGS += -DUSING_NEWMAT_API

else
LDFLAGS  += -llapack
LDFLAGS  += -lblas
CXXFLAGS += -DARMA_USE_LAPACK
CXXFLAGS += -DARMA_USE_BLAS
CXXFLAGS += -I$(ARMAWRAP_INCLUDE_DIR)/
endif

ifeq ($(LIB),armawrap)
CXXFLAGS  += -DUSING_NEWMAT_API
endif

testsrcs = $(wildcard test*.cpp)
testexcs = $(basename $(testsrcs))

default: $(testexcs)

%: %.cpp
	@echo "Compiling $< -> $@ ..."
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS)

clean:
	@rm -f $(testexcs) *.gcda *.gcno
