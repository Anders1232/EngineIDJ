#ifndef ENDSTATEDATA_H
#define ENDSTATEDATA_H

#include "StateData.h"
#include "Defines.h"

class EndStateData: StateData {
	public:
		bool Is(StateDataType typeToCheck) const;
		EndStateData(bool playerVictory);
		bool playerVictory;
};

inline EndStateData::EndStateData(bool playerVictory) {
	this-> playerVictory= playerVictory;
}

inline bool EndStateData::Is(StateDataType typeToCheck) const {
	return typeToCheck == STATE_DATA_END;
}


#endif
