#include <stdlib.h>
#include <stdio.h>
#include "estruturas.h"
#include "heap.h"

/* to remove comments, just delete or comment the next line */
#define DEMO

int LessNum(int a, int b){
  return (a > b);
}

/* A heap is represented by a structure: */
struct _heap {
  int (*less) (int, int);  
  int n_elements;               /* # elements in heap */
  int size;                     /* max size of the heap. */
  int *heapdata;               /* An array of ints. */
};

void FixUp(Heap * h, int k, dados*d)
{
  int t;
  while ((k > 0) && ((h->less) (d->caminho[(h->heapdata)[(k - 1) / 2]], d->caminho[(h->heapdata)[k]]))) {
#ifdef DEMO
    
#endif
    /*---------------------------------------------------------*/
    t = (h->heapdata)[k];
    (h->heapdata)[k] = (h->heapdata)[(k - 1) / 2];
    (h->heapdata)[(k - 1) / 2] = t;

#ifdef DEMO
  
#endif
 
    k = (k - 1) / 2;
  }

  return;
}

void FixDown(Heap * h, int k, dados*d)
{
  int j;
  int t;

  while ((2 * k + 1) < h->n_elements) {
    j = 2 * k + 1;
    if (((j + 1) < h->n_elements) &&
        (h->less) (d->caminho[h->heapdata[j]], d->caminho[h->heapdata[j + 1]])) {
      /* second offspring is greater */
      j++;
    }
    if (!(h->less) (d->caminho[h->heapdata[k]], d->caminho[h->heapdata[j]])) {
      /* Elements are in correct order. */

#ifdef DEMO
      /* --------------------------------------------------- */

#endif
      /*---------------------------------------------------------*/
      break;
    }
#ifdef DEMO

#endif
    /*---------------------------------------------------------*/

    /* the 2 elements are not correctly sorted, it is
       necessary to exchange them */
    t = (h->heapdata)[k];
    (h->heapdata)[k] = (h->heapdata)[j];
    (h->heapdata)[j] = t;
    k = j;

#ifdef DEMO
    /* --------------------------------------------------- */

#endif
    /*---------------------------------------------------------*/
  }

  return;
}

Heap *NewHeap(int size, int (*less) (int, int)){
  Heap *h;

  h = (Heap *) malloc(sizeof(Heap));
  if (h == ((Heap *) NULL)) {
    fprintf(stderr, "Error in malloc of heap\n");
    exit(1);
  }

  h->n_elements = 0;
  h->less = less;
  h->size = size;
  h->heapdata = (int *) malloc(size * sizeof(int));
  if (h->heapdata == ((int *) NULL)) {
    fprintf(stderr, "Error in malloc of heap data\n");
    exit(1);
  }

  return (h);
}

void FreeHeap(Heap *h)
{
    free(h->heapdata);
    free(h);

   return;
}

void Direct_Insert(Heap * h, int element)
{
  if (h->n_elements == h->size) {
    return;
  }
  h->heapdata[h->n_elements] = element;

  h->n_elements++;


  return;
}

int RemoveMax(Heap * h, dados*d)
{
  int t;

  if (h->n_elements > 0) {
    t = (h->heapdata)[0];
    (h->heapdata)[0] = (h->heapdata)[h->n_elements - 1];
    (h->heapdata)[h->n_elements - 1] = t;
    h->n_elements--;
    FixDown(h, 0, d);
    return t;
  }
 return -1;
}

void Heapify(Heap * h, dados*d)
{
	int i;
	for(i=h->n_elements-1; i>=0; i-=2){
		FixDown(h, (i-1)/2, d);
	}

    return;
}




int HeapEmpty(Heap*h){
	int b=0;
	if(h->n_elements==0)b=1;
	return b;
}



