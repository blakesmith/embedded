EESchema Schematic File Version 4
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
EELAYER 26 0
EELAYER END
$Descr A2 23386 16535
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
L MCU_ST_STM32F4:STM32F429ZITx U?
U 1 1 5B78632B
P 7050 4950
F 0 "U?" H 7050 1264 50  0000 C CNN
F 1 "STM32F429ZITx" H 7050 1173 50  0000 C CNN
F 2 "Package_QFP:LQFP-144_20x20mm_P0.5mm" H 6050 1550 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00071990.pdf" H 7050 4950 50  0001 C CNN
	1    7050 4950
	1    0    0    -1  
$EndComp
$Comp
L Memory_RAM:IS42S16400J-xT U?
U 1 1 5B786488
P 12200 2750
F 0 "U?" H 12200 4328 50  0000 C CNN
F 1 "IS42S16400J-xT" H 12200 4237 50  0000 C CNN
F 2 "Package_SO:TSOP-II-54_10.16x22.22mm_P0.8mm" H 12200 2750 50  0001 C CNN
F 3 "http://www.issi.com/WW/pdf/42-45S16400J.pdf" H 11600 4000 50  0001 C CNN
	1    12200 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	11400 1850 11150 1850
Text Label 11150 1850 2    50   ~ 0
ADDR_0
Wire Wire Line
	11400 1950 11150 1950
Text Label 11150 1950 2    50   ~ 0
ADDR_1
Wire Wire Line
	11150 2050 11400 2050
Text Label 11150 2050 2    50   ~ 0
ADDR_2
Wire Wire Line
	11400 2150 11150 2150
Text Label 11150 2150 2    50   ~ 0
ADDR_3
Wire Wire Line
	11400 2250 11150 2250
Text Label 11150 2250 2    50   ~ 0
ADDR_4
Wire Wire Line
	11400 2350 11150 2350
Text Label 11150 2350 2    50   ~ 0
ADDR_5
Wire Wire Line
	11400 2450 11150 2450
Text Label 11150 2450 2    50   ~ 0
ADDR_6
Wire Wire Line
	11400 2550 11150 2550
Text Label 11150 2550 2    50   ~ 0
ADDR_7
Wire Wire Line
	11400 2650 11150 2650
Text Label 11150 2650 2    50   ~ 0
ADDR_8
Wire Wire Line
	11400 2750 11150 2750
Text Label 11150 2750 2    50   ~ 0
ADDR_9
Wire Wire Line
	11400 2850 11150 2850
Text Label 11150 2850 2    50   ~ 0
ADDR_10
Wire Wire Line
	11400 2950 11150 2950
Text Label 11150 2950 2    50   ~ 0
ADDR_11
Wire Wire Line
	5850 5050 5650 5050
Text Label 5650 5050 2    50   ~ 0
ADDR_0
Wire Wire Line
	5850 5150 5650 5150
Text Label 5650 5150 2    50   ~ 0
ADDR_1
Wire Wire Line
	5850 5250 5650 5250
Text Label 5650 5250 2    50   ~ 0
ADDR_2
Wire Wire Line
	5850 5350 5650 5350
Text Label 5650 5350 2    50   ~ 0
ADDR_3
Wire Wire Line
	5850 5450 5650 5450
Text Label 5650 5450 2    50   ~ 0
ADDR_4
Wire Wire Line
	5850 5550 5650 5550
Text Label 5650 5550 2    50   ~ 0
ADDR_5
Wire Wire Line
	5850 6250 5650 6250
Text Label 5650 6250 2    50   ~ 0
ADDR_6
Wire Wire Line
	5850 6350 5650 6350
Text Label 5650 6350 2    50   ~ 0
ADDR_7
Wire Wire Line
	5850 6450 5650 6450
Text Label 5650 6450 2    50   ~ 0
ADDR_8
Wire Wire Line
	5850 6550 5650 6550
Text Label 5650 6550 2    50   ~ 0
ADDR_9
Wire Wire Line
	5850 3350 5650 3350
Text Label 5650 3350 2    50   ~ 0
ADDR_10
Wire Wire Line
	5850 3450 5650 3450
