#include <pebble.h>
#include "patterns.h"
void pattern_offset(uint8_t *data, int8_t x_offset, int8_t y_offset, uint8_t invert) {  // invert = [0 or 255] for [no or yes] ([1-254] inverts vertical stripes based on bit mask)
  uint8_t temp[8];
  uint8_t mask = ((x_offset%8)+8)%8;  // sanatize x_offset [-128 to 127] to [0 to  7]
  uint8_t row  = ((y_offset%8)+8);    // sanatize y_offset [-128 to 127] to [0 to 15]
  for(uint8_t i=0; i<8; i++)
    temp[i] = ((data[(row+i)%8] << mask) + (data[(row+i)%8] >> (8-mask))) ^ invert; // shift 8bit segment x&y offset, then invert using XOR
  for(uint8_t i=0; i<8; i++) data[i] = temp[i];
}

uint8_t* pattern_offset2(uint8_t *data, int8_t x_offset, int8_t y_offset, uint8_t invert) {  // invert=0 or 255
  static uint8_t temp[8];
  uint8_t mask = ((x_offset%8)+8)%8;  // convert [-128 to 127] to [0 to 7]
  uint8_t yoffset = ((y_offset%8)+8);  // sanatize y_offset [-128 to 127] to [0 to 15]
  for(uint8_t i=0; i<8; i++)
    temp[i] = ((data[(yoffset+i)%8] << mask) + (data[(yoffset+i)%8] >> (8-mask))) ^ invert; // shift 8bit segment x&y offset, then invert using XOR
  //if(invert) for(uint8_t i=0; i<8; i++) temp[i] = ~temp[i];  // back when invert was bool
  return temp;
}

void fill_bitmap(GBitmap *ctx, uint8_t *data) {
  for(uint16_t y_addr=0, row=0; y_addr<168*20; y_addr+=20, row=(row+1)%8)
    for(uint16_t x_addr=0; x_addr<19; x_addr++)
      ((uint8_t*)(((GBitmap*)ctx)->addr))[y_addr+x_addr] = data[row];
}

void fill_window(GContext *ctx, uint8_t *data) {
  for(uint16_t y_addr=0, row=0; y_addr<168*20; y_addr+=20, row=(row+1)%8)
    for(uint16_t x_addr=0; x_addr<19; x_addr++)
      ((uint8_t*)(((GBitmap*)ctx)->addr))[y_addr+x_addr] = data[row];
}

void fill_rect(GContext *ctx, GRect rect, uint8_t *data, bool invert, uint8_t x_offset, uint8_t y_offset) {
  uint8_t segment[8];
  GPoint addr;

  uint8_t l_mask = 255 << (rect.origin.x%8);               // mask for the left side
  uint8_t r_mask = 255 << ((rect.origin.x+rect.size.w)%8); // mask for the right side
  uint8_t s_mask = (x_offset+rect.origin.x)%8;             // mask for x_offset shifting
  if(invert) for(uint8_t i=0; i<8; i++) segment[i] = ~((data[i] << s_mask) + (data[i] >> (8-s_mask))); // shift 8bit segment x&y offset, then invert bits
  else       for(uint8_t i=0; i<8; i++) segment[i] =  ((data[i] << s_mask) + (data[i] >> (8-s_mask))); // shift 8bit segment x&y offset
  
  addr.y = rect.origin.y*20;
  for (int16_t y=0; y<rect.size.h; y++, y_offset=(y_offset+1)%8, addr.y+=20) {
    if(addr.y>=0 && addr.y<168*20) {   // if y row is on the screen
      addr.x = rect.origin.x>>3;       // init X memory address
      if(addr.x >= 0 && addr.x < 19) ((uint8_t*)(((GBitmap*)ctx)->addr))[addr.y + addr.x] = (segment[y_offset] & l_mask) + (((uint8_t*)(((GBitmap*)ctx)->addr))[addr.y + addr.x] & ~l_mask); // fill left-side of row
      for (addr.x++; addr.x<((rect.origin.x+rect.size.w)>>3); addr.x++) if(addr.x >= 0 && addr.x < 19) ((uint8_t*)(((GBitmap*)ctx)->addr))[addr.y + addr.x] = segment[y_offset];           // fill middle of row
      if(addr.x >= 0 && addr.x < 19) ((uint8_t*)(((GBitmap*)ctx)->addr))[addr.y + addr.x] = (((uint8_t*)(((GBitmap*)ctx)->addr))[addr.y + addr.x] & r_mask) + (segment[y_offset] & ~r_mask); // fill right-side of row
    }
  }
}