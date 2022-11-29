#include "Character.h"

Character::Character( Vec2 pos )
	:
	pos(pos)
{
	for ( int i = 0; i < (int)Sequence::StandingLeft; i++ )
	{
		animations.emplace_back( 90, 90 * i, 90, 90, 0.16f, 4, SpriteSheet );
	}

	for ( int i = (int)Sequence::WalkingLeft; i <= (int)Sequence::StandingDown; i++ )
	{
		animations.emplace_back( 0, 90 * i, 90, 90, 0.16f, 1, SpriteSheet );
	}
	
}

void Character::Update( float dt )
{
	pos += vel * dt;
	animations[(int)currSeq].Update( dt );
}

void Character::SetDirection( const Vec2& dir )
{
	if ( dir.x > 0 )
	{
		currSeq = Sequence::WalkingRight;
	}
	else if ( dir.x < 0 )
	{
		currSeq = Sequence::WalkingLeft;
	}
	else if ( dir.y < 0 )
	{
		currSeq = Sequence::WalkingUp;
	}
	else if ( dir.y > 0 )
	{
		currSeq = Sequence::WalkingDown;
	}
	else if ( dir.x == 0 && dir.y == 0 )
	{
		if ( vel.x > 0 )
		{
			currSeq = Sequence::StandingRight; 
		}
		else if ( vel.x < 0 )
		{
			currSeq = Sequence::StandingLeft; 
		}
		else if ( vel.y > 0 )
		{
			currSeq = Sequence::StandingDown; 
		}
		else if ( vel.y < 0 )
		{
			currSeq = Sequence::StandingUp; 
		}

	}
	vel = dir * speed;

}

void Character::Draw( Graphics& gfx ) const
{

	animations[(int)currSeq].Draw( (Vei2)pos, gfx);
	//animations[(int)Sequence::WalkingRight].Draw( { 50,50 }, gfx );
}
