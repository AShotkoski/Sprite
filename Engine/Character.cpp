#include "Character.h"
#include <assert.h>

Character::Character( Vec2 pos )
	:
	pos(pos)
{
	//init the walking animations
	for ( int i = 0; i < (int)Sequence::StandingLeft; i++ )
	{
		animations.emplace_back( 90, 90 * i, 90, 90, 0.16f, 4, SpriteSheet );
	}

	//init the standing animations
	for ( int i = (int)Sequence::WalkingDown; i <= (int)Sequence::StandingDown; i++ )
	{
		animations.emplace_back( 0, 90 * (i - (int)Sequence::WalkingDown), 90, 90, 0.16f, 1, SpriteSheet );
	}
	
}

void Character::Update( float dt )
{
	pos += vel * dt;
	animations[(int)currSeq].Update( dt );
}

void Character::SetDirection( const Vec2& dir )
{
	if ( dir.x > 0 ) //dir faces right
	{
		currSeq = Sequence::WalkingRight;
	}
	else if ( dir.x < 0 ) // dir faces left
	{
		currSeq = Sequence::WalkingLeft;
	}
	else if ( dir.y < 0 ) //dir faces up
	{
		currSeq = Sequence::WalkingUp;
	}
	else if ( dir.y > 0 ) //dir faces down
	{
		currSeq = Sequence::WalkingDown;
	}
	else if ( dir.x == 0 && dir.y == 0 ) // if hes standing still we can use the velocity since it will be last dir
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

	Vec2 normalizedDir = dir.GetNormalized();
	vel = normalizedDir * speed;
}

void Character::Draw( Graphics& gfx ) const
{
	Draw( gfx, 100 );
}

void Character::Draw( Graphics& gfx, float percentVis ) const
{
	animations[(int)currSeq].Draw( (Vei2)pos, gfx, percentVis );
}

Vec2 Character::getPos() const
{
	return pos;
}
