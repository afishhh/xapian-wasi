#include <assert.h>

# define EAI_BADFLAGS	  -1	/* Invalid value for `ai_flags' field.  */
# define EAI_NONAME	  -2	/* NAME or SERVICE is unknown.  */
# define EAI_AGAIN	  -3	/* Temporary failure in name resolution.  */
# define EAI_FAIL	  -4	/* Non-recoverable failure in name res.  */
# define EAI_FAMILY	  -6	/* `ai_family' not supported.  */
# define EAI_SOCKTYPE	  -7	/* `ai_socktype' not supported.  */
# define EAI_SERVICE	  -8	/* SERVICE not supported for `ai_socktype'.  */
# define EAI_MEMORY	  -10	/* Memory allocation failure.  */
# define EAI_SYSTEM	  -11	/* System error returned in `errno'.  */
# define EAI_OVERFLOW	  -12	/* Argument buffer overflow.  */
# ifdef __USE_GNU
#  define EAI_NODATA	  -5	/* No address associated with NAME.  */
#  define EAI_ADDRFAMILY  -9	/* Address family for NAME not supported.  */
#  define EAI_INPROGRESS  -100	/* Processing request in progress.  */
#  define EAI_CANCELED	  -101	/* Request canceled.  */
#  define EAI_NOTCANCELED -102	/* Request not canceled.  */
#  define EAI_ALLDONE	  -103	/* All requests done.  */
#  define EAI_INTR	  -104	/* Interrupted by a signal.  */
#  define EAI_IDN_ENCODE  -105	/* IDN encoding failed.  */
# endif

static const char *gai_strerror (int __ecode) {
	assert(false);
}

static int getaddrinfo (const char *__restrict name,
			const char *__restrict service,
			const struct addrinfo *__restrict req,
				 struct addrinfo **__restrict pai) {
	assert(false);
}

static void freeaddrinfo (struct addrinfo *__ai) {
	assert(false);
}
