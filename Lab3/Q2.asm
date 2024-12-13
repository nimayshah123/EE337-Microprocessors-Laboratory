ORG 0H
LJMP MAIN
ORG 100H
MAIN:
MOV P1, #01H
CALL DELAY_5s
MOV P1, #00H
HERE: SJMP HERE
ORG 130H
DELAY_5s:

MOV R0, #100
MOV R1, #51
h3: acall delay_1ms
again: DJNZ R1, h3
MOV R1, #51
DJNZ R0, again

RET
	  
delay_1ms:
push 00h
push 01h
mov r0, #4
h2: acall delay_250us
djnz r0, h2
pop 01h
pop 00h
ret
delay_250us:
push 00h
mov r0, #244
h1: djnz r0, h1
pop 00h
ret

END