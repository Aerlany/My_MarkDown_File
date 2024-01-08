#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HT 100 // 哈夫曼树的最大高度

typedef struct MinHeapNode {
  char data; // 字符
  int freq;  // 频率
  struct MinHeapNode *left;
  struct MinHeapNode *right;
} MinHeapNode;

typedef struct MinHeap {
  int size;
  int capacity;
  MinHeapNode **array;
} MinHeap;

typedef struct HuffmanCode {
  char data;
  char *code;
} HuffmanCode;

MinHeapNode *newNode(char data, int freq) {
  MinHeapNode *node = (MinHeapNode *)malloc(sizeof(MinHeapNode));
  node->data = data;
  node->freq = freq;
  node->left = NULL;
  node->right = NULL;
  return node;
}

MinHeap *createMinHeap(int capacity) {
  MinHeap *minHeap = (MinHeap *)malloc(sizeof(MinHeap));
  minHeap->size = 0;
  minHeap->capacity = capacity;
  minHeap->array = (MinHeapNode **)malloc(capacity * sizeof(MinHeapNode *));
  return minHeap;
}

void swapMinHeapNode(MinHeapNode **a, MinHeapNode **b) {
  MinHeapNode *t = *a;
  *a = *b;
  *b = t;
}

void minHeapify(MinHeap *minHeap, int idx) {
  int smallest = idx;
  int left = 2 * idx + 1;
  int right = 2 * idx + 2;
  if (left < minHeap->size &&
      minHeap->array[left]->freq < minHeap->array[smallest]->freq) {
    smallest = left;
  }
  if (right < minHeap->size &&
      minHeap->array[right]->freq < minHeap->array[smallest]->freq) {
    smallest = right;
  }
  if (smallest != idx) {
    swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
    minHeapify(minHeap, smallest);
  }
}

int isSizeOne(MinHeap *minHeap) { return (minHeap->size == 1); }

MinHeapNode *extractMin(MinHeap *minHeap) {
  MinHeapNode *temp = minHeap->array[0];
  minHeap->array[0] = minHeap->array[minHeap->size - 1];
  --minHeap->size;
  minHeapify(minHeap, 0);
  return temp;
}

void insertMinHeap(MinHeap *minHeap, MinHeapNode *minHeapNode) {
  ++minHeap->size;
  int i = minHeap->size - 1;
  while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
    minHeap->array[i] = minHeap->array[(i - 1) / 2];
    i = (i - 1) / 2;
  }
  minHeap->array[i] = minHeapNode;
}

void buildMinHeap(MinHeap *minHeap) {
  int n = minHeap->size - 1;
  for (int i = (n - 1) / 2; i >= 0; --i) {
    minHeapify(minHeap, i);
  }

  void printArr(int arr[], int n) {
    for (int i = 0; i < n; ++i) {
      printf("%d", arr[i]);
    }
    printf("\n");
  }

  int isLeaf(MinHeapNode * root) { return !(root->left) && !(root->right); }

  void printCodes(MinHeapNode * root, int arr[], int top,
                  HuffmanCode huffmanCode[]) {
    if (root->left) {
      arr[top] = 0;
      printCodes(root->left, arr, top + 1, huffmanCode);
    }
    if (root->right) {
      arr[top] = 1;
      printCodes(root->right, arr, top + 1, huffmanCode);
    }
    if (isLeaf(root)) {
      huffmanCode[root->data].data = root->data;
      huffmanCode[root->data].code = (char *)malloc(top * sizeof(char));
      memcpy(huffmanCode[root->data].code, arr, top * sizeof(char));
    }
  }

  void printHuffmanCode(HuffmanCode huffmanCode[], int size) {
    printf("Huffman Codes:\n");
    for (int i = 0; i < size; ++i) {
      if (huffmanCode[i].code != NULL) {
        printf("%c: %s\n", huffmanCode[i].data, huffmanCode[i].code);
      }
    }
  }

  void huffmanCode(char data[], int freq[], int size) {
    MinHeapNode *left, *right, *top;
    MinHeap *minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i) {
      insertMinHeap(minHeap, newNode(data[i], freq[i]));
    }
    while (!isSizeOne(minHeap)) {
      left = extractMin(minHeap);
      right = extractMin(minHeap);
      top = newNode('$', left->freq + right->freq);
      top->left = left;
      top->right = right;
      insertMinHeap(minHeap, top);
    }
    HuffmanCode huffmanCode[256] = {0};
    int arr[MAX_TREE_HT], top = 0;
    printCodes(extractMin(minHeap), arr, top, huffmanCode);
    printHuffmanCode(huffmanCode, size);
  }
}
int main() {
  char data[] = {'a', 'b', 'c', 'd', 'e', 'f'};
  int freq[] = {5, 9, 12, 13, 16, 45};
  int size = sizeof(data) / sizeof(data[0]);
  huffmanCode(data, freq, size);

  // 不同频率值的测试
  char data1[] = {'a', 'b', 'c', 'd', 'e', 'f'};
  int freq1[] = {1, 2, 3, 4, 5, 6};
  int size1 = sizeof(data1) / sizeof(data1[0]);
  huffmanCode(data1, freq1, size1);

  char data2[] = {'a', 'b', 'c', 'd', 'e', 'f'};
  int freq2[] = {10, 20, 30, 40, 50, 60};
  int size2 = sizeof(data2) / sizeof(data2[0]);
  huffmanCode(data2, freq2, size2);

  return 0;
}
