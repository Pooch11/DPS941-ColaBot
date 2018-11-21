
#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    clawLimit,      sensorPotentiometer)
#pragma config(Sensor, in2,    lineRIGHT,      sensorReflection)
#pragma config(Sensor, in3,    lineFollowerCENTER, sensorLineFollower)
#pragma config(Sensor, in4,    lineLEFT,       sensorReflection)
#pragma config(Sensor, in5,    lineFollowerRIGHT, sensorLineFollower)
#pragma config(Sensor, in6,    lineFollowerLEFT, sensorLineFollower)
#pragma config(Sensor, dgtl6,  sonarSensor,    sensorSONAR_cm)
#pragma config(Sensor, dgtl8,  LIMITSWITCHRIGHT, sensorTouch)
#pragma config(Sensor, dgtl9,  LIMITSWITCHLEFT, sensorTouch)
#pragma config(Sensor, dgtl10, Bumper,         sensorTouch)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           rightMotor,    tmotorVex393HighSpeed_HBridge, PIDControl, encoderPort, I2C_2)
#pragma config(Motor,  port2,           armMotor,      tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port3,           clawMotor,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port10,          leftMotor,     tmotorVex393HighSpeed_HBridge, PIDControl, reversed, encoderPort, I2C_1)
#pragma config(UART_Usage, UART1, uartUserControl, baudRate115200, IOPins, None, None)
#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//



//BB-UART Serial Information
#define PORT "/dev/ttyO4"
#define BAUDRATE B115200

struct Data
{
	short SonarValue;
	short ArmValue;
	bool Drive;
	bool ArmDown;
	bool ClawClosed;
	int Batt;
};

char value;

Data TxPkt;
task UARTRx() {
	//Receiving Data
	int rcvChar;		//Variable to hold the reciving byte data

	while (true)
	{
		rcvChar = getChar(uartOne);
		if (rcvChar != '1')
		{
			// No character available
	 		wait1Msec(3);
	 		continue;
		}
		if(rcvChar == '1' && TxPkt.Drive == false)
		{
			TxPkt.Drive = true;
			motor[leftMotor] = 35;
			motor[rightMotor] = 35;
		} else if (rcvChar == '1' && TxPkt.Drive == true) {
				TxPkt.Drive = false;
			motor[leftMotor] = 0;
			motor[rightMotor] = 0;
		}
	}
}


task main()
{
	TxPkt.SonarValue = TxPkt.ArmValue = 0;
	TxPkt.Drive = false;
	TxPkt.ArmDown = true;
	TxPkt.ClawClosed = true;
	TxPkt.Batt = 100;
	startTask(UARTRx);

//Sending Data

		char *ptr = (char *)&TxPkt;
while(true) {
		if (TxPkt.Drive == true) {
			value = '1';
		sendChar(uartOne, value);
	} else if (TxPkt.Drive == false) {
			value = '0';
		sendChar(uartOne, value);
	}
}

	/*
	while(true)
	{
		TxPkt.SonarValue = SensorValue(MiddleSonar);
		TxPkt.ArmValue = SensorValue(armPosition);
		TxPkt.ClawClosed = SensorValue(

		for(int x=0; x<11; x++)
			sendChar(uartOne, *(ptr+x));

		wait1Msec(5000);  //5 second bursts of data
	}*/




}
