build:
	gcc -w -std=c11 -o a.exe \
	./src/main.c \
	./src/screen/*.c \
	./src/component/*.c \
	./src/util/*.c \
	./src/shape/*.c \
	-lmingw32 \
	-lSDL2main \
	-lSDL2
