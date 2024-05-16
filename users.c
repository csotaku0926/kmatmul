#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <time.h>
#include "matmul.h"

#define ERR_QUIT(m) {perror(m); exit(0);}
#define SHOW_RESULT 0

void fill_matrix(int matrix[MAT_SIZE][MAT_SIZE])
{
    for (int i=0; i<MAT_SIZE; i++)
        for (int j=0; j<MAT_SIZE; j++)
            matrix[i][j] = j+1;
}

int matrixA[MAT_SIZE][MAT_SIZE];
int matrixB[MAT_SIZE][MAT_SIZE];
int result[MAT_SIZE][MAT_SIZE];

int main(void)
{
    int fd = open("/proc/matmul", O_RDWR);
    if (fd < 0) ERR_QUIT("open /proc/matmul");

    fill_matrix(matrixA);
    fill_matrix(matrixB);

    /* set matirx A, B */
    if (ioctl(fd, MATRIX_IOCTL_SET_A, matrixA) ||
        ioctl(fd, MATRIX_IOCTL_SET_B, matrixB) ) {
            close(fd);
            ERR_QUIT("ioctl matrix A or B");
        }

    /* compute in kernel */
    if (ioctl(fd, MATRIX_IOCTL_COMPUTE)) {
        close(fd);
        ERR_QUIT("ioctl compute");
    }

    /* Read result from kernel */
    ssize_t nbyte_read = read(fd, result, sizeof(result));
    if (nbyte_read != sizeof(result)) {
        close(fd);
        printf("expect %ld ,got %ld bytes\n", sizeof(result), nbyte_read);
        ERR_QUIT("fail to read result from kernel");
    }
    
    /* Display result */
#if SHOW_RESULT
    puts("Result matrix:");
    for (int i=0; i<MAT_SIZE; i++){
        for (int j=0; j<MAT_SIZE; j++)
            printf("%d ", result[i][j]);
        puts("");
    }
#endif
    close(fd);
    return 0;
}
