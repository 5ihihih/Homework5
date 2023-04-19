#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20
/* stack 내에서 우선순위는 내림차순, lparen = 0 가장 낮음 */

typedef enum{
    lparen = 0,     /* ( 왼쪽 괄호 */
    rparen = 9,     /* ) 오른쪽 괄호*/
    times = 7,      /* * 곱셈 */
    divide = 6,     /* / 나눗셈 */
    plus = 5,       /* + 덧셈 */
    minus = 4,      /* - 뺄셈 */
    operand = 1     /* 피연산자 */
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
    printf("[----- [오인화] [2022078036] -----]");
    
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
            case 'i': case 'I':     //'i' 또는 'I'를 입력받으면 수식을 입력받는다
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

void postfixPush(char x)    //스텍에서 top의 다음 위치에 문자 대입
{
    postfixStack[++postfixStackTop] = x;
}

char postfixPop()
{
    char x;
    if(postfixStackTop == -1)   //스텍에 아무것도 없다면 '\0'리턴
        return '\0';
    else {                      //x에 top에 위치한 문자를 대입하고 top-1을 한 후 x리턴 
        x = postfixStack[postfixStackTop--];
        return x;
    }

}

void evalPush(int x)
{
    evalStack[++evalStackTop] = x;  //top의 다음 위치에 x삽입
}

int evalPop()
{
    if(evalStackTop == -1)      //스텍이 비어있다면 -1을 리턴
        return -1;
    else                        //스텍이 비어있지 않다면 top에 위치한 원소 리턴
        return evalStack[evalStackTop--];
}

void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s", infixExp);      //중위표기식 수식을 입력받는다
}

/*문자를 우선순위로 변환해 리턴하는 함수*/
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

/*우선순위를 반환하는 함수*/
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
    char *exp = infixExp;       //배열 infixExp의 첫번째 원소의 주소를 포인터exp에 대입
    char x; 

    while(*exp != '\0'){        //원소가 비어있을 때까지 반복
        if(getPriority(*exp) == operand){        //원소가 숫자일 경우 postfixExp에 숫자 대입
            x = *exp;
            charCat(&x);
        }
        else if(getPriority(*exp) == lparen) {   //원소가 ')'일 경우 postfixstack에 문자 ')'대입
            postfixPush(*exp);
        }
        else if(getPriority(*exp) == rparen){    //원소가 '('일 경우 스텍에서 ')'가 나올 때까지 문자를 postfixExp에 대입
            while( (x = postfixPop()) != '(' ) {
                charCat(&x);
            }
        }
        //top에 있는 문자의 우선순위가 infixExp에 있는 문자의 우선순위보다 크거나 같다면 문자를 postfixExp에 대입한다
        else{                                    
            while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp)){
                x = postfixPop();
                charCat(&x);
            }
            postfixPush(*exp);
        }
        exp++;
    }

    while(postfixStackTop != -1){       //스텍에 문자가 있다면 postfixExp에 스텍의 top에 위치한 문자 대입
        x = postfixPop();
        charCat(&x);
    }
}

void debug(){   //현재 문자열을 출력하는 함수
    printf("\n---DEBUG\n");
    printf("infixExp = %s\n", infixExp);
    printf("postExp = %s\n", postfixExp);
    printf("eval result = %d\n", evalResult);
    printf("postfixStack : ");
    
    for(int i = 0; i < MAX_STACK_SIZE; i++)
        printf("%c ", postfixStack[i]);
    
    printf("\n");
}

void reset(){   //문자열을 리셋하는 함수
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
        
        if(getToken(symbol) == operand) {   //상수라면 postfixExp에 있는 수를 evalStack에 삽입
            evalPush(symbol - '0');         
        }
        else {
            opr2 = evalPop();   //evalStack에 있던 두 상수를 가져온다
            opr1 = evalPop();
            
            switch(getToken(symbol)) {      //두 상수를 연산해 evalStack에 삽입
                case plus: evalPush(opr1 + opr2); break;
                case minus: evalPush(opr1 - opr2); break;
                case times: evalPush(opr1 * opr2); break;
                case divide: evalPush(opr1 / opr2); break;
                default: break;
            }
        }
    }

    evalResult = evalPop();  //결과값 대입
}