#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct CentralityArray
{
    int userid;
    double centrality;
    double central;
} CentralityArray;

struct AdjListNode
{
    int dest;
    struct AdjListNode *next;
};

struct AdjList
{
    int nodevalue;
    struct AdjListNode *head;
};

struct Graph
{
    int V;
    struct AdjList *array;
};

void selectionSort(CentralityArray *CA, int n)
{
    int i, j, max_index;

    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (CA[j].centrality > CA[i].centrality)
            {
                double tmp = CA[j].centrality;
                CA[j].centrality = CA[i].centrality;
                CA[i].centrality = tmp;
                swab(&CA[j].userid, &CA[i].userid);
            }
        }
    }
}

struct AdjListNode *newAdjListNode(int dest)
{
    struct AdjListNode *newNode =
        (struct AdjListNode *)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

struct Graph *createGraph(int V)
{
    struct Graph *graph =
        (struct Graph *)malloc(sizeof(struct Graph));
    graph->V = V;

    graph->array =
        (struct AdjList *)malloc(V * sizeof(struct AdjList));

    int i;
    for (i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}

void addEdge(struct Graph *graph, int src, int dest)
{
    int i = 0;
    while (graph->array[i].nodevalue != src)
    { // src is a user, we find its index in the array
        i++;
    }
    struct AdjListNode *newNode = newAdjListNode(dest); // we create a new node and change dest, where we get the dest value
    newNode->next = graph->array[i].head;               // next of the new node shows the node in the array
    graph->array[i].head = newNode;                     // we place the node in that index in the array															//we place the node in that index in the array
}

void printGraph(struct Graph *graph)
{
    FILE *file;
    file = fopen("ADJList.txt", "a");
    int v;
    for (v = 0; v < graph->V; ++v)
    {

        struct AdjListNode *pCrawl = graph->array[v].head;
        fprintf(file, "\nAdjacency list of vertex %d\n%d ", graph->array[v].nodevalue, graph->array[v].nodevalue);
        while (pCrawl)
        {
            fprintf(file, "-> %d", pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        fprintf(file, "\n");
    }

    // printf("\nADJList.txt FILE HAS BEEN CREATED TO SHOW ALL USERS' NEIGHBORS!!\n");
}

void CountEdges(struct Graph *graph, int **mat, int *User, int length)
{
    int v;
    int i = 0;
    int count;
    for (v = 0; v < length; ++v)
    {
        struct AdjListNode *pCrawl = graph->array[v].head;
        count = 0;
        while (pCrawl)
        {
            pCrawl = pCrawl->next;
            count++;
        }

        mat[i][0] = graph->array[v].nodevalue;
        mat[i][1] = count;
        i++;
    }
}

void CountFollowers(struct Graph *graph, int **mat, int *User, int lenght)
{
    int v, z, userid;

    int i = 0;
    int count;
    for (z = 0; z < lenght; z++)
    {
        count = 0;
        for (v = 0; v < lenght; v++)
        {
            struct AdjListNode *pCrawl = graph->array[v].head;

            while (pCrawl)
            {

                if (pCrawl->dest == graph->array[z].nodevalue)
                {
                    count++;
                }
                pCrawl = pCrawl->next;
            }
        }

        mat[z][0] = graph->array[z].nodevalue;
        mat[z][1] = count;
    }
}

void findUSERS(int *array, int *len, char *filename)
{
    int i = 0, j = 0, founded = 0;
    FILE *fp;
    char buff[255];
    fp = fopen(filename, "r");
    fscanf(fp, "%*[^\n]\n");
    while (!feof(fp))
    {
        char *arr;
        fscanf(fp, "%s", buff);
        arr = strtok(buff, ",");
        j++;
        founded = 0;
        for (i = 0; i < j; i++)
        {
            if (array[i] == atoi(arr))
            {
                founded = 1;
            }
        }
        if (founded == 1)
        {
            j--;
        }
        else
        {
            *len += 1;
            array[i - 1] = atoi(arr);
        }
        while (arr != NULL)
        {
            arr = strtok(NULL, ",");
            j++;
            founded = 0;
            for (i = 0; i < j; i++)
            {
                if (array[i] == atoi(arr))
                {
                    founded = 1;
                }
            }
            if (founded == 1)
            {
                j--;
            }
            else
            {
                *len += 1;
                array[i - 1] = atoi(arr);
            }
            arr = strtok(NULL, ",");
        }
    }
    fclose(fp);
}

void printMatrix(int **array, int row)
{
    int i, j;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < 1; j++)
        {
            printf("\n%d  USER'S %d THERE IS ONE ", array[i][j], array[i][j + 1]);
        }
    }
}

void printSubMatrix(int **array, int row, int start)
{
    int i, j;
    for (i = start; i < row; i++)
    {
        for (j = 0; j < 1; j++)
        {

            printf(" User id:%d   \n", array[i][j]);
            // printf("%d",array[i][j + 1]);
             
        }
    }
}

float Average(int **array, int row)
{
    float count = 0;
    int i, j;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < 1; j++)
        {
            count += array[i][j + 1];
        }
    }
    return count / row;
}

