all:	build

build: Hello.exe	

Hello.exe: Hello.c
	gcc Hello.c -o Hello.exe
run: Hello.exe
	.\Hello.exe
clean:
	if exist Hello.exe del /F /Q Hello.exe