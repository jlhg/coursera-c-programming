/* Basic Interpreter */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define VAR_SIZE sizeof(char) * 100
#define BUF_SIZE sizeof(char) * 150
#define NCHAR 150
#define NVAR 100

int process_variable(char *line, char *var_names[], int *var_values);
void exec_statements(char *statements[], int lineno, char *var_names[], int *var_values);
void dump_vars(int nvars, char *var_names[], int *var_values);
int get_value(char *str, char *var_names[], int *var_values);
void set_value(char *lvalue, int rvalue, char *var_names[], int *var_values);
int judge_value(int lvalue, int rvalue, char *op);
int cal_value(int a, int b, char *op);
char *chomp(char *str);

int print_size = 0;
int print_values[200];
int nvars;

int main()
{
        char line[150];
        char *statements[52];
        char *var_names[NVAR];
        int var_values[NVAR];

        int lineno = 0;
        while (fgets(line, NCHAR, stdin) != NULL) {
                if (lineno == 0) {
                        nvars = process_variable(line, var_names, var_values);
                } else {
                        statements[lineno] = malloc(BUF_SIZE);
                        strncpy(statements[lineno], line, NCHAR);
                }
                ++lineno;
        }

        dump_vars(nvars, var_names, var_values);

        printf("Start to execute BASIC:\n");
        exec_statements(statements, 1, var_names, var_values);

        printf("\n");
        printf("Print values:\n");
        int i;
        for (i = 0; i < print_size; ++i) {
                printf("%d ", print_values[i]);
        }
        printf("\n");

        return 0;
}

/* Return the number of variables been parsed.  */
int process_variable(char *line, char *var_names[], int *var_values)
{
        char *pch;
        int i = 0;
        pch = strtok(line, " ");
        while (strncmp(pch, "END", 3) != 0) {
                var_names[i] = malloc(VAR_SIZE);
                strncpy(var_names[i], pch, NVAR);
                pch = strtok(NULL, " ");
                pch = strtok(NULL, " ");
                var_values[i] = atoi(pch);
                pch = strtok(NULL, " ");
                ++i;
        }

        return i;
}

void exec_statements(char *statements[], int lineno, char *var_names[], int *var_values)
{
        char s[NCHAR];
        strncpy(s, statements[lineno], NCHAR);
        char *pch;
        int lvalue, rvalue;
        char *op;
        int a, b;
        int nextline;
        if (strncmp(s, "STOP", 4) != 0) {
                pch = strtok(s, " ");
                if (strncmp(pch, "IF", 2) == 0) {
                        printf("if statement:\n");
                        /* dump_vars(8, var_names, var_values); */
                        lvalue = get_value(chomp(strtok(NULL, " ")), var_names, var_values);
                        op = strtok(NULL, " ");
                        rvalue = get_value(chomp(strtok(NULL, " ")), var_names, var_values);
                        printf("exp: %d %s %d\n", lvalue, op, rvalue);
                        if (judge_value(lvalue, rvalue, op)) {
                                printf("result: true\n");
                                strtok(NULL, " ");
                                nextline = atoi(chomp(strtok(NULL, " ")));
                                printf("goto: %d\n", nextline);
                                exec_statements(statements, nextline, var_names, var_values);
                        } else {
                                printf("result: false\n");
                                nextline = lineno + 1;
                                printf("goto: %d\n", nextline);
                                exec_statements(statements, nextline, var_names, var_values);
                        }
                } else if (strncmp(pch, "PRINT", 5) == 0) {
                        rvalue = get_value(chomp(strtok(NULL, " ")), var_names, var_values);
                        print_values[print_size++] = rvalue;
                        printf("print statement:\n");
                        printf("%d ", rvalue);
                        nextline = lineno + 1;
                        printf("goto: %d\n", nextline);
                        exec_statements(statements, nextline, var_names, var_values);
                } else if (strncmp(pch, "GOTO", 4) == 0) {
                        printf("goto statement:\n");
                        nextline = atoi(chomp(strtok(NULL, " ")));
                        printf("goto: %d\n", nextline);
                        exec_statements(statements, nextline, var_names, var_values);
                } else {
                        printf("assignment statement:\n");
                        strtok(NULL, " ");
                        a = get_value(chomp(strtok(NULL, " ")), var_names, var_values);
                        op = strtok(NULL, " ");
                        b = get_value(chomp(strtok(NULL, " ")), var_names, var_values);
                        printf("exp: %s = %d %s %d\n", pch, a, op, b);
                        rvalue = cal_value(a, b, op);
                        set_value(pch, rvalue, var_names, var_values);
                        printf("result: %s = %d\n", pch, get_value(pch, var_names, var_values));
                        nextline = lineno + 1;
                        printf("goto: %d\n", nextline);
                        exec_statements(statements, nextline, var_names, var_values);
                }
        }

        return;
}

void dump_vars(int nvars, char *var_names[], int *var_values)
{
        int i;
        printf("Dump varaiables:\n");
        for (i = 0; i < nvars; ++i) {
                printf("%s => %d\n", var_names[i], var_values[i]);
        }

        return;
}

int get_value(char *str, char *var_names[], int *var_values)
{
        int i;
        for (i = 0; i < nvars; ++i) {
                if (strncmp(str, var_names[i], NVAR) == 0)
                        return var_values[i];
        }

        return -1;
}

void set_value(char *lvalue, int rvalue, char *var_names[], int *var_values)
{
        int i;
        for (i = 0; i < NVAR; ++i) {
                if (strncmp(lvalue, var_names[i], 100) == 0) {
                        var_values[i] = rvalue;
                        break;
                }
        }

        return;
}

/* Return 1 if the expression result is true. */
int judge_value(int lvalue, int rvalue, char *op)
{
        if (strncmp(op, "==", 2) == 0) {
                if (lvalue == rvalue)
                        return 1;
                else
                        return 0;
        } else if (strncmp(op, "!=", 2) == 0) {
                if (lvalue != rvalue)
                        return 1;
                else
                        return 0;
        } else if (strncmp(op, ">", 2) == 0) {
                if (lvalue > rvalue)
                        return 1;
                else
                        return 0;
        } else if (strncmp(op, "<", 2) == 0) {
                if (lvalue < rvalue)
                        return 1;
                else
                        return 0;
        } else if (strncmp(op, ">=", 2) == 0) {
                if (lvalue >= rvalue)
                        return 1;
                else
                        return 0;
        } else if (strncmp(op, "<=", 2) == 0) {
                if (lvalue <= rvalue)
                        return 1;
                else
                        return 0;
        }

        return 0;
}

int cal_value(int a, int b, char *op)
{
        if (strncmp(op, "+", 1) == 0)
                return a + b;
        else if (strncmp(op, "-", 1) == 0)
                return a - b;
        else if (strncmp(op, "*", 1) == 0)
                return a * b;
        else if (strncmp(op, "/", 1) == 0)
                return a / b;
        else if (strncmp(op, "%", 1) == 0)
                return a % b;

        return -1;
}


char *chomp(char *str)
{
        unsigned int i;
        for (i = 0; i < strlen(str); ++i) {
                if (str[i] == '\n') {
                        str[i] = '\0';
                        break;
                }
        }

        return str;
}
