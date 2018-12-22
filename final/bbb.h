#ifndef serial_h__  
#define serial_h__
 
#define DATA_NUM_BYTES	1
#define MAX_BUF_READ	1

serial_open(int port, long baudrate, int data_bits, int parity, int stop_bits);
serial_close(int port);
serial_write(int port, char* buf, int len);
serial_read(int port, char* buf, int len);

#endif
