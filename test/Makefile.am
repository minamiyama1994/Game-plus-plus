noinst_bin_PROGRAMS = test
noinst_bindir = .
test_SOURCES = test.cpp ../include/GPP/GPP.hpp
test_CXXFLAGS = ` @FLTK_CONFIG@ --use-images --cxxflags ` -I../include
test_LDFLAGS = ` @FLTK_CONFIG@ --use-images --ldflags ` -L../src -lgpp