Text Label 5650 3450 2    50   ~ 0
ADDR_11
Wire Wire Line
	13000 1650 13250 1650
Text Label 13250 1650 0    50   ~ 0
DATA_0
Wire Wire Line
	13000 1750 13250 1750
Text Label 13250 1750 0    50   ~ 0
DATA_1
Wire Wire Line
	13000 1850 13250 1850
Text Label 13250 1850 0    50   ~ 0
DATA_2
Wire Wire Line
	13000 1950 13250 1950
Text Label 13250 1950 0    50   ~ 0
DATA_3
Wire Wire Line
	13000 2050 13250 2050
Text Label 13250 2050 0    50   ~ 0
DATA_4
Wire Wire Line
	13000 2150 13250 2150
Text Label 13250 2150 0    50   ~ 0
DATA_5
Wire Wire Line
	13000 2250 13250 2250
Text Label 13250 2250 0    50   ~ 0
DATA_6
Wire Wire Line
	13000 2350 13250 2350
Text Label 13250 2350 0    50   ~ 0
DATA_7
Wire Wire Line
	13000 2450 13250 2450
Text Label 13250 2450 0    50   ~ 0
DATA_8
Wire Wire Line
	13000 2550 13250 2550
Text Label 13250 2550 0    50   ~ 0
DATA_9
Wire Wire Line
	13000 2650 13250 2650
Text Label 13250 2650 0    50   ~ 0
DATA_10
Wire Wire Line
	13000 2750 13250 2750
Text Label 13250 2750 0    50   ~ 0
DATA_11
Wire Wire Line
	13000 2850 13250 2850
Text Label 13250 2850 0    50   ~ 0
DATA_12
Wire Wire Line
	13000 2950 13250 2950
Text Label 13250 2950 0    50   ~ 0
DATA_13
Wire Wire Line
	13000 3050 13250 3050
Text Label 13250 3050 0    50   ~ 0
DATA_14
Wire Wire Line
	13000 3150 13250 3150
Text Label 13250 3150 0    50   ~ 0
DATA_15
Wire Wire Line
	8250 8150 8500 8150
Text Label 8500 8150 0    50   ~ 0
DATA_0
Wire Wire Line
	8250 8250 8500 8250
Text Label 8500 8250 0    50   ~ 0
DATA_1
Wire Wire Line
	8250 6750 8500 6750
Text Label 8500 6750 0    50   ~ 0
DATA_2
Wire Wire Line
	8250 6850 8500 6850
Text Label 8500 6850 0    50   ~ 0
DATA_3
Wire Wire Line
	5850 7450 5550 7450
Text Label 5550 7450 2    50   ~ 0
DATA_4
Wire Wire Line
	5850 7550 5550 7550
Text Label 5550 7550 2    50   ~ 0
DATA_5
Wire Wire Line
	5850 7650 5550 7650
Text Label 5550 7650 2    50   ~ 0
DATA_6
Wire Wire Line
	5850 7750 5550 7750
Text Label 5550 7750 2    50   ~ 0
DATA_7
Wire Wire Line
	5850 7850 5550 7850
Text Label 5550 7850 2    50   ~ 0
DATA_8
Wire Wire Line
	5850 7950 5550 7950
Text Label 5550 7950 2    50   ~ 0
DATA_9
Wire Wire Line
	5850 8050 5550 8050
Text Label 5550 8050 2    50   ~ 0
DATA_10
Wire Wire Line
	5850 8150 5550 8150
Text Label 5550 8150 2    50   ~ 0
DATA_11
Wire Wire Line
	5850 8250 5550 8250
Text Label 5550 8250 2    50   ~ 0
DATA_12
Wire Wire Line
	8250 7550 8500 7550
Text Label 8500 7550 0    50   ~ 0
DATA_13
Wire Wire Line
	8250 7650 8500 7650
Text Label 8500 7650 0    50   ~ 0
DATA_14
Wire Wire Line
	8250 7750 8500 7750
Text Label 8500 7750 0    50   ~ 0
DATA_15
$EndSCHEMATC
