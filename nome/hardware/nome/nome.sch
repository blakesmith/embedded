EESchema Schematic File Version 4
LIBS:nome-cache
EELAYER 26 0
EELAYER END
$Descr User 15748 13780
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Label 2600 9750 0    60   ~ 0
ENC_A
Text Label 2600 9650 0    60   ~ 0
GND
Text Label 2600 9550 0    60   ~ 0
ENC_B
Text Label 2400 4600 2    60   ~ 0
ENC_A
Text Label 2400 4700 2    60   ~ 0
ENC_B
Text Label 3200 5300 3    60   ~ 0
ENC_BUTTON
$Comp
L GND-RESCUE-nome #PWR01
U 1 1 59E41BEB
P 4150 11750
F 0 "#PWR01" H 4150 11500 50  0001 C CNN
F 1 "GND" H 4150 11600 50  0000 C CNN
F 2 "" H 4150 11750 50  0001 C CNN
F 3 "" H 4150 11750 50  0001 C CNN
	1    4150 11750
	1    0    0    -1  
$EndComp
$Comp
L CS43L22-RESCUE-nome U6
U 1 1 59E6BCC3
P 9850 3700
F 0 "U6" H 9150 3100 60  0000 C CNN
F 1 "CS43L22" H 9850 3700 60  0000 C CNN
F 2 "Housings_DFN_QFN:QFN-40-1EP_6x6mm_Pitch0.5mm" H 9900 3650 60  0001 C CNN
F 3 "https://d3uzseaevmutz1.cloudfront.net/pubs/proDatasheet/CS43L22_F2.pdf" H 9900 3650 60  0001 C CNN
F 4 "598-1650-ND" H 9850 3700 60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/cirrus-logic-inc/CS43L22-CNZ/598-1650-ND/2024884" H 9850 3700 60  0001 C CNN "S1PL"
F 6 "Cirrus Logic Inc." H 9850 3700 60  0001 C CNN "MFN"
F 7 "CS43L22-CNZ" H 9850 3700 60  0001 C CNN "MFP"
	1    9850 3700
	1    0    0    -1  
$EndComp
Text Label 4000 5300 3    60   ~ 0
DAC_MCK
Text Label 9700 2650 1    60   ~ 0
DAC_MCK
Text Label 4950 4700 0    60   ~ 0
DAC_CK
Text Label 9600 2650 1    60   ~ 0
DAC_CK
Text Label 3900 2950 1    60   ~ 0
DAC_SD
Text Label 9500 2650 1    60   ~ 0
DAC_SD
Text Label 3300 5300 3    60   ~ 0
DAC_WS
Text Label 9400 2650 1    60   ~ 0
DAC_WS
$Comp
L GND-RESCUE-nome #PWR02
U 1 1 59E78773
P 4700 5900
F 0 "#PWR02" H 4700 5650 50  0001 C CNN
F 1 "GND" H 4700 5750 50  0000 C CNN
F 2 "" H 4700 5900 50  0001 C CNN
F 3 "" H 4700 5900 50  0001 C CNN
	1    4700 5900
	1    0    0    -1  
$EndComp
Text Label 4700 5900 0    60   ~ 0
GND
$Comp
L C-RESCUE-nome C6
U 1 1 59E787C7
P 4700 5500
F 0 "C6" H 4725 5600 50  0000 L CNN
F 1 "0.1uF" H 4725 5400 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 4738 5350 50  0001 C CNN
F 3 "http://datasheets.avx.com/X7RDielectric.pdf" H 4700 5500 50  0001 C CNN
F 4 "478-1395-1-ND" H 0   0   60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/avx-corporation/08055C104KAT2A/478-1395-1-ND/564427" H 0   0   60  0001 C CNN "S1PL"
F 6 "AVX Corporation" H 0   0   60  0001 C CNN "MFN"
F 7 "08055C104KAT2A" H 0   0   60  0001 C CNN "MFP"
	1    4700 5500
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-nome #PWR03
U 1 1 59E789AE
P 5500 4250
F 0 "#PWR03" H 5500 4000 50  0001 C CNN
F 1 "GND" H 5500 4100 50  0000 C CNN
F 2 "" H 5500 4250 50  0001 C CNN
F 3 "" H 5500 4250 50  0001 C CNN
	1    5500 4250
	1    0    0    -1  
$EndComp
Text Label 5500 4250 0    60   ~ 0
GND
$Comp
L STMF411CEU6-RESCUE-nome U4
U 1 1 59E41970
P 3750 4150
F 0 "U4" H 3700 4150 60  0000 C CNN
F 1 "STM32F413CGU6" H 3750 4000 60  0000 C CNN
F 2 "Housings_QFP:LQFP-48_7x7mm_Pitch0.5mm" H 3700 4150 60  0001 C CNN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/group3/f6/1d/4a/d9/f9/96/43/2a/DM00282249/files/DM00282249.pdf/jcr:content/translations/en.DM00282249.pdf" H 3700 4150 60  0001 C CNN
F 4 "497-17017-ND" H 3750 4150 60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/stmicroelectronics/STM32F413CGU6/497-17017-ND/6564709" H 3750 4150 60  0001 C CNN "S1PL"
F 6 "STMicroelectronics" H 3750 4150 60  0001 C CNN "MFN"
F 7 "STM32F413CGU6" H 3750 4150 60  0001 C CNN "MFP"
	1    3750 4150
	1    0    0    -1  
$EndComp
$Comp
L C-RESCUE-nome C5
U 1 1 59E78528
P 4000 1550
F 0 "C5" H 4025 1650 50  0000 L CNN
F 1 "4.7uF" H 4025 1450 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 4038 1400 50  0001 C CNN
F 3 "http://datasheets.avx.com/cx5r.pdf" H 4000 1550 50  0001 C CNN
F 4 "478-1415-1-ND" H 0   0   60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/avx-corporation/0805ZD475KAT2A/478-1415-1-ND/564447" H 0   0   60  0001 C CNN "S1PL"
F 6 "AVX Corporation" H 0   0   60  0001 C CNN "MFN"
F 7 "0805ZD475KAT2A" H 0   0   60  0001 C CNN "MFP"
	1    4000 1550
	1    0    0    -1  
$EndComp
Text Label 4000 1950 0    60   ~ 0
GND
$Comp
L GND-RESCUE-nome #PWR04
U 1 1 59E785A7
P 4000 1950
F 0 "#PWR04" H 4000 1700 50  0001 C CNN
F 1 "GND" H 4000 1800 50  0000 C CNN
F 2 "" H 4000 1950 50  0001 C CNN
F 3 "" H 4000 1950 50  0001 C CNN
	1    4000 1950
	1    0    0    -1  
$EndComp
$Comp
L C-RESCUE-nome C4
U 1 1 59E77FCD
P 3650 1550
F 0 "C4" H 3675 1650 50  0000 L CNN
F 1 "0.1uF" H 3675 1450 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 3688 1400 50  0001 C CNN
F 3 "http://datasheets.avx.com/X7RDielectric.pdf" H 3650 1550 50  0001 C CNN
F 4 "478-1395-1-ND" H 0   0   60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/avx-corporation/08055C104KAT2A/478-1395-1-ND/564427" H 0   0   60  0001 C CNN "S1PL"
F 6 "AVX Corporation" H 0   0   60  0001 C CNN "MFN"
F 7 "08055C104KAT2A" H 0   0   60  0001 C CNN "MFP"
	1    3650 1550
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-nome #PWR05
U 1 1 59E79752
P 2050 3650
F 0 "#PWR05" H 2050 3400 50  0001 C CNN
F 1 "GND" H 2050 3500 50  0000 C CNN
F 2 "" H 2050 3650 50  0001 C CNN
F 3 "" H 2050 3650 50  0001 C CNN
	1    2050 3650
	1    0    0    -1  
$EndComp
$Comp
L C-RESCUE-nome C3
U 1 1 59E79936
P 2050 3050
F 0 "C3" H 2075 3150 50  0000 L CNN
F 1 "1uF" H 2075 2950 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 2088 2900 50  0001 C CNN
F 3 "http://datasheets.avx.com/X7RDielectric.pdf" H 2050 3050 50  0001 C CNN
F 4 "478-1405-1-ND" H 0   0   60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/avx-corporation/0805ZC105KAT2A/478-1405-1-ND/564437" H 0   0   60  0001 C CNN "S1PL"
F 6 "AVX Corporation" H 0   0   60  0001 C CNN "MFN"
F 7 "0805ZC105KAT2A" H 0   0   60  0001 C CNN "MFP"
	1    2050 3050
	1    0    0    -1  
$EndComp
$Comp
L C-RESCUE-nome C2
U 1 1 59E7995F
P 1750 3050
F 0 "C2" H 1775 3150 50  0000 L CNN
F 1 "0.1uF" H 1775 2950 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 1788 2900 50  0001 C CNN
F 3 "http://datasheets.avx.com/X7RDielectric.pdf" H 1750 3050 50  0001 C CNN
F 4 "478-1395-1-ND" H 0   0   60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/avx-corporation/08055C104KAT2A/478-1395-1-ND/564427" H 0   0   60  0001 C CNN "S1PL"
F 6 "AVX Corporation" H 0   0   60  0001 C CNN "MFN"
F 7 "08055C104KAT2A" H 0   0   60  0001 C CNN "MFP"
	1    1750 3050
	1    0    0    -1  
$EndComp
Text Label 4150 11700 0    60   ~ 0
GND
$Comp
L Rotary_Encoder_Switch-RESCUE-nome SW2
U 1 1 59E7A30B
P 2200 9650
F 0 "SW2" H 2200 9910 50  0000 C CNN
F 1 "Rotary_Encoder_Switch" H 2200 9390 50  0000 C CNN
F 2 "nome:PEC11" H 2100 9810 50  0001 C CNN
F 3 "http://www.bourns.com/docs/Product-Datasheets/PEC11R.pdf" H 2200 9910 50  0001 C CNN
F 4 "PEC11R-4215K-S0024-ND" H 2200 9650 60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/bourns-inc/PEC11R-4215K-S0024/PEC11R-4215K-S0024-ND/4499662" H 2200 9650 60  0001 C CNN "S1PL"
F 6 "Bourns Inc." H 2200 9650 60  0001 C CNN "MFN"
F 7 "PEC11R-4215K-S0024" H 2200 9650 60  0001 C CNN "MFP"
	1    2200 9650
	-1   0    0    1   
$EndComp
Text Label 1600 9550 2    60   ~ 0
ENC_BUTTON
$Comp
L GND-RESCUE-nome #PWR06
U 1 1 59E7A59F
P 1600 9750
F 0 "#PWR06" H 1600 9500 50  0001 C CNN
F 1 "GND" H 1600 9600 50  0000 C CNN
F 2 "" H 1600 9750 50  0001 C CNN
F 3 "" H 1600 9750 50  0001 C CNN
	1    1600 9750
	1    0    0    -1  
$EndComp
Text Label 1700 9750 0    60   ~ 0
GND
$Comp
L GND-RESCUE-nome #PWR07
U 1 1 59E7A91F
P 3050 9650
F 0 "#PWR07" H 3050 9400 50  0001 C CNN
F 1 "GND" H 3050 9500 50  0000 C CNN
F 2 "" H 3050 9650 50  0001 C CNN
F 3 "" H 3050 9650 50  0001 C CNN
	1    3050 9650
	1    0    0    -1  
