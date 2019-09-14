/***************************************************************************//**
 * @file direction.cpp
 ******************************************************************************/
#include "direction.h"

std::ostream &operator<< ( std::ostream &out, direction const &dir )
{
	switch ( dir )
	{
		case UP:
			out << "up";
			break;

		case UPRIGHT:
			out << "upright";
			break;

		case RIGHT:
			out << "right";
			break;

		case DOWNRIGHT:
			out << "downright";
			break;

		case DOWN:
			out << "down";
			break;

		case DOWNLEFT:
			out << "downleft";
			break;

		case LEFT:
			out << "left";
			break;

		case UPLEFT:
			out << "upleft";
			break;

		case STAY:
			out << "stay";
			break;
	}

	return out;
}
