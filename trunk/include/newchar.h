#ifndef __NEWCHAR_H__
#define __NEWCHAR_H__

#include "module.h"
#include <string>

namespace AfroDS {

	class NewChar : public AfroDS::Module {
		public:
			NewChar();
			~NewChar();
			void moduleEvents();

		private:
			void createChar();
			std::string m_sCharName;
	};

}
#endif
