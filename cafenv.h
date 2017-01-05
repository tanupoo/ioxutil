#ifndef __cafenv_H__
#define __cafenv_H__

void ioxutil_cafenv_dump(void);
int ioxutil_config_load(void);
int ioxutil_config_get(char *, char *, char **, char *);
int ioxutil_config_getint(char *, char *, int *, int);
int ioxutil_init(void);

#endif

