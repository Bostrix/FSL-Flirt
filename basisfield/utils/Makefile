#include ${FSLCONFDIR}/default.mk

PROJNAME = utils
SOFILES  = libfsl-utils.so
LIBS     = -ldl
OBJS     = FSLProfiler.o matches.o fslStartup.o functions.o usage.o \
           check.o parse.o log.o time_tracer.o threading.o

BUILDSTRING="Unknown"
ifeq (,$(wildcard $${FSLDIR}/etc/fslversion))
    BUILDSTRING = "$(shell cat ${FSLDIR}/etc/fslversion)"
endif

USRCXXFLAGS = -DBUILDSTRING='${BUILDSTRING}'

all: libfsl-utils.so

libfsl-utils.so: ${OBJS}
	$(CXX) $(CXXFLAGS) -shared -o $@ $^ ${LDFLAGS}
