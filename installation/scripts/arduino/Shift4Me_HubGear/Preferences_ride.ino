// CHANGE ONLY THE LINES BEGINNING AT THE LEFT OF THE SCRIPT

     int LoadRidePrefs(String request){
      int Frequency;
      int ToleranceHigherGear;
      int ToleranceLowerGear;
      int ChangeDelayHeavy;
      int ChangeDelayLight;
      int HiLoAmount;
      int MaxTurns;
      
Frequency = 55; // recommended: between 50 (really slow cadence) and 90 (experienced cyclist of the sporty type)
ToleranceHigherGear = 5;  // tolerance if pedalling too fast // is substracted from Frequency // recommended: between 2 and 10
ToleranceLowerGear = 6;  // tolerance if pedalling too slow // is added to Frequency //  recommended: between 4 and 10
ChangeDelayHeavy = 2000; // recommended between 2500 and 5000
ChangeDelayLight = 3700; // recommended between 2500 and 5000
HiLoAmount = 8; // recommended between 4 and 10
MaxTurns = 5;  // recommended between 1 and 8

    if(request == "Frequency"){
      return Frequency;
      }
    else if(request == "ToleranceHigherGear"){
      return ToleranceHigherGear;
      }
    else if(request == "ToleranceLowerGear"){
      return ToleranceLowerGear;
      }
    else if(request == "ChangeDelayHeavy"){
      return ChangeDelayHeavy;
      }
    else if(request == "ChangeDelayLight"){
      return ChangeDelayLight;
      }
    else if(request == "HiLoAmount"){
      return HiLoAmount;
      }
    else if(request == "MaxTurns"){
      return MaxTurns;
      }
    else {
      }
     }
