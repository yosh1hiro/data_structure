#include <cstdio>
#include <cstdlib>
#include <cstring>

/*
  双方向連結リストへの要素の追加は、ポインタの繋ぎ変えだけなので、O(1)で行える。
  検索は要素を特定するためにポインタをたどる必要があるので、O(N)のアルゴリズムになる。
  特定のkeyを持つノードの削除もO(N)の計算量が必要になる。
*/

typedef struct Node {
  int key;
  Node *prev, *next;
} Node;

Node *nil;

void init() {
  nil = (Node *)malloc(sizeof(Node));
  nil->next = nil;
  nil->prev = nil;
}

void printList() {
  Node *cur = nil->next;
  int isf = 0;
  while (1) {
    if ( cur == nil ) break;
    if ( isf++ > 0 ) printf(" ");
    printf("%d", cur->key);
    cur = cur->next;
  }
  printf("\n");
}

void insert(int key) {
  Node *x = (Node *)malloc(sizeof(Node));
  x->key = key;
  // 番兵の直後に要素を追加
  x->next = nil->next;
  nil->next->prev = x;
  nil->next = x;
  x->prev = nil;
}

Node* listSearch(int key) {
  Node *cur = nil->next; // 番兵の次の要素からたどる
  while ( cur != nil && cur->key != key) {
    cur = cur->next;
  }
  return cur;
}

void deleteNode(Node *t) {
  if ( t == nil ) return; // tが番兵の場合は処理しない
  t->prev->next = t->next;
  t->next->prev = t->prev;
  free(t);
}

void deleteFirst() {
  deleteNode(nil->next);
}

void deleteLast() {
  deleteNode(nil->prev);
}

void deleteKey(int key) {
  // 検索したノードを削除
  deleteNode(listSearch(key));
}

int main() {
  int key, n;
  int size = 0;
  char com[20];
  int np = 0, nd = 0;

  scanf("%d", &n);
  init();

  for ( int i = 0; i < n; i++) {
    scanf("%s%d", com, &key);
    if ( com[0] == 'i' ) {
      insert(key); np++; size++;
    } else if ( com[0] == 'd' ) {
      if ( com[6] == 'F' ) deleteFirst();
      else if ( com[6] == 'L' ) deleteLast();
      else deleteKey(key); nd++;
      size --;
    }
  }

  printList();

  return 0;
}
