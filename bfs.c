#include <stdio.h>

#define MAX 100

int queue[MAX];
int front = -1, rear = -1;

void enqueue(int value) {
    if (rear == MAX - 1) {
        printf("Queue overflow\n");
        return;
    }
    if (front == -1) front = 0;
    queue[++rear] = value;
}

int dequeue() {
    if (front == -1 || front > rear) {
        return -1; 
    }
    return queue[front++];
}
int isQueueEmpty() {
    return (front == -1 || front > rear);
}

void BFS(int adj[MAX][MAX], int n, int start) {
    int visited[MAX] = {0}; 

    enqueue(start);
    visited[start] = 1;

    while (!isQueueEmpty()) {
        int v = dequeue();
        printf("%d ", v);

        for (int i = 0; i < n; i++) {
            if (adj[v][i] == 1 && visited[i] == 0) {
                enqueue(i);
                visited[i] = 1;
            }
        }
    }
}

int main() {
    int n, start;
    int adj[MAX][MAX];

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &adj[i][j]);
        }
    }

    printf("Enter the starting vertex (0 to %d): ", n - 1);
    scanf("%d", &start);

    printf("BFS traversal starting from vertex %d:", start);
    BFS(adj, n, start);

    return 0;
}