void swap(int *x, int *y)
{
    int tmp;
    tmp = *x;
    *x = *y;
    *y = tmp;
}

int partition(int **A, int p, int r)
{
    int x = A[r][1]; // pivot
    int i = p - 1, j;
    for (j = p; j < r; j++)
    {
        if (A[j][1] <= x)
        {
            i = i + 1;
            swap(&A[i][1], &A[j][1]);
            swap(&A[i][0], &A[j][0]);
        }
    }
    i = i + 1;
    swap(&A[i][1], &A[j][1]);
    swap(&A[i][0], &A[j][0]);
    return i;
}

void quick_sort(int **A, int p, int r)
{
    if (p < r)
    {
        int t = (rand() % (r - p + 1) + p);
        swap(&A[t][1], &A[r][1]);
        swap(&A[t][0], &A[r][0]);

        int q = partition(A, p, r);
        quick_sort(A, p, q - 1);
        quick_sort(A, q + 1, r);
    }
}

void CreateAdjanList(struct Graph *graph, char *filename)
{
    int lsource = -1, ldestination = -2, source, destination; // Function that creates ADJList by looking at the data read from the file
    FILE *fp;
    char buff[255];
    fp = fopen(filename, "r");
    fscanf(fp, "%*[^\n]\n");
    while (!feof(fp) && fp)
    {
        char *array;
        fscanf(fp, "%d,%d", &source, &destination); 
        if (lsource != source || ldestination != destination)
        {
            lsource = source;
            ldestination = destination;
            addEdge(graph, source, destination); // addEdge Function is called with these two parameters and continues until the file is finished
        }
    }
    fclose(fp);
}

// void printArray(int *array, int len)
// {
//     int i;
//     for (i = 0; i < len; i++)
//     {
//         printf("\n%d. USER ID == %d \n", i, array[i]);
//     }
// }

struct qnode
{
    int data;
    struct qnode *next;
};
typedef struct qnode QNODE;

struct queue
{
    int count;
    QNODE *front;
    QNODE *rear;
};
typedef struct queue QUEUE;

void initialize(QUEUE *q)
{
    q->count = 0;
    q->front = NULL;
    q->rear = NULL;
}

int isempty(QUEUE *q)
{

    return (q->rear == NULL);
}

void enqueue(QUEUE *q, int value)
{

    QNODE *tmp;
    tmp = malloc(sizeof(QNODE));
    tmp->data = value;
    tmp->next = NULL;
    if (!isempty(q))
    {
        q->rear->next = tmp;
        q->rear = tmp;
    }
    else
    {
        q->front = q->rear = tmp;
    }
    q->count++;
}

