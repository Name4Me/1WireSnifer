'****************************************************************
'*  Name    : Tiny_DS2450.BAS                                   *
'*  Author  : Vladimir I. Yershov                               *
'*                                                              *
'*  Date    : 21.12.2008                                        *
'*  Version : 1.0                                               *
'*  Notes   : Firmware for Tiny and Mega AVR to emulate Dallas  *
'*            DS2450 1-Wire Quad A/D Converter                  *
'*          :                                                   *
'****************************************************************
    '$regfile = "attiny45.dat" : Const Chip = 45         ' Choose chip for compilation by uncomment line
$regfile = "m32def.dat" : Const Chip = 32

$crystal = 8000000

#if Chip = 45
$loadersize = 512                                           ' bootloader space reservation
Config Clockdiv = 1
#endif

' HW Config
$hwstack = 32
$swstack = 8
$framesize = 16
Config Adc = Single , Prescaler = Auto
Config Timer0 = Timer , Prescale = 64

Const Dqpin = 1
Const Ipin = 0                                              ' value in DDRB for input
Const Opin = 1                                              ' value in DDRB for output

Timer Alias Tcnt0

Dq Alias Pinb.dqpin

' Commands
Const Search_rom = &HF0
Const Skip_rom = &HCC
Const Match_rom = &H55
Const Read_rom = &H33
Const Writemem = &H55
Const Convert = &H3C
Const Read_mem = &HAA
Const Bootload = &HEE
Const Write_epr = &HE0

' Timings

Const Owpresent = 150                                       '  60us < OWPresent < 240us
Const Owpause = 50                                          '  15us < OWPause   < 60us
Const Owstrobe = 15                                         '  read Dq value after Owstrobe us                                          '12                  '10 4MHz      12 8 MHz
Const Owdata = 25                                           '  Valid output data for Owdata us                                         '20 '15                                           '12                  '7            12

' Timer Delays

Const T1reset = 60                                          'T1us * 490 Min Reset width
Const Timeout = 120                                         'T1us * 970 Max Reset width

' Allocate variables

Dim I As Byte
Dim B As Byte
Dim Inmask As Byte
Dim Readout As Byte
Dim Addrlo As Byte
Dim Adcnum As Byte

Dim Myrom(8) As Byte

Dim Crc16_hi As Byte
Dim Crc16_lo As Byte

Dim Ram(32) As Byte
Dim Ramw(16) As Word At Ram() Overlay
Dim Ad_result As Word
Dim Bytedat As Byte
Dim Wreg As Byte

Dim Tstval As Byte
Dim Temp As Byte
Dim Templ As Byte
Dim Temph As Byte
Dim Tempw As Word At Templ Overlay

Dim Overresol As Byte
Dim Oversample As Byte
Dim Overcount As Byte
Dim Overshift As Byte
Dim Normshift As Byte

Dim Bitdat As Bit

         Enable Interrupts
         Enable Timer0
         On Timer0 Isr Nosave

         Restore Myrom
         For Addrlo = 1 To 8
         Read B
         Myrom(addrlo) = B
         Next Addrlo

         Stop Timer0

#if Chip = 45
         Admux = &B00100000
         Adcsra = &B00000110
         Adcsrb = &B00000000
'         Didr0 = &B00111101
         Didr0 = &B00111100
#endif
         Open "comb.0:57600,8,n,1" For Output As #1
         Print #1 , "T45.3 18.11.07"                        ' version info

         Waitms 500
'-----------------------------------

Mainloop:
Waitreset:

    Disable Interrupts
    Timer = 0

Waitfall:

L1:
    sbis pinb, DqPin
    rjmp L1
L2:
    sbic pinb, DqPin
    rjmp L2

    Start Timer0

Rwaitrise:

L01:
    sbic pinb, DqPin
    rjmp L01
L02:
    sbis pinb, DqPin
    rjmp L02

    Stop Timer0

    If Timer < T1reset Then Goto Waitreset
    If Timer > Timeout Then Goto Waitreset


Sendpresense:
    Waitus Owpause

    Ddrb.dqpin = Opin

    Waitus Owpresent
    Ddrb.dqpin = Ipin
    Timer = 0
    Enable Interrupts

Readb:

    Gosub Readbyte
Readb1:

    If Bytedat = Read_rom Then Goto Readrom
    If Bytedat = Search_rom Then Goto Sendrom
    If Bytedat = Skip_rom Then Goto Funct
    If Bytedat = Match_rom Then Goto Matchrom
   Goto Readb
End



Isr:
    Spl = &H5F
    Sph = 1

    If Dq = 0 Then
    Timer = T1reset

    Goto Rwaitrise
    Else
    Goto Waitreset
    End If

