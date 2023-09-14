// Calculates R1 + R2 - R3 and stores the result in R0.
// (R0, R1, R2, R3 refer to RAM[0], RAM[1], RAM[2], and RAM[3], respectively.)

// Put your code here.

@R1
D=M
@R2
D=M+D
@R3
D=D-M
@R0
M=D

(Loop)
@Loop
A;JMP