all: demo full

demo:
	gcc -Wall FullDemo.c -o demo.exe

full:
	gcc -DFULL -Wall FullDemo.c -o full.exe
run_demo: demo
	.\demo.exe
run_full: full
	.\full.exe

clean:
	if exist full.exe del /F /Q full.exe
	if exist demo.exe del /F /Q demo.exe

