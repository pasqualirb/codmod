/*
 * 25/10/2018
 */

#include <stdio.h>  /* puts() */
#include <stdlib.h> /* malloc() */
#include <string.h> /* memset() */

#include "draw.h"

void
draw_print(struct draw *d)
{
	puts(d->buffer);
}

void
draw_reset(struct draw *d)
{
	int real_width = d->width + 1 /* newline */;
	int i;

	for (i = 0; i < d->height; i++) {
		memset(d->buffer + i * real_width, ' ', d->width);
		d->buffer[i * real_width + d->width] = '\n';
	}
	d->buffer[(d->height - 1) * real_width + d->width] = '\0';

	d->current = 0;
	d->top = 0;
	d->bottom = d->height - 1;
	d->middle = d->height / 2;
}

void
draw_cleanup(struct draw *d)
{
	free(d->buffer);
}

void
draw_setup(struct draw *d)
{
	int real_width = d->width + 1 /* newline */;

	d->buffer = malloc(real_width * d->height);
}
