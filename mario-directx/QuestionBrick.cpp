#include "QuestionBrick.h"
#include "Utils.h"

CQuestionBrick::CQuestionBrick()
{
	background = 0;

	flyingSpeedY = MOVEMENT_SPEED_Y;
	SetState(QUESTIONBRICK_STATE_CONTAINING_OBJECTS);
	disappear = 0;
}

void CQuestionBrick::SetPosition(float x, float y)
{
	this->x = x;
	this->y = y;
	maxFlyingY = y;
	minFlyingY = y - QUESTIONBRICK_BBOX_HEIGHT * 0.75f;

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->SetDisappearingState();
		objects[i]->SetPosition(this->x, this->y);
	}
}

void CQuestionBrick::AddNewObject(CGameObject* obj)
{
	objects.push_back(obj);
}

void CQuestionBrick::HitQuestionBrick(int side)
{
	SetFlyingDirection(FLYING_DIRECTION_UP, side);

	if (objects.size() > 0)
	{
		CGameObject* obj = objects.back();
		objects.pop_back();

		obj->SetFlyingDirection(FLYING_DIRECTION_UP, -side);
	}
}

void CQuestionBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	UpdateFlying(dt);

	if (objects.size() == 0)
		SetState(QUESTIONBRICK_STATE_NONE_OBJECTS);
}

void CQuestionBrick::Render()
{
	int ani = -1;
	if (state == QUESTIONBRICK_STATE_CONTAINING_OBJECTS)
		ani = QUESTIONBRICK_ANI_CONTAINING_OBJECTS;
	else
		ani = QUESTIONBRICK_ANI_NONE_OBJECTS;

	animation_set->at(ani)->Render(x, y);
}

void CQuestionBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + QUESTIONBRICK_BBOX_WIDTH;
	b = t + QUESTIONBRICK_BBOX_HEIGHT;
}
