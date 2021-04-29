<br><img src="./image/interpreter.png" width="30%" alt = "image" align = "left"/> 
### Welcome!
*Tired of fixing compiler errors?* <br/>
*Do you keep forgetting the semicolon?* <br/>
*Are you missing the capabilities of your favorite programming language?* <br/><br/>

**We will help you! Let's write an interpreter for our own programming language, and no one but us can give us errors.**

<cut />
<br clear = "left">

---
To download, enter in the command line: 
```
git clone https://github.com/Valeriya-avt/interpreter
```
To compile, enter: 
```
make
```
You can run the program as follows: 

```
bin/main path/_to_file 
```
You can also use the `-detail` flag to see more detailed work of the interpreter:
```
bin/main path_to_file -detail
```
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
 * Work with a `while` cycle;
 * Work with arrays;
 * Work with functions.

Let's take a look at some of the main points.

**We can use the following operators**

>**Arithmetic operators:**

| Opername |PLUS | MINUS | MULT | DIV | MOD |
|----------|-----|-------|------|-----|-----|
|**Symbol**| \+  |  \-   |  \*  |  /  |  %  |

>**Assignment operator:**

| Opername | ASSIGN |
|----------|--------|
|**Symbol**|   :=   |

>**Bitwise operators:**

| Opername | XOR | BITAND | SHL | SHR |
|----------|-----|--------|-----|-----|
|**Symbol**|  ^  |    &   | <<  |  >> |

>**Logical operators:**

| Opername | OR | AND | EQ | NEQ | LEQ | LT | GEQ | GT | 
|----------|----|-----|----|-----|-----|----|-----|----|
|**Symbol**| or | and | == | !=  |<= |  < |  >= |  > | 

>**Jump operator:**

| Opername | GOTO |
|----------|------|
|**Symbol**| goto |

>**Conditional operator:**

| Opername | IF | THEN | ELSE | ENDIF |
|----------|----|------|------|-------|
|**Symbol**| if | then | else | endif |

>**`While` cycle:**

|   Name   | WHILE | THEN | ENDWHILE | 
|----------|-------|------|----------|
|**Symbol**| while | then | endwhile |

---

**The main stages of the interpreter's work:**
1. Read the source code of the program and create an infix notation;
2. Initialize all transitions (go to and jumps);
3. Convert infix notation to postfix notation;
4. Start executing the code from the `main` function;
5. The basic calculations are performed in the `evaluatePostfix` function.

---
Let's give an example of interpreting infix notation into postfix notation.

**Some code:** 

```
function main()
    n := 10
    i := 0
    a := 1
    b := 1
    while i < (n - 2) then
        c := a + b
        a := b
        b := c
        i := i + 1
    endwhile
    print b
    return

```
**Infix:**
```
1: [GOTO<row -2147483647>function] [main] [ ( ] [ ) ] 
2: [n] [:=] [10] 
3: [i] [:=] [0] 
4: [a] [:=] [1] 
5: [b] [:=] [1] 
6: [GOTO<row -2147483647>while] [i] [<] [ ( ] [n] [-] [2] [ ) ] [then] 
7: [c] [:=] [a] [+] [b] 
8: [a] [:=] [b] 
9: [b] [:=] [c] 
10: [i] [:=] [i] [+] [1] 
11: [GOTO<row -2147483647>endwhile] 
12: [print] [b] 
13: [GOTO<row -2147483647>return] 
```

**Postfix:**
```
1: [main] [GOTO<row 1>function] 
2: [n] [10] [:=] 
3: [i] [0] [:=] 
4: [a] [1] [:=] 
5: [b] [1] [:=] 
6: [i] [n] [2] [-] [<] [GOTO<row 11>while] 
7: [c] [a] [b] [+] [:=] 
8: [a] [b] [:=] 
9: [b] [c] [:=] 
10: [i] [i] [1] [+] [:=] 
11: [GOTO<row 5>endwhile] 
12: [b] [print] 
13: [GOTO<row -2147483647>return] 
```

Let's try to check the work of our interpreter on this program. To do this, enter into the command line: 
```
bin/main res/if_while/fibonacci.txt
```
For convenience, infix and postfix entries will be displayed on the screen. 

<p align="center">
<img src="https://github.com/Valeriya-avt/interpreter/blob/main/image/if_while_fibonacci.gif" width="80%"></p>

The problem of calculating Fibonacci numbers sounds pretty interesting, right? Let's try to solve this problem in several ways. We saw the first method, it works great! 

Now let's save the results of calculating the Fibonacci numbers into an array:
```
function main()
    f size 15
    n := 10
    f[0] := 0
    f[1] := 1
    i := 2
    while i <= n then
        f[i] := f[i - 1] + f[i - 2]
        print f[i]
        i := i + 1
    endwhile
    return
```

```
bin/main res/arrays/fibonacci.txt
```

<p align="center">
<img src="https://github.com/Valeriya-avt/interpreter/blob/main/image/arrays_fibonacci.gif" width="80%"></p>

<p align="center">
<img src="https://github.com/Valeriya-avt/interpreter/blob/main/image/arrays_image_1.png" width="80%"></p>

<p align="center">
<img src="https://github.com/Valeriya-avt/interpreter/blob/main/image/arrays_image_2.png" width="80%"></p>

---

Let's test the functions! Let's take the main calculations into a separate function that returns the desired Fibonacci number.

```
function fibonacci(n)
    a size 100
    a[0] := 0
    a[1] := 1
    i := 2
    while i <= n then
        a[i] := a[i - 1] + a[i - 2]
        print a[i]
        i := i + 1
    endwhile
    return a[n]

function main()
    n := 10
    answer := fibonacci(n)
    print answer
    return
```

```
bin/main res/functions/fibonacci1.txt
```

<p align="center">
<img src="https://github.com/Valeriya-avt/interpreter/blob/main/image/functions_fibonacci1.gif" width="80%"></p>

---

The function argument can even be an array!

```
function fibonacci(a, n)
    a[0] := 0
    a[1] := 1
    i := 2
    while i <= n then
        a[i] := a[i - 1] + a[i - 2]
        print a[i]
        i := i + 1
    endwhile
    return

function main()
    a size 100
    n := 10
    fibonacci(a, n)
    print a[n]
    return
```

```
bin/main res/functions/fibonacci2.txt
```
<p align="center">
<img src="https://github.com/Valeriya-avt/interpreter/blob/main/image/functions_fibonacci2.gif" width="80%"></p>

---

Think recursion is difficult and dangerous? Perhaps, but not with our interpreter and not with this task!

```
function fibonacci(n)
    if n < 2 then
        return n
    endif
    return fibonacci(n - 1) + fibonacci(n - 2)

function main()
    n := 10
    answer := fibonacci(n)
    print answer
    return
```

```
bin/main res/functions/fibonacci_recursion.txt
```
<p align="center">
<img src="https://github.com/Valeriya-avt/interpreter/blob/main/image/functions_fibonacci_recursion.gif" width="80%"></p>

I’m very glad if you liked this interpreter. I look forward to your comments and ideas!
