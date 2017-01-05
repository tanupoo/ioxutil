/*
 * Copyright (C) 2016 Shoichi Sakane <sakane@tanu.org>, All rights reserved.
 * See the file LICENSE in the top level directory for more details.
 */
#include <sys/types.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <err.h>

#include "cafenv.h"

int f_debug = 0;

char *prog_name = NULL;

void
usage()
{
	printf(
"Usage: %s [-dh]\n"
	, prog_name);

	exit(0);
}

int
run()
{
	char *g_server_url;
	char *g_auth_key;
	char *g_room_id;
	int g_frequency;

	ioxutil_init();
	ioxutil_cafenv_dump();
	ioxutil_config_load();
	ioxutil_config_get("spark", "server_url", &g_server_url, NULL);
	ioxutil_config_get("spark", "auth_key", &g_auth_key, NULL);
	ioxutil_config_get("spark", "room_id", &g_room_id, NULL);
	ioxutil_config_getint("spark", "frequency", &g_frequency, 60);

	return 0;
}

int
main(int argc, char *argv[])
{
	int ch;

	prog_name = 1 + rindex(argv[0], '/');

	while ((ch = getopt(argc, argv, "dh")) != -1) {
		switch (ch) {
		case 'd':
			f_debug++;
			break;
		case 'h':
		default:
			usage();
			break;
		}
	}
	argc -= optind;
	argv += optind;

	if (argc > 0)
		usage();

	run();

	return 0;
}

