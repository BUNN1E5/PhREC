# All Supported Messaged

### General Message Layout

All Messages are defined by this basic layout. The first 6 bits are for the message ID. Different message IDs correlate to different messages and special bit layouts

0 : 5 (6b) | 6 : 13 (8b) | 14 : 31 (18b)
--- | --- | ---
Message ID | Node ID | Message Data

Message IDs are split into 2 different types [requests](#requests) and [responses](#responses) as a general rule the response to a request is exactly the not of the request

Some Messages can target a specific node, when that is an option Node ID 000 is reserved for broadcast

Eg. If a node receives a Request Hardware ID (Message ID 1 or 000001), the bitwise NOT response is 111110 (which is -2 in 6-bit signed two's complement), representing the Hardware ID Response.

## Requests

### 0 : Reserved for Empty Messages
This is reserved for empty messages, this is not a valid message. This is the inital state of the message buffer, so it is defined as nothing.

### 1 : Request Hardware ID
0:5 (6b) | 6:7 (2b) | 8:31 (24b)
--- | --- | ---
000001 | Config | Group Offset

If a node recieves this message it will generate a unique ID based on the last 16 bits of its hardware ID.
The node will then wait a time based on it's hardware ID and respond with the [Hardware ID Response](#-2--hardware-id-response) message

Configuration States:
- 00 : Default
- 01 : Auto Compress Node ID
  - Requests the node to try and figure out its own a node ID based all heard nodes and group offset.
- 10 : Undefined
- 11 : Undefines

### 2 : Assign Node ID
0:5 (6b) | 6:13 (8b) | 14:31 (18b)
--- | --- | ---
00010 | Node ID | Hardware ID

Assigns the node an ID to send messages based on the Hardware ID

This request does not have a response

### 3 : Validate Node IDs
0:5 (6b) | 6:31 (26b)
--- | ---
000011 | Undefined

Broadcasts a request to all Node to respond with their node IDs and a CRC-8
Each node will wait their Node ID time and respond with [-4 : Validate Node ID Response](#-4--validate-node-id-response)


### 4 : Randomize Node IDs
0:5 (6b) | 6:13 (8b) | 14:15 (2b) | 16:31 (16b)
--- | :-: | :--: | :-:
00010 | Node ID | Configuration State | Undefined

Requests the given Node ID to randomize its node ID to a non used ID. Given Nodes will respond with

Configuration State:
- 00 : Default
- 01 : Auto Compress Node ID
  - Requests the node to try and compress itself into Node ID gaps new randomized nodes 
- 10 : Undefined
- 11 : Undefined

### 5 : Request Sensor Depth
0:5 (6b) | 6:13 (8b) | 14:31 (18b) 
--- | --- | --- 
001010 | Target Node | Undefined

Requests the total number of sensors on the target node

When target node is `000` the request is set to broadcast and all node will recieve the message


### 10 : Request Sensor Data
Requests the sensor data of all nodes
0:5 (6b) | 6:13 (8b) | 14:21 (8b) | 21:31
--- | --- | --- | --- 
000111 | Target Node | Sensor Depth | Undefined

Requests the sensor data from a specific target node up to a designated maximum number of sensors.

Each sensor will send its own [-11 : Sensor Data Response](#-11--sensor-data-response)

When target node is `000` the request is set to broadcast and all node will recieve the message

### 11 : Request Sensor Data Stream
Requests the sensor data of all nodes
0:5 (6b) | 6:13 (8b) | 14:21 (8b) | 21:31
--- | --- | --- | --- 
000111 | Target Node | Sensor Depth | Undefined

Requests the sensor data from a specific target node up to a designated maximum number of sensors.

Each sensor will send a single [-12 : Sensor Stream Header](#-12--sensor-stream-header) and then a [-13 : Sensor Stream Data](#-13--sensor-stream-data) for each sensor

When target node is `000` the request is set to broadcast and all node will recieve the message

## Responses

### -1 : Reserved for Empty Responses
Responses are defined by the request, and since the 000000 request is defined as nothing, the response (111111) is also nothing.

### -2 : Hardware ID Response
0:5 (6b) | 6:21 (16b) | 22:31 (10b)
--- | --- | ---
111110 | Hardware ID | Undefined

Broadcasts the last 16 bits hardware ID of the node

### -3 : UNDEFINED

### -4 : Validate Node ID Response

0:5 (6b) | 6:13 (8b) | 14:21 (8b) | 22:31 (10b)
--- | --- | --- | ---
111100 | Node ID | CRC-8 | Undefined

Waits Node ID time and responds with a node ID and a CRC-8 of the Node ID. If the CRC-8 fails then we have a collision and the Node ID needs to be reassigned

### -5 : Randomized Node ID Response

0:5 (6b) | 6:13 (8b) | 14:21 (8b) | 22:31 (10b)
--- | --- | --- | ---
111011 | Node ID | CRC-8 | Undefined

Identical to -4 Validate Node ID Response

### -11 : Sensor Data Response
0:5 (6b) | 6:13 (8b) | 14:31 (18b)
--- | --- | --- 
110101 | Node ID | Sensor Data

A single sensor's data from a given Node ID

### -12 : Sensor Stream Header
0:5 (6b) | 6:13 (8b) | 14:31 (18b)
--- | --- | --- 
110101 | Node ID | Sensor Count

Start signal for all sensor data

### -13 : Sensor Stream Data
0:5 (6b) | 6:13 (8b) | 14:31 (18b)
--- | --- | --- 
110101 | Sensor ID | Sensor Data

Sensor data for the node indicated in the last [-12 : Sensor Stream Header](#-12--sensor-stream-header) message