$EndComp
$Comp
L C-RESCUE-nome C15
U 1 1 59E7B0EB
P 9050 4950
F 0 "C15" H 9075 5050 50  0000 L CNN
F 1 "1uF" H 9075 4850 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 9088 4800 50  0001 C CNN
F 3 "http://datasheets.avx.com/X7RDielectric.pdf" H 9050 4950 50  0001 C CNN
F 4 "478-1405-1-ND" H 0   0   60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/avx-corporation/0805ZC105KAT2A/478-1405-1-ND/564437" H 0   0   60  0001 C CNN "S1PL"
F 6 "AVX Corporation" H 0   0   60  0001 C CNN "MFN"
F 7 "0805ZC105KAT2A" H 0   0   60  0001 C CNN "MFP"
	1    9050 4950
	1    0    0    -1  
$EndComp
$Comp
L C-RESCUE-nome C13
U 1 1 59E7B30C
P 8150 4500
F 0 "C13" H 8175 4600 50  0000 L CNN
F 1 "1uF" H 8175 4400 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 8188 4350 50  0001 C CNN
F 3 "http://datasheets.avx.com/X7RDielectric.pdf" H 8150 4500 50  0001 C CNN
F 4 "478-1405-1-ND" H 0   0   60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/avx-corporation/0805ZC105KAT2A/478-1405-1-ND/564437" H 0   0   60  0001 C CNN "S1PL"
F 6 "AVX Corporation" H 0   0   60  0001 C CNN "MFN"
F 7 "0805ZC105KAT2A" H 0   0   60  0001 C CNN "MFP"
	1    8150 4500
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-nome #PWR08
U 1 1 59E7B33F
P 8150 4800
F 0 "#PWR08" H 8150 4550 50  0001 C CNN
F 1 "GND" H 8150 4650 50  0000 C CNN
F 2 "" H 8150 4800 50  0001 C CNN
F 3 "" H 8150 4800 50  0001 C CNN
	1    8150 4800
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-nome #PWR09
U 1 1 59E7B49E
P 10100 1300
F 0 "#PWR09" H 10100 1050 50  0001 C CNN
F 1 "GND" H 10100 1150 50  0000 C CNN
F 2 "" H 10100 1300 50  0001 C CNN
F 3 "" H 10100 1300 50  0001 C CNN
	1    10100 1300
	1    0    0    -1  
$EndComp
Text Label 10100 1200 0    60   ~ 0
GND
$Comp
L GND-RESCUE-nome #PWR010
U 1 1 59E7B719
P 10250 2250
F 0 "#PWR010" H 10250 2000 50  0001 C CNN
F 1 "GND" H 10250 2100 50  0000 C CNN
F 2 "" H 10250 2250 50  0001 C CNN
F 3 "" H 10250 2250 50  0001 C CNN
	1    10250 2250
	1    0    0    -1  
$EndComp
$Comp
L C-RESCUE-nome C19
U 1 1 59E7B806
P 10250 2000
F 0 "C19" H 10275 2100 50  0000 L CNN
F 1 "0.1uF" H 10275 1900 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 10288 1850 50  0001 C CNN
F 3 "http://datasheets.avx.com/X7RDielectric.pdf" H 10250 2000 50  0001 C CNN
F 4 "478-1395-1-ND" H 0   0   60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/avx-corporation/08055C104KAT2A/478-1395-1-ND/564427" H 0   0   60  0001 C CNN "S1PL"
F 6 "AVX Corporation" H 0   0   60  0001 C CNN "MFN"
F 7 "08055C104KAT2A" H 0   0   60  0001 C CNN "MFP"
	1    10250 2000
	1    0    0    -1  
$EndComp
Text Label 10250 2200 0    60   ~ 0
GND
$Comp
L C-RESCUE-nome C23
U 1 1 59E7BA94
P 11150 2700
F 0 "C23" H 11175 2800 50  0000 L CNN
F 1 "1uF" H 11175 2600 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 11188 2550 50  0001 C CNN
F 3 "http://datasheets.avx.com/X7RDielectric.pdf" H 11150 2700 50  0001 C CNN
F 4 "478-1405-1-ND" H 0   0   60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/avx-corporation/0805ZC105KAT2A/478-1405-1-ND/564437" H 0   0   60  0001 C CNN "S1PL"
F 6 "AVX Corporation" H 0   0   60  0001 C CNN "MFN"
F 7 "0805ZC105KAT2A" H 0   0   60  0001 C CNN "MFP"
	1    11150 2700
	1    0    0    -1  
$EndComp
$Comp
L C-RESCUE-nome C21
U 1 1 59E7BAC7
P 10700 2700
F 0 "C21" H 10725 2800 50  0000 L CNN
F 1 "0.1uF" H 10725 2600 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 10738 2550 50  0001 C CNN
F 3 "http://datasheets.avx.com/X7RDielectric.pdf" H 10700 2700 50  0001 C CNN
F 4 "478-1395-1-ND" H 0   0   60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/avx-corporation/08055C104KAT2A/478-1395-1-ND/564427" H 0   0   60  0001 C CNN "S1PL"
F 6 "AVX Corporation" H 0   0   60  0001 C CNN "MFN"
F 7 "08055C104KAT2A" H 0   0   60  0001 C CNN "MFP"
	1    10700 2700
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-nome #PWR011
U 1 1 59E7BC76
P 11150 3100
F 0 "#PWR011" H 11150 2850 50  0001 C CNN
F 1 "GND" H 11150 2950 50  0000 C CNN
F 2 "" H 11150 3100 50  0001 C CNN
F 3 "" H 11150 3100 50  0001 C CNN
	1    11150 3100
	1    0    0    -1  
$EndComp
$Comp
L C-RESCUE-nome C8
U 1 1 59E7CECD
P 7500 3900
F 0 "C8" H 7525 4000 50  0000 L CNN
F 1 "10uF" H 7525 3800 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 7538 3750 50  0001 C CNN
F 3 "http://datasheets.avx.com/cx5r.pdf" H 7500 3900 50  0001 C CNN
F 4 "478-5167-1-ND" H 0   0   60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/avx-corporation/0805ZD106KAT2A/478-5167-1-ND/1913257" H 0   0   60  0001 C CNN "S1PL"
F 6 "AVX Corporation" H 0   0   60  0001 C CNN "MFN"
F 7 "0805ZD106KAT2A" H 0   0   60  0001 C CNN "MFP"
	1    7500 3900
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-nome #PWR012
U 1 1 59E7CFD0
P 7500 4150
F 0 "#PWR012" H 7500 3900 50  0001 C CNN
F 1 "GND" H 7500 4000 50  0000 C CNN
F 2 "" H 7500 4150 50  0001 C CNN
F 3 "" H 7500 4150 50  0001 C CNN
	1    7500 4150
	1    0    0    -1  
$EndComp
$Comp
L C-RESCUE-nome C11
U 1 1 59E7D0C7
P 7900 3050
F 0 "C11" H 7925 3150 50  0000 L CNN
F 1 "0.1uF" H 7925 2950 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 7938 2900 50  0001 C CNN
F 3 "http://datasheets.avx.com/X7RDielectric.pdf" H 7900 3050 50  0001 C CNN
F 4 "478-1395-1-ND" H 0   0   60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/avx-corporation/08055C104KAT2A/478-1395-1-ND/564427" H 0   0   60  0001 C CNN "S1PL"
F 6 "AVX Corporation" H 0   0   60  0001 C CNN "MFN"
F 7 "08055C104KAT2A" H 0   0   60  0001 C CNN "MFP"
	1    7900 3050
	1    0    0    -1  
$EndComp
$Comp
L C-RESCUE-nome C12
U 1 1 59E7D120
P 7900 3950
F 0 "C12" H 7925 4050 50  0000 L CNN
F 1 "0.1uF" H 7925 3850 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 7938 3800 50  0001 C CNN
F 3 "http://datasheets.avx.com/X7RDielectric.pdf" H 7900 3950 50  0001 C CNN
F 4 "478-1395-1-ND" H 0   0   60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/avx-corporation/08055C104KAT2A/478-1395-1-ND/564427" H 0   0   60  0001 C CNN "S1PL"
F 6 "AVX Corporation" H 0   0   60  0001 C CNN "MFN"
F 7 "08055C104KAT2A" H 0   0   60  0001 C CNN "MFP"
	1    7900 3950
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-nome #PWR013
U 1 1 59E7D220
P 7900 3400
F 0 "#PWR013" H 7900 3150 50  0001 C CNN
F 1 "GND" H 7900 3250 50  0000 C CNN
F 2 "" H 7900 3400 50  0001 C CNN
F 3 "" H 7900 3400 50  0001 C CNN
	1    7900 3400
	1    0    0    -1  
$EndComp
Text Label 7500 4100 0    60   ~ 0
GND
$Comp
L GND-RESCUE-nome #PWR014
U 1 1 59E7D3C5
P 7900 4350
F 0 "#PWR014" H 7900 4100 50  0001 C CNN
F 1 "GND" H 7900 4200 50  0000 C CNN
F 2 "" H 7900 4350 50  0001 C CNN
F 3 "" H 7900 4350 50  0001 C CNN
	1    7900 4350
	1    0    0    -1  
$EndComp
Text Label 7900 3300 0    60   ~ 0
GND
Text Label 7900 4200 0    60   ~ 0
GND
$Comp
L GND-RESCUE-nome #PWR015
U 1 1 59E82134
P 11900 5550
F 0 "#PWR015" H 11900 5300 50  0001 C CNN
F 1 "GND" H 11900 5400 50  0000 C CNN
F 2 "" H 11900 5550 50  0001 C CNN
F 3 "" H 11900 5550 50  0001 C CNN
	1    11900 5550
	1    0    0    -1  
$EndComp
Text Label 11900 5500 0    60   ~ 0
GND
$Comp
L C-RESCUE-nome C24
U 1 1 59E82294
P 11400 5050
F 0 "C24" H 11425 5150 50  0000 L CNN
F 1 "10uF" H 11425 4950 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 11438 4900 50  0001 C CNN
F 3 "http://datasheets.avx.com/cx5r.pdf" H 11400 5050 50  0001 C CNN
F 4 "478-5167-1-ND" H 0   0   60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/avx-corporation/0805ZD106KAT2A/478-5167-1-ND/1913257" H 0   0   60  0001 C CNN "S1PL"
F 6 "AVX Corporation" H 0   0   60  0001 C CNN "MFN"
F 7 "0805ZD106KAT2A" H 0   0   60  0001 C CNN "MFP"
	1    11400 5050
	1    0    0    -1  
$EndComp
$Comp
L C-RESCUE-nome C22
U 1 1 59E82493
P 10800 5100
F 0 "C22" H 10825 5200 50  0000 L CNN
F 1 "1uF" H 10825 5000 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 10838 4950 50  0001 C CNN
F 3 "http://datasheets.avx.com/X7RDielectric.pdf" H 10800 5100 50  0001 C CNN
F 4 "478-1405-1-ND" H 0   0   60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/avx-corporation/0805ZC105KAT2A/478-1405-1-ND/564437" H 0   0   60  0001 C CNN "S1PL"
F 6 "AVX Corporation" H 0   0   60  0001 C CNN "MFN"
F 7 "0805ZC105KAT2A" H 0   0   60  0001 C CNN "MFP"
	1    10800 5100
	1    0    0    -1  
$EndComp
$Comp
L C-RESCUE-nome C18
U 1 1 59E8284B
P 10200 5650
F 0 "C18" H 10225 5750 50  0000 L CNN
F 1 "150pF" H 10225 5550 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 10238 5500 50  0001 C CNN
F 3 "http://datasheets.avx.com/C0GNP0-Dielectric.pdf" H 10200 5650 50  0001 C CNN
F 4 "478-1318-1-ND" H 0   0   60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/avx-corporation/08055A151JAT2A/478-1318-1-ND/564350" H 0   0   60  0001 C CNN "S1PL"
F 6 "AVX Corporation" H 0   0   60  0001 C CNN "MFN"
F 7 "08055A151JAT2A" H 0   0   60  0001 C CNN "MFP"
	1    10200 5650
	1    0    0    -1  
