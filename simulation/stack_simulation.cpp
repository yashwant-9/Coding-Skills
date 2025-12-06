// Stack Concept Simulation - Interactive Learning Tool
#include <bits/stdc++.h>
using namespace std;

const int MAX_SIZE = 100;

class StackSimulation {
private:
    int stack[MAX_SIZE];
    int top;
    
    // Display current stack state
    void displayStack() {
        cout << "\n===== Current Stack =====" << endl;
        
        if (top == -1) {
            cout << "Stack is EMPTY!" << endl;
            cout << "Top pointer: -1" << endl;
            return;
        }
        
        cout << "Elements (Top to Bottom):" << endl;
        cout << "Position\tValue" << endl;
        cout << "--------\t-----" << endl;
        
        for (int i = top; i >= 0; i--) {
            if (i == top) {
                cout << "[" << i << "] <-- TOP\t" << stack[i] << endl;
            } else {
                cout << "[" << i << "]\t\t" << stack[i] << endl;
            }
        }
        
        cout << "Top pointer: " << top << endl;
        cout << "Size: " << (top + 1) << " / " << MAX_SIZE << endl;
        cout << "========================" << endl;
    }
    
    // Check if stack is full
    bool isFull() {
        return top == (MAX_SIZE - 1);
    }
    
    // Check if stack is empty
    bool isEmpty() {
        return top == -1;
    }

public:
    StackSimulation() : top(-1) {}
    
    // Push element onto stack
    void push() {
        if (isFull()) {
            cout << "Error: Stack is FULL! Cannot push." << endl;
            return;
        }
        
        int value;
        cout << "Enter value to push: ";
        
        if (!(cin >> value)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Error: Invalid input!" << endl;
            return;
        }
        
        top++;
        stack[top] = value;
        cout << "Value " << value << " pushed at position " << top << endl;
        displayStack();
    }
    
    // Pop element from stack
    void pop() {
        if (isEmpty()) {
            cout << "Error: Stack is EMPTY! Cannot pop." << endl;
            return;
        }
        
        int value = stack[top];
        cout << "Popped value: " << value << " from position " << top << endl;
        top--;
        
        displayStack();
    }
    
    // Peek at top element
    void peek() {
        if (isEmpty()) {
            cout << "Error: Stack is EMPTY! Nothing to peek." << endl;
            return;
        }
        
        cout << "\nTop element: " << stack[top] << " (at position " << top << ")" << endl;
    }
    
    // Display all stack elements
    void displayAll() {
        displayStack();
    }
    
    // Check stack status
    void checkStatus() {
        cout << "\n===== Stack Status =====" << endl;
        cout << "Top Position: " << top << endl;
        cout << "Current Size: " << (top + 1) << endl;
        cout << "Max Size: " << MAX_SIZE << endl;
        
        if (isEmpty()) {
            cout << "Status: EMPTY" << endl;
        } else if (isFull()) {
            cout << "Status: FULL" << endl;
        } else {
            int utilization = ((top + 1) * 100) / MAX_SIZE;
            cout << "Status: " << utilization << "% FULL" << endl;
        }
        cout << "=======================" << endl;
    }
    
    // Clear stack
    void clearStack() {
        if (isEmpty()) {
            cout << "Stack is already empty!" << endl;
            return;
        }
        
        top = -1;
        cout << "Stack cleared successfully!" << endl;
        displayStack();
    }
    
    // Reverse stack display
    void reverseDisplay() {
        if (isEmpty()) {
            cout << "Error: Stack is EMPTY!" << endl;
            return;
        }
        
        cout << "\n===== Stack (Reversed) =====" << endl;
        cout << "Position\tValue" << endl;
        cout << "--------\t-----" << endl;
        
        for (int i = 0; i <= top; i++) {
            cout << "[" << i << "]\t\t" << stack[i] << endl;
        }
        cout << "============================" << endl;
    }
    
