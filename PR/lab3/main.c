#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

double Ulimit = 1.0;
double Dlimit = 1.0;
double step = 1.0;
int selected = 0;
double area = 0.0;
double areaNewt = 0.0;
double absError = 0.0;
double relError = 0.0;
int a,b,c,d,g = 0;

char *menuOptions[] = {
    "1. Ввод верхнего предела.", "2. Ввод нижнего предела.",
    "3. Шаг интегрирования.",    "4. Расчет интеграла",
    "5. Расчет погрешности.",    "6. Выход."};

void menu() {
  printf("------------------------------\n");
  for (int i = 0; i < 6; i++) {
    if (i == selected) {
      printf("- %s\n", menuOptions[i]);
    } else {
      printf("%s\n", menuOptions[i]);
    }
  }
  printf("------------------------------");
  printf("\n\n");
  if (Dlimit > Ulimit) {
    double tmp = Dlimit;
    Dlimit = Ulimit;
    Ulimit = tmp;
    g = 1;
  }
  printf("Текущий конфиг: Предел: [%lf : %lf], шаг: %lf", Dlimit, Ulimit, step);
  if (g == 1)  {
    printf("\nЛимиты были поменяны местами");
    g = 0;
  }
  printf("\n\nНули функции: -1.45476, 0.19535, 1.75941");
  printf("\n\n\n");
  printf("Для передвижения по меню используйте стрелочки вверх и вниз, Enter - "
         "Ввод");
}

double integral(double x) {
   return (2 * (x * x * x) - 1 * (x * x) - 5 * x + 1);
}
double Newton(double x) {
  return (0.5 * x * x * x * x) - (0.33 * x * x * x) - (2.5 * x * x) + x;
}

void intCalc() {
  int k;
  double y;
  if (integral(Dlimit) > 0) {
    area = integral(Dlimit);
    if (integral(Ulimit) > 0) {
      area += integral(Ulimit);
    }
  }
  int i = 1;
  for (double x = Dlimit + step; x < Ulimit - step; x += step) {
    k = 2 + 2 * (i++ % 2);
    y = integral(x);
    if (y > 0) area += k * y;
  }
  area *= step / 3;
}

void NewtonCalc() {
  if (Dlimit <= 0.2) {
    if (Ulimit >= 0.2 && Ulimit <= 1.75) {
      areaNewt = Newton(0.2) - Newton(Dlimit);
    } else if (Ulimit > 1.75) {
      areaNewt = Newton(Ulimit) - Newton(Dlimit) - (Newton(1.75) - Newton(0.2));
    } else {
      areaNewt = Newton(Ulimit) - Newton(Dlimit);
    }
  } else if (Dlimit >= 0.2 && Dlimit <= 1.75) {
    if (Ulimit <= 1.75) {
      areaNewt = 0.0;
    } else {
      areaNewt = Newton(Ulimit) - Newton(1.75);
    }
  } else {
    areaNewt = Newton(Ulimit) - Newton(Dlimit);
  }
  absError = fabs(areaNewt - area);
  if (areaNewt != 0.0) relError = absError / (areaNewt / 100);
}


double getIntegerInput(char *prompt) {
  const char *options[] = {"корректный верхний лимит",
                           "корректный нижний лимит", "корректный шаг"};
  double value;
  char term;
  printf("%s", prompt);
  while (1) {
    if (scanf("%lf%c", &value, &term) != 2 || term != '\n') {
      system("cls");
      printf("Ввод должен содержать только число, введите %s: ",
             options[selected]);
      while (getchar() != '\n');
    } else {
      return value;
    }
  }
}

int main(void) {
  char input;
  while (1) {
    system("cls");
    menu();
    input = getch();
    switch (input) {
    case 72: 
      if (selected > 0)
        selected--;
      break;
    case 80: 
      if (selected < 5)
        selected++;
      break;
    case 13:
      switch (selected) {
      case 0:
        a++;
        system("cls");
        Ulimit = getIntegerInput("Введите верхний предел интегрирования(Пределы ниже -1.5 записываются как -1.5): ");
        if (Ulimit < -1.5) Ulimit = -1.5;
        break;
      case 1:
        b++;
        system("cls");
        Dlimit = getIntegerInput("Введите нижний предел интегрирования(Пределы "
                                 "ниже -1.5 записываются как -1.5): "); 
        if (Dlimit < -1.5) Dlimit = -1.5;
        break;
      case 2:
        c++;
        system("cls");
        step = getIntegerInput("Введите шаг: ");
        break;
      case 3:
        if (a != 0 && b != 0 && c != 0) {
          d++;
          system("cls");
          printf("Результат интегрирования на отрезке [%.2lf : %.2lf] с шагом "
                 "%lf:",
                 Dlimit, Ulimit, step);
          intCalc();
          NewtonCalc();
          printf("\n\nМетод Симпсона: %lf", area);
          printf("\nМетод Ньютона-Лейбница: %lf", areaNewt);
          printf("\n\n\nДля выхода в главное меню нажмите любую клавишу");
          if (getch()) {
            break;
          }
        } else {
          system("cls");
          printf("Для расчета интеграла нужно ввести оба предела и шаг "
                 "интегрирования");
          printf("\n\n\nДля выхода в главное меню нажмите любую клавишу");
          if (getch()) {
            break;
          }
        }
      case 4:
        if (d != 0) {
          system("cls");
          printf("Абсолютная погрешность: %.2lf", absError);
          printf("\nОтносительная погрешность: %.5lf%%", relError);
          printf("\n\n\n");
          printf("Для выхода в главное меню нажмите любую клавишу");
          if (getch()) {
            break;
          }
        } else {
          system("cls");
          printf("Для расчета погрешности нужно расчитать интеграл");
          printf("\n\n\nДля выхода в главное меню нажмите любую клавишу");
          if (getch()) {
            break;
          }
        }
      case 5:
        system("cls");
        return 0;
      }
    }
  }
  return 0;
}