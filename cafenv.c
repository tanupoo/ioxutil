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

//static int f_debug = 0;

static struct tini_base *ioxutil_config_base = NULL;

#define IOXUTIL_CAFENV_DEF(name) static char *g_##name

#define IOXUTIL_CAFENV_GET(name) { \
	g_##name = getenv(#name); \
	if (g_##name == NULL) { \
		printf("ERROR: %s is not defined.\n", #name); \
		return -1; \
	} \
}

#define IOXUTIL_CAFENV_PRINT(name) printf("%s = %s\n", #name, g_##name)

IOXUTIL_CAFENV_DEF(CAF_APP_PERSISTENT_DIR);
IOXUTIL_CAFENV_DEF(CAF_APP_LOG_DIR);
IOXUTIL_CAFENV_DEF(CAF_APP_CONFIG_FILE);
IOXUTIL_CAFENV_DEF(CAF_APP_CONFIG_DIR);
IOXUTIL_CAFENV_DEF(CAF_APP_USERNAME);
IOXUTIL_CAFENV_DEF(CAF_HOME);
IOXUTIL_CAFENV_DEF(CAF_HOME_ABS_PATH);
IOXUTIL_CAFENV_DEF(CAF_APP_PATH);
IOXUTIL_CAFENV_DEF(CAF_MODULES_PATH);
IOXUTIL_CAFENV_DEF(CAF_APP_DIR);
IOXUTIL_CAFENV_DEF(CAF_MODULES_DIR);
IOXUTIL_CAFENV_DEF(CAF_APP_ID);

void
ioxutil_cafenv_dump(void)
{
	IOXUTIL_CAFENV_PRINT(CAF_APP_PERSISTENT_DIR);
	IOXUTIL_CAFENV_PRINT(CAF_APP_LOG_DIR);
	IOXUTIL_CAFENV_PRINT(CAF_APP_CONFIG_FILE);
	IOXUTIL_CAFENV_PRINT(CAF_APP_CONFIG_DIR);
	IOXUTIL_CAFENV_PRINT(CAF_APP_USERNAME);
	IOXUTIL_CAFENV_PRINT(CAF_HOME);
	IOXUTIL_CAFENV_PRINT(CAF_HOME_ABS_PATH);
	IOXUTIL_CAFENV_PRINT(CAF_APP_PATH);
	IOXUTIL_CAFENV_PRINT(CAF_MODULES_PATH);
	IOXUTIL_CAFENV_PRINT(CAF_APP_DIR);
	IOXUTIL_CAFENV_PRINT(CAF_MODULES_DIR);
	IOXUTIL_CAFENV_PRINT(CAF_APP_ID);
}

char *
ioxutil_set_logfile(char *file)
{
	char *path;
	int path_len = 1024;

	if ((path = malloc(path_len)) == NULL)
		err(1, "ERROR: malloc(logfile)");

	snprintf(path, path_len, "%s/%s", g_CAF_APP_LOG_DIR, file);

	return path;
}

/*
 * "spark", "server_url", &g_server_url, NULL);
 */
int
ioxutil_config_get(char *section, char *key, char **dest, char *init)
{
	*dest = tini_get_v(ioxutil_config_base, section, key);
	if (*dest == NULL) {
		if (init != NULL) {
			*dest = init;
			return 0;
		}
		return -1;
	}

	return 0;
}

/*
 * "spark", "frequency", &g_frequency, 60);
 */
int
ioxutil_config_getint(char *sect, char *key, int *dest, int init)
{
	char tmp[128];
	if (ioxutil_config_get(section, key, *tmp, "") < 0)
		return -1;

	if (tmp[0] == '\0') {
		*dest = init;
		return 0;
	}

	*dest = strtol(tmp, &bp, 10);
	if (*bp == '\0')
		return -1;

	return 0;
}

int
ioxutil_config_load(void)
{
	char *path;
	int path_len = 1024;
	int len;

	if ((path = malloc(path_len)) == NULL)
		err(1, "ERROR: malloc(conf_file)");

	snprintf(path, path_len, "%s/%s",
			g_CAF_APP_PATH, g_CAF_APP_CONFIG_FILE);

	tini_parse_cb(path, ioxutil_config_handler);
	if (tini_parse(path, ioxutil_config_base) < 0)
		err(1, "ERROR: failed to load %s", path);

	return 0;
}

int
ioxutil_init(void)
{
	IOXUTIL_CAFENV_GET(CAF_APP_PERSISTENT_DIR);
	IOXUTIL_CAFENV_GET(CAF_APP_LOG_DIR);
	IOXUTIL_CAFENV_GET(CAF_APP_CONFIG_FILE);
	IOXUTIL_CAFENV_GET(CAF_APP_CONFIG_DIR);
	IOXUTIL_CAFENV_GET(CAF_APP_USERNAME);
	IOXUTIL_CAFENV_GET(CAF_HOME);
	IOXUTIL_CAFENV_GET(CAF_HOME_ABS_PATH);
	IOXUTIL_CAFENV_GET(CAF_APP_PATH);
	IOXUTIL_CAFENV_GET(CAF_MODULES_PATH);
	IOXUTIL_CAFENV_GET(CAF_APP_DIR);
	IOXUTIL_CAFENV_GET(CAF_MODULES_DIR);
	IOXUTIL_CAFENV_GET(CAF_APP_ID);

	return 0;
}
