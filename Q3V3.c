#include <stdio.h>
#include <stdlib.h>

#define MAXN 1002
int const NEINF = -1;

typedef struct stack {
    int top;
    int S[MAXN];


} Stack;

void ins(Stack *stack, int k) {
    stack->S[++(stack->top)] = k;
}

int tp(Stack *stack) {
    return stack->S[stack->top];
}

void pop(Stack *stack) {
    stack->top--;
}

int S[MAXN];
int F[MAXN];
int bel[MAXN];
int adjm[MAXN][MAXN];
int N, top1, top2;

void tryToPop(int *should, int *shouldIndex);

Stack T[3];

void init() {
    int j;
    for (j = 0; j < 3; ++j) {
        T[j].top = 0;
    }
    int i;
    //freopen("twostack.in","r",stdin);
    //freopen("twostack.out","w",stdout);
    scanf("%d", &N);
    for (i = 1; i <= N; i++) {
        scanf("%d", &S[i]);
    }
}

void noanswer() {
    printf("0");
    exit(0);
}

void color(int i, int c) {
    bel[i] = c;
    int j;
    for (j = 1; j <= N; j++) {
        if (adjm[i][j]) {
            if (bel[j] == c) //conflict : not a bipartite graph
            {
                noanswer();
            }
            if (!bel[j]) {
                color(j, 3 - c); // color the opposite color 1<->2
            }
        }
    }
}

void dye() {
    /* 231 for sortable
     * i<j<k, S[k]<S[i]<S[J]
     * 312 for generatable
     * k<i<j, S[i]<S[J]<S[k]
     * DONE: Modify the algorithm to make it right for generation instead of sortable
    */
    int i, j;
    F[0] = NEINF;
    for (i = 1; i <= N; i++) {
        F[i] = S[i];
        if (F[i - 1] > F[i])
            F[i] = F[i - 1];
    }
    for (i = 1; i <= N - 1; i++) {
        for (j = i + 1; j <= N; j++) {
            if (S[i] < S[j] && F[i - 1] > S[j]) {
                adjm[i][j] = adjm[j][i] = 1;
            }
        }
    }
    for (i = 1; i <= N; i++) {
        if (!bel[i]) {
            color(i, 1);
        }
    }
}
/*
void tryToPop(int *should, int *shouldIndex) {
    *should=S[*shouldIndex];
    while (tp(&T[1]) == *should || tp(&T[2]) == *should) {
        if (tp(&T[1]) == *should) {
            pop(&T[1]);
            printf("b");
            if (*should != S[N])
                printf(" ");
            (*shouldIndex)++;
            //should++;
        }
        else {
            pop(&T[2]);
            printf("d");
            if (*should != S[N])
                printf(" ");
            (*shouldIndex)++;
            //should++;
        }
    }
}*/
/*
 * //TODO: Fix process output
 *  */
void solve() {
    printf("1");
    exit(0);
    /*
       int i, should = 1, s,shouldIndex=1;
       for (i = 1; i <= N; i++) {

           //tryToPop(&should, &shouldIndex);
           should=S[shouldIndex];
           while (tp(&T[1]) == should || tp(&T[2]) == should) {
               if (tp(&T[1]) == should) {
                   pop(&T[1]);
                   printf("b");
                   if (should != S[N])
                       printf(" ");
                   shouldIndex++;
                   //should++;
               }
               else {
                   pop(&T[2]);
                   printf("d");
                   if (should != S[N])
                       printf(" ");
                   shouldIndex++;
                   //should++;
               }
           }
           s = bel[i];
           if (s == 1) {
               ins(&T[1], i);
               printf("a ");

           }
           else {
               ins(&T[2], i);
               printf("c ");

           }
           //tryToPop(&should, &shouldIndex);
           should=S[shouldIndex];
           while (tp(&T[1]) == should || tp(&T[2]) == should) {
               if (tp(&T[1]) == should) {
                   pop(&T[1]);
                   printf("b");
                   if (should != S[N])
                       printf(" ");
                   shouldIndex++;
                   //should++;
               }
               else {
                   pop(&T[2]);
                   printf("d");
                   if (should != S[N])
                       printf(" ");
                   shouldIndex++;
                   //should++;
               }
           }
       }*/
}


int main() {
    init();
    dye();
    solve();
    return 0;
}