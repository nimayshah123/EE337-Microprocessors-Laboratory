ORG 0H
LJMP MAIN
ORG 100H
MAIN:
CALL ADD16
HERE: SJMP HERE
ORG 130H
// *****************
ADD16:
CLR C
MOV A, 71h
ADD A, 73h
MOV 76h, A
MOV A, 72h
ADDC A, 70h
MOV 75h,A
CLR A
MOV ACC.0,C
MOV 74h,A

RET

END