$EndComp
$Comp
L C-RESCUE-nome C20
U 1 1 59E82AEA
P 10550 5650
F 0 "C20" H 10575 5750 50  0000 L CNN
F 1 "150pF" H 10575 5550 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 10588 5500 50  0001 C CNN
F 3 "http://datasheets.avx.com/C0GNP0-Dielectric.pdf" H 10550 5650 50  0001 C CNN
F 4 "478-1318-1-ND" H 0   0   60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/avx-corporation/08055A151JAT2A/478-1318-1-ND/564350" H 0   0   60  0001 C CNN "S1PL"
F 6 "AVX Corporation" H 0   0   60  0001 C CNN "MFN"
F 7 "08055A151JAT2A" H 0   0   60  0001 C CNN "MFP"
	1    10550 5650
	1    0    0    -1  
$EndComp
$Comp
L Speaker-RESCUE-nome LS1
U 1 1 59E82ECF
P 14050 1000
F 0 "LS1" H 14100 1225 50  0000 R CNN
F 1 "Speaker" H 14100 1150 50  0000 R CNN
F 2 "nome:WirePad-1x2-2.54mm" H 14050 800 50  0001 C CNN
F 3 "https://media.digikey.com/pdf/Data%20Sheets/Mallory%20Sonalert%20PDFs/PSR-57N08A01-AQ.PDF" H 14040 950 50  0001 C CNN
F 4 "https://www.digikey.com/product-detail/en/mallory-sonalert-products-inc/PSR-57N08A01-AQ/458-1136-ND/2071452" H 0   0   60  0001 C CNN "S1PL"
F 5 "458-1136-ND" H 0   0   60  0001 C CNN "S1PN"
F 6 "Mallory Sonalert Products Inc." H 0   0   60  0001 C CNN "MFN"
F 7 "PSR-57N08A01-AQ" H 0   0   60  0001 C CNN "MFP"
	1    14050 1000
	1    0    0    -1  
$EndComp
Text Label 13750 1000 2    60   ~ 0
SPKR_A_NEG
Text Label 13750 1100 2    60   ~ 0
SPKR_A_POS
Text Label 8950 3550 2    60   ~ 0
SPKR_A_POS
Text Label 8800 3750 2    60   ~ 0
SPKR_A_NEG
NoConn ~ 9800 3150
NoConn ~ 10400 3250
NoConn ~ 10400 3350
NoConn ~ 10400 3650
NoConn ~ 10400 3750
NoConn ~ 10400 3850
NoConn ~ 10400 3950
NoConn ~ 10400 4050
NoConn ~ 10400 4150
NoConn ~ 10250 4250
$Comp
L C-RESCUE-nome C14
U 1 1 59E8470E
P 8700 5900
F 0 "C14" H 8725 6000 50  0000 L CNN
F 1 "1uF" H 8725 5800 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 8738 5750 50  0001 C CNN
F 3 "http://datasheets.avx.com/X7RDielectric.pdf" H 8700 5900 50  0001 C CNN
F 4 "478-1405-1-ND" H 0   0   60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/avx-corporation/0805ZC105KAT2A/478-1405-1-ND/564437" H 0   0   60  0001 C CNN "S1PL"
F 6 "AVX Corporation" H 0   0   60  0001 C CNN "MFN"
F 7 "0805ZC105KAT2A" H 0   0   60  0001 C CNN "MFP"
	1    8700 5900
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-nome #PWR016
U 1 1 59E84953
P 8700 6150
F 0 "#PWR016" H 8700 5900 50  0001 C CNN
F 1 "GND" H 8700 6000 50  0000 C CNN
F 2 "" H 8700 6150 50  0001 C CNN
F 3 "" H 8700 6150 50  0001 C CNN
	1    8700 6150
	1    0    0    -1  
$EndComp
$Comp
L C-RESCUE-nome C16
U 1 1 59E84A6B
P 9100 5900
F 0 "C16" H 9125 6000 50  0000 L CNN
F 1 "0.1uF" H 9125 5800 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 9138 5750 50  0001 C CNN
F 3 "http://datasheets.avx.com/X7RDielectric.pdf" H 9100 5900 50  0001 C CNN
F 4 "478-1395-1-ND" H 9100 5900 60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/avx-corporation/08055C104KAT2A/478-1395-1-ND/564427" H 9100 5900 60  0001 C CNN "S1PL"
F 6 "AVX Corporation" H 9100 5900 60  0001 C CNN "MFN"
F 7 "08055C104KAT2A" H 9100 5900 60  0001 C CNN "MFP"
	1    9100 5900
	1    0    0    -1  
$EndComp
$Comp
L C-RESCUE-nome C17
U 1 1 59E84F64
P 9550 5850
F 0 "C17" H 9575 5950 50  0000 L CNN
F 1 "0.1uF" H 9575 5750 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 9588 5700 50  0001 C CNN
F 3 "http://datasheets.avx.com/X7RDielectric.pdf" H 9550 5850 50  0001 C CNN
F 4 "478-1395-1-ND" H 0   0   60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/avx-corporation/08055C104KAT2A/478-1395-1-ND/564427" H 0   0   60  0001 C CNN "S1PL"
F 6 "AVX Corporation" H 0   0   60  0001 C CNN "MFN"
F 7 "08055C104KAT2A" H 0   0   60  0001 C CNN "MFP"
	1    9550 5850
	1    0    0    -1  
$EndComp
Text Label 9650 5100 3    60   ~ 0
HP_B
Text Label 9750 5100 3    60   ~ 0
HP_A
Text Label 10200 2700 1    60   ~ 0
DAC_RST
Text Label 3400 5300 3    60   ~ 0
DAC_RST
NoConn ~ 9250 3850
NoConn ~ 9250 4050
$Comp
L C-RESCUE-nome C9
U 1 1 59E96545
P 13250 1750
F 0 "C9" H 13275 1850 50  0000 L CNN
F 1 "0.022uF" H 13275 1650 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 13288 1600 50  0001 C CNN
F 3 "http://datasheets.avx.com/X7RDielectric.pdf" H 13250 1750 50  0001 C CNN
F 4 "478-1360-1-ND" H 0   0   60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/avx-corporation/08051C223KAT2A/478-1360-1-ND/564392" H 0   0   60  0001 C CNN "S1PL"
F 6 "AVX Corporation" H 0   0   60  0001 C CNN "MFN"
F 7 "08051C223KAT2A" H 0   0   60  0001 C CNN "MFP"
	1    13250 1750
	0    1    1    0   
$EndComp
$Comp
L R-RESCUE-nome R6
U 1 1 59E9659C
P 13650 1750
F 0 "R6" V 13730 1750 50  0000 C CNN
F 1 "51.1" V 13650 1750 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 13580 1750 50  0001 C CNN
F 3 "http://www.yageo.com.tw/exep/pages/download/literatures/PYu-R_INT-thick_7.pdf" H 13650 1750 50  0001 C CNN
F 4 "311-51.1CRCT-ND" H 0   0   60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/yageo/RC0805FR-0751R1L/311-51.1CRCT-ND/730961" H 0   0   60  0001 C CNN "S1PL"
F 6 "Yageo" H 0   0   60  0001 C CNN "MFN"
F 7 "RC0805FR-0751R1L" H 0   0   60  0001 C CNN "MFP"
	1    13650 1750
	0    1    1    0   
$EndComp
$Comp
L GND-RESCUE-nome #PWR017
U 1 1 59E96B30
P 13900 2800
F 0 "#PWR017" H 13900 2550 50  0001 C CNN
F 1 "GND" H 13900 2650 50  0000 C CNN
F 2 "" H 13900 2800 50  0001 C CNN
F 3 "" H 13900 2800 50  0001 C CNN
	1    13900 2800
	1    0    0    -1  
$EndComp
Text Label 13900 2750 0    60   ~ 0
GND
$Comp
L C-RESCUE-nome C10
U 1 1 59E96D04
P 13250 2450
F 0 "C10" H 13275 2550 50  0000 L CNN
F 1 "0.022uF" H 13275 2350 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 13288 2300 50  0001 C CNN
F 3 "http://datasheets.avx.com/X7RDielectric.pdf" H 13250 2450 50  0001 C CNN
F 4 "478-1360-1-ND" H 0   0   60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/avx-corporation/08051C223KAT2A/478-1360-1-ND/564392" H 0   0   60  0001 C CNN "S1PL"
F 6 "AVX Corporation" H 0   0   60  0001 C CNN "MFN"
F 7 "08051C223KAT2A" H 0   0   60  0001 C CNN "MFP"
	1    13250 2450
	0    1    1    0   
$EndComp
$Comp
L R-RESCUE-nome R7
U 1 1 59E96D63
P 13650 2450
F 0 "R7" V 13730 2450 50  0000 C CNN
F 1 "51.1" V 13650 2450 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 13580 2450 50  0001 C CNN
F 3 "http://www.yageo.com.tw/exep/pages/download/literatures/PYu-R_INT-thick_7.pdf" H 13650 2450 50  0001 C CNN
F 4 "311-51.1CRCT-ND" H 0   0   60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/yageo/RC0805FR-0751R1L/311-51.1CRCT-ND/730961" H 0   0   60  0001 C CNN "S1PL"
F 6 "Yageo" H 0   0   60  0001 C CNN "MFN"
F 7 "RC0805FR-0751R1L" H 0   0   60  0001 C CNN "MFP"
	1    13650 2450
	0    1    1    0   
$EndComp
Text Label 12850 2250 2    60   ~ 0
HP_B
Text Label 12850 2050 2    60   ~ 0
HP_A
Text Label 10300 2850 1    60   ~ 0
SPKR_HP
$Comp
L GND-RESCUE-nome #PWR018
U 1 1 59EB968E
P 4950 11250
F 0 "#PWR018" H 4950 11000 50  0001 C CNN
F 1 "GND" H 4950 11100 50  0000 C CNN
F 2 "" H 4950 11250 50  0001 C CNN
F 3 "" H 4950 11250 50  0001 C CNN
	1    4950 11250
	1    0    0    -1  
$EndComp
$Comp
L +1V8-RESCUE-nome #PWR019
U 1 1 59EBA3CB
P 5900 10750
F 0 "#PWR019" H 5900 10600 50  0001 C CNN
F 1 "+1V8" H 5900 10890 50  0000 C CNN
F 2 "" H 5900 10750 50  0001 C CNN
F 3 "" H 5900 10750 50  0001 C CNN
	1    5900 10750
	0    1    1    0   
$EndComp
Text Label 5800 10750 1    60   ~ 0
1.8V
$Comp
L +1V8-RESCUE-nome #PWR020
U 1 1 59EBAC5C
P 7150 3350
F 0 "#PWR020" H 7150 3200 50  0001 C CNN
F 1 "+1V8" H 7150 3490 50  0000 C CNN
F 2 "" H 7150 3350 50  0001 C CNN
F 3 "" H 7150 3350 50  0001 C CNN
	1    7150 3350
	1    0    0    -1  
$EndComp
Text Label 7150 3450 0    60   ~ 0
1.8V
$Comp
L +1V8-RESCUE-nome #PWR021
U 1 1 59EBB07D
P 10250 1650
F 0 "#PWR021" H 10250 1500 50  0001 C CNN
F 1 "+1V8" H 10250 1790 50  0000 C CNN
F 2 "" H 10250 1650 50  0001 C CNN
F 3 "" H 10250 1650 50  0001 C CNN
	1    10250 1650
	1    0    0    -1  
