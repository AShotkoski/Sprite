#pragma once
#include "Animation.h"
#include "Vec2.h"

class Character
{
private:
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
	Character(Vec2 pos); //set each comp of animations vec with an animation, in order of seq
	void Update( float dt ); //move by vel 
	void SetDirection( const Vec2& dir );
	void Draw( Graphics& gfx ) const;
private:
	Surface SpriteSheet = ( "Sprites\\Link90x90.bmp" );
	std::vector<Animation> animations;
	Vec2 pos;
	Vec2 vel = { 0,0 };
	Sequence currSeq = Sequence::StandingRight;
	float speed = 150.f;
};

