/*
 * 03/11/2018
 */

#include "common.h"
#include "draw.h"

#include "codification.h"

#define get(flags, mask) (!!(*(flags) & mask))
#define set(flags, mask, value) \
        (value ? (*(flags) |= mask) : (*(flags) &= ~mask))

#define BIT_LENGTH   4

static void
vertical_line(struct draw *d, int start, int end)
{
	int i;
	int offset = d->current - 1;

	draw(d, offset, start, '.');
	for (i = start + 1; i < end; i++)
		draw(d, offset, i, '|');
	draw(d, offset, end, '\'');
}

static void
horizontal_line(struct draw *d, int n)
{
	int i;

	if (d->current + 4 > d->width)
		reset(d);

	for (i = 0; i < 4; i++)
		draw(d, d->current++, n, '-');
}

/* Executa comando de desenho */
static void
do_cmd(struct draw *d, int cmd, int *flags)
{
	int polarity = get(flags, MASK_POLARITY);
	int bottom = get(flags, MASK_BIPOLAR) ? d->bottom : d->middle;

	switch (cmd) {

	/* Desenha a polaridade contraria a anterior. */
	case INVERT:
		if (get(flags, MASK_MIDDLE)) {
			if (polarity)
				vertical_line(d, d->middle, d->bottom);
			else
				vertical_line(d, d->top, d->middle);
			set(flags, MASK_MIDDLE, 0);
		} else {
			vertical_line(d, d->top, bottom);
		}

		horizontal_line(d, polarity ? bottom : d->top);

		set(flags, MASK_POLARITY, !polarity);
		break;

	/* Desenha a mesma que a anterior. */
	case KEEP:
		if (get(flags, MASK_MIDDLE))
			horizontal_line(d, d->middle);
		else
			horizontal_line(d, polarity ? d->top : bottom);
		break;

	/* Desenha para cima. Polaridade se torna um. */
	case TOP:
		if (get(flags, MASK_MIDDLE)) {
			vertical_line(d, d->top, d->middle);
			set(flags, MASK_MIDDLE, 0);
		} else if (!polarity) {
			vertical_line(d, d->top, bottom);
		}
		horizontal_line(d, d->top);
		set(flags, MASK_POLARITY, 1);
		break;

	/* Desenha para baixo. Polaridade se torna zero. */
	case BOTTOM:
		if (get(flags, MASK_MIDDLE)) {
			vertical_line(d, d->middle, d->bottom);
			set(flags, MASK_MIDDLE, 0);
		} else if (polarity) {
			vertical_line(d, d->top, bottom);
		}
		horizontal_line(d, bottom);
		set(flags, MASK_POLARITY, 0);
		break;

	/* Desenha para meio. Nao afeta a polaridade. */
	case MIDDLE:
		if (!get(flags, MASK_MIDDLE)) {
			if (polarity)
				vertical_line(d, d->top, d->middle);
			else
				vertical_line(d, d->middle, d->bottom);
			set(flags, MASK_MIDDLE, 1);
		}
		horizontal_line(d, d->middle);
		break;
	}
}

void
cod(struct draw *d, int bit, void *data)
{
	struct codification *c = data;
	int *cmd = bit ? c->one : c->zero;

	while (*cmd != -1)
		do_cmd(d, *(cmd++), &c->flags);
}

#if 0
void
generic(struct draw *d, int bit, int *flags)
{
	if (!get(flags, MASK_HAS_PREVIOUS))
		do_cmd(d, MIDDLE, flags);

	//__function(d, bit, flags);

	set(flags, MASK_HAS_PREVIOUS, 1);
	set(flags, MASK_PREVIOUS_BIT, bit);
}

void
nrz(struct draw *d, int bit, int *flags)
{
	do_cmd(d, bit ? TOP : BOTTOM, flags);
}

void
nrzl(struct draw *d, int bit, int *flags)
{
	set(flags, MASK_BIPOLAR, 1);

	nrz(d, bit, flags);
}

void
nrzi(struct draw *d, int bit, int *flags)
{
	set(flags, MASK_BIPOLAR, 1);

	do_cmd(d, bit ? INVERT : KEEP, flags);
}

void
ami(struct draw *d, int bit, int *flags)
{
	/* always bipolar */
	set(flags, MASK_BIPOLAR, 1);

	do_cmd(d, bit ? INVERT : MIDDLE, flags);
}

/* Same as AMI, but bit is negated */
void
pseudoternary(struct draw *d, int bit, int *flags)
{
	ami(d, !bit, flags);
}

void
manchester(struct draw *d, int bit, int *flags)
{
	if (bit) {
		do_cmd(d, BOTTOM, flags);
		do_cmd(d, TOP, flags);
	} else {
		do_cmd(d, TOP, flags);
		do_cmd(d, BOTTOM, flags);
	}
}

void
diffmanchester(struct draw *d, int bit, int *flags)
{
	if (bit) {
		do_cmd(d, INVERT, flags);
		do_cmd(d, INVERT, flags);
	} else {
		do_cmd(d, KEEP, flags);
		do_cmd(d, INVERT, flags);
	}
}
#endif

#if 0
static void
test(struct draw *d)
{
	/* digital */

	draw_reset(d);
	vertical_line(d, d->top, d->bottom);
	horizontal_line(d, d->top);
	vertical_line(d, d->top, d->middle);
	horizontal_line(d, d->middle);
	vertical_line(d, d->middle, d->bottom);
	horizontal_line(d, d->bottom);
}
#endif
