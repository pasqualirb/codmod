# 07/11/2018

LDLIBS = -lm

all: codmod

codmod: codmod.o draw.o common.o codification.o modulation.o

codmod.o: codmod.c draw.h common.h codification.h modulation.h

draw.o: draw.c draw.h

common.o: common.c common.h

codification.o: codification.c codification.h draw.h common.h

modulation.o: modulation.c draw.h common.h
