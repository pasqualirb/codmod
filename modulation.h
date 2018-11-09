/*
 * 08/11/2018
 */

#ifndef MODULATION_H
#define MODULATION_H

#include "draw.h"

void
ask(struct draw *d, int bit, void *data);

void
fsk(struct draw *d, int bit, void *data);

void
psk(struct draw *d, int bit, void *data);

#endif /* MODULATION_H */
