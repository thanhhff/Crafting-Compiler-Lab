### Câu 1

1. Cách chạy biên dịch chương trình 

Bước 1: Compiler file Fibonaci.kpl
```
    ./kplc tests/Fibonaci.kpl Fibonaci
```

Bước 2: Chạy chương trình 
```
    ./kplrun Fibonaci
```

2. Biên dịch với tham số -dump 
```
    ./kplc tests/Fibonaci.kpl Fibonaci -dump
```
> Kết quả chạy:
```
0:  J 37        # Nhay den vi tri 37
--- Function
1:  J 2         # Nhay den vi tri 2
2:  INT 5       # Cong 5: 4 cai : RV,DL,RA,SL va bien n

---if n <= 0 then Fibonaci := 0;

3:  LV 0,4      # load value cua n
4:  LC 0        # load constant 0 (Cho nay la lenh IF)
5:  LE          # check <=
6:  FJ 10       # kiem tra fail jump => nhay den 10
7:  LA 0,0      # load address cua function 
8:  LC 0        # load constant 
9:  ST          # luu lai

---if n = 1 then Fibonaci := 1;

10:  LV 0,4     # load value n
11:  LC 1       # load contant 1
12:  EQ         # kiem tra equal
13:  FJ 17      # fail jump -> 17
14:  LA 0,0     # address cua function
15:  LC 1       # load constant 1   
16:  ST         # luu Fibonaci := 1;

---if n > 1 then Fibonaci := Fibonaci(n - 1) + Fibonaci(n - 2);

17:  LV 0,4     # load value n
18:  LC 1       # load constant 1
19:  GT         # kiem tra lon hon
20:  FJ 36      # faile nhay den 36
21:  LA 0,0

22:  INT 4      # tang 4 de luu 4 cai RV, DL, RA, SL: Fibonaci(n - 1)
23:  LV 0,4
24:  LC 1
25:  SB         # n - 1
26:  DCT 5      # giam 5
27:  CALL 1,1   # goi de quy
28:  INT 4      # tang 4 : Fibonaci(n - 2)
29:  LV 0,4     # load value 
30:  LC 2       # load constant
31:  SB         # phep tru
32:  DCT 5      # giam 5
33:  CALL 1,1   # goi ham
34:  AD         # add 2 function
35:  ST         # luu lai vao Fibonaci := Fibonaci(n - 1) + Fibonaci(n - 2);
36:  EF         # Ket thuc ham
--- Ket thuc Function
--- Ham main
37:  INT 6      # luu 4 cai RV, DL, RA, SL va dia chi n, sum
38:  LA 0,4     # lay dia chi cua n
39:  RI         # read integer
40:  ST         # store
41:  LA 0,5     # Lay dia chi cua sum
42:  INT 4      # Cong 4 cai RV, DL, RA, SL cho function
43:  LV 0,4     # Load value n
44:  DCT 5      # t = t - 5 
45:  CALL 0,1   # goi den function
46:  ST         # luu gia tri tra ve tu function
47:  LV 0,5     # load value sum
48:  WRI        # call write in ra man hinh
49:  HL         # Ket thuc
--- Ket thuc main
```


---
program test;
begin 
end.


0:  J 1     # Jump toi lenh 1
1:  INT 4   # Tang gia tri t len 4: de luu RV, DL, RA, SL 
2:  HL      # Ket thuc
---

program test;
var n : integer;
    sum : integer;
begin 
end.

0:  J 1
1:  INT 6   # 4 cai de luu RV, DL, RA, SL va them 2 de luu bien n va sum
2:  HL
---
program test;
var n : integer;
    sum : integer;
begin 
    n := readi;
end.


0:  J 1
1:  INT 6
2:  LA 0,4  # load dia chi cua bien n luu vao s[6]
3:  RI      # read integer luu vao s[4]
4:  ST      # store
5:  HL
---
program test;
var n : integer;
    sum : integer;
Function Fibonaci(n : integer) : Integer;
Begin
End;
begin 
    n := readi;
end.
0:  J 4
1:  J 2
2:  INT 5       # luu 4 cai + bien n
3:  EF          # exit function
4:  INT 6
5:  LA 0,4
6:  RI
7:  ST
8:  HL
---
program test;
var n : integer;
    sum : integer;
Function Fibonaci(n : integer) : Integer;
Begin
End;
begin 
    n := readi;
    sum := Fibonaci(n);
end.

0:  J 4
1:  J 2
2:  INT 5
3:  EF
4:  INT 6
5:  LA 0,4
6:  RI
7:  ST
8:  LA 0,5      # load den bien sum
9:  INT 4       # tang len 4 
10:  LV 0,4     # load value tu n
11:  DCT 5      # giam gia tri 
12:  CALL 0,1   # Goi vao trong ham call toi vi tri 1
13:  ST
14:  HL
---
program test;
var n : integer;
    sum : integer;
Function Fibonaci(n : integer) : Integer;
Begin
    if n = 0 then Fibonaci := 0;
End;

begin 
    n := readi;
    sum := Fibonaci(n);
end.
0:  J 11
1:  J 2

2:  INT 5
3:  LV 0,4      # load value n 
4:  LC 0        # load constant 
5:  EQ          # kiem tra equal
6:  FJ 10       # false jump 
7:  LA 0,0      # lay dia chi Fibonaci
8:  LC 0        # load constant
9:  ST          # luu lai 
10:  EF         # exit function

11:  INT 6
12:  LA 0,4
13:  RI
14:  ST
15:  LA 0,5
16:  INT 4
17:  LV 0,4
18:  DCT 5
19:  CALL 0,1
20:  ST
21:  HL
