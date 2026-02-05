default:
	gcc sleep.c -o sleep
	./sleep 3

nsl:
	gcc sleep.c -nostdlib -o sleep
	./sleep 3

lc:
	gcc sleep.c -nostdlib -lc -o sleep
	./sleep 3
