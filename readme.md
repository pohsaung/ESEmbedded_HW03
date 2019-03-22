###HW3 廖柏翔

===

## 1. 實驗題目 

觀察C語之參數傳遞與計算

## 2. 實驗步驟: 

#第一部份:先說明加法順序

1. 先將資料夾 gnu-mcu-eclipse-qemu 完整複製到 ESEmbedded_HW03 資料夾中



2. 根據題目要求設計程式，觀察暫存器的執行狀況



3. 設計測試程式` main.c `，總共宣告6個變數並給予初值，最終進行相加。


main.c:

```主程式

void mymain(void)

{

  int num1=1;

  int num2=2;

  int num3=3;

  int num4=4;

  int num5=5;

  int num6=6;

  num6=num5+num1+num3+num4+num2;

  while (1)

    ;

}

```



5. 將 main.c 編譯， 開啟另一 Terminal 連線 `$ arm-none-eabi-gdb` ，再輸入 `target remote localhost:1234` 連接，輸入 `layout regs`, 開啟 Register 以及指令，並且輸入 `si` 一步步執行觀察。(也可由objdump出來的結果)





當執行`int num6=6;`可以看出初值分別被堆放在記憶體某處([R7]處)



![](https://github.com/pohsaung/ESEmbedded_HW03/blob/master/n62.jpg)



接著至位址較大處依序將值取出至R2、R3，相加後再存入R2，如此不斷重複



![](https://github.com/pohsaung/ESEmbedded_HW02/blob/master/n6is15.jpg)



由上可得知連續加法的順序跟記憶體位置無關!!



#第二部分:說明子函式中的參數傳遞

1. 設計:
先將初值存入變數中，再傳入子程式中看參數傳遞情行

2. 主程式
除宣告並給定參數，並設計一個子函式ˋsunf()ˋ進行觀察。主要觀察有:[1]參數如何被傳入[2]參數如何被傳出的'return c'。

```
int sumf();
int mymain(void) {
  int a1=1;
  int a2=2;
  int a3=3;
  int a4=4;
  int a5=5;
  int a6=6;
  int su;
  su = sumf(a1,a2,a3,a4,a5,a6);
  while(1);
}
int sumf(int b1,int b2,int b3,int b4,int b5,int b6)
{
  int c = b1+b3+b5+b2+b4+b6;
  return c;
}

```

3. objump檔

```
00000010 <mymain>:
  10: b580        push  {r7, lr}
  12: b08a        sub sp, #40 ; 0x28
  14: af02        add r7, sp, #8
  16: 2301        movs  r3, #1
  18: 61fb        str r3, [r7, #28]
  1a: 2302        movs  r3, #2
  1c: 61bb        str r3, [r7, #24]
  1e: 2303        movs  r3, #3
  20: 617b        str r3, [r7, #20]
  22: 2304        movs  r3, #4
  24: 613b        str r3, [r7, #16]
  26: 2305        movs  r3, #5
  28: 60fb        str r3, [r7, #12]
  2a: 2306        movs  r3, #6
  2c: 60bb        str r3, [r7, #8]
  2e: 68fb        ldr r3, [r7, #12]
  30: 9300        str r3, [sp, #0]
  32: 68bb        ldr r3, [r7, #8]
  34: 9301        str r3, [sp, #4]
  36: 69f8        ldr r0, [r7, #28]
  38: 69b9        ldr r1, [r7, #24]
  3a: 697a        ldr r2, [r7, #20]
  3c: 693b        ldr r3, [r7, #16]
  3e: f000 f803   bl  48 <sumf>
  42: 6078        str r0, [r7, #4]
  44: e7fe        b.n 44 <mymain+0x34>
  46: bf00        nop

00000048 <sumf>:
  48: b480        push  {r7}
  4a: b087        sub sp, #28
  4c: af00        add r7, sp, #0
  4e: 60f8        str r0, [r7, #12]
  50: 60b9        str r1, [r7, #8]
  52: 607a        str r2, [r7, #4]
  54: 603b        str r3, [r7, #0]
  56: 68fa        ldr r2, [r7, #12]
  58: 687b        ldr r3, [r7, #4]
  5a: 441a        add r2, r3
  5c: 6a3b        ldr r3, [r7, #32]
  5e: 441a        add r2, r3
  60: 68bb        ldr r3, [r7, #8]
  62: 441a        add r2, r3
  64: 683b        ldr r3, [r7, #0]
  66: 441a        add r2, r3
  68: 6a7b        ldr r3, [r7, #36] ; 0x24
  6a: 4413        add r3, r2
  6c: 617b        str r3, [r7, #20]
  6e: 697b        ldr r3, [r7, #20]
  70: 4618        mov r0, r3
  72: 371c        adds  r7, #28
  74: 46bd        mov sp, r7
  76: f85d 7b04   ldr.w r7, [sp], #4
  7a: 4770        bx  lr




```
4. 
由上觀察，可將其拆成三個部分:
  (a) 將參數存入記憶體中
  (b) 將各參數取出並呼叫函式
![](https://github.com/pohsaung/ESEmbedded_HW03/blob/master/partab.jpg)
  (c) 進入涵式中，以堆疊存取
![](https://github.com/pohsaung/ESEmbedded_HW03/blob/master/partc.jpg)
則由上可知子程式結束後便在主程式中被存入記憶體中。


## 3. 結果與討論

 1. 初值的存入順序由位址高至低進行堆疊

 2. 取出相加時由先敘述的先進行加法





