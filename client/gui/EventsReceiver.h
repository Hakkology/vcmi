/*
 * EventsReceiver.h, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#pragma once

VCMI_LIB_NAMESPACE_BEGIN
class Point;
VCMI_LIB_NAMESPACE_END

class EventDispatcher;
enum class MouseButton;
enum class EShortcut;
using boost::logic::tribool;

/// Class that is capable of subscribing and receiving input events
/// Acts as base class for all UI elements
class AEventsReceiver
{
	friend class EventDispatcher;

	std::map<MouseButton, bool> currentMouseState;
	ui16 activeState;
	bool hoveredState;
	bool panningState;

protected:
	/// Activates particular events for this UI element. Uses unnamed enum from this class
	void activateEvents(ui16 what);
	/// Deactivates particular events for this UI element. Uses unnamed enum from this class
	void deactivateEvents(ui16 what);

	virtual void clickLeft(tribool down, bool previousState) {}
	virtual void clickRight(tribool down, bool previousState) {}
	virtual void clickDouble() {}

	/// Called when user pans screen by specified distance
	virtual void gesturePanning(const Point & initialPosition, const Point & currentPosition, const Point & lastUpdateDistance) {}

	virtual void gesturePinch(const Point & centerPosition, double lastUpdateFactor) {}

	virtual void wheelScrolled(int distance) {}
	virtual void mouseMoved(const Point & cursorPosition) {}

	/// Called when UI element hover status changes
	virtual void hover(bool on) {}

	/// Called when UI element panning gesture status changes
	virtual void panning(bool on, const Point & initialPosition, const Point & finalPosition) {}

	virtual void textInputed(const std::string & enteredText) {}
	virtual void textEdited(const std::string & enteredText) {}

	virtual void keyPressed(EShortcut key) {}
	virtual void keyReleased(EShortcut key) {}

	virtual void tick(uint32_t msPassed) {}

	virtual bool captureThisKey(EShortcut key) = 0;

	/// If true, event of selected type in selected position will be processed by this element
	virtual bool receiveEvent(const Point & position, int eventType) const= 0;

public:
	AEventsReceiver();
	virtual ~AEventsReceiver() = default;

	/// These are the arguments that can be used to determine what kind of input UI element will receive
	enum {LCLICK=1, RCLICK=2, HOVER=4, MOVE=8, KEYBOARD=16, TIME=32, GENERAL=64, WHEEL=128, DOUBLECLICK=256, TEXTINPUT=512, GESTURE_PANNING=1024, ALL=0xffff};

	/// Returns true if element is currently hovered by mouse
	bool isHovered() const;

	/// Returns true if panning/swiping gesture is currently active
	bool isPanning() const;

	/// Returns true if element is currently active and may receive events
	bool isActive() const;

	/// Returns true if particular mouse button was pressed when inside this element
	bool isMouseButtonPressed(MouseButton btn) const;
};
