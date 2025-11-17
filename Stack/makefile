all: build

build: stack.o stack_fn.o # execute first if make is called on its own and it will build the source code if required
	gcc stack.o stack_fn.o -o stack

stack.o: 
	gcc -Wall -c stack.c

stack_fn.o: 
	gcc -Wall -c stack_fn.c

run:
	./stack

clean:					# delete the built executable
	rm -f *.o stack

rebuild: clean all		# delete the built executable and rebuild it