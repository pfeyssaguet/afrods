#include "module.h"

using namespace AfroDS;

Module::Module() : m_bIsStopped(false) {

}

bool Module::isStopped() {
	return m_bIsStopped;
}
