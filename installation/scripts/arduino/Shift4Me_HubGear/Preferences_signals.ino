// CHANGE ONLY THE LINES BEGINNING AT THE LEFT OF THE SCRIPT
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
