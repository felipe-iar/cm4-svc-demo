                NAME    SVC_Handler
                SECTION .text:CONST(2)

                IMPORT SVC_Handler_C

                PUBLIC SVC_Handler
                THUMB
SVC_Handler:
                TST lr, #4
                ITE EQ
                MRSEQ r0, MSP
                MRSNE r0, PSP
                B SVC_Handler_C
                END