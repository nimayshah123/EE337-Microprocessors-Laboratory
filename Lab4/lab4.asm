ORG 0H
LJMP MAIN
ORG 100H
MAIN:
CALL TAKE_INP
CALL QUANT_ENC
CALL LED_DISP
HERE: SJMP HERE
ORG 130H
// *****************

DELAY_8s:
MOV R2, #100
MOV R3, #81
h3: acall delay_1ms
again: DJNZ R3, h3
MOV R3, #81
DJNZ R2, again
RET

DELAY_4s:
MOV R2, #100
MOV R3, #41
h2: acall delay_1ms
againie: DJNZ R3, h2
MOV R3, #41
DJNZ R2, againie
RET
	  
delay_1ms:
push 02h
push 03h
mov r2, #4
h1: acall delay_250us
djnz r2, h1
pop 03h
pop 02h
ret

delay_250us:
push 02h
mov r2, #244
h0: djnz r2, h0
pop 02h
ret

TAKE_INP:
MOV R5,#1Fh
MOV R0, #40h

MOV R7,#4

ABBA: MOV P1,R5
LCALL DELAY_8s
MOV A,P1
ANL A, #0Fh
MOV R6,A

MOV A, R5
ADD A, #16
MOV R5,A

MOV P1, R5
LCALL DELAY_8s
MOV A, P1
ANL A,#0FH
SWAP A
ADD A,r6
MOV @R0,A
INC R0
MOV A, R5
ADD A, #16
MOV R5,A

DJNZ R7, ABBA
ret

QUANT_ENC:
MOV R0, #40H

loop:
CLR C
MOV A, @R0
SUBB A, #40H
JC less_than_64

CLR C
MOV A, @R0
SUBB A, #80H
JC less_than_128

CLR C
MOV A, @R0
SUBB A, #0C0H
JC less_than_192

CLR C
MOV A, @R0
JMP greater_than_192

quant_enc_loop:
INC R0
CJNE R0, #44H, loop
ret

less_than_64:
MOV @R0, #01h
JMP quant_enc_loop

less_than_128:
MOV @R0, #02h
JMP quant_enc_loop

less_than_192:
MOV @R0, #04h
JMP quant_enc_loop

greater_than_192:
MOV @R0, #08h
//JMP quant_enc_loop
JMP quant_enc_loop

LED_DISP:
there: MOV R7,#4
MOV R0,#40h

MOVIE: MOV A,@R0
MOV B,#16
MUL AB
MOV P1,A
LCALL DELAY_4s
INC R0
DJNZ R7, MOVIE
SJMP there

RET
END