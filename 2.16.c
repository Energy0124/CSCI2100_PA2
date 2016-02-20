#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXSIZE 100000

typedef struct stack {
    int data[MAXSIZE];
    int top;
} Stack;

void push(Stack *s, int d);

int pop(Stack *s);

int peek(Stack *s);

int isEmpty(Stack *s);

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
        Stack s;
        s.top = -1;
        Stack *s_ptr = &s;
        int output[MAXSIZE];
        int outputHead = 0;
        int targetHead = 0;
        char steps[2 * MAXSIZE];
        int stepCount = 0;
        int k = 1;
        for (k = 1; k <= n; k++) {
            int pushed = 0;
            while (!pushed) {
                if (k == target[targetHead]) {
                    push(s_ptr, k);
                    output[outputHead] = pop(s_ptr);
                    steps[stepCount] = 'S';
                    stepCount++;
                    outputHead++;
                    targetHead++;
                    pushed=1;
                } else if (!isEmpty(s_ptr) && peek(s_ptr) == target[targetHead]) {
                    output[outputHead] = pop(s_ptr);
                    steps[stepCount] = 'O';
                    stepCount++;
                    outputHead++;
                    targetHead++;
                    pushed = 0;
                } else {
                    push(s_ptr, k);
                    steps[stepCount] = 'I';
                    stepCount++;
                    pushed=1;
                }
            }
        }
        int m = targetHead;
        for (m = targetHead; m < n; m++) {
            if (peek(s_ptr) == target[targetHead]) {
                output[outputHead] = pop(s_ptr);
                steps[stepCount] = 'O';
                stepCount++;
                outputHead++;
                targetHead++;
            } else {
                failed = 1;
                break;
            }
        }

        if (targetHead == n) {
            int l = 0;
            for (l = 0; l < stepCount; ++l) {
                printf("%c", steps[l]);
            }
            printf("\n");
        } else {
            printf("Impossible\n");
        }
    }
    return 0;
}
