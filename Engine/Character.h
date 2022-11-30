#pragma once
#include "Animation.h"
#include "Vec2.h"

class Character
{
private:
	//different animation states the character can be in
	enum class Sequence
	{
		WalkingLeft,
		WalkingRight,
		WalkingUp,
		WalkingDown,
		StandingLeft,
		StandingRight,
		StandingUp,
		StandingDown,
		Count
	};
public:
	//set each comp of animations vec with an animation, in order of seq
	Character(Vec2 pos);
	//moves character by velocity, proportional to realtime
	void Update( float dt );
	//sets animation to be one from sequence, and then moves char by normalized direction
	void SetDirection( const Vec2& dir );
	void Draw( Graphics& gfx ) const;
	void Draw( Graphics& gfx, float percentVis ) const;
	//getters and setters
	Vec2 getPos() const;
private:
	Surface SpriteSheet = ( "Sprites\\Link90x90.bmp" );
	//holds a diff animation for each state possible by enum Sequence
	std::vector<Animation> animations;
	//Position and Velocity stored as member vars
	Vec2 pos;
	Vec2 vel = { 0,0 };
	Sequence currSeq = Sequence::StandingRight;
	//since the direction is normalized, we use speed to control char move speed
	float speed = 150.f;
};

