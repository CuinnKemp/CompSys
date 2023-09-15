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


(ChangeOrder)
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

@R0
M = -1

(END)
@END
A;JMP





