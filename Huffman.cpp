#include <bits/stdc++.h>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node *left, *right;
    Node(char c, int f) {
        ch = c; freq = f;
        left = right = nullptr;
    }
};
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};
void generateCodes(Node* root, string code, unordered_map<char, string>& huffmanCode) {
    if (!root) return;
    // Leaf node
    if (!root->left && !root->right) {
        huffmanCode[root->ch] = code; return;
    }
    generateCodes(root->left, code + "0", huffmanCode);
    generateCodes(root->right, code + "1", huffmanCode);
}
int main() {
    string s; cin >> s;

    unordered_map<char, int> freq;
    for (char c : s) freq[c]++;

    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (auto [ch, f] : freq) pq.push(new Node(ch, f));

    while (pq.size() > 1) {

        Node* left = pq.top();
        pq.pop();

        Node* right = pq.top();
        pq.pop();

        Node* parent = new Node('\0',
                                left->freq + right->freq);

        parent->left = left;
        parent->right = right;

        pq.push(parent);
    }

    Node* root = pq.top();
    unordered_map<char, string> huffmanCode;

    generateCodes(root, "", huffmanCode);
    cout << "Huffman Codes:\n";

    for (auto [ch, code] : huffmanCode) cout << ch << " : " << code << '\n';

    string encoded = "";

    for (char c : s)
        encoded += huffmanCode[c];

    cout << "\nEncoded string:\n";
    cout << encoded << '\n';
}
