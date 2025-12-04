all: clean countInit countRUN

countInit:
	gcc -Wall -o count_marks count_marks.c

countRUN:
	.\count_marks.exe "marks.txt"

clean:
	-rm count_marks