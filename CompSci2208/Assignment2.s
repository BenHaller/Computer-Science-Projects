                AREA Assignment5, CODE, READONLY
                ENTRY
		
                                                                        ; In the following block, 'Ini', the registers r1, r2 and r3 are set to their initial values
Ini             ADR             r1, STRING1                             ; Here, r1 is set to the address of STRING1
                                                                        ; r1 will be used throughout this program to point to the character of STRING1 currently being examined
                ADR             r2, STRING2                             ; Here, r2 is set to the address of STRING2
                                                                        ; r2 will be used throughout this program to point to the next available space in STRING2, where the next valid character will be written
                LDR             r3, =theMid                             ; Here, r3 is set to the list of hex. digits representing 'the ', which is defined below
                                                                        ; This will be used to check for instances of 'the' prior to the last word of the sentence
                                                                        ; We will use the value in r3 later to determine if there is an instance of 'the' that is to be removed from STRING1

                                                                        ; The following block, 'Start', checks the beginning of STRING1 for 'the'
                                                                        ; This is handled slightly differently than checking for instances of 'the' later in the sentence, as here there is no leading space
Start           LDRB            r0, [r1]                                ; The first character from STRING1 is loaded into r0
                                                                        ; r0 will be used throughout this program to store the ASCII value of the current character
                CMP             r0, #t                                  ; This compares the value in r0 to the ASCII value of 't', which is defined below
                BEQ             Check                                   ; If the value in r0 is equal to that of 't', branch to the 'Check' block to see if the current word is 'the'

                                                                        ; The following block, 'Iter', iterates through STRING1 to identify any possible instance of 'the'
Iter            LDRB            r0, [r1], #1                            ; Here, r0 is loaded with the digit of STRING1 pointed to by r1
                                                                        ; r1 is then incremented by 1 to point to the next digit in STRING1
                STRB            r0, [r2], #1                            ; Here, the value in r0 is stored in the digit of STRING2 pointed to by r2
                                                                        ; r2 is then incremented by 1 to point to the next free digit in STRING2
                CMP             r0, #EoS                                ; This compares the value in r0 to the null value, defined by EoS ("end of string") below
                BEQ             Label                                   ; If the value in r0 is equal to the ASCII representation of null, the program branches to the infinite loop
                CMP             r0, #spc                                ; This compares the value in r0 to the ASCII representation of a space, defined by spc below
                BNE             Iter                                    ; If the value in r0 is not a space, we are still in the current word, which is not 'the', and we iterate to the next letter in the word
                                                                        ; If the value in r0 is a space, the above BNE instruction does not execute and we continue on to check if the next word is 'the'

                                                                        ; The following block, 'WordIni', initializes a few registers to begin checking the next word in the sentence
                                                                        ; At this point, the character pointed to by r0 is the first character of some word in the sentence
WordIni	        MOV             r5, r1                                  ; Here, the digit of STRING1 pointed to by r1 is stored in r5 in case the word we are analyzing is not 'the'
                                                                        ; If the current word is not 'the', r5 will later be used to restore the current value of r1
                MOV             r4, #0.                                 ; Here, r4 is set to 0 in order to 'clear' the value within the register
                                                                        ; r4 will be used to store the string of characters representing the current word
		
                                                                        ; The following block, 'Insert', is used to create a list of the character ASCII values of the current word
                                                                        ; This word either checks for a string of characters representing 'the ' or 'the\0' if we are at the end of the sentence
Insert	        LDRB            r0, [r1], #1                            ; Here, r0 is loaded with the digit of STRING1 pointed to by r1
                CMP             r0, #EoS                                ; r0 is compared to the null character, to check whether or not we are at the end of the sentence
                LDREQ           r3, =theEnd                             ; If the current character is the null character, we are at the end of the sentence
                                                                        ; Thus, the value in r3 is set to the list of the characters representing 'the\0', or 'the' followed by the null character
                ADD             r4, r0                                  ; The value in r0 is added to the value in r4, which stores the string of characters in the current word
                CMP             r4, #0x1000000                          ; This comparison is used to check how many characters have been stored in r4
                                                                        ; If r4 is less than this value, it means that less than 4 character have been stored in it so far
                LSLLT           r4, #0x8                                ; If this is the case, first shift the bits in r4 left by 8 (i.e. two bytes left) in order to make room for the next character
                BLT             Insert                                  ; Then, branch back to Check in order to include the next letter of the word in r4
		
                                                                        ; The following block, 'Check', is used to check if the current word is an instance of 'the'
Check           CMP             r4, r3                                  ; Here, the value stored in r4 is compared to that stored in r3
                                                                        ; If these values are equal, the current word is either 'the ' or 'the\0', depending on whether or not we are at the end of the sentence
                SUBEQ           r1, #1                                  ; If the values are equal, we decrease the value pointed to by r1 in order to retain either the space or null character following 'the'
                MOVNE           r1, r5                                  ; If the values are not equal, the pointer to the digit of STRING1 previously stored in r5 is moved back into r1
                                                                        ; This allows the word to be stored in STRING2 if it is not an instance of 'the'

                B               Iter                                    ; Here, the program branches back to the Iter block in order to iterate to the next valid character in STRING1
                                                                        ; Either the character following the word if it is 'the', or the character pointed to before WordIni if it is not
		
Label           B               Label                                   ; This loop ensures that the program does not attempt to access memory that it doesn't have permissions for


EoS             EQU             0x00                                    ; This sequence of hex characters represents the null character in ASCII code
t               EQU             0x74                                    ; This sequence of hex characters represents 't' in ASCII code
spc             EQU             0x20                                    ; This sequence of hex characters represents the space character in ASCII code
theMid          EQU             0x74686520                              ; This sequence of hex characters represents 'the ' in ASCII code, or 'the' in the middle of a sentence
theEnd          EQU             0x74686500                              ; This sequence of hex characters represents 'the\0' in ASCII code, or 'the' at the end of a sentence


                AREA Assignment5, DATA, READWRITE
STRING1	        DCB             "the, the  the 123    the."             ; The STRING1 label marks the string to have all instances of 'the' removed from it
EoS1	          DCB             0x00                                    ; This simply marks the end of STRING1, as the string is null-terminated
STRING2	        SPACE           0x7F                                    ; The STRING2 label marks the location where the updated version of STRING1 will be stored

                ALIGN
                END
