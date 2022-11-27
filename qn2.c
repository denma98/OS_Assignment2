#include <stdio.h>
#include <sys/syscall.h>
#include <linux/kernel.h>
#include <unistd.h>
#include <errno.h>

#define ONED_COPY_SYSCALL 451

int main()
{
    double src_arr[5][5] = {{1,2,3,4,5}, {1,2,3,4,5}, {1,2,3,4,5}, {1,2,3,4,5}, {1,2,3,4,5}};
    double dest_arr[5][5];

    double sys_call_status;

    sys_call_status = syscall(ONED_COPY_SYSCALL, src_arr, dest_arr, 25);

    if (sys_call_status == 0)
    {
        printf("Message : No Error in copying \n");
        // check_equal(src_arr, dest_arr, 2, 2);
    }
    else if (sys_call_status == -1)
    {
        printf("Message : Error in copying \n");
    }

    check_equal(src_arr, dest_arr, 25);

    for (int i = 0; i < 5; i++)
    {

        for (int j = 0; j <5; j++)
        {
            printf("%f", dest_arr[i][j]);
        }
        printf("\n");
    }

    return 0;
}
