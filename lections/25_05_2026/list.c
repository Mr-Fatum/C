/*
 3. Односвязный список
*/

// Тип одного элемента структуры списка - списка целых чисел

#include <stdio.h>
#include <stdlib.h>

typedef struct tagListElem {
  // Данные
  int data;

  // Указатель на следующий элемент
  struct tagListElem *next;
} ListElem;

// Тип "список"
typedef ListElem* List;

/* Какие функции работы со списком нужны:
 * 1) Создать пустой список
*/

List EmptyList(void) {
    return NULL;
}

/* 2. CONS: элемент, список -> список */
List cons(int elem, List list) {
    ListElem *newElem = (ListElem *)
                malloc(sizeof(ListElem));

    (*newElem).data = elem;
    newElem->next = list;
    // -> - разыменовать указатель на структуру и взять указанное поле

    return newElem;
}

// 3. Проверка на пустоту
int empty(List list) {
    return list == NULL;
}

// 4. Голова
int head(List list) {
  if (empty(list)) {
      printf("head of an empty list!");
      exit(1);
  }

  return list->data;
}

// 5. Хвост
List tail(List list) {
  if (empty(list)) {
      printf("tail of an empty list!");
      exit(1);
  }

  return list->next;
}

// 6. Длина
int length(List list) {
    List temp = list;
    int len = 0;

    while (temp != NULL) {
        len++;
        temp = temp->next;
    }

    return len;
}

// 7. Напечатать список
void printList(List list) {
    printf("[");

    List temp = list;
    while (temp != NULL) {
        printf("%d", temp->data);
        temp = temp->next;
        if (temp != NULL) {
            printf(",");
        }
    }

    printf("]");
}


int main(void) {
    List list = EmptyList();
    list = cons(1, list);
    list = cons(-10, list);
    list = cons(5, list);
    list = cons(0, list);
    list = cons(-3, list);
    list = cons(2, list);

    printList(list);
    printf("\n");

    printf("head = %d\n", head(list));

    printf("tail: ");
    printList(tail(list));
    printf("\n");

    return 0;
}




