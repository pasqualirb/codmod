/*
 * 25/10/2018
 *
 * p/ comunicacao de dados, prof. Vandersilvio
 *
 * Lucas Fagundes da Silva Lutz
 * Ricardo Biehl Pasquali
 */

#include <stdio.h>  /* printf() */
#include <stdlib.h> /* malloc() */
#include <string.h> /* memset() */

#include "draw.h"
#include "common.h" /* reset() */
#include "codification.h"
#include "modulation.h"

struct cmd {
	char *name;
	void (*function) (struct draw *d, int bit, void *data);
	void *data;
};

#define CODSEQ(...) (int[]) {__VA_ARGS__, -1}

/*
 * for zero,
 * for one,
 * flags
 * */
struct codification
nrz = {
	CODSEQ(BOTTOM),
	CODSEQ(TOP),
	0,
},
nrzl = {
	CODSEQ(TOP),
	CODSEQ(BOTTOM),
	MASK_BIPOLAR,
},
nrzi = {
	CODSEQ(KEEP),
	CODSEQ(INVERT),
	MASK_BIPOLAR,
},
ami = {
	CODSEQ(MIDDLE),
	CODSEQ(INVERT),
	MASK_BIPOLAR,
},
pseudoternary = {
	CODSEQ(INVERT),
	CODSEQ(MIDDLE),
	MASK_BIPOLAR,
},
manchester = {
	CODSEQ(TOP, BOTTOM),
	CODSEQ(BOTTOM, TOP),
	MASK_BIPOLAR,
},
diffmanchester = {
	CODSEQ(INVERT, INVERT),
	CODSEQ(KEEP, INVERT),
	MASK_BIPOLAR,
};

struct cmd commands[] = {
	/* codification */
	{"nrz",            cod, &nrz},
	{"nrzl",           cod, &nrzl},
	{"nrzi",           cod, &nrzi},
	{"ami",            cod, &ami},
	{"pseudoternary",  cod, &pseudoternary},
	{"manchester",     cod, &manchester},
	{"diffmanchester", cod, &diffmanchester},
	/* modulation */
	{"ask",            ask, NULL},
	{"fsk",            fsk, NULL},
	{"psk",            psk, NULL},
	{NULL}
};

static void
print_help(void)
{
	printf("usage: cmd <function> [options]\n"
	       "  codification:\n"
	       "    nrz\n"
	       "    nrzl\n"
	       "    nrzi\n"
	       "    ami\n"
	       "    pseudoternary\n"
	       "    manchester\n"
	       "    diffmanchester\n"
	       "  modulation:\n"
	       "    ask\n"
	       "    fsk\n"
	       "    psk\n");
}

int
main(int argc, char **argv)
{
	struct draw d;
	struct cmd *cmd;
	int size;
	int i;

	if (argc < 3) {
		print_help();
		return 1;
	}

	if (!(size = strlen(argv[2])))
		return 1;

	/* set function */

	cmd = commands;
	while (cmd->name) {
		if (strcmp(argv[1], cmd->name) == 0)
			break;
		cmd++;
	}

	if (cmd->name == NULL)
		return 1;

	d.width = 80;
	d.height = 9;

	draw_setup(&d);

	reset(&d); /* in common.c */

	for (i = 0; i < size; i++)
		cmd->function(&d, argv[2][i] == '0' ? 0 : 1, cmd->data);

	if (d.current)
		draw_print(&d);

	draw_cleanup(&d);

	return 0;
}
