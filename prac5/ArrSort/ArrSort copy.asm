//Check if array start far above R2
@R1
D=M
@R2
D=M+D
@16383
D=A-D
@Sorted
D;JLT

@R1
D=M
D=D-1
D=D-1

@Sorted
D;JLE

//Check that length of array is sufficient
@R2
D=M

@Sorted
D;JLE




(MainLoop)
@R1
D = M
@R3
M = D
(switchLoop)
@R3
A = M
D = M

@swAPOS
D;JGE

@swANEG
D;JMP

(swAPOS)
@R3
A = M + 1
D = M

@swChangeOrder
D;JLT

@swNNPP
D;JMP

(swANEG)
@R3
A = M + 1
D = M

@swNNPP
D;JLT

@swkeepOrder
D;JMP

(swNNPP)
@R3
A = M
D = M
A = A + 1
D = M - D

@swkeepOrder
D;JGE

(swChangeOrder)
@R3
A = M
D = M

@temp
M = D

@R3
A = M
A = A + 1
D = M
@temptwo
M = D

@R3
A = M
M = D

@temp
D = M

@R3
A = M
A = A + 1
M = D

(swkeepOrder)
@R3
M = M + 1

@R1
D = M

@R2
D = D - 1
D = D + M

@R3
D = D - M

@switchLoop
D;JNE

// CHECK IF SORTED
@R1
D = M

@R3
M = D
(scLoop)
@R3
A = M
D = M

@APOS
D;JGE

@ANEG
D;JMP

(APOS)
@R3
A = M + 1
D = M

@MainLoop
D;JLT

@NNPP
D;JMP

(ANEG)
@R3
A = M + 1
D = M

@NNPP
D;JLT

@Continue
D;JMP

(NNPP)
@R3
A = M
D = M
A = A + 1
D = M - D

@MainLoop
D;JLT

(Continue)
@R3
M = M + 1

@R1
D = M

@R2
D = D - 1
D = D + M

@R3
D = D - M

@scLoop
D;JNE

(Sorted)
@R0
M = -1

(END)
@END
A;JMP





