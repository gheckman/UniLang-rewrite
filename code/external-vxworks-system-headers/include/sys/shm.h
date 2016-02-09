#ifndef __Ishm
#define __Ishm

#ifdef	__cplusplus
extern "C" {
#endif

struct shmid_ds {
	struct ipc_perm	shm_perm;
	int		shm_segsz;
	struct region	*shm_reg;
	pid_t		shm_lpid;
	pid_t		shm_cpid;
	ushort		shm_nattch;
	ushort		shm_cnattch;
	time_t		shm_atime;
	unsigned long	shm_ausec;
	time_t		shm_dtime;
	unsigned long	shm_dusec;
	time_t		shm_ctime;
	unsigned long	shm_cusec;
};

#define	SHMLBA	sysconf(31)

#define	SHM_R		0400
#define	SHM_W		0200
#define	SHM_RDONLY	010000
#define	SHM_RND		020000

#define SHM_LOCK	3
#define SHM_UNLOCK	4

#define	SHM_INIT	01000
#define	SHM_DEST	02000

struct	shminfo {
	int shmmax,
	    shmmin,
	    shmmni,
	    shmseg,
	    shmbrk,
	    shmall;
};

extern int shmctl(int, int, struct shmid_ds *);
extern int shmget(key_t, int, int);
extern void *shmat(int, void *, int);
extern int shmdt(void *);

#ifdef	__cplusplus
}
#endif
#endif
