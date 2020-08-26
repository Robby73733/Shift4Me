// CHANGE ONLY THE LINES BEGINNING AT THE LEFT OF THE SCRIPT
// the GEARS parameters should be obtained using the SETUP SCRIPT
// NOTES on the DERAILLEUR settings
   // ** GearAmount ** how many sprockets does your bike have? 
   // ** Gears[] ** these figures should be obtained using the setup-script
      // it corresponds to the pulse that the servo receives, so minimum and maximum MUST be in the range that your servo can receive
      // first figure = high speed/smallest sprocket
      // last figure = low speed/biggest sprocket
      // if your system has 9 gears, you should enter 9 Gears figures.
        // carefully enter with correct syntax: figures end with ";"
   // ** CorrectAmount ** has to able to divide by 4 // set to around 240 for derailleurs with 8-11 sprockets // set to around 300 for 5-7 sprockets    
    int LoadSprocketWidth(String request, int var){
    int GearAmount;
    int CorrectAmount;
    int StartingGear;

GearAmount = 8;
CorrectAmount = 80; 
StartingGear = 4;

      int Gears[GearAmount];
      // calling startinggear upon request
      if (var == 99) {
        var = StartingGear;
      }

Gears[0] = 2340;
Gears[1] = 2080;
Gears[2] = 1820;
Gears[3] = 1560;
Gears[4] = 1300;
Gears[5] = 1040;
Gears[6] = 780;
Gears[7] = 520;

    if(request == "GetGear"){
      return Gears[var];
      }
    else if(request == "CorrectAmount"){
      return CorrectAmount;
      }
    else if(request == "GearAmount"){
      return GearAmount;
      }
    else if(request == "StartingGear"){
      return StartingGear;
      }
    else {
      }
    }

// NOTES on the DERAILLEUR settings
   // ** GearAmount ** how many sprockets does your bike have? 
   // ** Gears[] ** these figures should be obtained using the setup-script
      // it corresponds to the pulse that the servo receives, so minimum and maximum MUST be in the range that your servo can receive
      // first figure = high speed/smallest sprocket
      // last figure = low speed/biggest sprocket
      // if your system has 9 gears, you should enter 9 Gears figures.
        // carefully enter with correct syntax: figures end with ";"
  // ** ActiveGear ** is the number of the gear you want the bike to be in on startup
      // has to be set to 0 for derailleur bikes, and to the reference gear on Hub geared bikes (4 on a Shimano Nexus 8)
   // ** CorrectAmount ** has to able to divide by 4 // set to around 240 for derailleurs with 8-11 sprockets // set to around 300 for 5-7 sprockets // set to 0 for HUB GEARS
