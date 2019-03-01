#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// Needed for SPI port
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <unistd.h>

int spi_cs0_fd;				//file descriptor for the SPI device
int spi_cs1_fd;				//file descriptor for the SPI device
unsigned char spi_mode;
unsigned char spi_bitsPerWord;
unsigned int spi_speed;

int spi_open_port (int spi_device);
int spi_close_port (int spi_device);
int spi_write_read (int spi_device, unsigned char *data, int length);
