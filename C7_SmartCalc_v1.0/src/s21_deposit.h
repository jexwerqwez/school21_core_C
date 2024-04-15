#ifndef S21_DEPOSIT_H_
#define S21_DEPOSIT_H_
#include <gtk/gtk.h>

#include "s21_calculation.h"
#include "s21_check.h"
#include "s21_graph.h"
#include "s21_stack.h"

void deposit_callback(GtkWidget *, gpointer);
double interest_charges(double, const char *, const char *, const char *);
double tax_sum(double, const char *);
double deposit_amount(double, double, double);
void main_deposit_function(const char *, const char *, const char *,
                           const char *, const char *, const char *,
                           const char *, GtkWidget **);
double sum_of_list(const char *);
double deposit_modification(const char *, double, double);
void toggle_button_toggled(GtkToggleButton *, gpointer);
bool check_button3(const char *, const char *, const char *, const char *,
                   const char *, const char *, const char *);
#endif  // S21_DEPOSIT_H_