Return
'-------------------------------
Readrom:
       For B = 1 To 8
       Bytedat = Myrom(b)
       Gosub Sendbyte
       Next B
Goto Readb
'----------------------------------
Matchrom:
        For B = 1 To 8
        Gosub Readbyte
        If Bytedat <> Myrom(b) Then Goto Mainloop
        Next B
Funct:
        Gosub Readbyte

        If Bytedat = Convert Then Goto Conversion

        If Bytedat = Read_mem Then Goto Readmem

        If Bytedat = Writemem Then Goto Write_mem

        If Bytedat = Bootload Then Goto Fwupgrade

        '    If Bytedat = Write_epr Then Goto Writeepr

Goto Readb1
'----------------------------------------
Fwupgrade:
        Gosub Sendbyte
        jmp 0

Readmem:
        Crc16_lo = 0
        Crc16_hi = 0
        B = 0

        Gosub Crc_update                                    ' ByteDat = ReadMem

        Gosub Readbyte
        Addrlo = Bytedat
        Gosub Crc_update                                    ' ByteDat = AddrLo

        Gosub Readbyte
        Gosub Crc_update                                    ' ByteDat = AddrHi
Readloop:
        Bytedat = Ram(addrlo + 1)

        Gosub Sendbyte
        Gosub Crc_update

        Incr Addrlo
        Incr B

        If B = 8 Then Goto Exitreadmem
        Goto Readloop
Exitreadmem:
        B = 0

        Bytedat = Crc16_lo Xor &HFF
        Gosub Sendbyte
        Bytedat = Crc16_hi Xor &HFF
        Gosub Sendbyte

        Crc16_lo = 0
        Crc16_hi = 0

        If Addrlo < 31 Then Goto Readloop

Goto Mainloop

'----------------------------------------
Write_mem:
        Crc16_lo = 0 : Crc16_hi = 0

        Gosub Crc_update                                    'Bytedat = Writemem

        Gosub Readbyte
        Addrlo = Bytedat
        Gosub Crc_update                                    ' AddrLo

        Gosub Readbyte
        Gosub Crc_update                                    ' AddrLo

        Gosub Readbyte
        Ram(addrlo + 1) = Bytedat
        Gosub Crc_update                                    ' MemByte

        Bytedat = Crc16_lo Xor &HFF
        Gosub Sendbyte

        Bytedat = Crc16_hi Xor &HFF
        Gosub Sendbyte

        Bytedat = Ram(addrlo + 1)
        Gosub Sendbyte
' ====== END OF FIRST PASS ===========
 Writememloop:
        Incr Addrlo
            Crc16_hi = 0
            Crc16_lo = Addrlo                               ' low (Crc16) = Addrlo

            Gosub Readbyte
            Ram(addrlo + 1) = Bytedat
            Gosub Crc_update

            Bytedat = Crc16_lo Xor &HFF
            Gosub Sendbyte

            Bytedat = Crc16_hi Xor &HFF
            Gosub Sendbyte

            Bytedat = Ram(addrlo + 1)
            Gosub Sendbyte

         If Addrlo < 31 Then Goto Writememloop

Goto Mainloop

' =============
Conversion:
        Crc16_lo = 0 : Crc16_hi = 0
        Gosub Crc_update                'ByteDat = Convert

        Gosub Readbyte                  'ByteDat = InMask
        Gosub Crc_update

        Gosub Readbyte                  'ByteDat = ReadOut
        Gosub Crc_update

        Bytedat = Crc16_lo Xor &HFF
        Gosub Sendbyte

        Bytedat = Crc16_hi Xor &HFF
        Gosub Sendbyte

        Overresol = 12                  ' Desired Oversample Resolution
        Overshift = Overresol - 10      ' Shift Left After Oversampling
        Normshift = 6 - Overshift
        Oversample = 4 ^ Overshift

#if Chip = 45
        Didr0 = &B00111100
        Adcsra = &B00000101             ' ADC clock = 250 kHz
        Adcsra.7 = 1                    ' Enable ADC
        Adcsrb = &B00000000

#endif
          For Adcnum = 1 To 4
             Ramw(adcnum) = 0
          Next Adcnum
#if Chip = 45
          For Overcount = 1 To Oversample
              Admux = &B00000000        ' Righ aligned result
              For Adcnum = 1 To 4
              Adcsra.6 = 1
              While Adcsra.6 = 1 : Wend
              Templ = Adcl : Temph = Adch
              Ramw(adcnum) = Ramw(adcnum) + Tempw
              Incr Admux
              Next Adcnum
          Next Overcount
