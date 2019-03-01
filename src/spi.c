#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// these are not used anymore...
#include <string>
#include <cstring>

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

#define DISPLAY_OFF                 0xae
#define SET_MULTIPLEX_RATIO         0xa8 // 0x3f => 63d = 64 MUX
#define SET_DISPLAY_OFFSET          0xd3 // 0x00 => no offset
#define SET_DISPLAY_START_LINE      0x40
#define SET_SEGMENT_REMAP_start     0xa0 // start/end are not correct descriptions...
#define SET_SEGMENT_REMAP_end       0xa1
#define SET_COM_OUTPUT              0xc0
#define SET_COM_OUTPUT_SCAN_DIR     0xc8
#define SET_COM_PINS                0xda // 0x12 => RESET 
#define SET_CONTRAST_CONTROL        0x81 // 0xff => MAX contrast
#define ENTIRE_DISPLAY_ON_RESET     0xa4 // A4 resume to RAM content, A5 entire display on
#define INVERSE_OFF                 0xa6
#define SET_DISPLAY_CLOCK_DIVIDE    0xd5 // 0x80 => two values in one hex! Divide ratio (1) and Osc Freq. (RESET)
#define 0x8d
#define SET_HIGHER_COLUMN_PAGE_ADDR 0x14
#define DISPLAY_ON                  0xaf
#define SET_MEMORY                  0x20 // 0x02 Page addressing mode

//********** SPI OPEN PORT **********
//spi_device	0=CS0, 1=CS1
int spi_open_port (int spi_device) {
    int *spi_cs_fd;

    //----- SET SPI MODE -----
    //SPI_MODE_0 (0,0) 	CPOL = 0, CPHA = 0, Clock idle low, data is clocked in on rising edge, output data (change) on falling edge
    //SPI_MODE_1 (0,1) 	CPOL = 0, CPHA = 1, Clock idle low, data is clocked in on falling edge, output data (change) on rising edge
    //SPI_MODE_2 (1,0) 	CPOL = 1, CPHA = 0, Clock idle high, data is clocked in on falling edge, output data (change) on rising edge
    //SPI_MODE_3 (1,1) 	CPOL = 1, CPHA = 1, Clock idle high, data is clocked in on rising, edge output data (change) on falling edge
    spi_mode = SPI_MODE_0;
    //----- SET BITS PER WORD -----
    spi_bitsPerWord = 8;
    //----- SET SPI BUS SPEED -----
    spi_speed = 1000000;		//1000000 = 1MHz (1uS per bit) 

    if (spi_device) spi_cs_fd = &spi_cs1_fd;
    else spi_cs_fd = &spi_cs0_fd;

    if (spi_device)*spi_cs_fd = open("/dev/spidev0.1", O_RDWR);
    else *spi_cs_fd = open("/dev/spidev0.0", O_RDWR);

    if (*spi_cs_fd < 0) {
        perror("Error - Could not open SPI device");
        exit(1);
    }

    // Set SPI write mode
    if(ioctl(*spi_cs_fd, SPI_IOC_WR_MODE, &spi_mode) < 0) {
        perror("Could not set SPIMode (WR)...ioctl fail");
        exit(1);
    }
    // Set SPI read mode
    if(ioctl(*spi_cs_fd, SPI_IOC_RD_MODE, &spi_mode) < 0) {
      perror("Could not set SPIMode (RD)...ioctl fail");
      exit(1);
    }
    // Set SPI write bits-per-word
    if(ioctl(*spi_cs_fd, SPI_IOC_WR_BITS_PER_WORD, &spi_bitsPerWord) < 0) {
      perror("Could not set SPI bitsPerWord (WR)...ioctl fail");
      exit(1);
    }
    // Set SPI read bits-per-word
    if(ioctl(*spi_cs_fd, SPI_IOC_RD_BITS_PER_WORD, &spi_bitsPerWord) < 0) {
      perror("Could not set SPI bitsPerWord(RD)...ioctl fail");
      exit(1);
    }
    // Set SPI write max speed (hz)
    if(ioctl(*spi_cs_fd, SPI_IOC_WR_MAX_SPEED_HZ, &spi_speed) < 0) {
      perror("Could not set SPI speed (WR)...ioctl fail");
      exit(1);
    }
    // Set SPI read max speed (hz)
    if(ioctl(*spi_cs_fd, SPI_IOC_RD_MAX_SPEED_HZ, &spi_speed) < 0) {
      perror("Could not set SPI speed (RD)...ioctl fail");
      exit(1);
    }
    return 1;
}

//********** SPI CLOSE PORT **********
int spi_close_port (int spi_device) {
    int *spi_cs_fd;

    if (spi_device) spi_cs_fd = &spi_cs1_fd;
    else spi_cs_fd = &spi_cs0_fd;

    if(close(*spi_cs_fd); < 0) {
    	perror("Error - Could not close SPI device");
    	exit(1);
    }
    return 1;
}

//********** SPI WRITE & READ DATA **********
//data		Bytes to write.  Contents is overwritten with bytes read.
int spi_write_read (int spi_device, unsigned char *data, int length) {
	struct spi_ioc_transfer spi[length];
    int *spi_cs_fd;

    if (spi_device) spi_cs_fd = &spi_cs1_fd;
    else spi_cs_fd = &spi_cs0_fd;

	//one spi transfer for each byte
	for (int i = 0 ; i < length ; i++) {
		memset(&spi[i], 0, sizeof (spi[i]));
		spi[i].tx_buf        = (unsigned long)(data + i); // transmit from "data"
		spi[i].rx_buf        = (unsigned long)(data + i); // receive into "data"
		spi[i].len           = sizeof(*(data + i));
		spi[i].delay_usecs   = 0;
		spi[i].speed_hz      = spi_speed;
		spi[i].bits_per_word = spi_bitsPerWord;
		spi[i].cs_change = 0;
	}

	if(ioctl(*spi_cs_fd, SPI_IOC_MESSAGE(length), &spi) < 0) {
		perror("Error - Problem transmitting spi data..ioctl");
		exit(1);
	}
	return 1;
}