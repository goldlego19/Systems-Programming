

all: add avg

add: add.c
	gcc -o add add.c

avg: avg.c
	gcc -o avg avg.c

run_add:
	./add.exe ${ARGS}

run_avg:
	./avg.exe ${ARGS}

clean:
	if exist add.exe del /F /Q add.exe
	if exist avg.exe del /F /Q avg.exe
