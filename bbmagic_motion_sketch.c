#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "bbmagic_lib.h"

#define TIME_BUF_SIZE 50

int main(void)
{
    unsigned char bbm_buf[BBLIB_FRAME_SIZE];
    int i, adc1, adc2, data_length;
    float vcc_f;
    FILE *fptr;
    time_t timestamp;
    struct tm *loctime;
    char time_buffer[TIME_BUF_SIZE];

    fptr = fopen("logs.txt", "a");

    i = bbm_bt_open(17);
    if (i)
        exit(2);

    do
    {
        data_length = bbm_bt_read(bbm_buf);
        if (data_length > 0 && bbm_buf[BBMAGIC_DEVICE_TYPE] == BBMAGIC_M_MOTION) {
            timestamp = time(NULL);
            loctime = localtime(&timestamp);

            strftime(time_buffer, TIME_BUF_SIZE, "%X", loctime);
            printf("\n %s ", time_buffer);

            if (bbm_buf[BBM_MOTION_FLAGS] & BBM_MOTION_ALERT_MASK)
            {
                printf(" OBJECT DETECTED !!");
            }
            fprintf(fptr, "\n %s Object detected\n", time_buffer);
            usleep(100);
        }
    } while (data_length != -1);

    fclose(fptr);
    bbm_bt_close();

    exit(0);
}
