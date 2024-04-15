#include "s21_credit.h"

void differented_loan_callback(GtkWidget *widget, gpointer data) {
  inputdata_ty *inpdata = (inputdata_ty *)data;
  GtkWidget *new_window;
  new_window = gtk_window_new();
  gtk_window_set_title(GTK_WINDOW(new_window),
                       "SmartCalc:Дифференцированные платежи");
  gtk_window_set_default_size(GTK_WINDOW(new_window), 400, 400);
  const char *sum = gtk_editable_get_text(GTK_EDITABLE(inpdata->info1));
  const char *term = gtk_editable_get_text(GTK_EDITABLE(inpdata->info2));
  const char *percent = gtk_editable_get_text(GTK_EDITABLE(inpdata->info3));
  double pay = 0;
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  if (check_button2(sum, term, percent)) {
    GtkWidget *label = gtk_label_new(error_message());
    gtk_window_set_child(GTK_WINDOW(new_window), label);
  } else {
    char str[255];
    for (int i = 0; i < atoi(term); i++) {
      sprintf(str, "Выплата в месяц %d: %lf", i + 1,
              differented_loan(sum, term, percent, i, &pay));
      GtkWidget *label = gtk_label_new(str);
      gtk_box_append(GTK_BOX(box), label);
    }
    sprintf(str, "Переплата по кредиту: %lf", loan_overpayment(sum, pay));
    GtkWidget *label = gtk_label_new(str);
    gtk_box_append(GTK_BOX(box), label);
    sprintf(str, "Общая выплата: %lf", pay);
    GtkWidget *label2 = gtk_label_new(str);
    gtk_box_append(GTK_BOX(box), label2);
    gtk_window_set_child(GTK_WINDOW(new_window), box);
  }
  gtk_widget_show(new_window);
}

void annuity_loan_callback(GtkWidget *widget, gpointer data) {
  inputdata_ty *inpdata = (inputdata_ty *)data;
  GtkWidget *new_window;
  new_window = gtk_window_new();
  gtk_window_set_title(GTK_WINDOW(new_window), "SmartCalc:Аннуитетные платежи");
  gtk_window_set_default_size(GTK_WINDOW(new_window), 400, 400);
  const char *sum = gtk_editable_get_text(GTK_EDITABLE(inpdata->info1));
  const char *term = gtk_editable_get_text(GTK_EDITABLE(inpdata->info2));
  const char *percent = gtk_editable_get_text(GTK_EDITABLE(inpdata->info3));
  double pay = 0;
  char str[255];
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  if (check_button2(sum, term, percent)) {
    GtkWidget *label = gtk_label_new(error_message());
    gtk_window_set_child(GTK_WINDOW(new_window), label);
  } else {
    sprintf(str, "Ежемесячная выплата: %lf",
            annuity_loan(sum, term, percent, &pay));
    GtkWidget *label = gtk_label_new(str);
    gtk_box_append(GTK_BOX(box), label);
    sprintf(str, "Переплата по кредиту: %lf", loan_overpayment(sum, pay));
    GtkWidget *label2 = gtk_label_new(str);
    gtk_box_append(GTK_BOX(box), label2);
    sprintf(str, "Общая выплата: %lf", pay);
    GtkWidget *label3 = gtk_label_new(str);
    gtk_box_append(GTK_BOX(box), label3);
    gtk_window_set_child(GTK_WINDOW(new_window), box);
  }
  gtk_widget_show(new_window);
}

double annuity_loan(const char *sum, const char *term, const char *percent,
                    double *pay) {
  char expr[1023];
  int exit_code = SUCCESS;
  double number = 0;
  setlocale(LC_NUMERIC, "C");
  if (sprintf(expr, "%s*(%s/1200*(1+%s/1200)^%s)/((1+%s/1200)^%s-1)", sum,
              percent, percent, term, percent, term) < 0) {
    exit_code = ERROR;
  } else {
    stack_ty *input_stack = NULL;
    stack_ty *reversed_stack = NULL;
    parser(expr, &input_stack);
    reverse_stack(input_stack, &reversed_stack);
    number = calculate_rpn(&reversed_stack, 2);
    *pay = number * atoi(term);
    simple_destroy_stack(&input_stack);
    destroy_stack(&reversed_stack);
  }
  return (exit_code == ERROR) ? exit_code : number;
}

double differented_loan(const char *sum, const char *term, const char *percent,
                        int num, double *pay) {
  char expr[1023];
  int exit_code = SUCCESS;
  double number = 0;
  setlocale(LC_NUMERIC, "C");
  if (sprintf(expr, "%s/%s+(%s-(%d)*(%s/%s))*(%s/1200)", sum, term, sum, num,
              sum, term, percent) < 0) {
    exit_code = ERROR;
  } else {
    stack_ty *input_stack = NULL;
    stack_ty *reversed_stack = NULL;
    parser(expr, &input_stack);
    reverse_stack(input_stack, &reversed_stack);
    number = calculate_rpn(&reversed_stack, 2);
    *pay += number;
    simple_destroy_stack(&input_stack);
    destroy_stack(&reversed_stack);
  }
  return (exit_code == ERROR) ? exit_code : number;
}

double loan_overpayment(const char *sum, double pay) {
  char expr[1023];
  int exit_code = SUCCESS;
  double number = 0;
  setlocale(LC_NUMERIC, "C");
  if (sprintf(expr, "%lf-%s", pay, sum) < 0) {
    exit_code = ERROR;
  } else {
    stack_ty *input_stack = NULL;
    stack_ty *reversed_stack = NULL;
    parser(expr, &input_stack);
    reverse_stack(input_stack, &reversed_stack);
    number = calculate_rpn(&reversed_stack, 2);
    simple_destroy_stack(&input_stack);
    destroy_stack(&reversed_stack);
  }
  return (exit_code == ERROR) ? exit_code : number;
}

bool check_button2(const char *sum, const char *term, const char *percent) {
  return (!is_valid_expression(sum) || !is_valid_expression(term) ||
          !is_valid_expression(percent) || strlen(sum) == 0 ||
          strlen(term) == 0 || strlen(percent) == 0 || strlen(sum) > 255 ||
          strlen(term) > 255 || strlen(percent) > 255);
}