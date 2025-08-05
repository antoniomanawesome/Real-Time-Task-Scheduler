# Real-Time-Task Scheduler
Welcome to a Real-Time-Task Scheduler simulation created by Antonio Marrero-Acosta and Matthew Martin! Here's a walkthrough of our workflow while designing this project.

**1. Visual Studio Code**
First, we took the Catch2 Framework from the previous class projects and modified our own CMakeLists file to create Catch2 tests to test our custom data structures before even touching the GUI aspect of the project.
This should follow the same workflow as the previous two projects. We had our source files in the src/ folder, our test files in the test/ folder, and configured some json files to be able to run our desired cpp files. Along with creating headers and cpp files for each of our separate data structures (created using classes), we also created some catch tests to test the functionality of our data structures.

**2. Visual Studio**
We then moved on to using Visual Studio because the addition of a GUI library was too cumbersome to integrate with visual studio code alone. We made a Visual Studio project inside of the Scheduler_GUI/ folder, which included the imgui framework (a robust c++ GUI library with extensive documentation and examples) and all of our source files that we created.
We modified our source files to fit the use case for the GUI, like taking some code out of our functions and wrapping it in our main file in the Visual Studio Project. If you want to see some examples of how imgui can be used, there is a demo window that displays all the possible features of the library. We took inspiration from the 8,000+ loc file to create our custom GUI. Most of our work was in the gui.cpp and gui.h files, as we created one function that merged all of the functionality of our source files to then integrate into this new main file. If you want to run the code, open the Scheduler_GUI/Scheduler_GUI.sln file in visual studio to create the project and run the files.

**3. Executable**
In order to run the application, we copied the executable file (.exe) and its corresponding configuration file (.ini) in one folder called Executable/. Running the Scheduler_GUI.exe in this folder will run our application with the configuration that we designed. There is a tutorial in the application that goes into detail on how to use it.
