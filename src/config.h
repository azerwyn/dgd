/* these may be changed, but sizeof(uindex) <= sizeof(int) */
typedef unsigned short uindex;
# define UINDEX_MAX	USHRT_MAX

typedef uindex sector;
# define SW_UNUSED	UINDEX_MAX


/*
 * Gamedriver configuration.  Hash table sizes should be powers of two.
 */

/* general */
# define BUF_SIZE	FS_BLOCK_SIZE	/* I/O buffer size */
# define MAX_LINE_SIZE	1024	/* max. line size in ed and lex (power of 2) */
# define STRINGSZ	256	/* general (internal) string size */
# define STRMAPHASHSZ	20	/* # characters to hash of map string indices */
# define STRMERGETABSZ	1024	/* general string merge table size */
# define STRMERGEHASHSZ	20	/* # characters in merge strings to hash */
# define ARRMERGETABSZ	1024	/* general array merge table size */
# define OBJHASHSZ	256	/* # characters in object names to hash */
# define COPATCHHTABSZ	64	/* callout patch hash table size */
# define OBJPATCHHTABSZ	256	/* object patch hash table size */


/* interpreter */
# define MIN_STACK	3	/* minimal stack, # arguments in driver calls */
# define EXTRA_STACK	32	/* extra space in stack frames */

/* parser */
# define MAX_AUTOMSZ	6	/* DFA/PDA storage size, in strings */
# define PARSERULTABSZ	256	/* size of parse rule hash table */
# define PARSERULHASHSZ	10	/* # characters in parse rule symbols to hash */

/* editor */
# define NR_EDBUFS	3	/* # buffers in editor cache (>= 3) */
/*# define TMPFILE_SIZE	2097152 */ /* max. editor tmpfile size */

/* lexical scanner */
# define MACTABSZ	1024	/* macro hash table size */
# define MACHASHSZ	10	/* # characters in macros to hash */

/* compiler */
# define YYMAXDEPTH	500	/* parser stack size */
# define MAX_ERRORS	5	/* max. number of errors during compilation */
# define MAX_LOCALS	127	/* max. number of parameters + local vars */
# define OMERGETABSZ	128	/* inherit object merge table size */
# define VFMERGETABSZ	256	/* variable/function merge table sizes */
# define VFMERGEHASHSZ	10	/* # characters in function/variables to hash */
# define NTMPVAL	32	/* # of temporary values for LPC->C code */


extern bool		conf_init	P((char*, char*, uindex*));
extern char	       *conf_base_dir	P((void));
extern char	       *conf_driver	P((void));
extern int		conf_typechecking P((void));
extern unsigned short	conf_array_size	P((void));

extern void   conf_dump		P((void));
extern Uint   conf_dsize	P((char*));
extern Uint   conf_dconv	P((char*, char*, char*, Uint));
extern void   conf_dread	P((int, char*, char*, Uint));

extern bool   conf_statusi	P((frame*, Int, value*));
extern array *conf_status	P((frame*));
extern bool   conf_objecti	P((dataspace*, object*, Int, value*));
extern array *conf_object	P((dataspace*, object*));
