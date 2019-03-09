#include "oled.h"

int main(int argc, char *argv[]) {

	printf("Hello oled\n\n");
	/*
	printf( "argc = %d\n", argc );
	int i;
    for(i = 0; i < argc; ++i) {
        printf( "argv[ %d ] = %s\n", i, argv[ i ] );
    }
	printf( "\nDISPLAY_OFF = %X\n", DISPLAY_OFF );
	*/
	if(!spi_open_port(0)) {
		printf("SPI port open\n");
	}
	if(!spi_write_read(0, initbuf, sizeof(initbuf))) {
		printf("initbuf written successfully!\n");
	}
	if(!spi_close_port(0)) {
		printf("SPI port closed\n");
	}
	printf("Goodbye oled\n\n");

	return 0;
}
