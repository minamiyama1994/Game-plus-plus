lib_LTLIBRARIES = libgpp.la
libgpp_la_SOURCES = GPP.cpp GPP_impl.cpp
libgpp_la_CXXFLAGS = ` @FOX_CONFIG@ --cflags ` -std=gnu++11 -I../include -I/local/include/boost-1_55 -I../../FTMP/include -I../../Sprout
libgpp_la_LDFLAGS = ` @FOX_CONFIG@ --libs ` -lboost_thread-mgw48-mt-1_55 -lboost_system-mgw48-mt-1_55 -lboost_chrono-mgw48-mt-1_55