#include <bits/stdc++.h>
#define CHUNK_MAX_RECORDS 500000
#define ul unsigned long long
using namespace std;

void merge(ul arr[], int l, int m, int r);
void mergeSort(ul arr[], int l, int r);
FILE *openFile(char *fileName, char *mode);

int noOfChunks;
unsigned long long int noOfRecords = 0;

struct heapNode {
    ul data = 0;
    int fileNumber = 0;

    heapNode() {
        data = 0L;
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
        ul d1 = heapArr[x].data;
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
        if (rt < size && heapArr[rt].data < heapArr[smallest].data)
            smallest = rt;
        if (smallest != i) {
            mySwap(i, smallest);
            minHeapify(smallest);
        }
    }

    void insert(ul d, int f) {
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
        int i = size - 1;
        while (i != 0 && (heapArr[parent(i)].data > heapArr[i].data)) {
            mySwap(i, parent(i));
            i = parent(i);
        }
    }

    void deleteMin() {
        if (size == 0) {
            cout << "Calling deleteMin on empty heap not permitted...Exiting" << endl;
            exit(0);
        }
        if (size == 1) {
            size--;
        }
        mySwap(0, size - 1);
        size--; // the size itself is reduced now
        minHeapify(0);
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

    void replaceRootMinHeapify(ul d) {
        heapArr[0].data = d;
        minHeapify(0);
    }

    void deleteRoot() { deleteMin(); }

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

void mergeSort(ul arr[], int l, int r) {
    if (r > l) {
        int m = l + (r - l) / 2; // just to avoid overflow
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void merge(ul arr[], int l, int m, int r) {
    int n1 = m - l + 1; // no. of elements in left sub array from l to (m)
    int n2 = r - m;     // no. of elements in right sub array from (m + 1) to r

    ul left[n1] = {0L}, right[n2] = {0L};
    for (int i = 0; i < n1; i++) {
        left[i] = arr[l + i];
    }
    for (int j = 0; j < n2; j++) {
        right[j] = arr[m + 1 + j];
    }

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
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

void printArray(ul arr[]) {
    for (int i = 0; i < CHUNK_MAX_RECORDS; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void sortChunkWise(char *inBigFileName) {
    FILE *in = openFile(inBigFileName, (char *)"r");

    bool isThereMoreInput = true;
    int outFileNameInInt = 0;

    while (isThereMoreInput) {
        ul tempArr[CHUNK_MAX_RECORDS];
        int i = 0;
        for (i = 0; i < CHUNK_MAX_RECORDS; i++) {
            if (fscanf(in, "%llu,", &tempArr[i]) != 1) {
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
                    fprintf(outSmallSortedChunk, "%llu\n", tempArr[j]);
                else
                    fprintf(outSmallSortedChunk, "%llu,", tempArr[j]);
                noOfRecords++;
            }
            fclose(outSmallSortedChunk);
        }
        if (i != 0)
            outFileNameInInt++;
    }
    noOfChunks = outFileNameInInt;
    fclose(in);
}

void mergeFiles(char *outBigFileName) {
    cout << "mergeSort: noOfChunks is " << noOfChunks << endl;
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
        ul tempData;
        if (fscanf(in[i], "%llu,", &tempData) != 1) // read one element from each file and add it to the heap
            break;                                  // if it breaks do not add anything to heap, just break
        // tempData as the heapNode's data and i as the heapNode's fileNumber
        myHeap.insert(tempData, i);
    }
    int count = 0;
    while (count != i) {
        struct heapNode myMinNode = myHeap.getMin();
        ul tempData;
        noOfRecords--;
        if (noOfRecords == 0)
            fprintf(out, "%llu", myMinNode.data);
        else
            fprintf(out, "%llu,", myMinNode.data);

        if (fscanf(in[myMinNode.fileNumber], "%llu,", &tempData) != 1) {
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
