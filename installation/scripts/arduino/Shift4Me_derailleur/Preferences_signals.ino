// CHANGE ONLY THE LINES BEGINNING AT THE LEFT OF THE SCRIPT
 // **UseBuzzer** can be set to "no" or "yes". 
        // if set to yes (use only small caps!) the buzzer sounds when the gears are shifted.

  // **UseLed** can be set to "no" or "yes". 
        // if set to yes (use small caps!) the LED lights up when the gears are shifted.
    String LoadSignalPrefs(String request){
     String UseBuzzer;
     String UseLed;
     
UseBuzzer = "yes"; // recommended is "yes"
UseLed = "yes"; // recommended is "yes"


    if(request == "UseBuzzer"){
      return UseBuzzer;
      }
    else if(request == "UseLed"){
      return UseLed;
      }
    else {
      
    }
    }
