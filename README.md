<br><img src="./image/interpreter.png" width="30%" alt = "image" align = "left"/> 
### Welcome!
*Tired of fixing compiler errors?* <br/>
*Do you keep forgetting the semicolon?* <br/>
*Are you missing the capabilities of your favorite programming language?* <br/><br/>

**We will help you! Let's write an interpreter for our own programming language, and no one but us can give us errors.**

<cut />
<br clear = "left">

---

### This interpreter can:
 * Read code from file;
 * Divide the code into tokens by creating an infix notation;
 * Build a postfix record based on an infix record;
 * Work with arithmetic operators;
 * Handle the assignment operator;
 * Work with logical operators;
 * Realize the work of the jump operator (`goto`);
 * Handle a conditional statement;
 * Work with a `while` cycle. 

Let's take a look at some of the main points.

**We can use**

>**Arithmetic operators:**

| Opername |PLUS | MINUS | MULT | DIV | MOD |
|----------|-----|-------|------|-----|-----|
|  Symbol  | \+  |  \-   |  \*  |  /  |  %  |

>**Assignment operator:**

| Opername | ASSIGN |
|----------|--------|
|  Symbol  |   :=   |

>**Bitwise operators:**

| Opername | XOR | BITAND | SHL | SHR |
|----------|-----|--------|-----|-----|
|  Symbol  |  ^  |    &   | <<  |  >> |

>**Logical operators:**

| Opername | OR | AND | EQ | NEQ | LEQ | LT | GEQ | GT | 
|----------|----|-----|----|-----|-----|----|-----|----|
|  Symbol  | or | and | == | !=  |<= |  < |  >= |  > | 

>**Jump operator:**

| Opername | GOTO |
|----------|------|
|  Symbol  | goto |

>**Conditional operator:**

| Opername | IF | THEN | ELSE | ENDIF |
|----------|----|------|------|-------|
|  Symbol  | if | then | else | endif |

>**`While` cycle:**

|   Name   | WHILE | THEN | ENDWHILE | 
|----------|-------|------|----------|
|  Symbol  | while | then | endwhile |

