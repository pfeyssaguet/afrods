#include "module.h"

Module::Module() : m_bIsStopped(false) {

}

bool Module::isStopped() {
	return m_bIsStopped;
}
