The Little Person Computer (lpc), an updated version of the Little Man Computer. In this assignment, I will simulate the lpc using a C program. The lpc runs programs in the Little Person Language (lpl) and contains an accumulator, a special register where I store all information before the lpc can use or examine it.

I handle all information in terms of words, which are 4-bit signed decimal numbers (e.g., +3364, -1234, +0007, -0001). The lpc has a 100-word memory, and I refer to memory locations by their 2-digit addresses (00 to 99). Before I run an lpc program, I need to load it into the memory, starting with the first instruction at location 00. Each instruction is a 4-digit word, where the sign of an instruction is always positive, while data words can be positive or negative.

Each memory location in the lpc contains either an instruction, a data value, or is unused (undefined). The first two digits of an instruction represent the op-code, specifying the operation to be performed, while the last two digits are the operand, indicating the memory location to which the instruction applies.


![image](https://github.com/user-attachments/assets/0734c088-193c-42cc-9f58-1f39086603f2)
