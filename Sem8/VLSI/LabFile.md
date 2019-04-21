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

<img src="diagrams/half-adder.png" alt="drawing"  height="300"/>

**Truth Table** :

 |   A   |   B   |  SUM  | CARRY |
 | :---: | :---: | :---: | :---: |
 |   0   |   0   |   0   |   0   |
 |   0   |   1   |   1   |   0   |
 |   1   |   0   |   1   |   0   |
 |   1   |   1   |   0   |   1   |

**VHDL Code**

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

**Output Waveform**

---

## Full Adder Deisgn using Half Adder

**Experiment Number** : 2

**Experiment Name** : Full Adder Deisgn using Half Adder

**Circuit Diagram**  

<img src="diagrams/full-adder.png" alt="drawing"  height="300"/>

**Truth Table** :

 |   A   |   B   |  Cin  |  SUM  | Cout  |
 | :---: | :---: | :---: | :---: | :---: |
 |   0   |   0   |   0   |   0   |   0   |
 |   0   |   0   |   1   |   1   |   0   |
 |   0   |   1   |   0   |   1   |   0   |
 |   0   |   1   |   1   |   0   |   1   |
 |   1   |   0   |   0   |   1   |   0   |
 |   1   |   0   |   1   |   0   |   1   |
 |   1   |   1   |   0   |   0   |   1   |
 |   1   |   1   |   1   |   1   |   1   |

**VHDL Code** :

```vhdl
----------------------------------------------------------------------------------
-- Design Name:    1Bit Full Addrer design using Half Adder
-- Module Name:    fulladder - Behavioral 
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;


entity fulladder is
    Port ( a : in  STD_LOGIC;
           b : in  STD_LOGIC;
           cin : in  STD_LOGIC;
           sum : out  STD_LOGIC;
           cout : out  STD_LOGIC);
end fulladder;

architecture Behavioral of fulladder is

-- Componet of Half Adder
component halfadder is
    Port ( a : in  STD_LOGIC;
           b : in  STD_LOGIC;
           sum : out  STD_LOGIC;
           cout : out  STD_LOGIC);
end component;

signal m,n,l:std_logic;

begin

a0:halfadder port map(a,b,m,n);
a1:halfadder port map(m,cin,sum,l);
cout<= l or n;

end Behavioral;


```

**Output Waveform**

---

## 4 Bit Ripple Carry Adder design using 1 Bit Full Adder

**Experiment Number** : 3

**Experiment Name** : 4 Bit Ripple Carry Adder design using 1 Bit Full Adder

**Circuit Diagram** :

<img src="diagrams/ripple-carry-adder.png" alt="drawing"  height="300"/>


**VHDL Code** :

```vhdl
----------------------------------------------------------------------------------
-- Design Name:    4 Bit Ripple Carry Adder design using 1 Bit Full Adder
-- Module Name:    rippleadder - Behavioral 
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;


entity rippleadder is
    Port ( a : in  STD_LOGIC_VECTOR (3 downto 0);
           b : in  STD_LOGIC_VECTOR (3 downto 0);
           cin : in  STD_LOGIC;
           sum : out  STD_LOGIC_VECTOR (3 downto 0);
           cout : out  STD_LOGIC);
end rippleadder;

architecture Behavioral of rippleadder is

-- Componet of Full Adder
component fulladder is
    Port ( a : in  STD_LOGIC;
           b : in  STD_LOGIC;
           cin : in  STD_LOGIC;
           sum : out  STD_LOGIC;
           cout : out  STD_LOGIC);
end component;

-- Intermediate Carry declaration
signal c1,c2,c3: STD_LOGIC;

begin

FA1: fulladder port map( a(0), b(0), cin, s(0), c1);
FA2: fulladder port map( a(1), b(1), c1, s(1), c2);
FA3: fulladder port map( a(2), b(2), c2, s(2), c3);
FA4: fulladder port map( a(3), b(3), c3, s(3), cout);

end Behavioral;


```

**Output Waveform**

---

## Adder Subtractor Block

**Experiment Number** : 4

**Experiment Name** : Adder Subtractor Block

**Circuit Diagram** :

<img src="diagrams/ripple-carry-adder.png" alt="drawing"  height="300"/>


**VHDL Code** :

```vhdl
----------------------------------------------------------------------------------
-- Design Name:    Modified Full Adder
-- Module Name:    fulladder-modified - Behavioral 
----------------------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;
entity fulladder is
   port( X, Y, Cin : in std_logic;
         sum, Cout : out std_logic);
end fulladder;

architecture Behavioral of fulladder is
begin
   sum &amp;lt;= (X xor Y) xor Cin;
   Cout &amp;lt;= (X and (Y or Cin)) or (Cin and Y);
end Behavioral;
```

```vhdl
----------------------------------------------------------------------------------
-- Design Name:    4 bit Adder Subtractor
-- Module Name:    addsubblock - Behavioral 
----------------------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;

-- Define addsubblock ports
entity addsubblock is
   port( OP: in std_logic;
          A,B  : in std_logic_vector(3 downto 0);
          R  : out std_logic_vector(3 downto 0);
          Cout, OVERFLOW : out std_logic);
end addsubblock;

architecture Behavioral of addsubblock is

-- Componet of Full Adder
component fulladder is
  port( X, Y, Cin : in std_logic;
        sum, Cout : out std_logic);
end component;

signal C1, C2, C3, C4: std_logic;
signal TMP: std_logic_vector(3 downto 0);

begin
TMP &lt;= A xor B;
FA0:fulladder port map(A(0),TMP(0),OP, R(0),C1);-- R0
FA1:fulladder port map(A(1),TMP(1),C1, R(1),C2);-- R1
FA2:fulladder port map(A(2),TMP(2),C2, R(2),C3);-- R2
FA3:fulladder port map(A(3),TMP(3),C3, R(3),C4);-- R3
OVERFLOW &lt;= C3 XOR C4 ;
Cout &lt;= C4;
end Behavioral;
```

**Output Waveform**

---
