#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 100005

/*
  配列のよるキューの実装は配列をリングバッファとみなしてデータを管理している
*/

typedef struct {
  char name[100];
  int time;
} Queue;

Queue Q[LEN];
int head, tail, n;

void enqueue(Queue x) {
  Q[tail] = x;
  tail = (tail + 1) % LEN;
}

Queue dequeue() {
  Queue x = Q[head];
  head = (head + 1) % LEN;
  return x;
}

int min(int a, int b) { return a < b ? a : b; }

int main() {
  int elaps = 0, c, q;
  Queue u;

  scanf("%d %d", &n, &q);

  for ( int i = 1; i <= n; i++ ) {
    scanf("%s", Q[i].name);
    scanf("%d", &Q[i].time);
  }

  head = 1; tail = n + 1;

  while (head != tail) {
    u = dequeue();
    c = min(q, u.time);
    u.time -= c;
    elaps += c;
    if (u.time > 0) enqueue(u);
    else {
      printf("%s %d\n", u.name, elaps);
    }
  }

  return 0;
}
