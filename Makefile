CC=gcc
AR=ar
CFLAGS=-Wall -g

all: koordynator

coordinator: coordinator.o
	$(AR) rcs libcoordinator.a coordinator.o

agent: agent.o
	$(AR) rcs libagent.a agent.o

main: main.o libcoordinator.a libagent.a
	$(CC) -o koordynator main.o -L. -lcoordinator -lagent

koordynator: coordinator agent main

clean:
	rm -f *.o *.a koordynator
