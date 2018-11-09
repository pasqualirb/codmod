/*
 * 08/11/2018
 *
 * modulation
 *
 * link with -lm
 */

#include <assert.h> /* assert() */
#include <math.h>   /* sin(), rint() */

#include "common.h"
#include "draw.h"

/* Return amplitude (y) for a given phase (x) */
static int
get_sin(int phase, int wavelength, int amplitude)
{
	double _phase;

	assert(wavelength > 1);

	_phase = phase / (double) (wavelength - 1) * 2. * M_PI;

	return (int) rint(sin(_phase) * amplitude);
}

static void
do_sin(int *buffer, int size, int wavelength, int amplitude, int phase)
{
	int i;

	for (i = 0; i < size; i++)
		buffer[i] = get_sin(phase + i, wavelength, amplitude);
}

/*
 * E.g.:
 *    x
 *    0----------12> (wavelength = 13)
 * y 0  .-.
 *   | '   .
 *   |-     .
 *   |       .   -
 *   4        -.-
 *   v (amplitude = 5)
 */
static void
print_graph(struct draw *d, int *buffer, int size)
{
	int i;
	int tmp;
	char character;

	for (i = 0; i < size; i++) {
		tmp = buffer[i];
		tmp += d->height / 2 * 3;
		tmp  = d->height * 3 - 1 - tmp;

		switch (tmp % 3) {
		case 0:
			character = '\'';
			break;
		case 1:
			character = '-';
			break;
		case 2:
			character = '.';
			break;
		}

		draw(d, d->current, tmp / 3, character);

		d->current++;
		if (d->current == d->width)
			reset(d);
	}
}

void
ask(struct draw *d, int bit, void *data)
{
	int buffer[22];

	if (bit) {
		do_sin(buffer, 22, 12, 4 * 3, 0);
		print_graph(d, buffer, 22);
	} else {
		do_sin(buffer, 22, 12, 2 * 3, 0);
		print_graph(d, buffer, 22);
	}
}

void
fsk(struct draw *d, int bit, void *data)
{
	int buffer[24];

	if (bit) {
		do_sin(buffer, 22, 12, 4 * 3, 0);
		print_graph(d, buffer, 22);
	} else {
		do_sin(buffer, 23, 24, 4 * 3, 0);
		print_graph(d, buffer, 23);
	}
}

void
psk(struct draw *d, int bit, void *data)
{
	int buffer[24];

	if (bit) {
		do_sin(buffer, 23, 24, 4 * 3, 0);
		print_graph(d, buffer, 22);
	} else {
		do_sin(buffer, 23, 24, 4 * 3, 11);
		print_graph(d, buffer, 23);
	}
}

#if 0
static void
test(struct draw *d)
{
	int *buffer;

	buffer = malloc(sizeof(int) * d->width);

	/* frequency and amplitude */

	do_sin(buffer, 22, 12, 4 * 3, 0);
	print_graph(d, buffer, 22);

	do_sin(buffer, 16, 9, 2 * 3, 0);
	print_graph(d, buffer, 16);

	do_sin(buffer, 11, 6, 1 * 3, 0);
	print_graph(d, buffer, 11);

	draw_print(d);

	/* one wavelength */

	draw_reset(d);
	do_sin(buffer, d->width, d->width, 4 * 3, 0);
	print_graph(d, buffer, d->width);

	/* FSK */

	draw_reset(d);

	do_sin(buffer, 22, 12, 4 * 3, 0);
	print_graph(d, buffer, 22);

	do_sin(buffer, 23, 24, 4 * 3, 0);
	print_graph(d, buffer, 23);

	draw_print(d);

	/* ASK */

	draw_reset(d);

	do_sin(buffer, 22, 12, 4 * 3, 0);
	print_graph(d, buffer, 22);

	do_sin(buffer, 22, 12, 2 * 3, 0);
	print_graph(d, buffer, 22);

	draw_print(d);

	/* PSK */

	draw_reset(d);

	do_sin(buffer, 23, 24, 4 * 3, 0);
	print_graph(d, buffer, 23);

	do_sin(buffer, 23, 24, 4 * 3, 11);
	print_graph(d, buffer, 23);

	draw_print(d);

	free(buffer);
}
#endif
