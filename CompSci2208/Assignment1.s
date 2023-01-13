        AREA question1, CODE, READONLY
        ENTRY

                                       ; In the following block, 'Ini', the registers r0, r1 and r3 are initialized to the correct values
Ini     ADR r0, UPC                    ; Initialize r0 by setting it to the value in the UPC string
        MOV r1, #0                     ; Initialize r1 by setting it to 0 so that it will initially point to the first byte in r0
        MOV r3, #0                     ; Initialize r3 by setting it to 0 so that we can use it to accumulate the sum

                                       ; In the following block, 'Sum', the sum of all digits is accumulated which will later be checked for UPC validity
Sum     LDRB r2, [r0, r1]              ; Set r2 to the byte of r0 with the index of r1's current value
                                       ; This will be the first digit, then the third, etc., as we will deal with even digits later in this loop
        ADD r2, r2, r2, LSL #1         ; Multiply the value in r2 by three by taking the sum of r2 and r2 with 1-digit LSL and placing it back in r2
                                       ; We do this here as only an odd digit's value can be stored in r2 at this point in the loop
        ADD r3, r2                     ; Add this value to r3, in which our total sum will be stored
        ADD r1, #1                     ; Add 1 to the value in r1 to increment to the next digit in UPC
        LDRB r2, [r0, r1]              ; Set r2 to the byte of r0 with the index of r1's current value
                                       ; Now, we are dealing with even digits ie. the second, then fourth, etc.
                                       ; Note that the digit handled here in the last loop will be the check digit, which is treated no differently than the other even digits
        ADD r3, r2                     ; Add this value to r3 (the total sum)
        SUB r3, #toInt                 ; Here, the value in toInt is subtracted from r3, which converts from the ASCII codes of the odd and even digits added in one iteration of this loop back to their integer equivalent
        ADD r1, #1                     ; Increment r1 to the next digit in UPC
        CMP r1, #lastDig               ; Compare the current index to that of the last digit in the UPC code
        BNE Sum                        ; If the index does not yet equal to that of the last, loop back to Sum and handle the next two digits

                                       ; This block, 'SubTen', is used to check if the previously calculated sum is a multiple of 10, determining if the UPC is valid or not
SubTen  CMP r3, #-10                   ; Compare the value in r3 to -10, this comparison's status will determine the validity of the UPC code
        MOVEQ r0, #1                   ; If the value in r3 is -10, that means the code was a multiple of 10, the UPC is valid, and r1 is assigned the value 1
        MOVLT r0, #2                   ; If the value in r3 is less than -10, that means the code was not a multiple of 10, the UPC is invalid, and r1 is assigned the value 2
        SUB r3, #10                    ; The value in r3 has 10 subtracted from it in each iteration of the loop to determine validity
        BGT SubTen                     ; If the value in r3 was greater than -10 during the comparison at the 'SubTen' label, loop back to SubTen and complete another iteration
                                       ; Else, r3 is either equal to or less than -10 and r0 will have been set accordingly

Label   B Label                        ; This loop ensures that the program does not attempt to access memory that it doesn't have permissions for

UPC     DCB "013800150738"             ; Set up the UPC string in memory
toInt   EQU 0xC0                       ; The toInt symbol represents the constant used above to convert from ASCII code to numerical equivalent
                                       ; The value here is 0xC0, or 4 times 0x30, as this digit is used to convert the sum of 3 times some odd digit and some even digit to its numerical equivalent
lastDig EQU 12                         ; The lastDig symbol represents the index of the last digit within the UPC code

        END
