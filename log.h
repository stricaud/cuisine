#ifndef _LOG_H_
#define _LOG_H_

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#define LOG_LEVEL_DEBUG 1
#define LOG_LEVEL_CRIT 2
#define LOG_LEVEL_ERROR 3
#define LOG_LEVEL_WARNING 4
#define LOG_LEVEL_NOTICE 5
#define LOG_LEVEL_QUIET 6

static int log_level = LOG_LEVEL_WARNING;
static FILE *_fp = NULL; 

void log_set_level(int level)
{
  log_level = level;
}

void log_set_fp(FILE *fp)
{
  _fp = fp;
}

char *__get_time_now(void)
{
  time_t now;
  struct tm *now_tm;
  static char time_str[30];

  now = time(NULL);
  now_tm = localtime(&now);
  strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", now_tm);
  return time_str;
}

void __log_func(int level, char *fmt, ...)
{
  va_list ap;
  time_t now;
  
  if (level < log_level) return;
  if (!_fp) { _fp = stderr; }
  
  fprintf(_fp, "[%s] ", __get_time_now());
  
  va_start(ap, fmt);
  vfprintf(_fp, fmt, ap);
  va_end(ap);
}


#define log_debug(f, ...)   \
  __log_func(LOG_LEVEL_DEBUG,   f, ##__VA_ARGS__)
#define log_crit(f, ...)          \
  __log_func(LOG_LEVEL_CRIT,    f, ##__VA_ARGS__)
#define log_error(f, ...)   \
  __log_func(LOG_LEVEL_ERROR,   f, ##__VA_ARGS__)
#define log_warning(f, ...)   \
  __log_func(LOG_LEVEL_WARNING, f, ##__VA_ARGS__)
#define log_notice(f, ...)   \
  __log_func(LOG_LEVEL_NOTICE,  f, ##__VA_ARGS__)

void log_test()
{
  log_debug("debug:%d\n",123);
  log_crit("crit\n");
  log_error("error\n");
  log_warning("warning\n");
  log_notice("notice\n");
}

#endif // _LOG_H_
