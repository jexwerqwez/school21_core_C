#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int parser(int n, char **v);
void no_flag(FILE *, int);
void b_flag(FILE *, FILE *);
void e_flag(FILE *, FILE *);
void n_flag(FILE *, FILE *);
void s_flag(FILE *, FILE *);
void t_flag(FILE *, FILE *);
void v_flag(FILE *, FILE *);
FILE *read_file(int);
FILE *write_file(int);
int main(int argc, char *argv[]) {
  int len = 0, flag = 0, counter = 0, active_b_flag = 0;
  if (argc < 2) return -1;
  int args = argc;
  for (int i = 0; i < args; i++) {
    if (strchr(argv[i], '-') &&
        (strchr(argv[i], 'b') || strchr(argv[i], 'e') || strchr(argv[i], 'n') ||
         strchr(argv[i], 's') || strchr(argv[i], 't') ||
         strchr(argv[i], 'v'))) {
      continue;
    } else {
      if (flag == 0) flag = i;
      len++;
    }
  }
  len -= 1;
  if ((argc = parser(argc, argv)) == 0) {
    for (int i = flag; i < args; i++) {
      FILE *fp = fopen(argv[i], "r");
      if (fp == NULL) {
        perror("cat");
      } else {
        no_flag(fp, -1);
        fclose(fp);
      }
    }
  } else {
    for (int i = flag; i < args; i++) {
      counter = 0;
      FILE *readfp = fopen(argv[i], "r");
      FILE *writefp;
      if (readfp == NULL) {
        perror("cat");
      } else {
        if (argc & 1 || argc & 64) {
          writefp = write_file(counter);
          if (counter != 0) readfp = read_file(counter);
          t_flag(readfp, writefp);
          counter++;
        }
        if (argc & 2) {
          if (counter != 0) readfp = read_file(counter);
          writefp = write_file(counter);
          s_flag(readfp, writefp);
          counter++;
        }
        if (argc & 4) {
          if (counter != 0) readfp = read_file(counter);
          writefp = write_file(counter);
          b_flag(readfp, writefp);
          active_b_flag = 1;
          counter++;
        }
        if (argc & 8 || argc & 128) {
          if (counter != 0) readfp = read_file(counter);
          writefp = write_file(counter);
          e_flag(readfp, writefp);
          counter++;
        }
        if (argc & 16 && !active_b_flag) {
          if (counter != 0) readfp = read_file(counter);
          writefp = write_file(counter);
          n_flag(readfp, writefp);
          counter++;
        }
        if (argc & 32 || argc & 8 || argc & 1) {
          if (counter != 0) readfp = read_file(counter);
          writefp = write_file(counter);
          v_flag(readfp, writefp);
          counter++;
        }
        no_flag(writefp, counter);
      }
    }
  }
  return 0;
}

FILE *read_file(int counter) {
  FILE *tmpfp1 = fopen("temp1", "r");
  FILE *tmpfp2 = fopen("temp2", "r");
  if (counter % 2 == 0)
    return tmpfp2;
  else if (counter % 2 != 0)
    return tmpfp1;
  return NULL;
}
FILE *write_file(int counter) {
  if (counter % 2 == 0) {
    FILE *tmpfp1 = fopen("temp1", "w+");
    return tmpfp1;
  } else if (counter % 2 != 0) {
    FILE *tmpfp2 = fopen("temp2", "w+");
    return tmpfp2;
  }
  return NULL;
}

void no_flag(FILE *fp, int counter) {
  int ch;
  if (counter != -1) {
    if (counter % 2 == 0)
      fp = fopen("temp2", "r");
    else
      fp = fopen("temp1", "r");
  }
  while (!feof(fp)) {
    ch = getc(fp);
    if (ch != EOF) putchar(ch);
  }
  fclose(fp);
  remove("temp1");
  remove("temp2");
}
void b_flag(FILE *readfp, FILE *writefp) {
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int counter = 1;
  while ((read = getline(&line, &len, readfp)) != -1) {
    if (*line == '\0' || *line == '\n') {
      fprintf(writefp, "%s", line);
    } else {
      fprintf(writefp, "%6d\t%s", counter, line);
      counter++;
    }
  }
  if (line) free(line);
  fclose(readfp);
  fclose(writefp);
}
void e_flag(FILE *readfp, FILE *writefp) {
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  while ((read = getline(&line, &len, readfp)) != -1) {
    for (char *p = line; *p != '\0'; p++) {
      if (*p == '\n') fputc('$', writefp);
      fprintf(writefp, "%c", *p);
    }
  }
  if (line) free(line);
  fclose(readfp);
  fclose(writefp);
}
void n_flag(FILE *readfp, FILE *writefp) {
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int counter = 1;
  while ((read = getline(&line, &len, readfp)) != -1) {
    fprintf(writefp, "%6d\t%s", counter, line);
    counter++;
  }
  if (line) free(line);
  fclose(readfp);
  fclose(writefp);
}
void s_flag(FILE *readfp, FILE *writefp) {
  char ch, prev;
  int flag = 0;
  for (prev = '\n'; (ch = getc(readfp)) != EOF; prev = ch) {
    if (prev == '\n' && ch == '\n') {
      flag = 1;
      continue;
    } else {
      if (flag) {
        fputc('\n', writefp);
        flag = 0;
      }
      fputc(ch, writefp);
    }
  }
  fclose(readfp);
  fclose(writefp);
}
void t_flag(FILE *readfp, FILE *writefp) {
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  while ((read = getline(&line, &len, readfp)) != -1) {
    for (char *p = line; *p != '\0'; p++) {
      if (*p == '\t') {
        fprintf(writefp, "^I");
        continue;
      }
      fprintf(writefp, "%c", *p);
    }
  }
  if (line) free(line);
  fclose(readfp);
  fclose(writefp);
}

void v_flag(FILE *readfp, FILE *writefp) {
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  while ((read = getline(&line, &len, readfp)) != -1) {
    for (char *p = line; *p != '\0'; p++) {
      if ((int)*p == 127) {
        fprintf(writefp, "^%c", 63);
        continue;
      }
      if ((int)*p < 32 && (int)*p >= 0 && *p != '\n' && *p != '\t') {
        fprintf(writefp, "^%c", (int)*p + 64);
        continue;
      }
      fprintf(writefp, "%c", *p);
    }
  }
  if (line) free(line);
  fclose(readfp);
  fclose(writefp);
}

int parser(int n, char **v) {
  int opt;
  int p = 0;
  const struct option long_options[] = {{"number-nonblank", no_argument, &p, 4},
                                        {"number", no_argument, &p, 16},
                                        {"squeeze-blank", no_argument, &p, 2},
                                        {NULL, 0, NULL, 0}};
  while ((opt = getopt_long(n, v, "-benstvET", long_options, NULL)) != EOF) {
    switch (opt) {
      case 'b':
        p |= 4;
        break;
      case 'e':
        p |= 8;
        break;
      case 'n':
        p |= 16;
        break;
      case 's':
        p |= 2;
        break;
      case 't':
        p |= 1;
        break;
      case 'v':
        p |= 32;
        break;
      case 'T':
        p |= 64;
        break;
      case 'E':
        p |= 128;
        break;
      default:
        break;
    }
  }
  return p;
}
