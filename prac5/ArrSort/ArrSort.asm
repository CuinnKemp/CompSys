// Sorts the array of length R2 whose first element is at RAM[R1] in ascending order in place. Sets R0 to True (-1) when complete.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)


// Put your code here.
@outeriterator
M=0

(OUTERLOOP)
@inneriterator
M=0

(INNER)
// *(R1+inneriterator)
@R1
D=M

// iterating through the array
@inneriterator
A=M+D
D=A

//temporarily store the address of the inneriterator
@firstval
M=D
@secondval
M=D+1

//grabbing the data at that address
@firstval
A=M
D=M

//if negative
@IFNEG
D;JLT
//if positive
@IFPOS
D;JGT

(COMPARE)
// check if (firstval > secondval)
@firstval
A=M
D=M
@secondval
A=M
D=D-M
//swapping if greater than 0
@SWAP
D;JGT

(CHECKER)
// check if (inneriterator >= R2-outeriterator-1)
@outeriterator
D=M

// changing length of  bounds
@R2
D=D+1
D=M-D

//iterating inner
@inneriterator
M=M+1
D=D-M

//jumping to the inner loop
@INNER
D;JGT

// check if (outeriterator >= R2-1)
@outeriterator
M=M+1
D=M

//decrementing the length of the bounds
@R2
D=M-D
D=D-1

//back to the outer loop
@OUTERLOOP
D;JGT

(END)
@R0
M=-1
@END
0;JMP


(SWAP)
@firstval
A=M
D=M
//temporary value to store Firstval
@R4
M=D

//swaps them
@secondval
A=M
D=M
@firstval
A=M
M=D

//uses temp1 to put secondval as firstval
@R4
D=M
@secondval
A=M
M=D

@CHEKCER
0;JMP



(IFNEG)
//grabbing the data at second value
@secondval
A=M
D=M

//checking if greater than 0
@CHECKER
D;JGT

//comparing the vals otherwise
@COMPARE
0;JMP



// if the value is positive
(IFPOS)
//grabbing the data at second value
@secondval
A=M
D=M

//swapping if less than 0
@SWAP
D;JLT

// Otherwise comparing
@COMPARE
0;JMP
