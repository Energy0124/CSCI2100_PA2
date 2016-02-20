#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXSIZE 1000

typedef struct stack {
    int data[MAXSIZE];
    int top;
} Stack;


void push(Stack *s, int d);

int pop(Stack *s);

int peek(Stack *s);

int isEmpty(Stack *s);

//int comparePos(int d[], int size, int a, int b);

int getPos(int d[], int size, int a);

void push(Stack *s, int d) {
    (*s).top++;
    (*s).data[(*s).top] = d;

}


int pop(Stack *s) {
    int d = (*s).data[(*s).top];
    (*s).top--;
    return d;
}

int peek(Stack *s) {
    if (!isEmpty(s)) {
        return (*s).data[(*s).top];
    } else return -1;
}

int isEmpty(Stack *s) {
    if ((*s).top < 0) {
        return 1;
    } else return 0;
}

/*
int comparePos(int d[], int size, int a, int b) {
    int i = 0, al = -1, bl = -1;
    for (i = 0; i < size; ++i) {
        if (d[i] == a) {
            al = i;
        }
        if (d[i] == b) {
            bl = i;
        }

    }
    if (al != -1 && bl != -1) {
        if (bl > al) {
            return 1;
        }
        if (al > bl) {
            return -1;
        } else return 0;

    } else return -2;

}
*/
int getPos(int d[], int size, int a) {
    int i = 0, al = -1;
    for (i = 0; i < size; ++i) {
        if (d[i] == a) {
            al = i;
        }


    }
    if (al != -1) {
        return al;

    } else return -1;

}


int main() {
    int t = 0;
    scanf("%d", &t);
    int i = 0;
    for (i = 0; i < t; i++) {
        int failed = 0;
        int n = 0;
        scanf("%d", &n);
        int target[MAXSIZE];
        int j = 0;
        for (j = 0; j < n; j++) {
            scanf("%d", &target[j]);
        }
        Stack s1, s2;
        s1.top = -1;
        s2.top = -1;

        Stack *s1_ptr = &s1;
        Stack *s2_ptr = &s2;

        int output[MAXSIZE];
        int oh = 0;
        int th = 0;
        int k = 1;
        for (k = 1; k <= n; k++) {

            int f1 = 0, f2 = 0;
            int checkAgain = 1, pushed = 0;
            //PUSH_K:
            while (checkAgain) {
                checkAgain = 0;

                if (k == target[th]) {
                    push(s1_ptr, k);
                    output[oh] = pop(s1_ptr);
                    oh++;
                    th++;
                    pushed = 1;

                } else if (!isEmpty(s1_ptr) && peek(s1_ptr) == target[th]) {
                    output[oh] = pop(s1_ptr);
                    oh++;
                    th++;
                    checkAgain = 1;
                    //goto PUSH_K;
                } else if (!isEmpty(s2_ptr) && peek(s2_ptr) == target[th]) {
                    output[oh] = pop(s2_ptr);
                    oh++;
                    th++;
                    checkAgain = 1;
                    // goto PUSH_K;
                }
            }
            if (!pushed) {
                if (isEmpty(s1_ptr)) {
                    push(s1_ptr, k);
                } else if (isEmpty(s2_ptr)) {
                    push(s2_ptr, k);
                } else {
                    int s1l = getPos(target, n, peek(s1_ptr));
                    int s2l = getPos(target, n, peek(s2_ptr));
                    int kl = getPos(target, n, k);
                    if (s1l < s2l) {
                        if (kl < s2l) {
                            push(s2_ptr, k);
                        } else {
                            f1 = 1;
                        }
                    }
                    if (s2l <= s1l || f1) {
                        if (kl < s1l) {
                            push(s1_ptr, k);
                        } else {
                            f2 = 1;
                        }
                    }

                    if (f1 && f2) {
                        failed = 1;
                        break;
                    }
                }
            }
        }
        int m = th;
        for (m = th; m < n; m++) {
            if (peek(s1_ptr) == target[th]) {
                output[oh] = pop(s1_ptr);
                oh++;
                th++;

            } else if (peek(s2_ptr) == target[th]) {
                output[oh] = pop(s2_ptr);
                oh++;
                th++;

            } else {
                failed = 1;
                break;
            }
        }

        if (th == n) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }

    }

    return 0;
}
