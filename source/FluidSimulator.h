#pragma once

#include "Simulator.h"
#include "Vector3i.h"


//TODO This definitly needs a better naming :D but how?
enum Direction
{
	X_PLUS,
	X_MINUS,
	Y_PLUS,
	Y_MINUS,
	Z_PLUS,
	Z_MINUS,
	NONE
};

class Vector3i;
class cWorld;
class cFluidSimulator : public cSimulator
{
public:
	cFluidSimulator( cWorld* a_World );
	~cFluidSimulator();

	virtual void Simulate( float a_Dt );

	//Gets the flowing direction. if a_Over is true also the block over the current block affects the direction (standard)
	Direction GetFlowingDirection(int a_X, int a_Y, int a_Z, bool a_Over = true);

	virtual bool IsAllowedBlock( BLOCKTYPE a_BlockType ) = 0;
	virtual bool IsStationaryBlock( BLOCKTYPE a_BlockType);
	virtual bool IsPassableForFluid( BLOCKTYPE a_BlockType );
	bool CanWashAway( BLOCKTYPE a_BlockType );
	bool IsSolidBlock(BLOCKTYPE a_BlockType);
protected:
	virtual void AddBlock( int a_X, int a_Y, int a_Z);
	char GetHighestLevelAround( int a_X, int a_Y, int a_Z );

	bool UniqueSituation(Vector3i a_Pos); //Applys special for this fluid rules like generation of water betwin sources, returns false if it is necessary to apply general rules
	void ApplyUniqueToNearest(Vector3i a_Pos);

	float m_Timer;

	class FluidData;
	FluidData* m_Data;

	//Customize
	BLOCKTYPE m_FluidBlock;
	BLOCKTYPE m_StationaryFluidBlock;
	char m_MaxHeight;
	char m_FlowReduction;

};