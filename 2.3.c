#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFERSIZE 100


typedef struct node {
    int sid;
    int courseCode;
    struct node *prev_s_ptr;
    struct node *next_s_ptr;
    struct node *prev_c_ptr;
    struct node *next_c_ptr;

} Node;

//Node graphIndex = (Node) {.sid=0, .courseCode=0, NULL, NULL, NULL, NULL};
//Node *graphIndex_ptr = &graphIndex;
Node *studentIndex[1000002] = {NULL};
Node *courseIndex[1000002] = {NULL};


Node *createNode(int sid, int courseCode);

Node *addNode(int sid, int courseCode);

Node *findNode(int sid, int courseCode);

void dropNode(int sid, int courseCode);

Node *createNode(int sid, int courseCode) {
    Node *node_ptr = malloc(sizeof(Node));
    *node_ptr = (Node) {sid, courseCode, NULL, NULL, NULL, NULL};
    // node_ptr->sid = sid;
    // node_ptr->courseCode = courseCode;

    return node_ptr;
}


Node *nextStudent(Node *pNode) {
    if (pNode != NULL) {
        return pNode->next_s_ptr;
    }
    return NULL;
}


Node *nextCourse(Node *pNode) {
    if (pNode != NULL) {
        return pNode->next_c_ptr;
    }
    return NULL;
}

Node *findNode(int sid, int courseCode) {

    if (studentIndex[sid] == NULL) {
        return NULL;
    }
    if (courseIndex[courseCode] == NULL) {
        return NULL;
    }
    Node *nextNode = studentIndex[sid];
    do {
        if (nextNode->courseCode == courseCode) {
            return nextNode;
        } else {
            nextNode = nextStudent(nextNode);
        }
    } while (nextNode != NULL);
    return NULL;

    /* //Node *index = graphIndex_ptr;
    //if (sid == 0 && courseCode == 0) return index;
     * if (sid <= courseCode) {
         //traverse from sid
         //int hasNext = nextNode == NULL ? 0 : 1;
         if (nextNode) {
             do {
                 //if (nextNode != NULL) {
                 if (nextNode->sid == sid) {
                     if (nextNode->courseCode == courseCode) {
                         return nextNode;
                     } else {
                         nextNode = nextCourse(nextNode);
                     }
                 } else {
                     nextNode = nextStudent(nextNode);
                 }
                 //} else { return NULL; }
             } while (nextNode);
             return NULL;
         } else return NULL;
     } else {//traverse from course
         if (nextNode) {
             do {
                 //if (nextNode != NULL) {
                 if (nextNode->courseCode == courseCode) {
                     if (nextNode->sid == sid) {
                         return nextNode;
                     } else {
                         nextNode = nextStudent(nextNode);
                     }
                 } else {
                     nextNode = nextCourse(nextNode);
                 }
                 //} else { return NULL; }
             } while (nextNode);
             return NULL;
         } else return NULL;
     }*/
}

Node *addNode(int sid, int courseCode) {
    Node *targetNode = findNode(sid, courseCode);
    if (targetNode != NULL) {
        return targetNode;
    } else {
        targetNode = createNode(sid, courseCode);
        int initSI = 0, initCI = 0;
        initSI = studentIndex[sid] == NULL;
        if (initSI) {
            studentIndex[sid] = targetNode;
        }
        initCI = courseIndex[courseCode] == NULL;
        if (initCI) {
            courseIndex[courseCode] = targetNode;
        }
        //-------------------------------------------
        Node *nextSNode = studentIndex[sid];
        if (!initSI) {
            int linked = 0;
            if (nextSNode->next_s_ptr == NULL && nextSNode->courseCode > courseCode) {
                studentIndex[sid] = targetNode;
                targetNode->next_s_ptr = nextSNode;
                nextSNode->prev_s_ptr = targetNode;
                linked = 1;
            }
            if (nextSNode->next_s_ptr == NULL && nextSNode->courseCode < courseCode) {
                //studentIndex[sid] = targetNode;
                targetNode->prev_s_ptr = nextSNode;
                nextSNode->next_s_ptr = targetNode;
                linked = 1;
            }
            while (nextSNode->next_s_ptr != NULL) {
                if (nextSNode->courseCode < courseCode) {
                    nextSNode = nextSNode->next_s_ptr;
                } else if (nextSNode->prev_s_ptr == NULL) {
                    studentIndex[sid] = targetNode;
                    targetNode->next_s_ptr = nextSNode;
                    nextSNode->prev_s_ptr = targetNode;
                    linked = 1;
                    break;
                } else if (nextSNode->prev_s_ptr != NULL) {
                    targetNode->prev_s_ptr = nextSNode->prev_s_ptr;
                    targetNode->next_s_ptr = nextSNode;
                    nextSNode->prev_s_ptr->next_s_ptr = targetNode;
                    nextSNode->prev_s_ptr = targetNode;
                    linked = 1;
                    break;
                }
            }
            if (!linked && nextSNode->next_s_ptr == NULL && nextSNode->prev_s_ptr != NULL &&
                nextSNode->courseCode > courseCode) {
                targetNode->prev_s_ptr = nextSNode->prev_s_ptr;
                targetNode->next_s_ptr = nextSNode;
                nextSNode->prev_s_ptr->next_s_ptr = targetNode;
                nextSNode->prev_s_ptr = targetNode;
                linked = 1;
            }
            if (!linked && nextSNode->courseCode < courseCode) {
                nextSNode->next_s_ptr = targetNode;
                targetNode->prev_s_ptr = nextSNode;
            }
        }
//----------------------------------------------------------------------
        Node *nextCNode = courseIndex[courseCode];
        if (!initCI) {
            int linked = 0;
            if (nextCNode->next_c_ptr == NULL && nextCNode->sid > sid) {
                courseIndex[courseCode] = targetNode;
                targetNode->next_c_ptr = nextCNode;
                nextCNode->prev_c_ptr = targetNode;
                linked = 1;
            }
            if (nextCNode->next_c_ptr == NULL && nextCNode->sid < sid) {
                //courseIndex[courseCode] = targetNode;
                targetNode->prev_c_ptr = nextCNode;
                nextCNode->next_c_ptr = targetNode;
                linked = 1;
            }
            while (nextCNode->next_c_ptr != NULL) {
                if (nextCNode->sid < sid) {
                    nextCNode = nextCNode->next_c_ptr;
                } else if (nextCNode->prev_c_ptr == NULL) {
                    courseIndex[courseCode] = targetNode;
                    targetNode->next_c_ptr = nextCNode;
                    nextCNode->prev_c_ptr = targetNode;
                    linked = 1;
                    break;
                } else if (nextCNode->prev_c_ptr != NULL) {
                    targetNode->prev_c_ptr = nextCNode->prev_c_ptr;
                    targetNode->next_c_ptr = nextCNode;
                    nextCNode->prev_c_ptr->next_c_ptr = targetNode;
                    nextCNode->prev_c_ptr = targetNode;
                    linked = 1;
                    break;
                }
            }
            if (!linked && nextCNode->next_c_ptr == NULL && nextCNode->prev_c_ptr != NULL && nextCNode->sid > sid) {
                targetNode->prev_c_ptr = nextCNode->prev_c_ptr;
                targetNode->next_c_ptr = nextCNode;
                nextCNode->prev_c_ptr->next_c_ptr = targetNode;
                nextCNode->prev_c_ptr = targetNode;
                linked = 1;
            }
            if (!linked && nextCNode->sid < sid) {
                nextCNode->next_c_ptr = targetNode;
                targetNode->prev_c_ptr = nextCNode;
            }
        }
        //linkNode(sid, courseCode, targetNode);
    }
    return targetNode;
}


