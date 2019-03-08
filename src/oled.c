#include "oled.h"

int main(int argc, char *argv[]) {

	printf("Hello oled\n\n");
	printf( "argc = %d\n", argc );
    for( int i = 0; i < argc; ++i ) {
        printf( "argv[ %d ] = %s\n", i, argv[ i ] );
    }
	printf( "\nDISPLAY_OFF = %X\n", DISPLAY_OFF );

	return 0;
}
