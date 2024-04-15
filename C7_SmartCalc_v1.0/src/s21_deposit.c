#include "s21_deposit.h"

int capital_flag = 0;

void toggle_button_toggled(GtkToggleButton *toggle_button, gpointer data) {
  gboolean is_toggled = gtk_toggle_button_get_active(toggle_button);
  if (is_toggled) {
    capital_flag = 1;
  }
}

void deposit_callback(GtkWidget *widget, gpointer data) {
  inputdata_ty *inpdata = (inputdata_ty *)data;
  GtkWidget *new_window = gtk_window_new();
  gtk_window_set_title(GTK_WINDOW(new_window),
                       "SmartCalc:Депозитный калькулятор");
  gtk_window_set_default_size(GTK_WINDOW(new_window), 400, 400);
  const char *sum = gtk_editable_get_text(GTK_EDITABLE(inpdata->info1));
  const char *term = gtk_editable_get_text(GTK_EDITABLE(inpdata->info2));
  const char *percent = gtk_editable_get_text(GTK_EDITABLE(inpdata->info3));
  const char *tax = gtk_editable_get_text(GTK_EDITABLE(inpdata->info4));
  const char *period = gtk_editable_get_text(GTK_EDITABLE(inpdata->info5));
  const char *in_list = gtk_editable_get_text(GTK_EDITABLE(inpdata->info6));
  const char *out_list = gtk_editable_get_text(GTK_EDITABLE(inpdata->info7));
  if (check_button3(sum, term, percent, tax, period, in_list, out_list)) {
    GtkWidget *label = gtk_label_new(error_message());
    gtk_window_set_child(GTK_WINDOW(new_window), label);
  } else {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    main_deposit_function(sum, term, percent, tax, period, in_list, out_list,
                          &box);
    gtk_window_set_child(GTK_WINDOW(new_window), box);
  }
  gtk_widget_show(new_window);
}

void main_deposit_function(const char *sum, const char *term,
                           const char *percent, const char *tax,
                           const char *period, const char *in_list,
                           const char *out_list, GtkWidget **box) {
  double withdrawal_amount = 0, replenishment_amount = 0;
  if (strlen(in_list) != 0) {
    withdrawal_amount = sum_of_list(out_list);
  }
  if (strlen(out_list) != 0) {
    replenishment_amount = sum_of_list(in_list);
  }
  char str[255];
  double modif_sum =
      deposit_modification(sum, replenishment_amount, withdrawal_amount);
  double interest_charges_result =
      interest_charges(modif_sum, percent, term, period);
  sprintf(str, "Начисленные проценты: %lf", interest_charges_result);
  GtkWidget *label1 = gtk_label_new(str);
  gtk_box_append(GTK_BOX(*box), label1);
  double tax_sum_result = tax_sum(interest_charges_result, tax);
  sprintf(str, "Сумма налога: %lf", tax_sum_result);
  GtkWidget *label2 = gtk_label_new(str);
  gtk_box_append(GTK_BOX(*box), label2);
  double deposit_amount_result =
      deposit_amount(modif_sum, interest_charges_result, tax_sum_result);
  sprintf(str, "Сумма на вкладе к концу срока: %lf", deposit_amount_result);
  GtkWidget *label3 = gtk_label_new(str);
  gtk_box_append(GTK_BOX(*box), label3);
}

double interest_charges(double sum, const char *percent, const char *term,
                        const char *period) {
  char expr[1023];
  int exit_code = SUCCESS;
  double number = 0;
  setlocale(LC_NUMERIC, "C");
  if (!capital_flag) {
    if (sprintf(expr, "%lf*%s/100*%s", sum, percent, term) < 0) {
      exit_code = ERROR;
    }
  } else {
    if (sprintf(expr, "%lf*(1+%s/100/%s)^(%s*%s)-%lf", sum, percent, period,
                period, term, sum) < 0)
      exit_code = ERROR;
  }
  if (exit_code == SUCCESS) {
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

double tax_sum(double percent, const char *tax) {
  char expr[1023];
  int exit_code = SUCCESS;
  double number = 0;
  setlocale(LC_NUMERIC, "C");
  if (sprintf(expr, "%lf/100*%s", percent, tax) < 0) {
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

double deposit_amount(double sum, double percent, double tax) {
  char expr[1023];
  int exit_code = SUCCESS;
  double number = 0;
  setlocale(LC_NUMERIC, "C");
  if (sprintf(expr, "%lf+%lf-%lf", sum, percent, tax) < 0) {
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

double sum_of_list(const char *list) {
  char *end;
  double sum = 0.0;
  list++;
  while (*list) {
    double num = strtod(list, &end);
    if (list == end) {
      list++;
      continue;
    }
    sum += num;
    list = strchr(end, ';');
    if (!list) {
      break;
    }
    list++;
  }
  return sum;
}

double deposit_modification(const char *sum, double repl_am, double with_am) {
  char expr[1023];
  int exit_code = SUCCESS;
  double number = 0;
  setlocale(LC_NUMERIC, "C");
  if (sprintf(expr, "%s+%lf-%lf", sum, repl_am, with_am) < 0) {
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

bool check_button3(const char *sum, const char *term, const char *percent,
                   const char *tax, const char *period, const char *in_list,
                   const char *out_list) {
  return (strlen(sum) == 0 || strlen(term) == 0 || strlen(percent) == 0 ||
          strlen(tax) == 0 || strlen(period) == 0 ||
          !is_valid_expression(sum) || !is_valid_expression(term) ||
          !is_valid_expression(percent) || !is_valid_expression(tax) ||
          !is_valid_expression(period) || strlen(sum) > 255 ||
          strlen(term) > 255 || strlen(percent) > 255 || strlen(tax) > 255 ||
          strlen(period) > 255 || strlen(in_list) > 255 ||
          strlen(out_list) > 255);
}