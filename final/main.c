#include <linux/of_device.h>
#include <linux/sysfs.h>
#include <linux/leds.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#inclufe "serial.h"

#define LED3_PATH "/sys/class/leds/beaglebone:green:usr3"
#define LDR_PATH "/sys/bus/iio/devices/iio:device0/in_voltage0_raw"

void writeLED(char filename[], char value[]){
   FILE* fp;   // create a file pointer fp
   char  fullFileName[100];  // to store the path and filename
   sprintf(fullFileName, LED3_PATH "%s", filename); // write path and filename
   fp = fopen(fullFileName, "w+"); // open file for writing
   fprintf(fp, "%s", value);  // send the value to the file
   fclose(fp);  // close the file using the file pointer
}

void removeTrigger(){
  writeLED("/trigger", "none");
}
int read_adc()
{
	int fd;
	char s_adcBuffer[3];
	int value;
	fd = open(LDR_PATH, O_RDONLY);
	if (fd < 0) {
		perror("ADC - problem opening ADC");
	}
	int status = readread(fd, &s_adcBuffer, 4);
	close(fd);
	
	// Convert the string into an integer
	s_adcBuffer[status] = '\0';
	value = atoi(s_adcBuffer);

	return value;

}

static void read_data(unsigned char byteData)
{
	static E_DataState s_dataState = WAIT_STX;
	static unsigned char s_Id = 0;
	static unsigned char buf[DATA_NUM_BYTES] = {0};
	
	switch (s_dataState) {
	case WAIT_STX:
		if(byteData == STX)
		{
			s_dataState = WAIT_DATA;
			s_Id = 0;
		}
		break;
	case WAIT_DATA:
		buf[s_Id]=byteData;
		//		printf("data[%d]: %x\n",s_Id,buf[s_Id]);
		if(s_Id==DATA_NUM_BYTES-1)
		{
			s_dataState = WAIT_ETX;
		}
		s_Id++;
		break;
	case WAIT_ETX:
		if(byteData == ETX)
		{
			s_dataState = WAIT_STX;
			//correct packet, decode it
			if(buf[0]==0xfa) {
					removeTrigger();
					writeLED("/brightness", "1");
			}
			else if(buf[0]==0xfb){
					removeTrigger();
					writeLED("/brightness", "0");
				}
				else if(buf[0]==0xfc){
						int value_adc= read_adc();
						serial_write(1,(char*) value_adc,MAX_BUF_READ);
					}
			memset(buf,0,DATA_NUM_BYTES);

		}
		else
		{
			perror("Wrong Nunchuk packet \n");
			s_dataState = WAIT_STX;
		}
		break;
	default:
		break;
	}
}
int main(int argc, char** agrv)
{	
	unsigned char buf[MAX_BUF_READ]={0};
	serial_open(1,115200, 1,0,1)
		while(1)
	{
		int n = serial_read(1,buf,MAX_BUF_READ);
		if (n > 0)
		{
			for(int i =0; i<n;i++)
			{
				read_data(buf[i]);
			}
		}
	}
	return 0;
}
