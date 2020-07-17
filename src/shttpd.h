/**
 * Copyright (c) 2004-2008 Sergey Lyubka <valenok@gmail.com>
 * All rights reserved
 *
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Sergey Lyubka wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 *
 * $Id: shttpd.h,v 1.18 2008/08/23 08:34:50 drozd Exp $
 */
#ifndef SHTTPD_H_INCLUDED
#define SHTTPD_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

typedef struct shttpd_ctx_t * shttpd_ctx;
typedef struct shttpd_arg_t * shttpd_arg;


#define SHTTPD_END_OF_OUTPUT    1   /* No more data do send          */
#define SHTTPD_CONNECTION_ERROR 2   /* Server closed the connection  */
#define SHTTPD_MORE_POST_DATA   4   /* arg->in has incomplete data   */
#define SHTTPD_POST_BUFFER_FULL 8   /* arg->in has max data          */
#define SHTTPD_SSI_EVAL_TRUE    16  /* SSI eval callback must set it */
#define SHTTPD_SUSPEND          32  /* User wants to suspend output  */


typedef enum {
    SHOPT_ROOT,
    SHOPT_INDEX_FILES,
    SHOPT_PORTS,
    SHOPT_DIR_LIST,
    SHOPT_CGI_EXTS,
    SHOPT_CGI_INTERP,
    SHOPT_CGI_ENV,
    SHOPT_SSI_EXTS,
    SHOPT_AUTH_REALM,
    SHOPT_AUTH_GPASSWD,
    SHOPT_AUTH_PUT,
    SHOPT_ACCESS_LOG,
    SHOPT_ERROR_LOG,
    SHOPT_MIME_TYPES,
    SHOPT_SSL_CERT,
    SHOPT_ALIASES,
    SHOPT_ACL,
    SHOPT_INETD,
    SHOPT_UID,
    SHOPT_CFG_URI,
    SHOPT_PROTECT,
    SHOPT_SERVICE,
    SHOPT_HIDE,
    SHOPT_THREADS,
    SHOPTIONS_NUM
} shttpd_opt_t;


/**
 * shttpd_arg_t
 *   structure is passed to the user callback function
 */
struct shttpd_arg_t
{
    void *priv;              /* Private! Do not touch!      */
    void *state;             /* User state                  */
    void *user_data;         /* Data from register_uri()    */

    struct {
        char *buf;           /* Buffer pointer              */
        int   len;           /* Size of a buffer            */
        int   num_bytes;     /* Bytes processed by callback */
    } in;                    /* Input is here, POST data    */

    struct {
        char *buf;           /* Buffer pointer              */
        int   len;           /* Size of a buffer            */
        int   num_bytes;     /* Bytes processed by callback */
    } out;                   /* Output goes here            */

    unsigned int flags;
};


/*
 * User callback function
 *   Called when certain registered URLs have been requested.
 *   These are the requirements to the callback function:
 *
 * 1. It must copy data into 'out.buf' buffer, not more than 'out.len' bytes,
 *     and record how many bytes are copied, into 'out.num_bytes'
 * 2. It must not call any blocking functions
 * 3. It must set SHTTPD_END_OF_OUTPUT flag when there is no more data to send
 * 4. For POST requests, it must process the incoming data (in.buf) of length
 *     'in.len', and set 'in.num_bytes', which is how many bytes of POST
 *     data was processed and can be discarded by SHTTPD.
 * 5. If callback allocates arg->state, to keep state, it must deallocate it
 *     at the end of coonection SHTTPD_CONNECTION_ERROR or SHTTPD_END_OF_OUTPUT
 * 6. If callback function wants to suspend until some event, it must store
 *     arg->priv pointer elsewhere, set SHTTPD_SUSPEND flag and return. When
 *     the event happens, user code should call shttpd_wakeup(priv).
 *    It is safe to call shttpd_wakeup() from any thread. User code must
 *     not call shttpd_wakeup once the connection is closed.
 */
typedef void (*shttpd_callback_t)(shttpd_arg);


/**
 * shttpd_init
 *   Initialize shttpd context
 */
shttpd_ctx shttpd_init (int argc, char *argv[]);


/**
 * shttpd_set_option
 *   Set new value for option
 */
int shttpd_set_option (shttpd_ctx ctx, const char *optname, const char *optval);


/**
 * shttpd_get_option
 *   Get value of option
 */
const char * shttpd_get_option (shttpd_ctx ctx, shttpd_opt_t opt);


/**
 * shttpd_fini
 *   Dealocate the context, close all connections
 */
void shttpd_fini (shttpd_ctx ctx);


/**
 * shttpd_register_uri
 *   Setup the callback function for specified URL
 */
void shttpd_register_uri (shttpd_ctx ctx, const char *uri, shttpd_callback_t callback, void *const user_data);


/**
 * shttpd_poll
 *   Do connections processing
 */
void shttpd_poll (shttpd_ctx ctx, int milliseconds);


/**
 * shttpd_version
 *   return string with SHTTPD version
 */
const char *shttpd_version (void);


/**
 * shttpd_get_var
 *   Fetch POST/GET variable value by name. Return value len
 */
int shttpd_get_var (const char *var, const char *buf, int buf_len, char *value, int value_len);


/**
 * shttpd_get_header
 *   return value of the specified HTTP header
 */
const char *shttpd_get_header (shttpd_arg arg, const char *header_name);


/**
 * shttpd_get_env
 *   return values for the following pseudo-variables:
 *      REQUEST_METHOD
 *      REQUEST_URI
 *      REMOTE_USER
 *      REMOTE_ADDR
 */
const char *shttpd_get_env (shttpd_arg arg, const char *name);


void shttpd_get_http_version (shttpd_arg arg, unsigned long *major, unsigned long *minor);


/**
 * shttpd_printf
 *   helper function to output data
 */
size_t shttpd_printf (shttpd_arg arg, const char *fmt, ...);


/**
 * shttpd_handle_error
 *   Register custom HTTP error handler
 */
void shttpd_handle_error (shttpd_ctx ctx, int status, shttpd_callback_t func, void *const data);


void shttpd_register_ssi_func (shttpd_ctx ctx, const char *name, shttpd_callback_t func, void *const user_data);


/**
 * shttpd_wakeup
 *   Clear SHTTPD_SUSPEND state for the connection
 */
void shttpd_wakeup (const void *priv);


int shttpd_join (shttpd_ctx ctx, fd_set *, fd_set *, int *max_fd);


int shttpd_socketpair (int sp[2]);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SHTTPD_H_INCLUDED */
