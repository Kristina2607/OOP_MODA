#include "ViewCart.h"

ViewCart::ViewCart(System& system):Command(system){}

void ViewCart::execute()
{
	system.viewCart();
}
