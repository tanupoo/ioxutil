
BASENAME = ioxutil

TARGETS = lib$(BASENAME).a
OBJS = cafenv.o tini/tini.o

LDFLAGS = -L.
LDLIBS  = -lioxutil

TEST_TARGETS = test-cafenv lib$(BASENAME).a

DIRS=tini

include Makefile.common
