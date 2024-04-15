#include "s21_smartcalc.h"

int main(int argc, char **argv) {
  GtkApplication *app = gtk_application_new("com.example.GtkApplication",
                                            G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(mode_activate), NULL);
  int status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);
  return status;
}

void mode_activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *window;
  GtkWidget *button1, *button2, *button3;
  GtkWidget *box, *page1, *page2, *page3, *button;
  GtkWidget *label;
  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Меню");
  gtk_window_set_default_size(GTK_WINDOW(window), 500, 300);
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_window_destroy), NULL);
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_window_set_child(GTK_WINDOW(window), box);
  button1 = gtk_button_new_with_label("SmartCalc v1.0");
  g_signal_connect(button1, "clicked", G_CALLBACK(button1_clicked), NULL);
  gtk_box_append(GTK_BOX(box), button1);
  button2 = gtk_button_new_with_label("Кредитный калькулятор");
  g_signal_connect(button2, "clicked", G_CALLBACK(button2_clicked), NULL);
  gtk_box_append(GTK_BOX(box), button2);
  button3 = gtk_button_new_with_label("Депозитный калькулятор");
  g_signal_connect(button3, "clicked", G_CALLBACK(button3_clicked), NULL);
  gtk_box_append(GTK_BOX(box), button3);
  label = gtk_label_new("Введите необходимые параметры:");
  gtk_widget_set_margin_top(label, 20);
  gtk_box_append(GTK_BOX(box), label);
  stack = GTK_STACK(gtk_stack_new());
  gtk_box_append(GTK_BOX(box), GTK_WIDGET(stack));
  page1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_stack_add_named(stack, page1, "page1");
  button1_processing(page1, button1);
  page2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_stack_add_named(stack, page2, "page2");
  button2_processing(page2);
  page3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_stack_add_named(stack, page3, "page3");
  button3_processing(page3);
  gtk_widget_show(window);
}

void button1_processing(GtkWidget *page1, GtkWidget *button) {
  GtkWidget *info1, *info2, *info3, *info4;
  info1 = gtk_entry_new();
  gtk_widget_set_size_request(info1, 450, 50);
  gtk_entry_set_placeholder_text(GTK_ENTRY(info1), "Введите выражение");
  gtk_box_append(GTK_BOX(page1), info1);
  info2 = gtk_entry_new();
  gtk_widget_set_size_request(info2, 450, 50);
  gtk_entry_set_placeholder_text(GTK_ENTRY(info2), "Введите x");
  gtk_box_append(GTK_BOX(page1), info2);
  info3 = gtk_entry_new();
  gtk_widget_set_size_request(info3, 450, 50);
  gtk_entry_set_placeholder_text(
      GTK_ENTRY(info3), "Введите область определения формате (x_min;x_max)");
  gtk_box_append(GTK_BOX(page1), info3);
  info4 = gtk_entry_new();
  gtk_widget_set_size_request(info4, 450, 50);
  gtk_entry_set_placeholder_text(
      GTK_ENTRY(info4), "Введите область значений формате (y_min;y_max)");
  gtk_box_append(GTK_BOX(page1), info4);
  inputdata_ty *data = g_malloc(sizeof(inputdata_ty));
  data->info1 = info1;
  data->info2 = info2;
  data->info3 = info3;
  data->info4 = info4;
  data->info5 = NULL;
  data->info6 = NULL;
  data->info7 = NULL;
  button = gtk_button_new_with_label("=");
  g_signal_connect(button, "clicked", G_CALLBACK(draw_graph_callback), data);
  gtk_box_append(GTK_BOX(page1), button);
}

void button2_processing(GtkWidget *page2) {
  GtkWidget *sum, *term, *percent;
  GtkWidget *annuity, *different;
  sum = gtk_entry_new();
  gtk_widget_set_size_request(sum, 450, 50);
  gtk_entry_set_placeholder_text(GTK_ENTRY(sum), "Введите общую сумму кредита");
  gtk_box_append(GTK_BOX(page2), sum);
  term = gtk_entry_new();
  gtk_widget_set_size_request(term, 450, 50);
  gtk_entry_set_placeholder_text(GTK_ENTRY(term), "Введите срок кредита");
  gtk_box_append(GTK_BOX(page2), term);
  percent = gtk_entry_new();
  gtk_widget_set_size_request(percent, 450, 50);
  gtk_entry_set_placeholder_text(GTK_ENTRY(percent),
                                 "Введите процентную ставку кредита");
  gtk_box_append(GTK_BOX(page2), percent);
  inputdata_ty *data = g_malloc(sizeof(inputdata_ty));
  data->info1 = sum;
  data->info2 = term;
  data->info3 = percent;
  data->info4 = NULL;
  data->info5 = NULL;
  data->info6 = NULL;
  data->info7 = NULL;
  annuity = gtk_button_new_with_label("Аннуитетный кредит");
  g_signal_connect(annuity, "clicked", G_CALLBACK(annuity_loan_callback), data);
  gtk_box_append(GTK_BOX(page2), annuity);
  different = gtk_button_new_with_label("Дифференцированный кредит");
  g_signal_connect(different, "clicked", G_CALLBACK(differented_loan_callback),
                   data);
  gtk_box_append(GTK_BOX(page2), different);
}

void button3_processing(GtkWidget *page3) {
  GtkWidget *sum, *term, *percent, *tax, *period, *in_list, *out_list, *button;
  add_button3_field(&sum, &page3, 1);
  add_button3_field(&term, &page3, 2);
  add_button3_field(&percent, &page3, 3);
  add_button3_field(&tax, &page3, 4);
  add_button3_field(&period, &page3, 5);
  GtkWidget *toggle_button =
      gtk_toggle_button_new_with_label("Капитализация процентов");
  g_signal_connect(toggle_button, "toggled", G_CALLBACK(toggle_button_toggled),
                   NULL);
  gtk_box_append(GTK_BOX(page3), toggle_button);
  add_button3_field(&in_list, &page3, 6);
  add_button3_field(&out_list, &page3, 7);
  inputdata_ty *data = g_malloc(sizeof(inputdata_ty));
  data->info1 = sum;
  data->info2 = term;
  data->info3 = percent;
  data->info4 = tax;
  data->info5 = period;
  data->info6 = in_list;
  data->info7 = out_list;
  button = gtk_button_new_with_label("=");
  g_signal_connect(button, "clicked", G_CALLBACK(deposit_callback), data);
  gtk_box_append(GTK_BOX(page3), button);
}

void add_button3_field(GtkWidget **widget, GtkWidget **page3, int type) {
  char *str;
  if (type == 1) {
    str = "Введите сумму вклада";
  } else if (type == 2) {
    str = "Введите срок размещения";
  } else if (type == 3) {
    str = "Введите процентную ставку";
  } else if (type == 4) {
    str = "Введите налоговую ставку";
  } else if (type == 5) {
    str = "Введите периодичность выплат";
  } else if (type == 6) {
    str = "Введите список пополнений (через ;)";
  } else if (type == 7) {
    str = "Введите список частичных снятий (через ;)";
  }
  *widget = gtk_entry_new();
  gtk_widget_set_size_request(*widget, 450, 50);
  gtk_entry_set_placeholder_text(GTK_ENTRY(*widget), str);
  gtk_box_append(GTK_BOX(*page3), *widget);
}