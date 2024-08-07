namespace boop
{
	//use pimpl pattern to improve compile time and avoid ambiguity for a basic controller & no recompile needed
	//to-do research: maybe do some extra research for pimpl pattern for extra understanding
	class Controller final
	{
	private:
		class ControllerImpl;
		ControllerImpl* pImpl; //Pimpl pattern implementation of controller
	public:
		//structs from ppt for bindings
		//XINPUT_GAMEPAD_
		enum struct ControllerButton
		{
			DPadUp = 0x0001,
			DPadDown = 0x0002,
			DPadLeft = 0x0004,
			DPadRight = 0x0008,
			Start = 0x0010,
			Back = 0x0020,
			LeftThumb = 0x0040,
			RightThumb = 0x0080,
			LeftShoulder = 0x0100,
			RightShoulder = 0x0200,
			ButtonA = 0x1000,
			ButtonB = 0x2000,
			ButtonX = 0x4000,
			ButtonY = 0x8000
		};

		//amount of controllers -> limit to 2 for the game I have
		enum struct ControllerId
		{
			First,
			Second
		};
		unsigned int GetId() const; //getter

		//--
		//Functions

		explicit Controller(unsigned int controllerId);
		void Update();

		//Keystate functions
		bool IsDownThisFrame(ControllerButton button) const;
		bool IsUpThisFrame(ControllerButton button) const;
		bool IsPressed(ControllerButton button) const;

		//rule of 5
		~Controller();
		Controller(const Controller& other) = delete;
		Controller(Controller&& other) = delete;
		Controller& operator=(const Controller& other) = delete;
		Controller& operator=(Controller&& other) = delete;
	};
}