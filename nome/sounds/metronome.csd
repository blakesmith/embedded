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
  f1        0  128 10 1

  i         1  0.5      1.0 1320 1
  i         .  1.0      1.5  880 1
  i         .  1.5      2.0  880 1
  i         .  2.0      2.5  880 1
</CsScore>

</CsoundSynthesizer>

