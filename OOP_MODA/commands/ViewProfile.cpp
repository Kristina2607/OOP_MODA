#include "ViewProfile.h"

ViewProfile::ViewProfile(System& system) : Command(system) {}

void ViewProfile::execute()
{
	system.viewProfile();
}
