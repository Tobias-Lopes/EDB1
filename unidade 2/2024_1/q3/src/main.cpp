#include <iostream>
#include "../header/Analisador.h"

int main() 
{
  Analisador analisador;
  
  std::cout << analisador.eBemFormada("()");
  
  return 0;
}
