  
 ## RSHELL
	Description: Developed an Rshell in C++ that takes in various bash commands and executes them based on priority. 

	We utilized a composite design pattern to build a command shell called rshell.
  We are able to print a command prompt, read in a line of command(s) (and connector(s))
  from standard input, and execute the appropriate commands using fork, execvp, and wait.
  Our solution involves using an abstract base class that represents the entire command
  line interface. As well as a composite class called CommandLine. CommandLine represents
  the user input string which may be an aggregation of smaller commands. The leaf’s of our
  composite design pattern are two types of concrete classes, Command and Exit. They
  represent the two types of commands that may be found within a CommandLine object.   

## Getting Started

  Clone our repository and compile then run our rshell.cpp file.

### Prerequisites

  Make sure to understand how to use a built in terminal.

## Running the tests

In our test.cpp file you's find a series of tests utlizing the Google Unit Test Framework, that demonstrate the functionality of every necessary class function used within the command shell.

## Deployment

Add additional notes about how to deploy this on a live system

## Built With

* Google Unit Test Framework
* Hammer Server
* Cloud 9

## Bugs
* Some commands continue to give us errors, for example; cd. This may be due to it not being an executable located in a PATH directory.

## Authors

* **Rahul Nair**
* **Spyridon Catechis**
