#include <stdio.h>
#include <string.h>

#define MAXN 1002
int const NEINF = -1;

int targetPermutation[MAXN];
int precalculatedMax[MAXN];
int bipartiteGraph[MAXN];
int adjacencyMatrix[MAXN][MAXN];
int N;
int noSolution = 0;

void reset();

void colouringAndCheckConflict(int i, int c);

void checkAdjacencyAndDye();

void colouringAndCheckConflict(int i, int c) {
    bipartiteGraph[i] = c;
    int j;
    for (j = 1; j <= N; j++) {
        if (adjacencyMatrix[i][j]) {
            if (bipartiteGraph[j] == c) //conflict : not a bipartite graph
            {
                noSolution = 1;
                return;
            }
            if (!bipartiteGraph[j]) {
                colouringAndCheckConflict(j, 3 - c); // color the opposite color 1<->2
            }
        }
    }
}

void checkAdjacencyAndDye() {
    /* 231 for sortable
     * i<j<k, S[k]<S[i]<S[J]
     * 312 for generatable
     * k<i<j, S[i]<S[J]<S[k]
     * DONE: Modify the algorithm to make it right for generation instead of sortable
    */
    int i, j;
    precalculatedMax[0] = NEINF;
    for (i = 1; i <= N; i++) {
        precalculatedMax[i] = targetPermutation[i];
        if (precalculatedMax[i - 1] > precalculatedMax[i])
            precalculatedMax[i] = precalculatedMax[i - 1];
    }
    for (i = 1; i <= N - 1; i++) {
        for (j = i + 1; j <= N; j++) {
            if (targetPermutation[i] < targetPermutation[j] && precalculatedMax[i - 1] > targetPermutation[j]) {
                adjacencyMatrix[i][j] = adjacencyMatrix[j][i] = 1;
            }
        }
    }
    for (i = 1; i <= N; i++) {
        if (!bipartiteGraph[i] && !noSolution) {
            colouringAndCheckConflict(i, 1);
        }
    }
}

void reset() {
    memset(adjacencyMatrix, 0, sizeof(adjacencyMatrix));
    memset(bipartiteGraph, 0, sizeof(bipartiteGraph));
    memset(targetPermutation, 0, sizeof(targetPermutation));
    memset(precalculatedMax, 0, sizeof(precalculatedMax));
    N = 0;
    noSolution = 0;
}

int main() {

    int t;
    scanf("%d", &t);
    int k;
    for (k = 1; k <= t; k++) {


        int i;
        scanf("%d", &N);
        for (i = 1; i <= N; i++) {
            scanf("%d", &targetPermutation[i]);

        }
        checkAdjacencyAndDye();
        if (!noSolution) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
        reset();
    }

    return 0;
}

