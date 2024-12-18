#include <iostream>
#include "clsLoginScreen.h"
#include "clsCurrency.h"

void _Printcurrency(clsCurrency Currency)
{
  cout << "\nCurrency Card:";
  cout << "\n_________________________\n";
  cout << "Country       : " << Currency.Country() << endl;
  cout << "Currency Code : " << Currency.Country() << endl;
  cout << "Currency Name : " << Currency.Country() << endl;
  cout << "Rate          : " << Currency.Rate() << endl;
  cout << "_________________________\n";
}

using namespace std;

int main()
{

  while (true)
  {
    if (!clsLoginScreen::ShowLoginScreen())
    {
      break;
    }
  }

  return 0;
}
