// CHANGE ONLY THE LINES BEGINNING AT THE LEFT OF THE SCRIPT
  // ** Frequency ** the frequency you want to rotate at, your cycling cadence, in RPM (Rotations Per Minute)
  
  // ** Tolerance ** is added to, or substracted to, the Frequency.
    // lower Tolerance will:
        // change gears more often
        // result in a more accurate RPM flow
        // will increase power drawn by the servo, thus decrease how long your battery will last
    // higher Tolerance will do the opposite than the above...
    // normally, you set the ToleranceHigherGear the same as your ToleranceLowerGear
      // but if you want, you can have different settings for the up-or-downshifting
      
  // ** ChangeDelay ** the minimum time (in milliseconds) that the system will shift gears. This is to avoid shifting gears too often
    // Heavy is for going to a slower pace, Light is for a faster
  
  // ** HiLoAmount ** sets the function of the Hi-Lo preset-switch. The figure is the amount of RPM that is added or abstracted from your Frequency.
        // you can use this as a Uphill mode button (Hi) or Downhill mode (Lo)

  // ** MaxTurns ** this is the maximum amount of cycles you want before the system evaluates your RPM.
        // it bypassed your ChangeDelay: if, for example, you are turning at 200, you don't want the system only to react after two seconds.
 
     int LoadRidePrefs(String request){
      int Frequency;
      int ToleranceHigherGear;
      int ToleranceLowerGear;
      int ChangeDelayHeavy;
      int ChangeDelayLight;
      int HiLoAmount;
      int MaxTurns;
      
Frequency = 60; // recommended: between 50 (really slow cadence) and 90 (experienced cyclist of the sporty type)
ToleranceHigherGear = 5;  // tolerance to move to smaller sprocket // recommended: between 2 and 10
ToleranceLowerGear = 6;  // tolerance to move to larger sprocket // recommended: between 4 and 10
ChangeDelayHeavy = 2000; // recommended between 2500 and 5000
ChangeDelayLight = 4700; // recommended between 2500 and 5000
HiLoAmount = 5; // recommended between 4 and 10
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
