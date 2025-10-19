// Finds the smallest element in the array of length R2 whose first element is at RAM[R1] and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.
//Check if array start far above R2

@R1
D=M - 1

@SORTED
D;JLE

//Check that length of array is sufficient
@R2
D=M

@SORTED
D;JLE

(MainLoop)
@R2
D = M
@R5
M = D

//get current tempMin
@R1
A=M
D=M

@R0
M=D

@R4
M = 0

(Loop)
// get the loop counter - 1
@R5
D = M - 1

// get the value to compare
@R1
A = M + D
D = M

// store the comparison value at Ram[7]
@R7
M = D

//check whether B is positive
@BPOS
D;JGE

// if it isnt and a is positve switch em
@R0
D = M
@SwitchElements
D;JGE

// otherwise go to NNPP
@NNPP
A;JMP

(BPOS)
@R0
D = M
@keepTemp
D;JLE
//CONTINUE WITH both neg both positive program

// Negative and negative and positive positive
(NNPP)
// get the value being compared with
@R7
D = M

// check 0 < a-b (b < a)
@R0
D = M-D

// if this is true than dont switch
@keepTemp
D;JLE

// otherwise continue and swap min
(SwitchElements)
@R7
D = M

@R0
M=D

@R5
D = M

// hold minimum index
@R4 // Minimum Index
M = D-1

(keepTemp)
@R5
MD = M-1


@Loop
D-1;JGT

//after getting the minimum value


// get location of min
@R4
D = M

@R1
D = M + D

@R6
M = D

// get value at start
@R1
A = M
D = M

// place this value where the min used to be
@R6
A = M
M = D

// get the value of the min
@R0
D = M

//place it at the start of the array
@R1
A = M
M = D

@R1
M = M + 1

@R2
M = M - 1
D = M - 1

@MainLoop
D;JGT


(SORTED)
@R0
M = -1

(END)
@END
A;JMP