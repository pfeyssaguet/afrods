#ifndef __NEWCHAR_H__
#define __NEWCHAR_H__

#include "module.h"
#include "constants.h"
#include "externs.h"
#include <PA9.h>
#include <string>

class NewChar : public Module {
	public:
		NewChar();
		~NewChar();
		void moduleEvents();

	private:
		std::string m_sCharName;
};

#endif
