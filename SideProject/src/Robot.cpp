#include "WPILib.h"

/**
 * This is a demo program showing the use of the RobotDrive class.
 * The SampleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 *
 * WARNING: While it may look like a good choice to use for your code if you're inexperienced,
 * don't. Unless you know what you are doing, complex code will be much more difficult under
 * this system. Use IterativeRobot or Command-Based instead if you're new.
 */
class Robot: public SampleRobot
{

	Talon *left1, *left2, *right1, *right2;//Drive train motors
	Joystick *left, *right, *controller; // only joystick
	RobotDrive *drive; // robot drive system
	SendableChooser *chooser;
	DoubleSolenoid *shifter;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";



public:
	void RobotInit() override{

		controller = new Joystick(0);
		//Drive train motors
		left1 = new Talon(1);//LF
		left2 = new Talon(0);//LB
		right1 = new Talon(2);//RF
		right2 = new Talon(3);//RB

		drive = new RobotDrive(left1,left2,right1,right2);
	}

	/**
	 * This autonomous (along with the chooser code above) shows how to select between different autonomous modes
	 * using the dashboard. The sendable chooser code works with the Java SmartDashboard. If you prefer the LabVIEW
	 * Dashboard, remove all of the chooser code and uncomment the GetString line to get the auto name from the text box
	 * below the Gyro
	 *
	 * You can add additional auto modes by adding additional comparisons to the if-else structure below with additional strings.
	 * If using the SendableChooser make sure to add them to the chooser code above as well.
	 */
	void Autonomous()
	{
		/*
		std::string autoSelected = *((std::string*)chooser->GetSelected());
		//std::string autoSelected = SmartDashboard::GetString("Auto Selector", autoNameDefault);
		std::cout << "Auto selected: " << autoSelected << std::endl;

		if(autoSelected == autoNameCustom){
			//Custom Auto goes here
			std::cout << "Running custom Autonomous" << std::endl;
			myRobot.SetSafetyEnabled(false);
			myRobot.Drive(-0.5, 1.0); 	// spin at half speed
			Wait(2.0); 				//    for 2 seconds
			myRobot.Drive(0.0, 0.0); 	// stop robot
		} else {
			//Default Auto goes here
			std::cout << "Running default Autonomous" << std::endl;
			myRobot.SetSafetyEnabled(false);
			myRobot.Drive(-0.5, 0.0); 	// drive forwards half speed
			Wait(2.0); 				//    for 2 seconds
			myRobot.Drive(0.0, 0.0); 	// stop robot
		}
		*/

	}

	/**
	 * Runs the motors with arcade steering.
	 */
	void OperatorControl()
	{
		//myRobot.SetSafetyEnabled(true);
		while (IsOperatorControl() && IsEnabled())
		{
					//Driving with controller
			double leftValue = (-1 * controller->GetRawAxis(1));
			double rightValue = (-1 * controller->GetRawAxis(5));
			drive->TankDrive(leftValue,rightValue);


			Wait(0.005);				// wait for a motor update time
		}
	}

	/**
	 * Runs during test mode
	 */
	void Test()
	{
	}
};

START_ROBOT_CLASS(Robot)
