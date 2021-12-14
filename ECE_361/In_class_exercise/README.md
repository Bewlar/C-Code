# ECE 361 In-class Session 1
## Exercises and starter code for the in-class practice with git/GitHub, bash, and gcc

## After this work session students should know how to:
- Accept an assignment from GitHub Classroom and clone the starter repository
- Put your pre-work on git/GitHub into practice
- Edit a file using one of the "bash-friendly" text editors
- Compile, link, and execute a multi-file program with gcc

## Introduction:
This work is intended to be completed during an in-class work session.  The lesson builds on what you have learned from the YouTube videos on bash and gcc and with the git/GitHub pre-work you completed. Our belief is that it is worthwhile to complete this lesson even if there is not enough time during the in-class session.  There is no grade for this assignment, though, so the choice is yours.

After you have accepted this assignment in GitHub classroom you will  use a bash-friendly text editor to create a file containing <b>main()</b> called <i>justify.c<i/> that contains the main loop for the program.  The other files needed to create this application are contained in the /src directory of the repository.  Once all of the source code files are available you will compile and execute the program, saving the results.  I have provided test input for your program in the file [quote.txt](./quote.txt).

## Assignment

1. Accept this assignment in GitHub Classroom
[https://classroom.github.com/a/TOvQGL21]
2. Review the slides in [justify_application_explanation.pdf](./justify_application_explanation.pdf)
3. Open a bash terminal session using MobaXterm or your chosen environment
4. Clone your private repository for the assignment to your local PC using git
5. Enter/edit/save the code for <i>justify.c<i/> using your favorite bash-friendly text editor
The source code can be found on pages 15 - 16 of the slides
6. Commit <i>justify.c<i/> to your local repository
7. Compile and link the entire program.  Name the executable <i>justify.exe</i>
8. Execute the program at the bash command line, redirecting <b>stdin</b> to <i>quote.txt<i/> and redirectin <b>stdout</b> to <i>newquote.txt<i/>
9. Once the program executes correctly commit <i>newquote.txt<i/> to your local repository
10. Do a final push of your local repository to your private repository for the assignment.
