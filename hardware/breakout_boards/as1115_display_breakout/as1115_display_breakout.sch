EESchema Schematic File Version 4
LIBS:as1115_display_breakout-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
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
$Comp
L custom_ic:AS1115 U1
U 1 1 59EC3D68
P 4350 2750
F 0 "U1" H 4300 2900 60  0000 C CNN
F 1 "AS1115" H 4300 2750 60  0000 C CNN
F 2 "Housings_SSOP:QSOP-24_3.9x8.7mm_Pitch0.635mm" H 4300 2750 60  0001 C CNN
F 3 "http://ams.com/eng/content/download/18430/343782" H 4300 2750 60  0001 C CNN
F 4 "AS1115-BSSTCT-ND" H 4350 2750 60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/ams/AS1115-BSST/AS1115-BSSTCT-ND/2469597" H 4350 2750 60  0001 C CNN "S1PL"
F 6 "ams" H 4350 2750 60  0001 C CNN "MFN"
F 7 "AS1115-BSST" H 4350 2750 60  0001 C CNN "MFP"
	1    4350 2750
	1    0    0    -1  
$EndComp
NoConn ~ 8650 4100
NoConn ~ 8750 4100
NoConn ~ 8850 4100
$Comp
L power:GND #PWR02
U 1 1 59EC6122
P 4300 4650
F 0 "#PWR02" H 4300 4400 50  0001 C CNN
F 1 "GND" H 4300 4500 50  0000 C CNN
F 2 "" H 4300 4650 50  0001 C CNN
F 3 "" H 4300 4650 50  0001 C CNN
	1    4300 4650
	1    0    0    -1  
$EndComp
$Comp
L device:R R1
U 1 1 59EC64B4
P 3350 2550
F 0 "R1" V 3430 2550 50  0000 C CNN
F 1 "10k" V 3350 2550 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3280 2550 50  0001 C CNN
F 3 "http://www.yageo.com.tw/exep/pages/download/literatures/PYu-R_INT-thick_7.pdf" H 3350 2550 50  0001 C CNN
F 4 "311-10KARCT-ND" H 750 -4550 60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/yageo/RC0805JR-0710KL/311-10KARCT-ND/731188" H 750 -4550 60  0001 C CNN "S1PL"
F 6 "Yageo" H 750 -4550 60  0001 C CNN "MFN"
F 7 "RC0805JR-0710KL" H 750 -4550 60  0001 C CNN "MFP"
	1    3350 2550
	0    -1   -1   0   
$EndComp
NoConn ~ 3750 3500
NoConn ~ 3950 3100
NoConn ~ 3950 3200
$Comp
L custom_display:LTC-4727JS U2
U 1 1 59EC78C2
P 7900 3600
F 0 "U2" H 6950 4050 50  0000 C CNN
F 1 "LTC-4727JS" H 8670 4050 50  0000 C CNN
F 2 "custom_display:LTC-4727" H 7900 3000 50  0001 C CNN
F 3 "https://media.digikey.com/pdf/Data%20Sheets/Lite-On%20PDFs/LTC-4727JS.pdf" H 7520 3630 50  0001 C CNN
F 4 "160-1547-5-ND" H 7900 3600 60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/lite-on-inc/LTC-4727JS/160-1547-5-ND/408220" H 7900 3600 60  0001 C CNN "S1PL"
F 6 "Lite-On Inc." H 7900 3600 60  0001 C CNN "MFN"
F 7 "LTC-4727JS" H 7900 3600 60  0001 C CNN "MFP"
	1    7900 3600
	1    0    0    -1  
$EndComp
$Comp
L device:C C1
U 1 1 59EC7FF1
P 2200 3250
F 0 "C1" H 2225 3350 50  0000 L CNN
F 1 "0.1uF" H 2225 3150 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 2238 3100 50  0001 C CNN
F 3 "http://datasheets.avx.com/X7RDielectric.pdf" H 2200 3250 50  0001 C CNN
F 4 "478-1395-1-ND" H 750 -4550 60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/avx-corporation/08055C104KAT2A/478-1395-1-ND/564427" H 750 -4550 60  0001 C CNN "S1PL"
F 6 "AVX Corporation" H 750 -4550 60  0001 C CNN "MFN"
F 7 "08055C104KAT2A" H 750 -4550 60  0001 C CNN "MFP"
	1    2200 3250
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR01
U 1 1 59EC8828
P 2200 2250
F 0 "#PWR01" H 2200 2100 50  0001 C CNN
F 1 "+3V3" H 2200 2390 50  0000 C CNN
F 2 "" H 2200 2250 50  0001 C CNN
F 3 "" H 2200 2250 50  0001 C CNN
	1    2200 2250
	1    0    0    -1  
