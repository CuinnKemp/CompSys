// Finds the smallest element in the array of length R2 whose first element is at RAM[R1] and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.
//Check if array start far above R2
@R1
D=M
@R2
D=M+D
@16383
D=A-D
@END
D;JLT


@R1
D=M

@END
D=D-1
D=D-1
D;JLE

//get current tempMin
@R1
A=M
D=M

@R0
M=D

//Check that length of array is sufficient
@R2
D=M

@END
D;JLE



(Loop)
// get the loop counter - 1
@R2
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

@R2
D = M

(keepTemp)
@R2
M = M-1
D = M-1

@Loop
D;JGT

(END)
@END
A;JMP