#ifndef OLEDFONTS_H_
#define OLEDFONTS_H_

#include <stdint.h>

#define fontbyte(x) Font.font[x]

typedef const uint8_t fontdatatype;
typedef enum
{
	NORMAL	= 0,
	INVERT	= 1
} OLEDinverted;

typedef enum
{
	LEFT   = 253,
	RIGHT  = 254,
	CENTER = 255
} OLEDalign;

typedef struct
{
	const uint8_t* font;
	int16_t width;
	int16_t height;
	int16_t offset;
	int16_t numchars;
	OLEDinverted inverted;
} font_t;

extern font_t Font;

extern fontdatatype BigNumbers[];
extern fontdatatype Segoe_UI_Rus_12[];
extern fontdatatype Segoe_UI_Rus_10[];
extern fontdatatype Segoe_UI_Rus_8[];
extern fontdatatype Arial_Rus_7[];
extern fontdatatype Segoe_UI_Eng_12[];
extern fontdatatype Segoe_UI_Eng_10[];

void FontSet(const uint8_t* font);

#endif /* OLEDFONTS_H_ */
