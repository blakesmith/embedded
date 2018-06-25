EESchema Schematic File Version 4
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
L MCU_ST_STM32F0:STM32F042K6Tx U?
U 1 1 5B304C68
P 5500 3200
F 0 "U?" H 5500 2114 50  0000 C CNN
F 1 "STM32F042K6Tx" H 5500 2023 50  0000 C CNN
F 2 "Package_QFP:LQFP-32_7x7mm_P0.8mm" H 5100 2300 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00105814.pdf" H 5500 3200 50  0001 C CNN
	1    5500 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 4200 5400 4300
Wire Wire Line
	5400 4300 5450 4300
Wire Wire Line
	5500 4300 5500 4200
Wire Wire Line
	5450 4300 5450 4500
Connection ~ 5450 4300
Wire Wire Line
	5450 4300 5500 4300
$Comp
L power:GND #PWR?
U 1 1 5B304DF2
P 5450 4500
F 0 "#PWR?" H 5450 4250 50  0001 C CNN
F 1 "GND" H 5455 4327 50  0000 C CNN
F 2 "" H 5450 4500 50  0001 C CNN
F 3 "" H 5450 4500 50  0001 C CNN
	1    5450 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 2300 5600 2200
Wire Wire Line
	5600 2200 5500 2200
Wire Wire Line
	5500 2200 5500 2300
Wire Wire Line
	5400 2300 5400 2200
Wire Wire Line
	5400 2200 5500 2200
Connection ~ 5500 2200
Wire Wire Line
	5500 2200 5500 2050
$Comp
L power:+3.3V #PWR?
U 1 1 5B304F70
P 5500 2050
F 0 "#PWR?" H 5500 1900 50  0001 C CNN
F 1 "+3.3V" H 5515 2223 50  0000 C CNN
F 2 "" H 5500 2050 50  0001 C CNN
F 3 "" H 5500 2050 50  0001 C CNN
	1    5500 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 3800 6200 3800
Text Label 6200 3800 0    50   ~ 0
SWDIO
Wire Wire Line
	6000 3900 6200 3900
Text Label 6200 3900 0    50   ~ 0
SWCLK
$Comp
L Connector:USB_B_Micro J?
U 1 1 5B305155
P 7600 3700
F 0 "J?" H 7371 3598 50  0000 R CNN
F 1 "USB_B_Micro" H 7371 3689 50  0000 R CNN
F 2 "" H 7750 3650 50  0001 C CNN
F 3 "~" H 7750 3650 50  0001 C CNN
	1    7600 3700
	-1   0    0    1   
$EndComp
Wire Wire Line
	6000 3600 7300 3600
Wire Wire Line
	6000 3700 7300 3700
NoConn ~ 7700 3300
Wire Wire Line
	7600 3300 7600 3100
Wire Wire Line
	7600 3100 8000 3100
Wire Wire Line
	8000 3100 8000 3200
$Comp
L power:GND #PWR?
U 1 1 5B3057C1
P 8000 3200
F 0 "#PWR?" H 8000 2950 50  0001 C CNN
F 1 "GND" H 8005 3027 50  0000 C CNN
F 2 "" H 8000 3200 50  0001 C CNN
F 3 "" H 8000 3200 50  0001 C CNN
	1    8000 3200
	1    0    0    -1  
$EndComp
Text Label 6950 3900 0    50   ~ 0
VBUS
Wire Wire Line
	6950 3900 7300 3900
NoConn ~ 7300 3500
Text Label 4700 3600 0    50   ~ 0
ROW1
Text Label 4700 3700 0    50   ~ 0
ROW2
Wire Wire Line
	6000 2500 6150 2500
Text Label 6150 2500 0    50   ~ 0
COL0
Wire Wire Line
	6000 2600 6150 2600
Text Label 6150 2600 0    50   ~ 0
COL1
Wire Wire Line
	6000 2700 6150 2700
Text Label 6150 2700 0    50   ~ 0
COL2
Wire Wire Line
	6000 2800 6150 2800
Text Label 6150 2800 0    50   ~ 0
COL3
Wire Wire Line
	6000 2900 6150 2900
Text Label 6150 2900 0    50   ~ 0
COL4
Wire Wire Line
	6000 3000 6150 3000
Text Label 6150 3000 0    50   ~ 0
COL5
Wire Wire Line
	6000 3100 6150 3100
Text Label 6150 3100 0    50   ~ 0
COL6
Wire Wire Line
	6000 3200 6150 3200
Text Label 6150 3200 0    50   ~ 0
COL7
Wire Wire Line
	6000 3300 6150 3300
Text Label 6150 3300 0    50   ~ 0
COL10
Wire Wire Line
	6000 3400 6150 3400
Text Label 6150 3400 0    50   ~ 0
COL11
Wire Wire Line
	6000 3500 6150 3500
Text Label 6150 3500 0    50   ~ 0
COL12
Wire Wire Line
	6000 4000 6150 4000
Text Label 6150 4000 0    50   ~ 0
COL11
Text Label 4700 3800 0    50   ~ 0
ROW3
Text Label 4700 3900 0    50   ~ 0
ROW4
Wire Wire Line
	4700 3300 5000 3300
Wire Wire Line
	4700 3400 5000 3400
Wire Wire Line
	4700 3500 5000 3500
Wire Wire Line
	4700 3600 5000 3600
Wire Wire Line
	4700 3700 5000 3700
Wire Wire Line
	4700 3800 5000 3800
Wire Wire Line
	4700 3900 5000 3900
NoConn ~ 5000 2500
NoConn ~ 5000 3000
NoConn ~ 5000 3100
NoConn ~ 5000 4000
Text Label 4700 3300 0    50   ~ 0
COL8
Text Label 4700 3400 0    50   ~ 0
COL9
Text Label 4700 3500 0    50   ~ 0
ROW0
$EndSCHEMATC
