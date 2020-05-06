AM_CXXFLAGS = --pedantic -Wall -std=c++17 -O2

AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = cd-add cd-cut cd-join cd-sort

cd_add_SOURCES = cd-add.cpp libs/file.cpp libs/file.h libs/entries.cpp libs/entries.h libs/ranges.cpp libs/ranges.h
cd_add_DEPENDENCIES = $(srcdir)/../doc/hx_run
cd_cut_SOURCES = cd-cut.cpp libs/file.cpp libs/file.h libs/entries.cpp libs/entries.h libs/ranges.cpp libs/ranges.h
cd_cut_DEPENDENCIES = $(srcdir)/../doc/hx_run
cd_join_SOURCES = cd-cut.cpp libs/file.cpp libs/file.h libs/entries.cpp libs/entries.h libs/ranges.cpp libs/ranges.h libs/cmp.cpp libs/cmp.h
cd_join_DEPENDENCIES = $(srcdir)/../doc/hx_run
cd_sort_SOURCES = cd-cut.cpp libs/file.cpp libs/file.h libs/entries.cpp libs/entries.h libs/ranges.cpp libs/ranges.h libs/cmp.cpp libs/cmp.h
cd_sort_DEPENDENCIES = $(srcdir)/../doc/hx_run
