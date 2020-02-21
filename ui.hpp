#ifndef UI_MODE
#define UI_MODE

#ifndef UI

// Comment it out to disable UI mode for linux ONLY ( Output uncontrolled )
#define UI

#endif

void uiInit();		// Initializes the UI if its not (No need to call, auto called when uiClear first runs)
void uiClear();		// Clears the terminal screen for easier "Ui" building and screen navigation
void uiTerminate();	// Must call before the program ends (if ui has been used) to free the memory

#endif