noinst_bin_PROGRAMS = test
noinst_bindir = .
test_SOURCES = test.cpp ../include/GPP/GPP.hpp
test_CXXFLAGS = ` @FLTK_CONFIG@ --use-images --cxxflags ` -I../include -I/local/include/boost-1_55
test_LDFLAGS = ` @FLTK_CONFIG@ --use-images --ldflags ` -L../src -lgpp -lboost_thread-mgw48-mt-1_55 -lboost_system-mgw48-mt-1_55 -lboost_chrono-mgw48-mt-1_55