int dequeue(QUEUE *q)
{
    QNODE *tmp;
    int n = q->front->data;
    tmp = q->front;
    q->front = q->front->next;
    q->count--;

    if (q->count == 0)
    {
        q->rear = NULL;
        q->front = NULL;
    }
    else
    {
        free(tmp);
    }
    return n;
}

void displaypath(int from, int *pred, int *distance, struct Graph *graph, int foruser)
{
    FILE *file;
    file = fopen("Path.txt", "a"); 
    int fromindex = 0;
    while (from != graph->array[fromindex].nodevalue)
    { // we find the user we keep in the array and the index in the array.
        fromindex++;
    }
    if (distance[fromindex] != 9999)
    { // if the path is not found, it does not enter

        fprintf(file, "\nFOR USER %d \nDistance == %d \n", foruser, distance[fromindex]);

        fprintf(file, "%d <-- ", from);
        while (pred[fromindex] != 0 && pred[fromindex] != -1)
        { // In the pred array, the starting node is 0, so it enters while as long as the start is not reached.
            fprintf(file, "%d <-- ", pred[fromindex]);
            from = pred[fromindex]; 
            fromindex = 0;
            while (from != graph->array[fromindex].nodevalue)
            { // we find the index
                fromindex++;
            }
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

void measure(int from, int *pred, int *distance, struct Graph *graph, int foruser, CentralityArray *arr, float *Count, QUEUE *CQ)
{
    int i = 0, present;
    int fromindex = 0; // Function for Betweenness Centrality measure
    while (from != graph->array[fromindex].nodevalue)
    {
        fromindex++; 
    }
    if (distance[fromindex] != 9999)
    { // if the path is not found, it does not enter

        while (pred[fromindex] != 0)
        {
            present = 0;
            while (pred[fromindex] != foruser && pred[fromindex] != arr[i].userid)
            {
                i++; // If it is not equal to the starting nodes, we equalize the value in the pred search with the reason in the array and find the index
            }
            if (pred[fromindex] != foruser)
            {

                arr[i].central++;       // Increasing the value of central while searching for centrality
                QNODE *tmp = CQ->front; // Queuey creates a Qnode to navigate
                while (tmp)
                {
                    if (tmp->data == i)
                    {
                        present = 1;
                    } // Checks Queuey to see if this index exists before, if so it sets present 1.

                    tmp = tmp->next;
                }
            
            if (!present)
            {                   
                enqueue(CQ, i);  // Queue assigns the index of the node that changes the central of the node.
            }
        }
        i = 0;
        from = pred[fromindex];
        fromindex = 0;
        while (from != graph->array[fromindex].nodevalue)
        {
            fromindex++; // finds its index
        }
    }
    *Count = *Count + 1; 
}
}

void BFS(struct Graph *graph)
{
    int k;
    for (k = 0; k < graph->V; k++)
    { 
        int startuserid = graph->array[k].nodevalue;
        QUEUE *Q = (QUEUE *)malloc(sizeof(QUEUE)); // creating a queue
        initialize(Q);
        int i = 0, parent = 0, child = 0;
        int *visited = (int *)malloc(graph->V * sizeof(int)); // Creates visited, pred and distance arrays 
        int *pred = (int *)malloc(graph->V * sizeof(int));
        int *distance = (int *)malloc(graph->V * sizeof(int));
        for (i = 0; i < graph->V; i++)
        {
            visited[i] = 0;
        }
        for (i = 0; i < graph->V; i++)
        {
            pred[i] = -1;
        }
        for (i = 0; i < graph->V; i++)
        {
            distance[i] = 9999;
        }
        int process;
        i = 0;
        while (startuserid != graph->array[i].nodevalue)
        {
            i++; 
        }
        distance[i] = 0;      
        enqueue(Q, startuserid); // puts the user id into the queue
        pred[i] = 0;            // pred makes the index in the array 0
        visited[i] = 1;         // marks visited
        while (!isempty(Q))
        {                         // rotate until it finds the queue
            process = dequeue(Q); // dequeueing the user ID to the process
            parent = 0;
            while (process != graph->array[parent].nodevalue)
            {
                parent++;// finds the index of the user ID
            }
            struct AdjListNode *pCrawl = graph->array[parent].head;// creates a node to visit its neighbors
            while (pCrawl)
            { // If there is a neighbor, it enters
                child = 0;
                while (pCrawl->dest != graph->array[child].nodevalue)
                {
                    child++; // finds the index of its neighbor
                }
                if (visited[child] == 0)
                { // If that item is not visited, it puts it in the queue
                    enqueue(Q, pCrawl->dest);
                    if (distance[child] > distance[parent] + 1)		// The value in the distance array is entered if the distance of its parent is greater than +1
                    {                                           // If the value in the distance array is greater than the distance of its parent +1, it is entered
                        distance[child] = distance[parent] + 1;// setting the new distance
                        pred[child] = process;                // sets the index in the pred array to 0
                        visited[child] = 1;                     // MARKS visited
                    }
                }
                pCrawl = pCrawl->next; // moves to the next neighbor
            }
        } // finally startuserid finds the shortest paths for the users it can reach
        for (i = 0; i < graph->V; i++)
        {                                                           					   // returns the array inside for to check the users that can be visited
            int path = graph->array[i].nodevalue;                   
            if (path != startuserid)           						   // If path is equal to itself, it does not enter the file
                displaypath(path, pred, distance, graph, startuserid);   // here it calls the displaypath function
        }
    } // and repeats this for all users
    // printf("\nSHORTEST ROUTES IN Path.txt FILE!!\n");
}


void CentralityMeasure(struct Graph *graph, CentralityArray *carray)
{
    int k, i, parent; // This function is for measuring Centrality and its algorithm is similar to the BFS function above
    int startuserid;

    QUEUE *CQ = (QUEUE *)malloc(sizeof(QUEUE)); // create a queue in the meausre function to keep which users are among them 
    initialize(CQ);
    for (k = 0; k < graph->V; k++)
    {
        float count;
        startuserid = graph->array[k].nodevalue;
        QUEUE *Q = (QUEUE *)malloc(sizeof(QUEUE));
        initialize(Q);
        int i = 0, parent = 0, child = 0;
        int *visited = (int *)malloc(graph->V * sizeof(int));
        int *pred = (int *)malloc(graph->V * sizeof(int));
        int *distance = (int *)malloc(graph->V * sizeof(int));
        for (i = 0; i < graph->V; i++)
        {
            visited[i] = 0;
        }
        for (i = 0; i < graph->V; i++)
        {
            pred[i] = -1;
        }
        for (i = 0; i < graph->V; i++)
        {
            distance[i] = 9999;
        }
        int process;
        i = 0;
        while (startuserid != graph->array[i].nodevalue)
        {
            i++;
        }
        distance[i] = 0;
        enqueue(Q, startuserid);
        pred[i] = 0;
        visited[i] = 1;
        while (!isempty(Q))
        {
            process = dequeue(Q);
            parent = 0;
            while (process != graph->array[parent].nodevalue)
            {
                parent++;
            }
            struct AdjListNode *pCrawl = graph->array[parent].head;
            while (pCrawl)
            {
                child = 0;
                while (pCrawl->dest != graph->array[child].nodevalue)
                {
                    child++;
                }
                if (visited[child] == 0)
                {
                    enqueue(Q, pCrawl->dest);
                    if (distance[child] > distance[parent] + 1)
                    {
                        distance[child] = distance[parent] + 1;
                        pred[child] = process;
                        visited[child] = 1;
                    }
                }
                pCrawl = pCrawl->next;
            }
        }
        count = 0;  // we reset count to keep track of how many shortest paths user d1 has
        for (i = 0; i < graph->V; i++)
        { // From d1 we call the measure function for all users except d1
            int path = graph->array[i].nodevalue;
            if (path != startuserid)
                measure(path, pred, distance, graph, startuserid, carray, &count, CQ);
        }
        int index;
		while (!isempty(CQ))
		{												   // In the meausre function, the queue keeps track of which users' values have changed until the queue is empty.
			index = dequeue(CQ);						   // If the user's value has changed, that user's index is dequeued
			double number = carray[index].central / count; // in central, we keep track of how many times that node is among the roads, and in count, we keep track of how many roads there are.
			carray[index].central = 0;
			carray[index].centrality += number; // number we keep the quotient of these two and add it to the centrality of the node
		}
	}								 // These operations are performed for all d1 -- d2 paths
	selectionSort(carray, graph->V); // We sort the struct array where Centrality is kept with the selection sort function
}

int main()
{
    int i, j, index;
    int source, destination;
    srand(time(NULL));

    char filename[40];
    printf("ENTER THE NAME OF THE FILE TO BE READ:\n");
    scanf("%s", &filename);

    int *USERS = (int *)malloc(2000 * sizeof(int)); 
	int size = 0;									

	findUSERS(USERS, &size, filename); //  retrieves the file

	struct Graph *graph = createGraph(size); // Creating a Graph
	for (i = 0; i < size; i++)
	{
		graph->array[i].nodevalue = USERS[i];
	}

	CreateAdjanList(graph, filename); // Creating adjacent list

    

    int **UC = (int **)malloc(size * sizeof(int *));
    for (index = 0; index < size; index++)
    { // MATRIX THAT HOLDS USER FOLLOW COUNT
		UC[index] = (int *)malloc(2 * sizeof(int));
	}

	int **UF = (int **)malloc(size * sizeof(int *));
	for (index = 0; index < size; index++)
	{ // MATRIX THAT KEPT USER FOLLOWER COUNT
		UF[index] = (int *)malloc(2 * sizeof(int));
	}

	CentralityArray *CA = (CentralityArray *)malloc(size * sizeof(CentralityArray));
	for (i = 0; i < size; i++)
	{
		CA[i].centrality = 0;
		CA[i].central = 0; // Struct array for centrality measure value
		CA[i].userid = USERS[i];
	}

    CountEdges(graph, UC, USERS, size); // Count of follows


    CountFollowers(graph, UF, USERS, size); // Count of followers 


    quick_sort(UC, 0, size - 1);
    quick_sort(UF, 0, size - 1);



    printf("\n**************  TOP 10 USERS WHO FOLLOW THE MOST     **************\n\n");
	printSubMatrix(UC, size, size - 10);

	printf("\n**************   10 USERS WITH THE MOST NO OF FOLLOWERS       **************\n\n");
	printSubMatrix(UF, size, size - 10);

	printf("\n*************		AVERAGE NUMBER OF CONNECTIONS	**************\n\n");
	printf("\nAVERAGE NUMBER OF FOLLOWS = %f\n", Average(UC, size));
	printf("\nAVERAGE NUMBER OF FOLLOWERS = %f\n", Average(UF, size));

	printf("\n**************		MEDIAN	**************\n ");
	int n = (size + 1) / 2 - 1;
	printf("\nMEDIA VALUE OF FOLLOW NUMBER = %d\n", UC[n][1]);
	printf("\nMEDIA VALUE OF FOLLOWER NUMBER = %d\n", UF[n][1]);

	BFS(graph); // Function used to find out shortest path between all the nodes 

	CentralityMeasure(graph, CA); // Function that measures betweenness centrality

	printf("\n\n************TOP 10 CENTRAL USERS ******************\n");

	for (i = 0; i < 10; i++)
	{
		printf("\n %d USER has %.5lf CENTRALITY \n", CA[i].userid, CA[i].centrality);
	}

	return 0;
}