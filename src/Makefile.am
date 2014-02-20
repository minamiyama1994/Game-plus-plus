lib_LTLIBRARIES = libgpp.la
libgpp_la_SOURCES = GPP.cpp ../include/GPP/GPP.hpp
libgpp_la_CXXFLAGS = ` @FLTK_CONFIG@ --use-images --cxxflags ` -I../include -I/local/include/boost-1_55
libgpp_la_LDFLAGS = ` @FLTK_CONFIG@ --use-images --ldflags ` -lboost_thread-mgw48-mt-1_55 -lboost_system-mgw48-mt-1_55 -lboost_chrono-mgw48-mt-1_55