$EndComp
NoConn ~ 4750 2950
NoConn ~ 4750 3050
NoConn ~ 4750 3150
Text Label 2950 2750 0    60   ~ 0
7SEG_SDA
Text Label 2950 2850 0    60   ~ 0
7SEG_SCL
Text Notes 10900 7650 0    60   ~ 12
Status LED
$Comp
L Connector:Conn_01x04 J1
U 1 1 59EEB3FD
P 2450 2850
F 0 "J1" H 2450 3050 50  0000 C CNN
F 1 "7SEG_DEBUG" H 2450 2550 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm" H 2450 2850 50  0001 C CNN
F 3 "https://cdn.harwin.com/pdfs/Harwin_Product_Catalog_page_208.pdf" H 2450 2850 50  0001 C CNN
F 4 "952-2265-ND" H 2450 2850 60  0001 C CNN "S1PN"
F 5 "https://www.digikey.com/product-detail/en/harwin-inc/M20-9990445/952-2265-ND/3728229" H 2450 2850 60  0001 C CNN "S1PL"
F 6 "Harwin Inc." H 2450 2850 60  0001 C CNN "MFN"
F 7 "M20-9990445" H 2450 2850 60  0001 C CNN "MFP"
	1    2450 2850
	-1   0    0    1   
$EndComp
Wire Wire Line
	9900 1100 10100 1100
Wire Wire Line
	4750 2450 10050 2450
Wire Wire Line
	10050 2450 10050 3300
Wire Wire Line
	4750 2550 10150 2550
Wire Wire Line
	10150 2550 10150 3400
Wire Wire Line
	4750 2650 10250 2650
Wire Wire Line
	10250 2650 10250 3500
Wire Wire Line
	4750 2750 10400 2750
Wire Wire Line
	10400 2750 10400 3600
Wire Wire Line
	4750 2850 10500 2850
Wire Wire Line
	10500 2850 10500 3700
Wire Wire Line
	4750 3250 6900 3250
Wire Wire Line
	4750 3350 6900 3350
Wire Wire Line
	4750 3550 6900 3550
Wire Wire Line
	4750 3650 6900 3650
Wire Wire Line
	4750 3750 6900 3750
Wire Wire Line
	4750 3850 6900 3850
Wire Wire Line
	4750 3950 6900 3950
Wire Wire Line
	10050 3300 9000 3300
Wire Wire Line
	10150 3400 9000 3400
Wire Wire Line
	10250 3500 9000 3500
Wire Wire Line
	10400 3600 9000 3600
Wire Wire Line
	10500 3700 9000 3700
Wire Wire Line
	4300 4050 4300 4650
Wire Wire Line
	3950 2550 3500 2550
Wire Wire Line
	2200 2450 3950 2450
Wire Wire Line
	3200 2550 3150 2550
Wire Wire Line
	3150 2550 3150 2450
Connection ~ 3150 2450
Wire Wire Line
	2650 2750 3950 2750
Wire Wire Line
	4750 3450 6900 3450
Wire Wire Line
	2200 2250 2200 3100
Wire Wire Line
	2200 4250 4300 4250
Connection ~ 4300 4250
Connection ~ 2200 2450
Wire Wire Line
	2200 4250 2200 3400
Wire Wire Line
	2650 2850 3950 2850
Wire Wire Line
	2750 2450 2750 2650
Wire Wire Line
	2750 2650 2650 2650
Connection ~ 2750 2450
Wire Wire Line
	2650 2950 2750 2950
Wire Wire Line
	2750 2950 2750 4250
Connection ~ 2750 4250
Text Notes 14650 13150 0    60   ~ 0
A
$EndSCHEMATC
