#ifndef SRC_S21_SMARTCALC_H_
#define SRC_S21_SMARTCALC_H_

#include "s21_credit.h"
#include "s21_deposit.h"
#include "s21_graph.h"

GtkStack *stack;

void add_button3_field(GtkWidget **, GtkWidget **, int);
void button1_processing(GtkWidget *, GtkWidget *);
void button2_processing(GtkWidget *);
void button3_processing(GtkWidget *);

void default_page(GtkWidget *widget, gpointer data) {
  gtk_stack_set_visible_child_name(stack, "Выберите режим калькулятора");
}

void button1_clicked(GtkWidget *widget, gpointer data) {
  gtk_stack_set_visible_child_name(stack, "page1");
}

void button2_clicked(GtkWidget *widget, gpointer data) {
  gtk_stack_set_visible_child_name(stack, "page2");
}

void button3_clicked(GtkWidget *widget, gpointer data) {
  gtk_stack_set_visible_child_name(stack, "page3");
}

void eq_clicked(GtkWidget *widget, gpointer data) {
  gtk_stack_set_visible_child_name(stack, "page4");
}

void mode_activate(GtkApplication *, gpointer);

void on_window_closed(GtkWindow *window, gpointer data) {
  GtkWidget *box = GTK_WIDGET(data);
  g_object_unref(box);
  gtk_window_destroy(window);
}
#endif  // SRC_S21_SMARTCALC_H_