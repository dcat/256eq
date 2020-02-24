#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include "arg.h"
#include "256.h"


char *argv0;

void
usage(void) {
	printf("usage: %s <-n|-f|-b> <color>\n", argv0);
	exit(1);
}

int
distance(uint32_t *c1, uint32_t *c2) {
	struct rgb diff;
	struct rgb *p1 = (struct rgb *)c1;
	struct rgb *p2 = (struct rgb *)c2;

	diff.r = abs(p2->r - p1->r);
	diff.g = abs(p2->g - p1->g);
	diff.b = abs(p2->b - p1->b);

	return (diff.r * diff.r) + (diff.g * diff.g) + (diff.b * diff.b);
}

int
nearest(uint32_t c) {
	struct rgb *p;
	int i, dist, prev, index;

	index = -1;
	prev = INT_MAX;

	for (i = 16; i < sizeof(set)/sizeof(*set); i++) {
		p = (struct rgb *)&set[i];

		dist = distance(&set[i], &c);
		if (dist < prev) {
			prev = dist;
			index = i;
		}
	}

	return index;
}

int
main(int argc, char **argv) {
	ARGBEGIN {
	case '?':
	case 'h':
		usage();
		break;
	case 'f':
	case 'b':
		printf("\033[%d8;5;%dm",
				**argv == 'b' ? 4 : 3,
				nearest(strtoul(EARGF(usage()), NULL, 16))
		);
		break;
	case 'n':
		printf("%d\n", nearest(strtoul(EARGF(usage()), NULL, 16)));
		break;
	} ARGEND

	return 0;
}
