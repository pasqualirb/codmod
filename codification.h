/*
 * 05/11/2018
 */

#ifndef CODIFICATION_H
#define CODIFICATION_H

#include "draw.h"

#define MASK_PREVIOUS_BIT  (1 << 0)
#define MASK_HAS_PREVIOUS  (1 << 1)
#define MASK_POLARITY      (1 << 2)
#define MASK_BIPOLAR       (1 << 3)
#define MASK_MIDDLE        (1 << 4)

/* comandos de desenho */
enum {
	INVERT,
	KEEP,
	TOP,
	BOTTOM,
	MIDDLE,
};

struct codification {
	int *zero;
	int *one;
	int flags;
};

void
cod(struct draw *d, int bit, void *data);

#endif /* CODIFICATION_H */
