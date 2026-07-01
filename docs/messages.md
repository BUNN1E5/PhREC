# All Supported Messaged

### General Message Layout

All Inital Defined Messages are a 32bit word with the following layout.

On the PhREC Node the chipset used only supports up to 32 so we only allow up to 31 different IDs. You could *technically* add a repeater to extend that but we currently do not support that.

ID 00 is reserved for broadcast

We allocated 6 bit to the message ID to allow up to 64 different messages.

The remaining 16 bits is for additional message information, this can be sensor information, ex the angle sensor data is 14 bits

The last 6 bits are reserved for future use including "non broadcast mode"

0 : 4 (5b) | 5 : 10 (6b) | 11 : 26 (16b) | 27 : 31 (5b)
--- | --- | --- | ---
Node ID | Message ID | Message Data | Reserved

# Special Cases

These messages are for the setup of a device on the network

### 01 : Generate ID
When this message if recieved it will generate 

### 02 : Set ID
When this message is receive
