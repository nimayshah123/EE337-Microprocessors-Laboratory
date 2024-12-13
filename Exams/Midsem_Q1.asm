ORG 0H
LJMP MAIN
ORG 100H
MAIN:
LCALL DELAYER
HERE: SJMP HERE
ORG 130H
// *****************
DELAYER:
SETB P1.0

FIRSE:
LCALL the
CLR P1.0
LCALL next
SETB P1.0
JMP FIRSE

the:
MOV R3, #3
h3: acall delay_200us
DJNZ R3, h3
RET

next:
MOV R3, #7
h2: acall delay_200us
DJNZ R3, h2
RET
	  

delay_200us:
push 02h
mov r2, #255
h0: djnz r2, h0
pop 02h
ret

end