#else
          Start Adc
          For Overcount = 1 To Oversample
              For Adcnum = 1 To 4
              B = Adcnum - 1
              Ad_result = Getadc(b)
              Ramw(adcnum) = Ramw(adcnum) + Ad_result
              Next Adcnum
          Next Overcount
#endif
         For Adcnum = 1 To 4
              Shift Ramw(adcnum) , Right , Overshift
              Shift Ramw(adcnum) , Left , Normshift
         Next Adcnum

Exit_case:
#if Chip = 45
        Adcsra.7 = 0                                        ' Disable ADC
#else
        Stop Adc
#endif
Goto Mainloop
'======================================================
Crc_update:

        Wreg = Bytedat
        Wreg = Wreg Xor Crc16_lo
        Temp = Wreg
        Wreg = Crc16_hi
        Crc16_lo = Wreg
        Wreg = 0

        If Temp.0 = 1 Then Wreg = &HCC

        If Temp.1 = 1 Then Wreg = Wreg Xor &H8D

        If Temp.2 = 1 Then Wreg = Wreg Xor &H0F

        If Temp.3 = 1 Then Wreg = Wreg Xor &H0A

        Crc16_hi = Wreg
        Wreg = Wreg And &HF0
        Crc16_hi = Crc16_hi Xor Wreg
        Crc16_lo = Crc16_lo Xor Wreg
        Wreg = 0

        If Crc16_hi.3 = 1 Then Wreg = &HCC

        If Temp.4 = 1 Then Wreg = Wreg Xor &HCC

        If Temp.5 = 1 Then Wreg = Wreg Xor &HD8

        If Temp.6 = 1 Then Wreg = Wreg Xor &HF0

        If Temp.7 = 1 Then Wreg = Wreg Xor &HA0

        Crc16_hi = Crc16_hi Xor Wreg
        Wreg = 1

        If Crc16_hi.7 = 1 Then Crc16_lo = Crc16_lo Xor Wreg

Return
'---------------------------------
'================================
Readbyte:
         For I = 0 To 7

L11:
    sbis pinb, DqPin
    rjmp L11
L12:
    sbic pinb, DqPin
    rjmp L12
         Timer = 256 - T1reset
         Start Timer0

         Rotate Bytedat , Right
         Waitus Owstrobe


         Bytedat.7 = Dq

         Next I
         Stop Timer0
Return
'----------------------------------
Sendbyte:
       Adcnum = Bytedat
        For I = 0 To 7

L21:
    sbis pinb, DqPin
    rjmp L21
L22:
    sbic pinb, DqPin
    rjmp L22
           Timer = 256 - T1reset
           Start Timer0

           If Bytedat.0 = 0 Then Ddrb.dqpin = Opin
           Waitus Owdata
           Ddrb.dqpin = Ipin

           Rotate Bytedat , Right

        Next I
        Bytedat = Adcnum
        Stop Timer0
Return
'-----------------------------------
Sendrom:
'    Stop Timer0
    For I = 1 To 8
          Bytedat = Myrom(i)
      For B = 0 To 7
'----------------------------
Sendcbit1:

L31:
    sbis pinb, DqPin
    rjmp L31
L32:
    sbic pinb, DqPin
    rjmp L32

           If Bytedat.0 = 0 Then Ddrb.dqpin = Opin
           Waitus Owdata
           Ddrb.dqpin = Ipin
'----------------------------
Sendcbit2:

L41:
    sbis pinb, DqPin
    rjmp L41
L42:
    sbic pinb, DqPin
    rjmp L42

           If Bytedat.0 = 1 Then Ddrb.dqpin = Opin          
           Waitus Owdata
           Ddrb.dqpin = Ipin

'--------------------------
Readcbit:

L51:
    sbis pinb, DqPin
    rjmp L51
L52:
    sbic pinb, DqPin
    rjmp L52

           Waitus Owstrobe

           Bitdat = Dq

'-------------------------
             If Bitdat <> Bytedat.0 Then Goto Mainloop
             Rotate Bytedat , Right
      Next B
    Next I

Goto Readb
End


Myrom:
'Data &H20 , &H0D , &HCB , &H0A , 00 , 00 , 00 , &HEC
'Data &H81 , &H55 , &H22 , &H24 , 00 , 00 , 00 , &H6A
'Data &H20 , &HAC , &HC7 , &H0A , 00 , 00 , 00 , &HA6

'Data &H20 , &HA5 , &HC1 , &H0A , 00 , 00 , 00 , &HAC
Data &H81 , &H55 , &H22 , &H24 , 00 , 00 , 00 , &H6A
