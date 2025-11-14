#include <iostream>
#include "../include/Expressao.h"
int main() 
{
  std::vector<std::string> entrada = {"2", "10", "+"};

  std::cout << resolverExpressao(entrada) << std::endl;
  
  return 0;
}
