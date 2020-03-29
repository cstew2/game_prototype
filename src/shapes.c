#include <stdint.h>
#include <math.h>

#include "shapes.h"

int draw_line(uint32_t *bitmap, uint32_t colour, int width, int x0, int x1, int y0, int y1)
{
	int y = y1 - y0;
	int x = x1 - x0;
	if(fabs(y) < fabs(x)) {
		if (x0 > x1) {
			draw_line_low(bitmap, colour, width, x1, x0, y1, y0);
		}
		else {
			draw_line_low(bitmap, colour, width, x0, x1, y0, y1);
		}
			       
	}
	else {
		if(y0 > y1) {
			draw_line_high(bitmap, colour, width, x1, x0, y1, y0);
		}
		else {
			draw_line_high(bitmap, colour, width, x0, x1, y0, y1);
		}
	}
	return 0;
}

int draw_line_low(uint32_t *bitmap, uint32_t colour, int width, int x0, int x1, int y0, int y1)
{
        int dx = x1 - x0;
	int dy = y1 - y0;
	int yi = 1;
	if(dy < 0) {
		yi = -1;
		dy = -dy;
	}
	int D = 2*dy - dx;
	int y = y0;

	for(int x=x0; x < x1; x++) {
		bitmap[y*width + x] = colour;
		if(D > 0) {
			y = y + yi;
			D = D - 2*dx;
		}
		D = D + 2*dy;
	}
	return 0;
}

int draw_line_high(uint32_t *bitmap, uint32_t colour, int width, int x0, int x1, int y0, int y1)
{
	int dx = x1 - x0;
	int dy = y1 - y0;
	int xi = 1;
	if(dx < 0) {
		xi = -1;
		dx = -dx;
	}
	int D = 2*dx - dy;
	int x = x0;

	for(int y=y0; y < y1; y++) {
		bitmap[y*width + x] = colour;
		if(D > 0) {
			x = x + xi;
			D = D -2 *dy;
		}
		D = D + 2*dx;
	}
	return 0;
}

int draw_circle(uint32_t *bitmap, uint32_t colour, int width, int x, int y, int r)
{	
	for (int i = -r; i < r ; i++)
	{
		int height = sqrt(r * r - i * i);

		for (int j = -height; j < height; j++)
			bitmap[(j + y)*width + (i + x)] = colour;
	}
	return 0;
}

int draw_poly(uint32_t *bitmap, uint32_t colour, int width, int height, point *vertices, size_t vertex_count)
{
	for(int y=0; y < height; y++) {
		int x_inter[vertex_count];
		int x_count = 0;

		//find intercepts on y scanline
		int j=vertex_count-1;
		for(int i=0; i < vertex_count; i++) {
			if((vertices[i].y < y &&  vertices[j].y >= y) ||
			   (vertices[i].y < y &&  vertices[j].y >= y)) {
				x_inter[x_count++] = (vertices[i].x + y-vertices[i].y) /
					             (vertices[j].y - vertices[i].y) *
					             (vertices[j].x - vertices[i].x);
			}
			j=i;
		}

		//sort by x value
		sorti(x_inter, vertex_count);
		
		//draw between intercepts
		for(int i=0; i < x_count; i+=2) {
			if(x_inter[i] < 0) {
				x_inter[i] = 0;
			}
			if(x_inter[i+1] > width-1) {
				x_inter[i+1] = width-1;
			}
			for(int j=x_inter[i]; j < x_inter[i+1]; j++) {
				bitmap[(y * width) + j] = colour;
			}
		}
	}
	
	return 0;
}
