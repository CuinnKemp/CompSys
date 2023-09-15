// Finds the smallest element in the array of length R2 whose first element is at RAM[R1] and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.
//initialise variables

@R1
D=M

@ArrOne
M=D

@R2
D=M

@ArrLen
M=D

@ArrPoint
A=M
D=M

@tempMin
M=D

@LoopCounter
M = 1

(Loop)
@LoopCounter
D = M

@ArrPoint
A = M + D
D = M

@tempMin
D = D-M

@keepTemp
D;JLT

@ArrPoint
A = M + D
D = M

@tempMin
M=D

(keepTemp)
@LoopCounter
M = M + 1
D = M

@ArrLen
D = D+1
D = M-D

@Loop
D;JLT

@tempMin
D=M

@R0
M=D

(END)
@END
A;JMP