
BASENAME = ioxutil

TARGETS = lib$(BASENAME).a
OBJS = cafenv.o tini/tini.o

ifndef LDFLAGS
LDFLAGS = -L.
endif

LDLIBS  = -lioxutil

TEST_TARGETS = test-cafenv
TEST_OBJS = lib$(BASENAME).a

DIRS=tini

include Makefile.common
