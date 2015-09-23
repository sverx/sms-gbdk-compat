
#define TARGET_GG
#include <gb.h>

void add_VBL(int_handler h) {}
void add_LCD(int_handler h) {}
void add_TIM(int_handler h) {}
void add_SIO(int_handler h) {}
void add_JOY(int_handler h) {}
void mode(UBYTE m) {}
UBYTE	get_mode(void) {}

/* ************************************************************ */


void delay(UWORD d) {}


/* ************************************************************ */


UBYTE joypad(void) {
  return SMS_getKeysStatus();
}

UBYTE waitpad(UBYTE mask) {
  UBYTE joy;
  while (!(joy = joypad() & mask)) {
    SMS_waitForVBlank();
  }
  return joy;
}

void waitpadup(void) {
  while (joypad()) {
    SMS_waitForVBlank();
  }
}


/* ************************************************************ */


void enable_interrupts(void) {}

void disable_interrupts(void) {}

void set_interrupts(UBYTE flags) {}

void reset(void) {}

void wait_vbl_done(void) {
  SMS_waitForVBlank();
}

void display_off(void) {
  SMS_displayOff();
}


/* ************************************************************ */

void SMS_loadTiles_2bpp(UWORD first_tile, UBYTE nb_tiles, unsigned char *data) {
  UWORD i;
  UBYTE j;
	unsigned char buffer[32], *o, *d;

	o = data;
	for (i = 0; i != nb_tiles; i++) {
		d = buffer;
		for (j = 0; j != 8; j++) {
			*d = *o; o++; d++;
      *d = *o; o++; d++;
			*d = 0;	d++;
			*d = 0;	d++;
		}
		SMS_loadTiles(buffer, i + first_tile, 32);
	}
}

void set_bkg_data(UBYTE first_tile, UBYTE nb_tiles, unsigned char *data) {
  SMS_loadTiles_2bpp(first_tile, nb_tiles, data);
}

void set_bkg_tiles(UBYTE x, UBYTE y, UBYTE w, UBYTE h, unsigned char *tiles) {
  UBYTE i;
  UWORD buffer[32], *d;

  for (; h; h--, y++) {
    d = buffer;
    for (i = w; i; i--, d++, tiles++) {
      *d = *tiles;
    }
    SMS_loadTileMapArea(x, y, buffer, w, 1);
  }
}

void get_bkg_tiles(UBYTE x,
	      UBYTE y,
	      UBYTE w,
	      UBYTE h,
	      unsigned char *tiles) {
}

void move_bkg(UBYTE x, UBYTE y) {
  SMS_setBGScrollX(x);
  SMS_setBGScrollY(y);
}

void scroll_bkg(BYTE x, BYTE y) {

}


/* ************************************************************ */


void set_win_data(UBYTE first_tile, UBYTE nb_tiles, unsigned char *data) {}
void set_win_tiles(UBYTE x, UBYTE y, UBYTE w, UBYTE h, unsigned char *tiles) {}
void get_win_tiles(UBYTE x, UBYTE y, UBYTE w, UBYTE h, unsigned char *tiles) {}
void move_win(UBYTE x, UBYTE y) {}
void scroll_win(BYTE x, BYTE y) {}


/* ************************************************************ */


void set_sprite_data(UBYTE first_tile, UBYTE nb_tiles, unsigned char *data) {
  SMS_loadTiles_2bpp(((UWORD) first_tile) + 256, nb_tiles, data);
}

void get_sprite_data(UBYTE first_tile, UBYTE nb_tiles, unsigned char *data) {}
void set_sprite_tile(UBYTE nb, UBYTE tile) {}
UBYTE get_sprite_tile(UBYTE nb) {}
void set_sprite_prop(UBYTE nb, UBYTE prop) {}
UBYTE get_sprite_prop(UBYTE nb) {}
void move_sprite(UBYTE nb, UBYTE x, UBYTE y) {}
void scroll_sprite(BYTE nb, BYTE x, BYTE y) {}


/* ************************************************************ */


void cgb_compatibility(void) {
  GG_setBGPaletteColor (0, 0xDEF);
  GG_setSpritePaletteColor (0, 0xDEF);
  GG_setBGPaletteColor (1, 0x89A);
  GG_setSpritePaletteColor (1, 0x89A);
  GG_setBGPaletteColor (2, 0x455);
  GG_setSpritePaletteColor (2, 0x455);
  GG_setBGPaletteColor (3, 0x022);
  GG_setSpritePaletteColor (3, 0x022);
}