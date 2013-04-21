UNSORTED_C 	:= g_unsorted_array.c
GEN_UNSORTED_C 	:= gen_unsorted_array.c
GEN_UNSORTED	:= /tmp/gen_unsorted
HFILES		:= utils.h
CFILES 		:= ${UNSORTED_C} utils.c sort.c
BIN 		:= /tmp/sort
CC 		:= clang

.PHONY : unsorted clean clobber

all: ${BIN}

unsorted: ${UNSORTED_C}

${UNSORTED_C}: ${GEN_UNSORTED_C}
	${CC} ${GEN_UNSORTED_C} -o ${GEN_UNSORTED}
	${GEN_UNSORTED}

${BIN}: ${CFILES} ${HFILES}
	${CC} ${CFILES} -o $@

clean clobber:
	rm -rf ${BIN} ${GEN_UNSORTED}

