#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

int cacheIndex = 0;
double Ulimit = 1.0;
double Dlimit = 1.0;
double parts = 1.0;
int selected = 0;
double area = 0.0;
double areaNewt = 0.0;
double absError = 0.0;
double relError = 0.0;

// Объявление массива с опциями меню

const char *menuOptions[] = {
    "Ввод верхнего предела.", "Ввод нижнего предела.",
    "Шаг интегрирования.",    "Расчет интеграла.",
    "Расчет погрешности.",    "Выход."};

// Функция для отрисовки меню

void menu() {
  printf("\n");
  for (int i = 0; i < 6; i++) { // Цикл по всем опциям меню
    if (i == selected) { // Проверка, является ли текущая опция выбранной
      printf("%d. > %s <\n",i + 1, menuOptions[i]); // Выделение выбранной опции
    } else {
      printf("%d.  %s\n",i + 1, menuOptions[i]); // Печать остальных опций
    }
  }
  printf("\n\n\n");
  printf("Для передвижения по меню используйте клавишы 1-6, Enter - Ввод");
}

double integral(double x) {
  return 2 * x * x * x -2  * x * x - 4 * x + 18;
}

double newtonIntegral(double x) {
  return 0.5 * x * x * x * x -0.66 * x * x * x - 2 * x * x + 18 * x;
}

void intCalc() {
  double h = (Ulimit - Dlimit) / parts;
  area = 0.0;
  areaNewt = 0.0;
  for (int i = 1; i <= parts; i++) {
    if (integral(Ulimit + i * h) > 0) { // Если Y в точке Ulimit + i * h > 0, то прибавляем к общей площади площадь данного прямоугольника
        area += h * integral(Dlimit + i * h);
    }
  }
  areaNewt = newtonIntegral(Ulimit) - newtonIntegral(Dlimit);
  absError = fabs(areaNewt - area);
  relError = fabs(areaNewt - area) / (areaNewt / 100);
}

// Функция для получения числового ввода от пользователя

double getIntegerInput(const char *prompt) {
  // Массив строк с сообщениями об ошибках
  const char *options[] = {"правильный верхний лимит",
                           "правильный нижний лимит", "правильное кол-во отрезков"};
  double value; // Переменная для хранения введенного значения
  char term; // Переменная для хранения символа, введенного после числа
  printf("%s", prompt);
  while (1) { // Бесконечный цикл для повторного запроса ввода
    if (scanf("%lf%c", &value, &term) != 2 || term != '\n') {
      system("cls");
      printf("Ввод должен содержать только цифры, введите %s: ", options[selected]); // Сообщение об ошибке
      while (getchar() != '\n'); // Очистка буфера ввода
    } else {
      return value;
    }
  }
}

int main(void) {
  char input;
  int a, b, c, d;
  intCalc();
  while (1) {
    system("cls");
    menu();
    input = getch();
    selected = input - '1';
    switch (input) {
    // case 49:
    //   selected = 0;
    //   break;
    // case 50:
    //   selected = 1;
    //   break;
    // case 51:
    //   selected = 2;
    //   break;
    // case 52:
    //   selected = 3;
    //   break;
    // case 53:
    //   selected = 4;
    //   break;
    // case 54:
    //   selected = 5;
    //   break;
    case 13:
      switch (selected) {
      case 0:
        a++;
        system("cls");
        Ulimit = getIntegerInput("Введите верхний предел интегрирования: ");
        break;
      case 1:
        b++;
        system("cls");
        Dlimit = getIntegerInput("Введите нижний предел интегрирования(Пределы "
                                 "ниже -2.00 записываются как -2.00): ");
        if (Dlimit < -2.0) Dlimit = -2.0;
        break;
      case 2:
        c++;
        system("cls");
        parts = getIntegerInput("Введите кол-во частей отрезка: ");
        break;
      case 3:
        if (a != 0 && b != 0 && c != 0) {
          d++;
          system("cls");
          printf("Результат интегрирования на отрезке [%.2lf : %.2lf] с шагом "
                 "%lf:",
                 Dlimit, Ulimit, parts);
          intCalc();
          printf("\n\n%lf", area);
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
          printf("\nОтносительная погрешность: %.2lf%%", relError);
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
      break;
    }
  }
  return 0;
}
