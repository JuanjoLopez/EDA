//---------------------------------------------------------------------------
// citiesMain.cpp - This is a test for DBM-Tree.
//
// Author: Marcos Rodrigues Vieira (mrvieira@icmc.usp.br)
// Copyright (c) 2003 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#pragma hdrstop
#include "app.h"
#include <iostream>

#pragma argsused
int main(int argc, char* argv[]){
   TApp app;

   cout<<">>>>>>>>>>>>>>>>>>> hola shoby: archivo principal es Cities.cpp <<<<<<<<<<<<<<<<<<<<<"<<endl;
   // Init application.
   app.Init();
   // Run it.
   app.Run();
   // Release resources.
   app.Done();



   return 0;
}//end main
