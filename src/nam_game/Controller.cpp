#include "pch.h"
#include "Controller.h"

using namespace nam;

bool Controller::Get(ControlType controlType)
{
	switch (controlType)
	{
	case ControlType::RightClick:
		return Input::IsKeyDown(VK_RBUTTON);
	case ControlType::LeftClick:
		return Input::IsKeyDown(VK_LBUTTON);
	case ControlType::FireTongue:
		return Input::IsKeyDown('E');
	case ControlType::GroundPound:
		return Input::IsKeyDown('A');
	case ControlType::Up:
		return Input::IsKey('Z') || Input::IsKey(VK_UP);
	case ControlType::Down:
		return Input::IsKey('S') || Input::IsKey(VK_DOWN);
	case ControlType::Right:
		return Input::IsKey('D') || Input::IsKey(VK_RIGHT);
	case ControlType::Left:
		return Input::IsKey('Q') || Input::IsKey(VK_LEFT);
	case ControlType::MoveArrowUp:
		return Input::IsKey(VK_SHIFT);
	case ControlType::MoveArrowDown:
		return Input::IsKey(VK_CONTROL);
	case ControlType::JumpCharge:
		return Input::IsKeyDown(VK_SPACE);
	case ControlType::JumpRelease:
		return Input::IsKeyUp(VK_SPACE);
	case ControlType::SwitchFrog1:
		return Input::IsKeyDown('1');
	case ControlType::SwitchFrog2:
		return Input::IsKeyDown('2');
	case ControlType::UnlockCamera:
		return Input::IsKeyDown(VK_ESCAPE);
	default:
		return false;
	}
}
