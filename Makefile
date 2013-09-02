CPPS= \
	asciiart \
	chucknorris \
	defillibrators \
	stock_losses \
	network_cabling \
	conway \
	horse_racing \
	super_computer \
	temperatures \
	dwarfs_and_giants \
	mimetypes \
	roller_coaster \
	telephone \
	cgx_formatter \
	tan_network \
	genome_sequencing

HASKELLS=tan_network_haskell

all: $(CPPS) $(HASKELLS)

CPPFLAGS+=-std=c++0x -Wall -pedantic 
#CPPFLAGS+=-fsanitize=undefined 
CPPFLAGS+=-g -O3
CPPFLAGS+=-isystem ~/custom/boost/

CPPFLAGS+=-fopenmp
CPPFLAGS+=-march=native

LDFLAGS+=-ltcmalloc
# LDFLAGS+=-L ~/custom/boost/stage/lib/
# LDFLAGS+=-lboost_system -lboost_regex -lboost_thread -lpthread

CXX=/usr/lib/gcc-snapshot/bin/g++
CC=/usr/lib/gcc-snapshot/bin/gcc
# CXX=clang++
# CC=clang

%:%.cpp
	$(CXX) $(CPPFLAGS) $^ -o $@ $(LDFLAGS)

%:%.hs
	ghc -O2 $^ -o $@
