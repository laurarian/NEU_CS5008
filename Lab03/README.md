# Lab 3 -- Counting Assembly

This is the starting readme for this assignment.  Please edit the following 
information by removing the "*edit me*" and replace it with appropriate 
information your assignment. If it is asking you a question, please provide 
a response.

- Name: Rong Huang

- Title: Lab 3: Estimating Execution

- How many hours did it take you to complete this assignment? 3 hours 

- Did you collaborate with any other students/TAs/Professors? If so, tell 
  us who and in what capacity.
  - Prof Scoot
  - Hang Zhao
  
- Did you use any external resources? (Cite them below)
  - Module 3 videos and slides
  - C strcat() function:https://www.fresh2refresh.com/c-programming/c-strings/c-strcat-function/
  - C Programming Strings:https://www.programiz.com/c-programming/c-strings
  
- Use your tool to measure the  number of instructions that are require to 
  execute your implementation of the guessing game program that you 
  implemented in Homework 1 using two different levels of optimization:

  - When your program is compiled using the -O0 flag:

    ```
    ADD: 7
    SUB: 6
    MUL: 2
    DIV: 1
    MOV: 70
    LEA: 4
    PUSH: 6
    POP: 6
    RET: 1

    Total Instructions: 103
    Total Cycles: 138
    ```

  - When your program is compiled using the -O3 flag:

    ```
    ADD: 6
    SUB: 3
    MUL: 1
    DIV: 0
    MOV: 25
    LEA: 4
    PUSH: 4
    POP: 4
    RET: 1

    Total Instructions: 48
    Total Cycles: 58
    ```

- (Optional) What was your favorite part of the assignment? 
  - *edit me*
  
- (Optional) How would you improve the assignment? 
  - *edit me*

## Logistics

For this assignment (and every assignment/lab), you must login into the 
servers through `your_khoury_name@login.khoury.northeastern.edu` to complete 
and test your work. The reason is the examples I will provide below are 
compiled strictly for our machine's architecture, and this is a consistent 
architecture where your submission will be graded.

### Important notes

* Your code **must compile and run** on the Khoury machines to earn credit. 
  Make sure you test your programs on these machines, as this is where we 
  grade your assignments.
* You must commit any additional files (if any) into your repository so we 
  can test your code.
  * Points will be lost if you forget!
* Do not forget to push your changes in your private repo for grading before 
  the assignment deadline!**
