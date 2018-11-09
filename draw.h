/*
 * 05/11/2018
 */

#ifndef DRAW_H
#define DRAW_H

struct draw {
	int top;
	int bottom;
	int middle;
	int current;

	int width;
	int height;

	char *buffer;
};

static inline void
draw(struct draw *d, int x, int y, char symbol)
{
        d->buffer[y * (d->width + 1) + x] = symbol;
}

static inline char*
draw_get_line(struct draw *d, int y)
{
	return d->buffer + y * (d->width + 1);
}

void
draw_print(struct draw *d);

void
draw_reset(struct draw *d);

void
draw_cleanup(struct draw *d);

void
draw_setup(struct draw *d);

#endif /* DRAW_H */
