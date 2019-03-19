###HW3 廖柏翔
===
## 1. 實驗題目 
撰寫簡易組合語言觀察C語之參數傳遞與計算
## 2. 實驗步驟
1. 先將資料夾 gnu-mcu-eclipse-qemu 完整複製到 ESEmbedded_HW03 資料夾中

2. 根據題目要求設計程式，觀察暫存器的執行狀況

3. 設計測試程式` main.c `，總共宣告6個變數並給予初值，最終進行相加




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

## 3. 結果與討論
 1. 初值的存入順序由位址高至低進行堆疊

 2. 取出相加時由先敘述的先進行加法

![](https://github.com/pohsaung/ESEmbedded_HW02/blob/master/sumorder.jpg)




```
arm-none-eabi-objcopy -O binary main.elf main.bin
arm-none-eabi-objdump -D main.elf

main.elf:     file format elf32-littlearm


Disassembly of section .mytext:

00000000 <mymain-0x8>:
   0: 20000100  andcs r0, r0, r0, lsl #2
   4: 00000009  andeq r0, r0, r9

00000008 <mymain>:
   8: b480        push  {r7}
   a: b087        sub sp, #28
   c: af00        add r7, sp, #0
   e: 2301        movs  r3, #1
  10: 617b        str r3, [r7, #20]
  12: 2302        movs  r3, #2
  14: 613b        str r3, [r7, #16]
  16: 2303        movs  r3, #3
  18: 60fb        str r3, [r7, #12]
  1a: 2304        movs  r3, #4
  1c: 60bb        str r3, [r7, #8]
  1e: 2305        movs  r3, #5
  20: 607b        str r3, [r7, #4]
  22: 2306        movs  r3, #6
  24: 603b        str r3, [r7, #0]
  26: 697a        ldr r2, [r7, #20]
  28: 693b        ldr r3, [r7, #16]
  2a: 441a        add r2, r3
  2c: 68fb        ldr r3, [r7, #12]
  2e: 441a        add r2, r3
  30: 68bb        ldr r3, [r7, #8]
  32: 441a        add r2, r3
  34: 687b        ldr r3, [r7, #4]
  36: 4413        add r3, r2
  38: 603b        str r3, [r7, #0]
  3a: e7fe        b.n 3a <mymain+0x32>

Disassembly of section .comment:

00000000 <.comment>:
   0: 3a434347  bcc 10d0d24 <mymain+0x10d0d1c>
   4: 35312820  ldrcc r2, [r1, #-2080]! ; 0xfffff7e0
   8: 392e343a  stmdbcc lr!, {r1, r3, r4, r5, sl, ip, sp}
   c: 732b332e      ; <UNDEFINED> instruction: 0x732b332e
  10: 33326e76  teqcc r2, #1888 ; 0x760
  14: 37373131      ; <UNDEFINED> instruction: 0x37373131
  18: 2029312d  eorcs r3, r9, sp, lsr #2
  1c: 2e392e34  mrccs 14, 1, r2, cr9, cr4, {1}
  20: 30322033  eorscc  r2, r2, r3, lsr r0
  24: 35303531  ldrcc r3, [r0, #-1329]! ; 0xfffffacf
  28: 28203932  stmdacs r0!, {r1, r4, r5, r8, fp, ip, sp}
  2c: 72657270  rsbvc r7, r5, #112, 4
  30: 61656c65  cmnvs r5, r5, ror #24
  34: 00296573  eoreq r6, r9, r3, ror r5

Disassembly of section .ARM.attributes:

00000000 <.ARM.attributes>:
   0: 00003041  andeq r3, r0, r1, asr #32
   4: 61656100  cmnvs r5, r0, lsl #2
   8: 01006962  tsteq r0, r2, ror #18
   c: 00000026  andeq r0, r0, r6, lsr #32
  10: 726f4305  rsbvc r4, pc, #335544320  ; 0x14000000
  14: 2d786574  cfldr64cs mvdx6, [r8, #-464]! ; 0xfffffe30
  18: 0600344d  streq r3, [r0], -sp, asr #8
  1c: 094d070d  stmdbeq sp, {r0, r2, r3, r8, r9, sl}^
  20: 14041202  strne r1, [r4], #-514 ; 0xfffffdfe
  24: 17011501  strne r1, [r1, -r1, lsl #10]
  28: 1a011803  bne 4603c <mymain+0x46034>
  2c: 22061e01  andcs r1, r6, #1, 28
  30: Address 0x0000000000000030 is out of bounds.

```


