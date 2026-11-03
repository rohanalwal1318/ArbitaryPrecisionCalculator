all: demo test

demo: Src/main.c Helper/apcHelper.c Include/apc.h
	gcc -g -IInclude Src/main.c Helper/apcHelper.c Operations/sum.c Operations/sub.c Operations/mul.c Operations/div.c -o a.out

test: Tests/test.c Helper/apcHelper.c Include/apc.h
	gcc -g -IInclude Tests/test.c Helper/apcHelper.c Operations/sum.c Operations/sub.c Operations/mul.c Operations/div.c -o test_apc
