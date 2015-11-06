# MJSoft's ADSP Utilities
# (c) 1996 Martin Mares, <mj@k332.feld.cvut.cz>

OPT=-fomit-frame-pointer -O2
CFLAGS=$(OPT) -Wall -Wno-parentheses
LDFLAGS=-s

AOBJS=main.o lex.yy.o syn.tab.o kwds.o lists.o expr.o mem.o dump.o

all: adspc as2181 mkrom

as2181: $(AOBJS)
	$(CC) $(LDFLAGS) $(AOBJS) -o as2181

main.o: main.c glob.h as2181.h
lex.yy.o: lex.yy.c glob.h as2181.h syn.tab.h
syn.tab.o: syn.tab.c glob.h as2181.h syn.tab.h
kwds.o: kwds.c glob.h as2181.h syn.tab.h
	$(CC) $(CFLAGS) -c -Wno-char-subscripts kwds.c -o kwds.o
lists.o: lists.c glob.h as2181.h
expr.o: expr.c glob.h as2181.h
mem.o: mem.c glob.h as2181.h
dump.o: dump.c glob.h as2181.h

syn.tab.c syn.tab.h: syn.y
	bison -dv syn.y

lex.yy.c: lex.l
	flex -s8i lex.l

kwds.c: kwds.k
	gperf -aCgptT -H kwd_hash -N is_kwd -k 1,2,\$$ <kwds.k >kwds.c

adspc: adspc.o
	$(CC) $(CFLAGS) $(LDFLAGS) adspc.o -o adspc

adspc.o: adspc.c glob.h

mkrom: mkrom.o
	$(CC) $(CFLAGS) $(LDFLAGS) mkrom.o -o mkrom

mkrom.o: mkrom.c glob.h

tags:
	etags *.[ch]

clean:
	rm -f *.o adspc as2181 mkrom *~ \#*\# TAGS lex.yy.c syn.{tab.[ch],output} kwds.c

backup: clean
	tar czvvf adsp`date +%d%m%y`.tgz .
	flop 0
	mv *.tgz /fd0
	ls -l /fd0
	unflop
