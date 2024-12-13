ORG 0H
LJMP MAIN
ORG 100
MAIN:
CALL FINDn // N in R5
MOV 30H, R5
MOV R0, #40H
CALL FINDr // R6 <= r
BACK: MOV R0, #40H
MOV A, @R0 //A has the value at 40h(2)
MOV R5, 30H
BACKIN:
MOV B, R6 //R6 is 41h/40h=(4/2)=2
MUL AB //A has 4 and B has 0 now
MOV P1, A //Port gets a value 4
CALL DELAY 
DJNZ R5, BACKIN //goes on until R5 becomes 0 i.e 5 times
JMP BACK //goes on in an infinite loop then

ORG 200
FINDn:
PUSH 0
MOV R0, #50H
MOV A, @R0
MOV R5, A //N
POP 0
RET

FINDr:
INC R0
MOV A, @R0
DEC R0
MOV B, @R0
DIV AB
MOV R6, A
RET

DELAY:
PUSH ACC
PUSH B
PUSH 5
PUSH 6
MOV R5, #0xFF //Max out R5 and R6
MOV R6, #0xFF
HERE1: DEC R5
HERE2: DJNZ R6, HERE2 //Runs until R6 becomes 0
MOV A, R5 //loops until R5 becomes 0
JNZ HERE1
POP 6 //makes r6=2 that was earlier stored in the stack
POP 5 //makes r5=5 that was stored eariler
POP B 
POP ACC //Makes A=04 as earlier
RET

END