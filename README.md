# Assignment2
Advanced Representation Direct Mapping and Signed Numbers

## Files
- **main.c** – Test runner program. Reads the test file, runs appropriate function, prints PASS/FAIL, and shows a summary.

- **convert.c** – Implementation of required functions:
  - `oct_to_bin` – maps octal digits to 3-bit binary
  - `oct_to_hex` – converts octal to hexadecimal
  - `hex_to_bin` – maps hex digits to 4-bit binary
  - `to_sign_magnitude` – 32-bit sign-magnitude representation
  - `to_ones_complement` – 32-bit one’s complement representation
  - `to_twos_complement` – 32-bit two’s complement representation
- **A2_tests.txt** – Provided test cases
- **output.txt** – Generated test results after running the program.
- **Makefile** – Build automation (compile + run).

## Build & Run Instructions
Run the following command in the terminal:

```bash
make