$EndComp
Text Label 10250 1700 0    60   ~ 0
1.8V
$Comp
L +1V8-RESCUE-nome #PWR022
U 1 1 59EBB271
P 11150 2250
F 0 "#PWR022" H 11150 2100 50  0001 C CNN
F 1 "+1V8" H 11150 2390 50  0000 C CNN
F 2 "" H 11150 2250 50  0001 C CNN
F 3 "" H 11150 2250 50  0001 C CNN
	1    11150 2250
	1    0    0    -1  
$EndComp
Text Label 11150 2300 0    60   ~ 0
1.8V
$Comp
L +1V8-RESCUE-nome #PWR023
U 1 1 59EBB434
P 8700 5450
F 0 "#PWR023" H 8700 5300 50  0001 C CNN
F 1 "+1V8" H 8700 5590 50  0000 C CNN
F 2 "" H 8700 5450 50  0001 C CNN
F 3 "" H 8700 5450 50  0001 C CNN
	1    8700 5450
	1    0    0    -1  
$EndComp
Text Label 8700 5500 0    60   ~ 0
1.8V
$Comp
L +3.3V-RESCUE-nome #PWR024
U 1 1 59EBC448
P 4000 1100
F 0 "#PWR024" H 4000 950 50  0001 C CNN
F 1 "+3.3V" H 4000 1240 50  0000 C CNN
F 2 "" H 4000 1100 50  0001 C CNN
F 3 "" H 4000 1100 50  0001 C CNN
	1    4000 1100
	1    0    0    -1  
$EndComp
Text Label 4000 1200 0    60   ~ 0
3.3V
$Comp
L +3.3V-RESCUE-nome #PWR025
U 1 1 59EBC6B7
P 5500 3400
F 0 "#PWR025" H 5500 3250 50  0001 C CNN
F 1 "+3.3V" H 5500 3540 50  0000 C CNN
F 2 "" H 5500 3400 50  0001 C CNN
F 3 "" H 5500 3400 50  0001 C CNN
	1    5500 3400
	1    0    0    -1  
$EndComp
Text Label 5500 3450 0    60   ~ 0
3.3V
$Comp
L +3.3V-RESCUE-nome #PWR026
U 1 1 59EBC777
P 4700 5100
F 0 "#PWR026" H 4700 4950 50  0001 C CNN
F 1 "+3.3V" H 4700 5240 50  0000 C CNN
F 2 "" H 4700 5100 50  0001 C CNN
F 3 "" H 4700 5100 50  0001 C CNN
	1    4700 5100
	1    0    0    -1  
$EndComp
Text Label 4700 5150 0    60   ~ 0
3.3V
$Comp
L +3.3V-RESCUE-nome #PWR027
U 1 1 59EBCB9F
P 2050 2350
F 0 "#PWR027" H 2050 2200 50  0001 C CNN
F 1 "+3.3V" H 2050 2490 50  0000 C CNN
F 2 "" H 2050 2350 50  0001 C CNN
F 3 "" H 2050 2350 50  0001 C CNN
	1    2050 2350
	1    0    0    -1  
$EndComp
$Comp
L LM1117-1.8-RESCUE-nome U1
U 1 1 59EBCE5C
P 4950 10750
F 0 "U1" H 4800 10875 50  0000 C CNN
F 1 "LM1117-1.8" H 4950 10875 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-223" H 4950 10750 50  0001 C CNN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/99/3b/7d/91/91/51/4b/be/CD00000544.pdf/files/CD00000544.pdf/jcr:content/translations/en.CD00000544.pdf" H 4950 10750 50  0001 C CNN
F 4 "497-7308-1-ND" H 4950 10750 60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/stmicroelectronics/LD1117S18TR/497-7308-1-ND/1883983" H 4950 10750 60  0001 C CNN "S1PL"
F 6 "STMicroelectronics" H 4950 10750 60  0001 C CNN "MFN"
F 7 "LD1117S18TR" H 4950 10750 60  0001 C CNN "MFP"
	1    4950 10750
	1    0    0    -1  
$EndComp
Text Label 4950 11200 0    60   ~ 0
GND
$Comp
L LM1117-3.3-RESCUE-nome U2
U 1 1 59EBD530
P 4950 11600
F 0 "U2" H 4800 11725 50  0000 C CNN
F 1 "LM1117-3.3" H 4950 11725 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-223" H 4950 11600 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm1117.pdf" H 4950 11600 50  0001 C CNN
F 4 "LM1117MP-3.3/NOPBCT-ND" H 4950 11600 60  0001 C CNN "497-1242-6-ND"
F 5 "https://www.digikey.com/product-detail/en/stmicroelectronics/LD1117S33TR/497-1242-6-ND/1706544" H 4950 11600 60  0001 C CNN "S1PL"
F 6 "STMicroelectronics" H 4950 11600 60  0001 C CNN "MFN"
F 7 "LD1117S33TR" H 4950 11600 60  0001 C CNN "MFP"
	1    4950 11600
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-nome #PWR028
U 1 1 59EBDD02
P 4950 12050
F 0 "#PWR028" H 4950 11800 50  0001 C CNN
F 1 "GND" H 4950 11900 50  0000 C CNN
F 2 "" H 4950 12050 50  0001 C CNN
F 3 "" H 4950 12050 50  0001 C CNN
	1    4950 12050
	1    0    0    -1  
$EndComp
Text Label 4950 12000 0    60   ~ 0
GND
$Comp
L +3.3V-RESCUE-nome #PWR029
U 1 1 59EBE08C
P 5800 11600
F 0 "#PWR029" H 5800 11450 50  0001 C CNN
F 1 "+3.3V" H 5800 11740 50  0000 C CNN
F 2 "" H 5800 11600 50  0001 C CNN
F 3 "" H 5800 11600 50  0001 C CNN
	1    5800 11600
	0    1    1    0   
$EndComp
$Comp
L AS1115-RESCUE-nome U3
U 1 1 59EC3D68
P 3600 7300
F 0 "U3" H 3550 7450 60  0000 C CNN
F 1 "AS1115" H 3550 7300 60  0000 C CNN
F 2 "Housings_SSOP:QSOP-24_3.9x8.7mm_Pitch0.635mm" H 3550 7300 60  0001 C CNN
F 3 "http://ams.com/eng/content/download/18430/343782" H 3550 7300 60  0001 C CNN
F 4 "AS1115-BSSTCT-ND" H 3600 7300 60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/ams/AS1115-BSST/AS1115-BSSTCT-ND/2469597" H 3600 7300 60  0001 C CNN "S1PL"
F 6 "ams" H 3600 7300 60  0001 C CNN "MFN"
F 7 "AS1115-BSST" H 3600 7300 60  0001 C CNN "MFP"
	1    3600 7300
	1    0    0    -1  
$EndComp
NoConn ~ 7900 8650
NoConn ~ 8000 8650
NoConn ~ 8100 8650
$Comp
L GND-RESCUE-nome #PWR030
U 1 1 59EC6122
P 3550 9200
F 0 "#PWR030" H 3550 8950 50  0001 C CNN
F 1 "GND" H 3550 9050 50  0000 C CNN
F 2 "" H 3550 9200 50  0001 C CNN
F 3 "" H 3550 9200 50  0001 C CNN
	1    3550 9200
	1    0    0    -1  
$EndComp
Text Label 3550 9150 0    60   ~ 0
GND
$Comp
L R-RESCUE-nome R1
U 1 1 59EC64B4
P 2600 7100
F 0 "R1" V 2680 7100 50  0000 C CNN
F 1 "10k" V 2600 7100 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2530 7100 50  0001 C CNN
F 3 "http://www.yageo.com.tw/exep/pages/download/literatures/PYu-R_INT-thick_7.pdf" H 2600 7100 50  0001 C CNN
F 4 "311-10KARCT-ND" H 0   0   60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/yageo/RC0805JR-0710KL/311-10KARCT-ND/731188" H 0   0   60  0001 C CNN "S1PL"
F 6 "Yageo" H 0   0   60  0001 C CNN "MFN"
F 7 "RC0805JR-0710KL" H 0   0   60  0001 C CNN "MFP"
	1    2600 7100
	0    -1   -1   0   
$EndComp
NoConn ~ 3000 8050
NoConn ~ 3200 7650
NoConn ~ 3200 7750
$Comp
L LTC-4727JS-RESCUE-nome U5
U 1 1 59EC78C2
P 7150 8150
F 0 "U5" H 6200 8600 50  0000 C CNN
F 1 "LTC-4727JS" H 7920 8600 50  0000 C CNN
F 2 "nome:LTC-4727" H 7150 7550 50  0001 C CNN
F 3 "https://media.digikey.com/pdf/Data%20Sheets/Lite-On%20PDFs/LTC-4727JS.pdf" H 6770 8180 50  0001 C CNN
F 4 "160-1547-5-ND" H 7150 8150 60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/lite-on-inc/LTC-4727JS/160-1547-5-ND/408220" H 7150 8150 60  0001 C CNN "S1PL"
F 6 "Lite-On Inc." H 7150 8150 60  0001 C CNN "MFN"
F 7 "LTC-4727JS" H 7150 8150 60  0001 C CNN "MFP"
	1    7150 8150
	1    0    0    -1  
$EndComp
$Comp
L C-RESCUE-nome C1
U 1 1 59EC7FF1
P 1450 7800
F 0 "C1" H 1475 7900 50  0000 L CNN
F 1 "0.1uF" H 1475 7700 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 1488 7650 50  0001 C CNN
F 3 "http://datasheets.avx.com/X7RDielectric.pdf" H 1450 7800 50  0001 C CNN
F 4 "478-1395-1-ND" H 0   0   60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/avx-corporation/08055C104KAT2A/478-1395-1-ND/564427" H 0   0   60  0001 C CNN "S1PL"
F 6 "AVX Corporation" H 0   0   60  0001 C CNN "MFN"
F 7 "08055C104KAT2A" H 0   0   60  0001 C CNN "MFP"
	1    1450 7800
	1    0    0    -1  
$EndComp
$Comp
L +3.3V-RESCUE-nome #PWR031
U 1 1 59EC8828
P 1450 6800
F 0 "#PWR031" H 1450 6650 50  0001 C CNN
F 1 "+3.3V" H 1450 6940 50  0000 C CNN
F 2 "" H 1450 6800 50  0001 C CNN
F 3 "" H 1450 6800 50  0001 C CNN
	1    1450 6800
	1    0    0    -1  
$EndComp
NoConn ~ 4000 7500
NoConn ~ 4000 7600
NoConn ~ 4000 7700
Text Label 1450 6900 0    60   ~ 0
3.3V
Text Label 5650 11600 1    60   ~ 0
3.3V
Text Label 3450 2300 0    60   ~ 0
DAC_SDA
Text Label 3450 2450 0    60   ~ 0
7SEG_SDA
Text Label 4200 2050 0    60   ~ 0
DAC_SCL
Text Label 4250 2200 0    60   ~ 0
7SEG_SCL
$Comp
L LED-RESCUE-nome D4
U 1 1 59ECB766
P 11800 8450
F 0 "D4" H 11800 8550 50  0000 C CNN
F 1 "LED Orange" H 11800 8350 50  0000 C CNN
F 2 "LEDs:LED_0805_HandSoldering" H 11800 8450 50  0001 C CNN
F 3 "http://optoelectronics.liteon.com/upload/download/DS-22-99-0170/LTST-C171AKT.pdf" H 11800 8450 50  0001 C CNN
F 4 "160-1419-1-ND" H 11800 8450 60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/lite-on-inc/LTST-C171AKT/160-1419-1-ND/386784" H 11800 8450 60  0001 C CNN "S1PL"
F 6 "Lite-On Inc." H 11800 8450 60  0001 C CNN "MFN"
F 7 "LTST-C171AKT" H 11800 8450 60  0001 C CNN "MFP"
	1    11800 8450
	0    -1   -1   0   
