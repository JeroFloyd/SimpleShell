Assignment - 2 (Section-A)
SimpleShell - A Unix Shell in C from scratch
-----------------------------------------------------------------------------------------------
Jerovin Floyd, Aryan Verma - Group-109
-----------------------------------------------------------------------------------------------


So in this assignment we were asked to create a functioning shell type of program (SimpleShell) from scratch. Me, Jerovin and my teammate Aryan have worked pretty hard on this assignment. I'd say like usual we both had equal parts in doing this assignment. Everyday we met at the library and programmed it on my laptop. So we had 50-50 contribution in this assignment. This was a bigger and longer assignment compared to the last one and we had to put in a lot of effort.

So basically the SimpleShell works just like a normal shell. The user has to input certain Linux-based commands like "ls", "ls/home", "echo", and so on. We created multiple functions which serves separate functionalities in making the final code work. For each command we created a function and called it in the main function. Here are some of the purposes and functionalities of the functions:

. ls_func - This function is used to list all the files in the specified directory. It basically opens the directory and prints each file name.

. ls_home_func - This function does the same thing as the previous function but it opens and prints each files inside the home directory.

. ls_r_func - This function recursively lists files and directories within a specified path, printing the directory structure with indentation based on depth.

. echo_func - This prints the arguments passed using the echo command. So if the user enters "echo hello jero", the output will be "hello jero". It basically repeats it.

. wc_l_func - This function basically counts the number of lines in a specific file and prints it. In this case it's the fib.c file.

. wc_c_func - This is just like the previous function but it counts and prints the number of characters in a specific file.

. grep_func - This function searches for patterns in a file and prints those lines.

. sort_func - This function just reads lines from a file, sorts them and then prints those lines.

. uniq_func - This function reads the file and prints unique lines, omitting consecutive duplicate lines.

. fib_func - This fibonacci function calculates the fibonacci number for a given n using iteration.

. history_adder - This adds a command to the history. If the history has 100 commands, it removes the oldest command before adding the new one.

. dis_hist - This function is used to display the command history to the user.

. int main - The main function is used to call all the required functions including all the command functions and the history function and so on.



This is how the code works in short. Reading the code will help in a better understanding. We also did the bonus part of the assignment. We made our code support "&" for background processes in our SimpleShell.



Limitations of our SimpleShell:
We didn't use pipelining for our code because it was too complex already.



GitHub Repo Link: https://github.com/JeroFloyd/SimpleShell-Assignment-2.git

