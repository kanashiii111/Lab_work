#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include "CLL.h"

#define KEY_UP 72
#define KEY_DOWN 80
typedef void (*proc1)(Node**, int);
typedef void (*proc2)(Node**);
typedef void (*proc3)(int, Node*);
typedef void (*proc4)();

proc1 procc1[2] = {&insertFront, &removeNode};
proc2 procc2[2] = {&printList, &clearList};
proc3 procc3[1] = {&findNodeByPos};
proc4 procc4[2] = {&clearCMD, &help};

int programRunning;

const char* commands[] = {"find", "add", "remove", "print", "clear", "screenClear", "help", "exit"};
char commandsHistory[10][256] = {""};
int commandsHistoryCount = 0;
int chosenCommand = 0;

void clearCurrentLine(int len) {
    for (int i = 0; i < len; i++) {
        printf("\b \b");
    }
}

void addToHistory(char* buffer) {
    if (commandsHistoryCount >= 10) {
        for (int i = 0; i < 9; i++) {
            strcpy(commandsHistory[i], commandsHistory[i+1]);
        }
        commandsHistoryCount--;
    }
    strcpy(commandsHistory[commandsHistoryCount], buffer);
    commandsHistoryCount++;
    chosenCommand = commandsHistoryCount; 
}

void arrowKeysHandling(int key, char* buffer, int* len) {
    if (key == KEY_UP) {
        clearCurrentLine(*len);
        if (chosenCommand > 0) {
            chosenCommand--;
        }
        strcpy(buffer, commandsHistory[chosenCommand]);
        *len = strlen(commandsHistory[chosenCommand]);
        printf("%s", commandsHistory[chosenCommand]);
    } else if (key == KEY_DOWN) {
        clearCurrentLine(*len);
        if (chosenCommand < commandsHistoryCount - 1) {
            chosenCommand++;
            strcpy(buffer, commandsHistory[chosenCommand]);
            *len = strlen(commandsHistory[chosenCommand]);
            printf("%s", commandsHistory[chosenCommand]);
        } else if (chosenCommand == commandsHistoryCount - 1) {
            chosenCommand++;
            *len = 0;
            buffer[0] = '\0';
        }
    }
}
void commandHandling(char* command, Node** lastNode) {
    char cmd[256] = {0};
    int value = 0;
    int params = sscanf(command, "%s %d", cmd, &value);
    
    if (params == 0) return;

    int commandFound = 0;
    for (int i = 0; i < 8; i++) {
        if (strcmp(cmd, commands[i]) == 0) {
            commandFound = 1;
            if (i == 0) {
                if (params != 2) {printf("Использование find <позиция>\n"); continue;}
                procc3[i](value, *lastNode);
            } else if (i == 1 || i == 2) {
                if (params != 2) {printf("Использование add/remove <число>\n"); continue;}
                procc1[i-1](lastNode, value);
            } else if (i == 3 || i == 4) {
                procc2[i-3](lastNode);
            } else if (i == 5 || i == 6) {
                procc4[i-5]();
            } else if (i == 7) {
                programRunning = 0;
            }
            break;
        }
    }
    
    if (!commandFound) {
        printf("Неизвестная команда\n");
        printf("Доступные команды: find, add, remove, print, clear, screenClear, help, exit\n");
    }
}

void commandCompletion(Node** lastNode) {
    int len = 0;
    int buf_size = 32;
    char* buffer = (char*)calloc(buf_size, sizeof(char));
    printf("> ");
    fflush(stdout);
    int run = 1;
    while (run) {
        char c = getch();

        // Обработка стрелок

        if ((int)c == KEY_UP || (int)c == KEY_DOWN) {
            arrowKeysHandling((int)c, buffer, &len);
        }

        // Обработка Enter

        if (c == '\r' || c == '\n') {
            printf("\n");
            if (len > 0) {
                addToHistory(buffer);
                commandHandling(buffer, lastNode);
                if (strcmp(buffer, "exit") == 0) programRunning = 0;
            }
            break;
        }
        
        // Обработка Backspace

        if (c == '\b') {
            if (len > 0) {
                len--;
                buffer[len] = '\0';
                printf("\b \b");
                fflush(stdout);
            }
            continue;
        }
        
        // Обработка TAB

        if (c == '\t') {
            const char* match = NULL;
            int match_count = 0;
            
            for (int i = 0; commands[i]; i++) {
                if (strncmp(buffer, commands[i], len) == 0) {
                    match = commands[i];
                    match_count++;
                }
            }
            if (match_count == 1) {
                clearCurrentLine(len);
                strcpy(buffer, match);
                len = strlen(match);
                printf("%s", buffer);
            }
            continue;
        }
        
        // Обработка обычных символов

        if (c >= 32 && c <= 126) {
            if (c == KEY_DOWN || c == KEY_UP) continue;
            if (len >= buf_size - 1) {
                buf_size *= 2;
                char* new_buf = realloc(buffer, buf_size);
                if (!new_buf) break;
                buffer = new_buf;
            }
            
            buffer[len++] = c;
            buffer[len] = '\0';
            putchar(c); 
        }
    }
    free(buffer);
}

int main(void) {
    Node* lastNode = NULL;
    programRunning = 1;
    printf("Для получения списка комманд введите help\n");
    while (programRunning) {
        commandCompletion(&lastNode);
    }
    return 0;
}