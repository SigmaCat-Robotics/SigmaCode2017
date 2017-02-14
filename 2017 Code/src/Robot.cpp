#include <iostream>
#include <memory>
#include <string>

#include <Encoder.h>
#include <ADXRS450_Gyro.h>
#include <CameraServer.h>
#include <VictorSP.h>
#include <DoubleSolenoid.h>
#include <Joystick.h>
#include <SampleRobot.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <RobotDrive.h>
#include <Timer.h>

#define FORWARD 1
#define BACKWARD -1
#define ENCODERTICKSPERFOOT
#define LOWGEAR 1
#define HIGHGEAR -1
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
	frc::VictorSP *intakeMotor, *shooterMotor, *indexerMotor, *agitatorMotor, *climberMotor;
	frc::Joystick *controller;
	frc::RobotDrive *sigmaDrive, *boostDrive;
	frc::DoubleSolenoid *sigmaShifter;
	frc::SmartDashboard *SmartDashboard;
	frc::ADXRS450_Gyro *gyro;
	frc::Encoder *rightEncoder, *leftEncoder;
public:

	void RobotInit() {
		rightFront = new VictorSP(9);   // Motor w/ Silver sticker
		rightBack = new VictorSP(9);    // Motor w/ Purple sticker
		rightTop = new VictorSP(9);     // Motor w/ Brown sticker
		leftFront = new VictorSP(0);    // Motor w/ Green sticker
		leftBack = new VictorSP(0);     // Motor w/ Red sticker
		leftTop = new VictorSP(0);      // Motor w/ White sticker
		intakeMotor = new VictorSP(4);  // Motor w/ purple orange sticker
		shooterMotor = new VictorSP(5); // Motor w/ blue sticker
		agitatorMotor = new VictorSP(1); // Motor w/ yellow green sticker
		indexerMotor = new VictorSP(3);  // Motor w/ Orange sticker
		//climberMotor = new VictorSP()//Motor w/yellow sticker
		controller = new Joystick(0);
		sigmaDrive = new RobotDrive(rightFront, rightBack, leftFront, leftBack);
		boostDrive = new RobotDrive(rightTop, leftTop);
	//	rightEncoder new Encoder;
	//	leftEncoder = new Encoder;
	//	CameraServer::GetInstance()->StartAutomaticCapture();
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
	//This is an algorithm that you enter the direction, distance, speed.
	void SigmaDrive(int direction, int gear, double distance, double speed)
	{
		rightEncoder->Reset();
		leftEncoder->Reset();
		if(gear == LOWGEAR)
		{
			LowGear();
		}
		if(gear == HIGHGEAR)
		{
			HighGear();
		}
		double destination = distance * ENCODERTICKSPERFOOT * direction *gear;
		if(destination > 0)//Forward
		{
			while(rightEncoder->Get() <= destination && leftEncoder->Get() <= destination )
			{
				std::cout << "Right Encoder: " << rightEncoder->Get() << std::endl;
				std::cout << "Left Encoder: " << leftEncoder->Get() << std::endl;
				sigmaDrive->TankDrive(speed, speed);
			}
		}
		else//Backward
		{
			while(rightEncoder->Get() <= destination && leftEncoder->Get() <= destination)
			{
				std::cout << "Right Encoder: " << rightEncoder->Get() << std::endl;
				std::cout << "Left Encoder: " << leftEncoder->Get() << std::endl;
				sigmaDrive->TankDrive(-speed, -speed);
			}

		}
	}
*/
/*
	*This is the start of an algorithm that you enter the degrees
	void Gyro(int n)
	{
		if(n > 0)
		{
			while(gyro->GetAngle() <= n)
			{
				std::cout << "Angle: " << gyro->GetAngle() << std::endl;
				sigmaDrive->TankDrive(0.7,-0.7);
			}
		}
		else
		{
			while(gyro->GetAngle() >= n)
			{
				std::cout << "Angle: " << gyro->GetAngle() << std::endl;
				sigmaDrive->TankDrive(-0.7,0.7);
			}
		}
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
//		sigmaDrive.SetSafetyEnabled(true);
		int firstTimeInX = 1;

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
			double RT = (controller->GetRawAxis(3));
			sigmaDrive->TankDrive(leftValue, rightValue);
			boostDrive->TankDrive(leftValue, rightValue);
			/*
			 * The following code needed to change gears
			 * Not Subject to change
			 */

			if(LB)
			{
				intakeMotor->Set(-0.98);
				std::cout <<"LB!" << std::endl;
				frc::Wait(.001);
				firstTimeInX = 1;
			}
			else if(RB)
			{
				intakeMotor->Set(0.98);
				std::cout <<"RB!" << std::endl;
				frc::Wait(.001);
				firstTimeInX = 1;
			}
			else if(RT >= 0.1)
			{
				shooterMotor->Set(0.635);
				if (firstTimeInX == 1)
				{
					firstTimeInX = 0;
					Wait(2);
				}

				indexerMotor->Set(0.14);
				agitatorMotor->Set(0.25);
				intakeMotor->Set(-0.98);
				std::cout <<"X! -" << std::endl;
			}
			else
			{
				intakeMotor->Set(0.0);
				shooterMotor->Set(0.0);
				indexerMotor->Set(0.0);
				agitatorMotor->Set(0.0);
				firstTimeInX = 1;
			}
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
		// wait for a motor update time
		//frc::Wait(0.005);
		}
}
	/*
	 * Runs during test mode
	 */
	void Test() override {

	}
};

START_ROBOT_CLASS(Robot)
