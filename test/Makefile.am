noinst_bin_PROGRAMS = test
noinst_bindir = .
test_SOURCES = test.cpp
test_CXXFLAGS = ` @FOX_CONFIG@ --cflags ` -std=gnu++11 -I../include -I/local/include/boost-1_55 -I../../FTMP/include -I../../Sprout
test_LDFLAGS = ` @FOX_CONFIG@ --libs ` -L../src -lgpp -lboost_thread-mgw48-mt-1_55 -lboost_system-mgw48-mt-1_55 -lboost_chrono-mgw48-mt-1_55