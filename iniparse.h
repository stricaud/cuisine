struct _ini_t {
  char **keyvals;
  size_t keyvals_size;
  int n_items;
};
typedef struct _ini_t ini_t;

ini_t *ini_parse_file(char *filename);
ini_t *ini_parse_buffer(char *buf, long size);
char *ini_get_value(ini_t *ini, char *key);
void ini_free(ini_t *ini);
