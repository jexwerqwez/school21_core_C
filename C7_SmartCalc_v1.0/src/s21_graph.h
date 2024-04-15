#ifndef S21_GRAPH_H_
#define S21_GRAPH_H_
#include <gtk/gtk.h>

#include "s21_calculation.h"
#include "s21_check.h"
#include "s21_stack.h"

typedef struct s21_inputdata {
  GtkWidget *info1;
  GtkWidget *info2;
  GtkWidget *info3;
  GtkWidget *info4;
  GtkWidget *info5;
  GtkWidget *info6;
  GtkWidget *info7;
} inputdata_ty;

typedef struct s21_scale {
  double x_min;
  double x_max;
  double y_min;
  double y_max;
} scale_ty;

typedef struct s21_coordinate {
  double x;
  double y;
  double x_prev;
  double y_prev;
} coordinate_ty;

bool not_definition_area(const char *, double);
void first_draw_processing(cairo_t *, int, int, scale_ty *, coordinate_ty *,
                           bool);
bool second_draw_processing(cairo_t *cr, bool, int, int, scale_ty *,
                            coordinate_ty *, bool);
bool is_second_dp(const char *);
bool check_button1(const char *, const char *, const char *, const char *);
void draw_function(cairo_t *, scale_ty *, const char *, int, int);
void draw_graph(GtkDrawingArea *, cairo_t *, int, int, gpointer);
void draw_graph_callback(GtkWidget *, gpointer);
void initialize_scale(const char *, const char *);
void activate(GtkApplication *);
void draw_coordinate_system(cairo_t *, int, int);
char *error_message();
#endif