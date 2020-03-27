#ifndef __SHAPES_H__
#define __SHAPES_H__

int draw_line(uint32_t *bitmap, uint32_t colour, int width, int x0, int x1, int y0, int y1);
int draw_line_high(uint32_t *bitmap, uint32_t colour, int width,int x0, int x1, int y0, int y1);
int draw_line_low(uint32_t *bitmap, uint32_t colour, int width, int x0, int x1, int y0, int y1);

int draw_circle(uint32_t *bitmap, uint32_t colour, int width, int x, int y, int r);

#endif
