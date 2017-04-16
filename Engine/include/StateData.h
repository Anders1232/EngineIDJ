#ifndef STATEDATA_H
#define STATEDATA_H

typedef int StateDataType;

class StateData
{
	public:
		virtual bool Is(StateDataType typeToCheck) const=0;
};

#endif // STATEDATA_H
