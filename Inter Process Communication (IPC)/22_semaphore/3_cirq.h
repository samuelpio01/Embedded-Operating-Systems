#ifndef __CIRQ_H
#define __CIRQ_H

#define MAX 	5

typedef struct cirque
{
	int arr[MAX];
		int front, rear, cnt;
}cirque_t;

void cq_init(cirque_t *q);
void cq_push(cirque_t *q, int val);
int cq_pop(cirque_t *q);
int cq_peek(cirque_t *q);
int cq_full(cirque_t *q);
int cq_empty(cirque_t *q);

#endif
