#include "module.h"

using namespace AfroDS;

Module::Module(Context * context) : m_context(context) {

}

Context * Module::getContext() const {
	return m_context;
}

void Module::moduleEvents() {

}

void Module::modulePause() {

}

void Module::moduleResume() {

}
