# Robot Inventory
Your task is to create a program that functions as an inventory for parts of a robot. The program would have a list of parts for a robot, and users would be able to ask the program whether or not a certain part is in the list. For example, if the robot had a RoboRIO, a Talon, a CIM, and a wheel, a run of the program might look like this (user input has a '$' in front of it):

    Name a part:
    $CIM
    The robot has one.
    Name a part:
    $Talon
    The robot has one.
    Name a part:
    $heart
    The robot does not have one.
    Name a part:
    $:(

... and so on. 

# Background
To do this, you'll need to know or learn about:

 * cin/cout
 * variables
 * std::string
 * arrays
 * for/while loops
 * if statements. 

If you need help, ask a mentor or the internet. For reading on the above topics, try [cplusplus.com](http://www.cplusplus.com).

# Tips
The structure of the program should roughly be as follows:

1. Create your list of parts. You can use an array of strings for this.
2. Start a loop that will run forever. The rest of the steps happen inside this loop.
3. Ask the user what part they want to know about and store their answer.
4. Go through the list of parts you made in step 1 and see if the one they want is in there.
5. Tell the user what you decided on in step 4.

# Extensions
Once you're finished, add these features:

1. Use your LinkedList class from the Linked List project to make the list of parts dynamically sized. Allow users to add or remove parts from the list.
2. A robot can have more than one of each kind of part. Make your inventory capable of tracking how many of each part the robot has. You should use a map or dictionary data structure for this.