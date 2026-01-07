#include <iostream>

using namespace std;

struct Node {
    int data; //Data field
    Node* next; //Pointer to the next node
};

// Define 'node' as a type alias for a pointer to a Node structure
typedef struct Node* node;

// Function to create a new node with a given value
// Time_complexity O(1) - Constant time as it performs a fixed number of operations
// Space_complexity O(1) - Allocates memory for exactly one node
node makeNode(int x){
    node tmp = new Node(); // Dynamically allocate memory for a new Node on the Heap
    tmp->data = x; // Assign the input value to the 'data' field of the node
    tmp->next = nullptr; // Initialize the 'next' pointer to nullptr to indicate it doesn't point to anything yet
    return tmp; // Return the memory address (pointer) of the newly created node
}

// Function to check if the Node is empty
// Time Complexity O(1) - Constant time. The operation only performs a single null-check comparison regardless of the list size
// Space Complexity O(1) - Constant space. No additional memory is allocated during execution
inline bool empty(node a){ // 'inline': Suggests the compiler to replace the function call with the actual code to reduce "function call overhead"
    return a == nullptr;
}

// Function to check the number of elements in linked list
// Time Complexity: O(n) - We must traverse the entire list
// space Complexity O(1) - Constant space. We only use a single integer counter and do not allocate additional memory regardless of list size
int Size(node a){
    int cnt = 0;
    while(a != nullptr){
        ++cnt;
        a= a->next; // Assign the next node's address to the current note's address
        // Moving the pointer to the next memory address
    }
    return cnt;
}

// Function to insert a new element at the beginning of the list
// Time Complexity O(1) - Constant time. Regardless of list size, we only perform a fixed number of pointer reassignments.
// Space Complexity O(1) - Constant space. We allocate memory for exactly one new node
void insertFirst(node &head, int x){
    node tmp = makeNode(x);
    tmp->next = head; // Point new node to the current head (works even if head is nullptr)
    head = tmp;       // Update head to the new node
}

// Function to insert a new element at the end of the list
// Time Complexity O(n) - Linear time. The function must traverse the entire list to find the last node (where next is nullptr)
// Space Complexity O(1) - Constant space. Only one new node is allocated
void insertLast(node &head, int x){
    node tmp = makeNode(x);
    if(head == nullptr){
        head = tmp;
    }
    else{
        node p = head;
        while(p->next != nullptr){
            p = p->next;
        }
        p->next = tmp;
    }
}

// Function to insert a new element at the middle of the list
// Time Complexity O(n) - due to list traversal (Size calculation and position search)
// Space Complexity O(1) - as memory allocation is fixed for one node
void insertMiddle(node &head, int x, int pos){
    // 1. Handle Case: Insert at the very beginning
    if (pos == 1) {
        insertFirst(head, x);
        return;
    }

    // 2. Traversal: Find the node at position (pos - 1)
    node p = head;
    // We walk until (pos - 1) OR until we hit the end of the list
    for (int i = 1; i < pos - 1 && p != nullptr; i++) {
        p = p->next;
    }

    // 3. Validation: If p is null, the position is out of bounds
    if (p == nullptr) {
        cout << "Invalid Insert Position!" << endl;
        return;
    }

    // 4. Execution: Create and link the new node
    node tmp = makeNode(x);
    tmp->next = p->next; // Link new node to the next part of the list
    p->next = tmp;       // Point the current node to the new node
}

// Function to delete an element at the beginning of the list
// Time Complexity O(1)
// Space Complexity O(1)
void deleteFirst(node &head){
    // 1. Safety Check: Handle empty list to prevent segmentation faults
    if (head == nullptr) {
        return; 
    }

    // 2. Capture: Use a temporary pointer to hold the current head's address
    node tmp = head;

    // 3. Reassign: Move the head pointer to the second node in the list
    head = head->next;

    // 4. Cleanup: Explicitly free the memory of the original first node
    delete tmp;
}

