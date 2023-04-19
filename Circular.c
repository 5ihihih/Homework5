#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;				//charŸ�� �ڷ��� element ����
typedef struct {					//element�� �迭�� int�� ������ ���� �ڷ��� QueueType ����
	element queue[MAX_QUEUE_SIZE];	
	int front, rear;
}QueueType;


QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();

int main(void)
{
	QueueType *cQ = createQueue();		//QueueType�� �����ͺ��� cQ�� �����ϰ� �Լ� createQueue()�� ȣ���� ���ϰ��� �����Ѵ�
	element data;
	char command;

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':			//'i' �Ǵ� 'I'�� �Է¹����� �����͸� �Է¹޴´�
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':			//'d' �Ǵ� 'D'�� �Է¹����� �����͸� �����Ѵ�
			deQueue(cQ, &data);
			break;
		case 'p': case 'P':			//'p' �Ǵ� 'P'�� �Է¹����� �迭 queue�� ����� ���� ����Ѵ�
			printQ(cQ);
			break;
		case 'b': case 'B':			//'b' �Ǵ� 'B'�� �Է¹����� front�� rear�� ���� ����Ѵ�
			debugQ(cQ);
			break;
		case 'q': case 'Q':			//'q' �Ǵ� 'Q'�� �Է¹����� �Ҵ���� �޸𸮸� �����Ѵ�
   	        freeQueue(cQ);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');	//'q' �Ǵ� 'Q'�� �Է¹��� �ʾ��� ��� �ݺ��� �����Ѵ�


	return 1;
}

/*QueueType��ŭ�� ũ�⸦ cQ�� �����Ҵ��ϰ�, front�� rear���� 0���� �ʱ�ȭ�� �� cQ�� ��ȯ�ϴ� �Լ�*/
QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;
}

/*�Ҵ���� �޸𸮸� �����ϴ� �Լ�*/
int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1;
    free(cQ);
    return 1;
}

/*ť�� ���� ���� �Է¹޴� �Լ�*/
element getElement()               
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


/* ť�� ������� 1, ���� �ʾ����� 0�� �����ϴ� �Լ� */
int isEmpty(QueueType *cQ)
{
	if(cQ->front == cQ->rear) return 1;
	else return 0;
}

/* ť�� ���� ������ ������ 1�� ������ 0�� �����ϴ� �Լ� */
int isFull(QueueType *cQ)
{
	if(cQ->front == (cQ->rear + 1)%MAX_QUEUE_SIZE) return 1;
	else return 0;
}


/* ť�� ���ڸ� �����ϴ� �Լ� */
void enQueue(QueueType *cQ, element item)
{
	if(isFull(cQ))
		printf("ť�� ���� á���ϴ�");
	else{
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;	//rear�� rear�� ���� �ε������� �ִ´�
		cQ->queue[cQ->rear] = item;					//�ε����� rear�� ������ ���� item�� �ִ´�
	}
}

/* ť�� ���ڸ� �����ϴ� �Լ� */
void deQueue(QueueType *cQ, element *item)
{	
	if(isEmpty(cQ)) 
		printf("ť�� ������ϴ�");	//ť�� ����ٸ� �Լ� ����
    else {
		cQ->front = (cQ->front + 1)%MAX_QUEUE_SIZE;	//ť�� ���� �ʾҴٸ� front�� front ���� �ε������� �ְ�, ���� �ε������� ť�� ���۵ǵ��� �Ѵ�  
		*item = cQ->queue[cQ->front];
	}
}

void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;		//����ť���� front ���� ������ �ε��� ���� first�� �����Ѵ�
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;		//����ť���� rear ���� ������ �ε��� ���� last�� �����Ѵ�

	printf("Circular Queue : [");

	i = first;
	while(i != last){					//first�� last�� �ٸ� ���(�迭�� empty�� �ƴ� ���) �迭�� ���Ҹ� ���ʷ� ����Ѵ�
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;		//i�� i ���� �ε����� ���� �����Ѵ�

	}
	printf(" ]\n");

}

/*���� front�� rear�� ���� �����ִ� �Լ�*/
void debugQ(QueueType *cQ)
{
	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {								//front�� i�̶�� 0�� ���
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);			//front�� 0�̶�� ����
															//0�� �ƴ϶�� i�� �ε����� i�� �迭�� ���Ҹ� ���
	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);	//fornt���� rear�� ���
}
