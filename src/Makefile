
all: hddotb

hddotb:  main.o
	gcc -o hddotb main.o

main.o: main.c 
	gcc -o main.o -c main.c -W -Wall -ansi -pedantic

clean:
	rm -rf *.o

mrproper: clean
	rm -rf hddotb