void dropNode(int sid, int courseCode) {
    Node *targetNode = findNode(sid, courseCode);
    if (targetNode == NULL) {
        return;
    }
    if (targetNode->prev_s_ptr != NULL)targetNode->prev_s_ptr->next_s_ptr = targetNode->next_s_ptr;
    else if (targetNode->next_s_ptr != NULL) studentIndex[sid] = targetNode->next_s_ptr;
    else studentIndex[sid] = NULL;

    if (targetNode->next_s_ptr != NULL)targetNode->next_s_ptr->prev_s_ptr = targetNode->prev_s_ptr;

    if (targetNode->prev_c_ptr != NULL)targetNode->prev_c_ptr->next_c_ptr = targetNode->next_c_ptr;
    else if (targetNode->next_c_ptr != NULL) courseIndex[courseCode] = targetNode->next_c_ptr;
    else courseIndex[courseCode] = NULL;

    if (targetNode->next_c_ptr != NULL)targetNode->next_c_ptr->prev_c_ptr = targetNode->prev_c_ptr;

    free(targetNode);

}

void printStudent(int sid) {
    if (studentIndex[sid] == NULL) {
        puts("NIL");
        return;
    }
    // int c=0;
    printf("%d", studentIndex[sid]->courseCode);
    Node *nextNode = studentIndex[sid]->next_s_ptr;
    while (nextNode != NULL) {
        printf(" %d", nextNode->courseCode);
        nextNode = nextStudent(nextNode);
    }
    printf("\n");
    return;

}

void printCourse(int courseCode) {
    if (courseIndex[courseCode] == NULL) {
        puts("NIL");
        return;
    }
    printf("%d", courseIndex[courseCode]->sid);
    Node *nextNode = courseIndex[courseCode]->next_c_ptr;
    while (nextNode != NULL) {
        printf(" %d", nextNode->sid);
        nextNode = nextCourse(nextNode);
    }
    printf("\n");
    return;
}

//debug
/*void sighandler(int sig) {
    while (1);
}*/

int main() {
    // debug
    //signal(SIGSEGV, sighandler);

    char buffer[BUFFERSIZE];
    while (fgets(buffer, BUFFERSIZE, stdin)) /* break with ^D or ^Z */
    {
        char operation[100];
        int S = 0, C = 0;
        sscanf(buffer, "%s", operation);

        if (strcmp(operation, "ADD") == 0) {
            sscanf(buffer, "%s %d %d", operation, &S, &C);
            addNode(S, C);
        } else if (strcmp(operation, "DROP") == 0) {
            sscanf(buffer, "%s %d %d", operation, &S, &C);
            dropNode(S, C);
        } else if (strcmp(operation, "PRINTS") == 0) {
            sscanf(buffer, "%s %d", operation, &S);
            printStudent(S);
        } else if (strcmp(operation, "PRINTC") == 0) {
            sscanf(buffer, "%s %d", operation, &C);
            printCourse(C);
        }
    }
    return 0;


}
