(MainLoop)
@R1
D = M
@R3
M = D
(switchLoop)
@R3
A = M
D = M
A = A + 1
D = M - D

@keepOrder
D;JGE

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

(keepOrder)
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

@R1
D = M

@R3
M = D
(scLoop)
@R3
A = M
D = M
A = A + 1
D = M - D

@MainLoop
D;JLT

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

@R0
M = -1

(END)
@END
A;JMP





