
class naza_interface_manual{
	public:
		// A: For roll control (left/right)
		// E: For pitch control (front/back)
		// T: For throttle control 
		// R: For rudder control
		// U: For Control Model Switch
		void configure_pins(int A, int E, int T, int R, int U);

		void fly_forward(int speed);
		void fly_backward(int speed);
		void fly_up(int speed);
		void fly_down(int speed);
		void fly_left(int speed);
		void fly_right(int speed);

};
