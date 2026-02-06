default:
	gcc sleep.c -o sleep
na:
	gcc sleep.c -nostdlib -fno-stack-protector -o sleep
nsl:
	gcc sleep.c -nostdlib -o sleep
lc:
	gcc sleep.c -nostdlib -lc -o sleep
all:
	./sleep 3
