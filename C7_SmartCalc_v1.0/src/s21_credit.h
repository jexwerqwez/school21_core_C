#ifndef S21_CREDIT_H_
#define S21_CREDIT_H_
#include <gtk/gtk.h>

#include "s21_calculation.h"
#include "s21_check.h"
#include "s21_graph.h"
#include "s21_stack.h"

double annuity_loan(const char *, const char *, const char *, double *);
double differented_loan(const char *, const char *, const char *, int,
                        double *);
double loan_overpayment(const char *, double);
void differented_loan_callback(GtkWidget *, gpointer);
void annuity_loan_callback(GtkWidget *, gpointer);
bool check_button2(const char *, const char *, const char *);
#endif  // S21_CREDIT_H_