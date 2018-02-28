#pragma once

class InputHandler {
public:

	// Constructor
	InputHandler();

	virtual ~InputHandler();

	// Act function called before rendering
	virtual void Act(int delta) = 0;
};