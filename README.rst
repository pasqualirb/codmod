codmod
======

:Date: 2018-11-09

Draw codification or modulation patterns in text.


How to use
==========

``codmod <command> <1s_and_0s>``

Commands::

	Codification:
	  nrz
	  nrzl
	  nrzi
	  ami
	  pseudoternary
	  manchester
	  diffmanchester
	Modulation:
	  ask
	  fsk
	  psk

E.g.: ``codmod nrz 1010111001``.


How it works
============

Codification
------------

Draw horizontal or vertical lines (``horizontal_line()``
and ``vertical_line()`` in ``codification.c``) according
to the drawing commands below:

- INVERT: Draw to the opposite polarity. Invert polarity.
- KEEP:   Draw horizontal line as previous.
- TOP:    Draw to the top. Polarity becomes 1.
- BOTTOM: Draw to the botom. Polarity becomes 0.
- MIDDLE: Draw to the middle. Does not affect polarity.

The following masks store flags used for the above commands:

- MASK_PREVIOUS_BIT: The previous bit value.
- MASK_HAS_PREVIOUS: Whether a previous bit exists.
- MASK_POLARITY: The previous polarity.
- MASK_BIPOLAR: Whether it is bipolar.
- MASK_MIDDLE: Whether the previous draw was in the middle
  (MIDDLE command).

For implementation details, see ``do_cmd()`` in
``codification.c``. Currently, ``MASK_PREVIOUS_BIT`` and
``MASK_HAS_PREVIOUS`` are not being used.

For codification commands and their drawing commands, see
``codmod.c``.

Modulation
----------

The ``sin()`` function is used to generate the sine wave.
See ``get_sin()`` in ``modulation.c``.

For better drawing resolution, a single line is split in
three levels. The character ' is used for the top, - for
the middle, and . for the bottom. See ``print_graph()``
in ``modulation.c``.
