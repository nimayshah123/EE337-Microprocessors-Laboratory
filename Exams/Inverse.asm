ORG 0H
LJMP MAIN
ORG 100H
MAIN:
CALL INVERSE
HERE: SJMP HERE
ORG 130H
// *****************
INVERSE:
MOV R2,64H
MOV R3,68H
MOV R4,65H
MOV R5,67H
LCALL multiplier
MOV 70h,R2

MOV R2,65H
MOV R3,66H
MOV R4,63H
MOV R5,68H
LCALL multiplier
MOV 71H, R2

MOV R2,63H
MOV R3,67H
MOV R4,64H
MOV R5,66H
LCALL multiplier
MOV 72H, R2

LCALL determinant //R0 now has the determinant

MOV R2,62H	
MOV R3,67H
MOV R4,61H
MOV R5,68H
LCALL multiplier
MOV 73h,R2

MOV R2,60H
MOV R3,68H
MOV R4,62H
MOV R5,66H
LCALL multiplier
MOV 74h,R2

MOV R2,61H
MOV R3,66H
MOV R4,60H
MOV R5,67H
LCALL multiplier
MOV 75h,R2

MOV R2,61H
MOV R3,65H
MOV R4,62H
MOV R5,64H
LCALL multiplier
MOV 76h,R2

MOV R2,63H
MOV R3,62H
MOV R4,60H
MOV R5,65H
LCALL multiplier
MOV 77h,R2

MOV R2,60H
MOV R3,64H
MOV R4,61H
MOV R5,63H
LCALL multiplier
MOV 78h,R2

LCALL transpose_it
MOV A,R0
MOV R7,A //R7 HAS THE DETERMINANT NOW

MOV R0, #70H
MOV R1, 70H
MOV R5, #10H
LCALL DIVIDER

LJMP HERE

RET

DIVIDER:
MOV A,@R0
MOV B,R7
DIV AB
MOV @R0,A
INC R0
CJNE R0, #79H, DIVIDER
RET


multiplier:
MOV A,R2
MOV B,R3
MUL AB
MOV R6,A
MOV A,R4
MOV B,R5
MUL AB
MOV R7,A
MOV A,R6
SUBB A,R7
MOV R2,A
ret

determinant:
MOV R2, 70H
MOV R3, 71H
MOV R4, 72H
MOV R5, 60H
MOV R6, 61H
MOV R7, 62H

MOV A,R2
MOV B,R5
MUL AB
MOV R2,A

MOV A,R3
MOV B,R6
MUL AB
MOV R3,A

MOV A,R4
MOV B,R7
MUL AB
MOV R4,A

MOV A,R2
ADD A,R3
ADD A,R4
JZ TERMINATE
MOV R0,A
RET

TERMINATE:
DEC A
MOV R0,A
MOV 70h, R0
MOV 71H, R0
MOV 72H, R0
MOV 73H, R0
MOV 74H, R0
MOV 75H, R0
MOV 76H, R0
MOV 77H, R0
MOV 78H, R0
JMP HERE

transpose_it:
MOV R1, 71H
MOV R2, 73H
MOV 71H, R2
MOV 73H, R1

MOV R1, 72H
MOV R2, 76H
MOV 72H, R2
MOV 76H, R1

MOV R1, 75H
MOV R2, 77H
MOV 75H, R2
MOV 77H, R1
RET

END