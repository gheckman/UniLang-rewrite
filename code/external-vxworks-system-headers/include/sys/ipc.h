/*
 *	Copyright 1985 Dataindustrier AB
 *
 *	IPC access structure
 */

#define	IPC_ALLOC	0100000		/* Entry currently allocated. */

#define IPC_CREAT	0001000		/* Create entry if key doesn't exist. */
#define IPC_EXCL	0002000		/* Fail if key exist and create set. */
#define IPC_NOWAIT	0004000		/* Error if request must wait. */

#define IPC_PRIVATE	(key_t)0	/* Private key. */

#define IPC_RMID	0		/* Remove identifier. */
#define IPC_SET		1		/* Set options. */
#define IPC_STAT	2		/* Get options. */

struct	ipc_perm {
#ifdef __mot68
	ushort	uid;			/* Owners user id. */
	ushort	gid;			/* Owners group id. */
	ushort	cuid;			/* Creator's user id. */
	ushort	cgid;			/* Creator's group id. */
	ushort	mode;			/* Access mode. */
#else
	uid_t	uid;			/* Owners user id. */
	gid_t	gid;			/* Owners group id. */
	uid_t	cuid;			/* Creator's user id. */
	gid_t	cgid;			/* Creator's group id. */
	mode_t	mode;			/* Access mode. */
#endif
#if defined(m88k) || defined(__m88k)
	char	ipc_pad[2];
#endif
	ushort	seq;			/* Slot usage sequence number. */
#ifdef __ALIGNBY2
	ushort	dummy1;
#endif
	key_t	key;			/* Key. */
};
