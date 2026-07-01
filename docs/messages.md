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

### Special Cases

In the inital setup of the RS485 network there are special messages that do not follow in the normal

### 00 : Reserved for Empty Messages
This is reserved for empty messages, this is not a valid message. This is the inital state of the message buffer, so it is defined as nothing.