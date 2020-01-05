/*
 * This file is part of DGD, https://github.com/dworkin/dgd
 * Copyright (C) 1993-2010 Dworkin B.V.
 * Copyright (C) 2010-2020 DGD Authors (see the commit log for details)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* these may be changed, but sizeof(type) <= sizeof(int) */
typedef unsigned short uindex;
# define UINDEX_MAX	USHRT_MAX

typedef uindex Sector;
# define SW_UNUSED	UINDEX_MAX

/* sizeof(ssizet) <= sizeof(uindex) */
typedef unsigned short ssizet;
# define SSIZET_MAX	USHRT_MAX

/* eindex can be anything */
typedef unsigned char eindex;
# define EINDEX_MAX	UCHAR_MAX
# define EINDEX(e)	UCHAR(e)

typedef unsigned short kfindex;
# define KFTAB_SIZE	1024
# define KFCRYPT_SIZE	128


/*
 * Gamedriver configuration.  Hash table sizes should be powers of two.
 */

/* general */
# define BUF_SIZE	FS_BLOCK_SIZE	/* I/O buffer size */
# define MAX_LINE_SIZE	4096	/* max. line size in ed and lex (power of 2) */
# define STRINGSZ	256	/* general (internal) string size */
# define STRMAPHASHSZ	20	/* # characters to hash of map string indices */
# define STRMERGETABSZ	1024	/* general string merge table size */
# define STRMERGEHASHSZ	20	/* # characters in merge strings to hash */
# define ARRMERGETABSZ	1024	/* general array merge table size */
# define OBJHASHSZ	256	/* # characters in object names to hash */
# define COPATCHHTABSZ	1024	/* callout patch hash table size */
# define OBJPATCHHTABSZ	256	/* object patch hash table size */
# define CMPLIMIT	2048	/* compress strings if >= CMPLIMIT */
# define SWAPCHUNKSZ	10	/* # objects reconstructed in main loop */

/* comm */
# define INBUF_SIZE	2048	/* telnet input buffer size */
# define OUTBUF_SIZE	8192	/* telnet output buffer size */
# define BINBUF_SIZE	8192	/* binary/UDP input buffer size */
# define UDPHASHSZ	10	/* # characters in UDP challenge to hash */

/* swap */
# define SWAPCHUNK	(128 * 1024 * 1024)

/* interpreter */
# define MIN_STACK	5	/* minimal stack, # arguments in driver calls */
# define EXTRA_STACK	32	/* extra space in stack frames */
# define MAX_STRLEN	SSIZET_MAX	/* max string length, >= 65535 */
# define INHASHSZ	4096	/* instanceof hashtable size */

/* parser */
# define MAX_AUTOMSZ	6	/* DFA/PDA storage size, in strings */
# define PARSERULTABSZ	256	/* size of parse rule hash table */
# define PARSERULHASHSZ	10	/* # characters in parse rule symbols to hash */

/* editor */
# define NR_EDBUFS	3	/* # buffers in editor cache (>= 3) */
/*# define TMPFILE_SIZE	2097152 */ /* max. editor tmpfile size */

/* lexical scanner */
# define INCLUDEDEPTH	64	/* maximum include depth */
# define MACTABSZ	16384	/* macro hash table size */
# define MACHASHSZ	10	/* # characters in macros to hash */

/* compiler */
# define YYMAXDEPTH	500	/* parser stack size */
# define MAX_ERRORS	5	/* max. number of errors during compilation */
# define MAX_LOCALS	127	/* max. number of parameters + local vars */
# define OMERGETABSZ	512	/* inherit object merge table size */
# define VFMERGETABSZ	2048	/* variable/function merge table sizes */
# define VFMERGEHASHSZ	10	/* # characters in function/variables to hash */
# define NTMPVAL	32	/* # of temporary values for LPC->C code */

/* builtin type prefix */
# define BIPREFIX	"builtin/"
# define BIPREFIXLEN	8


class SnapshotInfo {
public:
    char valid;
    char version;
    char model;
    char typecheck;
    char secsize0;
    char secsize1;
    char s0;			/* short, msb */
    char s1;			/* short, lsb */
    char i0;			/* Int, msb */
    char i1;
    char i2;
    char i3;			/* Int, lsb */
    char l0;
    char l1;
    char l2;
    char l3;
    char l4;
    char l5;
    char l6;
    char l7;
    char utsize;		/* sizeof(uindex) + sizeof(ssizet) */
    char desize;		/* sizeof(sector) + sizeof(eindex) */
    char psize;			/* sizeof(char*), upper nibble reserved */
    char calign;		/* align(char) */
    char salign;		/* align(short) */
    char ialign;		/* align(Int) */
    char palign;		/* align(char*) */
    char zalign;		/* align(struct) */
    char start0;
    char start1;
    char start2;
    char start3;
    char elapsed0;
    char elapsed1;
    char elapsed2;
    char elapsed3;
    char zero1;			/* reserved (0) */
    char zero2;			/* reserved (0) */
    char zero3;			/* reserved (0) */
    char zero4;			/* reserved (0) */
    char dflags;		/* flags */
    char zero5;			/* reserved (0) */
    char vstr[18];
    char offset0;
    char offset1;
    char offset2;
    char offset3;

    unsigned int restore(int fd);
};

class Config {
public:
    static void modFinish();
    static bool init(char *configfile, char *snapshot, char *snapshot2,
		     char *module, Sector *fragment);
    static char *baseDir();
    static char	*driver();
    static char	**hotbootExec();
    static int typechecking();
    static unsigned short arraySize();
    static bool attach(int port);

    static void dump(bool incr, bool boot);
    static Uint dsize(const char *layout);
    static Uint dconv(char *buf, char *rbuf, const char *layout, Uint n);
    static void dread(int fd, char *buf, const char *layout, Uint n);

    static bool statusi(Frame *f, Int idx, Value *v);
    static Array *status(Frame *f);
    static bool objecti(Dataspace *data, Object *obj, Int idx, Value *v);
    static Array *object(Dataspace *data, Object *obj);

    const char *name;	/* name of the option */
    short type;		/* option type */
    bool resolv;	/* TRUE if path name must be resolved */
    bool set;		/* TRUE if option is set */
    Uint low, high;	/* lower and higher bound, for numeric values */
    union {
	long num;	/* numeric value */
	char *str;	/* string value */
    };

private:
    static void dumpinit();
    static bool restore(int fd, int fd2);
    static void err(const char *err);
    static bool config();
    static void fdlist();
    static bool open(char *file);
    static void puts(const char *str);
    static bool close();
    static bool includes();
    static void putval(Value *v, size_t n);
};

/* utility functions */
extern Int strtoint		(char**);