$EndComp
$Comp
L LED-RESCUE-nome D3
U 1 1 59ECB7DD
P 11500 8450
F 0 "D3" H 11500 8550 50  0000 C CNN
F 1 "LED Red" H 11500 8350 50  0000 C CNN
F 2 "LEDs:LED_0805_HandSoldering" H 11500 8450 50  0001 C CNN
F 3 "http://optoelectronics.liteon.com/upload/download/DS22-2000-109/LTST-C171KRKT.pdf" H 11500 8450 50  0001 C CNN
F 4 "160-1427-1-ND" H 11500 8450 60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/lite-on-inc/LTST-C171KRKT/160-1427-1-ND/386800" H 11500 8450 60  0001 C CNN "S1PL"
F 6 "Lite-On Inc." H 11500 8450 60  0001 C CNN "MFN"
F 7 "LTST-C171KRK" H 11500 8450 60  0001 C CNN "MFP"
	1    11500 8450
	0    -1   -1   0   
$EndComp
$Comp
L LED-RESCUE-nome D2
U 1 1 59ECB8E0
P 11200 8450
F 0 "D2" H 11200 8550 50  0000 C CNN
F 1 "LED Green" H 11200 8350 50  0000 C CNN
F 2 "LEDs:LED_0805_HandSoldering" H 11200 8450 50  0001 C CNN
F 3 "https://media.digikey.com/pdf/Data%20Sheets/Lite-On%20PDFs/LTST-C171GKT.pdf" H 11200 8450 50  0001 C CNN
F 4 "160-1423-1-ND" H 11200 8450 60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/lite-on-inc/LTST-C171GKT/160-1423-1-ND/386792" H 11200 8450 60  0001 C CNN "S1PL"
F 6 "Lite-On Inc." H 11200 8450 60  0001 C CNN "MFN"
F 7 "LTST-C171GKT" H 11200 8450 60  0001 C CNN "MFP"
	1    11200 8450
	0    -1   -1   0   
$EndComp
$Comp
L LED-RESCUE-nome D1
U 1 1 59ECB959
P 10900 8450
F 0 "D1" H 10900 8550 50  0000 C CNN
F 1 "LED Blue" H 10900 8350 50  0000 C CNN
F 2 "LEDs:LED_0805_HandSoldering" H 10900 8450 50  0001 C CNN
F 3 "http://optoelectronics.liteon.com/upload/download/DS22-2000-233/LTST-C171TBKT(0630).pdf" H 10900 8450 50  0001 C CNN
F 4 "160-1645-1-ND" H 10900 8450 60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/lite-on-inc/LTST-C171TBKT/160-1645-1-ND/573585" H 10900 8450 60  0001 C CNN "S1PL"
F 6 "Lite-On Inc." H 10900 8450 60  0001 C CNN "MFN"
F 7 "LTST-C171TBKT" H 10900 8450 60  0001 C CNN "MFP"
	1    10900 8450
	0    -1   -1   0   
$EndComp
Text Label 11200 8200 1    60   ~ 0
LED_Ok
Text Label 11500 8200 1    60   ~ 0
LED_Err
Text Label 11800 8200 1    60   ~ 0
LED_Act
Text Label 4650 4100 0    60   ~ 0
LED_Ok
Text Label 4650 4200 0    60   ~ 0
LED_Err
Text Label 4650 4300 0    60   ~ 0
LED_Act
$Comp
L R-RESCUE-nome R2
U 1 1 59ECD1A0
P 10900 8900
F 0 "R2" V 10980 8900 50  0000 C CNN
F 1 "25" V 10900 8900 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 10830 8900 50  0001 C CNN
F 3 "http://www.yageo.com.tw/exep/pages/download/literatures/PYu-R_INT-thick_7.pdf" H 10900 8900 50  0001 C CNN
F 4 "311-24.9CRCT-ND" H 0   0   60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/yageo/RC0805FR-0724R9L/311-24.9CRCT-ND/730706" H 0   0   60  0001 C CNN "S1PL"
F 6 "Yageo" H 0   0   60  0001 C CNN "MFN"
F 7 "RC0805FR-0724R9L" H 0   0   60  0001 C CNN "MFP"
	1    10900 8900
	1    0    0    -1  
$EndComp
$Comp
L R-RESCUE-nome R3
U 1 1 59ECD35A
P 11200 8900
F 0 "R3" V 11280 8900 50  0000 C CNN
F 1 "40" V 11200 8900 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 11130 8900 50  0001 C CNN
F 3 "http://www.yageo.com.tw/exep/pages/download/literatures/PYu-R_INT-thick_7.pdf" H 11200 8900 50  0001 C CNN
F 4 "311-40.2CRCT-ND" H 0   0   60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/yageo/RC0805FR-0740R2L/311-40.2CRCT-ND/730887" H 0   0   60  0001 C CNN "S1PL"
F 6 "Yageo" H 0   0   60  0001 C CNN "MFN"
F 7 "RC0805FR-0740R2L" H 0   0   60  0001 C CNN "MFP"
	1    11200 8900
	1    0    0    -1  
$EndComp
$Comp
L R-RESCUE-nome R4
U 1 1 59ECD4E9
P 11500 8900
F 0 "R4" V 11580 8900 50  0000 C CNN
F 1 "40" V 11500 8900 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 11430 8900 50  0001 C CNN
F 3 "http://www.yageo.com.tw/exep/pages/download/literatures/PYu-R_INT-thick_7.pdf" H 11500 8900 50  0001 C CNN
F 4 "311-40.2CRCT-ND" H 0   0   60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/yageo/RC0805FR-0740R2L/311-40.2CRCT-ND/730887" H 0   0   60  0001 C CNN "S1PL"
F 6 "Yageo" H 0   0   60  0001 C CNN "MFN"
F 7 "RC0805FR-0740R2L" H 0   0   60  0001 C CNN "MFP"
	1    11500 8900
	1    0    0    -1  
$EndComp
$Comp
L R-RESCUE-nome R5
U 1 1 59ECD626
P 11800 8900
F 0 "R5" V 11880 8900 50  0000 C CNN
F 1 "40" V 11800 8900 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 11730 8900 50  0001 C CNN
F 3 "http://www.yageo.com.tw/exep/pages/download/literatures/PYu-R_INT-thick_7.pdf" H 11800 8900 50  0001 C CNN
F 4 "311-40.2CRCT-ND" H 0   0   60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/yageo/RC0805FR-0740R2L/311-40.2CRCT-ND/730887" H 0   0   60  0001 C CNN "S1PL"
F 6 "Yageo" H 0   0   60  0001 C CNN "MFN"
F 7 "RC0805FR-0740R2L" H 0   0   60  0001 C CNN "MFP"
	1    11800 8900
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-nome #PWR032
U 1 1 59ECDC25
P 10900 9200
F 0 "#PWR032" H 10900 8950 50  0001 C CNN
F 1 "GND" H 10900 9050 50  0000 C CNN
F 2 "" H 10900 9200 50  0001 C CNN
F 3 "" H 10900 9200 50  0001 C CNN
	1    10900 9200
	1    0    0    -1  
$EndComp
Text Label 10900 9150 2    60   ~ 0
GND
$Comp
L GND-RESCUE-nome #PWR033
U 1 1 59ECDE0F
P 11200 9200
F 0 "#PWR033" H 11200 8950 50  0001 C CNN
F 1 "GND" H 11200 9050 50  0000 C CNN
F 2 "" H 11200 9200 50  0001 C CNN
F 3 "" H 11200 9200 50  0001 C CNN
	1    11200 9200
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-nome #PWR034
U 1 1 59ECDE7F
P 11500 9200
F 0 "#PWR034" H 11500 8950 50  0001 C CNN
F 1 "GND" H 11500 9050 50  0000 C CNN
F 2 "" H 11500 9200 50  0001 C CNN
F 3 "" H 11500 9200 50  0001 C CNN
	1    11500 9200
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-nome #PWR035
U 1 1 59ECE00C
P 11800 9200
F 0 "#PWR035" H 11800 8950 50  0001 C CNN
F 1 "GND" H 11800 9050 50  0000 C CNN
F 2 "" H 11800 9200 50  0001 C CNN
F 3 "" H 11800 9200 50  0001 C CNN
	1    11800 9200
	1    0    0    -1  
$EndComp
Text Label 11200 9150 2    60   ~ 0
GND
Text Label 11500 9150 2    60   ~ 0
GND
Text Label 11800 9150 2    60   ~ 0
GND
Text Label 2200 7300 0    60   ~ 0
7SEG_SDA
Text Label 2200 7400 0    60   ~ 0
7SEG_SCL
Text Label 8550 3250 0    60   ~ 0
DAC_SDA
Text Label 8550 3350 0    60   ~ 0
DAC_SCL
NoConn ~ 3100 3700
NoConn ~ 3100 3800
NoConn ~ 3100 3900
NoConn ~ 3100 4000
NoConn ~ 3100 4100
NoConn ~ 3100 4500
NoConn ~ 3500 4750
NoConn ~ 3600 4750
NoConn ~ 3700 4750
NoConn ~ 3800 4750
NoConn ~ 3900 4750
NoConn ~ 4400 4600
NoConn ~ 4400 4500
NoConn ~ 4400 4400
NoConn ~ 4400 3900
NoConn ~ 3700 3550
NoConn ~ 3500 3550
$Comp
L GND-RESCUE-nome #PWR036
U 1 1 59ED71C5
P 3600 2700
F 0 "#PWR036" H 3600 2450 50  0001 C CNN
F 1 "GND" H 3600 2550 50  0000 C CNN
F 2 "" H 3600 2700 50  0001 C CNN
F 3 "" H 3600 2700 50  0001 C CNN
	1    3600 2700
	-1   0    0    1   
$EndComp
Text Label 4750 3800 0    60   ~ 0
JTMS
Text Label 4300 3050 1    60   ~ 0
JTCK
Text Label 4200 3050 1    60   ~ 0
JTDI
Text Label 4100 3050 1    60   ~ 0
JTDO
Text Label 4000 3050 1    60   ~ 0
JTRST
$Comp
L +3.3V-RESCUE-nome #PWR037
U 1 1 59EDA31D
P 10900 8100
F 0 "#PWR037" H 10900 7950 50  0001 C CNN
F 1 "+3.3V" H 10900 8240 50  0000 C CNN
F 2 "" H 10900 8100 50  0001 C CNN
F 3 "" H 10900 8100 50  0001 C CNN
	1    10900 8100
	1    0    0    -1  
$EndComp
Text Label 10900 8200 2    60   ~ 0
3.3V
$Comp
L Conn_02x05_Odd_Even-RESCUE-nome J2
U 1 1 59EDA6EA
P 7150 11250
F 0 "J2" H 7200 11550 50  0000 C CNN
F 1 "JTAG_SWD" H 7200 10950 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x05_Pitch2.54mm" H 7150 11250 50  0001 C CNN
F 3 "http://www.on-shore.com/wp-content/uploads/2015/09/302-sxxx.pdf" H 7150 11250 50  0001 C CNN
F 4 "ED1543-ND" H 7150 11250 60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/on-shore-technology-inc/302-S101/ED1543-ND/2178422" H 7150 11250 60  0001 C CNN "S1PL"
F 6 "On Shore Technology Inc." H 7150 11250 60  0001 C CNN "MFN"
F 7 "302-S101" H 7150 11250 60  0001 C CNN "MFP"
	1    7150 11250
	1    0    0    -1  
