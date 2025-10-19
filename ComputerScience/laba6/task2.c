#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  double prob;
  int left, right;
} Node;

void buildHuffmanTree(Node *nodes, int n) {
  for (int i = 0; i < n - 1; i++) {
    int min1 = -1, min2 = -1;
    for (int j = 0; j < n + i; j++) {
      if (nodes[j].prob >= 0) {
        if (min1 == -1 || nodes[j].prob <= nodes[min1].prob) {
          min2 = min1;
          min1 = j;
        } else if (min2 == -1 || nodes[j].prob < nodes[min2].prob) {
          min2 = j;
        }
      }
    }
    nodes[n + i].prob = nodes[min1].prob + nodes[min2].prob;
    if (nodes[min1].prob > nodes[min2].prob) {
      nodes[n + i].left = min1;
      nodes[n + i].right = min2;
    } else {
      nodes[n + i].left = min2;
      nodes[n + i].right = min1;
    }
    nodes[min1].prob = -1;
    nodes[min2].prob = -1;
  }
}

void printCodes(Node *nodes, int index, int *code, int codeLen) {
  if (nodes[index].left == -1 && nodes[index].right == -1) {
    for (int i = 0; i < codeLen; i++) {
      printf("%d", code[i]);
    }
    printf(" ");
    return;
  }
  code[codeLen] = 0;
  printCodes(nodes, nodes[index].left, code, codeLen + 1);
  code[codeLen] = 1;
  printCodes(nodes, nodes[index].right, code, codeLen + 1);
}

int main() {
  int n;
  scanf("%d", &n);
  Node *nodes = (Node *)malloc((2 * n - 1) * sizeof(Node));
  for (int i = 0; i < n; i++) {
    scanf("%lf", &nodes[i].prob);
    nodes[i].left = nodes[i].right = -1;
  }
  buildHuffmanTree(nodes, n);
  int *code = (int *)malloc((2 * n - 1) * sizeof(int));
  printCodes(nodes, 2 * n - 2, code, 0);
  free(nodes);
  free(code);
  return 0;
}
