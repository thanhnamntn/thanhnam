#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<termios.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#inclufe "serial.h"

typedef enum
{
	WAIT_STX,
	WAIT_DATA,
	WAIT_ETX
}E_DataState;

const char* uart1="/dev/ttyO1";
static int s_fd_uart1;

static int uart_config(int fd, long baudrate, int data_bits, int parity, int stop_bits)
{
	struct termios  UART_TypeDef ;

	UART_TypeDef.c_iflag &= ~(IGNBRK | BRKINT | ICRNL | INLCR |
			PARMRK | INPCK | ISTRIP | IXON);
	UART_TypeDef.c_oflag = 0;
	UART_TypeDef.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);
	UART_TypeDef.c_cflag &= ~(CSIZE);
	UART_TypeDef.c_cflag &= ~(PARENB | PARODD); 
	UART_TypeDef.c_cflag |= parity;	//
	UART_TypeDef.c_cflag |= data_bits;	//CS8;
	UART_TypeDef.c_cc[VMIN]  = 1;
	UART_TypeDef.c_cc[VTIME] = 0;
	tty.c_cflag &= ~stop_bits;	//CSTOPB;
	tty.c_cflag &= ~CRTSCTS;

	if (cfsetispeed (&UART_TypeDef,baudrate) < 0 || cfsetospeed (&UART_TypeDef, baudrate) < 0)
	{
		printf ("-E- cannot setg baudrate \r\n");
		return -1;
	}

	if (tcsetattr (fd, TCSAFLUSH, &UART_TypeDef) < 0)
	{
		printf ("-E- config failed \r\n");
		return -1;
	}

	printf ("-I- config success \r\n");
	return 0;
}

serial_open(int port, long baudrate, int data_bits, int parity, int stop_bits)
{
	switch (port) {
	case 1:
		s_fd_uart1 = open(uart1,O_RDWR | O_NOCTTY | O_NDELAY);
		if(s_fd_uart1 == -1)
		{
			perror("Uart: Failed to open the file.\n");
			return -1;

		}
		uart_config(s_fd_uart1,baudrate,);
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	default:
		break;
	}
	return 0;
}
serial_close(int port)
{
	switch (port) {
	case 1:
		close(s_fd_uart1);
		break;
	default:
		break;
	}
	return 0;
}
serial_write(int port, char* buf, int len)
{
	int nByteActual =0;
	switch (port) {
	case 1:
		nByteActual = write(s_fd_uart1,buf,len);
		if(nByteActual <0 )
		{
			perror("Failed to write to the output\n");
			return -1;
		}
		else
		{
			printf("Send data successful !\r\n");

		}
		break;
	default:
		break;
	}
	return nByteActual;
}
serial_read(int port, char* buf, int len)
{
	int nByteActual;
	switch (port) {
		case 1:
			nByteActual = read (s_fd_uart1, buf, len);
			if(nByteActual<0)
			{
				perror("Error reading uart\n");
				return -1;
			}
			else
			{
				return nByteActual;
			}
			break;
		default:
			perror("Invalid Uart port \n");
			return -1;
			break;
	}
}
