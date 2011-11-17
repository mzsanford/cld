AM_CFLAGS = -Wall

noinst_PROGRAMS = test
test_SOURCES = test.cc
test_CPPFLAGS = -I.. -I../base -DCLD_WINDOWS
test_LDADD = ../libcld.la
test_LDFLAGS = $(AM_LDFLAGS) $(LIBPNG_LIBS)

TESTS = test


