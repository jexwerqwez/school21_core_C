#include "s21_graph.h"
#define STEP 0.001

scale_ty scale;

void initialize_scale(const char *areax, const char *areay) {
  double x1 = 0, x2 = 0, y1 = 0, y2 = 0;
  int flag = 0;
  if (strlen(areax) == 0) {
    scale.x_min = -10;
    scale.x_max = 10;
    flag = 1;
  }
  if (strlen(areay) == 0) {
    scale.y_min = -10;
    scale.y_max = 10;
    flag = 1;
  }
  if (!flag) {
    if ((sscanf(areax, "(%lf;%lf)", &x1, &x2) == 2) &&
        (sscanf(areax, "(%lf;%lf)", &y1, &y2) == 2)) {
      scale.x_min = x1;
      scale.x_max = x2;
      scale.y_min = y1;
      scale.y_max = y2;
    } else {
      error_message();
    }
  }
}

void draw_graph(GtkDrawingArea *area, cairo_t *cr, int width, int height,
                gpointer data) {
  const char *expression = data;
  draw_coordinate_system(cr, width, height);
  draw_function(cr, &scale, expression, width, height);
}

void draw_graph_callback(GtkWidget *widget, gpointer data) {
  inputdata_ty *inpdata = (inputdata_ty *)data;
  const char *expr = gtk_editable_get_text(GTK_EDITABLE(inpdata->info1));
  const char *x = gtk_editable_get_text(GTK_EDITABLE(inpdata->info2));
  const char *areax = gtk_editable_get_text(GTK_EDITABLE(inpdata->info3));
  const char *areay = gtk_editable_get_text(GTK_EDITABLE(inpdata->info4));
  GtkWidget *new_window;
  new_window = gtk_window_new();
  gtk_window_set_title(GTK_WINDOW(new_window), "SmartCalc:Calcucate");
  gtk_window_set_default_size(GTK_WINDOW(new_window), 400, 400);
  char *expr_copy = (char *)expr;
  replace_mod(expr_copy);
  if (check_button1(expr_copy, x, areax, areay)) {
    if (strchr(expr_copy, 'x') && (strlen(x) == 0)) {
      GtkWidget *drawing_area = gtk_drawing_area_new();
      initialize_scale(areax, areay);
      gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(drawing_area), draw_graph,
                                     (gpointer)expr_copy, NULL);
      gtk_window_set_child(GTK_WINDOW(new_window), drawing_area);
    } else {
      stack_ty *input_stack = NULL;
      stack_ty *reversed_stack = NULL;
      parser(expr, &input_stack);
      reverse_stack(input_stack, &reversed_stack);
      double number = calculate_rpn(&reversed_stack, atof(x));
      char str[255];
      sprintf(str, "%lf", number);
      GtkWidget *label = gtk_label_new(str);
      gtk_window_set_child(GTK_WINDOW(new_window), label);
      simple_destroy_stack(&input_stack);
      destroy_stack(&reversed_stack);
    }
  } else {
    GtkWidget *label = gtk_label_new(error_message());
    gtk_window_set_child(GTK_WINDOW(new_window), label);
  }
  gtk_widget_show(new_window);
}

void draw_function(cairo_t *cr, scale_ty *scale, const char *expression,
                   int width, int height) {
  gdk_cairo_set_source_rgba(
      cr, &(GdkRGBA){.red = 1.0, .green = 0.0, .blue = 0.0, .alpha = 1.0});
  stack_ty *input_stack = NULL;
  stack_ty *reversed_stack = NULL;
  parser(expression, &input_stack);
  reverse_stack(input_stack, &reversed_stack);
  bool first_valid_point = true, skipped = false;
  double y_threshold = 100;
  coordinate_ty *coordinate = malloc(sizeof(coordinate_ty));
  if (coordinate != NULL) {
    coordinate->x = 0;
    coordinate->y = 0;
    coordinate->x_prev = scale->x_min;
    coordinate->y_prev = calculate_rpn(&reversed_stack, coordinate->x_prev);
  }
  for (coordinate->x = scale->x_min + STEP; coordinate->x <= scale->x_max;
       coordinate->x += STEP) {
    if (not_definition_area(expression, coordinate->x)) {
      cairo_new_sub_path(cr);
      continue;
    }
    input_stack = NULL;
    reversed_stack = NULL;
    parser(expression, &input_stack);
    reverse_stack(input_stack, &reversed_stack);
    coordinate->y = calculate_rpn(&reversed_stack, coordinate->x);
    if (isinf(coordinate->y) || isinf(coordinate->x) || isnan(coordinate->x) ||
        isnan(coordinate->y)) {
      skipped = true;
      continue;
    }
    simple_destroy_stack(&input_stack);
    destroy_stack(&reversed_stack);
    if (is_second_dp(expression)) {
      first_valid_point = second_draw_processing(
          cr, first_valid_point, height, width, scale, coordinate, skipped);
    } else {
      if (fabs(coordinate->y - coordinate->y_prev) > y_threshold) {
        coordinate->x_prev = coordinate->x;
        coordinate->y_prev = coordinate->y;
        skipped = true;
        continue;
      }
      first_draw_processing(cr, width, height, scale, coordinate, skipped);
    }
    skipped = false;
  }
  cairo_stroke(cr);
  free(coordinate);
}

