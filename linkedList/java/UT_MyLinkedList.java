import org.junit.Test;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.core.Is.is;

// This class contains unit tests for MyLinkedList that verify that each method works as expected. If your implementation
// is correct, all of the tests here should pass when you run them. (In IntelliJ, you can click the green arrows next to
// each test to run them individually, or the one next to the class name to run them all.) You shouldn't need to modify
// the tests that are here, but feel free to add more.
public class UT_MyLinkedList
{
    private MyLinkedList linkedList;
    
    @Test
    public void getReturnsCorrectValues()
    {
        System.out.println("Creating new MyLinkedList with elements {1,2,3}");
        int[] arr = {1, 2, 3};
        linkedList = new MyLinkedList(arr);
        
        System.out.println("Verifying that get() returns the correct value for each index of the list");
        assertThat(linkedList.get(0), is(1));
        assertThat(linkedList.get(1), is(2));
        assertThat(linkedList.get(2), is(3));
    }
    
    @Test
    public void pushAddsToFront()
    {
        System.out.println("Creating new empty MyLinkedList");
        linkedList = new MyLinkedList();
        System.out.println("Pushing 1 onto the front of the list");
        linkedList.push(1);
        
        System.out.println("Verifying that the first element of the list is 1");
        assertThat(linkedList.get(0), is(1));
        
        System.out.println("Pushing 2 onto the front of the list");
        linkedList.push(2);
        
        System.out.println("Verifying that the first element of the list is 2 and the second element is 1");
        assertThat(linkedList.get(0), is(2));
        assertThat(linkedList.get(1), is(1));
    }
    
    @Test
    public void insertAddsAtSpecifiedIndex()
    {
        System.out.println("Creating new MyLinkedList with elements {1,2,3}");
        int[] arr = {1, 2, 3};
        linkedList = new MyLinkedList(arr);
        System.out.println("Inserting 4 at index 1");
        linkedList.insert(4, 1);
        
        System.out.println("Verifying that the list's contents are correct");
        assertThat(linkedList.get(0), is(1));
        assertThat(linkedList.get(1), is(4));
        assertThat(linkedList.get(2), is(2));
        assertThat(linkedList.get(3), is(3));
    }
    
    @Test
    public void popRemovesFromFront()
    {
        System.out.println("Creating new MyLinkedList with elements {1,2,3}");
        int[] arr = {1, 2, 3};
        linkedList = new MyLinkedList(arr);
        System.out.println("Popping the first element from the list");
        int poppedValue = linkedList.pop();
        
        System.out.println("Verifying that the correct element was popped and the list's contents are correct");
        assertThat(poppedValue, is(1));
        assertThat(linkedList.get(0), is(2));
        assertThat(linkedList.get(1), is(3));
    }
    
    @Test
    public void removeDeletesSpecifiedIndex()
    {
        System.out.println("Creating new MyLinkedList with elements {1,2,3}");
        int[] arr = {1, 2, 3};
        linkedList = new MyLinkedList(arr);
        System.out.println("Removing the element at index 1");
        int removedValue = linkedList.remove(1);
        
        System.out.println("Verifying that the correct element was removed and the list's contents are correct");
        assertThat(removedValue, is(2));
        assertThat(linkedList.get(0), is(1));
        assertThat(linkedList.get(1), is(3));
    }
    
    @Test
    public void setChangesValueAtSpecifiedIndex()
    {
        System.out.println("Creating new MyLinkedList with elements {1,2,3}");
        int[] arr = {1, 2, 3};
        linkedList = new MyLinkedList(arr);
        System.out.println("Setting the value of the element at index 1 to 4");
        linkedList.set(4, 1);
        
        System.out.println("Verifying that the list's contents are correct");
        assertThat(linkedList.get(0), is(1));
        assertThat(linkedList.get(1), is(4));
        assertThat(linkedList.get(2), is(3));
    }
}
