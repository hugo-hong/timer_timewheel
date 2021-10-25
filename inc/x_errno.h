/*********************************************************************************
   Copyright (C)
   Written 2020 by hugo（yongguang hong） <hugo.08@163.com>
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License version 2 as
   published by the Free Software Foundation;
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.
   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY
   CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES
   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS,
   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS
   SOFTWARE IS DISCLAIMED.
*********************************************************************************/
#ifndef __X_ERRNO_H_
#define __X_ERRNO_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * POSIX Error codes
 */
#define X_ESUCCESS      0	/* No err */
#define X_EPERM         1	/* Not owner */
#define X_ENOENT        2	/* No such file or directory */
#define X_ESRCH         3	/* No such context */
#define X_EINTR         4	/* Interrupted system call */
#define X_EIO           5	/* I/O error */
#define X_ENXIO         6	/* No such device or address */
#define X_E2BIG         7	/* Arg list too long */
#define X_ENOEXEC       8  /* Exec format error */
#define X_EBADF         9	/* Bad file number */
#define X_ECHILD        10 /* No children */
#define X_EAGAIN        11 /* No more contexts */
#define X_ENOMEM        12 /* Not enough core */
#define X_EACCES        13 /* Permission denied */
#define X_EFAULT        14 /* Bad address */
#define X_ENOTEMPTY     15 /* Directory not empty */
#define X_EBUSY         16	/* Mount device busy */
#define X_EEXIST        17 /* File exists */
#define X_EXDEV         18	/* Cross-device link */
#define X_ENODEV        19 /* No such device */
#define X_ENOTDIR       20 /* Not a directory */
#define X_EISDIR        21 /* Is a directory */
#define X_EINVAL        22 /* Invalid argument */
#define X_ENFILE        23 /* File table overflow */
#define X_EMFILE        24 /* Too many open files */
#define X_ENOTTY        25 /* Not a typewriter */
#define X_ENAMETOOLONG  26 /* File name too long */
#define X_EFBIG         27	/* File too large */
#define X_ENOSPC        28 /* No space left on device */
#define X_ESPIPE        29 /* Illegal seek */
#define X_EROFS         30	/* Read-only file system */
#define X_EMLINK        31 /* Too many links */
#define X_EPIPE         32	/* Broken pipe */
#define X_EDEADLK       33 /* Resource deadlock avoided */
#define X_ENOLCK        34 /* No locks available */
#define X_ENOTSUP       35 /* Unsupported value */
#define X_EMSGSIZE      36 /* Message size */

/* ANSI math software */
#define X_EDOM          37 /* Argument too large */
#define X_ERANGE        38 /* Result too large */

/* ipc/network software */

/* argument errors */
#define X_EDESTADDRREQ     40 /* Destination address required */
#define X_EPROTOTYPE       41 /* Protocol wrong type for socket */
#define X_ENOPROTOOPT      42 /* Protocol not available */
#define X_EPROTONOSUPPORT  43 /* Protocol not supported */
#define X_ESOCKTNOSUPPORT  44 /* Socket type not supported */
#define X_EOPNOTSUPP       45 /* Operation not supported on socket */
#define X_EPFNOSUPPORT     46 /* Protocol family not supported */
#define X_EAFNOSUPPORT     47 /* Addr family not supported */
#define X_EADDRINUSE       48 /* Address already in use */
#define X_EADDRNOTAVAIL    49 /* Can't assign requested address */
#define X_ENOTSOCK         50	/* Socket operation on non-socket */

/* operational errors */
#define X_ENETUNREACH      51 /* Network is unreachable */
#define X_ENETRESET        52 /* Network dropped connection on reset */
#define X_ECONNABORTED     53 /* Software caused connection abort */
#define X_ECONNRESET       54 /* Connection reset by peer */
#define X_ENOBUFS          55 /* No buffer space available */
#define X_EISCONN          56 /* Socket is already connected */
#define X_ENOTCONN         57 /* Socket is not connected */
#define X_ESHUTDOWN        58 /* Can't send after socket shutdown */
#define X_ETOOMANYREFS     59 /* Too many references: can't splice */
#define X_ETIMEDOUT        60 /* Connection timed out */
#define X_ECONNREFUSED     61 /* Connection refused */
#define X_ENETDOWN         62 /* Network is down */
#define X_ETXTBSY          63 /* Text file busy */
#define X_ELOOP            64	/* Too many levels of symbolic links */
#define X_EHOSTUNREACH     65 /* No route to host */
#define X_ENOTBLK          66 /* Block device required */
#define X_EHOSTDOWN        67 /* Host is down */

/* non-blocking and interrupt i/o */
#define X_EINPROGRESS      68 /* Operation now in progress */
#define X_EALREADY         69 /* Operation already in progress */
#define X_EWOULDBLOCK      70 /* Operation would block */

#define X_ENOSYS           71 /* Function not implemented */

/* aio errors (should be under posix) */
#define X_ECANCELED        72 /* Operation canceled */

#define X_ERRMAX           81

/* specific STREAMS errno values */

#define X_ENOSR            74 /* Insufficient memory */
#define X_ENOSTR           75 /* STREAMS device required */
#define X_EPROTO           76 /* Generic STREAMS error */
#define X_EBADMSG          77 /* Invalid STREAMS message */
#define X_ENODATA          78 /* Missing expected message data */
#define X_ETIME            79 /* STREAMS timeout occurred */
#define X_ENOMSG           80 /* Unexpected message type */

#define X_EILSEQ           138 /* Illegal byte sequence */


#ifdef __cplusplus
}
#endif

#endif //__X_ERRNO_H_
