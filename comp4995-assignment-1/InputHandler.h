#pragma once

// abstract class
class InputHandler {
public:

	// Constructor
	InputHandler();

	// deconstrucotr
	virtual ~InputHandler();

	// Act function called before rendering
	virtual void Act(int delta) = 0;
};