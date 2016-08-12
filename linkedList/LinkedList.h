class LinkedList
{
public:
    // Create an empty linked list
    LinkedList();
    
    // Create a linked list that contains the data in the provided array
    LinkedList(int initialData[]);
    
    // Add a node to the start of the list
    void push(int newValue);
    
    // Add a node at the provided index (such that LinkedList.get(index) == newValue after this call completes)
    void insert(int newValue, int index);
    
    // Remove a node from the front of the list
    int pop();
    
    // Remove the node at the specified index
    int remove(int index);
    
    // Set the value of the node at the specified index
    void set(int newValue, int index);
    
    // Return the value held by the node at the specified index
    int get(int index);
};
