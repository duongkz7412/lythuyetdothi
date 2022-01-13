#include <stdio.h> ;
#include <stdlib.h> ;

#define tankcapacity_X 9 // suc chua binh X
#define tankcapacity_Y 4 //suc chua binh Y
#define empty 0
#define goal 6 //Muc tieu 
#define Maxlength 100 // su dung cai dat ngan xxep (stack)

const char* action[] = { "First State","pour Water Full X","pour Water Full Y","pour Water Empty X","pour Water Empty Y","pour Water X to Y","pour Water Y to X" };

typedef struct Node {
	State state; 
	struct Node* Parent;
	int no_function;
}Node;

typedef struct MyStruct
{
	int x;
	int y;
}State;

//khai bao cau truc stack luu trang thai duyet 
typedef struct {
	Node* Elements[Maxlength];
	int Top_idx;
}Stack; 

//Dua 1 phan tu len ngan xep
void push(Node* x, Stack* stack) {
	if (full_Stack(*stack))
		printf("Error!Stack is full");
	else{
		stack->Top_idx -= 1;
		stack->Elements[stack->Top_idx] = x;
	}
}

//khoi tao ngan xep rong 
void makeNull_Stack(Stack *stack) {
	stack->Top_idx = Maxlength;
}

//kiem tra xem ngan xep co rong hay khong 
int empty_Stack(Stack stack) {
	return stack.Top_idx == Maxlength;
}

//kiem tra xem ngan xep co day hay khong
int full_Stack(Stack stack) {
	return stack.Top_idx == 0;
}

//tra ve phan tu tren dinh ngan xep
Node* top(Stack stack) {
	if (!empty_Stack(stack))
		return stack.Elements[stack.Top_idx];
	return NULL;
}

//xoa phan tu tai dinh ngan xep
void pop(Stack *stack) {
	if (!empty_Stack(*stack))
		stack->Top_idx += 1;
	else pritnf("Error! Stack is empty");
}

// Tim trang thai trong Stack Open/Close
int find_Stae(State state, Stack openStack) {
	while (!empty_Stack(openStack)) {
		if (comparaStates(top(openStack)->state, state))
			return 1;
		pop(&openStack);
	}
	return 0;
}

// thuat toan duyet theo chieu sau 
Node* DFS_Algorithm(State state) {
	// khai bao hai ngan xep open va close 
	Stack Open_DFS;
	Stack Close_DFS;
	makeNull_Stack(&Open_DFS);
	makeNull_Stack(&Close_DFS);
	//tao nut trang thai cha
	Node* root = (Node*)malloc(sizeof(Node));
	root->state = state;
	root->Parent = NULL;
	root->no_function = 0;
	push(root, &Open_DFS);
	while (!empty_Stack(Open_DFS)){
		//lay mot dinh trong ngan xep
		Node* node = top(Open_DFS);
		pop(&Open_DFS);
		push(node, &Close_DFS);
		// kiem tra xme dinh lay ra co phai la trang thai muc tieu?
		if (goalcheck(node->state))
			return node;
		int opt;
		//Goi cac phep toan tren trang thai
		for (opt = 1;opt <= 6;opt++) {
			State newstate;
			makeNullState(&newstate);
			if (call_operator(node->state, &newstate, opt)) {
				// neu trang thai moi sinh ra da ton tai thi bo qua
				if(fint_State(newstate, Close_DFS) || fint_State(newstate,Open_DFS)) 
					continue ;
				//Neu trang thai moi chua ton thi them vao ngan xep
				Node* newNode = (Node*)malloc(sizeof(Node));
				newNode->state = newstate;
				newNode->Parent = node;
				newNode->no_function = opt;
				push(newNode, &Open_DFS);
			}
		}
	}
	return NULL;
}

//in ket qua chuyen nuoc de dat den trang thai muc tieu 
void print_WaysToGetGoal(Node* node) {
	Stack stackPrint;
	makeNull_Stack(&stackPrint);
	//Duyet nguoc ve nut parent
	while (node->Parent != NULL){
		push(node, &stackPrint);
		node = node->Parent;
	}
	push(node, &stackPrint);
// in ra thu tu hanh dong chuyen nuoc
	int no_action = 0;
	while (!empty_Stack(stackPrint)) {
		printf("\n Action %d: %s", no_action, action[top(stackPrint)->no_function]);
		print_State(top(stackPrint)->state);
		pop(&stackPrint);
		no_action++;
	}
}

int main() {
	State cur_state = { 0,0 };
	Node* p = DFS_Algorithm(cur_state);
	print_WaysToGetGoal(p);
	return 0;
}