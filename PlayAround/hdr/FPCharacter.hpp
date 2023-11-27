#ifndef FPCHARACTER_HPP
# define FPCHARACTER_HPP

# include "Camera.hpp"

class FPCharacter : public Camera
{
	private:

	
	public:
		FPCharacter();
		FPCharacter(FPCharacter & src);
		~FPCharacter();
}

#endif