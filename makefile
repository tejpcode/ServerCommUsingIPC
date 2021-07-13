#! /bin/bash
Server: init.o server.o infra.o exitfunc.o threadfunc.o
	gcc -o Server init.o server.o infra.o exitfunc.o threadfunc.o -lpthread
server.o: server.c header.h declaration.h datastructure.h
	gcc -c server.c 
infra.o: infra.c header.h declaration.h datastructure.h
	gcc -c infra.c 
threadfunc.o: threadfunc.c header.h declaration.h datastructure.h
	gcc -c threadfunc.c 
init.o: init.c header.h declaration.h
	gcc -c init.c
exitfunc.o: exitfunc.c header.h declaration.h datastructure.h
	gcc -c exitfunc.c
