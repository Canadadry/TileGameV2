
#ifndef BASIC_IA_H_
#define BASIC_IA_H_

#include <Engine/GamePad.h>

class BasicIA : public GamePad
{
public:
	BasicIA();
	virtual ~BasicIA();


	virtual void update();

};

#endif /* BASIC_IA_H_ */
