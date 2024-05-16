#include <linux/version.h>

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 6, 0)
#define HAVE_PROC_OPS
#endif

/* total size of matrix buffer */
#define MAT_SIZE 1000

/* submatrix size for concurrent computation */
#define SUBMAT_SIZE 10

#define MATRIX_IOCTL_MAGIC 'm'
#define MATRIX_IOCTL_SET_A _IOW(MATRIX_IOCTL_MAGIC, 1, int)
#define MATRIX_IOCTL_SET_B _IOW(MATRIX_IOCTL_MAGIC, 2, int)
#define MATRIX_IOCTL_COMPUTE _IO(MATRIX_IOCTL_MAGIC, 3)

/**
 * TODO:
 * Is there a way to introduce AVX/SSE in to Linux kernel ?
 *
 * #ifdef __ARM_NEON
 * #include <arm_neon.h>
 * #endif
 * #ifdef __x86_64__
 * #include <immintrin.h>
 * #endif 
 * 
*/