// Function to delete an element at the end of the list
// Time Complexity O(n) - Linear time. Requires a full traversal to find the tail's predecessor
// Space Complexity O(1) - Constant space. Only a few auxiliary pointers are used
void deleteLast(node &head){
    // Guard Clause: Handle the empty list scenario to prevent runtime errors.
    if (head == nullptr) {
        return;
    }

    // Edge Case: Handling a list with exactly one node.
    // If we don't handle this separately, p->next->next will cause a crash.
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
        return;
    }

    // Traversal: Use a pointer 'p' to locate the second-to-last node.
    node p = head;
    while (p->next->next != nullptr) {
        p = p->next;
    }

    // Memory Management:
    node tmp = p->next; // Temporarily hold the actual tail node's address.
    p->next = nullptr;  // Disconnect the tail from the list.
    delete tmp;         // Explicitly deallocate memory to prevent leaks.
}

// Function to delete an element at the middle of the list
// Time Complexity O(n) - Linear time (One-pass traversal)
// Space Complexity O(1) - Constant space
void deleteMiddle(node &head, int pos) {
    // 1. Guard Clause: Empty list
    if (head == nullptr || pos <= 0) return;

    // 2. Special Case: Delete the first node (pos == 1)
    if (pos == 1) {
        deleteFirst(head); // Reusing your existing logic is cleaner!
        return;
    }

    // 3. Traversal: Find the target node (nxt) and its predecessor (prev)
    node prev = nullptr;
    node nxt = head;
    for (int i = 1; i < pos && nxt != nullptr; i++) {
        prev = nxt;
        nxt = nxt->next;
    }

    // 4. Validation: If nxt is null, the position was out of bounds
    if (nxt == nullptr) {
        // Position exceeds list length
        return; 
    }

    // 5. The "Bypass" and "Scrub"
    prev->next = nxt->next; // Link previous node to the one AFTER the target
    delete nxt;             // Explicitly free memory
}

// Function to print all the node
// Time Complexity O(n) - Linear time. Every node is visited once
// Space Complexity O(1) - Constant space. No extra memory allocated
void print(node head){
    cout << "-----------------------------------------\n";
    // Iterate through the list until we reach the tail (nullptr)
    while(head != nullptr){
        cout << head->data << " ";
        // Advance to the next node
        head = head->next;
    }
    cout << endl << "-----------------------------------------\n";
}

int main(){
    node head = nullptr;
    while(true){
        cout << "\n--- Linked List Manager ---\n";
        cout << "1. Insert First\n2. Insert Last\n3. Insert Middle\n";
        cout << "4. Delete First\n5. Delete Last\n6. Delete Middle\n";
        cout << "7. Print Size\n8. Print List\n9. Exit\n";
        cout << "Enter choice: ";
        
        int choice; 
        if(!(cin >> choice)) break; // Safety check for non-numeric input

        if(choice == 1){
            cout << "Enter value: ";
            int x; cin >> x;
            insertFirst(head, x);
        }
        else if(choice == 2){
            cout << "Enter value: ";
            int x; cin >> x;
            insertLast(head, x);
        }
        else if(choice == 3){
            cout << "Enter value and position: ";
            int x, pos; cin >> x >> pos;
            insertMiddle(head, x, pos);
        }
        else if(choice == 4){
            deleteFirst(head);
            cout << "Deleted first node.\n";
        }
        else if(choice == 5){
            deleteLast(head);
            cout << "Deleted last node.\n";
        }
        else if(choice == 6){
            cout << "Enter position to delete: ";
            int pos; cin >> pos;
            deleteMiddle(head, pos);
        }
        else if(choice == 7){
            cout << "Current Size: " << Size(head) << endl;
        }
        else if(choice == 8){
            print(head);
        }
        else if(choice == 9){
            break;
        }
        else {
            cout << "Invalid choice! Please try again.\n";
        }
    }
    return 0;
}

