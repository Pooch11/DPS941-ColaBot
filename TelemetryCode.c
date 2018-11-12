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

//Handle this after testing the streams are working
/*
struct Data
{
	short SonarValue;
	short ArmValue;
	bool Drive;
	bool ArmDown;
	bool ClawClosed;
	int Batt;
};
*/
void pointTurnLeft(int angle);
void pointTurnRight(int angle);
void send();
void receive(); 

// perform a 90 degree point turn to the left
	void pointTurnLeft(int angle){
		if (angle == 45){
			motorTarget = motorTarget /2;
		}
		nMotorEncoder[leftMotor] = 0;
		nMotorEncoder[rightMotor] = 0;
		wait1Msec(1000);
		moveMotorTarget(rightMotor, motorTarget, turningMotorSpeed, true);
		moveMotorTarget(leftMotor, -motorTarget, -turningMotorSpeed, true);

		while(getMotorTargetCompleted(rightMotor) == false && getMotorTargetCompleted(leftMotor) == false){
		}
		motor[rightMotor] = 0;
		motor[leftMotor] = 0;
		motorTarget = 525;
	}
	
	
	//perform a 90 degree point turn to the right
	void pointTurnRight(int angle){
		if (angle == 45){
			motorTarget = motorTarget /2;
		}
		nMotorEncoder[leftMotor] = 0;
		nMotorEncoder[rightMotor] = 0;
		wait1Msec(1000);
		moveMotorTarget(rightMotor, -motorTarget, -turningMotorSpeed, true);
		moveMotorTarget(leftMotor, motorTarget, turningMotorSpeed, true);

		while(getMotorTargetCompleted(rightMotor) == false && getMotorTargetCompleted(leftMotor) == false){

		}
		motorTarget = 525;
		motor[rightMotor] = 0;
		motor[leftMotor] = 0;
	}

void send() {
	int TxPkt = 10;
	char *ptr = (char *)&TxPkt;
	while(true) {
		for(int x=0; x<11; x++)
			sendChar(uartOne, *(ptr+x));

			wait1Msec(5000);  //5 second bursts of data
	}
	
	/*while(true)
	{
		TxPkt.SonarValue = SensorValue(MiddleSonar);
		TxPkt.ArmValue = SensorValue(armPosition);
		TxPkt.Batt = nImmediateBatteryLevel;

		for(int x=0; x<11; x++)
			sendChar(uartOne, *(ptr+x));

		wait1Msec(5000);  //5 second bursts of data
	}*/

}

void receive() {
	
	int rcvChar;		//Variable to hold the reciving byte data

	while (true)
	{
		rcvChar = getChar(uartOne);
		if (rcvChar == -1)
		{
			// No character available
	 		wait1Msec(3); 
	 		continue;
		}
		
		if(rcvChar == 1)
		{
			TxPkt.Drive = true;
			motor[leftMotor] = 50;
			motor[rightMotor] = 50;
		}
	}

}

task main() {
	
	startTask(send);
	startTask(receive);
	//code below is from the website I showed earlier. Can use these since its really simple send tasks.
	/*
	while(true) {

	    sendChar(uartOne, 'A');
	    delay(250);
	    sendChar(uartOne, 'B');
	    delay(250);
	    sendChar(uartOne, 'C');
	    delay(250);
	    sendChar(uartOne, 'D');
	    delay(250);
	    sendChar(uartOne, 'E');
	    delay(250);
	    sendChar(uartOne, '\n');
	    delay(250);
	*/
}