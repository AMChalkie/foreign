#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "regexp9.h"

struct x
{
	char *re;
	char *s;
	Reprog *p;
};

struct x t[] = {
	{ "^[^!@]+$", "/bin/upas/aliasmail '&'", 0 },
	{ "^local!(.*)$", "/mail/box/\\1/mbox", 0 },
	{ "^plan9!(.*)$", "\\1", 0 },
	{ "^helix!(.*)$", "\\1", 0 },
	{ "^([^!]+)@([^!@]+)$", "\\2!\\1", 0 },
	{ "^(uk\\.[^!]*)(!.*)$", "/bin/upas/uk2uk '\\1' '\\2'", 0 },
	{ "^[^!]*\\.[^!]*!.*$", "inet!&", 0 },
	{ "^\xE2\x98\xBA$", "smiley", 0 },
	{ "^(coma|research|pipe|pyxis|inet|hunny|gauss)!(.*)$", "/mail/lib/qmail '\\s' 'net!\\1' '\\2'", 0 },
	{ "^.*$", "/mail/lib/qmail '\\s' 'net!research' '&'", 0 },
	{ 0, 0, 0 },
};

int main(int ac, char **av)
{
	Resub rs[10];
	char dst[128];
	struct x *tp;

	if (ac == 1) {
		fprintf(stderr, "Usage: %s <string>\n", av[0]);
		return 1;
	}

	for(tp = t; tp->re; tp++)
		tp->p = regcomp9(tp->re);

	for(tp = t; tp->re; tp++){
		printf("%s VIA %s", av[1], tp->re);
		memset(rs, 0, sizeof rs);
		if(regexec9(tp->p, av[1], rs, 10)){
			regsub9(tp->s, dst, sizeof dst, rs, 10);
			printf(" sub %s -> %s", tp->s, dst);
		}
		printf("\n");
	}
	return 0;
}
