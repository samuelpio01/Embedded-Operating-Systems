#include "3_cirq.h"


void cq_init(cirque_t *q)
{
	q->front = -1;
	q->rear = -1;
	q->cnt= 0;
}

void cq_push(cirque_t *q, int val)
{
	q->rear = (q->rear + 1) % MAX;
	q->arr[q->rear] = val;
	q->cnt++;
}

int cq_pop(cirque_t *q)
{
	q->front = (q->front + 1) % MAX;
	q->cnt--;
	return q->arr[q->front];
}

int cq_peek(cirque_t *q)
{
	int next = (q->front +1) % MAX;
	return q->arr[next];
}

int cq_full(cirque_t *q)
{
	return (q->cnt == MAX);
}

int cq_empty(cirque_t *q)
{
	return (q->cnt == 0);
}
