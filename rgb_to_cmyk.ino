String incomingData; // Variable to store incoming data

void setup() {
  Serial.begin(9600); // Start serial communication at 9600 baud rate
}

void loop() {
  if (Serial.available() > 0) { // Check if data is available to read
    incomingData = Serial.readString(); // Read the incoming data as a string
    Serial.println(incomingData); // Print the incoming data to the Serial Monitor
    
    // Check if incoming data is in RGB format
    if (incomingData.startsWith("RGB(") && incomingData.endsWith(")")) {
      // Remove the 'RGB(' prefix and ')' suffix
      incomingData = incomingData.substring(4, incomingData.length() - 1);

      // Split the RGB values
      int firstCommaIndex = incomingData.indexOf(',');
      int secondCommaIndex = incomingData.indexOf(',', firstCommaIndex + 1);

      int r = incomingData.substring(0, firstCommaIndex).toInt();
      int g = incomingData.substring(firstCommaIndex + 1, secondCommaIndex).toInt();
      int b = incomingData.substring(secondCommaIndex + 1).toInt();

      // Convert RGB to CMYK
      float c = 1 - (r / 255.0);
      float m = 1 - (g / 255.0);
      float y = 1 - (b / 255.0);
      float k = min(c, min(m, y));

      if (k < 1) {
        c = (c - k) / (1 - k);
        m = (m - k) / (1 - k);
        y = (y - k) / (1 - k);
      } else {
        c = 0;
        m = 0;
        y = 0;
      }

      // Print the CMYK values to the Serial Monitor
      Serial.print("CMYK(");
      Serial.print(c * 100);
      Serial.print(", ");
      Serial.print(m * 100);
      Serial.print(", ");
      Serial.print(y * 100);
      Serial.print(", ");
      Serial.print(k * 100);
      Serial.println(")");

      // Example usage of LED
      if (r == 255 && g == 165 && b == 0) { // Orange
        digitalWrite(13, HIGH); // Turn on the LED
      } else {
        digitalWrite(13, LOW); // Turn off the LED
      }
    }
  }
}