$EndComp
Text Label 7500 11050 0    60   ~ 0
JTMS
Text Label 7500 11150 0    60   ~ 0
JTCK
Text Label 7500 11250 0    60   ~ 0
JTDO
Text Label 7500 11350 0    60   ~ 0
JTDI
$Comp
L GND-RESCUE-nome #PWR038
U 1 1 59EDB933
P 6600 11250
F 0 "#PWR038" H 6600 11000 50  0001 C CNN
F 1 "GND" H 6600 11100 50  0000 C CNN
F 2 "" H 6600 11250 50  0001 C CNN
F 3 "" H 6600 11250 50  0001 C CNN
	1    6600 11250
	1    0    0    -1  
$EndComp
NoConn ~ 6950 11350
$Comp
L +3.3V-RESCUE-nome #PWR039
U 1 1 59EDBC98
P 6600 10850
F 0 "#PWR039" H 6600 10700 50  0001 C CNN
F 1 "+3.3V" H 6600 10990 50  0000 C CNN
F 2 "" H 6600 10850 50  0001 C CNN
F 3 "" H 6600 10850 50  0001 C CNN
	1    6600 10850
	1    0    0    -1  
$EndComp
Text Label 6600 10900 0    60   ~ 0
3.3V
Text Label 7500 11450 0    60   ~ 0
RESET
Text Label 2100 4200 0    60   ~ 0
RESET
$Comp
L C-RESCUE-nome C26
U 1 1 59EDD613
P 4100 5700
F 0 "C26" H 4125 5800 50  0000 L CNN
F 1 "4.7uF" H 4125 5600 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 4138 5550 50  0001 C CNN
F 3 "http://datasheets.avx.com/cx5r.pdf" H 4100 5700 50  0001 C CNN
F 4 "478-1415-1-ND" H 0   0   60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/avx-corporation/0805ZD475KAT2A/478-1415-1-ND/564447" H 0   0   60  0001 C CNN "S1PL"
F 6 "AVX Corporation" H 0   0   60  0001 C CNN "MFN"
F 7 "0805ZD475KAT2A" H 0   0   60  0001 C CNN "MFP"
	1    4100 5700
	-1   0    0    1   
$EndComp
$Comp
L +3.3V-RESCUE-nome #PWR040
U 1 1 59EDDD84
P 2500 3350
F 0 "#PWR040" H 2500 3200 50  0001 C CNN
F 1 "+3.3V" H 2500 3490 50  0000 C CNN
F 2 "" H 2500 3350 50  0001 C CNN
F 3 "" H 2500 3350 50  0001 C CNN
	1    2500 3350
	1    0    0    -1  
$EndComp
Text Label 2500 3400 0    60   ~ 0
3.3V
Text Notes 1900 6600 0    60   ~ 12
User Interface
Text Notes 1000 10400 0    60   ~ 12
Power
Text Notes 6550 10500 0    60   ~ 12
JTAG / SWD
Text Notes 10900 7650 0    60   ~ 12
Status LED
Text Notes 7200 2050 0    60   ~ 12
Audio
Text Notes 1600 1700 0    60   ~ 12
Microcontroller
$Comp
L Conn_01x04-RESCUE-nome J4
U 1 1 59EEB3FD
P 1700 7400
F 0 "J4" H 1700 7600 50  0000 C CNN
F 1 "7SEG_DEBUG" H 1700 7100 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm" H 1700 7400 50  0001 C CNN
F 3 "https://cdn.harwin.com/pdfs/Harwin_Product_Catalog_page_208.pdf" H 1700 7400 50  0001 C CNN
F 4 "952-2265-ND" H 1700 7400 60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/harwin-inc/M20-9990445/952-2265-ND/3728229" H 1700 7400 60  0001 C CNN "S1PL"
F 6 "Harwin Inc." H 1700 7400 60  0001 C CNN "MFN"
F 7 "M20-9990445" H 1700 7400 60  0001 C CNN "MFP"
	1    1700 7400
	-1   0    0    1   
$EndComp
$Comp
L SW_SPDT-RESCUE-nome SW1
U 1 1 59EEDFE5
P 4150 11400
F 0 "SW1" H 4150 11570 50  0000 C CNN
F 1 "SW_SPDT" H 4150 11200 50  0000 C CNN
F 2 "nome:CK_SPDT" H 4150 11400 50  0001 C CNN
F 3 "http://www.ckswitches.com/media/1422/js.pdf" H 4150 11400 50  0001 C CNN
F 4 "401-1999-1-ND" H 4150 11400 60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/c-k/JS102011SAQN/401-1999-1-ND/1640114" H 4150 11400 60  0001 C CNN "S1PL"
F 6 "C&K" H 4150 11400 60  0001 C CNN "MFN"
F 7 "JS102011SAQN" H 4150 11400 60  0001 C CNN "MFP"
	1    4150 11400
	0    -1   -1   0   
$EndComp
$Comp
L C-RESCUE-nome C27
U 1 1 59EF03DA
P 1200 11100
F 0 "C27" H 1225 11200 50  0000 L CNN
F 1 "4.7uF" H 1225 11000 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 1238 10950 50  0001 C CNN
F 3 "http://datasheets.avx.com/cx5r.pdf" H 1200 11100 50  0001 C CNN
F 4 "478-1415-1-ND" H 0   0   60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/avx-corporation/0805ZD475KAT2A/478-1415-1-ND/564447" H 0   0   60  0001 C CNN "S1PL"
F 6 "AVX Corporation" H 0   0   60  0001 C CNN "MFN"
F 7 "0805ZD475KAT2A" H 0   0   60  0001 C CNN "MFP"
	1    1200 11100
	1    0    0    -1  
$EndComp
$Comp
L MCP73831-RESCUE-nome U8
U 1 1 59EF0F9D
P 2650 10850
F 0 "U8" H 2650 10600 50  0000 C CNN
F 1 "MCP73831" H 2650 11050 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-5_HandSoldering" H 2650 10850 60  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/20001060AQ.pdf" H 2650 10850 60  0001 C CNN
F 4 "MCP73831T-2ACI/OTCT-ND" H 2650 10850 60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/microchip-technology/MCP73831T-2ACI-OT/MCP73831T-2ACI-OTCT-ND/1979802" H 2650 10850 60  0001 C CNN "S1PL"
F 6 "Microchip Technology" H 2650 10850 60  0001 C CNN "MFN"
F 7 "MCP73831T-2ACI/OT" H 2650 10850 60  0001 C CNN "MFP"
	1    2650 10850
	1    0    0    -1  
$EndComp
$Comp
L MICRO-B_USB-RESCUE-nome U7
U 1 1 59EF1058
P 800 11850
F 0 "U7" H 800 11550 50  0000 C CNN
F 1 "MICRO-B_USB" H 800 12150 50  0000 C CNN
F 2 "open-project:MICRO-B_USB" H 800 11850 60  0001 C CNN
F 3 "http://portal.fciconnect.com/Comergent/fci/drawing/10118192.pdf" H 800 11850 60  0001 C CNN
F 4 "609-4613-1-ND" H 800 11850 60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/amphenol-fci/10118192-0001LF/609-4613-1-ND/2785378" H 800 11850 60  0001 C CNN "S1PL"
F 6 "10118192-0001LF" H 800 11850 60  0001 C CNN "MFP"
F 7 "Amphenol FCI" H 800 11850 60  0001 C CNN "MFN"
	1    800  11850
	1    0    0    -1  
$EndComp
$Comp
L C-RESCUE-nome C28
U 1 1 59EF12EB
P 3450 11050
F 0 "C28" H 3475 11150 50  0000 L CNN
F 1 "4.7uF" H 3475 10950 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 3488 10900 50  0001 C CNN
F 3 "http://datasheets.avx.com/cx5r.pdf" H 3450 11050 50  0001 C CNN
F 4 "478-1415-1-ND" H 0   0   60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/avx-corporation/0805ZD475KAT2A/478-1415-1-ND/564447" H 0   0   60  0001 C CNN "S1PL"
F 6 "AVX Corporation" H 0   0   60  0001 C CNN "MFN"
F 7 "0805ZD475KAT2A" H 0   0   60  0001 C CNN "MFP"
	1    3450 11050
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-nome #PWR041
U 1 1 59EF16A2
P 3450 11350
F 0 "#PWR041" H 3450 11100 50  0001 C CNN
F 1 "GND" H 3450 11200 50  0000 C CNN
F 2 "" H 3450 11350 50  0001 C CNN
F 3 "" H 3450 11350 50  0001 C CNN
	1    3450 11350
	1    0    0    -1  
$EndComp
$Comp
L C-RESCUE-nome C29
U 1 1 59EF1FFF
P 3700 11050
F 0 "C29" H 3725 11150 50  0000 L CNN
F 1 "4.7uF" H 3725 10950 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 3738 10900 50  0001 C CNN
F 3 "http://datasheets.avx.com/cx5r.pdf" H 3700 11050 50  0001 C CNN
F 4 "478-1415-1-ND" H 0   0   60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/avx-corporation/0805ZD475KAT2A/478-1415-1-ND/564447" H 0   0   60  0001 C CNN "S1PL"
F 6 "AVX Corporation" H 0   0   60  0001 C CNN "MFN"
F 7 "0805ZD475KAT2A" H 0   0   60  0001 C CNN "MFP"
	1    3700 11050
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-nome #PWR042
U 1 1 59EF2281
P 3700 11350
F 0 "#PWR042" H 3700 11100 50  0001 C CNN
F 1 "GND" H 3700 11200 50  0000 C CNN
F 2 "" H 3700 11350 50  0001 C CNN
F 3 "" H 3700 11350 50  0001 C CNN
	1    3700 11350
	1    0    0    -1  
$EndComp
$Comp
L R-RESCUE-nome R10
U 1 1 59EF248D
P 3200 11100
F 0 "R10" V 3280 11100 50  0000 C CNN
F 1 "4.7k" V 3200 11100 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3130 11100 50  0001 C CNN
F 3 "http://www.yageo.com.tw/exep/pages/download/literatures/PYu-R_INT-thick_7.pdf" H 3200 11100 50  0001 C CNN
F 4 "311-4.70KCRCT-ND" H 0   0   60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/yageo/RC0805FR-074K7L/311-4.70KCRCT-ND/730876" H 0   0   60  0001 C CNN "S1PL"
F 6 "Yageo" H 0   0   60  0001 C CNN "MFN"
F 7 "RC0805FR-074K7L" H 0   0   60  0001 C CNN "MFP"
	1    3200 11100
	-1   0    0    1   
$EndComp
$Comp
L GND-RESCUE-nome #PWR043
U 1 1 59EF0222
P 1200 11400
F 0 "#PWR043" H 1200 11150 50  0001 C CNN
F 1 "GND" H 1200 11250 50  0000 C CNN
F 2 "" H 1200 11400 50  0001 C CNN
F 3 "" H 1200 11400 50  0001 C CNN
	1    1200 11400
	1    0    0    -1  
$EndComp
$Comp
L R-RESCUE-nome R8
U 1 1 59EF4541
P 1950 10950
F 0 "R8" V 2030 10950 50  0000 C CNN
F 1 "470" V 1950 10950 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 1880 10950 50  0001 C CNN
F 3 "http://www.yageo.com.tw/exep/pages/download/literatures/PYu-R_INT-thick_7.pdf" H 1950 10950 50  0001 C CNN
F 4 "311-470ARCT-ND" H 0   0   60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/yageo/RC0805JR-07470RL/311-470ARCT-ND/731280" H 0   0   60  0001 C CNN "S1PL"
F 6 "Yageo" H 0   0   60  0001 C CNN "MFN"
F 7 "RC0805JR-07470RL" H 0   0   60  0001 C CNN "MFP"
	1    1950 10950
	0    1    1    0   
