#include <bits/stdc++.h>
#define CHUNK_MAX_RECORDS 100
using namespace std;

void merge(int arr[], int l, int m, int r);
void mergeSort(int arr[], int l, int r);
FILE *openFile(char *fileName, char *mode);

int noOfChunks;
struct heapNode {
    int data = 0;
    int fileNumber = 0;

    heapNode() {
        data = 0;
        fileNumber = 0;
    }
};

class custom_heap {
    struct heapNode *heapArr;
    int size;
    int capacity;

  public:
    custom_heap(int heapSize) {
        heapArr = new struct heapNode[heapSize];
        size = 0;
        capacity = heapSize;
    }

    int left(int i) { return (2 * i + 1); }
    int right(int i) { return (2 * i + 2); }
    int parent(int i) { return (i - 1) / 2; }

    void mySwap(int x, int y) {
        int d1 = heapArr[x].data;
        heapArr[x].data = heapArr[y].data;
        heapArr[y].data = d1;

        int f1 = heapArr[x].fileNumber;
        heapArr[x].fileNumber = heapArr[y].fileNumber;
        heapArr[y].fileNumber = f1;
    }

    void minHeapify(int i) {
        int lt = left(i), rt = right(i);
        int smallest = i;
        if (lt < size && heapArr[lt].data < heapArr[i].data)
            smallest = lt;
        if (rt < size && heapArr[rt].data < heapArr[i].data)
            smallest = rt;
        if (smallest != i) {
            mySwap(i, smallest);
            minHeapify(smallest);
        }
    }

    void insert(int d, int f) {
        if (size == capacity) {
            struct heapNode *tempArr = new struct heapNode[2 * capacity];
            capacity = 2 * capacity;
            for (int i = 0; i < size; i++) {
                tempArr[i].data = heapArr[i].data;
                tempArr[i].fileNumber = heapArr[i].fileNumber;
            }
            delete[] heapArr;
            heapArr = tempArr;
        }
        heapArr[size].data = d;
        heapArr[size].fileNumber = f;
        size++;
        display();
        int i = size - 1;
        while (i != 0 && (heapArr[parent(i)].data > heapArr[i].data)) {
            mySwap(i, parent(i));
            i = parent(i);
        }
    }

    struct heapNode extractMin() {
        if (size == 0) {
            cout << "Calling extractMin on empty heap not permitted...Exiting" << endl;
            exit(0);
        }
        if (size == 1) {
            size--;
            return heapArr[0];
        }
        mySwap(0, size - 1);
        size--; // the size itself is reduced now
        minHeapify(0);
        return heapArr[size]; // worried about out of bounds? the size itself reduced by 1 :P
    }

    struct heapNode getMin() {
        return heapArr[0];
    }

    void replaceRootMinHeapify(int d) {
        heapArr[0].data = d;
        minHeapify(0);
    }

    void deleteRoot() {
        heapArr[0].data = INT_MIN;
        struct heapNode ignore = extractMin();
    }

    void display() {
        cout << "size is: " << size << endl;
        cout << "capacity is: " << capacity << endl;
        for (int i = 0; i < size; i++) {
            cout << i << ": (" << heapArr[i].data << "," << heapArr[i].fileNumber << ") ";
        }
        cout << endl;
        cout << "=================================" << endl;
    }
};

void mergeSort(int arr[], int l, int r) {
    if (r > l) {
        int m = l + (r - l) / 2; // just to avoid overflow
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1; // no. of elements in left sub array from l to (m)
    int n2 = r - m;     // no. of elements in right sub array from (m + 1) to r

    int left[n1], right[n2];
    for (int i = 0; i < n1; i++) {
        left[i] = arr[l + i];
    }
    for (int j = 0; j < n2; j++) {
        right[j] = arr[m + j + 1];
    }

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (left[i] <= right[i]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }

    while (i < n1)
        arr[k++] = left[i++];
    while (j < n2)
        arr[k++] = right[j++];
}

FILE *openFile(char *fileName, char *mode) {
    FILE *fp = fopen(fileName, mode);
    if (fp == NULL) {
        perror("Error while opening file!!!\n");
        exit(EXIT_FAILURE);
    }
    return fp;
}

void sortChunkWise(char *inBigFileName) {
    FILE *in = openFile(inBigFileName, (char *)"r");

    bool isThereMoreInput = true;
    int outFileNameInInt = 0;

    while (isThereMoreInput) {
        int tempArr[CHUNK_MAX_RECORDS];
        int i = 0;
        for (i = 0; i < CHUNK_MAX_RECORDS; i++) {
            if (fscanf(in, "%d,", &tempArr[i]) != 1) {
                isThereMoreInput = false;
                break;
            }
        }

        if (isThereMoreInput || i != 0) {
            mergeSort(tempArr, 0, i - 1);
            string outFileNameStr = to_string(outFileNameInInt) + ".txt";
            char outFileNameCharArr[outFileNameStr.size()];
            strcpy(outFileNameCharArr, outFileNameStr.c_str());
            FILE *outSmallSortedChunk = openFile(outFileNameCharArr, (char *)"w");
            for (int j = 0; j < i; j++) {
                if (j == (i - 1))
                    fprintf(outSmallSortedChunk, "%d\n", tempArr[j]);
                else
                    fprintf(outSmallSortedChunk, "%d,", tempArr[j]);
            }
            fclose(outSmallSortedChunk);
        }
        outFileNameInInt++;
    }
    noOfChunks = outFileNameInInt;
    fclose(in);
}

void mergeFiles(char *outBigFileName) {
    FILE *in[noOfChunks];
    for (int i = 0; i < noOfChunks; i++) {
        string inFileNameStr = to_string(i) + ".txt";
        char inFileNameCharArr[inFileNameStr.size()];
        strcpy(inFileNameCharArr, inFileNameStr.c_str());
        in[i] = openFile(inFileNameCharArr, (char *)"r");
    }

    FILE *out = openFile(outBigFileName, (char *)"w");
    custom_heap myHeap(noOfChunks);
    int i;

    // simply load 1 value from each file
    for (i = 0; i < noOfChunks; i++) {
        int tempData, tempFileNumber;
        if (fscanf(in[i], "%d,", &tempData) != 1) // read one element from each file and add it to the heap
            break;                                // if it breaks do not add anything to heap, just break
        // tempData as the heapNode's data and i as the heapNode's fileNumber
        myHeap.insert(tempData, i);
    }

    int count = 0;
    while (count != i) {
        struct heapNode myMinNode = myHeap.getMin();
        int tempData;
        fprintf(out, "%d ", myMinNode.data);
        if (fscanf(in[myMinNode.fileNumber], "%d,", &tempData) != 1) {
            count++;
            myHeap.deleteRoot();
        } else {
            // add tempData to the root and minHeapify(0)
            // in this case you would have read from the same file, hence no need to update fileNumber
            myHeap.replaceRootMinHeapify(tempData);
        }
    }

    for (int i = 0; i < noOfChunks; i++)
        fclose(in[i]);
    fclose(out);
}

int main(int argc, char *argv[]) {
    char *inBigFileName, *outBigFileName;
    if (argc != 3) {
        cout << "usage: pass input and output file names as command line arguments" << endl;
        return 0;
    }

    inBigFileName = argv[1];
    outBigFileName = argv[2];
    sortChunkWise(inBigFileName);
    mergeFiles(outBigFileName);
    return 0;
}
