    .data
buffer: .space 4096   # Temporary buffer for storing words

    .text
    .globl main
main:
    # Step 1: Read memory address α
    jal readWord       # Read 32-bit address α from standard input
    move $s0, $3       # Store α in $s0 (base address for loading)

    # Step 2: Load and print MERL code segment
    move $t0, $s0      # $t0 holds current write address

load_loop:
    jal readWord       # Read a word from input
    beq $3, $zero, done_reading  # If end of input, stop

    sw $3, 0($t0)      # Store word at address α
    move $1, $3        # Move word to $1 for printing
    jal printHex       # Print word

    addiu $t0, $t0, 4  # Move to next memory location
    j load_loop        # Repeat

done_reading:
    move $t1, $s0      # Reset read address to α

print_loop:
    lw $1, 0($t1)      # Load word from memory
    jal printHex       # Print word

    addiu $t1, $t1, 4  # Move to next word
    bne $t1, $t0, print_loop  # Loop until all words printed again

    # Exit program
    li $v0, 10
    syscall