$EndComp
$Comp
L LED-RESCUE-nome D5
U 1 1 59EF45D4
P 1550 10950
F 0 "D5" H 1550 11050 50  0000 C CNN
F 1 "LED Red" H 1550 10850 50  0000 C CNN
F 2 "LEDs:LED_0805_HandSoldering" H 1550 10950 50  0001 C CNN
F 3 "http://optoelectronics.liteon.com/upload/download/DS22-2000-109/LTST-C171KRKT.pdf" H 1550 10950 50  0001 C CNN
F 4 "160-1427-1-ND" H 0   0   60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/lite-on-inc/LTST-C171KRKT/160-1427-1-ND/386800" H 0   0   60  0001 C CNN "S1PL"
F 6 "Lite-On Inc." H 0   0   60  0001 C CNN "MFN"
F 7 "LTST-C171KRK" H 0   0   60  0001 C CNN "MFP"
	1    1550 10950
	-1   0    0    1   
$EndComp
$Comp
L R-RESCUE-nome R9
U 1 1 59EF4E4D
P 1950 11350
F 0 "R9" V 2030 11350 50  0000 C CNN
F 1 "470" V 1950 11350 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 1880 11350 50  0001 C CNN
F 3 "http://www.yageo.com.tw/exep/pages/download/literatures/PYu-R_INT-thick_7.pdf" H 1950 11350 50  0001 C CNN
F 4 "311-470ARCT-ND" H 0   0   60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/yageo/RC0805JR-07470RL/311-470ARCT-ND/731280" H 0   0   60  0001 C CNN "S1PL"
F 6 "Yageo" H 0   0   60  0001 C CNN "MFN"
F 7 "RC0805JR-07470RL" H 0   0   60  0001 C CNN "MFP"
	1    1950 11350
	0    1    1    0   
$EndComp
$Comp
L LED-RESCUE-nome D6
U 1 1 59EF4EDC
P 1550 11350
F 0 "D6" H 1550 11450 50  0000 C CNN
F 1 "LED Green" H 1550 11250 50  0000 C CNN
F 2 "LEDs:LED_0805_HandSoldering" H 1550 11350 50  0001 C CNN
F 3 "https://media.digikey.com/pdf/Data%20Sheets/Lite-On%20PDFs/LTST-C171GKT.pdf" H 1550 11350 50  0001 C CNN
F 4 "160-1423-1-ND" H 0   0   60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/lite-on-inc/LTST-C171GKT/160-1423-1-ND/386792" H 0   0   60  0001 C CNN "S1PL"
F 6 "Lite-On Inc." H 0   0   60  0001 C CNN "MFN"
F 7 "LTST-C171GKT" H 0   0   60  0001 C CNN "MFP"
	1    1550 11350
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-nome #PWR044
U 1 1 59EF50C8
P 1350 11650
F 0 "#PWR044" H 1350 11400 50  0001 C CNN
F 1 "GND" H 1350 11500 50  0000 C CNN
F 2 "" H 1350 11650 50  0001 C CNN
F 3 "" H 1350 11650 50  0001 C CNN
	1    1350 11650
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x02_Female-RESCUE-nome J3
U 1 1 59EF56AB
P 4250 10750
F 0 "J3" H 4250 10850 50  0000 C CNN
F 1 "JST" H 4250 10550 50  0000 C CNN
F 2 "third_party:JST_PH_B2B-PH-SM4-TB_02x2.00mm_Straight" H 4250 10750 50  0001 C CNN
F 3 "http://www.jst-mfg.com/product/pdf/eng/ePH.pdf" H 4250 10750 50  0001 C CNN
F 4 "455-1734-1-ND" H 4250 10750 60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/jst-sales-america-inc/B2B-PH-SM4-TB-LF-SN/455-1734-1-ND/926831" H 4250 10750 60  0001 C CNN "S1PL"
F 6 "JST Sales America Inc." H 4250 10750 60  0001 C CNN "MFN"
F 7 "B2B-PH-SM4-TB(LF)(SN)" H 4250 10750 60  0001 C CNN "MFP"
	1    4250 10750
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-nome #PWR045
U 1 1 59EF7018
P 1000 12350
F 0 "#PWR045" H 1000 12100 50  0001 C CNN
F 1 "GND" H 1000 12200 50  0000 C CNN
F 2 "" H 1000 12350 50  0001 C CNN
F 3 "" H 1000 12350 50  0001 C CNN
	1    1000 12350
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-nome #PWR046
U 1 1 59EF8AD6
P 3200 11350
F 0 "#PWR046" H 3200 11100 50  0001 C CNN
F 1 "GND" H 3200 11200 50  0000 C CNN
F 2 "" H 3200 11350 50  0001 C CNN
F 3 "" H 3200 11350 50  0001 C CNN
	1    3200 11350
	1    0    0    -1  
$EndComp
NoConn ~ 4250 11200
NoConn ~ 1000 11750
NoConn ~ 1000 11850
NoConn ~ 1000 11950
$Comp
L SJ-2524-RESCUE-nome J1
U 1 1 59F00B3E
P 14350 2150
F 0 "J1" H 14350 2440 50  0000 C CNN
F 1 "SJ-2524" H 14200 1950 50  0000 L CNN
F 2 "nome:SJ-2524" H 14600 2250 50  0001 C CNN
F 3 "http://www.cui.com/product/resource/sj-252x-smt-series.pdf" H 14600 2250 50  0001 C CNN
F 4 "CP-2524SJCT-ND" H 14350 2150 60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/cui-inc/SJ-2524-SMT-TR/CP-2524SJCT-ND/669703" H 14350 2150 60  0001 C CNN "S1PL"
F 6 "CUI Inc." H 14350 2150 60  0001 C CNN "MFN"
F 7 "SJ-2524-SMT-TR" H 14350 2150 60  0001 C CNN "MFP"
	1    14350 2150
	-1   0    0    1   
$EndComp
Wire Wire Line
	7450 11450 7750 11450
Connection ~ 3200 11300
Wire Wire Line
	3050 11300 3200 11300
Wire Wire Line
	3050 10950 3050 11300
Wire Wire Line
	3200 11250 3200 11350
Wire Wire Line
	3200 10850 3200 10950
Wire Wire Line
	3450 11350 3450 11200
Connection ~ 3450 10750
Wire Wire Line
	3450 10900 3450 10750
Wire Wire Line
	3050 10850 3200 10850
Connection ~ 3700 10750
Wire Wire Line
	3700 10900 3700 10750
Wire Wire Line
	4050 10850 4050 11200
Connection ~ 4500 10750
Wire Wire Line
	4500 11600 4500 10750
Wire Wire Line
	4650 11600 4500 11600
Connection ~ 4050 10750
Wire Wire Line
	3050 10750 4650 10750
Wire Wire Line
	1800 11350 1700 11350
Wire Wire Line
	1350 11350 1350 11650
Wire Wire Line
	1400 11350 1350 11350
Connection ~ 2150 10950
Wire Wire Line
	2150 11350 2100 11350
Wire Wire Line
	2150 10950 2150 11350
Wire Wire Line
	2100 10950 2250 10950
Wire Wire Line
	1700 10950 1800 10950
Connection ~ 1400 10750
Wire Wire Line
	1400 10950 1400 10750
Connection ~ 1200 10750
Wire Wire Line
	1200 10950 1200 10750
Wire Wire Line
	1200 11400 1200 11250
Wire Wire Line
	1000 11650 1000 10750
Wire Wire Line
	3700 11200 3700 11350
Wire Wire Line
	1000 10750 2250 10750
Wire Wire Line
	1000 12350 1000 12050
Wire Wire Line
	5250 10750 5900 10750
Wire Wire Line
	5250 11600 5800 11600
Wire Wire Line
	4950 11900 4950 12050
Wire Wire Line
	4950 11050 4950 11250
Wire Wire Line
	10300 3150 10300 2600
Connection ~ 13900 2450
Wire Wire Line
	13800 2450 13900 2450
Wire Wire Line
	13400 2450 13500 2450
Wire Wire Line
	13900 1750 13900 2800
Wire Wire Line
	13800 1750 13900 1750
Wire Wire Line
	13400 1750 13500 1750
Connection ~ 9900 1750
Wire Wire Line
	8400 3450 9250 3450
Wire Wire Line
	3400 4750 3400 5300
Wire Wire Line
	10200 3150 10200 2600
Wire Wire Line
	9750 4250 9750 5200
Wire Wire Line
	9650 4250 9650 5200
Connection ~ 9300 5650
Wire Wire Line
	9300 5650 9300 5450
Wire Wire Line
	9300 5450 9550 5450
Wire Wire Line
	9550 5450 9550 4250
Wire Wire Line
	9550 6050 9550 6000
Wire Wire Line
	9550 5650 9550 5700
Connection ~ 9100 6050
Connection ~ 9550 5650
Wire Wire Line
	9850 5650 9850 4250
Connection ~ 9100 5650
Wire Wire Line
	9100 5750 9100 5650
Wire Wire Line
	8700 6050 8700 6150
Wire Wire Line
	8700 6050 9550 6050
Connection ~ 8700 5650
Wire Wire Line
	8700 5650 9850 5650
Wire Wire Line
	8700 5450 8700 5750
Wire Wire Line
	9250 3350 8500 3350
Wire Wire Line
	9250 3250 8500 3250
Wire Wire Line
	3400 2300 3400 3550
Wire Wire Line
	9250 3750 8500 3750
Wire Wire Line
	9250 3550 8500 3550
Wire Wire Line
	13850 1100 13650 1100
Wire Wire Line
	13850 1000 13650 1000
Wire Wire Line
	10550 5300 10550 5500
Wire Wire Line
	10550 5900 10550 5800
Connection ~ 10550 5300
Wire Wire Line
	12150 5900 10550 5900
Wire Wire Line
	12150 3450 12150 5900
Wire Wire Line
	10400 3450 12150 3450
Wire Wire Line
	10200 5500 10200 5300
Wire Wire Line
	10200 6050 10200 5800
Connection ~ 10200 5300
Wire Wire Line
	12350 6050 10200 6050
Wire Wire Line
	12350 3550 12350 6050
Wire Wire Line
	10400 3550 12350 3550
Wire Wire Line
	10800 4800 10800 4950
Wire Wire Line
	10800 5300 10800 5250
Connection ~ 10800 5300
Wire Wire Line
	10150 4800 10800 4800
Wire Wire Line
	10150 4250 10150 4800
Connection ~ 11400 5300
Wire Wire Line
	11400 5300 11400 5200
Wire Wire Line
	10050 4900 11400 4900
Wire Wire Line
	10050 4250 10050 4900
Wire Wire Line
	11900 5300 11900 5550
Wire Wire Line
	9950 5300 11900 5300
Wire Wire Line
	9950 4250 9950 5300
Connection ~ 7500 3650
Wire Wire Line
	7500 3750 7500 3650
Connection ~ 7900 2900
Wire Wire Line
	8350 3650 9250 3650
Wire Wire Line
	8350 2900 8350 3650
Wire Wire Line
	8200 3950 9250 3950
Wire Wire Line
	8200 3650 8200 3950
Wire Wire Line
	7150 3650 8200 3650
Wire Wire Line
	7700 2900 8350 2900
Connection ~ 7900 3650
Wire Wire Line
	7150 3650 7150 3350
Connection ~ 7700 3650
Wire Wire Line
	7700 3650 7700 2900
Wire Wire Line
	7900 3200 7900 3400
Wire Wire Line
	7900 4100 7900 4350
