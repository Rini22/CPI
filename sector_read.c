

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

struct partition
{
        unsigned char boot_flag;       
        unsigned char chs_begin[3];
        unsigned char sys_type;         
        unsigned char chs_end[3];
        unsigned char start_sector[4];
        unsigned char nr_sector[4];
};

void string_in_hex(void *in_string, int in_string_size);



void string_in_hex(void *in_string, int in_string_size)
{
        int i;
        int k = 0;




        for (i = 0; i < in_string_size; i++)
        {
                printf("%02x ", ((char *)in_string)[i]& 0xFF);
                k = k + 1;
                if (k == 16)
                {
                        printf("\n");
                        k = 0;
                }
        }
        printf("\n");
}

int main(int argc, char **argv)
{
        int /*gc = 0,*/ i = 1, nr = 0, pos = -1/*, nw = 0*/;
        int fd = 0;
        char  buf[512] ;
        struct partition *sp;
        int ret = 0;

        printf("Ok ");

        if ((fd = opendir("/sys/block/sda/sda4\\", O_RDONLY | O_SYNC)) == -1)
        {
                perror("Open");
                exit(1);
        }
        printf("fd is %d\n", fd);

        pos = lseek (fd, 0, SEEK_CUR);

        printf("Position of pointer is :%d\n", pos);
        if ((nr = read(fd, buf, sizeof(buf))) == -1)
        {
                perror("Read");
                exit(1);
        }

        ret = close(fd);
        if (ret == -1)
        {
                perror("close");
                exit(1);
        }

        
        string_in_hex(buf, 512);

        printf("Size of buf = %d - and number of bytes read are %d\n", sizeof(buf), nr);
        

}
