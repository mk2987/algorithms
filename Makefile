UNSORTED_C 	:= g_unsorted_array.c
GEN_UNSORTED_C 	:= gen_unsorted_array.c
GEN_UNSORTED	:= /tmp/gen_unsorted
HFILES		:= utils.h main.h sort.h
CFILES 		:= ${UNSORTED_C} utils.c sort.c main.c
BIN 		:= /tmp/sort
CC 		:= clang
ifdef DEBUG
	CFLAGS	= -g
endif

.PHONY : run unsorted clean clobber

all: ${BIN}

unsorted: ${UNSORTED_C}

${UNSORTED_C}: ${GEN_UNSORTED_C} ${HFILES}
	${CC} ${CFLAGS} ${GEN_UNSORTED_C} -o ${GEN_UNSORTED}
	${GEN_UNSORTED}

${BIN}: ${CFILES} ${HFILES}
	${CC} ${CFLAGS} ${CFILES} -o $@

run: ${BIN}
	${BIN}

clean clobber:
	rm -rf ${BIN} ${GEN_UNSORTED}

