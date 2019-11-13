#define STACK_INIT_SIZE	100;
#define STACKINCREMENT 10;

typedef struct{
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;

Status InitStack(SqStack &S)
{
	S.base=(SElemType *)malloc(STACK_INIT_SIZE * sizeof(ElemType));
	if(!S.base)exit(OVERFLOW);
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}

Status GetTop(SqStack S,SElemType &e)
{
	if(S.top == S.base) return ERROR;
	e = *(S.top-1);//先移位-1再赋值
	return OK;
}

Status Push(SqStack &S, SElemType e)
{
	if(S.top-S.base >= S.stacksize){//栈满
		S.base= (ElemType *)realloc(S.base,S.(stacksize+STACKINCREMENT)*sizeof(ElemType));
	if(!s.base)exit(OVERFLOW);
	
	S.top = S.base+S.stacksize;
	S.stacksize += STACKINCREMENT;
	}
	*S.top++ = e;//先进栈再移位+1
	return OK;
}

Status Pop(SqStack &S, SElemType)
{
	if(S.top == S.base) return ERROR;
	e = *(--S.top);//先出栈再移位-1
	return OK;
}

void conversion(){
	InitStack(S);
	scanf("%d",N);
	while(N){
		Push(S,N%8);
		N = N/8;
	}
	while(!StackEmpty(s)){
		Pop(S,e);
		printf("%d",e);
	}
}

void kuohao(){
	InitStack(S);
	scanf(%d,N);
	ch = getchar();
	while(ch != EOF){
		switch(ch){
			case '(':
			case '[': Push(S,ch);	break;
			case ']': if(*(S.top) == '[')
						Pop(S,c);
						else return ERROR;
						break;
			case ')': if(*(S.top) == '(') Pop(S,c);
						else return ERROR;
						break;
			default: break;
		}
	}
}

void LineEdit()
{
	InitStack(S);
	ch = getchar();
	while(ch != EOF){
		while(ch!=EOF&&ch!='\n'){
			swithc(ch){
				case '#':Pop(S,c);	break;
				case '@':ClearStack(S);	break;
				default: Push(S,ch);	break;
			}
			ch = getchar();
		}
		//TODO：将栈底到栈内的字符传送至调用过程的数据区
		ClearStack(S);
		if(ch != EOF) ch = getchar();
	}
}

typedef struct{
	int	ord;
	PosType seat;
	int di;
}SElemType;

Status MazePtath(MazeType maze, PosType start, PosType end){
	InitStack(S);
	curpos = start;
	curstep = 1;
	do{
		if(Pass(curpos)){
			FootPrint(curpos);
			e = (curstep,curpos,1);
			Push(S,e);
			if(curpos==end) return(true);
			curpos = NextPos(curpos,1);
			curstep++;
		}//if
		else{
			if(!StackEmpty(S)){
				Pop(S,e);
				while(e,di==4&&!StackEmpty(S)){
					ParkPrint(e,seat); Pop(S,e);
				}//while
				if(e.di<4){
					e.di++; Push(S,e);
					curpos=NextPos(e.seat,e.di)
				}//if
			}//if
		}//else
	}while(!StackEmpty(S));
	return (FALSE);
}

OperandType EvaluateExpression(){
	InitStack(OPTR); Push(OPTR,'#');
	InitStack(OPND); c=getchar();
	while(c!='#' || GetTop(OPTR)!='#')