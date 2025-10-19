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
@R2
D = M

@R1
D=D-1
A = M + D
D = M

@BPOS
D;JGE

@R0
D = M
@BNEGAPOS
D;JGE

@NNPP
A;JMP

(BPOS)
@R0
D = M
@keepTemp
D;JLE
//CONTINUE WITH both neg both positive program
@NNPP
A;JMP


(BNEGAPOS)
@R2
D = M

@R1
D=D-1
A = M + D
D = M

@R0
M=D
@keepTemp
A;JMP

(NNPP)
@R2
D = M

@R1
D=D-1
A = M + D
D = M

@R0
D = M-D

@keepTemp
D;JLE

@R2
D=M

@R1
D=D-1
A = M + D
D = M

@R0
M=D

@R4
M = D

(keepTemp)
@R2
M = M-1
D = M

@Loop
D;JGT

(END)
@END
A;JMP