Wire Wire Line
	7900 3650 7900 3800
Wire Wire Line
	7500 4050 7500 4150
Connection ~ 11150 2950
Connection ~ 11150 2450
Wire Wire Line
	11150 2850 11150 3100
Wire Wire Line
	10700 2950 11150 2950
Wire Wire Line
	10700 2850 10700 2950
Connection ~ 10700 2450
Wire Wire Line
	10700 2450 10700 2550
Wire Wire Line
	11150 2250 11150 2550
Wire Wire Line
	10100 2450 11150 2450
Wire Wire Line
	10100 3150 10100 2450
Connection ~ 10250 1800
Wire Wire Line
	10250 2150 10250 2250
Wire Wire Line
	10250 1650 10250 1850
Wire Wire Line
	10000 1800 10250 1800
Wire Wire Line
	10000 3150 10000 1800
Wire Wire Line
	9900 1100 9900 3150
Wire Wire Line
	9900 1100 10100 1100
Wire Wire Line
	10100 1100 10100 1300
Wire Wire Line
	8150 4150 8150 4350
Wire Wire Line
	9250 4150 8150 4150
Wire Wire Line
	9450 5100 9450 4250
Wire Wire Line
	9050 5100 9450 5100
Wire Wire Line
	9350 4800 9050 4800
Wire Wire Line
	9350 4250 9350 4800
Wire Wire Line
	2500 9750 2850 9750
Wire Wire Line
	2500 9650 3050 9650
Wire Wire Line
	2500 9550 2850 9550
Wire Wire Line
	1900 9750 1600 9750
Wire Wire Line
	1900 9550 1600 9550
Wire Wire Line
	4150 11750 4150 11600
Wire Wire Line
	1450 2650 2050 2650
Wire Wire Line
	1450 4400 1450 2650
Wire Wire Line
	3100 4400 1450 4400
Wire Wire Line
	1750 4300 3100 4300
Wire Wire Line
	2050 3400 1750 3400
Connection ~ 2050 3400
Connection ~ 2050 2650
Connection ~ 1750 2650
Connection ~ 1750 3400
Wire Wire Line
	3200 1300 4000 1300
Wire Wire Line
	4000 1800 3300 1800
Wire Wire Line
	3200 3550 3200 1300
Wire Wire Line
	3300 1800 3300 3550
Connection ~ 4000 1800
Connection ~ 4000 1300
Connection ~ 3650 1300
Connection ~ 3650 1800
Connection ~ 5500 4050
Connection ~ 5500 3600
Wire Wire Line
	5100 3700 4400 3700
Wire Wire Line
	5100 4050 5100 3700
Wire Wire Line
	5500 4050 5100 4050
Wire Wire Line
	4400 3600 5500 3600
Connection ~ 4700 5750
Connection ~ 4700 5300
Wire Wire Line
	4300 5300 4300 4750
Wire Wire Line
	4700 5300 4300 5300
Wire Wire Line
	4200 5750 4700 5750
Wire Wire Line
	4200 4750 4200 5750
Wire Wire Line
	9400 3150 9400 2650
Wire Wire Line
	3300 4750 3300 5300
Wire Wire Line
	9500 3150 9500 2650
Wire Wire Line
	3900 3550 3900 2950
Wire Wire Line
	9600 3150 9600 2650
Wire Wire Line
	4400 4700 4950 4700
Wire Wire Line
	9700 3150 9700 2650
Wire Wire Line
	4000 4750 4000 5300
Wire Wire Line
	3200 4750 3200 5300
Wire Wire Line
	3100 4700 2400 4700
Wire Wire Line
	3100 4600 2400 4600
Wire Wire Line
	4000 7000 9300 7000
Wire Wire Line
	9300 7000 9300 7850
Wire Wire Line
	4000 7100 9400 7100
Wire Wire Line
	9400 7100 9400 7950
Wire Wire Line
	4000 7200 9500 7200
Wire Wire Line
	9500 7200 9500 8050
Wire Wire Line
	4000 7300 9650 7300
Wire Wire Line
	9650 7300 9650 8150
Wire Wire Line
	4000 7400 9750 7400
Wire Wire Line
	9750 7400 9750 8250
Wire Wire Line
	4000 7800 6150 7800
Wire Wire Line
	4000 7900 6150 7900
Wire Wire Line
	4000 8100 6150 8100
Wire Wire Line
	4000 8200 6150 8200
Wire Wire Line
	4000 8300 6150 8300
Wire Wire Line
	4000 8400 6150 8400
Wire Wire Line
	4000 8500 6150 8500
Wire Wire Line
	9300 7850 8250 7850
Wire Wire Line
	9400 7950 8250 7950
Wire Wire Line
	9500 8050 8250 8050
Wire Wire Line
	9650 8150 8250 8150
Wire Wire Line
	9750 8250 8250 8250
Wire Wire Line
	3550 8600 3550 9200
Wire Wire Line
	3200 7100 2750 7100
Wire Wire Line
	1450 7000 3200 7000
Wire Wire Line
	2450 7100 2400 7100
Wire Wire Line
	2400 7100 2400 7000
Connection ~ 2400 7000
Wire Wire Line
	1900 7300 3200 7300
Wire Wire Line
	4000 8000 6150 8000
Wire Wire Line
	1450 6800 1450 7650
Wire Wire Line
	1450 8800 3550 8800
Connection ~ 3550 8800
Connection ~ 1450 7000
Wire Wire Line
	1450 8800 1450 7950
Wire Wire Line
	3400 2300 3750 2300
Wire Wire Line
	3400 2450 3750 2450
Connection ~ 3400 2450
Wire Wire Line
	4000 2550 4000 2200
Wire Wire Line
	4000 2200 4450 2200
Wire Wire Line
	4200 2200 4200 2050
Wire Wire Line
	4200 2050 4450 2050
Connection ~ 4200 2200
Wire Wire Line
	10900 8300 10900 8100
Wire Wire Line
	11200 8300 11200 8100
Wire Wire Line
	11500 8300 11500 8100
Wire Wire Line
	11800 8300 11800 8100
Wire Wire Line
	4400 4100 5050 4100
Wire Wire Line
	4400 4200 5050 4200
Wire Wire Line
	4400 4300 5050 4300
Wire Wire Line
	10900 8600 10900 8750
Wire Wire Line
	11200 8600 11200 8750
Wire Wire Line
	11800 8600 11800 8750
Wire Wire Line
	11500 8600 11500 8750
Wire Wire Line
	10900 9050 10900 9200
Wire Wire Line
	11200 9050 11200 9200
Wire Wire Line
	11500 9050 11500 9200
Wire Wire Line
	11800 9050 11800 9200
Wire Wire Line
	1900 7400 3200 7400
Wire Wire Line
	4000 2550 3800 2550
Wire Wire Line
	3800 2550 3800 3550
Wire Wire Line
	3600 3550 3600 2700
Wire Wire Line
	4400 3800 5050 3800
Wire Wire Line
	4300 2850 4300 3550
Wire Wire Line
	4200 3550 4200 2850
Wire Wire Line
	4100 3550 4100 2850
Wire Wire Line
	4000 3550 4000 2850
Wire Wire Line
	7450 11050 7750 11050
Wire Wire Line
	7450 11150 7750 11150
Wire Wire Line
	7450 11250 7750 11250
Wire Wire Line
	7450 11350 7750 11350
Wire Wire Line
	6600 11150 6950 11150
Wire Wire Line
	6600 11150 6600 11250
Wire Wire Line
	6950 11050 6600 11050
Wire Wire Line
	6600 11050 6600 10850
Wire Wire Line
	3100 4200 2050 4200
Wire Wire Line
	4100 5850 4700 5850
Connection ~ 4700 5850
Wire Wire Line
	4100 4750 4100 5550
Wire Wire Line
	3100 3600 2500 3600
Wire Wire Line
	2500 3600 2500 3350
Wire Wire Line
	6950 11250 6800 11250
Wire Wire Line
	6800 11250 6800 11150
Connection ~ 6800 11150
Wire Wire Line
	6950 11450 6700 11450
Wire Wire Line
	6700 11450 6700 11150
Connection ~ 6700 11150
Wire Wire Line
	2000 7000 2000 7200
Wire Wire Line
	2000 7200 1900 7200
Connection ~ 2000 7000
Wire Wire Line
	1900 7500 2000 7500
Wire Wire Line
	2000 7500 2000 8800
Connection ~ 2000 8800
$Comp
L GND-RESCUE-nome #PWR047
U 1 1 59F01205
P 14750 2200
F 0 "#PWR047" H 14750 1950 50  0001 C CNN
F 1 "GND" H 14750 2050 50  0000 C CNN
F 2 "" H 14750 2200 50  0001 C CNN
F 3 "" H 14750 2200 50  0001 C CNN
	1    14750 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	14550 1950 14750 1950
Wire Wire Line
	14750 1950 14750 2200
Wire Wire Line
	14150 2150 13950 2150
Text Label 14050 2150 2    60   ~ 0
SPKR_HP
Wire Wire Line
	12850 2250 14150 2250
Connection ~ 13100 2250
Wire Wire Line
	13100 2250 13100 2450
Wire Wire Line
	12850 2050 14150 2050
Connection ~ 13100 2050
Wire Wire Line
	13100 2050 13100 1750
Text Notes 11450 13000 0    60   ~ 0
Nome metronome
Text Notes 12250 13150 0    60   ~ 0
10/24/17
Text Notes 14650 13150 0    60   ~ 0
A
Wire Wire Line
	4000 1400 4000 1100
Wire Wire Line
	4000 1700 4000 1950
Wire Wire Line
	3650 1400 3650 1300
Wire Wire Line
	3650 1700 3650 1800
Wire Wire Line
	1750 2650 1750 2900
Wire Wire Line
	1750 3400 1750 3200
Wire Wire Line
	2050 2350 2050 2900
Wire Wire Line
	2050 3200 2050 3650
$Comp
L C-RESCUE-nome C7
U 1 1 59E789E3
P 5500 3850
F 0 "C7" H 5525 3950 50  0000 L CNN
F 1 "0.1uF" H 5525 3750 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 5538 3700 50  0001 C CNN
F 3 "http://datasheets.avx.com/X7RDielectric.pdf" H 5500 3850 50  0001 C CNN
F 4 "478-1395-1-ND" H 0   0   60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/avx-corporation/08055C104KAT2A/478-1395-1-ND/564427" H 0   0   60  0001 C CNN "S1PL"
F 6 "AVX Corporation" H 0   0   60  0001 C CNN "MFN"
F 7 "08055C104KAT2A" H 0   0   60  0001 C CNN "MFP"
	1    5500 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 3700 5500 3400
Wire Wire Line
	5500 4000 5500 4250
Wire Wire Line
	4700 5100 4700 5350
Wire Wire Line
	4700 5650 4700 5900
Wire Wire Line
	1750 4300 1750 3600
Wire Wire Line
	1750 3600 2050 3600
Connection ~ 2050 3600
Wire Wire Line
	8150 4650 8150 4800
Text Label 3600 2850 0    60   ~ 0
GND
Wire Wire Line
	8400 3450 8400 2750
Wire Wire Line
	8400 2750 8600 2750
Wire Wire Line
	8600 2750 8600 2900
$Comp
L GND-RESCUE-nome #PWR048
U 1 1 59F27A93
P 8600 2900
F 0 "#PWR048" H 8600 2650 50  0001 C CNN
F 1 "GND" H 8605 2727 50  0000 C CNN
F 2 "" H 8600 2900 50  0001 C CNN
F 3 "" H 8600 2900 50  0001 C CNN
	1    8600 2900
	1    0    0    -1  
$EndComp
$EndSCHEMATC
