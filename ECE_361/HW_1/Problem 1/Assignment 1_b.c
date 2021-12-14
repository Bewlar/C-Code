b. [5] Indicate which of the following items SHOULD NOT be put into a C header (.h) file. Why not?
    a) Function prototypes
    Header files should have declarations(not definitions). These are the input definitions.
    It depends on whether the declaration is in the .c file. If part of it needs to be private then it can just be included in the .c file.

    b) Source code for functions
    Header files should contain the source code unless you don't want others to have access to it.
    Discussion with Rishitosh good coding practice is to place source code in the .c file and only prototypes into the .h file.

    c) Macro definitions
    One reference discussing .h files state header files contain C declarations and macro definitions.
    However, macro definitions shouldn't be put into .h files due to unexpected occurences due to potentially ending up in someone elses code where they reference the same definition.
    The term is called namespace pollution for the negative argument.
    They can be used if header guards are in place or used in private scope.


    d) Type definitions
    These should go in the source code so it will depend upon whether you will want others to have access or not. Typically can go in .c file.

    e) Variables
    These should go in the source code so it will depend upon whether you will want others to have access or not. Typically can go in .c file.
