10 CLEAR &HB000
20 drive=1:'ドライブ番号
30 MEM$(&HB000,16)=HEXCHR$("f3 01 f8 0f ed 78 e6 02 28 fa 21 00 b2 16 20 3e")
40 MEM$(&HB010,16)=HEXCHR$("c0 ed 79 3e 07 3d 20 fd ed 78 0f 30 0d 0f 30 f8")
50 MEM$(&HB020,16)=HEXCHR$("0e fb ed 78 77 23 0e f8 18 ee ed 78 77 23 7a fe")
60 MEM$(&HB030,16)=HEXCHR$("20 3a 02 b2 20 0e 5f 15 7d fe 01 20 d2 2b 36 ff")
70 MEM$(&HB040,16)=HEXCHR$("fb c9 18 cb e5 dd e1 dd be fb 20 06 dd 36 f9 ff")
80 MEM$(&HB050,16)=HEXCHR$("18 05 15 20 ba 36 ff 21 00 b2 11 00 b3 01 00 40")
90 MEM$(&HB060,16)=HEXCHR$("23 23 7e d9 01 fa 0f ed 79 0e f8 3e 80 ed 79 3e")
100 MEM$(&HB070,16)=HEXCHR$("07 3d 20 fd ed 78 0f 30 10 0f 30 f8 0e fb ed 78")
110 MEM$(&HB080,16)=HEXCHR$("d9 ed 79 03 d9 0e f8 18 eb ed 78 d9 eb 71 23 70")
120 MEM$(&HB090,16)=HEXCHR$("23 77 23 eb 23 23 23 23 23 7e fe ff 20 c2 60 69")
130 MEM$(&HB0A0,5)=HEXCHR$("22 80 b3 fb c9")
140 MEM$(&HB100,16)=HEXCHR$("18 02 18 54 21 00 b2 11 00 b4 01 1c 00 cd 26 b1")
150 MEM$(&HB110,16)=HEXCHR$("21 00 b3 01 0c 00 cd 26 b1 21 80 b3 7e b7 28 03")
160 MEM$(&HB120,16)=HEXCHR$("23 34 2b 36 40 c9 d9 01 00 08 1e 00 cb 21 d9 7e")
170 MEM$(&HB130,16)=HEXCHR$("23 d9 fe 80 38 02 cb c1 57 cd b4 b1 7a 83 5f 10")
180 MEM$(&HB140,16)=HEXCHR$("eb 79 cd b4 b1 7b cb 27 cb 79 28 02 f6 01 cd b4")
190 MEM$(&HB150,16)=HEXCHR$("b1 d9 0b 78 b1 20 cf c9 21 80 b3 46 0e 00 23 7e")
200 MEM$(&HB160,16)=HEXCHR$("90 fe 30 38 05 21 00 06 18 0c 67 af cb 3c 1f cb")
210 MEM$(&HB170,16)=HEXCHR$("3c 1f cb 3c 1f 6f 11 00 b4 d9 01 00 08 1e 00 cb")
220 MEM$(&HB180,16)=HEXCHR$("21 d9 ed 78 03 d9 fe 80 38 02 cb c1 57 cd b4 b1")
230 MEM$(&HB190,16)=HEXCHR$("7a 83 5f 10 ea 79 cd b4 b1 7b cb 27 cb 79 28 02")
240 MEM$(&HB1A0,16)=HEXCHR$("f6 01 cd b4 b1 d9 2b 7c b5 20 ce ed 53 82 b3 78")
250 MEM$(&HB1B0,16)=HEXCHR$("32 80 b3 c9 e6 7f c6 20 fe 7f 38 02 c6 32 d9 12")
260 MEM$(&HB1C0,3)=HEXCHR$("13 d9 c9")
270 A=INP(&HFFF):A=INP(&HFFD)
280 OUT &HFFC,&H80 OR drive:GOSUB 550
290 OUT &HFF8,0:GOSUB 550
300 OPEN "C",#1,"COM:6N81R"
310 PRINT #1,"===X1:D88"
320 PRINT #1,"WRITE PROTECT:";
330 IF INP(&HFF8) AND &H40 THEN PRINT #1,"ON" ELSE PRINT #1,"OFF"
340 FOR tr=0 TO 40:PRINT TR;:FOR si=0 TO 1
350 OUT &HFFC,&H80 OR drive OR &H10*si:GOSUB 550
360 OUT &HFF9,tr:OUT &HFFB,tr:OUT &HFF8,&H1C:GOSUB 550
370 CALL &HB000
380 OUT &HFFC,drive
390 IF PEEK(&HB200)=&HFF THEN 470
400 PRINT #1,"==TRACK,SIDE:";tr;",";si
410 CALL &HB100:sz=PEEK(&HB381)
420 FOR i=&HB400 TO &HB58F STEP 50:PRINT #1,MEM$(i,50):NEXT
430 IF sz=&H40 THEN 470
440 CALL &HB102:last=PEEK(&HB382)+PEEK(&HB383)*256-1
450 FOR i=46080! TO last STEP 64:PRINT #1,MEM$(i,64):NEXT
460 IF sz<>PEEK(&HB380) THEN 440
470 NEXT
480 IF tr=40 THEN 520
490 OUT &HFFC,&H80 OR drive:GOSUB 550
500 OUT &HFF8,&H58:GOSUB 550
510 OUT &HFFC,drive
520 NEXT
530 PRINT #1,"===END":PRINT:PRINT "END"
540 END
550 count=0
560 IF (INP(&HFF8) AND &H81) = 0 THEN RETURN
570 count=count+1:IF count < 1000 THEN 560
580 PRINT"Err":OUT &HFFC,drive:STOP
