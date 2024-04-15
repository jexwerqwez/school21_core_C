#include <ctype.h>
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int parser(int n, char **v, FILE *);
int i_flag(char *, char *, regex_t, int);
int v_flag(char *, char *, int, int, int);
void o_flag(char *, char *, char *, int, int, int);
void write_files(int, int, char **, FILE *, FILE *, int *);
int check_for_f_in_row(char *row);
int check_for_e_in_row(char *row);
void add_line_tr(char *tem);

int main(int argc, char *argv[]) {
  int filecount = 0, n_flag = 0, c_flag = 0, l_flag = 0, vflag = 0;
  int counter = 0, c = 0;
  ssize_t readfile, readtem, readfpins;
  size_t lenfile = 0, len_fpins = 0, lentem = 0;
  regex_t myre;
  char *linefile = NULL, *line_fpins = NULL, *line_tem = NULL;
  FILE *fp_inside = NULL;
  FILE *temfp = fopen("tem", "a+");
  FILE *filefp = fopen("file", "a+");
  int rez = parser(argc, argv, temfp);
  int iteration = 0;
  write_files(argc, rez, argv, temfp, filefp, &filecount);
  fseek(temfp, 0, SEEK_SET);
  fseek(filefp, 0, SEEK_SET);
  while ((readfile = getline(&linefile, &lenfile, filefp)) != -1) {
    for (char *p = linefile; *p != '\0'; p++) {
      if (*p == '\n') linefile[counter] = '\0';
      counter++;
    }
    l_flag = 0;
    c_flag = 0;
    n_flag = 0;
    fp_inside = fopen(linefile, "r");
    while ((readfpins = getline(&line_fpins, &len_fpins, fp_inside)) != -1) {
      vflag = 0;
      iteration = 0;
      n_flag++;
      fseek(temfp, 0, SEEK_SET);
      int regex_result = 0;
      while ((readtem = getline(&line_tem, &lentem, temfp)) != -1) {
        iteration++;
        c = 0;
        for (char *p = line_tem; *p != '\0'; p++) {
          if (*p == '\n') line_tem[c] = '\0';
          c++;
        }
        if ((rez & 512) && ((rez & 1) == 0) && ((rez & 8) == 0) &&
            ((rez & 16) == 0))
          o_flag(line_tem, line_fpins, linefile, rez, n_flag, filecount);
        regex_result = i_flag(line_tem, line_fpins, myre, rez);
        if (regex_result == 1) {
          if ((rez & 16) == 0) {
            if ((rez & 8) == 0) {
              if (filecount == 1 || (rez & 64) != 0) {
                if (rez & 32) {
                  printf("%d:%s", n_flag, line_fpins);
                  add_line_tr(line_fpins);
                } else {
                  printf("%s", line_fpins);
                  add_line_tr(line_fpins);
                }
              } else {
                if (rez & 32) {
                  printf("%s:%d:%s", linefile, n_flag, line_fpins);
                  add_line_tr(line_fpins);
                } else {
                  printf("%s:%s", linefile, line_fpins);
                  add_line_tr(line_fpins);
                }
              }
            } else if (rez & 8) {
              c_flag++;
              break;
            }
            break;
          } else if (rez & 16) {
            if (rez & 8) c_flag++;
            l_flag++;
            break;
          }
        } else if (regex_result == -1)
          vflag++;
      }
      if (((rez & 1) != 0) && (vflag == iteration) && ((rez & 512) == 0)) {
        int br = v_flag(line_fpins, linefile, rez, filecount, n_flag);
        if (br == -2) {
          l_flag++;
          break;
        }
        if (br == -1) {
          c_flag++;
        }
      }
      if ((rez & 16) && (rez & 8) && (l_flag != 0)) break;
    }
    fclose(fp_inside);
    counter = 0;
    if ((rez & 8) && (rez & 16)) printf("%d\n", c_flag);
    if ((rez & 8) && (rez & 16) == 0) {
      if (rez & 1) {
        if (filecount != 1)
          printf("%s:%d\n", linefile, c_flag);
        else if (filecount == 1 || rez & 64)
          printf("%d\n", c_flag);
      } else {
        if (filecount != 1)
          printf("%s:%d\n", linefile, c_flag);
        else if (filecount == 1 || rez & 64)
          printf("%d\n", c_flag);
      }
    }
    if (((rez & 16) != 0) && (l_flag != 0)) printf("%s\n", linefile);
  }
  if (linefile) free(linefile);
  if (line_fpins) free(line_fpins);
  if (line_tem) free(line_tem);
  fclose(temfp);
  fclose(filefp);
  remove("tem");
  remove("file");
  return 0;
}
void add_line_tr(char *tem) {
  int line_tr = 0;
  for (char *p = tem;; p++) {
    if (*p == '\0') {
      if (line_tr == 0) putchar('\n');
      break;
    }
    if (*p == '\n') line_tr = 1;
  }
}
void write_files(int argc, int opt, char *argv[], FILE *temfp, FILE *filefp,
                 int *filecount) {
  int n_eflag = 0;
  if (opt & 256) n_eflag++;
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '-') {
      if (check_for_f_in_row(argv[i - 1]) == 2) {
        FILE *readfp = NULL;
        if ((readfp = fopen(argv[i], "r")) != NULL) {
          ssize_t read;
          size_t len = 0;
          char *line = NULL;
          while ((read = getline(&line, &len, readfp)) != -1) {
            fprintf(temfp, "%s", line);
          }
          fclose(readfp);
          if (line) free(line);
        } else {
          if (!(opt & 128))
            fprintf(stderr, "grep: %s: No such file or directory\n", argv[i]);
          break;
        }
      } else {
        if (((opt & 4) == 0) && (n_eflag == 0)) {
          fprintf(temfp, "%s\n", argv[i]);
          n_eflag++;
        } else {
          if (check_for_e_in_row(argv[i - 1]) != 2) {
            FILE *readfilefp = NULL;
            if ((readfilefp = fopen(argv[i], "r")) != NULL) {
              fprintf(filefp, "%s\n", argv[i]);
              fclose(readfilefp);
              (*filecount)++;
            } else {
              if (!(opt & 128)) {
                fprintf(stderr, "grep: %s: No such file or directory\n",
                        argv[i]);
              }
              (*filecount)++;
            }
          }
        }
      }
    }
  }
}

