# Skunkworks-code-exercises
This repo contains exercises for the programming subteam of FRC team 1983 (Skunk Works Robotics). These exercises can use either C++ or Java. The code here may contain "the answers", so if you're a student on the team, please don't go rooting around in here without permission. Maybe I'll shell out the $7 a month to make this private at some point, but for now, do yourself a favor and don't ruin your opportunity to learn. The following exercises exist here:

# PIDDebug
Debugging practice using simulated PID controllers, encoders, and motors. Students will solve a variety of common compile errors, runtime crashes and logic mistakes while fixing the supplied broken program. Students will be taught about basic debugger features to help with this project. The fully-working program is a useful tool for learning about and examining the functionality of PID controllers.

# robotInventory
Coding practice with arrays, loops, conditionals, and strings. Students will work on the basics of C++ or Java while making a program to track what parts are present on a robot.

# linkedList
Coding and design practice with classes and pointers. Students will learn about dealing with references and designing object-oriented code as they solve a canonical programming problem. This exercise also serves as an introduction to dynamic data structures.

# ghost
A competitive introduction to AI. Students will learn about file I/O and designing data structures for performance while creating bots to play a word game.

----

For Java with IntelliJ, setup for all of the contained exercises is simple and uniform:
1. Import the repo as a project in IntelliJ (File > New > Project from Version Control > GitHub, then select this repo from the dropdown). When IntelliJ asks if you want to create a new project from the repo, choose "Yes".
2. Use the default options in the prompts that appear. Each exercise should appear as a separate module in your new project. Starter code for each exercise (where applicable) can be found in the "java" directory of each module.
3. Make sure that the project's compiler output location is set (File > Project Structure > Project compiler output, then choose a location for compiled .class and .jar files to be saved).
4. Add JUnit as a library to the project. Go to File > Project Structure > Libraries, click the "Add" button, select "From Maven", and enter "junit:junit:4.12" in the search box. After it finds the library, click "OK" and select all of the modules in the next window. After you do this, you should be able to run unit tests for any of the exercises.

For C++, Windows with MinGW is supported. (TODO: write instructions for C++ IDE setup)
