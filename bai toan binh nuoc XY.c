#include <stdio.h>
#include <stdlib.h>

#define tankcapacity_X 9 // suc chua binh X
#define tankcapacity_Y 4 //suc chua binh Y
#define empty 0
#define goal 6 //Muc tieu 
#define Maxlength 100 // su dung cai dat ngan xxep (stack)

const char* action[] = {"First State","pour Water Full X","pour Water Full Y","pour Water Empty X","pour Water Empty Y","pour Water X to Y","pour Water Y to X"};

typedef struct MyStruct
{
    int x;
    int y;
}State;

//Khoi tao trang thai binh
void makenullState (State *state) {
    state -> x=0;
    state -> y=0;
}
void print_State (State state) {
     printf("\n X:%d --- Y:%d",state.x,state.y);
 }

// kiem tra trang thai muc tieu 
int goalcheck (State state) {
    return (state.x==gold || state.y == goal);
} 

//lam day binh X
int pourWaterfullX(State cur_state, State *result) {
    if (cur_state.x < tankcapacity_X) {
        result->x = tankcapacity_X;
        result->y = cur_state.y;
        return 1;
    }
    return 0;
}

// lam day binh Y 
int pourWaterfullY(State cur_state, State *result) {
    if (cur_state.y < tankcapacity_Y) {
        result->y = tankcapacity_Y;
        result->x =  cur_state.x;
        return 1;
    }
    return 0;
}

// lam rong nuoc binh X 
int pourWaterEmptyX (State cur_state, State *result) {
    if (cur_state.x>0) {
        result->x = empty ;
        result->y = cur_state.y;
        return 1;
    }
    return 0;
}

// lam rong binh Y
int pourWaterEmptyY (State cur_state, State *result) {
    if(cur_state.y>0) {
        result->y = empty ;
        result->x = cur_state.x;
        return 1;
    }
    return 0;
}

// chuyen tu X sang Y
int pourWaterXY (State cru_state, State *result) {
    if (cur_state.x>0 && cur_state.y<tankcapacity_Y ) {
        result->x = max(cur_state.x - (tankcapacity_Y - cur_state.y), empty);
        result->y = min(cur_state.x + cur_state.y, tankcapacity_Y);
        return 1;
    } 
    return 0;
}

//chuyen tu Y sang X
int pourWaterYX (State cru_state, State *result) {
    if (cur_state.y>0 && cur_state.x<tankcapacity_X ) {
        result->y = max(cur_state.y - (tankcapacity_X - cur_state.x), empty);
        result->x = min(cur_state.y + cur_state.x, tankcapacity_X);
        return 1;
    } 
    return 0;
}

// Goi cac phep toan trang thai 
int call_operator(State cur_state, State *result, int option) {
    switch (option) {
        case 1: return pourWaterFullX ( cur_state, result) ;
        case 2: return pourWaterFullY ( cur_state, result) ;
        case 3: return pourWaterEmptyX ( cur_state, result) ;
        case 4: return pourWaterEmptyY ( cur_state, result) ;
        case 5: return pourWaterXY ( cur_state, result) ;
        case 6: return pourWaterYX ( cur_state, result) ;
        default: printf("Error calls opertators")
        return 0;
    }
}

int main () {
    State cur_state = {5,4}, result;
     printf("Trang thai bat dau") ; 
     print_State(cur_state) ;
     int opt;
     for (opt= 1; opt < 6; opt++) {
         int thuchien = call_opertator (cur_state, &result,opt) ;
         if (thuchien==1) {
             printf("\n Hanh dong %s thanh cong",action[opt]);
             pritn_State(result);
         }
         else 
            printf ("\n Hanh dong %s KHONG thanh cong", action[p]) ;
     }
     return 0;
}