
#define DISPLAY_OFF                 	0xae
#define SET_MULTIPLEX_RATIO         	0xa8 // 0x3f => 63d = 64 MUX
#define SET_DISPLAY_OFFSET          	0xd3 // 0x00 => no offset
#define SET_DISPLAY_START_LINE      	0x40
#define SET_SEGMENT_REMAP_start     	0xa0 // start/end are not correct descriptions...
#define SET_SEGMENT_REMAP_end       	0xa1
#define SET_COM_OUTPUT              	0xc0
#define SET_COM_OUTPUT_SCAN_DIR     	0xc8
#define SET_COM_PINS                	0xda // 0x12 => RESET 
#define SET_CONTRAST_CONTROL        	0x81 // 0xff => MAX contrast
#define ENTIRE_DISPLAY_ON_RESET     	0xa4 // A4 resume to RAM content, A5 entire display on
#define INVERSE_OFF                 	0xa6
#define SET_DISPLAY_CLOCK_DIVIDE    	0xd5 // 0x80 => two values in one hex! Divide ratio (1) and Osc Freq. (RESET)
#define CHARGE_PUMP						0x8d
#define SET_HIGHER_COLUMN_PAGE_ADDR 	0x14
#define DISPLAY_ON                  	0xaf
#define SET_LOWER_COLUMN_START_ADDR		0x00

/*
#define MEMORY_MODE          					0x20 ///< See datasheet
#define COLUMN_ADDR          					0x21 ///< See datasheet
#define PAGE_ADDR            					0x22 ///< See datasheet
#define SET_CONTRAST         					0x81 ///< See datasheet
#define CHARGE_PUMP          					0x8D ///< See datasheet
#define SEG_REMAP            					0xA0 ///< See datasheet
#define DISPLAY_ALL_ON_RESUME 					0xA4 ///< See datasheet
#define DISPLAY_ALL_ON        					0xA5 ///< Not currently used
#define NORMAL_DISPLAY       					0xA6 ///< See datasheet
#define INVERT_DISPLAY       					0xA7 ///< See datasheet
#define SET_MULTIPLEX        					0xA8 ///< See datasheet
#define DISPLAY_OFF          					0xAE ///< See datasheet
#define DISPLAY_ON           					0xAF ///< See datasheet
#define COM_SCAN_INC          					0xC0 ///< Not currently used
#define COM_SCAN_DEC          					0xC8 ///< See datasheet
#define SET_DISPLAY_OFFSET    					0xD3 ///< See datasheet
#define SET_DISPLAY_CLOCK_DIV  					0xD5 ///< See datasheet
#define SET_PRE_CHARGE        					0xD9 ///< See datasheet
#define SET_COM_PINS          					0xDA ///< See datasheet
#define SET_VCOM_DETECT       					0xDB ///< See datasheet

#define SET_LOW_COLUMN        					0x00 ///< Not currently used
#define SET_HIGH_COLUMN       					0x10 ///< Not currently used
#define SET_START_LINE        					0x40 ///< See datasheet

#define EXTERNAL_VCC         					0x01 ///< External display voltage source
#define SWITCH_CAP_VCC        					0x02 ///< Gen. display voltage from 3.3V

#define RIGHT_HORIZONTAL_SCROLL              	0x26 ///< Init rt scroll
#define LEFT_HORIZONTAL_SCROLL               	0x27 ///< Init left scroll
#define VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 	0x29 ///< Init diag scroll
#define VERTICAL_AND_LEFT_HORIZONTAL_SCROLL  	0x2A ///< Init diag scroll
#define DEACTIVATE_SCROLL                    	0x2E ///< Stop scroll
#define ACTIVATE_SCROLL                      	0x2F ///< Start scroll
#define SET_VERTICAL_SCROLL_AREA             	0xA3 ///< Set scroll rangedefine SET_MEMORY                  	0x20 // 0x02 Page addressing mode
*/

static const unsigned char initbuf[] = {
	DISPLAY_OFF, 
	SET_MULTIPLEX_RATIO, 0x3f,
	SET_DISPLAY_OFFSET, 0x00,
	SET_DISPLAY_START_LINE,
	SET_SEGMENT_REMAP_start, SET_SEGMENT_REMAP_end,
	SET_COM_OUTPUT,
	SET_COM_OUTPUT_SCAN_DIR,
	SET_COM_PINS, 0x12,
	SET_CONTRAST_CONTROL, 0xff,
	ENTIRE_DISPLAY_ON_RESET,
	INVERSE_OFF,
	SET_DISPLAY_CLOCK_DIVIDE, 0x80,
	CHARGE_PUMP,
	SET_HIGHER_COLUMN_PAGE_ADDR,
	DISPLAY_ON,
	SET_LOWER_COLUMN_START_ADDR
};

