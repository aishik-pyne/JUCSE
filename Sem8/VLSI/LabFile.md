# VSLI LAB REPORT

## Index

1. Half Adder
2. Full Adder Deisgn using Half Adder
3. 4 Bit Ripple Carry Adder design using 1 Bit Full Adder.
4. Adder Subtractor Block
5. BCD Adder
6. 2:1 Multiplexer
7. 4:1 Multiplexer design using 2:1 Multiplexer
8. 1:4 Demultiplexer
9. 3:8 Decoder
10. Flip Flip
    - D Flip Flip
    - RS Flip Flip
    - JK Flip Flip
    - T Flip Flip
11. 7 Segment Decoder
12. 4 Bit Comparator
13. Binary-to-Gray Code Converter
14. 4 Bit ALU

---

## Half Adder

**Experiment Number** : 1  

**Experiment Name** : Half Adder

**Circuit Diagram** :  

<img src="diagrams/VSLI.png" alt="drawing" width="350" height="300"/>

**Truth Table**:

 |   A   |   B   |  SUM  | CARRY |
 | :---: | :---: | :---: | :---: |
 |   0   |   0   |   0   |   0   |
 |   0   |   1   |   1   |   0   |
 |   1   |   0   |   1   |   0   |
 |   1   |   1   |   0   |   1   |

**VHDL Code** :

```vhdl
----------------------------------------------------------------------------------
-- Design Name:    1 Bit Half Adder Design 
-- Module Name:    halfadder - Behavioral 
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity halfadder is
    Port ( a : in  STD_LOGIC;
           b : in  STD_LOGIC;
           sum : out  STD_LOGIC;
           cout : out  STD_LOGIC);
end halfadder;

architecture Behavioral of halfadder is

begin

sum<= a xor b;
cout<= a and b;


end Behavioral;

```

**Output Waveform** :

---

## Full Adder Deisgn using Half Adder

**Experiment Number** : 2

**Experiment Name** : Full Adder Deisgn using Half Adder

**Circuit Diagram** :  

<img src="diagrams/full-adder.png" alt="drawing" width="350" height="300"/>
**Truth Table**:

 |   A   |   B   |  SUM  | CARRY |
 | :---: | :---: | :---: | :---: |
 |   0   |   0   |   0   |   0   |
 |   0   |   1   |   1   |   0   |
 |   1   |   0   |   1   |   0   |
 |   1   |   1   |   0   |   1   |

**VHDL Code** :

```vhdl
----------------------------------------------------------------------------------
-- Design Name:    1 Bit Half Adder Design 
-- Module Name:    halfadder - Behavioral 
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity halfadder is
    Port ( a : in  STD_LOGIC;
           b : in  STD_LOGIC;
           sum : out  STD_LOGIC;
           cout : out  STD_LOGIC);
end halfadder;

architecture Behavioral of halfadder is

begin

sum<= a xor b;
cout<= a and b;


end Behavioral;

```

**Output Waveform** :

---
