#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/file.h>
#include <sys/ioctl.h>
#include<linux/version.h>
#ifdef __sparc__
#include <asm/param.h>
#endif


static int valid_rates[] = { 300, 267, 240, 218, 200, 185, 171, 160, 150,
                                   133, 120, 109, 100, 92, 86, 80, 75, 67,
                                   60, 55, 50, 46, 43, 40, 37, 33, 30, 27,
                                   25, 23, 21, 20 };
#define RATE_COUNT (sizeof( valid_rates ) / sizeof( int ))

static int valid_delays[] = { 250, 500, 750, 1000 };
#define DELAY_COUNT (sizeof( valid_delays ) / sizeof( int ))


int main( int argc, char **argv ) {

int         value = 0x7f; 
 double      rate = 10.9;    
      int         delay = 250;
                             
      int         silent = 0;
      int         fd;
      char        data;
      int         c;
      int         i;
      extern char *optarg;

     

     for (i = 0; i < RATE_COUNT; i++)
            if (rate * 10 >= valid_rates[i]) {
                  value &= 0x60;
                  value |= i;
                  break;
            }


      for (i = 0; i < DELAY_COUNT; i++)
            if (delay <= valid_delays[i]) {
                  value &= 0x1f;
                  value |= i << 5;
                  break;
            }

      if ( (fd = open( "/dev/port", O_RDWR )) < 0) {
            perror("Cannot open /dev/port" );
            exit( 1 );
      }

      
      lseek( fd, 0x60, 0 );
      data = 0xf3;                 /* set typematic rate */
      if (write( fd, &data, 1 ) == -1) {
            perror( "write" );
            exit( 1 );
      }

      
      lseek( fd, 0x60, 0 );
      sleep( 1 );
      if (write( fd, &value, 1 ) == -1) {
            perror( "write" );
            exit( 1 );
      }

      close( fd );

      printf("Typematic Rate set to %.1f cps (delay = %d ms)\n",valid_rates[value & 0x1f] / 10.0,valid_delays[ (value & 0x60) >> 5 ] );

      return 0;
}
