<CsoundSynthesizer>

<CsOptions>
</CsOptions>

<CsInstruments>
  sr        =  44100
  nchnls    =  2
  0dbfs     =  1

    instr 1
  kAmp      =  0.6
  kFreq     =  p4
  iFn       =  p5
  iAtt      =  0.0001
  iDec      =  0.0999
  iSus      =  0.0
  iRel      =  0.9

  aSig      oscili    kAmp, kFreq, iFn
  kEnv      madsr     iAtt, iDec, iSus, iRel
            outs       aSig*kEnv, aSig*kEnv
    endin
</CsInstruments>

<CsScore>
  ; sine
  f 1        0  128 10 1
  ; square wave, odd harmonics
  f 2       0  512 10 1 0 .333 0 .2 0 .143 0 .111 0 .0909 0 .077 0 .0666 0 .0588
  ; sawtooth wave - all harmonics
  f 3      0  512 10 1 .5 .333 .25 .2 .166 .143 .125 .111 .1 .0909 .0833 .077
  ; triangle
  f 4 0 513 9 1 1 0 3 .333 180 5 .2 0 7 .143 180 9 .111 0

  i         1  0.5      1.0 1320 4
  i         .  1.0      1.5  880 4
  i         .  1.5      2.0  880 4
  i         .  2.0      2.5  880 4
  i         1  2.5      3.0 1320 2
  i         .  3.0      3.5  880 2
  i         .  3.5      4.0  880 2
  i         .  4.0      4.5  880 2
</CsScore>

</CsoundSynthesizer>