    // Get stack size
    void getSize() {
        cout << "Current stack size: " << (top + 1) << " elements" << endl;
    }
    
    // Check if specific value exists
    void searchValue() {
        if (isEmpty()) {
            cout << "Error: Stack is EMPTY!" << endl;
            return;
        }
        
        int value;
        cout << "Enter value to search: ";
        
        if (!(cin >> value)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Error: Invalid input!" << endl;
            return;
        }
        
        cout << "Search results:" << endl;
        bool found = false;
        
        for (int i = top; i >= 0; i--) {
            if (stack[i] == value) {
                cout << "  Found at position " << i << endl;
                found = true;
            }
        }
        
        if (!found) {
            cout << "  Value not found in stack!" << endl;
        }
    }
    
    // Demonstrate LIFO (Last In First Out)
    void demonstrateLIFO() {
        cout << "\n===== LIFO Demonstration =====" << endl;
        cout << "LIFO = Last In First Out" << endl;
        cout << "The last element pushed will be first to be popped." << endl;
        
        if (isEmpty()) {
            cout << "Stack is empty. Cannot demonstrate." << endl;
            return;
        }
        
        cout << "\nCurrent stack:" << endl;
        for (int i = top; i >= 0; i--) {
            cout << "Position " << i << ": " << stack[i];
            if (i == top) cout << " <-- Will be popped first";
            cout << endl;
        }
        cout << "=============================" << endl;
    }
    
    // Bulk push operations
    void bulkPush() {
        int count;
        cout << "How many elements to push? ";
        
        if (!(cin >> count) || count < 0 || count > (MAX_SIZE - top - 1)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Error: Invalid count!" << endl;
            return;
        }
        
        for (int i = 0; i < count; i++) {
            int value;
            cout << "Enter value " << (i + 1) << ": ";
            
            if (!(cin >> value)) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input, skipping..." << endl;
                i--;
                continue;
            }
            
            top++;
            stack[top] = value;
        }
        
        cout << count << " elements pushed successfully!" << endl;
        displayStack();
    }
    
    // Main menu
    void runSimulation() {
        int choice;
        
        while (true) {
            cout << "\n========== STACK SIMULATION ==========" << endl;
            cout << "1. Push (Add element)" << endl;
            cout << "2. Pop (Remove element)" << endl;
            cout << "3. Peek (View top element)" << endl;
            cout << "4. Display Stack" << endl;
            cout << "5. Check Status" << endl;
            cout << "6. Get Size" << endl;
            cout << "7. Search Value" << endl;
            cout << "8. Demonstrate LIFO" << endl;
            cout << "9. Reverse Display" << endl;
            cout << "10. Bulk Push" << endl;
            cout << "11. Clear Stack" << endl;
            cout << "12. Exit" << endl;
            cout << "======================================" << endl;
            cout << "Enter your choice: ";
            
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Error: Invalid choice! Please try again." << endl;
                continue;
            }
            
            switch(choice) {
                case 1:
                    push();
                    break;
                case 2:
                    pop();
                    break;
                case 3:
                    peek();
                    break;
                case 4:
                    displayAll();
                    break;
                case 5:
                    checkStatus();
                    break;
                case 6:
                    getSize();
                    break;
                case 7:
                    searchValue();
                    break;
                case 8:
                    demonstrateLIFO();
                    break;
                case 9:
                    reverseDisplay();
                    break;
                case 10:
                    bulkPush();
                    break;
                case 11:
                    clearStack();
                    break;
                case 12:
                    cout << "Thank you for using Stack Simulation! Goodbye!" << endl;
                    return;
                default:
                    cout << "Error: Invalid choice! Please try again." << endl;
            }
        }
    }
};

int main() {
    cout << "\n" << endl;
    cout << "     STACK CONCEPT SIMULATION TOOL      " << endl;
    cout << "  Learn Stack Operations & LIFO Concept " << endl;
    cout << "\n" << endl;
    
    StackSimulation sim;
    sim.runSimulation();
    
    return 0;
}
