# my-gcc

This is just a toy project

Installation: 
    
    Dependencies:
        nasm: 
            In ubuntu: sudo apt install nasm

    Building:
        ./build.sh

    Running:
        ./my-gcc [filename]

        Required output code will be a.out.
        Assembly code will be in asm.asm.

Please be careful while using it. Do not use invalid C code.
Might go into infinite-loop. Idk

There is a test code in example.cpp

Features supported:
    
    Comments not supported
    #include not supported

    "int"'s are supported. But only one at a time.
        int a;      //right
        int b;

        int a,b;    //wrong

    Operator supported:
        +,-,==,!=

        Only two operand at a time.
            a = 1 + 2;       //right
            a = a - 1;      

            a = 1 + 2 + 3;   //wrong

    if supported: 
        Again operators support must be considered. i.e
        
        if(a != b)
        if(a == b)  //supported provided a and b are supported datatypes

        else not supported.

    while supprted:
        Same as "if"
    
    printf and scanf supported:
        printf: upto 6 parameters
        scanf: upto 4 parameters