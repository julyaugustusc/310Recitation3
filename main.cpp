//
//  main.cpp
//  Recitiation3
//
//  Created by Augustus Crosby on 6/9/19.
//  Copyright © 2019 Augustus Crosby. All rights reserved.
//


//I'm assuming time isn't actually moving in regards to how long they can land, I have no idea how to actually implement that.

#include <iostream>
#include <cstdlib>
#include <queue>

using namespace std;

/*class BinaryTree{
    private:
    
    class node{
        public:
        node* left;
        node* right;
        int key;
        string data;
    };
    
    public:
    node* root;
    
    BinaryTree(){
        root = NULL;
    }
    
    bool isEmpty() const { return root == NULL; }
    void INORDER_TREE_WALK(node*);
    void TREE_INSERT(int, node*);
};

void BinaryTree::TREE_INSERT(int d, node * r){
    // if the root is null, insert the node to the root
    if (r == NULL){
        node* z = new node();
        z->key = d;
        z->left = NULL;
        z->right = NULL;
        root = z;}
    else {
        // if root is not null, Do level order traversal until we find an empty place using queue
        queue<struct node*> q;
        q.push(r);
        while (!q.empty()) {
            struct node* temp = q.front();
            q.pop();
            if (!temp->left) {
                node* z = new node();
                z->key = d;
                z->left = NULL;
                z->right = NULL;
                temp->left = z;
                break;
            } else {
                q.push(temp->left);
            }
            if (!temp->right) {
                node* z = new node();
                z->key = d;
                z->left = NULL;
                z->right = NULL;
                temp->right = z;
                break;}
            else
                q.push(temp->right);
            
        } //end of while loop
        
        
    } //end of else
    
}

void BinaryTree::INORDER_TREE_WALK(node* x){
    if (x != NULL){
        if (x->left)
            INORDER_TREE_WALK(x->left);
        cout << " " << x->key << " ";
        if (x->right)
            INORDER_TREE_WALK(x->right);
        
    }
    
}*/
//Honestly this code didn't make much sense to me, so I went with this:

class minHeap{
    int *planeArray;
    int sizeOfPlaneArray;
    int heap_size;
public:
    //constructor
    minHeap();
    
    int parent(int i) {
        return (i-1)/2;
    }
    int left(int i){
        return 2*i + 1;
    }
    int right(int i){
        return 2*i + 2;
    }
    int getMin(){
        return planeArray[0];
    }
    
    void insertKey(int key);
    void decreaseKey(int i, int input);
    int extractMin();
    void deleteKey(int i);
    void minHeapify(int i);
    
    void display();
    
};

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

minHeap::minHeap(){
    heap_size = 0;
    sizeOfPlaneArray = 100; // empty at first but has potential to hold up to 100 planes
    planeArray = new int[sizeOfPlaneArray];
    
}

void minHeap::insertKey(int key){
    if (heap_size == 100){
        cout << "There are too many planes in the queue already. 100 is way too many anyway. Your passengers are going to be very angry with that wait time." << endl;
        return;
    }
    //insert at end
    heap_size++;
    int i = heap_size - 1;
    planeArray[i] = key;
    cout << planeArray[i] << endl;
    
    //heapify
    while(i != 0 && planeArray[parent(i)] > planeArray[i]){
        swap(&planeArray[parent(i)], &planeArray[i]);
        i = parent(i);

    }
    cout << planeArray[i] << endl;
    cout << heap_size << endl;
    
}

void minHeap::decreaseKey(int i, int key){
    planeArray[i] = key;
    
    //heapify
    while(i != 0 && planeArray[parent(i)] > planeArray[i]){
        swap(&planeArray[parent(i)], &planeArray[i]);
        i = parent(i);
        
    }
    
}

int minHeap::extractMin(){
    int min;
    
    if (heap_size <= 0){
        cout << "There is no data in the heap." << endl;
        return -1;
    } else if (heap_size == 1){
        heap_size--;
        min = planeArray[0];
        return min;
    } else {
        min = planeArray[0];
        planeArray[0] = planeArray[heap_size - 1];
        heap_size--;
        minHeapify(0);
        return min;
        
    }
}

void minHeap::deleteKey(int i){
    decreaseKey(i, -1); // shouldn't have negative wait times, -1 is appropriate
    extractMin();
    
}

void minHeap::minHeapify(int i){
    int l = left(i);
    int r = right(i);
    int min = i;
    
    if (l < heap_size && planeArray[l] < planeArray[i])
        min = l;
    if (r < heap_size && planeArray[r] < planeArray[min])
        min = r;
    if (min != i)
    {
        swap(&planeArray[i], &planeArray[min]);
        minHeapify(min);
    }
    
}

void minHeap::display(){
    for(int i = 0; i < heap_size; i++){
        cout << " " << planeArray[i] << "\n";
    }
    cout << endl;
}

int main() {
    minHeap * planeHeap = new minHeap();
    
    char input = 'i';                // initialized to a dummy value
    int key = -1;
    
    do {
        cout << "\t\tWelcome to the Plane Landing System:\n\n";
        cout << "a: Make a landing request\n";
        cout << "b: Land a Plane\n";
        cout << "c: List all landing requests\n";
        cout << "q: Exit\n";
        cin >> input;
        cin.ignore();
        
        switch (input) {
            case 'a':    // Make landing request
                // input details from user
                while (key < 0){
                    cout << "Input how long the plane can wait before landing:\n";
                    cin >> key;
                    cin.ignore();
                    if (key < 0){
                        cout << "Cannot have negative wait times!\n" << endl;
                    }
                }
                planeHeap->insertKey(key);
                
                key = -1;
                break;
                
            case 'b':        // Land a plane
                planeHeap->extractMin();
                break;
                
            case 'c':        // display all requests
                planeHeap->display();
                break;
                
            case 'q':        // quit
                delete(planeHeap);
                break;
                
            default:
                cout << "Invalid choice\n";
        }
    } while (input != 'q');
}
