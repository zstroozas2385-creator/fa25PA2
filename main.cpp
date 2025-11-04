// Author: Zach Stroozas

#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) {
    // TODO:
    MinHeap h;
    if (nextFree == 0) {
        cerr << "There are no encodable characters were found in input.\n";
        exit(1);
    }
    for (int i = 0; i < nextFree; ++i) {
        h.push(i, weightArr);
    }
    int curr = nextFree;
    while (h.size > 1) {
        int a = h.pop(weightArr);
        int b = h.pop(weightArr);

        if (curr >= MAX_NODES) {
            cerr << "Node capacity exceeded while building tree.\n";
            exit(1);
        }
        leftArr[curr]   = a;
        rightArr[curr]  = b;
        weightArr[curr] = weightArr[a] + weightArr[b];
        charArr[curr]   = '\0';

        h.push(curr, weightArr);
        curr++;
    }
    int root = h.pop(weightArr);
    return root;
}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {
    // TODO:
    if (root < 0) return;

    struct Frame { int node; string path; };
    stack<Frame> st;
    st.push({root, ""});

    while (!st.empty()) {
        Frame f = st.top(); st.pop();
        int u = f.node;

        bool isLeaf = (leftArr[u] == -1 && rightArr[u] == -1);

        if (isLeaf) {
            char c = charArr[u];
            if (c >= 'a' && c <= 'z') {
                codes[c - 'a'] = (f.path.empty() ? "0" : f.path);
            }
        } else {
            if (rightArr[u] != -1) st.push({ rightArr[u], f.path + "1" });
            if (leftArr[u]  != -1) st.push({ leftArr[u],  f.path + "0" });
        }
    }
}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}