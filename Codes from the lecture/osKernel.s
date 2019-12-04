				AREA| .text,CODE,READONLY,ALIGN=2
				THUMB
				EXTERN currentPt
				
				
SysTick_Handler				 		;Saves r0,r1,r2,r3,r12,lr,pc,psr
		CPSID		I
		PUSH		{R4-R11}		;Save r4.r5.r6.r7.r8,r9,r10,r11
		LDR			R0,=currentPt	;r0 points to currentPt
		LDR			R1,{R0}			;r1 = currentPt
		STR			SP,[R1]
		LDR			R1,[R1,#4]		;r1 = currentPt->next
		STR			R1,[R0]			;currentPt = r1
		LDR			SP,[R1]			;SP = currentPt -> stackPt
		
		