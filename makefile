work11: work11.o
	gcc -o work11 work11.o

work11.o: work11.c
	gcc -c work11.c

run:
	./work11

clean:
	rm -f *.txt copy
	rm -f *.o work11
	echo Clean Done