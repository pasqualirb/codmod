/*
 * 08/11/2018
 */

#include <stdio.h>  /* putchar() */
#include <string.h> /* memcpy() */

#include "draw.h"

#include "common.h"

void
reset(struct draw *d)
{
	char *line;
	int i;

	if (d->current)
		draw_print(d);

	draw_reset(d);

	if (d->width < 5)
		return;

	line = draw_get_line(d, d->top);
	memcpy(line, "+5V", 3);

	line = draw_get_line(d, d->middle);
	memcpy(line, " 0V", 3);

	line = draw_get_line(d, d->bottom);
	memcpy(line, "-5V", 3);

	d->current = START_OFFSET;

	/* dividing line */
	for (i = 0; i < d->width; i++)
		putchar('-');
	putchar('\n');
}
