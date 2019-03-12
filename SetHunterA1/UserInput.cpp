#include "UserInput.h"

void UserInput::Acquire()
{
		HRESULT hr = m_diDevice->Acquire();
		acquired = (hr == S_OK || hr == S_FALSE);
}
