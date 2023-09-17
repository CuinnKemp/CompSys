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

@100
D=A

@R2
D = M-D

@SelectionSort
D;JLT



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


(SelectionSort)
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
@R5
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
@R5
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
@R5
D = M

@R1
D=D-1
A = M + D
D = M

@R0
D = M-D

@keepTemp
D;JLE

@R5
D=M

@R1
D=D-1
A = M + D
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
M = M-1
D = M

@Loop
D;JGT

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


@MainLoop
D;JNE


(SORTED)
@R0
M = -1

(END)
@END
A;JMP





