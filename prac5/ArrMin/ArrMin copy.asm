// Finds the smallest element in the array of length R2 whose first element is at RAM[R1] and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.



//take in 
@R1
D = M

@ElementPointer
A=M


// getting length of array
@R2
D=M
// First value will be used as initial min
@LoopCounter
M = D - 1
D = M

@R1
//access last element of array
A = M + D
D = M

//place this value into tempMin
@tempMin
M = D


(ForArrLoop)
@LoopCounter
D = M

@R1
//access last element of array
A = M + D
D = M
@tempMin
D = M-D

@keepTemp
D;JLE
//else get the element and place it into temp
@R1
//access last element of array
A = M + D
D = M
@tempMin
M = D

(keepTemp)
// decrease the array length
@LoopCounter
M = M - 1
D = M - 1

//Check if the array has been searched through completely
@ForArrLoop
D;JGE

@tempMin
D=M

@R0
M=D

(End)
@End
A;JMP
