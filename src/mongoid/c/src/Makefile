
uuid-test: test.o muuid.o
	gcc test.o muuid.o -o uuid-test
	
muuid.o:
	gcc -c MongoUUID.c -o muuid.o
	
test.o:
	gcc -c test.c -o test.o
	
clean:
	rm -f test.o muuid.o uuid-test