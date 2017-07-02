int LessNum(int a, int b);

typedef struct _heap Heap;

Heap *NewHeap(int tamanho, int (*less) (int, int));

void FreeHeap(Heap * h);

void FixUp(Heap * h, int k, dados*d);

void FixDown(Heap * h, int k, dados*d);

void Direct_Insert(Heap * h, int element);

int RemoveMax(Heap * h, dados*d);

void Heapify(Heap * h, dados*d);

int HeapEmpty(Heap*h);

