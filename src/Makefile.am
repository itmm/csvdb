AM_CXXFLAGS = --pedantic -Wall -std=c++17 -O2

AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = csv-add csv-cut csv-join csv-sort

csv_add_SOURCES = csv-add.cpp libs/file.cpp libs/file.h libs/entries.cpp libs/entries.h libs/ranges.cpp libs/ranges.h
csv_add_DEPENDENCIES = $(srcdir)/../docs/hx_run
csv_cut_SOURCES = csv-cut.cpp libs/file.cpp libs/file.h libs/entries.cpp libs/entries.h libs/ranges.cpp libs/ranges.h
csv_cut_DEPENDENCIES = $(srcdir)/../docs/hx_run
csv_join_SOURCES = csv-join.cpp libs/file.cpp libs/file.h libs/entries.cpp libs/entries.h libs/ranges.cpp libs/ranges.h libs/cmp.cpp libs/cmp.h
csv_join_DEPENDENCIES = $(srcdir)/../docs/hx_run
csv_sort_SOURCES = csv-sort.cpp libs/file.cpp libs/file.h libs/entries.cpp libs/entries.h libs/ranges.cpp libs/ranges.h libs/cmp.cpp libs/cmp.h
csv_sort_DEPENDENCIES = $(srcdir)/../docs/hx_run
