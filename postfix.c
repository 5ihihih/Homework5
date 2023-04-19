#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20
/* stack ������ �켱������ ��������, lparen = 0 ���� ���� */

typedef enum{
    lparen = 0,     /* ( ���� ��ȣ */
    rparen = 9,     /* ) ������ ��ȣ*/
    times = 7,      /* * ���� */
    divide = 6,     /* / ������ */
    plus = 5,       /* + ���� */
    minus = 4,      /* - ���� */
    operand = 1     /* �ǿ����� */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];     
char postfixExp[MAX_EXPRESSION_SIZE];
char postfixStack[MAX_STACK_SIZE];
int evalStack[MAX_STACK_SIZE];

int postfixStackTop = -1;       
int evalStackTop = -1;
int evalResult = 0;

void postfixPush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();

int main()
{
    printf("[----- [����ȭ] [2022078036] -----]");
    
    char command;
    do{
        printf("-------------------------------------------------------\n");
        printf(" Infix to Postfix, then Evaluation\n");
        printf("-------------------------------------------------------\n");
        printf(" Infix=i, Postfix=p, Eval=e, Debug=d, Reset=r, Quit=q \n");
        printf("-------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch(command) {
            case 'i': case 'I':     //'i' �Ǵ� 'I'�� �Է¹����� ������ �Է¹޴´�
                getInfix();
                break;
            case 'p': case 'P':
                toPostfix();
                break;
            case 'e': case 'E':
                evaluation();
                break;
            case 'd': case 'D':
                debug();
                break;
            case 'r': case 'R':
                reset();
                break;
            case 'q': case 'Q':
                break;
            default:
                printf("\n >>>>> Concentration!! <<<<<\n");
                break;
        }
    }while(command != 'q' && command != 'Q');
    
    return 1;
}

void postfixPush(char x)    //���ؿ��� top�� ���� ��ġ�� ���� ����
{
    postfixStack[++postfixStackTop] = x;
}

char postfixPop()
{
    char x;
    if(postfixStackTop == -1)   //���ؿ� �ƹ��͵� ���ٸ� '\0'����
        return '\0';
    else {                      //x�� top�� ��ġ�� ���ڸ� �����ϰ� top-1�� �� �� x���� 
        x = postfixStack[postfixStackTop--];
        return x;
    }

}

void evalPush(int x)
{
    evalStack[++evalStackTop] = x;  //top�� ���� ��ġ�� x����
}

int evalPop()
{
    if(evalStackTop == -1)      //������ ����ִٸ� -1�� ����
        return -1;
    else                        //������ ������� �ʴٸ� top�� ��ġ�� ���� ����
        return evalStack[evalStackTop--];
}

void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s", infixExp);      //����ǥ��� ������ �Է¹޴´�
}

/*���ڸ� �켱������ ��ȯ�� �����ϴ� �Լ�*/
precedence getToken(char symbol)
{
    switch(symbol) {
    case '(' : return lparen;
    case ')' : return rparen;
    case '+' : return plus;
    case '-' : return minus;
    case '/' : return divide;
    case '*' : return times;
    default : return operand;
    }
}

/*�켱������ ��ȯ�ϴ� �Լ�*/
precedence getPriority(char x)
{
    return getToken(x);
}

void charCat(char* c){
    if (postfixExp == '\0')
        strncpy(postfixExp, c, 1);
    else
        strncat(postfixExp, c, 1);
}

void toPostfix(){
    char *exp = infixExp;       //�迭 infixExp�� ù��° ������ �ּҸ� ������exp�� ����
    char x; 

    while(*exp != '\0'){        //���Ұ� ������� ������ �ݺ�
        if(getPriority(*exp) == operand){        //���Ұ� ������ ��� postfixExp�� ���� ����
            x = *exp;
            charCat(&x);
        }
        else if(getPriority(*exp) == lparen) {   //���Ұ� ')'�� ��� postfixstack�� ���� ')'����
            postfixPush(*exp);
        }
        else if(getPriority(*exp) == rparen){    //���Ұ� '('�� ��� ���ؿ��� ')'�� ���� ������ ���ڸ� postfixExp�� ����
            while( (x = postfixPop()) != '(' ) {
                charCat(&x);
            }
        }
        //top�� �ִ� ������ �켱������ infixExp�� �ִ� ������ �켱�������� ũ�ų� ���ٸ� ���ڸ� postfixExp�� �����Ѵ�
        else{                                    
            while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp)){
                x = postfixPop();
                charCat(&x);
            }
            postfixPush(*exp);
        }
        exp++;
    }

    while(postfixStackTop != -1){       //���ؿ� ���ڰ� �ִٸ� postfixExp�� ������ top�� ��ġ�� ���� ����
        x = postfixPop();
        charCat(&x);
    }
}

void debug(){   //���� ���ڿ��� ����ϴ� �Լ�
    printf("\n---DEBUG\n");
    printf("infixExp = %s\n", infixExp);
    printf("postExp = %s\n", postfixExp);
    printf("eval result = %d\n", evalResult);
    printf("postfixStack : ");
    
    for(int i = 0; i < MAX_STACK_SIZE; i++)
        printf("%c ", postfixStack[i]);
    
    printf("\n");
}

void reset(){   //���ڿ��� �����ϴ� �Լ�
    infixExp[0] = '\0';     
    postfixExp[0] = '\0';

    for(int i = 0; i < MAX_STACK_SIZE; i++)
        postfixStack[i] = '\0';

    postfixStackTop = -1;
    evalStackTop = -1;
    evalResult = 0;
}

void evaluation(){
    int opr1, opr2, i;
    int length = strlen(postfixExp);    
    char symbol;
    evalStackTop = -1;

    for(i = 0; i < length; i++){
        symbol = postfixExp[i];
        
        if(getToken(symbol) == operand) {   //������ postfixExp�� �ִ� ���� evalStack�� ����
            evalPush(symbol - '0');         
        }
        else {
            opr2 = evalPop();   //evalStack�� �ִ� �� ����� �����´�
            opr1 = evalPop();
            
            switch(getToken(symbol)) {      //�� ����� ������ evalStack�� ����
                case plus: evalPush(opr1 + opr2); break;
                case minus: evalPush(opr1 - opr2); break;
                case times: evalPush(opr1 * opr2); break;
                case divide: evalPush(opr1 / opr2); break;
                default: break;
            }
        }
    }

    evalResult = evalPop();  //����� ����
}