int check_for_f_in_row(char *row) {
  int flag = 0;
  if (*row == '-') {
    flag = 1;
  }
  if (flag) {
    for (char *p = row; *p != '\0'; p++) {
      if (*p == 'f') {
        flag = 2;
      }
    }
  }
  return flag;
}

int check_for_e_in_row(char *row) {
  int flag = 0;
  if (*row == '-') {
    flag = 1;
  }
  if (flag) {
    for (char *p = row; *p != '\0'; p++) {
      if (*p == 'e') {
        flag = 2;
      }
    }
  }
  return flag;
}

int i_flag(char *tem, char *preg, regex_t myre, int flags) {
  int rez = 0, regrez = 0;
  if ((flags & 2) == 0) {
    regcomp(&myre, tem, REG_EXTENDED);
  } else {
    regcomp(&myre, tem, REG_ICASE);
  }
  regrez = regexec(&myre, preg, 0, NULL, 0);
  if ((regrez == 0) && ((flags & 1) == 0)) {
    rez = 1;
  } else if (regrez == REG_NOMATCH) {
    rez = -1;
  }
  regfree(&myre);
  return rez;
}

void o_flag(char *tem, char *line, char *file, int flags, int n_flag,
            int filecount) {
  char *tmpstr = NULL;
  while (strstr(line, tem)) {
    tmpstr = strstr(line, tem);
    if (tmpstr)
      for (int i = 0; i < (int)strlen(tem); i++)
        for (int j = 0; j < (int)strlen(line); j++) {
          tmpstr[j] = tmpstr[j + 1];
        }
    if (filecount == 1 || (flags & 64) != 0) {
      if (flags & 32) printf("%d:", n_flag);
      printf("%s", tem);
      add_line_tr(tem);
    } else {
      printf("%s:", file);
      if (flags & 32) printf("%d:", n_flag);
      printf("%s", tem);
      add_line_tr(tem);
    }
  }
}

int v_flag(char *tem, char *file, int flags, int filecount, int n_flag) {
  int v_combo = 1;
  if ((((flags & 8) == 0) && (flags & 16) == 0)) {
    if (filecount == 1 || (flags & 64) != 0) {
      if (flags & 32) {
        printf("%d:", n_flag);
      }
      printf("%s", tem);
      add_line_tr(tem);
    } else {
      printf("%s:", file);
      if (flags & 32) printf("%d:", n_flag);
      printf("%s", tem);
      add_line_tr(tem);
    }
  } else {
    if (flags & 8) v_combo = -1;
    if (flags & 16) v_combo = -2;
  }
  return v_combo;
}
int parser(int n, char **v, FILE *tem) {
  int opt;
  int p = 0;
  const struct option long_options[] = {{0, 0, 0, 0}};
  while ((opt = getopt_long(n, v, "-e:ivclnhsfo", long_options, NULL)) != -1) {
    switch (opt) {
      case 'e':
        p |= 4;
        fprintf(tem, "%s\n", optarg);
        break;
      case 'i':
        p |= 2;
        break;
      case 'v':
        p |= 1;
        break;
      case 'c':
        p |= 8;
        break;
      case 'l':
        p |= 16;
        break;
      case 'n':
        p |= 32;
        break;
      case 'h':
        p |= 64;
        break;
      case 's':
        p |= 128;
        break;
      case 'f':
        p |= 256;
        break;
      case 'o':
        p |= 512;
        break;
      default:
        break;
    }
  }
  return p;
}
