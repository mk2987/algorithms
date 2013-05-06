UNSORTED_C 	:= g_unsorted_array.c
GEN_UNSORTED_C 	:= gen_unsorted_array.c
GEN_UNSORTED	:= /tmp/gen_unsorted
HFILES		:= utils.h main.h sort.h tree.h heap.h
CFILES 		:= ${UNSORTED_C} utils.c sort.c main.c tree.c heap.c
BIN 		:= /tmp/sort
CC 		:= clang
ifdef DEBUG
CFLAGS	= -g
endif

.PHONY : run unsorted clean clobber bintree maxheap

all: ${BIN}

unsorted: ${UNSORTED_C}

${UNSORTED_C}: ${GEN_UNSORTED_C} ${HFILES}
	${CC} ${CFLAGS} ${GEN_UNSORTED_C} -o ${GEN_UNSORTED}
	${GEN_UNSORTED}

${BIN}: ${CFILES} ${HFILES}
	${CC} ${CFLAGS} ${CFILES} -o $@

run: ${BIN}
	${BIN}

bintree: ${BIN}
	${BIN}
	dot -Tps /tmp/bintree.dot -o /tmp/g1.ps && \
	ps2pdf /tmp/g1.ps /tmp/g1.pdf && \
	acroread /tmp/g1.pdf;

maxheap: ${BIN}
	${BIN}
	dot -Tps /tmp/bintree.dot -o /tmp/g1.ps && \
	ps2pdf /tmp/g1.ps /tmp/g1.pdf && \
	acroread /tmp/g1.pdf;

clean clobber:
	rm -rf ${BIN} ${GEN_UNSORTED} /tmp/bintree.dot /tmp/g1.ps /tmp/g1.pdf

