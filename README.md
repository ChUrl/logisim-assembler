# README

Small assembler that generates Logisim readable memory files for [this](https://gitlab.com/ChUrl/logisim-cpu).
**Since I stopped using Logisim for the CPU design, this repository is succeeded by [this](https://gitlab.com/ChUrl/systemverilog-rom-assembler).**

## Usage

`lasm -i <inputfile> -o <outputfile>`

## Instructionset

| Instruction | 1. Operand                  | 2. Operand      | Note                                   |
|-------------|-----------------------------|-----------------|----------------------------------------|
| MOV         | Constant or Source Register | Target Register |                                        |
| AND         | NONE                        | NONE            | Works on reg1 and reg2, result in reg3 |
| OR          | NONE                        | NONE            | Works on reg1 and reg2, result in reg3 |
| NAND        | NONE                        | NONE            | Works on reg1 and reg2, result in reg3 |
| NOR         | NONE                        | NONE            | Works on reg1 and reg2, result in reg3 |
| ADD         | NONE                        | NONE            | Works on reg1 and reg2, result in reg3 |
| SUB         | NONE                        | NONE            | Works on reg1 and reg2, result in reg3 |
| JMP         | NONE                        | NONE            | Works on reg3                          |
| JEQ         | NONE                        | NONE            | Works on reg3                          |
| JLE         | NONE                        | NONE            | Works on reg3                          |
| JLEQ        | NONE                        | NONE            | Works on reg3                          |
| NOP         | NONE                        | NONE            | Works on reg3                          |
| JNEQ        | NONE                        | NONE            | Works on reg3                          |
| JGR         | NONE                        | NONE            | Works on reg3                          |
| JGEQ        | NONE                        | NONE            | Works on reg3                          |

Line comments are recognized, indicated by '#'

