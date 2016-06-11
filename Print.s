; Print.s
; Student names: change this to your names or look very silly
; Last modification date: change this to the last modification date or look very silly
; Runs on LM4F120 or TM4C123
; EE319K lab 7 device driver for any LCD
;
; As part of Lab 7, students need to implement these LCD_OutDec and LCD_OutFix
; This driver assumes two low-level LCD functions
; ST7735_OutChar   outputs a single 8-bit ASCII character
; ST7735_OutString outputs a null-terminated string 

    IMPORT   ST7735_OutChar
    IMPORT   ST7735_OutString
    EXPORT   LCD_OutDec
    EXPORT   LCD_OutFix

    AREA    |.text|, CODE, READONLY, ALIGN=2
    THUMB
	PRESERVE8 {TRUE}
Char_A EQU 0					; Binding for local variables
decim EQU 0 

;-----------------------LCD_OutDec-----------------------
; Output a 32-bit number in unsigned decimal format
; Input: R0 (call by value) 32-bit unsigned number
; Output: none
; Invariables: This function must not permanently modify registers R4 to R11
LCD_OutDec
	PUSH {R4,LR}			; Preserve original value of R4 and pushes LR onto the stack.
	SUB SP,#4				; Allocation of 32 bits in memory for local variable
	STR R0, [SP, #Char_A]	; Store input in local variable, Char A (Access)
	ADD SP,#4				; Deallocate the memory for the local variable.
	MOV R1,R0				
	LDR R4, =0				; R4 is the counter variable.
	
loop	; %10 Operation
		LDR R3, =10
		UDIV R2, R1, R3		; Integer division of decimal value and 10
		MLS R3, R3, R2, R1  ; Input - ((Input/10)*10)
		PUSH {R3}			; Store digit. LSB will be the at highest memory address; MSB will be at the highest.
		ADD R4, #1			; Increment the counter.
		
		LDR R3, =10			; Divide decimal value by 10.
		UDIV R1, R3
		
		CMP R1, #0			; If decimal value is greater than 0, go to the loop again.
		BNE loop
		
loop2	CMP R4, #0			; Is the counter equal to 0 yet?
		BEQ ret				; -> If so, return from the function.
		POP {R0}			; Otherwise, update R0.
		ADD R0, #0x30
		BL ST7735_OutChar	; Output char.
		SUB R4, #1			; Decrement counter.
		B loop2
		
ret		POP {R4,PC}			; Restore R4 and return from the function.
;* * * * * * * * End of LCD_OutDec * * * * * * * *

; -----------------------LCD _OutFix----------------------
; Output characters to LCD display in fixed-point format
; unsigned decimal, resolution 0.001, range 0.000 to 9.999
; Inputs:  R0 is an unsigned 32-bit number
; Outputs: none
; E.g., R0=0,    then output "0.000 "
;       R0=3,    then output "0.003 "
;       R0=89,   then output "0.089 "
;       R0=123,  then output "0.123 "
;       R0=9999, then output "9.999 "
;       R0>9999, then output "*.*** "
; Invariables: This function must not permanently modify registers R4 to R11
LCD_OutFix
	PUSH {R4,LR}						; Push used registers
	SUB SP,#4							; Allocation for local variable decim
	STR R0, [SP, #decim]				; Store R0 in decim local variable (Access).
	ADD SP,#4							; Deallocation
	LDR R1, =9999						
	CMP R0, R1							; Is R0 > 9999?
	BHI Overnum							; -> If so, go to Overnum, which prints "*.***"
		 
	MOV R4, R0							; Print the most significant bit.
	MOV R1, #1000						
	UDIV R0, R4, R1					
	ADD R0, #0x30						
	BL ST7735_OutChar
		 
	MOV R0, #0x2E						; Print a decimal point.
	BL ST7735_OutChar
		 
	MOV R0, R4							; R4 contains the original number.
	MOV R1, #1000						; Get R0 % 1000
	BL MOD								
	MOV R4, R0							; R4 = R0 % 1000 (thousandths place)
	
	MOV R1, #100						;tenth's place
	UDIV R0, R4, R1
	ADD R0, #0x30
	BL ST7735_OutChar
	
	MOV R0, R4							
	MOV R1, #100
	BL MOD								; R4 % 100
	MOV R4, R0							
		 
	MOV R1, #10							;hundredth's place
	UDIV R0, R4, R1
	ADD R0, #0x30
	BL ST7735_OutChar
	
	MOV R0, R4							; R4 % 10 LSB)
	MOV R1, #10
	BL MOD
		 
	ADD R0, #0x30						;MSB
	BL ST7735_OutChar
		 
    POP {R4,PC}
	
Overnum	; Output *.***
		 MOV R0,#0x2A
		 BL ST7735_OutChar
		 MOV R0,#0x2E
		 BL ST7735_OutChar
		 MOV R0,#0x2A
		 BL ST7735_OutChar
		 MOV R0,#0x2A
		 BL ST7735_OutChar
		 MOV R0,#0x2A
		 BL ST7735_OutChar
		 POP {R4,PC}
MOD	; Modulus Operation
	UDIV R2, R0, R1
	MUL R1, R2
	SUB R0, R1
	BX LR
 
     ALIGN
;* * * * * * * * End of LCD_OutFix * * * * * * * *

     ALIGN                           ; make sure the end of this section is aligned
     END                             ; end of file
