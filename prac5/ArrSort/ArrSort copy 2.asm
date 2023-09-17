// Check if array start far above R2
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

// Check that the length of the array is sufficient
@R2
D=M
@Sorted
D;JLE

// Main Loop
(MainLoop)
@R1
D=M
@R3
M=D

// Switch Loop
(switchLoop)
@R3
A=M
D=M
@swAPOS
D;JLE

@swANEG
D;JMP

// Handle swAPOS case
(swAPOS)
@R3
A=M+1
D=M
@swChangeOrder
D;JGT

@swNNPP
D;JMP

// Handle swANEG case
(swANEG)
@R3
A=M+1
D=M
@swNNPP
D;JGT

@swkeepOrder
D;JMP

// Handle swNNPP case
(swNNPP)
@R3
A=M
D=M
A=A+1
D=M-D
@swkeepOrder
D;JGE

// Handle swChangeOrder case
(swChangeOrder)
@R3
A=M
D=M
@temp
M=D

@R3
A=M
A=A+1
D=M
@temptwo
M=D

@R3
A=M
M=D

@temp
D=M

@R3
A=M
A=A+1
M=D

(swkeepOrder)
@R3
M=M+1

@R1
D=M
@R2
D=D-1
D=D+M

@R3
D=D-M

@switchLoop
D;JNE

// CHECK IF SORTED
@R1
D=M

@R3
M=D

(scLoop)
@R3
A=M
D=M

// Handle APOS case
@APOS
D;JLE

@ANEG
D;JMP

// Handle APOS case
(APOS)
@R3
A=M+1
D=M
@MainLoop
D;JLT

@NNPP
D;JMP

// Handle ANEG case
(ANEG)
@R3
A=M+1
D=M
@NNPP
D;JLT

@Continue
D;JMP

// Handle NNPP case
(NNPP)
@R3
A=M
D=M
A=A+1
D=M-D

@MainLoop
D;JLT

(Continue)
@R3
M=M+1

@R1
D=M
@R2
D=D-1
D=D+M

@R3
D=D-M

@scLoop
D;JNE

(Sorted)
@R0
M=-1

(END)
@END
0;JMP
