    .import readWord 
    .import printHex

    # Constants
    .eqv HEADER_SIZE 8  # Offset in words (8 * 4 bytes = 32 bytes)
    .eqv OUTPUT_ADDR 0xffff000c  # Memory-mapped I/O for output
    .eqv INPUT_ADDR 0xffff0004   # Memory-mapped I/O for input

    main:
        # Step 1: Skip the header
        li $5, HEADER_SIZE  # Counter to skip header
    skip_header:
        beqz $5, read_code_segment
        jal readWord   # Read and discard header word
        sub $5, $5, 1  # Decrement counter
        j skip_header

    # Step 2: Read and print the code segment
    read_code_segment:
        jal readWord   # Read next word from input
        beqz $3, end   # Stop if EOF (0 word)
        move $1, $3    # Move read value to $1 for printHex
        jal printHex   # Print hexadecimal representation
        
        # Store to memory-mapped output (stdout)
        li $2, OUTPUT_ADDR
        sw $1, 0($2)
        
        j read_code_segment  # Continue reading next word

    end:
        jr $31         # Return from program
