#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;				//char타입 자료형 element 선언
typedef struct {					//element형 배열과 int형 변수를 갖는 자료형 QueueType 선언
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
	QueueType *cQ = createQueue();		//QueueType형 포인터변수 cQ를 선언하고 함수 createQueue()를 호출해 리턴값을 대입한다
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
		case 'i': case 'I':			//'i' 또는 'I'를 입력받으면 데이터를 입력받는다
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':			//'d' 또는 'D'를 입력받으면 데이터를 제거한다
			deQueue(cQ, &data);
			break;
		case 'p': case 'P':			//'p' 또는 'P'를 입력받으면 배열 queue에 저장된 값을 출력한다
			printQ(cQ);
			break;
		case 'b': case 'B':			//'b' 또는 'B'를 입력받으면 front와 rear의 값을 출력한다
			debugQ(cQ);
			break;
		case 'q': case 'Q':			//'q' 또는 'Q'를 입력받으면 할당받은 메모리를 해제한다
   	        freeQueue(cQ);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');	//'q' 또는 'Q'를 입력받지 않았을 경우 반복을 수행한다


	return 1;
}

/*QueueType만큼의 크기를 cQ에 동적할당하고, front와 rear값을 0으로 초기화한 후 cQ를 반환하는 함수*/
QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;
}

/*할당받은 메모리를 해제하는 함수*/
int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1;
    free(cQ);
    return 1;
}

/*큐에 넣을 값을 입력받는 함수*/
element getElement()               
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


/* 큐가 비었으면 1, 비지 않았으면 0을 리턴하는 함수 */
int isEmpty(QueueType *cQ)
{
	if(cQ->front == cQ->rear) return 1;
	else return 0;
}

/* 큐에 남은 공간이 없으면 1을 있으면 0을 리턴하는 함수 */
int isFull(QueueType *cQ)
{
	if(cQ->front == (cQ->rear + 1)%MAX_QUEUE_SIZE) return 1;
	else return 0;
}


/* 큐에 문자를 삽입하는 함수 */
void enQueue(QueueType *cQ, element item)
{
	if(isFull(cQ))
		printf("큐가 가득 찼습니다");
	else{
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;	//rear에 rear의 다음 인덱스값을 넣는다
		cQ->queue[cQ->rear] = item;					//인덱스가 rear인 공간에 문자 item을 넣는다
	}
}

/* 큐의 문자를 삭제하는 함수 */
void deQueue(QueueType *cQ, element *item)
{	
	if(isEmpty(cQ)) 
		printf("큐가 비었습니다");	//큐가 비었다면 함수 종료
    else {
		cQ->front = (cQ->front + 1)%MAX_QUEUE_SIZE;	//큐가 비지 않았다면 front에 front 다음 인덱스값을 넣고, 다음 인덱스부터 큐가 시작되도록 한다  
		*item = cQ->queue[cQ->front];
	}
}

void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;		//원형큐에서 front 다음 원소의 인덱스 값을 first에 대입한다
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;		//원형큐에서 rear 다음 원소의 인덱스 값을 last에 대입한다

	printf("Circular Queue : [");

	i = first;
	while(i != last){					//first와 last가 다를 경우(배열이 empty가 아닐 경우) 배열의 원소를 차례로 출력한다
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;		//i에 i 다음 인덱스의 값을 대입한다

	}
	printf(" ]\n");

}

/*현재 front와 rear의 값을 보여주는 함수*/
void debugQ(QueueType *cQ)
{
	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {								//front가 i이라면 0을 출력
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);			//front가 0이라면 생략
															//0이 아니라면 i와 인덱스가 i인 배열의 원소를 출력
	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);	//fornt값과 rear값 출력
}
