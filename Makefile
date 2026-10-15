all: demo test

# demo: src/main.c src/dstring.c include/dstring.h
# 	gcc -g -Iinclude src/main.c src/dstring.c -o demo

test: tests/test.c Helper/apcHelper.c Include/apc.h
	gcc -g -Iinclude tests/test.c Helper/apcHelper.c Operations/sum.c Operations/sub.c Operations/mul.c -o test_apc