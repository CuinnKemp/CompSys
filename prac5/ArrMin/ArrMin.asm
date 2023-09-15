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

@R0
D = M-D

@keepTemp
D;JLT

@R1
D=D-1
A = M + D
D = M

@DMNEG
D;JLT

@DMPOS
D;JGE

(DMNEG)
@R0
D = M
@NotOverflow
D;JLT

@keepTemp
D;JMP

(DMPOS)
@R0
D = M

@NotOverflow
D;JGE

@keepTemp
D;JMP

(NotOverflow)
@R0
D = M
@R2
D=M

@R1
D=D-1
A = M + D
D = M

@keepTemp
D;

@R0
M=D

(keepTemp)
@R2
M = M-1
D = M

@Loop
D;JGT

(END)
@END
A;JMP