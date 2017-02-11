#include <iostream>
#include <memory>
#include <string>

#include <CameraServer.h>
#include <VictorSP.h>
#include <DoubleSolenoid.h>
#include <Joystick.h>
#include <SampleRobot.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <RobotDrive.h>
#include <Timer.h>

//#define LOWGEAR
//#define HIGHGEAR
//#define TICKS

/**
 * This is a demo program showing the use of the RobotDrive class.
 * The SampleRobot class is the base of a robot application that will
 * automatically call your Autonomous and OperatorControl methods at the right
 * time as controlled by the switches on the driver station or the field
 * controls.
 *
 * WARNING: While it may look like a good choice to use for your code if you're
 * inexperienced, don't. Unless you know what you are doing, complex code will
 * be much more difficult under this system. Use IterativeRobot or Command-Based
 * instead if you're new.
 */
class Robot: public frc::SampleRobot {
	frc::VictorSP *rightFront, *rightBack, *rightTop, *leftFront, *leftBack, *leftTop;
	frc::VictorSP *intakeMotor, *shooterMotor, *indexerMotor, *agitatorMotor;
	frc::Joystick *controller;
	frc::RobotDrive *sigmaDrive, *boostDrive;
	frc::DoubleSolenoid *sigmaShifter;
	frc::SmartDashboard *SmartDashboard;
public:

	void RobotInit() {
		rightFront = new VictorSP(9);   // Motor w/ Silver sticker
		rightBack = new VictorSP(9);    // Motor w/ Purple sticker
		rightTop = new VictorSP(9);     // Motor w/ Brown sticker
		leftFront = new VictorSP(0);    // Motor w/ Green sticker
		leftBack = new VictorSP(0);     // Motor w/ Red sticker
		leftTop = new VictorSP(0);      //  Motor w/ White sticker
		intakeMotor = new VictorSP(4);  //Motor w/ yellow sticker
		shooterMotor = new VictorSP(5);  //Motor w/ blue sticker
		//agitatorMotor = new VictorSP(); // Motor w/
		indexerMotor = new VictorSP(3);  // Motor w/ Orange sticker
		controller = new Joystick(0);
		sigmaDrive = new RobotDrive(rightFront, rightBack, leftFront, leftBack);
		boostDrive = new RobotDrive(rightTop, leftTop);
		CameraServer::GetInstance()->StartAutomaticCapture();
		//sigmaShifter = new DoubleSolenoid(0,1);

	}
	void LowGear()
	{
		sigmaShifter->Set(DoubleSolenoid::kForward);
	}
	void HighGear()
	{
		sigmaShifter->Set(DoubleSolenoid::kReverse);
	}
	/*
	*This is the start of an algorithm that you enter the distance, speed, and gear
	* and the robot moves for auto
	void SigmaDrive(bool LOWGEAR, int speed, double distance)
	{
		if(LOWGEAR == true)
		{
			//Lowgear * distance;
		}
		else
		{
			//Highgear * distance;
		}
		// double Encdistance = distance * TICKS;
		double pwmSpeed = speed/100;
		sigmaDrive->TankDrive(pwmSpeed, pwmSpeed);
		boostDrive->TankDrive(pwmSpeed, pwmSpeed);
	}
	*/
	/*
	 * This autonomous (along with the chooser code above) shows how to select
	 * between different autonomous modes using the dashboard. The sendable
	 * chooser code works with the Java SmartDashboard. If you prefer the
	 * LabVIEW Dashboard, remove all of the chooser code and uncomment the
	 * GetString line to get the auto name from the text box below the Gyro.
	 *
	 * You can add additional auto modes by adding additional comparisons to the
	 * if-else structure below with additional strings. If using the
	 * SendableChooser make sure to add them to the chooser code above as well.
	 */
	void Autonomous()
	{
		//Enter code here
	}

	/*
	 * Runs the motors with arcade steering.
	 */
	void OperatorControl() override {
		//myRobot.SetSafetyEnabled(true);
		while (IsOperatorControl() && IsEnabled())
		{
			double leftValue = (-1 * controller->GetRawAxis(5));
			//double leftValue = 0;
			SmartDashboard->PutNumber("leftValue: ",leftValue);
			double rightValue = (-1 * controller->GetRawAxis(1));
			SmartDashboard->PutNumber("rightValue: ",rightValue);
						//Buttons
			double A = (controller->GetRawButton(1));
			double X = (controller->GetRawButton(3));
			//double LT = (controller->GetRawAxis(2));
			double RB = (controller->GetRawButton(6));
			double LB = (controller->GetRawButton(5));
			//int state = 0;
			//double RT = (controller->GetRawButton());
			sigmaDrive->TankDrive(leftValue, rightValue);
			boostDrive->TankDrive(leftValue, rightValue);
			/*
			 * The following code needed to change gears
			 * Not Subject to change
			 */

			if(LB)
			{
				intakeMotor->Set(-.98);
			}
			else if(RB)
			{
				intakeMotor->Set(.98);
			}
			else if(X)
			{
				shooterMotor->Set(.55);
				Wait(2);
				indexerMotor->Set(.55);
				agitatorMotor->Set(.25);
				intakeMotor->Set(-.98);
			}
			else
			{
				intakeMotor->Set(0.0);
				shooterMotor->Set(0.0);
				indexerMotor->Set(0.0);
				agitatorMotor->Set(0.0);
			}



			/*
			if(X)
			{
				shooterMotor->Set(.55);
				Wait(2);
				indexerMotor->Set(.55);
				agitatorMotor->Set(.25);
				intakeMotor->Set(-.98);
			}
			else
			{
				shooterMotor->Set(0.0);
				indexerMotor->Set(0.0);
			}
			*/
			/*
			 * if(RT >= 0.9)
			 * {
			 *
			 * }
			if(LT >= 0.1)
			{
				LowGear();
			}
			else
			{
				HighGear();
			}
			*/
			/*
			 * The following is the code needed to run the intake system
			 * Subject to change
			 */
			/*
			 *
			if(A)
			{
				state = 1;
			}
			else if(B)
			{
				state = 0;
			}
			switch(state)
			{
				case 0:
				{
				//Set all off
					shooterMotor->Set(0.0);
					agitatorMotor->Set(0.0);
					indexerMotor->Set(0.0);
					intakeMotor->Set(0.0);
					SmartDashboard->PutString("Currently in case 0");
					break;
				}
				case 1:
				{
				//Starts the shooter motor
					shooterMotor->Set();
					Wait(1);
					SmartDashboard->PutString("Currently in case 1");
					state = 2;
					break;
				}
				case 2:
				{
				//Turns the intake motor and the agitator motor on at the same time and waits to turn on indexter
					intakeMotor->Set();
					agitatorMotor->Set();
					Wait(.002);
					indexerMotor->Set();
					SmartDashboard->PutString("Currently in case 2");
					break;
				}
				default:
				{
					shooterMotor->Set(0.0);
					agitatorMotor->Set(0.0);
					indexerMotor->Set(0.0);
				}
			}
			*/



			// wait for a motor update time
			frc::Wait(0.005);
		}
}
	/*
	 * Runs during test mode
	 */
	void Test() override {

	}
};

START_ROBOT_CLASS(Robot)
