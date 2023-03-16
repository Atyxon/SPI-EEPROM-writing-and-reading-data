// Define the pins used for SPI communicationx
#define SCK_PIN   13 // SCK - Serial Clock pin
#define MISO_PIN  12 // MISO - Master In Slave Out pin
#define MOSI_PIN  11 // MOSI - Master Out Slave In pin
#define CS_PIN    10 // CS - Chip Select pin for the EEPROM

// Define EEPROM commands
#define COMMAND_WRITE_ENABLE  0b00000110 // EEPROM command to enable writing
#define COMMAND_WRITE         0b00000010 // EEPROM command to write data
#define COMMAND_READ          0b00000011 // EEPROM command to read data

// Define memory
#define MEMORY_ADDRESS  0x0010 // Address of memory to save data
#define MEMORY_MSB      0x00 // Most significant bit
#define MEMORY_LSB      0x10 // Least significant bit

uint8_t value = 240; // Test value to write on EEPROM

void setup() {
  pinMode(SCK_PIN, OUTPUT); // Set SCK pin as output
  pinMode(MISO_PIN, INPUT); // Set MISO pin as input
  pinMode(MOSI_PIN, OUTPUT); // Set MOSI pin as output
  pinMode(CS_PIN, OUTPUT); // Set CS pin as output

  digitalWrite(CS_PIN, HIGH); // Set the CS pin high to disable the EEPROM
  digitalWrite(SCK_PIN, LOW); // Set the SCK pin low to start with

  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  value++; // increase the value to monitor program performance
  eepromDataWrite(value); // use eepromDataWrite() function to write value to EEPROM
  Serial.print("Data Write: ");
  Serial.println(value); // Print the write data

  byte data = eepromDataRead(); // use eepromDataRead() function to read value from EEPROM and store it to data variable
  Serial.print("Data Read: ");
  Serial.println(data); // Print the read data

  Serial.println("---------------");
  delay(1000); // Wait for 1 second before repeating the loop
}

byte eepromDataRead(){
  // Read data from EEPROM
  digitalWrite(CS_PIN, LOW); // Enable EEPROM by setting CS pin low
  spi_transfer(COMMAND_READ); // Send the EEPROM Read command
  spi_transfer(MEMORY_MSB); // Send the EEPROM address (MSB)
  spi_transfer(MEMORY_LSB); // Send the EEPROM address (LSB)
  byte data = spi_transfer(MEMORY_ADDRESS); // Read the data from the EEPROM
  digitalWrite(CS_PIN, HIGH); // Disable EEPROM by setting CS pin high

  return data; // Return read data
}

void eepromDataWrite(byte data){
  // Write data to EEPROM
  digitalWrite(CS_PIN, LOW); // Enable EEPROM by setting CS pin low
  spi_transfer(COMMAND_WRITE_ENABLE); // Send the EEPROM Write Enable command
  digitalWrite(CS_PIN, HIGH); // Disable EEPROM by setting CS pin high

  delay(10); // Wait for the EEPROM to enable the Write operation

  digitalWrite(CS_PIN, LOW); // Enable EEPROM by setting CS pin low
  spi_transfer(COMMAND_WRITE); // Send the EEPROM Write command
  spi_transfer(MEMORY_MSB); // Send the EEPROM address (MSB)
  spi_transfer(MEMORY_LSB); // Send the EEPROM address (LSB)
  spi_transfer(data); // Send the data to be written
  digitalWrite(CS_PIN, HIGH); // Disable EEPROM by setting CS pin high

  delay(10); // Wait for the EEPROM to complete the Write operation
}

byte spi_transfer(byte data) {
  // Function to transfer a byte using bit-bang method
  byte read_value = 0;
  for (int i = 7; i >= 0; i--) { 
    // Iterate 8 times (foreach bit in byte)
    // Iteration start from the most significant bit (bit 7) and end at the least significant bit (bit 0)
    digitalWrite(SCK_PIN, LOW); // Set the clock low before changing data
    digitalWrite(MOSI_PIN, (data >> i) & 0x01); // Send the bit
    digitalWrite(SCK_PIN, HIGH); // Set the clock high to shift the bit
    read_value |= digitalRead(MISO_PIN) << i; // Read the bit from MISO pin and store it
  }
  return read_value; // Return read data
}