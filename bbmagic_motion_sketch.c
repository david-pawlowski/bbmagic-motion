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
        if (data_length > 0)
        {
            switch (bbm_buf[BBMAGIC_DEVICE_TYPE])
            {
            case BBMAGIC_M_MOTION:

                timestamp = time(NULL);
                loctime = localtime(&timestamp);

                strftime(time_buffer, TIME_BUF_SIZE, "%X", loctime);
                printf("\n %s ", time_buffer);

                if (bbm_buf[BBM_MOTION_FLAGS] & BBM_MOTION_ALERT_MASK)
                {
                    printf(" OBJECT DETECTED !!");
                }
                printf("\n BBM_MOTION addr: ");
                //- BT address - 6 B
                for (i = 0; i < BBM_BT_ADDR_SIZE; i++)
                    printf("%0.2X", bbm_buf[BBMAGIC_DEVICE_ADDR_5 + i]);
                //- vcc
                vcc_f = (float)bbm_buf[BBM_MOTION_V_SUP];
                vcc_f /= BBMAGIC_VCC_DIVIDER; //-calculate power suuply voltage
                printf(" < %0.2fV", vcc_f);
                printf(" | %ddBm", (signed char)bbm_buf[BBMAGIC_DEVICE_RSSI]); //-RSSI
                //-firm version
                printf(" | firm.%0.2X.%0.2X", bbm_buf[BBM_MOTION_FIRM_1], bbm_buf[BBM_MOTION_FIRM_0]);
                printf(" >\n");

                //- working time
                i = bbm_buf[BBM_MOTION_WORKTIME_3];
                i <<= 8;
                i |= bbm_buf[BBM_MOTION_WORKTIME_2];
                i <<= 8;
                i |= bbm_buf[BBM_MOTION_WORKTIME_1];
                i <<= 8;
                i |= bbm_buf[BBM_MOTION_WORKTIME_0];
                printf(" %4ds", i);

                //-Light. chip temperature, BBM_MOTION_MOTION_ALERTS
                printf(" L=%d chT=%d*C F=%0.2X", bbm_buf[BBM_MOTION_LIGHT], (signed char)bbm_buf[BBM_MOTION_CHIP_TEMP], bbm_buf[BBM_MOTION_FLAGS]);

                //-adc data
                adc1 = bbm_buf[BBM_MOTION_ADC_1_MSB];
                adc1 *= 256;
                adc1 += bbm_buf[BBM_MOTION_ADC_1_LSB];
                adc2 = bbm_buf[BBM_MOTION_ADC_2_MSB];
                adc2 *= 256;
                adc2 += bbm_buf[BBM_MOTION_ADC_2_LSB];
                printf(" ADC1=%dmV ADC2=%dmV", adc1, adc2);
                fprintf(fptr, "\n %s Object detected\n power supply voltage: %0.2fV \n", time_buffer, vcc_f);

                break;

            default:
                printf("BBM_UNKNOWN_");
                //-BT address - 6 B
                for (i = 0; i < BBM_BT_ADDR_SIZE; i++)
                    printf("%0.2X", bbm_buf[BBMAGIC_DEVICE_ADDR_5 + i]);

                printf(" BBM_TYPE=%0.2X", bbm_buf[BBMAGIC_DEVICE_TYPE]);
                break;
            };
            printf("\n");
        }
        usleep(100);
    } while (data_length != -1);
    fclose(fptr);
    bbm_bt_close();

    exit(0);
}