bool not_definition_area(const char *expression, double x) {
  double epsilon = STEP;
  return (strstr(expression, "tan") != NULL &&
          fabs(fmod(x + M_PI / 2, M_PI)) < epsilon) ||
         ((strstr(expression, "ln") != NULL || strstr(expression, "log")) &&
          (x <= 0 || fabs(x - 1) < epsilon)) ||
         (strstr(expression, "sqrt") != NULL && x < 0) ||
         ((strstr(expression, "asin") != NULL ||
           strstr(expression, "acos") != NULL) &&
          (x < -1 || x > 1)) ||
         (strstr(expression, "pow") != NULL &&
          x < 0 /*&& fmod(power, 1) != 0*/);
}

void draw_coordinate_system(cairo_t *cr, int width, int height) {
  gdk_cairo_set_source_rgba(
      cr, &(GdkRGBA){.red = 0.0, .green = 0.0, .blue = 0.0, .alpha = 1.0});
  cairo_move_to(cr, width / 2, 0);
  cairo_line_to(cr, width / 2, height);
  cairo_move_to(cr, 0, height / 2);
  cairo_line_to(cr, width, height / 2);
  cairo_stroke(cr);
}

void first_draw_processing(cairo_t *cr, int width, int height, scale_ty *scale,
                           coordinate_ty *coordinate, bool skipped) {
  if (!skipped) {
    cairo_line_to(
        cr,
        (coordinate->x - scale->x_min) * width / (scale->x_max - scale->x_min),
        height - (coordinate->y - scale->y_min) * height /
                     (scale->y_max - scale->y_min));
  } else {
    cairo_move_to(
        cr,
        (coordinate->x - scale->x_min) * width / (scale->x_max - scale->x_min),
        height - (coordinate->y - scale->y_min) * height /
                     (scale->y_max - scale->y_min));
  }
}

bool second_draw_processing(cairo_t *cr, bool first_valid_point, int height,
                            int width, scale_ty *scale,
                            coordinate_ty *coordinate, bool skipped) {
  if (!first_valid_point && !skipped) {
    cairo_line_to(
        cr,
        (coordinate->x - scale->x_min) * width / (scale->x_max - scale->x_min),
        height - (coordinate->y - scale->y_min) * height /
                     (scale->y_max - scale->y_min));
  } else {
    cairo_move_to(
        cr,
        (coordinate->x - scale->x_min) * width / (scale->x_max - scale->x_min),
        height - (coordinate->y - scale->y_min) * height /
                     (scale->y_max - scale->y_min));
    first_valid_point = false;
  }
  return first_valid_point;
}

bool is_second_dp(const char *expression) {
  return strstr(expression, "sqrt") != NULL ||
         strstr(expression, "log") != NULL ||
         strstr(expression, "ln") != NULL ||
         strstr(expression, "acos") != NULL ||
         strstr(expression, "asin") != NULL;
}

bool check_button1(const char *expr, const char *x, const char *areax,
                   const char *areay) {
  return (is_valid_expression(expr) && strlen(expr) < 256 && strlen(x) < 256 &&
          strlen(areax) < 256 && strlen(areay) < 256 && strlen(expr) != 0);
}

char *error_message() { return "Ошибка ввода!\n"; }